#include "Debug.h"
#include "global_def.h"
#include "String.h"
#include "Mutex.h"

BOOL CDebug::m_bPrepared = FALSE;

CDebug::CDebug()
{
	m_pcMutex = NULL;
}
CDebug::~CDebug()
{
	DELET(m_pcMutex);
}
void CDebug::WriteDebugger(const char* msg)
{
	OutputDebugString(msg);
}
void CDebug::WriteFile(const char* msg)
{
	SYSTEMTIME time;

	GetLocalTime(&time);

	char szMessage[1024] = { 0 };

	STRINGFORMAT(szMessage, "%02d:%02d:%02d:%03d - %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, msg);

	FILE* fp;

	if (fopen_s(&fp, "DEBUG.log", "a") == 0)
	{
		fputs(szMessage, fp);
		fclose(fp);
	}
}
LPCDEBUG CDebug::GetInstance()
{
	static CDebug d;

	d.Prepare();

	return &d;
}
void CDebug::Prepare()
{
	if (!m_bPrepared)
	{
		m_bPrepared = TRUE;

		m_pcMutex = new CMutex;

		Clear();
	}
}
void CDebug::Clear()
{
	DeleteFileA("DEBUG.log");
}
void CDebug::ErrorBox(const char* msg, ...)
{
	va_list vl;
	char szMessage[1024] = { 0 };

	va_start(vl, msg);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, msg, vl);
	va_end(vl);

	MessageBoxA(NULL, szMessage, "Error", MB_OK | MB_ICONEXCLAMATION);
}

void CDebug::WriteLine(const char* szfile, int line, const char* msg, ...)
{
	va_list vl;
	char szMessage[2048] = { 0 };
	char szFormattedMessage[2048] = { 0 };

	m_pcMutex->Lock();

	va_start(vl, msg);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, msg, vl);
	va_end(vl);

	STRINGFORMAT(szFormattedMessage, "[%04d] [%04d] %s(%d): %s", GetCurrentProcessId(), GetCurrentThreadId(), szfile, line, szMessage);

	WriteDebugger(szFormattedMessage);
	WriteFile(szFormattedMessage);

	m_pcMutex->UnLock();
}