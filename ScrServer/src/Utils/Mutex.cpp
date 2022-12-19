#include "Mutex.h"
#include "global_def.h"

CMutex::CMutex() : m_iIDMutex(0), m_bLocked(FALSE), m_strName(""), m_dwLockTime(0)
{
	m_psCritcalSection = new CRITICAL_SECTION;
	InitializeCriticalSection(m_psCritcalSection);
}
CMutex::CMutex(std::string strName, LPCRITICAL_SECTION lp) : m_iIDMutex(0), m_bLocked(FALSE), m_strName(strName), m_dwLockTime(0)
{
	if (lp)
		m_psCritcalSection = lp;
	else
	{
		m_psCritcalSection = new CRITICAL_SECTION;
		InitializeCriticalSection(m_psCritcalSection);
	}
}
CMutex::~CMutex()
{
	DeleteCriticalSection(m_psCritcalSection);

	DELET(m_psCritcalSection);
}
void CMutex::Lock(int iID)
{
	EnterCriticalSection(m_psCritcalSection);
	m_iIDMutex = iID;

	m_dwLockTime = GetTickCount();

	m_bLocked = TRUE;
}
BOOL CMutex::UnLock()
{
	BOOL bRet = FALSE;

	DWORD dwTime = (GetTickCount() - m_dwLockTime);

	if (dwTime >= 250)
	{
		bRet = TRUE;
	}

	m_iIDMutex = 0;

	m_bLocked = FALSE;

	LeaveCriticalSection(m_psCritcalSection);

	return bRet;
}

BOOL CMutex::Unlock()
{
	return UnLock();
}