#pragma once

#include <Windows.h>
#include "Mutex.h"

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define ERRORBOX( msg, ... ) CDebug::GetInstance()->ErrorBox( msg, ##__VA_ARGS__ )
#define WRITEDBG( msg, ... ) {CDebug::GetInstance()->WriteLine( __FILENAME__, __LINE__, msg, ##__VA_ARGS__ ); }

typedef class CDebug* LPCDEBUG;

class CDebug
{
public:
	CDebug();
	virtual ~CDebug();

	static LPCDEBUG GetInstance();

	void Prepare();
	void Clear();
	void ErrorBox(const char* msg, ...);
	void WriteLine(const char* szfile, int line, const char* msg, ...);
	void WriteDump(const char* szfile, void* dmp, int size);
protected:
	void WriteDebugger(const char* msg);
	void WriteFile(const char* msg);
private:
	static BOOL m_bPrepared;
	LPCMUTEX m_pcMutex;
};