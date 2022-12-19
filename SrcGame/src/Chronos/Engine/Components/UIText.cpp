#include "UIText.h"
#include "UI.h"
#include "UIEvent.h"
#include "DXFont.h"
#include <vector>

namespace UI
{
	Text::Text(Rectangle2D rRectangle) : Element(rRectangle)
	{
		iFontHandler = FONTHANDLER->CreateFont("Arial", 16, 0, FALSE, FALSE, -1);
	}

	Text::Text(const std::string& strText, const Rectangle2D& rBox, BOOL bBold, const DWORD dwColor) : Element(rBox)
	{
		iFontHandler = FONTHANDLER->CreateFont("Arial", 16, 0, FALSE, bBold, dwColor);
		SetColor(dwColor);
		SetText(strText);
	}

	Text::Text(const Rectangle2D& rBox, BOOL bBold, const DWORD dwColor) : Element(rBox)
	{
		iFontHandler = FONTHANDLER->CreateFont("Arial", 16, 0, FALSE, bBold, dwColor);
		SetColor(dwColor);
	}

	Text::~Text()
	{
	}

	void Text::Clear()
	{
	}

	void Text::SetFont(const char* pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		iFontHandler = FONTHANDLER->CreateFont(pszFont, iHeight, iWidth, bItalic, bBold, -1);
		dwColorText = dwColor;
	}

	int Text::GetHeightFont()
	{
		return FONTHANDLER->GetHeightText(iFontHandler);
	}

	void Text::UpdateText()
	{
		strHighlightText = "";

		if (iMaxTextWidth > 0)
		{
			int iTextWidth = 0;
			const char* pszText = strText.c_str();

			for (UINT i = 0; i < strText.size(); i++)
			{
				char c = pszText[i];

				int iWidth = FONTHANDLER->GetWidthText(iFontHandler, &c, 1);

				iTextWidth += iWidth;

				if (iTextWidth >= iMaxTextWidth)
				{
					strText.insert(strText.begin() + i, '\n');
					iTextWidth = 0;
				}
			}
		}

		if (bHighlightText)
		{
			if (strText.find(":") != std::string::npos)
			{
				strHighlightText = strText.substr(0, strText.find(":") + 1);
				strText = strText.substr(strText.find(":") + 1);
				iHighlightTextWidth = FONTHANDLER->GetWidthText(iFontHandler, strHighlightText.c_str(), strHighlightText.length());
			}
		}
	}

	int Text::GetCountLines()
	{
		int iLengthText = strText.length();

		if (iLengthText <= 0)
			return 0;

		int iCountLines = 1;

		for (int i = 0; i < iLengthText; i++)
		{
			if (strText[i] == '\n')
				iCountLines++;
		}

		return iCountLines;
	}

	void Text::SetTextEx(char* pszFormat, ...)
	{
		va_list vl;

		char szText[32768];

		va_start(vl, pszFormat);
		_vsnprintf_s(szText, _countof(szText), _TRUNCATE, pszFormat, vl);
		va_end(vl);

		SetText(szText);
	}

	int Text::GetTextWidth()
	{
		if (bHighlightText)
		{
			int iWidthText = -1;
			iWidthText = FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), strText.find('\n') != std::string::npos ? strText.find('\n') : strText.length());

