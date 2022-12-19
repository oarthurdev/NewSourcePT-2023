#pragma once

#include "UILinkerOld.h"

#define BattleEventWindow (CBattleEventsWindow::GetInstance())

enum OBJID2
{
	OBJID2_None,
	OBJID2_ONBox,
	OBJID2_OFFBox,
	OBJID2_Main,
	OBJID2_Close,
	OBJID2_Accept,
};

class CBattleEventsWindow
{
public:	
	CBattleEventsWindow();
	~CBattleEventsWindow();

	static CBattleEventsWindow* GetInstance();

	void Init();
	void Draw();
	bool OnMouseClick(bool flag);
	void OnMouseMove();
	void OnMouseScroll(int zDelta);
	void Resize();
	void Open();
	void Close();
	void Accept();

	bool isOpen() { return ((m_pWindow && m_pWindow->isVisible()) ? true : false); }

private:
	UIWindowOld* m_pWindow;

	void BuildMainWindow();
};

