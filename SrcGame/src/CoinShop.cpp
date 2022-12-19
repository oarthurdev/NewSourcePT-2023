#include "CoinShop.h"

cCOINSHOP cCoinShop;

bool isMousePos(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return true;

	return false;
}

cCOINSHOP::cCOINSHOP()
{
	Clear();
	Coin = 0;
}

cCOINSHOP::~cCOINSHOP()
{
	Clear();
}

void cCOINSHOP::Init()
{
	BaseX = 113;
	BaseY = 50;

	Mat[MC::BACKGROUND] = CreateTextureMaterial("game\\shop\\background.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::WEAPON] = CreateTextureMaterial("game\\shop\\armas.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ARMOR] = CreateTextureMaterial("game\\shop\\defesas.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHIELD] = CreateTextureMaterial("game\\shop\\trajes.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SETBLB] = CreateTextureMaterial("game\\shop\\acessorio.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RINGS] = CreateTextureMaterial("game\\shop\\sheltons.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHELTONS] = CreateTextureMaterial("game\\shop\\itenspremiuns.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::PREMIUM] = CreateTextureMaterial("game\\shop\\servico.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ITEMBOX] = CreateTextureMaterial("game\\shop\\itembox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Mat[MC::WEAPON_] = CreateTextureMaterial("game\\shop\\armas_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ARMOR_] = CreateTextureMaterial("game\\shop\\defesas_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHIELD_] = CreateTextureMaterial("game\\shop\\trajes_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SETBLB_] = CreateTextureMaterial("game\\shop\\acessorio_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RINGS_] = CreateTextureMaterial("game\\shop\\sheltons_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::SHELTONS_] = CreateTextureMaterial("game\\shop\\itenspremiuns_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::PREMIUM_] = CreateTextureMaterial("game\\shop\\servico_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::ITEMBOX_] = CreateTextureMaterial("game\\shop\\itembox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Mat[MC::BUYBTN] = CreateTextureMaterial("game\\shop\\buy.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::LEFTARROW] = CreateTextureMaterial("game\\shop\\left.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::RIGHTARROW] = CreateTextureMaterial("game\\shop\\right.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MC::CLOSEBTN] = CreateTextureMaterial("game\\shop\\close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cCOINSHOP::Clear()
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

void cCOINSHOP::Open()
{
	Clear();

	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_GET_SHOPCOIN;
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

bool cCOINSHOP::isOpen()
{
	return OpenFlag;
}

void cCOINSHOP::Close()
{
	Clear();

	DispEachMode = FALSE;
	CurrentSection = 0;
	CurrentPage = 0;
	SelectedBox = 0;
	OpenFlag = false;
}

void cCOINSHOP::SetButtonSelection(int iID)
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

void cCOINSHOP::SetPage(int iID)
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

void cCOINSHOP::SetSection(int iID)
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
		smTransCommand.code = OpCode::OPCODE_GET_SHOPITEM;
		smTransCommand.WParam = CurrentSection;

		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}
}

void cCOINSHOP::RecvItemFromServer(smTRANS_SHOPDATA * lpTransShopData)
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

void cCOINSHOP::RecvCoinFromServer(smTRANS_COMMAND * lpTransCommand)
{
	Coin = lpTransCommand->WParam;
}

void cCOINSHOP::Draw()
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
				dsTextLineOut(0,BaseX + Item->x + 15, BaseY + Item->y + Item->h - 20, Item->PriceText, lstrlen(Item->PriceText));
			}
		}
	}

	char CoinBuff[32] = {};
	NumLineComa(Coin, CoinBuff);
	SetFontTextColor(RGB(255, 255, 255));
	dsTextLineOut(0,BaseX + 98, BaseY + 385, CoinBuff, lstrlen(CoinBuff));

	ZeroMemory(CoinBuff, sizeof(CoinBuff));
	NumLineComa(lpCurPlayer->smCharInfo.Money, CoinBuff);
	dsTextLineOut(0,BaseX + 78, BaseY + 407, CoinBuff, lstrlen(CoinBuff));
}

void cCOINSHOP::SelectBox(sITEMBOX * Box)
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

void cCOINSHOP::BuySelectedItem()
{
	if (!SelectedBox)
	{
		cMessageBox.ShowMessageEvent("Selecione um item para comprar .");
		return;
	}

	if (Coin < SelectedBox->Price)
	{
		cMessageBox.ShowMessageEvent("Você não tem credito suficiente.");
		return;
	}

	if (!cInvenTory.CheckSetEmptyArea(SelectedBox->psItem))
	{
		cMessageBox.ShowMessageEvent("Não tem espaõ suficiente no inventuario.");
		return;
	}

	if (!cInvenTory.CheckSetOk(SelectedBox->psItem, 1))
	{
		cMessageBox.ShowMessageEvent("Peso Limite.");
		return;
	}
	UINT timeDoshop;
	timeDoshop = GetTickCount();
	smTRANS_BUYSHOP TransBuy = {};
	TransBuy.code = OpCode::OPCODE_BUY_SHOPITEM;
	TransBuy.size = sizeof(smTRANS_BUYSHOP);
	lstrcpy(TransBuy.szItemCode, SelectedBox->psItem->LastCategory);
	smWsockDataServer->Send((char*)&TransBuy, TransBuy.size, TRUE);

	cMessageBox.ShowMessageEvent("Comprado com sucesso");

	AddChatBuff("> Comprado com sucesso!", 3);
}

bool cCOINSHOP::LButtonDown()
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