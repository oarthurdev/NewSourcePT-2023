#pragma once

#include "sinbaram/sinLinkHeader.h"
#include "Database/Database.h"

class cCOINSHOP
{
public:
	cCOINSHOP();
	~cCOINSHOP();

	void LoadItems();
	void RecvGetItemShop(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);
	void RecvGetItemCoin(rsPLAYINFO* lpPlayInfo);
	void RecvBuyShopItem(rsPLAYINFO* lpPlayInfo, smTRANS_BUYSHOP* lpTransBuy);
	int GetPlayerCoin(rsPLAYINFO * lpPlayInfo);
	void AddPlayerCoin(rsPLAYINFO * lpPlayInfo, int coin);

private:
	struct sITEMSHOP
	{
		char szItemCode[32];
		int Price;
		char ItemName[32];
	};

	vector<sITEMSHOP*> vItemShop[7];
};

extern cCOINSHOP cCoinShop;