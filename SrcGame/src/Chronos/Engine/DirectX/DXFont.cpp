#include <memory>
#include "DXFont.h"
#include "DXGraphicEngine.h"
#include "Utils/String.h"
#include "FontImage.h"
#include "drawsub.h"
#include "def.h"
#include "Emojize.h"

using namespace DX;

typedef std::shared_ptr<stFontStructure> FontSt_ptr;
//T
bool bCreatedFonts = true;

void DXFont::Init()
{
	AddFontResourceExA("game\\font\\Frutiger.ttf", FR_PRIVATE, NULL);
	AddFontResourceExA("game\\font\\NotoSans-Regular.ttf", FR_PRIVATE, NULL);
}

int DXFont::CreateFont(const char* FontName, int iHeight, int iWidth, BOOL Italic, BOOL Bold, int MemValue)
{
	// Font mismatch ? return pointer
	for (UINT i = 0; i < vFontResource.size(); i++)
	{
		if (STRINGCOMPARE(FontName, vFontResource[i].fname.c_str()))
		{
			if (vFontResource[i].bold == Bold && vFontResource[i].italic == Italic && vFontResource[i].Width == iWidth && vFontResource[i].Height == iHeight)
				return i;
		}
	}

	stFontStructure pFont;
	ZeroMemory(&pFont, sizeof(stFontStructure));

	UINT uWeight = FW_NORMAL;
	if (Bold == TRUE)
		uWeight = FW_BOLD;

	// Create the dx font
	//D3DXCreateFontA( GRAPHICENGINE->GetDevice(), iHeight, iWidth, uWeight, 0, Italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH|FF_DONTCARE, FontName, &pFont.hFont );

	D3DXFONT_DESCA s;
	s.Height = iHeight;
	s.Width = iWidth;
	s.Weight = uWeight;
	s.MipLevels = D3DX_DEFAULT;
	s.Italic = Italic;
	s.CharSet = DEFAULT_CHARSET;
	s.OutputPrecision = OUT_DEFAULT_PRECIS;
	s.Quality = CLEARTYPE_QUALITY;
	s.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	STRINGCOPY(s.FaceName, FontName);

	D3DXCreateFontIndirectA(GRAPHICENGINE->GetDevice(), &s, &pFont.hFont);

	// Set Values
	pFont.Width = iWidth;
	pFont.Height = iHeight;
	pFont.italic = Italic;
	pFont.bold = Bold;
	pFont.fname = FontName;
	pFont.uWidthWhitespace = 0;

	if (vFontResource.size() == 0)
	{
		pFont.hFont->PreloadCharacters(32, 127);
		pFont.hFont->PreloadCharacters(32, 127);
	}

	//Get Width of white space character
	int iWidthUnderline = 0;
	if (pFont.hFont)
	{
		RECT r = { 0, 0, 0, 0 };
		pFont.hFont->DrawTextA(NULL, "_", 1, &r, DT_CALCRECT, -1);
		iWidthUnderline = r.right - r.left;

		r = { 0, 0, 0, 0 };
		pFont.hFont->DrawTextA(NULL, " _", 2, &r, DT_CALCRECT, -1);
		pFont.uWidthWhitespace = (r.right - r.left) - iWidthUnderline;
	}

	// Store in the memory
	if (MemValue < 0)
		vFontResource.push_back(pFont);
	else
		vFontResource[MemValue] = pFont;

	return vFontResource.size() - 1;
}

