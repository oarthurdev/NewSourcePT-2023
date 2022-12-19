#pragma once

#include <Windows.h>
#include <string>

typedef class CMutex *LPCMUTEX;

class CMutex
{
public:
	CMutex();
	CMutex(std::string strName,LPCRITICAL_SECTION lp = NULL);
	virtual ~CMutex();

	void Lock(int iID = 0);
	BOOL UnLock();
	BOOL Unlock();
private:
	LPCRITICAL_SECTION m_psCritcalSection;
	int m_iIDMutex;
	BOOL m_bLocked;
	std::string m_strName;
	DWORD m_dwLockTime;
};