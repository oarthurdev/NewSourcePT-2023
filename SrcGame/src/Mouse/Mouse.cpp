#include "Mouse.h"
#include "playmain.h"
#include "character.h"

BOOL bMouseCreatedHandler = FALSE;


CMouse::CMouse()
{
	cPosition.iX = 0;
	cPosition.iY = 0;
	bMouseCreatedHandler = TRUE;

	vCursor.push_back(new CursorData(EMOUSEICON_Default, LoadCursorFromFileA("game\\images\\mouse\\default.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_Sell, LoadCursorFromFileA("game\\images\\mouse\\sell.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_Buy, LoadCursorFromFileA("game\\images\\mouse\\buy.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_Repair, LoadCursorFromFileA("game\\images\\mouse\\repair.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_Attack, LoadCursorFromFileA("game\\images\\mouse\\attack.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_GetItem1, LoadCursorFromFileA("game\\images\\mouse\\dropsee.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_GetItem2, LoadCursorFromFileA("game\\images\\mouse\\droppick.cur")));
	vCursor.push_back(new CursorData(EMOUSEICON_Talk, LoadCursorFromFileA("game\\images\\mouse\\talk.cur")));
}


CMouse::~CMouse()
{
}

EMouseEvent CMouse::GetEvent(DWORD dwKey)
{
	switch (dwKey)
	{
	case WM_LBUTTONDOWN:
		return EMouseEvent::ClickDownL;
	case WM_LBUTTONUP:
		return EMouseEvent::ClickUpL;
	case WM_RBUTTONDOWN:
		return EMouseEvent::ClickDownR;
	case WM_RBUTTONUP:
		return EMouseEvent::ClickUpR;
	}
	return (EMouseEvent)-1;
}

void CMouse::OnMouseMoveHandler(int iX, int iY)
{
	cPosition.iX = iX;
	cPosition.iY = iY;
}


BOOL CMouse::OnMouseClickHandler(DWORD dwKey)
{
	if (IsEndNoMove())
	{
		MOUSEHANDLER->IsEndNoMove(FALSE);
		MOUSEHANDLER->IsNoMove(FALSE);
	}

	eEventMouse = GetEvent(dwKey);

	return !IsNoMove();
}

BOOL CMouse::OnMouseScrollHandler(short sDistance)
{
	this->sDistance = sDistance / WHEEL_DELTA;

	if (sDistance < 0)
		eEventMouse = ScrollUp;
	else
		eEventMouse = ScrollDown;

	return TRUE;
}

void CMouse::IsNoMove(BOOL b)
{
	bNoMove = b;

	if (bNoMove == TRUE)
		bEndNoMove = FALSE;

	lpCurPlayer->DontMoveFlag = bNoMove;
}

void CMouse::BlockMouse()
{
	iBlockedRefCount++;

	// BLOQUEIA O MOUSE
	IsNoMove(TRUE);

	// FAZ O PERSONAGEM PARAR DE ANDAR
	if (lpCurPlayer)
		lpCurPlayer->SetAction(0);
}

void CMouse::UnblockMouse()
{
	if (iBlockedRefCount > 0)
	{
		iBlockedRefCount--;
		if (iBlockedRefCount == 0)
			IsEndNoMove(TRUE);
	}
}

void CMouse::SetCursorGame(int iID)
{
	if (iID == EMOUSEICON_RepairAll)
		iID = EMOUSEICON_Repair;

	for (std::vector<CursorData*>::iterator it = vCursor.begin(); it != vCursor.end(); it++)
	{
		CursorData* pc = (*it);

		if (pc->iID == iID)
			SetCursor(pc->hCursor);
	}

	iLastCursorID = iID;
}