int DXFont::GetWidthText(int FontObject, const char* Text, INT Size)
{
	if ((int)vFontResource.size() <= FontObject)
		return 0;

	stFontStructure pFont = vFontResource[FontObject];
	if (!pFont.hFont)
		return 0;

	std::string strText(Text);
	int iWidthText = 0;

	for (int i = 0; i < Size; ++i)
	{
		if (strText[i] == 0x20)
			iWidthText += pFont.uWidthWhitespace;
		else
		{
			RECT rcRect = { 0, 0, 0, 0 };

			pFont.hFont->DrawTextA(NULL, &strText[i], 1, &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
			iWidthText += rcRect.right - rcRect.left;
		}
	}

	return iWidthText;
}

int DXFont::GetHeightText(int FontObject, const char* Text, RECT rRect)
{
	if ((int)vFontResource.size() <= FontObject)
		return 0;

	stFontStructure pFont = vFontResource[FontObject];

	if (!pFont.hFont)
		return 0;

	pFont.hFont->DrawTextA(NULL, Text, lstrlenA(Text), &rRect, DT_WORDBREAK | DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	return rRect.bottom - rRect.top;
}

int DXFont::GetHeightText(int FontObject, UINT uFormat, const char* Text, RECT rRect)
{
	if ((int)vFontResource.size() <= FontObject)
		return 0;

	stFontStructure pFont = vFontResource[FontObject];

	if (!pFont.hFont)
		return 0;

	pFont.hFont->DrawTextA(NULL, Text, lstrlenA(Text), &rRect, uFormat | DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	return rRect.bottom - rRect.top;
}

int DXFont::GetHeightText(int iFontID)
{
	if ((int)vFontResource.size() <= iFontID)
		return 0;

	// Get Font in the memory
	stFontStructure pFont = vFontResource[iFontID];

	RECT rcRect = { 0, 0, 0, 0 };

	// calculate required rect
	if (!pFont.hFont)
		return 0;

	return pFont.Height;
}

void DXFont::Draw(int FontObject, int x, int y, const std::string& pText, UINT uFormat, D3DCOLOR Color)
{
	RECT rect{ x, y, RESOLUTION_WIDTH + x, RESOLUTION_HEIGHT + y };

	Draw(FontObject, rect, pText.c_str(), pText.length(), uFormat, Color);
}

void DXFont::Draw(int FontObject, RECT& rRect, LPCTSTR Text, INT Count, UINT uFormat, D3DCOLOR Color)
{
	if ((int)vFontResource.size() <= FontObject)
		return;

	// Get Font in the memory
	stFontStructure pFont = vFontResource[FontObject];
	int iCount = Count;

	if (iCount <= 0)
		iCount = lstrlenA(Text);

	static char szBuf[2048];
	ZeroMemory(szBuf, 2048);
	wsprintfA(szBuf, "%s ", Text);

	// Draw
	if (bCreatedFonts)
	{
		if (pFont.hFont)
		{
			pFont.hFont->DrawTextA(NULL, szBuf, iCount + 1, &rRect, uFormat, Color);
			// pFont.hFont->DrawTextW( NULL, wTextDraw, STRLENW( wTextDraw ), &rRect, uFormat, Color );
		}
	}
}

void DXFont::Draw(int FontObject, RECT& rRect, const std::string& strText, UINT uFormat, D3DCOLOR Color)
{
	Draw(FontObject, rRect, strText.c_str(), strText.length(), uFormat, Color);
}

void DXFont::DrawBellatraFont(int x, int y, float Size, DWORD Color, const char* Text, ...)
{
	va_list ap;
	char szBuf[2048];
	ZeroMemory(szBuf, 2048);
	va_start(ap, Text);
	_vsnprintf_s(szBuf, 2048, 2047, Text, ap);
	va_end(ap);

	DrawFontImage(szBuf, x, y, Color, Size);
}


void DXFont::OnResetDevice()
{
	if (vFontResource.size() == 0)
		return;

	// Loop for release the reset font

	for (int i = 0; i < (int)vFontResource.size(); i++)
		vFontResource[i].hFont->OnResetDevice();
}

void DXFont::OnLostDevice()
{

	if (vFontResource.size() == 0)
		return;

	for (int i = 0; i < (int)vFontResource.size(); i++)
		vFontResource[i].hFont->OnLostDevice();
}

void DXFont::ReCreateFontDevice()
{
	if (vFontResource.size() == 0)
		return;

	FontSt_ptr pFont = std::make_shared<stFontStructure>();

	// Loop for recreate released fonts

	for (int i = 0; i < (int)vFontResource.size(); i++)
	{
		// this->CreateFontDX( ( char* )vFontResource[ i ].fname.c_str( ), vFontResource[ i ].iHeight, vFontResource[ i ].italic, vFontResource[ i ].bold, i );
	}

	bCreatedFonts = true;
}


DXFont::~DXFont()
{
}

D3DCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

int DX::DrawText(HDC hdc, int x, int y, LPCTSTR lpszString, int nCount)
{
	if (dsDrawOffset_X || dsDrawOffset_Y)
	{
		if (dsDrawOffsetArray & dsARRAY_RIGHT)
			x += dsDrawOffset_X;

		if (dsDrawOffsetArray & dsARRAY_BOTTOM)
			y += dsDrawOffset_Y;
	}

	RECT rc;
	rc.left = x;
	rc.right = x + RESOLUTION_WIDTH;
	rc.top = y;
	rc.bottom = y + RESOLUTION_HEIGHT;

	std::string text(cEmoji.handleEmoji(lpszString, x, y));
	FONTHANDLER->Draw(0, rc, text.c_str(), nCount, DT_WORDBREAK, fontColor);
	//FONTHANDLER->Draw(0, rc, lpszString, nCount, DT_WORDBREAK, fontColor);

	return TRUE;
}

void DX::SetTextColor(HDC hdc, COLORREF crColor)
{
	fontColor = D3DCOLOR_RGBA(GetRValue(crColor), GetGValue(crColor), GetBValue(crColor), 255);
}


BOOL DX::GetTextExtentPoint(HDC hdc, LPCTSTR lpString, int c, LPSIZE  lpSize, int fontObject)
{
	RECT rcRect = { 0,0,0,0 };

	lpSize->cx = FONTHANDLER->GetWidthText(fontObject, lpString, c);
	lpSize->cy = FONTHANDLER->GetHeightText(fontObject, lpString, RECT{ 0,0,0,0 });

	return TRUE;
}