#include "CoinShop_T.h"
#include "DXFont.h"

cCOINSHOP_T cCoinShop_T;

extern bool isMousePos(int x, int y, int w, int h);




cCOINSHOP_T::cCOINSHOP_T()
{
	Clear();
	Coin = 0;
}

cCOINSHOP_T::~cCOINSHOP_T()
{
	Clear();
}

void cCOINSHOP_T::Init()
{
	BaseX = 113;
	BaseY = 50;

	Mat[MC::BACKGROUND] = CreateTextureMaterial("game\\timeshop\\background.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::WEAPON] = CreateTextureMaterial("game\\timeshop\\armas.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ARMOR] = CreateTextureMaterial("game\\timeshop\\defesas.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHIELD] = CreateTextureMaterial("game\\timeshop\\trajes.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SETBLB] = CreateTextureMaterial("game\\timeshop\\acessorio.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RINGS] = CreateTextureMaterial("game\\timeshop\\sheltons.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHELTONS] = CreateTextureMaterial("game\\timeshop\\itenspremiuns.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::PREMIUM] = CreateTextureMaterial("game\\timeshop\\servico.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ITEMBOX] = CreateTextureMaterial("game\\timeshop\\itembox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Mat[MC::WEAPON_] = CreateTextureMaterial("game\\timeshop\\armas_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ARMOR_] = CreateTextureMaterial("game\\timeshop\\defesas_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHIELD_] = CreateTextureMaterial("game\\timeshop\\trajes_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SETBLB_] = CreateTextureMaterial("game\\timeshop\\acessorio_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RINGS_] = CreateTextureMaterial("game\\timeshop\\sheltons_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHELTONS_] = CreateTextureMaterial("game\\timeshop\\itenspremiuns_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::PREMIUM_] = CreateTextureMaterial("game\\timeshop\\servico_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ITEMBOX_] = CreateTextureMaterial("game\\timeshop\\itembox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Mat[MC::BUYBTN] = CreateTextureMaterial("game\\timeshop\\buy.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::LEFTARROW] = CreateTextureMaterial("game\\timeshop\\left.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RIGHTARROW] = CreateTextureMaterial("game\\timeshop\\right.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::CLOSEBTN] = CreateTextureMaterial("game\\timeshop\\close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cCOINSHOP_T::Clear()
{
	for (auto& btn : vButton)
	{
		if (btn)
		{
			delete btn;
			btn = 0;
		}
	}

	vButton.clear();

	for (int i = 0; i < 7; i++)
	{
		for (auto& item : vItemBox[i])
		{
			if (item)
			{
				delete item;
				item = 0;
			}
		}

		vItemBox[i].clear();
		PageCount[i] = 0;
	}
}


void cCOINSHOP_T::Open()
{
	Clear();

	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_GET_SHOPCOIN_T;
	smTransCommand.WParam = 0;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	// Sections
	vButton.push_back(new sSHOPBUTTON(MC::WEAPON, Mat[MC::WEAPON], Mat[MC::WEAPON_], 67, 65, 41, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::ARMOR, Mat[MC::ARMOR], Mat[MC::ARMOR_], 67, 103, 52, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::SHIELD, Mat[MC::SHIELD], Mat[MC::SHIELD_], 67, 143, 40, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::SETBLB, Mat[MC::SETBLB], Mat[MC::SETBLB_], 67, 179, 70, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::RINGS, Mat[MC::RINGS], Mat[MC::RINGS_], 67, 217, 56, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::SHELTONS, Mat[MC::SHELTONS], Mat[MC::SHELTONS_], 67, 256, 90, 12, false));
	vButton.push_back(new sSHOPBUTTON(MC::PREMIUM, Mat[MC::PREMIUM], Mat[MC::PREMIUM_], 67, 294, 55, 12, false));
	SetSection(MC::WEAPON);


	// Close
	vButton.push_back(new sSHOPBUTTON(MC::CLOSEBTN, Mat[MC::CLOSEBTN], 0, 530, 19, 13, 15, false, 128));

	// Buy and pages
	vButton.push_back(new sSHOPBUTTON(MC::BUYBTN, Mat[MC::BUYBTN], 0, 323, 395, 97, 35, false, 200));
	vButton.push_back(new sSHOPBUTTON(MC::LEFTARROW, Mat[MC::LEFTARROW], 0, 280, 395, 34, 35, false, 170));
	vButton.push_back(new sSHOPBUTTON(MC::RIGHTARROW, Mat[MC::RIGHTARROW], 0, 425, 395, 36, 35, false, 170));

	OpenFlag = true;
}

bool cCOINSHOP_T::isOpen()
{
	return OpenFlag;
}

void cCOINSHOP_T::Close()
{
	Clear();

	DispEachMode = FALSE;
	CurrentSection = 0;
	CurrentPage = 0;
	SelectedBox = 0;
	OpenFlag = false;
}

void cCOINSHOP_T::SetButtonSelection(int iID)
{
	for (auto& Button : vButton)
	{
		if (Button)
		{
			if (Button->iID == iID)
				Button->Selected = true;
			else
				Button->Selected = false;
		}
	}
}

void cCOINSHOP_T::SetPage(int iID)
{
	if (iID == MC::LEFTARROW)
	{
		if (CurrentPage > 0)
		{
			CurrentPage--;
			SelectBox(0);
		}
	}
	else if (iID == MC::RIGHTARROW)
	{
		if (CurrentPage < PageCount[CurrentSection - 1])
		{
			CurrentPage++;
			SelectBox(0);
		}
	}
}

void cCOINSHOP_T::SetSection(int iID)
{
	if (iID == CurrentSection || iID > 7)
		return;

	SetButtonSelection(iID);

	CurrentSection = iID;
	SelectBox(0);

	if (!vItemBox[iID - 1].size())
	{
		smTRANS_COMMAND smTransCommand = {};

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_GET_SHOPITEM_T;
		smTransCommand.WParam = CurrentSection;

		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}
}

void cCOINSHOP_T::RecvItemFromServer(smTRANS_SHOPDATA * lpTransShopData)
{
	if (lpTransShopData->Section <= 0 || lpTransShopData->Section > 7 || !lpTransShopData->Count)
		return;

	int Section = lpTransShopData->Section - 1;
	sITEMINFO* lpItemInfo = new sITEMINFO[lpTransShopData->Count];

	for (int cnt = 0; cnt < lpTransShopData->Count; cnt++)
	{
		DecodeCompress((BYTE*)&lpTransShopData->sCompItem[cnt], (BYTE*)&lpItemInfo[cnt]);
		vItemBox[Section].push_back(new sITEMBOX(0, 0, 78, 98, Mat[MC::ITEMBOX], Mat[MC::ITEMBOX_], MC::ITEMBOX, false, &lpItemInfo[cnt], lpTransShopData->sCompItem[cnt].Price));
	}

	int colCount = 0;
	int lineCount = 0;

	for (int i = 0; i < vItemBox[Section].size(); i++)
	{
		sITEMBOX* Item = vItemBox[Section][i];

		Item->x = 200 + (78 + 11) * colCount;
		Item->y = 54 + (98 + 21) * lineCount;

		colCount++;
		if (colCount > 3)
		{
			colCount = 0;
			lineCount++;
			if (lineCount > 2)
			{
				lineCount = 0;
			}
		}
	}

	PageCount[Section] = vItemBox[Section].size() / 12;
	/*if(vItemBox[Section].size() % 12)
		PageCount[Section]++;*/

	CurrentPage = 0;
}

void cCOINSHOP_T::RecvCoinFromServer(smTRANS_COMMAND * lpTransCommand)
{
	Coin = lpTransCommand->WParam;
}

void cCOINSHOP_T::Draw()
{
	if (!OpenFlag)
		return;

	BaseX = (WinSizeX - 601) / 2;
	BaseY = (WinSizeY - 451) / 2;

	dsDrawTexImage(Mat[MC::BACKGROUND], BaseX, BaseY, 601, 451, 255);

	for (auto& Button : vButton)
	{
		if (Button)
		{
			if (Button->Selected || isMousePos(BaseX + Button->x, BaseY + Button->y, Button->w, Button->h))
			{
				dsDrawTexImage(Button->iHoverMat, BaseX + Button->x, BaseY + Button->y, Button->w, Button->h, 255);
			}
			else
			{
				dsDrawTexImage(Button->iMat, BaseX + Button->x, BaseY + Button->y, Button->w, Button->h, Button->Opacity);
			}
		}
	}

	int begin = 12 * CurrentPage;
	int end = 12 * (CurrentPage + 1) > vItemBox[CurrentSection - 1].size() ? vItemBox[CurrentSection - 1].size() : 12 * (CurrentPage + 1);

	for (int i = begin; i < end; i++)
	{
		sITEMBOX* Item = vItemBox[CurrentSection - 1][i];
		if (Item)
		{
			if (Item->Selected || isMousePos(BaseX + Item->x, BaseY + Item->y, Item->w, Item->h))
			{
				dsDrawTexImage(Item->iHoverMat, BaseX + Item->x, BaseY + Item->y, Item->w, Item->h, 255);
			}
			else
			{
				dsDrawTexImage(Item->iMat, BaseX + Item->x, BaseY + Item->y, Item->w, Item->h, 255);
			}

			if (Item->psItem->lpItem)
			{
				Item->psItem->x = Item->psItem->SetX = Item->x + BaseX + (Item->w / 2 - Item->psItem->w / 2);
				Item->psItem->y = Item->psItem->SetY = Item->y + BaseY + (Item->h / 2 - Item->psItem->h / 2);

				DrawSprite(Item->psItem->x, Item->psItem->y, Item->psItem->lpItem, 0, 0, Item->psItem->w, Item->psItem->h);

				if (isMousePos(Item->psItem->x, Item->psItem->y, Item->psItem->w, Item->psItem->h)) {
					cItem.ShowItemInfo(Item->psItem, 1);
					sinShowItemInfoFlag = 1;
				}
			}

			if (Item->PriceText[0])
			{
				SetFontTextColor(RGB(255, 204, 0));
				dsTextLineOut(0, BaseX + Item->x + 15, BaseY + Item->y + Item->h - 20, Item->PriceText, lstrlen(Item->PriceText));
			}
		}
	}

	char CoinBuff[32] = {};
	NumLineComa(Coin, CoinBuff);
	DX::SetTextColor(0, RGB(255, 255, 255));
	dsTextLineOut(0, BaseX + 98, BaseY + 385, CoinBuff, lstrlen(CoinBuff));

	/*ZeroMemory(CoinBuff, sizeof(CoinBuff));
	NumLineComa(lpCurPlayer->smCharInfo.Money, CoinBuff);
	dsTextLineOut(BaseX + 78, BaseY + 407, CoinBuff, lstrlen(CoinBuff));*/ //Gold no Shop
}

void cCOINSHOP_T::SelectBox(sITEMBOX * Box)
{
	if (!Box)
	{
		if (SelectedBox)
			SelectedBox->Selected = false;
		SelectedBox = 0;
		return;
	}

	if (SelectedBox)
		SelectedBox->Selected = false;
	Box->Selected = true;
	SelectedBox = Box;
}

void cCOINSHOP_T::BuySelectedItem()
{
	if (!SelectedBox)
	{
		cMessageBox.ShowMessageEvent("Selecione um item para comprar.");
		return;
	}

	if (Coin < SelectedBox->Price)
	{
		cMessageBox.ShowMessageEvent("Você não tem Tempo suficiente.");
		return;
	}

	if (!cInvenTory.CheckSetEmptyArea(SelectedBox->psItem))
	{
		cMessageBox.ShowMessageEvent("Você não tem espaço suficiente no inventário.");
		return;
	}

	if (!cInvenTory.CheckSetOk(SelectedBox->psItem, 1))
	{
		cMessageBox.ShowMessageEvent("Excede o peso limite.");
		return;
	}

	smTRANS_BUYSHOP TransBuy = {};
	TransBuy.code = OpCode::OPCODE_BUY_SHOPITEM_T;
	TransBuy.size = sizeof(smTRANS_BUYSHOP);
	lstrcpy(TransBuy.szItemCode, SelectedBox->psItem->LastCategory);
	smWsockDataServer->Send((char*)&TransBuy, TransBuy.size, TRUE);

	cMessageBox.ShowMessageEvent("Compra feita com sucesso!");

	AddChatBuff("> Compra feita com sucesso!", 3);
}

bool cCOINSHOP_T::LButtonDown()
{
	if (!OpenFlag)
		return false;

	bool bClicked = false;

	BaseX = (WinSizeX - 600) / 2;
	BaseY = (WinSizeY - 450) / 2;

	for (auto& Button : vButton)
	{
		if (Button)
		{
			if (isMousePos(BaseX + Button->x, BaseY + Button->y, Button->w, Button->h))
			{
				switch (Button->iID)
				{
				case MC::WEAPON:
				case MC::ARMOR:
				case MC::SHIELD:
				case MC::SETBLB:
				case MC::RINGS:
				case MC::SHELTONS:
				case MC::PREMIUM:
					SetSection(Button->iID);
					bClicked = true;
					break;

				case MC::LEFTARROW:
				case MC::RIGHTARROW:
					SetPage(Button->iID);
					bClicked = true;
					break;

				case MC::CLOSEBTN:
					Close();
					bClicked = true;
					break;

				case MC::BUYBTN:
					BuySelectedItem();
					bClicked = true;
					break;
				}
			}
		}
	}

	if (CurrentSection > 0 && vItemBox[CurrentSection - 1].size())
	{
		int begin = 12 * CurrentPage;
		int end = 12 * (CurrentPage + 1) > vItemBox[CurrentSection - 1].size() ? vItemBox[CurrentSection - 1].size() : 12 * (CurrentPage + 1);

		for (int i = begin; i < end; i++)
		{
			sITEMBOX* Box = vItemBox[CurrentSection - 1][i];
			if (Box && isMousePos(BaseX + Box->x, BaseY + Box->y, Box->w, Box->h))
			{
				SelectBox(Box);
				bClicked = true;
				break;
			}
		}
	}

	return bClicked;
}