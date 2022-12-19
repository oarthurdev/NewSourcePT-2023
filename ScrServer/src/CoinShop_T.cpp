#include "CoinShop_T.h"

cCOINSHOP_T cCoinShop_T;

cCOINSHOP_T::cCOINSHOP_T()
{
}

cCOINSHOP_T::~cCOINSHOP_T()
{
	for (int i = 0; i < 7; i++)
	{
		if (vItemShop[i].size())
		{
			for (auto& itemShop : vItemShop[i])
			{
				if (itemShop)
				{
					delete itemShop;
					itemShop = 0;
				}
			}

			vItemShop[i].clear();
		}
	}
}

void cCOINSHOP_T::LoadItems()
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_CoinShopDB);

	for (int i = 0; i < 7; i++)
	{
		if (vItemShop[i].size())
		{
			for (auto& itemShop : vItemShop[i])
			{
				if (itemShop)
				{
					delete itemShop;
					itemShop = 0;
				}
			}

			vItemShop[i].clear();
		}
	}


	if (db && db->Open())
	{
		if (db->Prepare("SELECT * FROM ItemList_T WHERE ItemSection > 0 AND ItemSection < 8"))
		{
			if (db->Execute(false))
			{
				while (db->NextRow())
				{
					sITEMSHOP* pItemShop = new sITEMSHOP;
					int Section = 0;

					db->GetData(pItemShop->szItemCode, 32, 1, PARAMTYPE_String);
					db->GetData(&Section, 4, 2, PARAMTYPE_Integer);
					db->GetData(&pItemShop->Price, 4, 3, PARAMTYPE_Integer);

					if (Section > 0 && Section <= 7)
						vItemShop[Section - 1].push_back(pItemShop);
				}
			}
		}
	}
}

#define	DEF_ITEM_MAX		2000

extern int DefaultItemCount;
extern sDEF_ITEMINFO DefaultItems[DEF_ITEM_MAX];

void cCOINSHOP_T::RecvGetItemShop(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND * lpTransCommand)
{
	if (lpTransCommand->WParam <= 0 || lpTransCommand->WParam > 7 || !lpPlayInfo->lpsmSock)
		return;



	int Section = lpTransCommand->WParam - 1;
	int cnt = 0;
	int itemCount = 0;
	DWORD dwCode = 0;
	sDEF_ITEMINFO* lpDefItem = 0;
	smTRANS_SHOPDATA TransShopData;

	if (vItemShop[Section].size())
	{
		TransShopData.code = OpCode::OPCODE_GET_SHOPITEM_T;
		TransShopData.size = sizeof(smTRANS_SHOPDATA);
		TransShopData.Section = lpTransCommand->WParam;

		for (auto& itemShop : vItemShop[Section])
		{
			if (itemShop && itemShop->szItemCode[0])
			{
				for (cnt = 0; cnt < MAX_ITEM; cnt++)
				{
					if (!lstrcmpi(itemShop->szItemCode, sItem[cnt].LastCategory))
					{
						dwCode = sItem[cnt].CODE;
						break;
					}
				}

				if (dwCode)
				{
					for (cnt = 0; cnt < DefaultItemCount; cnt++) {
						if (!DefaultItems[cnt].Item.UniqueItem && dwCode == DefaultItems[cnt].Item.CODE) {
							lpDefItem = &DefaultItems[cnt];
							break;
						}
					}

					memcpy(&TransShopData.sCompItem[itemCount], lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
					TransShopData.sCompItem[itemCount].Price = itemShop->Price;
					itemCount++;

					if (itemCount >= 15)
					{
						TransShopData.Count = itemCount;
						lpPlayInfo->lpsmSock->Send((char*)&TransShopData, TransShopData.size, TRUE);
						ZeroMemory(TransShopData.sCompItem, sizeof(sCOMPRESSED) * 15);
						itemCount = 0;
						TransShopData.Count = 0;
					}
				}
			}
		}

		if (itemCount > 0)
		{
			TransShopData.Count = itemCount;
			lpPlayInfo->lpsmSock->Send((char*)&TransShopData, TransShopData.size, TRUE);
		}
	}
}

void cCOINSHOP_T::RecvGetItemCoin(rsPLAYINFO * lpPlayInfo)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_CoinShopDB);
	smTRANS_COMMAND TransCommand = {};

	if (db->Open())
	{
		char playerID[32];
		wsprintf(playerID, "%s", lpPlayInfo->getAccount().c_str());
		if (db->Prepare("IF NOT EXISTS(SELECT * FROM UserInfo_T WHERE UserID=?) BEGIN INSERT INTO UserInfo VALUES (?, 0, GETDATE()) END"))
		{
			db->BindInputParameter(playerID, 1, PARAMTYPE_String);
			db->BindInputParameter(playerID, 2, PARAMTYPE_String);
			db->Execute();
		}

		if (db->Prepare("SELECT * FROM UserInfo_T WHERE UserID=?"))
		{
			db->BindInputParameter(playerID, 1, PARAMTYPE_String);
			if (db->Execute())
			{
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.code = OpCode::OPCODE_GET_SHOPCOIN_T;
				db->GetData(&TransCommand.WParam, 4, 2, PARAMTYPE_Integer);
				lpPlayInfo->lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
			}
		}

		db->Close();
	}
}

