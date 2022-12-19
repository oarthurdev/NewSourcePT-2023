
#include "UIButton.h"
#include "UIElement.h"
#include "UIText.h"
#include "UIImageRender.h"
#include "UIImageLoader.h"
#include "UIEvent.h"
#include "Mouse/Mouse.h"
#include "Utils/Geometry.h"
#include "Utils/FileReader.h"
#include "Utils/String.h"
#include "Utils/Macros.h"

namespace UI
{
	Button::Button(Rectangle2D rRectangle) : Element(rRectangle)
	{

	}

	Button::~Button()
	{
	}

	void Button::Clear()
	{
		CLEARPTR(pImage);
		CLEARPTR(pImageActive);
		CLEARPTR(pImageDisable);
		UI::ImageLoader::DeleteImage(pImage);
		UI::ImageLoader::DeleteImage(pImageActive);
		UI::ImageLoader::DeleteImage(pImageDisable);
	}

	void Button::SetActiveImage(std::pair<class UI::Image*, class UI::Image*> pPair)
	{
		pImage = pPair.first;
		pImageActive = pPair.second;
	}

	void Button::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			if ((iWidth - GetX()) <= 0)
				return;

			if ((iHeight - GetY()) <= 0)
				return;

			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = low(GetWidth(), iWidth - GetX());
			int iRenderHeight = low(GetHeight(), iHeight - GetY());

			if (bDisable)
			{
				UI::ImageRender::Render(pImageDisable, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				bHover = FALSE;
				bSelect = FALSE;
				return;
			}

			if (bCanHold && bHolding)
				UI::Event::Invoke(iEventID);

			if (bHover || bSelect)
			{
				if (pGroupMain)
				{
					if (pGroupMain->GetIndexObject() != GetID())
						bSelect = FALSE;
				}
				UI::ImageRender::Render(pImageActive, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
			}
			else
				UI::ImageRender::Render(pImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);

			Element::Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		}
	}



	BOOL Button::OnMouseClick(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return FALSE;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		if (bCanHold && bHolding && (pcMouse->GetEvent() == ClickUpL || pcMouse->GetEvent() == ClickUpR))
			bHolding = FALSE;

		// Inside X?
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			// Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				//Dropdown Menu
				if ((pDropdownMenu) && !pDropdownMenu->IsOpen() && pDropdownMenu->GetMouseEvent() == pcMouse->GetEvent())
				{
					pDropdownMenu->Open();
					return TRUE;
				}
				else if ((pDropdownMenu) && pDropdownMenu->IsOpen() && pDropdownMenu->GetMouseEvent() == pcMouse->GetEvent())
				{
					pDropdownMenu->Close();
					return TRUE;
				}

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

				if (iEventID && eMouseEvent == pcMouse->GetEvent() || bHolding)
				{
					if (bCanHold)
						bHolding = TRUE;

					UI::Event::Invoke(iEventID);
					return TRUE;
				}
			}
		}

		return FALSE;
	}

	void Button::OnMouseMove(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		bHover = FALSE;
		// Inside X?
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			// Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				bHover = TRUE;
			}
		}
	}
}