			return FONTHANDLER->GetWidthText(iFontHandler, strHighlightText.c_str(), strHighlightText.length()) + iWidthText;
		}

		return FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), strText.length());
	}

	int Text::GetHeightText()
	{
		int iRenderX = GetX();
		int iRenderY = GetY();
		int iRenderWidth = GetWidth();
		int iRenderHeight = GetHeight();

		RECT rRect;
		rRect.left = iRenderX;
		rRect.top = iRenderY;
		rRect.right = rRect.left + GetWidth();
		rRect.bottom = rRect.top + GetHeight();

		return FONTHANDLER->GetHeightText(iFontHandler, BuildFormat(), strText.c_str(), rRect);
	}

	void Text::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		// Is activated Button?
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		DWORD dwColor = dwColorText;

		if (dwColorTextLink != 0 && bHover && !bDisable)
			dwColor = dwColorTextLink;

		RECT rRect;
		rRect.left = iRenderX;
		rRect.top = iRenderY;
		rRect.right = rRect.left + GetWidth();
		rRect.bottom = rRect.top + GetHeight();

		if (bHighlightText && strHighlightText.length() > 0 && IsOpen() && !bDisable)
		{
			//vector Delimiter
			std::vector<std::string> vLines = split(strText, '\n');

			for (size_t i = 0; i < vLines.size(); i++)
			{
				if (i == 0)
				{
					if (bShadow)
					{
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iShadowDistance, rRect.top + iShadowDistance, rRect.right, rRect.bottom }, strHighlightText, BuildFormat(), dwColorTextShadow != -1 ? dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth + iShadowDistance, rRect.top + iShadowDistance, rRect.right, rRect.bottom }, vLines[i], BuildFormat(), dwColorTextShadow != -1 ? dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
					}
					else if (dwColorTextOutline)
					{
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + 1, rRect.top, rRect.right, rRect.bottom }, strHighlightText, BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth + 1, rRect.top, rRect.right, rRect.bottom }, vLines[i], BuildFormat(), dwColorTextOutline);

						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, rRect.top + 1, rRect.right, rRect.bottom }, strHighlightText, BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth, rRect.top + 1, rRect.right, rRect.bottom }, vLines[i], BuildFormat(), dwColorTextOutline);

						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left - 1, rRect.top, rRect.right, rRect.bottom }, strHighlightText, BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth - 1, rRect.top, rRect.right, rRect.bottom }, vLines[i], BuildFormat(), dwColorTextOutline);

						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, rRect.top - 1, rRect.right, rRect.bottom }, strHighlightText, BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth, rRect.top - 1, rRect.right, rRect.bottom }, vLines[i], BuildFormat(), dwColorTextOutline);
					}

					FONTHANDLER->Draw(iFontHandler, rRect, strHighlightText, BuildFormat(), dwColorTextHighlight);
					FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iHighlightTextWidth,rRect.top,rRect.right + iHighlightTextWidth,rRect.bottom }, vLines[i], BuildFormat(), dwColor);
				}
				else
				{
					UINT uYLine = GetHeightFont() * i;

					if (bShadow)
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iShadowDistance,(LONG)(rRect.top + uYLine + iShadowDistance),rRect.right,(LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColorTextShadow != -1 ? dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
					else if (dwColorTextOutline)
					{
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + 1, (LONG)(rRect.top + uYLine), rRect.right, (LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, (LONG)(rRect.top + uYLine) + 1, rRect.right, (LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left - 1, (LONG)(rRect.top + uYLine), rRect.right, (LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColorTextOutline);
						FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, (LONG)(rRect.top + uYLine - 1), rRect.right, (LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColorTextOutline);
					}

					FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left,(LONG)(rRect.top + uYLine),rRect.right,(LONG)(rRect.bottom + uYLine) }, vLines[i], BuildFormat(), dwColor);
				}
			}
		}
		else if (!bHighlightText && IsOpen() && !bDisable)
		{
			if (bShadow)
				FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + iShadowDistance, (LONG)(rRect.top + iShadowDistance), rRect.right, (LONG)(rRect.bottom) }, strText, BuildFormat(), dwColorTextShadow != -1 ? dwColorTextShadow : D3DCOLOR_XRGB(74, 74, 74));
			else if (dwColorTextOutline)
			{
				FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left + 1, (LONG)(rRect.top), rRect.right, (LONG)(rRect.bottom) }, strText, BuildFormat(), dwColorTextOutline);
				FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, (LONG)(rRect.top + 1), rRect.right, (LONG)(rRect.bottom) }, strText, BuildFormat(), dwColorTextOutline);
				FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left - 1, (LONG)(rRect.top), rRect.right, (LONG)(rRect.bottom) }, strText, BuildFormat(), dwColorTextOutline);
				FONTHANDLER->Draw(iFontHandler, RECT{ rRect.left, (LONG)(rRect.top - 1), rRect.right, (LONG)(rRect.bottom) }, strText, BuildFormat(), dwColorTextOutline);
			}

			FONTHANDLER->Draw(iFontHandler, rRect, strText, BuildFormat(), dwColor);
		}
		else if (IsOpen() && bDisable)
			FONTHANDLER->Draw(iFontHandler, rRect, strText, BuildFormat(), D3DCOLOR_ARGB(255, 135, 135, 135));

		Element::Render(iRenderX, iRenderY, GetWidth(), GetHeight(), iSourceX, iSourceY);
	}

	void Text::Update(float fTime)
	{
	}

	UINT Text::BuildFormat() const
	{
		UINT uFormat = DT_EXPANDTABS;

		switch (eHorizontalAlign)
		{
		default:
		case ALIGN_Left:
			uFormat |= DT_LEFT;
			break;
		case ALIGN_Center:
			uFormat |= DT_CENTER;
			break;
		case ALIGN_Right:
			uFormat |= DT_RIGHT;
			break;
		}

		switch (eVerticalAlign)
		{
		default:
		case ALIGN_Top:
			uFormat |= DT_TOP;
			break;
		case ALIGN_Middle:
			uFormat |= DT_VCENTER;
			break;
		case ALIGN_Bottom:
			uFormat |= DT_BOTTOM;
			break;
		}

		if (!bMultiLine)
			uFormat |= DT_SINGLELINE;

		if (bWordWrap)
			uFormat |= DT_WORDBREAK;

		if (bNoClip)
			uFormat |= DT_NOCLIP;

		return uFormat;
	}

	BOOL Text::OnMouseClick(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return FALSE;

		if (eMouseEvent != pcMouse->GetEvent())
			return FALSE;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		// Inside X?
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			// Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (bSelectType)
				{
					if (pGroupMain)
					{
						if (!bSelect)
							pGroupMain->SetIndexObject(GetID());
						bSelect = TRUE;

					}
					else
						bSelect = bSelect ? FALSE : TRUE;
				}
				if (bSelectType || iEventID != (-1))
				{
					UI::Event::Invoke(iEventID);
					return TRUE;
				}
			}
		}
		return FALSE;
	}

	void Text::OnMouseMove(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();


		BOOL bOldHover = bHover;

		bHover = FALSE;

		//Inside X?
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			//Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				bHover = TRUE;

				if (bHover != bOldHover && (iHoverEventID != (-1)))
				{
					UI::Event::Invoke(iHoverEventID);
				}
			}
		}
	}
}
