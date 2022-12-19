#pragma once

#include "sinbaram/sinLinkHeader.h"

enum TYPES
{
	WINDOW,
	OBJECT,
};

enum CLICKS
{
	Click,
	Down,
	Up
};

enum ALIGN
{
	EALIGN_TOP,
	EALIGN_BOT,
};

class ElementOld
{
public:
	ElementOld() { iType = -1; }

	int low(int a, int b)
	{
		if (a < b)
			return a;

		return b;
	}

	void						setID(int id) { iID = id; }
	int							getID() { return iID; }

	void						setType(int type) { iType = type; }
	int							getType() { return iType; }

	virtual void				setSelected(bool selected) { bSelected = selected; }
	virtual bool				getSelected() { return bSelected; }

	void						setHover(bool hover) { bHover = hover; }
	bool						getHover() { return bHover; }

	void						show() { bVisible = true; }
	void						hide() { bVisible = false; }
	bool						isVisible() { return bVisible; }

	void						setWidth(int Width) { iWidth = Width; }
	int							getWidth() { return iWidth; }
	void						setHeight(int Height) { iHeight = Height; }
	int							getHeight() { return iHeight; }

	virtual void				setX(int x) { iX = x; }
	virtual int					getX() { return iX; }
	virtual void				setY(int y) { iY = y; }
	virtual int					getY() { return iY; }

	void						setFree(bool free) { bFree = free; }
	bool						getFree() { return bFree; }

	void						setFixed(bool fixed) { bFixed = fixed; }
	bool						getFixed() { return bFixed; }
	void						setRectMove(RECT& pRect) { memcpy(&RectMove, &pRect, sizeof(RECT)); bSetRectMove = true; };
	bool						getRectMove() { return bSetRectMove ? isMousePos(iX + RectMove.left, iY + RectMove.top, RectMove.right, RectMove.bottom) : true; };
	void						setAlign(ALIGN align) { eAlign = align; }
	ALIGN						getAlign() { return eAlign; }

	virtual void				Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) {}
	virtual bool				OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) { return false; };
	virtual bool				OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) { return false; };
	virtual bool				OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) { return false; };
	virtual bool				OnKeyDown(char Code) { return false; };
	virtual bool				OnKeyChar(char Code) { return false; };

private:
	int							iType = 0;
	int							iID = -1;
	bool						bVisible = true;
	bool						bFree = true;

protected:
	bool						bSelected = false;
	bool						bHover = true;
	bool						bFixed = true;
	bool						bSetRectMove = false;
	ALIGN						eAlign = EALIGN_TOP;
	RECT						RectMove = { 0,0,0,0 };
	int							iX = 0, iY = 0, iWidth = 0, iHeight = 0;
};