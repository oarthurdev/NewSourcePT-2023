#pragma once

#include "roll.h"

struct RollItem
{
	DWORD iRollID;
	psITEM psItem;
	vector<pair<DWORD, int>> vPlayers;
	DWORD dwCreateTime;
	int x, y, z;
	STG_AREA* lpStgArea;
	bool bRolled;
};

class CRollHandler
{
public:
	static CRollHandler* getInstance();

	void CreateRoll(psITEM* lpItemInfo, vector<DWORD> vSerials, int x, int y, int z, STG_AREA* lpStgArea);
	void Main();

	void HandlePacket(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* psPacket);

private:
	void EndRoll(RollItem* pRoll);

	vector<RollItem> vRollItems;
	DWORD iRollScroll = 0;
	DWORD dwTime = 0;
};

#define ROLLHANDLER CRollHandler::getInstance()