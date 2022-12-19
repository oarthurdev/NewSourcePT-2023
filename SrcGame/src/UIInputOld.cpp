#include "UILinkerOld.h"

UIInputOld::UIInputOld(int iID, char* path, int x, int y, int w, char* active_path)
{
	setID(iID);
	setX(x);
	setY(y);

	Background = new UIImageOld(0, path, 0, 0, w);
	if (Background)
	{
		if (active_path)
			Background_ = new UIImageOld(0, active_path, 0, 0, w);

		pWindow = new UIWindowOld(0, 30, 0, Background->getWidth() - 30, Background->getHeight());

		InputText = new UITextOld(0, "", 0, 0);
		//InputText->setOrientation(EORIENT_Right);
		pWindow->AddElement(InputText);

		Cursor = new UITextOld(0, "|", InputText->getWidth(), 0);
		pWindow->AddElement(Cursor);

		setWidth(Background->getWidth());
		setHeight(Background->getHeight());
	}
}

void UIInputOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
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
		int iRenderWidth = low(cWidth, iWidth);
		int iRenderHeight = low(cHeight, iHeight);
		int iRenderX = cX + iX + iStartX;
		int iRenderY = cY + iY + iStartY;

		if (cX + iRenderWidth > iWidth)
			iRenderWidth -= (cX + iRenderWidth) - iWidth;

		if (cY + iRenderHeight > iHeight)
			iRenderHeight -= (cY + iRenderHeight) - iHeight;

		if (Background_ && isActive())
			Background_->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iStartX, iStartY);
		else if (Background)
			Background->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iStartX, iStartY);

		if (isActive() && Cursor && getCursor())
		{
			if (GetCurrentTime() - frametime > 200)
			{
				if (Cursor->isVisible())
					Cursor->hide();
				else
					Cursor->show();

				frametime = GetCurrentTime();
			}
		}
		else
		{
			frametime = 0;
			if (Cursor)
				Cursor->hide();
		}

		if (pWindow)
			pWindow->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, 0, 0);
	}
}

bool UIInputOld::OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{
		if (iWidth <= 0 || iHeight <= 0)
			return true;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();

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

		if (eActivate == EACTIVATE_Click || eActivate == EACTIVATE_Both)
		{
			if (isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight))
			{
				setActive(true);
				frametime = 0;
				return true;
			}
			else
			{
				setActive(false);
				frametime = 0;
			}
		}
	}
	return false;
}

bool UIInputOld::OnKeyDown(char Code)
{
	if (isVisible())
	{
		if (isActive() && Code != VK_TAB)
		{
			char buff[255];
			GetWindowText(hFocusWnd, buff, 255);
			TrueText.assign(buff);

			if (bFilter)
			{
				string str(buff);
				fill(str.begin(), str.end(), '*');
				InputText->setText(str);
			}
			else
			{
				InputText->setText(buff);
			}
		}

		auto it = vKeyBinds.find(Code);
		if (it != vKeyBinds.end())
			it->second();
	}
	return isActive();
}

bool UIInputOld::OnKeyChar(char Code)
{
	if (isVisible())
	{
		if (isActive())
		{
			char buff[255];
			GetWindowText(hFocusWnd, buff, 255);
			TrueText.assign(buff);

			if (bFilter)
			{
				string str(buff);
				fill(str.begin(), str.end(), '*');
				InputText->setText(str);
			}
			else
			{
				InputText->setText(buff);
			}
			return true;
		}
	}
	return false;
}

extern HWND hFocusWnd;
extern HWND hTextWnd;

void UIInputOld::setActive(bool active)
{
	if (!getEnabled())
	{
		bActive = false;
		return;
	}

	if (isActive())
		hFocusWnd = 0;

	bActive = active;
	if (isActive())
	{
		hFocusWnd = hTextWnd;
		SetWindowText(hFocusWnd, TrueText.c_str());
		SendMessage(hFocusWnd, EM_SETSEL, TrueText.length(), TrueText.length());
	}
}

void UIInputOld::setText(string text)
{
	if (bFilter)
	{
		string str(text);
		fill(str.begin(), str.end(), '*');
		InputText->setText(str);
	}
	else
	{
		InputText->setText(text);
	}

	TrueText.assign(text);

	if (isActive())
	{
		Cursor->setX(getX() + 2 + InputText->getWidth());
		SetWindowText(hFocusWnd, TrueText.c_str());
		SendMessage(hFocusWnd, EM_SETSEL, TrueText.length(), TrueText.length());
	}
}

void UIInputOld::Bind(char Code, function<void()> func)
{
	vKeyBinds.emplace(Code, func);
}

void UIInputOld::setTextArea(int x, int y, int w, int h)
{
	pWindow->setX(x);
	pWindow->setY(y);
	pWindow->setWidth(w);
	pWindow->setHeight(h);
}
