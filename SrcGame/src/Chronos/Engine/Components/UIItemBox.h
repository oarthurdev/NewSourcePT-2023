#pragma once

namespace UI
{
	typedef std::shared_ptr<class ItemBox> ItemBox_ptr;
	class ItemBox : public Element
	{
	public:
		/**
		* Item Box Slot
		* @param iX X position of slot
		* @param iY Y position of slot
		* @param iSlotCountX number of slots by column = 4 Default
		* @param iSlotCountY number of slots by row = 6 Default
		*/

		enum ERule
		{
			RULE_None,
			RULE_Allow,
			RULE_Disallow,
		};

		enum ETypeRule
		{
			TYPERULE_None,
			TYPERULE_ItemID,
			TYPERULE_ItemBase,
			TYPERULE_ItemType,
			TYPERULE_QuestItem,
			TYPERULE_AgeItem,
			TYPERULE_ItemPerfect,
			TYPERULE_EquippedItem,
		};

		struct SRuleData
		{
			ERule eRule;
			ETypeRule eType;
			int iParam;

			BOOL bMessage;
			char szMessage[128];
		};


		ItemBox(int iX, int iY, int _iSlotCountX = 4, int _iSlotCountY = 6);
		virtual ~ItemBox();


		void SetMaxItems(int iMax) { iMaxItems = iMax; }
		void SetFreePlace(BOOL b) { bFreeSlotPlace = b; }

		int GetItemsMax() { return iMaxItems; };

		void SetEventOnPutItem(int iID) { iPutItemEventID = iID; }
		void SetEventOnGetItem(int iID) { iGetItemEventID = iID; }
		void SetEventOnDeniedItem(int iID) { iDeniedItemEventID = iID; }
		void SetEventOnAllowedItem(int iID) { iAllowedItemEventID = iID; }

		void AddRule(ERule eRule, ETypeRule eType, int iParam);

		void HandleEvent(ItemData* pcItemData, int iEventID);

		void ClearItems();

		void Clear();

		ItemData* GetEventItemData() { return pcLastItemDataPtr; }

		//Render
		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		//Event Handlers
		BOOL OnMouseClick(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
		void OnMouseMove(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		void Enable() { bDisable = FALSE; };
		void Disable() { bDisable = TRUE; };
		void EnableMouse() { bDisableClick = FALSE; };
		void DisableMouse() { bDisableClick = TRUE; };

		BOOL AddItem(ItemData* pcItemData, int iX, int iY, int iMouseX = 0, int iMouseY = 0);
		BOOL GetItem(Point2D* psPosition, int iX, int iY, BOOL bAutomatic = FALSE);

		std::vector<ItemData*>& GetItems() { return vItems; }
	private:

		BOOL IsAllowedItem(ItemData* pcItemData);

		BOOL bDisable = FALSE;

		BOOL bFreeSlotPlace = FALSE;

		Point2D sPosition;
		int iSlotCountX, iSlotCountY;
		int iMaxItems;

		BOOL bDisableClick = FALSE;

		std::vector<ItemData*> vItems;
		std::vector<SRuleData*> vRules;


		int iPutItemEventID = -1;
		int iGetItemEventID = -1;
		int iDeniedItemEventID = -1;
		int iAllowedItemEventID = -1;

		ItemData* pcLastItemDataPtr = NULL;

	};
}