extern int CreateCommandItem(rsPLAYINFO *lpPlayInfo, rsPLAYINFO *lpPlayInfo2, char *szItem);

extern int GetPostBoxFile(const char *szID, char *szFileName);

extern void SendPostBox(char* szID, char* szItemCode, int spec);

void cCOINSHOP_T::RecvBuyShopItem(rsPLAYINFO * lpPlayInfo, smTRANS_BUYSHOP * lpTransBuy)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_CoinShopDB);

	if (db->Open())
	{
		char playerID[32];
		wsprintf(playerID, "%s", lpPlayInfo->getAccount().c_str());
		if (db->Prepare("SELECT * FROM ItemList_T WHERE szItemCode=?"))
		{
			db->BindInputParameter(lpTransBuy->szItemCode, 1, PARAMTYPE_String);
			if (db->Execute())
			{
				int Price = 0;
				int PlayerCoin = 0;

				db->GetData(&Price, 4, 3, PARAMTYPE_Integer);

				if (Price > 0)
				{
					if (db->Prepare("SELECT * FROM UserInfo_T WHERE UserID=?"))
					{
						db->BindInputParameter(playerID, 1, PARAMTYPE_String);
						if (db->Execute())
						{
							db->GetData(&PlayerCoin, 4, 2, PARAMTYPE_Integer);

							if (PlayerCoin >= Price)
							{
								PlayerCoin -= Price;
								if (db->Prepare("UPDATE UserInfo_T SET UserCoin=?, LastChange=GETDATE() WHERE UserID=?"))
								{
									db->BindInputParameter(&PlayerCoin, 1, PARAMTYPE_Integer);
									db->BindInputParameter(playerID, 2, PARAMTYPE_String);

									if (db->Execute(false))
									{
										if (lpTransBuy->szItemCode[0] == 'P' || lpTransBuy->szItemCode[0] == 'p' || lpTransBuy->szItemCode[0] == 'G' || lpTransBuy->szItemCode[0] == 'g')
										{
											CreateCommandItem(lpPlayInfo, lpPlayInfo, lpTransBuy->szItemCode);
											//SendPostBox(playerID, lpTransBuy->szItemCode, 1);
										}
										else
											CreateCommandItem(lpPlayInfo, lpPlayInfo, lpTransBuy->szItemCode);
											//SendPostBox(playerID, lpTransBuy->szItemCode, lpPlayInfo->smCharInfo.JOB_CODE);
									}

								}
							}
						}
					}
				}
			}
		}
		db->Close();
	}

	RecvGetItemCoin(lpPlayInfo);
}

int cCOINSHOP_T::GetPlayerCoin(rsPLAYINFO * lpPlayInfo)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_CoinShopDB);
	char playerID[32];
	int coin;

	lstrcpy(playerID, lpPlayInfo->getAccount().c_str());

	if (db->Open())
	{
		if (db->Prepare("IF NOT EXISTS(SELECT * FROM UserInfo_T WHERE UserID=?) BEGIN INSERT INTO UserInfo_T VALUES (?, 0, GETDATE()) END"))
		{
			db->BindInputParameter(playerID, 1, PARAMTYPE_String);
			db->BindInputParameter(playerID, 2, PARAMTYPE_String);
			db->Execute();
		}

		if (db->Prepare("SELECT * FROM UserInfo_T WHERE UserID=?"))
		{
			db->BindInputParameter(playerID, 1, PARAMTYPE_String);
			if (db->Execute())
			{
				db->GetData(&coin, 4, 2, PARAMTYPE_Integer);
			}
		}

		db->Close();
	}

	return coin;
}

void cCOINSHOP_T::AddPlayerCoin(rsPLAYINFO * lpPlayInfo, int coin)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_CoinShopDB);
	char playerID[32];

	lstrcpy(playerID, lpPlayInfo->getAccount().c_str());

	if (db->Open())
	{

		if (db->Prepare("IF NOT EXISTS(SELECT * FROM UserInfo_T WHERE UserID=?) BEGIN INSERT INTO UserInfo_T VALUES (?, 0, GETDATE()) END"))
		{
			db->BindInputParameter(playerID, 1, PARAMTYPE_String);
			db->BindInputParameter(playerID, 2, PARAMTYPE_String);
			db->Execute();
		}

		if (db->Prepare("UPDATE UserInfo_T SET UserMinutos=UserMinutos + ? WHERE UserID=?"))
		{
			db->BindInputParameter(&coin, 1, PARAMTYPE_Integer);
			db->BindInputParameter(playerID, 2, PARAMTYPE_String);
			db->Execute();
		}
	
		db->Close();
	}
}