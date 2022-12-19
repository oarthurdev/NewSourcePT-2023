#ifndef _UTILS__FILESYSTEM_H_
#define _UTILS__FILESYSTEM_H_

#include <cstdio>
#include <cstdlib>
#include <windows.h> 
#include <iostream> 

#define NOT_LOG_IF_NOT_EXSIST 0
#define LOG_IF_NOT_EXSIST 1

FILE* Utils_FileOpen(char* path, char* mode, DWORD LOG_FLAG = NOT_LOG_IF_NOT_EXSIST);
HANDLE Utils_CreateFile(LPCTSTR FileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile, DWORD LOG_FLAG = NOT_LOG_IF_NOT_EXSIST);

#endif
