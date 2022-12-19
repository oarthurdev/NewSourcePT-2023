#pragma once

#include <Windows.h>
#include <vector>
#include "Utils/Geometry.h"
#include "structs/CursorData.h"

enum EMouseIcon : int
{
	EMOUSEICON_None,
	EMOUSEICON_Default,
	EMOUSEICON_Sell,
	EMOUSEICON_Buy,
	EMOUSEICON_Repair,
	EMOUSEICON_RepairAll,
	EMOUSEICON_Attack,
	EMOUSEICON_GetItem1,
	EMOUSEICON_GetItem2,
	EMOUSEICON_Talk
};

enum EMouseEvent
{
	None,
	ClickDownL,
	ClickUpL,
	ClickDownR,
	ClickUpR,
	DoubleClickL,
	DoubleClickR,
	ScrollUp,
	ScrollDown
};

class CMouse
{
private:
	Point2D cPosition;
	BOOL bDisable = FALSE;
	BOOL bNoMove = FALSE;
	BOOL bEndNoMove = FALSE;
	EMouseEvent eEventMouse = (EMouseEvent)-1;
	short sDistance = 0;

	std::vector<CursorData*> vCursor;
	int iLastCursorID = 0;
	int iBlockedRefCount = 0;
	CMouse();

public:
	static CMouse* getInstance()
	{
		static CMouse inst;
		return &inst;
	}

	
	virtual ~CMouse();
	EMouseEvent GetEvent(DWORD dwKey);
	EMouseEvent GetEvent() { return eEventMouse; };
	Point2D* GetPosition() { return &cPosition; };
	short GetDistance() { return sDistance; }
	BOOL IsDisabled() { return bDisable; };
	BOOL OnMouseClickHandler(DWORD dwKey);
	void OnMouseMoveHandler(int iX, int iY);
	BOOL OnMouseScrollHandler(short sDistance);

	void IsNoMove(BOOL b);
	BOOL IsNoMove() { return bNoMove; }
	BOOL IsEndNoMove() { return bEndNoMove; }
	void IsEndNoMove(BOOL b) { bEndNoMove = b; }

	void BlockMouse();
	void UnblockMouse();

	void SetCursorGame(int iID);

};

#define MOUSEHANDLER (CMouse::getInstance())
