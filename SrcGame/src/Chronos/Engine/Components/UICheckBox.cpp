
#include "UICheckBox.h"
#include "UIElement.h"
#include "UIImageRender.h"
#include "UIImageLoader.h"
#include "UIEvent.h"
#include "Mouse/Mouse.h"
#include "DXFont.h"
#include "Utils/Geometry.h"
#include "Utils/Macros.h"
#include "Utils/String.h"

namespace UI
{
	CheckBox::CheckBox(Rectangle2D rRectangle) : Element(rRectangle)
	{}

	CheckBox::~CheckBox()
	{}

	void CheckBox::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			if (pGroupMain)
			{
				if (!pGroupMain->IsOpen())
					return;

				if (pGroupMain->GetIndexObject() != GetID())
					bSelect = FALSE;
				else
					bSelect = TRUE;
			}
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			UI::ImageRender::Render(pImage, iRenderX, iRenderY, GetWidth(), GetHeight(), -1);
			if (bSelect)
				UI::ImageRender::Render(pImage2, iRenderX, iRenderY, GetWidth(), GetHeight(), -1);

			FONTHANDLER->Draw(iFontHandler, iRenderX + GetWidth() + 5, iRenderY + ((GetHeight() >> 1) - (iFontHeight >> 1)), strText, DT_WORDBREAK, dwColorText);

			Element::Render(iRenderX, iRenderY, GetWidth(), GetHeight(), iSourceX, iSourceY);
		}
	}

	BOOL CheckBox::OnMouseClick(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return FALSE;

		if (pGroupMain)
		{
			if (!pGroupMain->IsOpen())
				return FALSE;
		}

		if (EMouseEvent::ClickDownL != pcMouse->GetEvent())
			return FALSE;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		// Inside X?
		int iWidthText = FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), strText.length());
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iWidthText + iRenderWidth - iSourceX)))
		{
			// Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (pGroupMain)
				{
					if (!bSelect)
						pGroupMain->SetIndexObject(GetID());
					bSelect = TRUE;

				}
				else
					bSelect = bSelect ? FALSE : TRUE;

				UI::Event::Invoke(iEventID);
				return TRUE;
			}
		}
		return FALSE;
	}

	void CheckBox::Clear()
	{
		CLEARPTR(pImage);
		CLEARPTR(pImage2);
		UI::ImageLoader::DeleteImage(pImage);
		UI::ImageLoader::DeleteImage(pImage2);
	}

	void CheckBox::SetFont(const char* pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		iFontHandler = FONTHANDLER->CreateFont(pszFont, iHeight, iWidth, bItalic, bBold, -1);
		iFontHeight = iHeight;
		dwColorText = dwColor;
	}
}