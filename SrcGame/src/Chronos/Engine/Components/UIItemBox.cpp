
#include "UIItemBox.h"

namespace UI
{

	ItemBox::ItemBox(int iX, int iY, int _iSlotCountX, int _iSlotCountY) : Element(), sPosition(Point2D{ iX,iY }), iSlotCountX(_iSlotCountX), iSlotCountY(_iSlotCountY)
	{
		SetMaxItems(1);
	}

	ItemBox::~ItemBox()
	{
		Clear();
	}

	void ItemBox::AddRule(ERule eRule, ETypeRule eType, int iParam)
	{
		SRuleData* ps = new SRuleData;
		ps->eRule = eRule;
		ps->eType = eType;
		ps->iParam = iParam;

		vRules.push_back(ps);
	}

	void ItemBox::HandleEvent(ItemData* pcItemData, int iEventID)
	{
		pcLastItemDataPtr = NULL;

		if (iEventID != -1)
		{
			pcLastItemDataPtr = pcItemData;
			UI::Event::Invoke(iEventID);
		}
	}

	void ItemBox::ClearItems()
	{
		for (std::vector<ItemData*>::iterator it = vItems.begin(); it != vItems.end(); it++)
		{
			ItemData* pc = (*it);

			delete pc;
		}

		vItems.clear();
	}

	void ItemBox::Clear()
	{
		ClearItems();

		for (std::vector<SRuleData*>::iterator it = vRules.begin(); it != vRules.end(); it++)
		{
			SRuleData* ps = (*it);

			delete ps;
		}


		vRules.clear();

		SetMaxItems(1);

		iSlotCountX = 4;
		iSlotCountY = 6;
	}

	void ItemBox::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{

		if (IsOpen())
		{

			if ((iWidth - sPosition.iX) <= 0)
				return;

			if ((iHeight - sPosition.iY) <= 0)
				return;


			int iRenderX = sPosition.iX + iX;
			int iRenderY = sPosition.iY + iY;
			int iRenderWidth = low((iSlotCountX * 22), iWidth - sPosition.iX);
			int iRenderHeight = low((iSlotCountY * 22), iHeight - sPosition.iY);

			for (std::vector<ItemData*>::iterator it = vItems.begin(); it != vItems.end(); it++)
			{
				ItemData* pc = (*it);

				if (pc && pc->bValid)
				{
					ITEMHANDLER->DrawSprite((pc->sPosition.iX + iRenderX), (pc->sPosition.iY + iRenderY), (int)pc->pcInventoryTexture, 0, 0, pc->iWidth, pc->iHeight);

					Point2D* psPosition = MOUSEHANDLER->GetPosition();

					if (psPosition->iX >= (pc->sPosition.iX + iRenderX) && psPosition->iX <= (pc->sPosition.iX + pc->iWidth + iRenderX))
					{
						if (psPosition->iY >= (pc->sPosition.iY + iRenderY) && psPosition->iY <= (pc->sPosition.iY + pc->iHeight + iRenderY))
						{
							pc->sPosition.iX += iRenderX;
							pc->sPosition.iY += iRenderY;
							ITEMHANDLER->ShowItemInfo(pc, FALSE);
							pc->sPosition.iX -= iRenderX;
							pc->sPosition.iY -= iRenderY;
						}
					}
				}
			}

			Element::Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		}
	}

