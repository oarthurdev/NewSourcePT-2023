#include "utils_filesystem.h"
#include "utils_logging.h"

FILE* Utils_FileOpen(char* path, char* mode, DWORD LOG_FLAG)
{
	FILE* fp = fopen(path, mode);

	if (!fp && LOG_FLAG == LOG_IF_NOT_EXSIST)
		Utils_Log(LOG_ERROR, "Cannot find file: %s", path);

	return fp;
}

HANDLE Utils_CreateFile(LPCTSTR FileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile,
	DWORD LOG_FLAG)
{
	HANDLE hFile = CreateFile(FileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

	if (hFile == INVALID_HANDLE_VALUE && LOG_FLAG == LOG_IF_NOT_EXSIST)
		Utils_Log(LOG_ERROR, "Cannot find file: %s", FileName);

	return hFile;

}
