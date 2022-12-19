#include "sinbaram/sinLinkHeader.h"
#include "Server/onserver.h"
#include "CRollHandler.h"

#include <iostream>
using namespace std;

CRollHandler cRollHandler;

CRollHandler * CRollHandler::getInstance()
{
	return &cRollHandler;
}

void CRollHandler::CreateRoll(psITEM * lpItemInfo, vector<DWORD> vSerials, int x, int y, int z, STG_AREA* lpStgArea)
{
	if (!vSerials.size())
		return;

	iRollScroll++;
	RollItem sRoll;
	memcpy(&sRoll.psItem, lpItemInfo, sizeof(psITEM));
	sRoll.iRollID = iRollScroll % 1024;
	sRoll.dwCreateTime = GetCurrentTime();
	sRoll.x = x;
	sRoll.y = y;
	sRoll.z = z;
	sRoll.lpStgArea = lpStgArea;
	sRoll.bRolled = false;
	
	PacketRollInfo sPacket;
	sPacket.size = sizeof(sPacket);
	sPacket.code = OpCode::OPCODE_ROLL;
	memcpy(&sPacket.sItemInfo, &sRoll.psItem.ItemInfo, sizeof(sITEMINFO));
	sPacket.iRollID = sRoll.iRollID;

	for (auto Serial : vSerials)
	{
		rsPLAYINFO* lpPlayInfo = FindUserFromCode(Serial);
		if (lpPlayInfo)
		{
			sRoll.vPlayers.push_back({ Serial, 0 });
			lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
		}
	}

	vRollItems.push_back(sRoll);
}

void CRollHandler::Main()
{
	if (dwTime + 500 < GetCurrentTime())
	{
		dwTime = GetCurrentTime();

		for (auto it = vRollItems.begin(); it != vRollItems.end(); it++)
		{
			auto sRoll = (*it);
			if (sRoll.dwCreateTime + 15000 < GetCurrentTime())
			{
				EndRoll(&sRoll);
				vRollItems.erase(it);
				it--;
			}
		}
	}
}

void CRollHandler::HandlePacket(rsPLAYINFO * lpPlayInfo, smTRANS_COMMAND * psPacket)
{
	int val = -1;
	TRANS_CHATMESSAGE sPacket;
	sPacket.code = OpCode::OPCODE_WHISPERMESSAGE;

	if (psPacket->LParam == 1)
	{
		val = (rand() % 100) + 1;
		wsprintf(sPacket.szMessage, "> %s tirou %d na roleta!", lpPlayInfo->getName().c_str(), val);
	}
	else
	{
		wsprintf(sPacket.szMessage, "> %s optou por não jogar na roleta.", lpPlayInfo->getName().c_str());
	}

	sPacket.size = lstrlen(sPacket.szMessage) + 32;
	sPacket.dwIP = 9;
	sPacket.dwObjectSerial = 0;

	for (auto &Roll : vRollItems)
	{
		if (Roll.iRollID == psPacket->WParam)
		{
			for (auto &Player : Roll.vPlayers)
			{
				if (Player.first == lpPlayInfo->dwObjectSerial)
				{
					if (Player.second == 0)
						Player.second = val;

					//cout << Player.first << " | " << Player.second << endl;
					
					lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);

					if(val > 0)
						Roll.bRolled = true;
				}
				else
				{

					rsPLAYINFO* playerInfo = FindUserFromCode(Player.first);
					if (playerInfo)
					{
						playerInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
					}
				}
			}
		}
	}
}

extern int rsPutItem2(rsPLAYINFO *lpPlayInfo, sITEMINFO *lpItem);
//extern int RecordLog(char* lpLogName, char *lpBuff);

void CRollHandler::EndRoll(RollItem* pRoll)
{
	TRANS_CHATMESSAGE TransChatMessage;
	TransChatMessage.code = OpCode::OPCODE_WHISPERMESSAGE;

	if (!pRoll->bRolled)
	{
		if (pRoll->lpStgArea)
		{
			pRoll->psItem.state = TRUE;
			auto lpStgItem = pRoll->lpStgArea->AddItem(&pRoll->psItem, pRoll->x, pRoll->y, pRoll->z, TRUE);
			if (lpStgItem)
				pRoll->lpStgArea->SendStgItemToNearUsers(lpStgItem);
		}

		wsprintf(TransChatMessage.szMessage, "> Ninguém recebeu o item %s.", pRoll->psItem.ItemInfo.ItemName);
	}
	else
	{
		sort(pRoll->vPlayers.begin(), pRoll->vPlayers.end(), [](auto a, auto b) { return a.second > b.second; });

		for (auto p : pRoll->vPlayers)
		{
			rsPLAYINFO* lpPlayInfo = FindUserFromCode(p.first);
			if (lpPlayInfo)
			{
				char buff[255];
				wsprintf(buff, "Name:( %s ) Level( %d ) Item( %s ) Code( %d ) Unique Number( %d %d ) Spec Code( %d )",
					lpPlayInfo->smCharInfo.szName, lpPlayInfo->smCharInfo.Level,
					pRoll->psItem.ItemInfo.ItemName,
					pRoll->psItem.ItemInfo.CODE,
					pRoll->psItem.ItemInfo.ItemHeader.Head,
					pRoll->psItem.ItemInfo.ItemHeader.dwChkSum,
					pRoll->psItem.ItemInfo.JobCodeMask);
				//RecordLog("ROLL", buff);
				rsPutItem2(lpPlayInfo, &pRoll->psItem.ItemInfo);
				wsprintf(TransChatMessage.szMessage, "> %s ganhou %s na roleta com o numero %d!", lpPlayInfo->getName().c_str(), pRoll->psItem.ItemInfo.ItemName, p.second);
				break;
			}
		}
	}

	TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
	TransChatMessage.dwIP = 9;
	TransChatMessage.dwObjectSerial = 0;

	smTRANS_COMMAND sPacket;
	sPacket.code = OpCode::OPCODE_ENDROLL;
	sPacket.size = sizeof(sPacket);
	sPacket.WParam = pRoll->iRollID;

	for (auto p : pRoll->vPlayers)
	{
		rsPLAYINFO* lpPlayInfo = FindUserFromCode(p.first);
		if (lpPlayInfo)
		{
			lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
			lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}
}
