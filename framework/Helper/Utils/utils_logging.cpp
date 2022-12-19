#include <iostream>
#include <fstream>
#include <string>
#include "utils_filesystem.h"
#include "utils_logging.h"

void Utils_DeleteLogFiles()
{
	DeleteFile(GameLogFile);
	DeleteFile(ServerLogFile);
	DeleteFile(ErrorLogFile);
	DeleteFile(DebugLogFile);
	DeleteFile(SQLLogFile);
}

void Utils_Log(DWORD type, char* msg, ...)
{
#ifndef _DEBUG
	if(type == LOG_DEBUG)
		return;
#endif

	char buffer[1024];
	va_list args;
	va_start(args, msg);
	vsprintf(buffer, msg, args);


	if(type == LOG_ERROR)
		std::cout << "ERROR: " << buffer << std::endl;
	else if(type == LOG_GAME)
		std::cout << "GAME: " << buffer << std::endl;
	else if(type == LOG_SERVER)
		std::cout << "SERVER: " << buffer << std::endl;
	else if(type == LOG_DEBUG)
		std::cout << "DEBUG: " << buffer << std::endl;
	else if(type == LOG_SQL)
		std::cout << "SQL: " << buffer << std::endl;

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);

	std::ofstream file;

	if(type == LOG_ERROR)
		file.open(ErrorLogFile, std::ios::app);
	else if(type == LOG_GAME)
		file.open(GameLogFile, std::ios::app);
	else if(type == LOG_SERVER)
		file.open(ServerLogFile, std::ios::app);
	else if(type == LOG_DEBUG)
		file.open(DebugLogFile, std::ios::app);
	else if(type == LOG_SQL)
		file.open(SQLLogFile, std::ios::app);

	if(file.fail())
		return;

	file << std::to_string(SystemTime.wHour) + ":" + std::to_string(SystemTime.wMinute) + ":" + std::to_string(SystemTime.wSecond) + " - " << buffer << std::endl;

	file.close();
}

void Utils_DumpPacket(char* pckname, BYTE* buffer, int size)
{
	FILE *fpc = NULL;

	fpc = fopen(pckname, "wb");

	fwrite(buffer, sizeof(BYTE), size, fpc);

	fclose(fpc);
}