	BOOL ItemBox::OnMouseClick(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (bDisableClick)
			return FALSE;

		if (EMouseEvent::ClickDownL == pcMouse->GetEvent())
		{

			Point2D* psPosition = pcMouse->GetPosition();

			int iRenderX = sPosition.iX + iX + iSourceX;
			int iRenderY = sPosition.iY + iY + iSourceY;
			int iRenderWidth = low((iSlotCountX * 22), iWidth);
			int iRenderHeight = low((iSlotCountY * 22), iHeight);


			// Inside X?
			if ((psPosition->iX >= iRenderX) && (psPosition->iX <= (iRenderX + iRenderWidth - iSourceX)))
			{
				// Inside Y?
				if ((psPosition->iY >= iRenderY) && (psPosition->iY <= (iRenderY + iRenderHeight - iSourceY)))
				{
					ItemData* pcItemData = ITEMHANDLER->GetMouseItem();

					Point2D sPositionMouse = Point2D(psPosition->iX, psPosition->iY);

					if (bFreeSlotPlace == FALSE)
						sPositionMouse = Point2D(0, 0);

					if (pcItemData->bValid)
					{
						if (AddItem(pcItemData, iRenderX, iRenderY, sPositionMouse.iX, sPositionMouse.iY))
						{
							//Show Cursor
							WRITEDWORD(0x00999308, TRUE);
							return TRUE;
						}
					}
					else
					{
						if (GetItem(psPosition, iRenderX, iRenderY, FALSE))
							return TRUE;
					}
				}
			}
		}
		else if (EMouseEvent::ClickDownR == pcMouse->GetEvent())
		{
			int iRenderX = sPosition.iX + iX + iSourceX;
			int iRenderY = sPosition.iY + iY + iSourceY;

			ItemData* pcItemData = ITEMHANDLER->GetMouseItemHover();

			if (pcItemData && pcItemData->bValid)
			{
				AddItem(pcItemData, iRenderX, iRenderY);
				return TRUE;
			}
			else
			{
				if (GetItem(pcMouse->GetPosition(), iRenderX, iRenderY, TRUE))
					return TRUE;
			}
		}

		return FALSE;
	}

	void ItemBox::OnMouseMove(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
	}

	BOOL ItemBox::IsAllowedItem(ItemData* pcItemData)
	{

		BOOL bDisallowed = FALSE;
		BOOL bAllowed = FALSE;

		auto IsRule = [&bAllowed](ItemData* pcItemData, ERule eRule, std::vector<SRuleData*> vRules)->BOOL
		{

			BOOL bRet = FALSE;

			BOOL bFoundAllow = FALSE;
			BOOL bFoundDisallow = FALSE;

			for (std::vector<SRuleData*>::iterator it = vRules.begin(); it != vRules.end(); it++)
			{
				SRuleData* ps = (*it);

				if (ps)
				{
					if (ps->eRule == ERule::RULE_Allow)
						bFoundAllow = TRUE;
					if (ps->eRule == ERule::RULE_Disallow)
						bFoundDisallow = TRUE;

					if (ps->eRule == eRule)
					{

						if (ps->eType == TYPERULE_EquippedItem)
						{
							BOOL bEquipped = FALSE;

							for (int i = 0; i < 15; i++)
							{
								if (INVENTORYITEMSLOT[i].iItemIndex)
								{
									ItemData* psItemData = &INVENTORYITEMS[INVENTORYITEMSLOT[i].iItemIndex - 1];

									if (psItemData == pcItemData)
									{
										bEquipped = TRUE;
										break;
									}
								}
							}

							if (bEquipped == ps->iParam)
								bRet = TRUE;
						}

						if (ps->eType == TYPERULE_ItemID)
							if ((EItemID)ps->iParam == pcItemData->sItem.sItemID.ToItemID())
								bRet = TRUE;

						if (ps->eType == TYPERULE_ItemType)
							if ((EItemType)ps->iParam == pcItemData->sItem.sItemID.ToItemType())
								bRet = TRUE;

						if (ps->eType == TYPERULE_ItemBase)
							if ((EItemBase)ps->iParam == pcItemData->sItem.sItemID.ToItemBase())
								bRet = TRUE;

						if (ps->eType == TYPERULE_AgeItem)
							if (pcItemData->sItem.eCraftType == ITEMCRAFTTYPE_Aging)
								bRet = TRUE;

						if (ps->eType == TYPERULE_QuestItem)
							if (pcItemData->sItem.eCraftType == ITEMCRAFTTYPE_Quest || pcItemData->sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon ||
								ITEMINFOBOX->IsBeginnerSet(pcItemData))
								bRet = TRUE;

						if (ps->eType == TYPERULE_ItemPerfect)
							if (pcItemData->sItem.bPerfectItem == ps->iParam)
								bRet = TRUE;


						if (bRet)
							return TRUE;
					}
				}
			}

			if (vRules.size() == 0 && eRule == ERule::RULE_Allow)
				return TRUE;

			if (vRules.size() > 0)
			{
				if (eRule == ERule::RULE_Disallow && bFoundAllow == TRUE && bFoundDisallow == FALSE && bAllowed == FALSE)
					return TRUE;
			}

			return FALSE;
		};

		bAllowed = IsRule(pcItemData, RULE_Allow, vRules);
		bDisallowed = IsRule(pcItemData, RULE_Disallow, vRules);

		//Allowed or not in Disallowed Rule? Allow to set...
		if ((bAllowed == TRUE) && (bDisallowed == FALSE))
			return TRUE;

		return FALSE;
	}

