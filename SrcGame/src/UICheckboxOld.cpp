#include "UILinkerOld.h"
DWORD dwNumC = 0;
UICheckboxOld::UICheckboxOld(int ID, int x, int y, char* szText, bool free, bool selected, bool hover, bool bold)
{
	Image = new UIImageOld(ID, "game\\settings\\checkbox.tga", x, y + 2);

	if (!Image)
		return;

	Image_ = new UIImageOld(ID, "game\\settings\\checkbox_.tga", x, y + 2);

	if (lstrlen(szText) > 0)
	{
		pText = new UITextOld(0, szText, x + Image->getWidth() + 5, y, bold);

		setWidth(Image->getWidth() + pText->getWidth() + 5);
		setHeight((Image->getHeight() > pText->getHeight() ? Image->getHeight() : pText->getHeight()) + 2);
	}
	else
	{
		setWidth(Image->getWidth());
		setHeight(Image->getHeight());
	}

	setID(ID);
	setX(x);
	setY(y);

	setHover(hover);
	setSelected(selected);
	setFree(free);
}

UICheckboxOld::UICheckboxOld(int ID, int x, int y, char* path, char* path_, char* szText, bool free, bool selected, bool hover, bool bold)
{
	Image = new UIImageOld(ID, path, 0, 0);

	if (!Image)
		return;

	Image_ = new UIImageOld(ID, path_, 0, 0);

	if (lstrlen(szText) > 0)
	{
		pText = new UITextOld(0, szText, Image->getWidth() + 5, 0, bold);

		setWidth(Image->getWidth() + pText->getWidth() + 5);
		setHeight((Image->getHeight() > pText->getHeight() ? Image->getHeight() : pText->getHeight()) + 2);
	}
	else
	{
		setWidth(Image->getWidth());
		setHeight(Image->getHeight());
	}

	setID(ID);
	setX(x);
	setY(y);

	setHover(hover);
	setSelected(selected);
	setFree(free);
}

void UICheckboxOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
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

		if (((isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight) && getHover()) || getSelected()) && Image_)
		{
			if (pText)
				pText->setHover(true);
			Image_->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iStartX, iStartY);
			if (isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight) && getHover() && fHover)
				fHover();

		}
		else
		{
			if (pText)
				pText->setHover(false);
			Image->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iStartX, iStartY);
		}

		if (pText)
		{
			pText->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iStartX, iStartY);
		}

	}
}

bool UICheckboxOld::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible() && Type != Up)
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

		if (cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX + iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		if (isMousePos(iRenderX, iRenderY - iStartY, iRenderWidth, iRenderHeight))
		{
			if (getFree())
				setSelected(!getSelected());

			if (Activation)
				Activation();
			return true;
		}
	}
	return false;
}
