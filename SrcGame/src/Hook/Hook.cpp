#include "Hook.h"
#include "drawsub.h"
#include "smLib3d\\smd3d.h"
#include <winbase.h>
#include <vector>

using namespace std;

#ifndef _W_SERVER

bool HookAPI(char* moduleName, char* apiName, void* callBack, void* backup = NULL)
{
	void * apiH = NULL;
	DWORD old;

	apiH = GetProcAddress(GetModuleHandle(moduleName), apiName);

	if (apiH == NULL)
		return false;

	if (backup != NULL)
	{
		MoveMemory(backup, apiH, 5);
	}

	VirtualProtect(apiH, 5, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)((DWORD)apiH) = 0xE9;
	*(DWORD*)((DWORD)apiH + 1) = (DWORD)callBack - (DWORD)apiH - 5;
	VirtualProtect(apiH, 5, old, &old);

	return true;
}

int  __stdcall GetFontExtentPoint(HDC hdc, char* lpString, int c, SIZE* lpSize)
{
	RECT rcRect = { 0,0,0,0 };

	ID3DXFont * pCurrentFont = nullptr;

	switch (FontType)
	{
	case 0:
		if (Font)
			pCurrentFont = Font;
		break;
	case 1:
		if (FontBold)
			pCurrentFont = FontBold;
		break;
	}

	if (pCurrentFont)
	{
		if (lpString[c - 1] == ' ')
		{
			char buff[2048] = {};
			RECT rcRect2 = { 0,0,0,0 };

			lstrcpy(buff, lpString);
			lstrcat(buff, "_");

			pCurrentFont->DrawText(NULL, buff, c+1, &rcRect, DT_CALCRECT, FontColor);
			pCurrentFont->DrawText(NULL, "_", 1, &rcRect2, DT_CALCRECT, FontColor);

			lpSize->cx = rcRect.right - rcRect.left - (rcRect2.right - rcRect2.left);
			lpSize->cy = rcRect.bottom - rcRect.top;
		}
		else
		{
			pCurrentFont->DrawText(NULL, lpString, c, &rcRect, DT_CALCRECT, FontColor);

			lpSize->cx = rcRect.right - rcRect.left;
			lpSize->cy = rcRect.bottom - rcRect.top;
		}
	}
	return TRUE;
}

int __stdcall SetFontColor(HDC hdc, DWORD textcolor)
{
	FontColor = D3DCOLOR_RGBA(GetRValue(textcolor), GetGValue(textcolor), GetBValue(textcolor), 255);
	return TRUE;
}

extern int WinSizeX;
extern int WinSizeY;

int __stdcall DrawFont(HDC hdc, int x, int y, char* lpszString, int nCount)
{
	RECT rc;
	rc.left = x;
	rc.right = WinSizeX;
	rc.top = y;
	rc.bottom = WinSizeY;

	char dwFontGame[32] = { 0 };
	//int SizeFontGame = 0;
	
	if ((!Font && FontType == 0) || (!FontBold && FontType == 1))
	{
		GetPrivateProfileString("FontG", "Type", "", dwFontGame, 32, ".\\game\\Font\\Config.ini");
		//SizeFontGame = GetPrivateProfileInt("FontG", "Size", 0, ".\\game\\Font\\Config.ini");
	}

	switch (FontType)
	{
	case 0:
		if (Font)
			return Font->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &Font);
		break;
	case 1:
		if (FontBold)
			return FontBold->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &FontBold);
		break;
	case 2:
		if (FontRank)
			return FontRank->DrawText(NULL, lpszString, nCount, &rc, 0, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &FontBold);
		break;
	}
	return TRUE;
}

int DrawFontRect(HDC hdc, RECT rc, char* lpszString, int nCount, UINT uFormat)
{
	char dwFontGame[32] = { 0 };
	//int SizeFontGame = 0;
	
	if ((!Font && FontType == 0) || (!FontBold && FontType == 1))
	{
		GetPrivateProfileString("FontG", "Type", "", dwFontGame, 32, ".\\game\\Font\\Config.ini");
		//SizeFontGame = GetPrivateProfileInt("FontG", "Size", 0, ".\\game\\Font\\Config.ini");
	}

	switch (FontType)
	{
	case 0:
		if (Font)
			return Font->DrawText(NULL, lpszString, nCount, &rc, uFormat, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &Font);
		break;
	case 1:
		if (FontBold)
			return FontBold->DrawText(NULL, lpszString, nCount, &rc, uFormat, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &FontBold);
		break;
	case 2:
		if (FontRank)
			return FontRank->DrawText(NULL, lpszString, nCount, &rc, uFormat, FontColor);
		else
			D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &FontRank);
		break;
	}
	

	return TRUE;
}

void SetBold(bool bold)
{
	FontType = bold;
}

void InitFont()
{
	char dwFontGame[32] = { 0 };
	//int SizeFontGame = 0;
	GetPrivateProfileString("FontG", "Type", "", dwFontGame, 32, ".\\game\\Font\\Config.ini");
	//SizeFontGame = GetPrivateProfileInt("FontG", "Size", 0, ".\\game\\Font\\Config.ini");

	if (!Font)
		D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &Font);

	if (!FontBold)
		D3DXCreateFont(GRAPHICDEVICE, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY, DEFAULT_PITCH | FF_DONTCARE, dwFontGame, &FontBold);

	HookAPI("gdi32.dll", "TextOutA", &DrawFont);
	HookAPI("gdi32.dll", "SetTextColor", &SetFontColor);
	HookAPI("gdi32.dll", "GetTextExtentPointA", &GetFontExtentPoint);
	HookAPI("gdi32.dll", "GetTextExtentPoint32A", &GetFontExtentPoint);
}

#endif