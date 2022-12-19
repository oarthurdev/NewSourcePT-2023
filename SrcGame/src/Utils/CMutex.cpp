#include "CMutex.h"
#include "String.h"

CMutex::CMutex()
{
	STRINGCOPY(szName, "");

	psCriticalSection = new CRITICAL_SECTION;

	InitializeCriticalSection(psCriticalSection);
}

CMutex::CMutex(std::string strName, LPCRITICAL_SECTION lp)
{
	if (lp)
		psCriticalSection = lp;
	else
	{
		psCriticalSection = new CRITICAL_SECTION;
		InitializeCriticalSection(psCriticalSection);
	}

	STRINGCOPY(szName, strName.c_str());
}

void CMutex::Lock(int iID)
{
	EnterCriticalSection(psCriticalSection);
	iIDMutex = iID;

	dwLockTime = GetTickCount();

	bLocked = TRUE;
}

BOOL CMutex::Unlock()
{
	BOOL bRet = FALSE;

	DWORD dwTime = (GetTickCount() - dwLockTime);

	if (dwTime >= 250)
	{
		// WRITEDBG( "Wait Time [%d][%d]", iIDMutex, dwTime );

		bRet = TRUE;
	}

	iIDMutex = 0;

	bLocked = FALSE;

	LeaveCriticalSection(psCriticalSection);

	return bRet;
}