	BOOL ItemBox::AddItem(ItemData* pcItemData, int iX, int iY, int iMouseX, int iMouseY)
	{

		if (!IsAllowedItem(pcItemData))
		{
			//Event
			HandleEvent(pcItemData, iDeniedItemEventID);
			return FALSE;
		}

		//Event
		HandleEvent(pcItemData, iAllowedItemEventID);

		Rectangle2D sBox(iX, iY, iSlotCountX * 22, iSlotCountY * 22);

		if (vItems.size() >= (UINT)iMaxItems)
			return FALSE;

		if (iMaxItems > 1)
		{

			int iPlaceX = -1;
			int iPlaceY = -1;

			//Check Collision
			for (int i = 0; i < iSlotCountY; i++)
			{
				BOOL bDone = FALSE;

				for (int j = 0; j < iSlotCountX; j++)
				{
					int iRelativeX = (j * 22);
					int iRelativeY = (i * 22);

					RECT rPlaceRect;
					rPlaceRect.left = iRelativeX;
					rPlaceRect.top = iRelativeY;
					rPlaceRect.right = rPlaceRect.left + pcItemData->iWidth;
					rPlaceRect.bottom = rPlaceRect.top + pcItemData->iHeight;

					int iCollideX = rPlaceRect.right + sBox.iX - 1;
					int iCollideY = rPlaceRect.bottom + sBox.iY - 1;

					if (!sBox.Inside(&Point2D(iCollideX, iCollideY)))
						continue;

					if (iMouseX > 0 && iMouseY > 0)
					{
						int iDifferenceX = ((iMouseX - iX) / 22) * 22;
						int iDifferenceY = ((iMouseY - iY) / 22) * 22;

						Rectangle2D sBoxFree(iX + iDifferenceX - 1, iY + iDifferenceY - 1, (iSlotCountX * 22) - iDifferenceX, (iSlotCountY * 22) - iDifferenceY);
						if (!sBoxFree.Inside(&Point2D(iMouseX, iMouseY)))
							continue;
						if (!sBoxFree.Inside(&Point2D(iX + (iDifferenceX - 22) + pcItemData->iWidth - 1, iY + (iDifferenceY - 22) + pcItemData->iHeight - 1)))
							continue;

						rPlaceRect.left = iDifferenceX;
						rPlaceRect.top = iDifferenceY;
					}

					BOOL bCollides = FALSE;

					for (std::vector<ItemData*>::iterator it = vItems.begin(); it != vItems.end(); it++)
					{
						ItemData* pc = (*it);

						if (pc)
						{
							if (pc->bValid == FALSE)
								continue;

							RECT rItemRect;
							rItemRect.left = pc->sPosition.iX;
							rItemRect.top = pc->sPosition.iY;
							rItemRect.right = rItemRect.left + pc->iWidth - 1;
							rItemRect.bottom = rItemRect.top + pc->iHeight - 1;

							if (rPlaceRect.left < rItemRect.right && rPlaceRect.right > rItemRect.left&&
								rPlaceRect.top < rItemRect.bottom && rPlaceRect.bottom > rItemRect.top)
							{
								bCollides = TRUE;
								break;
							}
						}
					}

					if (bCollides)
						continue;

					iPlaceX = rPlaceRect.left;
					iPlaceY = rPlaceRect.top;

					bDone = TRUE;
					break;
				}

				if (bDone)
					break;
			}

			if (iPlaceY == (-1))
				return FALSE;

			ItemData* psSlot = new ItemData;
			CopyMemory(psSlot, pcItemData, sizeof(ItemData));

			pcItemData->bValid = FALSE;

			psSlot->sPosition.iX = iPlaceX;
			psSlot->sPosition.iY = iPlaceY;

			PLAYMINISOUND(pcItemData->iInvItemSound);

			vItems.push_back(psSlot);

			// Validate Inventory
			ITEMHANDLER->ValidateInventoryItems();
			ITEMHANDLER->ResetInventoryItemChecksum();

			CHARACTERGAME->UpdateWeight();

			//Event
			HandleEvent(psSlot, iPutItemEventID);

			return TRUE;

		}
		else
		{
			ItemData* psSlot = new ItemData;
			CopyMemory(psSlot, pcItemData, sizeof(ItemData));

			psSlot->sPosition.iX = (sBox.iWidth >> 1) - (psSlot->iWidth >> 1);
			psSlot->sPosition.iY = (sBox.iHeight >> 1) - (psSlot->iHeight >> 1);

			PLAYMINISOUND(pcItemData->iInvItemSound);

			vItems.push_back(psSlot);

			ZeroMemory(pcItemData, sizeof(ItemData));

			// Validate Inventory
			ITEMHANDLER->ValidateInventoryItems();
			ITEMHANDLER->ResetInventoryItemChecksum();

			CHARACTERGAME->UpdateWeight();

			//Event
			HandleEvent(psSlot, iPutItemEventID);

			return TRUE;
		}

		return FALSE;
	}

