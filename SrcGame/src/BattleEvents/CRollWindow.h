#pragma once

#include "UILinkerOld.h"
#include "roll.h"

class CRollWindow
{
public:
	CRollWindow(DWORD iRollID, int x, int y, sITEMINFO* lpItemInfo);
	~CRollWindow();

	bool isInside();

	UIWindowOld* GetWindow() { return pWindow1; }

protected:
	void OnClickRollButton();
	void OnClickSkipButton();
	void OnHoverItemImage();

private:
	UIWindowOld* pWindow1;
	sITEM Item;
};