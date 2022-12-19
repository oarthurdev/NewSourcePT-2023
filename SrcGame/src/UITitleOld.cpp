#include "UILinkerOld.h"

UITitleOld::UITitleOld(int iID, char* left, char* middle, char* right, int x, int y, char* text, bool bold, DWORD dwColor)
{
	setID(iID);
	setX(x);
	setY(y);

	Left = new UIImageOld(0, left, 0, 0);
	Middle = new UIImageOld(0, middle, 0, 0);
	Right = new UIImageOld(0, right, 0, 0);
	Text = new UITextOld(0, text, 0, 0, bold);

	Middle->setWidth(Text->getWidth());
	Middle->setX(Left->getWidth());
	Right->setX(Left->getWidth() + Middle->getWidth());
	setHeight(Left->getHeight());
	setWidth(Left->getWidth() + Middle->getWidth() + Right->getWidth());
	Text->setX((getWidth() - Text->getWidth()) / 2);
	Text->setY((getHeight() - Text->getHeight()) / 2);
}

void UITitleOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
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

		Left->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		Middle->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		Right->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		Text->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
	}
}

void UITitleOld::setText(string text)
{
	Text->setText(text);
	Middle->setWidth(Text->getWidth());
	Middle->setX(Left->getWidth());
	Right->setX(Left->getWidth() + Middle->getWidth());
	setHeight(Left->getHeight());
	setWidth(Left->getWidth() + Middle->getWidth() + Right->getWidth());
	Text->setX((getWidth() - Text->getWidth()) / 2);
	Text->setY((getHeight() - Text->getHeight()) / 2);
}
