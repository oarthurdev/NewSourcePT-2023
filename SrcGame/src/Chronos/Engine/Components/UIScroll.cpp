
#include "UIScroll.h"
#include "UIElement.h"
#include "UIImageLoader.h"
#include "UIImageRender.h"
#include "Utils/Macros.h"
#include "Utils/Geometry.h"

namespace UI
{
	Scroll::Scroll(Rectangle2D rRectangle) : Element(rRectangle)
	{
		rScroll = new Rectangle2D(0, 0, 0, 0);
	}

	Scroll::~Scroll()
	{
		DELET(rScroll);
	}

	void Scroll::Clear()
	{
		CLEARPTR(pImage);
		CLEARPTR(pImageScroller);
		CLEARPTR(pImageBackground);
		UI::ImageLoader::DeleteImage(pImage);
		UI::ImageLoader::DeleteImage(pImageScroller);
		UI::ImageLoader::DeleteImage(pImageBackground);

		DELET(rScroll);
	}

	void Scroll::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = GetWidth();
			int iRenderHeight = GetHeight();

			UI::ImageRender::Render(pImage, iRenderX + iSourceX, iRenderY + iSourceY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);

			int iPercent = (bVertical ? rScroll->iY : rScroll->iX);

			// Background render?
			if (pImageBackground)
			{
				int iWidthBackground = bVertical ? iRenderWidth : (iPercent + (iWidthScroller >> 1));
				int iHeightBackground = bVertical ? (iPercent + (iHeightScroller >> 1)) : iRenderHeight;
				UI::ImageRender::Render(pImageBackground, iRenderX + iSourceX, iRenderY + iSourceY, iWidthBackground, iHeightBackground, iSourceX, iSourceY, -1);
			}

			// Scroller render?
			if (pImageScroller)
			{
				int iXScroller = bVertical ? ((iRenderWidth >> 1) - (iWidthScroller >> 1)) : 0;
				int iYScroller = bVertical ? 0 : ((iRenderHeight >> 1) - (iHeightScroller >> 1));
				UI::ImageRender::Render(pImageScroller, iRenderX + iSourceX + iXScroller + rScroll->iX, iRenderY + iSourceY + iYScroller + rScroll->iY, iWidthScroller, iHeightScroller, iSourceX, iSourceY, -1);
			}

			Element::Render(iRenderX, iRenderY, iWidth, iHeight, iSourceX, iSourceY);
		}
	}

	BOOL Scroll::OnMouseClick(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen())
			return FALSE;

		EMouseEvent eEvent = pcMouse->GetEvent();

		if (EMouseEvent::ClickDownL != eEvent && EMouseEvent::ClickUpL != eEvent)
			return FALSE;
		if (eEvent == EMouseEvent::ClickUpL && bScrollable)
		{
			bScrollable = FALSE;
			return TRUE;
		}

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceX;
		int iRenderWidth = GetWidth();
		int iRenderHeight = GetHeight();

		// Inside X?
		if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
		{
			// Inside Y?
			if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
			{
				if (eEvent == ClickDownL)
					bScrollable = TRUE;
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL Scroll::OnMouseScroll(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen())
			return FALSE;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceX;

		int iXScrollBar = iRenderX + (iWidthScroller >> 1);
		int iYScrollBar = iRenderY + (iHeightScroller >> 1);

		if (bVertical)
		{
			rScroll->iY = rScroll->iY - (pcMouse->GetDistance() * 16);
			if (rScroll->iY > (GetHeight() - (iHeightScroller >> 1)))
				rScroll->iY = (int)((float)GetHeight() - (float)(iHeightScroller >> 1));
			else if (rScroll->iY < 0)
				rScroll->iY = 0;
		}

		return TRUE;
	}

	void Scroll::OnMouseMove(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || !bScrollable)
			return;

		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceX;

		int iXScrollBar = iRenderX + (iWidthScroller >> 1);
		int iYScrollBar = iRenderY + (iHeightScroller >> 1);

		if (bVertical)
		{
			rScroll->iY = psPosition->iY - iYScrollBar;
			if (rScroll->iY > (GetHeight() - (iHeightScroller >> 1)))
				rScroll->iY = (int)((float)GetHeight() - (float)(iHeightScroller >> 1));
			else if (rScroll->iY < 0)
				rScroll->iY = 0;
		}
		else
		{
			rScroll->iX = psPosition->iX - iXScrollBar;
			if (rScroll->iX > (GetWidth() - (iWidthScroller >> 1)))
				rScroll->iX = (int)((float)GetWidth() - (float)(iWidthScroller >> 1));
			else if (rScroll->iX < 0)
				rScroll->iX = 0;
		}
	}

	int Scroll::GetPercent()
	{
		float fMinMax = fMaxScroll - fMinScroll;

		float fRet = 0;

		if (bVertical)
			fRet = (((float)rScroll->iY * fMinMax) / ((float)GetHeight() - (float)(iHeightScroller >> 1))) + fMinScroll;
		else
			fRet = (((float)rScroll->iX * fMinMax) / ((float)GetWidth() - (float)(iWidthScroller >> 1))) + fMinScroll;

		return (int)round(fRet);
	}

	void Scroll::SetPercent(int iCur)
	{
		float fMinMax = fMaxScroll - fMinScroll;
		if (iCur >= (int)fMinScroll && iCur <= (int)fMaxScroll)
		{
			iCurrentPercent = iCur;
			if (bVertical)
			{
				rScroll->iY = (int)round(abs((((float)GetHeight() - (float)(iHeightScroller >> 1))* (float)iCur) / fMinMax) + fMinScroll);
				if (rScroll->iY < 0)
					rScroll->iY = 0;
			}
			else
			{
				rScroll->iX = (int)round(abs((((float)GetWidth() - (float)(iWidthScroller >> 1))* (float)iCur) / fMinMax) + fMinScroll);
				if (rScroll->iX < 0)
					rScroll->iX = 0;
			}
		}
	}
}