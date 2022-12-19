#include "UILinkerOld.h"

UIHorizontalScrollOld::UIHorizontalScrollOld(int iID, int x, int y, int minValue, int maxValue, int startValue)
{
	setID(iID);
	setX(x);
	setY(y);

	ScrollBarBg = new UIImageOld(0, "game\\GUI\\Settings\\scroll\\barbg.png", x, y);
	ScrollBar = new UIImageOld(0, "game\\GUI\\Settings\\scroll\\bar.png", x, y);
	ScrollButton = new UIImageOld(0, "game\\GUI\\Settings\\scroll\\icon.png", x - 10, y - 6);

	setWidth(ScrollBarBg->getWidth());
	setHeight(ScrollBarBg->getHeight());

	setMin(minValue);
	setMax(maxValue);

	if (startValue >= 0)
		setValue(startValue);
	else
		setValue(((getMax() - getMin()) / 2) + getMin());

	ScrollButton->setX(ScrollBar->getX() + ScrollBar->getWidth() - 10);
}

void UIHorizontalScrollOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
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

		if(cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX+ iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		ScrollBarBg->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
		ScrollBar->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
		ScrollButton->Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
	}
}

bool UIHorizontalScrollOld::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

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

		if(cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX+ iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		if (isMousePos(iRenderX, iRenderY - iStartY, iRenderWidth, iRenderHeight))
		{
			if (Type == Down)
			{
				bTrackX = true;

				if (pRealCursorPos.x >= iRenderX && pRealCursorPos.x <= iRenderX + iRenderWidth)
					updateButtonPos(pRealCursorPos.x - iX);
			}
			else if(Type == Up)
			{
				bTrackX = false;
			}
			return true;
		}

		if (Type == Up)
		{
			bTrackX = false;
		}
	}
	return false;
}

bool UIHorizontalScrollOld::OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		if (bTrackX)
		{
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

			if(cX + iRenderWidth > iWidth)
				iRenderWidth -= (cX+ iRenderWidth) - iWidth;

			if (cY + iRenderHeight > iHeight)
				iRenderHeight -= (cY + iRenderHeight) - iHeight;

			if(pRealCursorPos.x >= iRenderX && pRealCursorPos.x <= iRenderX + iRenderWidth)
				updateButtonPos(pRealCursorPos.x - iX);
		}
		return true;
	}
	return false;
}

void UIHorizontalScrollOld::updateBar()
{
	ScrollBar->setWidth((int)(ScrollBar->getTrueWidth() * ((getValue() - getMin()) / static_cast<float>(getMax() - getMin()))));
}

void UIHorizontalScrollOld::updateButtonPos(int iX)
{
	ScrollButton->setX(iX-10);

	int interval = iX - getX();
	float percent = interval / (float)getWidth();
	setValue(((getMax() - getMin()) * percent) + getMin());
}
