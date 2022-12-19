#include <Windows.h>
#include <cstddef>
#include <exception>
#include <functional>
#include <new>
#include <type_traits>
#include <utility>
#include <string>
#include <time.h>
#include "_common.h"
#include "String.h"


short RandomS(short l, short h, bool bUseTime)
{
	if (l == h)
		return l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	return (short)(rand() % (h - l)) + l;
}

int RandomI(int l, int h, bool bUseTime)
{
	if (l == h)
		return l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	int i = rand();

	return (i % (h - l)) + l;
}

UINT RandomU(UINT l, UINT h, bool bUseTime)
{
	if (l == h)
		return l;

	h -= l;

	if (bUseTime)
		srand(GetCurrentTime() << 8 | rand());

	USHORT sh1 = RandomI(0, RAND_MAX + 1) + RandomI(0, RAND_MAX + 1);
	USHORT sh2 = RandomI(0, RAND_MAX + 1) + RandomI(0, RAND_MAX + 1);

	UINT i = sh1 | (sh2 << 16);

	return (i % (h - l)) + l;
}

float RandomF(float l, float h)
{
	if (l == h)
		return l;

	return ((((float)rand()) / ((float)RAND_MAX)) * (h - l)) + l;
}

double RandomD(double l, double h)
{
	if (l == h)
		return l;

	return ((((double)rand()) / ((double)RAND_MAX)) * (h - l)) + l;
}

BOOL IsNull(const char* pszString)
{
	if (STRLEN(pszString) <= 0)
		return TRUE;

	if (STRINGCOMPARE(pszString, "NULL"))
		return TRUE;

	return FALSE;
}

BOOL IsNull(int iValue)
{
	if (!iValue)
		return TRUE;

	return FALSE;
}

void ChangeFileExtension(const char* pszFile, const char* pszExt, char* pszBuffer)
{
	int cnt, len;

	STRINGCOPYLEN(pszBuffer, STRLEN(pszFile), pszFile);
	len = STRLEN(pszBuffer);

	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (pszBuffer[cnt] == '.')
		{
			STRINGCOPYLEN(&pszBuffer[cnt + 1], STRLEN(pszExt), pszExt);
			return;
		}
	}

	pszBuffer[len] = '.';
	STRINGCOPYLEN(pszBuffer + len + 1, STRLEN(pszExt), pszExt);
}

void GetDateTime(char* pszDateTime)
{
	char szDate[9] = { 0 };
	char szTime[9] = { 0 };
	_strdate_s(szDate, 9);
	_strtime_s(szTime, 9);

	STRINGFORMATLEN(pszDateTime, 20, "%s %s", szDate, szTime);
}

std::string GetDayOfWeek(int iDay)
{
	switch (iDay)
	{
	case 0:
		return "Sunday";
	case 1:
		return "Monday";
	case 2:
		return "Tuesday";
	case 3:
		return "Wednesday";
	case 4:
		return "Thursday";
	case 5:
		return "Friday";
	case 6:
		return "Saturday";
	}

	return "";
}

BOOL FileExist(const std::string& name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name.c_str(), "rb");
	if (fp)
	{
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}

void SetClipboardText(char* szText)
{
	HGLOBAL x;
	char* y;
	x = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, 0x64);
	y = (char*)GlobalLock(x);
	strcpy_s(y, 0x64, szText);
	GlobalUnlock(x);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, x);
	CloseClipboard();
}

std::string GetClipboardText()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
	{
		return "";
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (hData == nullptr)
	{
		return "";
	}

	// Lock the handle to get the actual text pointer
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
		return "";
	}

	// Save text in a string class instance
	std::string text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}

int GetDaysCountMonth(int iMonth, int iYear)
{
	if ((iMonth == 4) || (iMonth == 6) || (iMonth == 9) || (iMonth == 11))
		return 30;
	else if (iMonth == 2)
	{
		if (((iYear % 400) == 0) || (((iYear % 4) == 0) && ((iYear % 100) != 0)))
			return 29;
		else
			return 28;
	}

	return 31;
}

DWORD SystemTimeToDWORD(SYSTEMTIME* ps)
{
	if (ps == NULL)
		return NULL;

	DWORD dw;
	int iDM = GetDaysCountMonth(ps->wMonth, ps->wYear);

	dw = ps->wSecond + (ps->wMinute * 60) + (ps->wHour * 60 * 60) + (ps->wDay * 60 * 60 * 24) + (ps->wMonth * 60 * 60 * 24 * iDM);

	return dw;
}

DWORD GetFileSize(const char* pszFile)
{
	DWORD dwSize = 0;
	FILE* fp = NULL;
	fopen_s(&fp, pszFile, "rb");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		dwSize = ftell(fp);
		fclose(fp);
	}
	return dwSize;
}