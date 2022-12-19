#ifndef _UTILS_LOGGING_H_
#define _UTILS_LOGGING_H_

#include <cstdio>
#include <cstdlib>

#define GameLogFile "game.txt"
#define ServerLogFile "server.txt"
#define ErrorLogFile "error.txt"
#define DebugLogFile "debug.txt"
#define SQLLogFile "SQL.txt"

#define LOG_ERROR 1
#define LOG_GAME 2
#define LOG_SERVER 3
#define LOG_DEBUG 4
#define LOG_SQL 5

void Utils_DeleteLogFiles();

void Utils_Log(DWORD type, char* msg, ...);

void Utils_DumpPacket(char* pckname, BYTE* buffer, int size);

#endif