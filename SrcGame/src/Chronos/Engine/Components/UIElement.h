#pragma once

#include <vector>
#include <memory>
#include "Mouse/Mouse.h"
#include "Utils/Geometry.h"

typedef int EID;
typedef int EImage;
typedef int EButton;
typedef int EButton;

typedef std::shared_ptr<class Element> Element_ptr;

enum EType
{
	TYPE_None,

	TYPE_Button,
	TYPE_Group,
	TYPE_Window,
	TYPE_Scroller,
	TYPE_Checkbox,
	TYPE_Text,
	TYPE_InputField,
	TYPE_ImageBox,
	TYPE_Tooltip,
};

class Element
{
public:
	//Constructor
	Element();
	Element(class Rectangle2D rRectangle);
	virtual ~Element();

	virtual void Clear() {};

	//Getters and Setters
	virtual int GetID() { return iID; };
	virtual void SetID(int iIDObject) { iID = iIDObject; };
	virtual int GetX() { return rRect.iX; };
	virtual int GetY() { return rRect.iY; };

	virtual void SetWidth(int i) { rRect.iWidth = i; };
	virtual int GetWidth() { return rRect.iWidth; };

	virtual void SetHeight(int i) { rRect.iHeight = i; };
	virtual int GetHeight() { return rRect.iHeight; };

	virtual void SetYAxis(int iY) {};
	virtual void SetPosition(int iX, int iY) { rRect.iX = iX; rRect.iY = iY; };

	virtual void SetType(EType e) { eType = e; }
	virtual int GetType() { return eType; };

	virtual void SetBox(Rectangle2D sBox) { rRect = sBox; };
	virtual Rectangle2D GetRect() { return rRect; };

	virtual void Update(float fTime) {};

	//Render
	virtual void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY, int iSourceWidth, int iSourceHeight) {};
	virtual void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

	//Event Handlers
	virtual BOOL OnMouseClick(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) { return FALSE; };
	virtual void OnMouseMove(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) {};
	virtual BOOL OnMouseScroll(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY) { return FALSE; };
	virtual BOOL OnKeyChar(class CKeyboard* pcKeyboard) { return FALSE; };
	virtual BOOL OnKeyPress(class CKeyboard* pcKeyboard) { return FALSE; };

	void Show() { bShow = TRUE; };
	void Hide() { bShow = FALSE; };

	BOOL IsOpen() { return bShow; };
	virtual BOOL IsParentChild() { return TRUE; };

	std::vector<Element_ptr> vElementsChild;
protected:
	int iID = -1;
	BOOL bShow = TRUE;
	Rectangle2D rRect;

	EType eType = TYPE_None;
};

