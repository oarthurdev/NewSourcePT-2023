#pragma once

#include "sinbaram/sinLinkHeader.h"
#include "cRestaureWindow.h"
class cCOINSHOP
{
public:
	cCOINSHOP();
	~cCOINSHOP();

	void Init();
	void Draw();

	void RecvItemFromServer(smTRANS_SHOPDATA* lpTransShopData);
	void RecvCoinFromServer(smTRANS_COMMAND* lpTransCommand);

	void Open();
	bool isOpen();
	void Close();
	void Clear();

	bool LButtonDown();

	friend void cRESTAURE::Draw();
	friend void cRESTAURE::Restaure();

	int Coin;

private:

	struct sSHOPBUTTON
	{
		int iID;
		int iMat;
		int iHoverMat;
		int x, y, w, h;
		bool Selected;
		int Opacity;

		sSHOPBUTTON(int ID, int Mat, int HoverMat, int ix, int iy, int iw, int ih, bool bSelected, int iOpacity = 255)
		{
			iID = ID;
			iMat = Mat;

			if (HoverMat)
				iHoverMat = HoverMat;
			else
				iHoverMat = iMat;

			x = ix;
			y = iy;
			w = iw;
			h = ih;
			Selected = bSelected;
			Opacity = iOpacity;
		}
	};

	struct sITEMBOX
	{
		int x, y, w, h;
		int iMat, iHoverMat;
		int iID;
		bool Selected;

		sITEM* psItem;

		int Price;
		char PriceText[32];

		sITEMBOX(int ix, int iy, int iw, int ih, int Mat, int HoverMat, int ID, bool bSelected, sITEMINFO* pItemInfo, int iPrice)
		{
			x = ix;
			y = iy;
			w = iw;
			h = ih;
			iMat = Mat;
			iHoverMat = HoverMat;
			iID = ID;
			Selected = bSelected;

			if (pItemInfo)
			{
				psItem = new sITEM;
				LoadItemImage(pItemInfo, psItem);
			}

			Price = iPrice;
			wsprintf(PriceText, "%d Coins", iPrice);
		}
	};

	enum MC
	{
		BACKGROUND,
		WEAPON = 1,
		ARMOR = 2,
		SHIELD = 3,
		SETBLB = 4,
		RINGS = 5,
		SHELTONS = 6,
		PREMIUM = 7,
		ITEMBOX,
		WEAPON_,
		ARMOR_,
		SHIELD_,
		SETBLB_,
		RINGS_,
		SHELTONS_,
		PREMIUM_,
		ITEMBOX_,
		BUYBTN,
		LEFTARROW,
		RIGHTARROW,
		CLOSEBTN,
		MAX_MAT,
	};

	bool OpenFlag;
	vector<sSHOPBUTTON*> vButton;
	int Mat[MAX_MAT];
	int BaseX, BaseY;
	int CurrentSection;

	void SetSection(int iID);
	void SetButtonSelection(int iID);
	void SetPage(int iID);

	vector<sITEMBOX*> vItemBox[7];
	int PageCount[7];
	int CurrentPage;

	sITEMBOX* SelectedBox;

	void SelectBox(sITEMBOX* Box);

	void BuySelectedItem();

};

extern cCOINSHOP cCoinShop;