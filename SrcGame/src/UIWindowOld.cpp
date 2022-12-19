#include "UILinkerOld.h"

UIWindowOld::UIWindowOld(int ID, char * path, int x, int y, bool fixed)
{
	Background = new UIImageOld(ID, path, 0, 0);
	if (!Background)
		return;

	setID(ID);

	setX(x);
	setY(y);

	setWidth(Background->getWidth());
	setHeight(Background->getHeight());

	setType(1);
	setFixed(fixed);
}

UIWindowOld::UIWindowOld(int ID, char * top, char * mid, char * bot, int x, int y, bool fixed)
{
	bgSplit[0] = new UIImageOld(0, top, 0, 0);
	if (!bgSplit[0])
		return;

	bgSplit[1] = new UIImageOld(0, mid, 0, bgSplit[0]->getHeight());
	if (!bgSplit[1])
		return;

	bgSplit[2] = new UIImageOld(0, bot, 0, bgSplit[0]->getHeight() + bgSplit[1]->getHeight());
	if (!bgSplit[2])
		return;

	setID(ID);

	setX(x);
	setY(y);

	setWidth(bgSplit[0]->getWidth());
	setHeight(bgSplit[0]->getHeight() + bgSplit[1]->getHeight() + bgSplit[2]->getHeight());

	setType(2);
	setFixed(fixed);
}

UIWindowOld::UIWindowOld(int ID, int x, int y, int w, int h, bool fixed)
{
	setID(ID);
	setX(x);
	setY(y);
	setWidth(w);
	setHeight(h);
	setFixed(fixed);

	Background = 0;

	setType(1);
}

UIWindowOld::~UIWindowOld()
{
	for (auto element : vElements)
		if (element)
			delete element;
}

void UIWindowOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();

		int iScroll = pVerticalScroll ? pVerticalScroll->getValue() : 0;

		int iStartX = cX < iSourceX ? abs(cX - iSourceX) : 0;
		int iStartY = cY < iSourceY ? abs(cY - iSourceY) : 0;
		int iRenderWidth = low(cWidth, iWidth);
		int iRenderHeight = low(cHeight, iHeight);
		int iRenderX = cX + iX + iStartX;
		int iRenderY = cY + iY + iStartY;

		if (cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX + iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		if (Background) //Background corrigido por Leo
			Background->Render(iRenderX, iRenderY, cWidth, cHeight, iSourceX, iSourceY);

		for (auto element : vElements)
		{
			element->Render(iRenderX, iRenderY - iScroll, iRenderWidth, iRenderHeight + iScroll, iSourceX, iSourceY + iScroll);
		}

		if (pVerticalScroll)
			pVerticalScroll->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
	}
}

bool UIWindowOld::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();

		int iScroll = pVerticalScroll ? pVerticalScroll->getValue() : 0;

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

		if (isMousePos(iRenderX, iRenderY - iStartY, iRenderWidth, iRenderHeight) || Type == Up)
		{
			for (auto element : vElements)
				element->OnMouseClick(Type, iRenderX, iRenderY - iScroll, iRenderWidth, iRenderHeight + iScroll, iSourceX, iSourceY + iScroll);

			if(pVerticalScroll)
				pVerticalScroll->OnMouseClick(Type, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
			return true;
		}
	}
	return false;
}

bool UIWindowOld::OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();

		int iScroll = pVerticalScroll ? pVerticalScroll->getValue() : 0;

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

		if (isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight))
		{
			for (auto element : vElements)
				element->OnMouseMove(iRenderX, iRenderY - iScroll, iRenderWidth, iRenderHeight + iScroll, iSourceX, iSourceY + iScroll);

			if(pVerticalScroll)
				pVerticalScroll->OnMouseMove(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
			return true;
		}
	}
	return false;
}

bool UIWindowOld::OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return false;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();

		int iScroll = pVerticalScroll ? pVerticalScroll->getValue() : 0;

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

		if (isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight))
		{
			for (auto element : vElements)
				element->OnMouseScroll(zDelta, iRenderX, iRenderY - iScroll, iRenderWidth, iRenderHeight + iScroll, iSourceX, iSourceY + iScroll);

			if (pVerticalScroll)
				pVerticalScroll->OnMouseScroll(zDelta, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
			return true;
		}
	}
	return false;
}

bool UIWindowOld::OnKeyDown(char Code)
{
	for (auto pElement : vElements)
		pElement->OnKeyDown(Code);
	return true;
}

void UIWindowOld::AddElement(ElementOld* pElement)
{
	if (pElement->getY() + pElement->getHeight() > iMaxY && pElement->getID() != 500)
	{
		iMaxY = pElement->getY() + pElement->getHeight();

		if (iMaxY > getHeight())
		{
			if (!pVerticalScroll)
			{
				pVerticalScroll = new UIVerticalScrollOld(500, getWidth() - 12, getHeight() / 2 - 190, -1, 380, 0, iMaxY - getHeight() + 10);
			}
			else
			{
				pVerticalScroll->setMax(iMaxY - getHeight() + 10);
			}
		}
	}

	vElements.push_back(pElement);
}
