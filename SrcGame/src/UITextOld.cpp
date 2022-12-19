#include "UILinkerOld.h"
#include "DXFont.h"

char* FormatString(char* fmt, ...)
{
	static char buff[4096];

	ZeroMemory(buff, sizeof(buff));

	va_list args;

	va_start(args, fmt);
	vsprintf(buff, fmt, args);
	va_end(args);

	return buff;
}

UITextOld::UITextOld(int iID, char* Text, int x, int y, bool bold)
{
	ZeroMemory(szText, sizeof(szText));
	bBold = false;
	iFontHandler = FONTHANDLER->CreateFont("Arial", 15, 0, FALSE, bold ? TRUE : FALSE, -1);

	setID(iID);
	setX(x);
	setY(y);
	bBold = bold;

	lstrcpy(szText, Text);

	SIZE sz = {};
	DX::GetTextExtentPoint(NULL, szText, lstrlen(szText), &sz, iFontHandler);
	setWidth(sz.cx);
	setHeight(sz.cy);
}

void UITextOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();
		int iStartX = cX < iSourceX ? abs(cX - iSourceX) : 0;
		int iStartY = cY < iSourceY ? abs(cY - iSourceY) : 0;

		int iRenderX = cX + iX + iStartX;
		int iRenderY = cY + iY + iStartY;

		int iRenderWidth = low(cWidth, iWidth);
		int iRenderHeight = low(cHeight, iHeight);

		if (cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX + iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		UINT uFormat = 0;

		if (iStartX > 0)
		{
			uFormat |= DT_RIGHT;
		}

		if (iStartY > 0)
		{
			uFormat |= DT_BOTTOM;
		}

		FONTHANDLER->Draw(iFontHandler, RECT({ iRenderX, iRenderY, iRenderX + iRenderWidth - iStartX, iRenderY + iRenderHeight - iStartY }), szText, uFormat, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void UITextOld::AddChar(char Code)
{
	if (lstrlen(szText) < 254)
	{
		szText[lstrlen(szText)] = Code;
		szText[lstrlen(szText)] = 0;

		SIZE sz = {};
		DX::GetTextExtentPoint(NULL, szText, lstrlen(szText), &sz, iFontHandler);
		setWidth(sz.cx);
		setHeight(sz.cy);
	}
}

void UITextOld::RemoveChar(int count)
{
	if (lstrlen(szText) >= count && count > 0)
	{
		szText[lstrlen(szText) - count] = 0;

		SIZE sz = {};
		DX::GetTextExtentPoint(NULL, szText, lstrlen(szText), &sz, iFontHandler);
		setWidth(sz.cx);
		setHeight(sz.cy);
	}
}

void UITextOld::setText(string text)
{
	lstrcpy(szText, text.c_str());

	SIZE sz = {};
	DX::GetTextExtentPoint(NULL, szText, lstrlen(szText), &sz, iFontHandler);
	setWidth(sz.cx);
	setHeight(sz.cy);
}