	BOOL ItemBox::GetItem(Point2D* psPosition, int iX, int iY, BOOL bAutomatic)
	{
		BOOL bCollides = FALSE;

		for (std::vector<ItemData*>::iterator it = vItems.begin(); it != vItems.end(); it++)
		{
			ItemData* pc = (*it);

			if (pc)
			{
				if (pc->bValid == FALSE)
					continue;

				if (psPosition->iX >= (pc->sPosition.iX + iX) && psPosition->iX <= (pc->sPosition.iX + iX + pc->iWidth))
				{
					if (psPosition->iY >= (pc->sPosition.iY + iY) && psPosition->iY <= (pc->sPosition.iY + iY + pc->iHeight))
					{
						// Check iWeight
						if (!CHARACTERGAME->CheckInventoryWeight(pc))
						{
							TITLEBOX("Weight limit exceeded");
							return TRUE;
						}

						// Check Space
						if (!CHARACTERGAME->CheckInventorySpace(pc))
						{
							TITLEBOX("Not enough space in inventory");
							return TRUE;
						}


						// Put Item Back to Inventory
						if (bAutomatic == TRUE)
						{
							ITEMHANDLER->BackItemToInventory(pc);
						}
						else
						{
							CopyMemory(ITEMHANDLER->GetMouseItem(), pc, sizeof(ItemData));
							//Hide Cursor
							WRITEDWORD(0x00999308, FALSE);
						}
						ITEMHANDLER->ResetInventoryItemChecksum();

						// Invalidate Item
						pc->bValid = FALSE;

						// iSound
						PLAYMINISOUND(pc->iInvItemSound);

						//Event
						HandleEvent(pc, iGetItemEventID);
						DELET(pc);
						vItems.erase(it);
						break;
					}
				}
			}
		}

		return TRUE;
	}

}