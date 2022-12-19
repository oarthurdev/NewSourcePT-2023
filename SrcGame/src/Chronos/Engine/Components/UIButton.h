#pragma once

#include "UIImage.h"
#include "UIGroup.h"
#include "UIDropdownMenu.h"
#include <memory>

namespace UI
{
	typedef std::shared_ptr<class Button> Button_ptr;
	class Button : public Element
	{
	public:
		//Constructor
		Button(Rectangle2D rRectangle);
		virtual ~Button();

		void Clear();

		//Getters and Setters
		void SetParentChild(BOOL bParent) { bParentChild = bParent; };
		BOOL IsParentChild() { return bParentChild; };
		BOOL IsHover() { return bHover; };
		BOOL IsSelected() { return bSelect; };
		void SetSelect(BOOL bSel) { bSelectType = bSel; };
		void SetSelected(BOOL b) { bSelect = b; if (pGroupMain) pGroupMain->SetIndexObject(GetID()); }
		void SetEvent(int iEvent) { iEventID = iEvent; };
		void SetImage(class Image* pImage) { this->pImage = pImage; };
		void SetActiveImage(std::pair<class Image*, class Image*> pPair);
		void SetDisabledImage(class Image* pImage) { pImageDisable = pImage; };
		void SetGroup(std::shared_ptr<class Group> pGroup) { pGroupMain = pGroup; };
		void SetDropdownMenu(DropdownMenu_ptr p) { pDropdownMenu = p; }
		void SetCanHold(BOOL b) { bCanHold = b; }
		void SetMouseEvent(EMouseEvent e) { eMouseEvent = e; }

		//Render
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		//Event Handlers
		BOOL OnMouseClick(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		void Enable() { bDisable = FALSE; };
		void Disable() { bDisable = TRUE; };
	private:
		class Image* pImage = NULL;
		class Image* pImageActive = NULL;
		class Image* pImageDisable = NULL;
		int iEventID = -1;
		BOOL bHover = FALSE;
		BOOL bDisable = FALSE;
		BOOL bSelect = FALSE;
		BOOL bSelectType = FALSE;
		BOOL bParentChild = TRUE;
		BOOL bCanHold = FALSE;
		BOOL bHolding = FALSE;
		enum EMouseEvent eMouseEvent = EMouseEvent::ClickDownL;
		std::shared_ptr<class Group> pGroupMain = NULL;

		DropdownMenu_ptr pDropdownMenu = NULL;
	};
}