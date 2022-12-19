#include "sinbaram/sinLinkHeader.h"
#include "cRestaureWindow.h"
#include "CoinShop.h"
cRESTAURE cRestaure;

extern bool isMousePos(int x, int y, int w, int h);

void cRESTAURE::Load()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\GUI\\Restaure\\background.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[CLOSE] = CreateTextureMaterial("game\\GUI\\Restaure\\close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[LEFT] = CreateTextureMaterial("game\\GUI\\Restaure\\left.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RIGHT] = CreateTextureMaterial("game\\GUI\\Restaure\\right.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RESTAURE] = CreateTextureMaterial("game\\GUI\\Restaure\\restaure.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cRESTAURE::Draw()
{
	if (!OpenFlag)
		return;

	BaseX = (WinSizeX - 296) / 2;
	BaseY = (WinSizeY - 310) / 2;

	dsDrawTexImage(Mat[BACKGROUND], BaseX, BaseY, 297, 311, 255);

	if (isMousePos(BaseX + 266, BaseY + 16, 22, 22))
		dsDrawTexImage(Mat[CLOSE], BaseX + 266, BaseY + 16, 23, 23, 255);
	else
		dsDrawTexImage(Mat[CLOSE], BaseX + 266, BaseY + 16, 23, 23, 200);

	if (isMousePos(BaseX + 98, BaseY + 254, 105, 25))
		dsDrawTexImage(Mat[RESTAURE], BaseX + 98, BaseY + 254, 106, 26, 255);
	else
		dsDrawTexImage(Mat[RESTAURE], BaseX + 98, BaseY + 254, 106, 26, 200);

	if (isMousePos(BaseX + 64, BaseY + 104, 29, 29))
		dsDrawTexImage(Mat[LEFT], BaseX + 64, BaseY + 104, 30, 30, 255);
	else
		dsDrawTexImage(Mat[LEFT], BaseX + 64, BaseY + 104, 30, 30, 200);

	if (isMousePos(BaseX + 208, BaseY + 104, 29, 29))
		dsDrawTexImage(Mat[RIGHT], BaseX + 208, BaseY + 104, 30, 30, 255);
	else
		dsDrawTexImage(Mat[RIGHT], BaseX + 208, BaseY + 104, 30, 30, 200);

	if (itemCount && itemIndex < itemCount)
	{
		RESTAURE_ITEM* Item = vItems[itemIndex];
		if (Item->psItem.lpItem)
		{
			Item->psItem.x = Item->psItem.SetX = 116 + BaseX + (69 / 2 - Item->psItem.w / 2);
			Item->psItem.y = Item->psItem.SetY = 74 + BaseY + (90 / 2 - Item->psItem.h / 2);

			DrawSprite(Item->psItem.x, Item->psItem.y, Item->psItem.lpItem, 0, 0, Item->psItem.w, Item->psItem.h);

			if (isMousePos(Item->psItem.x, Item->psItem.y, Item->psItem.w, Item->psItem.h)) {
				cItem.ShowItemInfo(&Item->psItem, 1);
				sinShowItemInfoFlag = 1;
			}
		}
	}

	char buff[255] = {};
	NumLineComa(cCoinShop.Coin, buff);
	dsTextLineOut(0,BaseX + 55, BaseY + 195, buff, lstrlen(buff));

	wsprintf(buff, "+08 ~ +13: %dc", 500);
	dsTextLineOut(0,BaseX + 167, BaseY + 195, buff, lstrlen(buff));
	wsprintf(buff, "+14 ~ +17: %dc", 700);
	dsTextLineOut(0,BaseX + 167, BaseY + 210, buff, lstrlen(buff));
	wsprintf(buff, "+18 ~ +20: %dkc", 1000);
	dsTextLineOut(0,BaseX + 167, BaseY + 225, buff, lstrlen(buff));
}

bool cRESTAURE::LButtonDown()
{
	if (!OpenFlag)
		return FALSE;

	if (isMousePos(BaseX + 266, BaseY + 16, 22, 22))
	{
		Close();
	}

	if (isMousePos(BaseX + 98, BaseY + 254, 105, 25))
	{
		Restaure();
	}

	if (isMousePos(BaseX + 64, BaseY + 104, 29, 29))
	{
		SwitchItem(-1);
	}

	if (isMousePos(BaseX + 208, BaseY + 104, 29, 29))
	{
		SwitchItem(1);
	}

	return false;
}

void cRESTAURE::Open()
{
	itemCount = 0;
	itemIndex = 0;

	smTRANS_COMMAND smTransCommand;
	smTransCommand.code = OPCODE_GET_RESTAURE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);

	smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	OpenFlag = true;
}

void cRESTAURE::Close()
{
	OpenFlag = false;

	for (auto item : vItems)
		delete item;

	vItems.clear();
}

void cRESTAURE::Restaure()
{
	if (!itemCount || itemIndex >= itemCount)
	{
		cMessageBox.ShowMessageEvent("Você não tem itens para restaurar.");
		return;
	}

	RESTAURE_ITEM* Item = vItems[itemIndex];

	if (cCoinShop.Coin < Item->CoinPrice)
	{
		cMessageBox.ShowMessageEvent("Você não tem crédito suficiente.");
		return;
	}


	if (!cInvenTory.CheckSetEmptyArea(&Item->psItem))
	{
		cMessageBox.ShowMessageEvent("Você não tem espaço suficiente no inventário.");
		return;
	}

	if (!cInvenTory.CheckSetOk(&Item->psItem, 1))
	{
		cMessageBox.ShowMessageEvent("Excede o peso limite.");
		return;
	}

	smTRANS_COMMAND_EX smTransCommand = {};
	smTransCommand.code = OpCode::OPCODE_RESTAURE_ITEM;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = Item->psItem.sItemInfo.ItemHeader.Head;
	smTransCommand.LParam = Item->psItem.sItemInfo.ItemHeader.dwChkSum;

	resetList = true;

	smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
}

void cRESTAURE::SwitchItem(int Side)
{
	if (Side < 0)
	{
		if (itemIndex > 0)
			itemIndex--;
	}
	else
	{
		if (itemIndex < itemCount - 1)
			itemIndex++;
	}
}

void cRESTAURE::RecvRestaureList(RESTAURE_LIST * lpRestaureList)
{
	if (resetList)
	{
		resetList = false;

		for (auto item : vItems)
			delete item;

		vItems.clear();

		itemCount = 0;
		itemIndex = 0;
	}

	itemCount += lpRestaureList->Count;
	itemIndex = 0;

	for (int i = 0; i < itemCount; i++)
	{
		RESTAURE_ITEM* item = new RESTAURE_ITEM;

		if (item)
		{
			LoadItemImage(&lpRestaureList->ItemList[i].sItem, &item->psItem);
			if (item->psItem.lpItem)
			{
				item->CoinPrice = lpRestaureList->ItemList[i].CoinPrice;

				vItems.push_back(item);
			}
			else
				delete item;
		}
	}
}
