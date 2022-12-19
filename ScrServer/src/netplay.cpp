

#include "smlib3d\\smd3d.h"

#include "SocketServer/smwsock.h"
#include "character.h"
#include "playmain.h"
#include "fileread.h"

#include "particle.h"
#include "sinbaram\\sinlinkheader.h"
#include "record.h"
#include "netplay.h"
#include "playsub.h"
#include "field.h"
#include "Language\\language.h"
#include "Language\\jts.h"
#include "TextMessage.h"
#include "cracker.h"
#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\help.h"
#include "damage.h"
#include "skillsub.h"

#include "AreaServer.h"

#include "BellatraFontEffect.h"
#include "Server\\onserver.h"



#include "WinInt\\WinIntThread.h"
#include "WinInt\\WavIntHttp.h"
#include "WinInt\\ZipLib.h"


#include "CurseFilter.h"		



extern int WinSizeX;
extern int WinSizeY;
extern HWND hwnd;

#define SERVER_CHAR_INFO


#define RECORD_TIME_STEP		(5*60*1000)

#define NET_LOADING_WAIT_LIMIT		10000


extern CRITICAL_SECTION	cSection;
extern rsRECORD_DBASE	rsRecorder;
DWORD	dwLastRecordTime = 0;

CRITICAL_SECTION	cServSection;

int Debug_SendCount = 0;
int Debug_RecvCount1 = 0;
int Debug_RecvCount2 = 0;
int Debug_RecvCount3 = 0;

int NetWorkInitFlag = 0;
int	BellatraEffectInitFlag = 0;
SBL_SetFontEffect SoD_SetFontEffect;


DWORD	dwTime_ServerT = 0;
DWORD	dwTime_ConnectMS = 0;





#ifdef _LANGUAGE_BRAZIL
#ifndef	_WINMODE_DEBUG
#define	CLIENT_VERSION_NUM		4135
#else
#define	CLIENT_VERSION_NUM		15030
#endif
#endif


#define CLIENT_VERSION_CHECK	(-CLIENT_VERSION_NUM * 2)

int	Client_Version = CLIENT_VERSION_NUM;
int	Server_LimitVersion = CLIENT_VERSION_NUM;


int	Version_WareHouse = 1;
int	Version_CharInfo = 1;


SocketData* smWsockServer = 0;
SocketData* smWsockDataServer = 0;
SocketData* smWsockUserServer = 0;
SocketData* smWsockExtendServer = 0;


int	ReconnDataServer = 0;
int	ReconnServer = 0;

char	szConnServerName[16];

DWORD	dwRecvUserServerTime = 0;
DWORD	dwRecvDataServerTime = 0;
DWORD	dwRecvServerTime = 0;
DWORD	dwRecvExtendServerTime = 0;


int	rsRecvDataServer = TRUE;
int	rsRecvServer = TRUE;
int	rsRecvUserServer = TRUE;
int	rsRecvExtendServer = TRUE;

#define CHATBUFF_MAX		64
#define CHATBUFF_MASK		63

DWORD dwMyIP;

CHATBUFF ChatBuff[CHATBUFF_MAX];
CHATBUFF ChatBuff2[6][CHATBUFF_MAX];


int	ChatBuffCnt = 0;
int	ChatBuffCnt2[6] = { 0,0,0,0,0,0 };
int ChatDispCnt = 0;
int	ChatBuffCompCnt = 0;

char* szDefaultServIP = "211.50.44.170";

char* szNetLogFile = "debugnet.log";
FILE* fpNetLog = 0;


int	DisconnectFlag = 0;
int	DisconnectServerCode = 0;


int	WarningHack = 0;

DWORD	dwQuestDelayTime = 0;

DWORD	dwLoadingTime = 0;

char szServIP[32];
DWORD dwServPort;
char szDataServIP[32];
DWORD dwDataServPort;
char szUserServIP[32];
DWORD dwUserServPort;
char szExtendServIP[32];
DWORD dwExtendServPort;



DWORD	dwConnectedClientTime = 0;
DWORD	dwConnectedServerTime = 0;
DWORD	dwLastRecvGameServerTime = 0;
DWORD	dwLastRecvGameServerTime2 = 0;
DWORD	dwLastRecvGameServerTime3 = 0;
DWORD	dwLastRecvGameServerTime4 = 0;

typedef DWORD(*LPFN_CheckMem)(TRANS_FUNC_MEMORY* TransFuncMem, smTRANS_COMMAND* lpTransCommand);
LPFN_CheckMem	fnChkMem2;


static int	CompWareHouseMoney = 0;
int	WareHouseSubMoney = 0;
int TotalSubMoney = 0;
int TotalAddMoney = 0;
int	TotalAddExp = 0;
int	TotalSubExp = 0;


smTRANS_COMMAND* lpTransVirtualPotion = 0;


LPFN_CheckMem	fnChkMem;
DWORD	dwMemFunChkCode = 0;

int	RecvMemFuncData(TRANS_FUNC_MEMORY* TransFuncMem);
int	RecvMemFuncData2(TRANS_FUNC_MEMORY* TransFuncMem);

DWORD funcCheckMemSum(DWORD FuncPoint, int count);

int CheckProcessModule();



smPLAYDATA	PlayData;
char	TransBuff[smSOCKBUFF_SIZE];
int		TransLen;



TRANS_ITEMINFO	TransThrowItem;

TRANS_ITEMINFO	TransRecvItem;


TRANS_TRADE_ITEMKEY	LastTransTradeItemKey;
DWORD				dwLastTransTradeKeyTime = 0;

int					InitClanMode = 0;

DWORD				dwYahooTime = 0;

int					ServerHideMode = 0;



PK_FIELD_STATE	PK_FieldState;



struct TRANS_TRADE_CHECKITEM
{
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwSendItemCode[MAX_TRADE_ITEM];
	DWORD	dwSendItemSum[MAX_TRADE_ITEM];

	DWORD	dwRecvItemCode[MAX_TRADE_ITEM];
	DWORD	dwRecvItemSum[MAX_TRADE_ITEM];
};



int		TradeItemSucessFlag = 0;
int		TradeRecvItemKeyFlag = 0;
int		TradeSendSucessFlag = 0;
DWORD	dwTradeMaskTime = 0;
int		TradeItemCancelCount = 0;

TRANS_TRADEITEMS	TransLastRecvTrade;

TRANS_TRADEITEMS	TransTradeItems_MyShop;


DWORD	dwLastWareHouseChkSum = 0;


int		TransAgingItemFlag;

smTRANS_COMMAND	TransServerConnectInfo;


int ConnectOtherPlayer(DWORD dwIP);

int HoRecvMessage(DWORD dwCode, void* RecvBuff);


int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY* lpTransTradeItemKey, sTRADE* lpTrade);

int SendTradeSucessKey(sTRADE* lpTrade, DWORD dwSender);

int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM* lpTransTradeCheckItem);

int SendCrackWindow(HWND hWnd);


int ThrowItemToServer(smTRANS_COMMAND_EX* lpTransCommand);

int RecvCheckItemFromServer(TRANS_ITEM_CODE* lpTransItemCode);

int	SendClientFuncPos();


int OpenTimeCheckThread();

int SendPlayTimerMax();



TRANS_ITEMINFO* FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	PushRecvTransItemQue(TRANS_ITEMINFO* lpTransItemInfo);


int RecvProcessSkill(smTRANS_COMMAND* lpTransCommand);

int RecvPartySkillFromServer(TRANS_PARTY_SKILL* lpTransPartySkill);


int FiltQuestItem(TRANS_ITEMINFO* lpTransItemInfo, DWORD dwPacketCode);

int SucessLinkCore(smTRANS_COMMAND_EX* lpTransCommandEx);

int RecvSodGameInfomation(void* Info);


int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2* lpTransItemGroup2);


int XTrap_Recv(smTRANS_COMMAND* lpPacket, SocketData* lpsmSock);


rsBLESS_CASTLE	rsBlessCastleOld;


DWORD	dwResistance_SendingTime = 0;



#define	ATT_MONSTER_MAX	128
#define	ATT_MONSTER_MASK	(ATT_MONSTER_MAX-1)

DWORD	dwAttMonsterCodeList[ATT_MONSTER_MAX];
int		AttMonsterCodeCount = 0;


int ClearAttMonsterCode()
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++)
	{
		dwAttMonsterCodeList[cnt] = 0;
	}
	return TRUE;
}

int	AddAttMonsterCode(DWORD dwCode)
{
	int mcnt;
	if (dwCode)
	{
		mcnt = (AttMonsterCodeCount - 1) & ATT_MONSTER_MASK;
		if (dwAttMonsterCodeList[mcnt] == dwCode) return TRUE;
		mcnt = AttMonsterCodeCount & ATT_MONSTER_MASK;
		dwAttMonsterCodeList[mcnt] = dwCode;
		AttMonsterCodeCount++;
		return TRUE;
	}

	return FALSE;
}

int	CheckAttMonsterCode(DWORD dwCode)
{
	int cnt;
	for (cnt = 0; cnt < ATT_MONSTER_MAX; cnt++)
	{
		if (dwAttMonsterCodeList[cnt] == dwCode) return TRUE;
	}
	return FALSE;
}


int CheckServerInfo(smTRANS_COMMAND* lpTransCommand)
{
	if ((-Client_Version * 2) != CLIENT_VERSION_CHECK)
	{
		SetGameError(1);
		return TRUE;
	}

	if (Client_Version < lpTransCommand->WParam)
	{
		SetGameError(1);
		return TRUE;
	}

	if (lpTransCommand->LParam > 0)
	{
		SetGameError(2);
		return TRUE;
	}

	SetGameError(0);
	return TRUE;
}


int SendProcessInfo()
{
	TRANS_CHATMESSAGE	smTransChatMessage;

	if (smWsockDataServer)
	{
		smTransChatMessage.code = OpCode::OPCODE_PROCESSINFO;
		smTransChatMessage.dwIP = dwExeCheckSum;
		smTransChatMessage.dwObjectSerial = dwExeCheckSum;

		strcpy_s(smTransChatMessage.szMessage, szProcessPath);
		smTransChatMessage.size = 32 + lstrlen(szProcessPath);

		return smWsockDataServer->Send((char*)&smTransChatMessage, smTransChatMessage.size, TRUE);
	}
	return FALSE;
}



SocketData* ConnectServer_Main()
{


	return NULL;
}


int DisconnectServerFull()
{/*
	if(smWsockDataServer && smWsockDataServer != smWsockServer)
	{
		smWsockDataServer->CloseSocket();
		smWsockDataServer = 0;
	}
	if(smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		smWsockUserServer->CloseSocket();
		smWsockUserServer = 0;
	}
	if(smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		smWsockExtendServer->CloseSocket();
		smWsockExtendServer = 0;
	}
	if(smWsockServer)
	{
		smWsockServer->CloseSocket();
		smWsockServer = 0;
	}

	DisconnectFlag = 0;*/

	return TRUE;
}



SocketData* ConnectServer_InfoMain()
{
	return NULL;
}


SocketData* ConnectServer_GameMain(char* szIP1, DWORD dwPort1, char* szIP2, DWORD dwPort2)
{
	return NULL;
}

SocketData* ConnectServer_GameMain(char* szIP1, DWORD dwPort1, char* szIP2, DWORD dwPort2, char* szIP3, DWORD dwPort3)
{
	return NULL;
}



int DisconnectServer_GameMain()
{/*
	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockExtendServer)
		{
			smWsockExtendServer->CloseSocket();
		}
	}
	smWsockExtendServer = 0;

	if (smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockUserServer)
		{
			smWsockUserServer->CloseSocket();
		}
	}
	smWsockUserServer = 0;


	if (smWsockServer && smWsockDataServer != smWsockServer)
	{
		if (smWsockDataServer != smWsockServer)
		{
			smWsockServer->CloseSocket();
		}
	}
	smWsockServer = 0;

	DisconnectFlag = 0;*/

	return TRUE;
}


SocketData* GetServerSock(int ServerCode)
{
	switch (ServerCode)
	{
	case PLAY_SERVER_CODE_EXTEND:
		if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
			return smWsockExtendServer;
		else
			return smWsockUserServer;

	case PLAY_SERVER_CODE_USER:
		return smWsockUserServer;

	case PLAY_SERVER_CODE_MAIN:
		return smWsockServer;

	case PLAY_SERVER_CODE_AREA1:
		return lpWSockServer_DispArea[0];

	case PLAY_SERVER_CODE_AREA2:
		return lpWSockServer_DispArea[1];

	}

	return NULL;
}


SocketData* GetAreaServerSock()
{
	int ServerCode;

	if (lpCurPlayer->OnStageField >= 0)
	{
		if (AreaServerMode)
		{
			return lpWSockServer_DispArea[lpCurPlayer->OnStageField];
		}
		else
		{
			ServerCode = StageField[lpCurPlayer->OnStageField]->ServerCode;
			return GetServerSock(ServerCode);
		}
	}

	return NULL;
}



scITEM* FindScItem(int x, int z)
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (scItems[cnt].Flag && scItems[cnt].pX == x && scItems[cnt].pZ == z)
		{
			return &scItems[cnt];
		}
	}

	return NULL;
}


scITEM* FindEmptyScItem()
{
	int cnt;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (!scItems[cnt].Flag) return &scItems[cnt];
	}

	return NULL;
}


int GetTradeDistance(smCHAR* lpChar)
{
	int	x, y, z;
	int dist;

	x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
	y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
	z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < (256 * 256)) return TRUE;

	return FALSE;
}


int GetTradeDistanceFromCode(DWORD dwObjectSerial)
{
	smCHAR* lpChar;

	lpChar = FindAutoPlayer(dwObjectSerial);

	if (lpChar && lpChar->DisplayFlag && lpChar->smCharInfo.szName[0])
	{

		return  GetTradeDistance(lpChar);

	}
	return FALSE;
}


int	CheckStartCharInfo()
{

	smCHAR_INFO	smCharInfo;
	int cnt;

	memcpy(&smCharInfo, sinChar, sizeof(smCHAR_INFO));

	CheckCharForm();
	CodeXorExp = dwPlayTime + smCharInfo.Exp;
	CodeXorExp_High = dwPlayTime | (dwPlayTime * dwPlayTime);
	CodeXorLife = (dwPlayTime * smCharInfo.Life[0]) & 0xFFFF;
	cnt = smCharInfo.Dexterity + smCharInfo.Health + smCharInfo.Spirit + smCharInfo.Strength + smCharInfo.Talent;

	if (smCharInfo.Level >= 2 || cnt > 102 || smCharInfo.Exp || smCharInfo.ChangeJob || smCharInfo.Money)
	{

		SendSetHackUser2(6000, smCharInfo.Money);
		WarningHack = TRUE;
		return FALSE;
	}

	lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
	lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;

	lpCurPlayer->smCharInfo.Life[0] ^= CodeXorLife;
	ReformCharForm();

	return TRUE;
}


int	RecvMemFuncData2(TRANS_FUNC_MEMORY* TransFuncMem)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = -1;
	fnChkMem2 = (LPFN_CheckMem)((void*)TransFuncMem->szData);
	fnChkMem2(TransFuncMem, &smTransCommand);

	ZeroMemory(TransFuncMem, 1500);

	if (smTransCommand.size > 0 && smWsockDataServer)
	{
		smTransCommand.code = OpCode::OPCODE_FUNCTION_MEM2;
		smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}



sSERVER_MONEY	sServerMoney[3] = { {0,0,0,0,0},{0,0,0,0,0} };
sSERVER_EXP		sServerExp[3] = { {0,0,0,0},{0,0,0,0} };
DWORD			dwLastSendTotalExpMoenyTime = 0;


int	SendTotalExpMoney()
{
	TRANS_TOTAL_EXPMONEY	TransTotalExpMoney;

	if ((dwLastSendTotalExpMoenyTime + 30000) > dwPlayTime) return FALSE;

	TransTotalExpMoney.code = OpCode::OPCODE_CHECK_EXPMONEY;
	TransTotalExpMoney.size = sizeof(TRANS_TOTAL_EXPMONEY);

	if (smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[0], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[0], sizeof(sSERVER_MONEY));
		smWsockServer->Send((char*)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}
	if (smWsockUserServer && smWsockUserServer != smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[1], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[1], sizeof(sSERVER_MONEY));
		smWsockUserServer->Send((char*)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}
	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
	{
		memcpy(&TransTotalExpMoney.sServerExp, &sServerExp[2], sizeof(sSERVER_EXP));
		memcpy(&TransTotalExpMoney.sServerMoney, &sServerMoney[2], sizeof(sSERVER_MONEY));
		smWsockExtendServer->Send((char*)&TransTotalExpMoney, TransTotalExpMoney.size, TRUE);
	}

	dwLastSendTotalExpMoenyTime = dwPlayTime;

	return TRUE;
}


int CheckServerMoney(SocketData* lpsmSock, TRANS_ITEMINFO* lpTransItemInfo)
{
	sSERVER_MONEY* lpServerMoney;

	lpServerMoney = 0;

	if (lpsmSock == smWsockServer)
	{
		lpServerMoney = &sServerMoney[0];
	}
	else
	{
		if (lpsmSock == smWsockUserServer)
		{
			lpServerMoney = &sServerMoney[1];
		}
		else if (lpsmSock == smWsockExtendServer)
		{
			lpServerMoney = &sServerMoney[2];
		}
	}

	if (lpServerMoney)
	{
		lpServerMoney->InputMoney += lpTransItemInfo->Item.Money;
		lpServerMoney->Counter++;
		lpServerMoney->TotalX = lpTransItemInfo->x;
		lpServerMoney->TotalY = lpTransItemInfo->y;
		lpServerMoney->TotalZ = lpTransItemInfo->z;



		int cnt;
		cnt = lpServerMoney->TotalZ ^ (lpServerMoney->TotalX + lpServerMoney->TotalY);
		cnt += 200;
		if (cnt < lpServerMoney->InputMoney)
		{

		}
	}

	return TRUE;
}


int CheckServerExp(SocketData* lpsmSock, smTRANS_COMMAND* lpTransCommand)
{
	sSERVER_EXP* lpServerExp = nullptr;

	if (lpsmSock == smWsockServer)
	{
		lpServerExp = &sServerExp[0];
	}
	else
	{
		if (lpsmSock == smWsockUserServer)
		{
			lpServerExp = &sServerExp[1];
		}
		else if (lpsmSock == smWsockExtendServer)
		{
			lpServerExp = &sServerExp[2];
		}
	}

	if (lpServerExp)
	{
		lpServerExp->InputExp += lpTransCommand->WParam;
		lpServerExp->Counter++;
		lpServerExp->Total1 = lpTransCommand->SParam;
		lpServerExp->Total2 = lpTransCommand->EParam;


		int cnt = (lpServerExp->Total1 ^ lpServerExp->Total2) + 1600000;

		if (cnt < lpServerExp->InputExp)
		{
			SendSetHackUser(83);
		}

	}

	return TRUE;
}


int CreateConnectThread(DWORD dwIP);

int CreateDisconnectThread(SocketData* lpsmSock);


int FindNewOtherPlayer()
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (!chrOtherPlayer[cnt].Flag)
			return cnt;
	}

	return -1;
}


smCHAR* FindAutoPlayer(DWORD dwObjectSerial)
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial == dwObjectSerial)
		{
			return &chrOtherPlayer[cnt];
		}
	}

	return NULL;
}


smCHAR* FindChrPlayer(DWORD dwObjectSerial)
{
	int cnt;

	if (lpCurPlayer->dwObjectSerial == dwObjectSerial)
		return lpCurPlayer;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial == dwObjectSerial)
		{
			return &chrOtherPlayer[cnt];
		}
	}

	return NULL;
}


smCHAR* FindDeadPartyUser()
{
	int cnt;
	smCHAR* lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = 0;
	NearDist = 300 * 300;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].PartyFlag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER)
		{
			if (chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_DEAD)
			{

				x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}


smCHAR* FindNearMonster(smCHAR* lpCurChar)
{
	int cnt;
	smCHAR* lpChar;
	int dist, x, y, z;
	int	NearDist;

	lpChar = 0;
	NearDist = 300 * 300;

	if (!lpCurChar) return NULL;

	if (lpCurChar != lpCurPlayer)
	{
		x = (lpCurChar->pX - lpCurPlayer->pX) >> FLOATNS;
		y = (lpCurChar->pY - lpCurPlayer->pY) >> FLOATNS;
		z = (lpCurChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

		dist = x * x + z * z + y * y;
		if (dist < NearDist)
		{
			if (!lpCurChar->smCharInfo.ClassClan || lpCurChar->smCharInfo.ClassClan != lpCurPlayer->smCharInfo.ClassClan)
			{
				lpChar = lpCurPlayer;
				NearDist = dist;
			}
		}
	}

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY && lpCurChar != &chrOtherPlayer[cnt])
		{
			if (chrOtherPlayer[cnt].smCharInfo.Brood != smCHAR_MONSTER_USER && chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 &&
				(!chrOtherPlayer[cnt].smCharInfo.ClassClan || chrOtherPlayer[cnt].smCharInfo.ClassClan != lpCurChar->smCharInfo.ClassClan))
			{
				x = (lpCurChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpCurChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpCurChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + z * z + y * y;

				if (dist < NearDist)
				{
					lpChar = &chrOtherPlayer[cnt];
					NearDist = dist;
				}
			}
		}
	}

	return lpChar;
}


smCHAR* FindEmptyChar()
{
	int cnt;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (!chrOtherPlayer[cnt].Flag)
			return &chrOtherPlayer[cnt];
	}

	return NULL;
}


int AddChatBuff(char* szMsg, DWORD dwIP)
{
	int ChatCnt = ChatBuffCnt & CHATBUFF_MASK;
	ChatBuff[ChatCnt].dwIP = dwIP;
	strcpy_s(ChatBuff[ChatCnt].szMessage, szMsg);
	ChatBuffCnt++;
	ChatDispCnt = 70 * 10;
	if (ChatScrollPoint)
		ChatScrollPoint++;

	return ChatBuffCnt;
}


int AddChatBuff(char* szMsg)
{
	return AddChatBuff(szMsg, 0);
}

int	ChatBuffFilter(char* szMsg, DWORD dwIP)
{
	int cnt, len, cnt2;
	char	szBuff[256];
	char	szBuff2[64];

	if (dwIP >= 256) return TRUE;

	len = lstrlen(szMsg);

	for (cnt = 0; cnt < len; cnt++)
	{
		if (szMsg[cnt] == '>')
		{
			szBuff[cnt] = 0;
			break;
		}
		else
		{
			szBuff[cnt] = szMsg[cnt];
		}
	}

	if (cnt < len)
	{
		if (lstrcmpi(szBuff, "De") == 0)
		{
			cnt2 = 0;
			szBuff[0] = 0;
			for (cnt = cnt + 1; cnt < len; cnt++)
			{
				if (szMsg[cnt] == ':')
				{
					szBuff[cnt2] = 0;
					break;
				}
				else
				{
					if (szMsg[cnt] != ' ')
						szBuff[cnt2++] = szMsg[cnt];
				}
			}
			if (cnt < len && szBuff[0])
			{

				for (cnt2 = 0; cnt2 < 15; cnt2++)
				{
					if (InterfaceParty.chat_IDs(2, cnt2, szBuff2) == TRUE)
					{
						if (lstrcmpi(szBuff, szBuff2) == 0)
						{
							wsprintf(szBuff, "/** %s %s", szBuff2, mgRefuseWhisper);
							SendChatMessageToServer(szBuff);
							return FALSE;
						}
					}
				}

				InterfaceParty.latest_Insert(szBuff);
			}

			return TRUE;
		}

		if (lstrcmpi(szBuff, "Para") == 0)
		{
			cnt2 = 0;
			szBuff[0] = 0;
			for (cnt = cnt + 1; cnt < len; cnt++)
			{
				if (szMsg[cnt] == ':')
				{
					szBuff[cnt2] = 0;
					break;
				}
				else
				{
					if (szMsg[cnt] != ' ')
						szBuff[cnt2++] = szMsg[cnt];
				}
			}
			if (cnt < len && szBuff[0])
			{
				InterfaceParty.latest_Insert(szBuff);
			}
			return TRUE;
		}
	}





	return TRUE;
}


DWORD	ConvSysTimeToGameTime(DWORD dwTime)
{
	return dwTime / GAME_WORLDTIME_MIN;
}

//DispLoading

#define RECV_DATA_QUE_COUNT		64
#define RECV_DATA_QUE_MASK		63


class	rsTRANS_SERVER
{
	char TransBuff[smSOCKBUFF_SIZE];
	rsRECORD_DBASE* lpRecorder;
	void* RecvDataQue[RECV_DATA_QUE_COUNT];
	int	RecvDataQuePush;
	int	RecvDataQuePop;
	TRANS_PLAYPOS TransPlayPosLast;
	int	TransPlayPosCount;

public:
	SocketData* lpsmSock;

	rsTRANS_SERVER();

	int	Init(SocketData* lpsmsock);
	int SendChat(char* szMessage);
	int SendPlayData(smCHAR* lpChar);

	int RecvMessage(void* SockInfo);

	int RecvMessageQue();

};

rsTRANS_SERVER::rsTRANS_SERVER()
{
	ZeroMemory(TransBuff, sizeof(TransBuff));
	lpRecorder = nullptr;
	ZeroMemory(RecvDataQue, RECV_DATA_QUE_COUNT * 4);
	RecvDataQuePush = 0;
	RecvDataQuePop = 0;
	TransPlayPosCount = 0;
	lpsmSock = nullptr;
}


int rsTRANS_SERVER::RecvMessageQue()
{
	int cnt;

	if (RecvDataQuePop >= RecvDataQuePush) return TRUE;
	if (MessageLoading) return FALSE;


	EnterCriticalSection(&cSection);

	while (1)
	{
		if (RecvDataQuePop >= RecvDataQuePush) break;

		cnt = RecvDataQuePop & RECV_DATA_QUE_MASK;

		if (RecvDataQue[cnt])
		{
			RecvMessage(RecvDataQue[cnt]);

			delete RecvDataQue[cnt];
			RecvDataQue[cnt] = 0;
		}

		RecvDataQuePop++;
	}


	LeaveCriticalSection(&cSection);

	return TRUE;
}


DWORD	dwGetCharInfoTime = 0;


int rsTRANS_SERVER::RecvMessage(void* pData)
{
	return 1;
}

int rsTRANS_SERVER::Init(SocketData* lpsmsock)
{

	lpsmSock = lpsmsock;
	lpRecorder = 0;


	InitializeCriticalSection(&cServSection);

	RecvDataQuePush = 0;
	RecvDataQuePop = 0;

	ZeroMemory(RecvDataQue, RECV_DATA_QUE_COUNT * 4);

	return TRUE;
}



extern int szSpaceSorting(char* lpString);


int rsTRANS_SERVER::SendChat(char* szMessage)
{
	int len = 0;

	if (!szMessage || !szMessage[0]) return FALSE;

	if (szMessage[0] == '/' && (szMessage[1] == ';' || szMessage[1] == ':'))
	{

		szSpaceSorting(szMessage);
	}

	if (szMessage[0] == '`' && szMessage[1] == '/')
	{
		len = lstrlen(szMessage + 1) + 9;
		strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage + 1);
		((int*)TransBuff)[0] = len;
		((int*)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		if (smWsockDataServer) smWsockDataServer->Send(TransBuff, len, TRUE);
		return TRUE;
	}

	if (szMessage[0] == '~' && szMessage[1] == '/')
	{

		len = lstrlen(szMessage + 1) + 9;
		strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage + 1);
		((int*)TransBuff)[0] = len;
		((int*)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
		if (smWsockServer != smWsockUserServer && smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);
		if (smWsockServer != smWsockExtendServer && smWsockExtendServer) smWsockExtendServer->Send(TransBuff, len, TRUE);
		if (AreaServerMode)
		{
			if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send(TransBuff, len, TRUE);
			if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send(TransBuff, len, TRUE);
		}

	}
	else
	{

		if (szMessage[0] == '@')
		{


			wsprintf(TransBuff + 8, "%s> %s", PlayerName, szMessage + 1);
			len = lstrlen(TransBuff + 8) + 9;
			((int*)TransBuff)[0] = len;
			((int*)TransBuff)[1] = OpCode::OPCODE_PARTY_CHATMSG;

			if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
			AddChatBuff(TransBuff + 8, 4);
			return TRUE;
		}
		else
		{
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szMessage);
			len = lstrlen(szMessage) + 9;

			((int*)TransBuff)[0] = len;
			((int*)TransBuff)[1] = OpCode::OPCODE_CHATMESSAGE;
		}

		if (szMessage[0] == '/')
		{

			if (szMessage[1] == 'c' && szMessage[2] == 'o' && szMessage[3] == 'u' && szMessage[4] == 'p' &&
				szMessage[5] == 'l' && szMessage[6] == 'e')
			{
				if (smWsockUserServer && cInvenTory.SearchItemCode(sinSP1 | sin15)) smWsockUserServer->Send(TransBuff, len, TRUE);
				return TRUE;
			}

			if (szMessage[1] == '/')
			{
				if (smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);
			}
			else
			{
				if (smWsockServer) smWsockServer->Send(TransBuff, len, TRUE);
			}

			return TRUE;
		}

		if (AreaServerMode)
		{
			if (lpCurPlayer->OnStageField >= 0 && lpWSockServer_DispArea[lpCurPlayer->OnStageField])
			{
				lpWSockServer_DispArea[lpCurPlayer->OnStageField]->Send(TransBuff, len, TRUE);
			}
		}
		else
			if (smWsockUserServer) smWsockUserServer->Send(TransBuff, len, TRUE);

	}
	return TRUE;
}


int rsTRANS_SERVER::SendPlayData(smCHAR* lpChar)
{


	TRANS_PLAYPOS* lpTransPlayPos;
	int	dist, x, y, z;

	TransPlayPosCount++;

	if ((TransPlayPosCount & 1) == 0)
	{
		x = (TransPlayPosLast.rsPlayPos.x - lpChar->pX) >> FLOATNS;
		y = (TransPlayPosLast.rsPlayPos.y - lpChar->pY) >> FLOATNS;
		z = (TransPlayPosLast.rsPlayPos.z - lpChar->pZ) >> FLOATNS;
		dist = x * x + y * y + z * z;

		if (sinGetLife() > 0 && dist < (16 * 16 * 16))
		{

			return TRUE;
		}
	}

	lpTransPlayPos = (TRANS_PLAYPOS*)TransBuff;
	lpTransPlayPos->code = OpCode::OPCODE_POSITION;
	lpTransPlayPos->size = sizeof(TRANS_PLAYPOS);

	if (lpCurPlayer->OnStageField >= 0)
		lpTransPlayPos->rsPlayPos.Area = StageField[lpCurPlayer->OnStageField]->FieldCode;
	else
		lpTransPlayPos->rsPlayPos.Area = -1;

	lpTransPlayPos->rsPlayPos.x = lpChar->pX;
	lpTransPlayPos->rsPlayPos.y = lpChar->pY;
	lpTransPlayPos->rsPlayPos.z = lpChar->pZ;

	if (lpCurPlayer->MotionInfo && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
		lpTransPlayPos->Hp[0] = 0;
	else
		lpTransPlayPos->Hp[0] = sinGetLife();

	lpTransPlayPos->Hp[1] = lpChar->smCharInfo.Life[1];

	if (smWsockServer)
		smWsockServer->Send((char*)lpTransPlayPos, lpTransPlayPos->size, TRUE);

	if (smWsockExtendServer && smWsockExtendServer != smWsockServer)
		smWsockExtendServer->Send((char*)lpTransPlayPos, lpTransPlayPos->size, TRUE);


	int	MainArea, SubArea;

	if (AreaServerMode)
	{
		if (lpCurPlayer->OnStageField >= 0)
		{
			MainArea = (lpCurPlayer->OnStageField) & 1;
			SubArea = (lpCurPlayer->OnStageField + 1) & 1;

			if (lpWSockServer_DispArea[SubArea] && lpWSockServer_DispArea[MainArea] != lpWSockServer_DispArea[SubArea])
			{
				lpWSockServer_DispArea[SubArea]->Send((char*)lpTransPlayPos, lpTransPlayPos->size, TRUE);
			}
		}
	}


	return TRUE;
}



rsTRANS_SERVER	rsMainServer;









#define SAVE_CHAT_COMMAND_MAX		16
#define SAVE_CHAT_COMMAND_MASK		15

char szSaveChatCommands[SAVE_CHAT_COMMAND_MAX][256];
int ChatCommandSaveCnt = 0;
int ChatSaveRecallCnt = 0;


int SaveChatCommand(char* szMessage)
{
	int len, cnt;
	int mcnt;
	char szBuff[256];

	len = lstrlen(szMessage);
	strcpy_s(szBuff, szMessage);

	for (cnt = 0; cnt < len; cnt++)
	{
		if (szBuff[cnt] == ' ')
		{
			szBuff[cnt] = 0;
			break;
		}
	}
	lstrcat(szBuff, " ");


	for (cnt = 0; cnt < ChatCommandSaveCnt; cnt++)
	{
		if (cnt >= SAVE_CHAT_COMMAND_MAX) break;
		if (lstrcmp(szSaveChatCommands[cnt], szBuff) == 0)
			return TRUE;
	}

	mcnt = ChatCommandSaveCnt & SAVE_CHAT_COMMAND_MASK;
	strcpy_s(szSaveChatCommands[mcnt], szBuff);

	ChatCommandSaveCnt++;
	ChatSaveRecallCnt = ChatCommandSaveCnt;

	return TRUE;
}


int RecallSavedChatCommand(HWND hChatWnd, int Arrow)
{
	int mcnt;
	int len;

	if (ChatCommandSaveCnt <= 0) return FALSE;

	if (Arrow)
	{
		ChatSaveRecallCnt--;
		if (ChatSaveRecallCnt < 0)
		{
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
		}
	}
	else
	{
		ChatSaveRecallCnt++;
		if (ChatSaveRecallCnt >= ChatCommandSaveCnt)
		{
			ChatSaveRecallCnt = ChatCommandSaveCnt - 1;
			SetWindowText(hChatWnd, "");
			return TRUE;
		}
	}

	mcnt = ChatSaveRecallCnt & SAVE_CHAT_COMMAND_MASK;
	SetWindowText(hChatWnd, szSaveChatCommands[mcnt]);

	len = lstrlen(szSaveChatCommands[mcnt]);
	SendMessage(hChatWnd, EM_SETSEL, len, len);

	return TRUE;
}


int rsCompString(char* src1, char* src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2) len = len1;
	else len = len2;

	if (!len) return NULL;

	for (cnt = 0; cnt < len1; cnt++)
	{
		if (src1[cnt] == 0) break;
		if (src1[cnt] != src2[cnt]) return NULL;
	}

	return cnt;
}



char szLastChatMessage[256];
DWORD	dwLastChatTime;
DWORD	dwContiueChatCount = 0;
#include "CurseFilter.h"		

char* rsGetWord(char* q, char* p);

extern int WaveCameraMode;


int SendChatMessageToServer(char* szChatMessage)
{
	return 0;
}



int ChatScrollPoint = 0;


int DisplayChatMessage(HDC hdc, int x, int y, int MaxLine)
{
	int cnt;
	int chatCnt;
	char* lpString;
	int start, end;

	if (ChatDispCnt == 0) return FALSE;

	if (ChatScrollPoint > CHATBUFF_MASK)
		ChatScrollPoint = CHATBUFF_MASK;
	if (ChatScrollPoint < 0)
		ChatScrollPoint = 0;

	start = ChatBuffCnt - MaxLine - ChatScrollPoint;
	end = ChatBuffCnt - ChatScrollPoint;

	for (cnt = start; cnt < end; cnt++)
	{
		if (cnt >= 0)
		{
			chatCnt = cnt & CHATBUFF_MASK;
			lpString = ChatBuff[chatCnt].szMessage;

			SetTextColor(hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, x + 1, y + 1, lpString, lstrlen(lpString));
			if (ChatBuff[chatCnt].dwIP == dwMyIP)
				SetTextColor(hdc, RGB(255, 128, 96));
			else
			{
				SetTextColor(hdc, RGB(255, 255, 128));

				switch (ChatBuff[chatCnt].dwIP)
				{
				case 1:
					SetTextColor(hdc, RGB(255, 128, 96));
					break;
				case 2:
					SetTextColor(hdc, RGB(96, 256, 255));
					break;
				}
			}
			dsTextLineOut(hdc, x, y, lpString, lstrlen(lpString));
		}
		y += 16;
	}

	return TRUE;
}










int GetNextLineCount(char* szString, int LineMax)
{
	int cnt;
	int len;
	char* lp;

	len = lstrlen(szString);
	if (len <= LineMax) return 0;

	lp = szString;

	cnt = 0;

	while (1)
	{

		if (CheckCode_2Byte(lp) == 2)
		{
			cnt += 2;
			lp += 2;
		}
		else
		{
			cnt++;
			lp++;
		}

		if (cnt > (LineMax - 2)) break;
	}


	return cnt;
}
//cores do chat
int SetIpColor(HDC hdc, DWORD dwIP)
{

	if (dwIP == dwMyIP)
	{
		SetTextColor(hdc, RGB(255, 128, 96));
		return TRUE;
	}

	switch (dwIP)
	{
	case 0:
		SetTextColor(hdc, RGB(255, 128, 96));
		break;
	case 1:

		SetTextColor(hdc, RGB(150, 190, 255));
		break;
	case 2:

		SetTextColor(hdc, RGB(255, 255, 255));
		break;
	case 3:
		SetTextColor(hdc, RGB(230, 160, 255));
		break;
	case 4:
		SetTextColor(hdc, RGB(200, 255, 0));
		break;
	case 5:
		SetTextColor(hdc, RGB(255, 255, 80));
		break;
	case 6:
		SetTextColor(hdc, RGB(200, 255, 255));
		break;

	case 9:
		SetTextColor(hdc, RGB(200, 128, 128));
		break;

	case 10:
		SetTextColor(hdc, RGB(255, 180, 0));
		break;
		//Comando Reload
	case 11:
		SetTextColor(hdc, RGB(238, 173, 45));
		break;
		//Quest Diaria
	case 12:
		SetTextColor(hdc, RGB(255, 176, 127));
		break;
		//Arena de Batalha
	case 13:
		SetTextColor(hdc, RGB(255, 47, 41));
		break;
		//Logado Premiado
	case 14:
		SetTextColor(hdc, RGB(117, 254, 255));
		break;
		// Nuevo colores para chat
	case 15:
		SetTextColor(hdc, RGB(180, 51, 255));
		break;
		// Nuevo colores para chat
	case 16:
		SetTextColor(hdc, RGB(0, 255, 0));
		break;
	default:
		SetTextColor(hdc, RGB(255, 255, 192));
		break;
	}


	return TRUE;
}

static int	DisplayChatFilter = -1;
int	DispChatMsgHeight = 6;
int	DispChatMode = 0;


int	SetChatMsgFilter(int mode)
{

	DisplayChatFilter = -1;
	ChatScrollPoint = 0;

	switch (mode)
	{
	case 0:
		DisplayChatFilter = -1;
		break;

	case 1:
		DisplayChatFilter = 5;
		break;

	case 2:
		DisplayChatFilter = 4;
		break;

	case 3:
		DisplayChatFilter = 6;
		break;

	case 4:
		DisplayChatFilter = 1;
		break;
	}

	DispChatMode = mode;

	return TRUE;
}

int ChatBuffSort()
{
	int cnt, cnt2;
	int mCnt, nCnt;
	int	Col;

	if (ChatBuffCnt <= ChatBuffCompCnt) return FALSE;

	for (cnt = ChatBuffCompCnt; cnt < ChatBuffCnt; cnt++)
	{
		mCnt = cnt & CHATBUFF_MASK;
		Col = 0;
		switch (ChatBuff[mCnt].dwIP)
		{
		case 5:
			Col = 1;
			break;
		case 4:
			Col = 2;
			break;

		case 6:
			Col = 3;
			break;
		case 1:
			Col = 4;
			break;

		case 9:
			Col = 5;
			break;
		}
		nCnt = ChatBuffCnt2[Col] & CHATBUFF_MASK;
		memcpy(&ChatBuff2[Col][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
		ChatBuffCnt2[Col]++;

		if (Col > 0 && Col < 5)
		{
			nCnt = ChatBuffCnt2[0] & CHATBUFF_MASK;
			memcpy(&ChatBuff2[0][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
			ChatBuffCnt2[0]++;
		}

		if (Col == 0 && ChatBuff[mCnt].dwIP < 10)
		{
			for (cnt2 = 1; cnt2 < 5; cnt2++)
			{
				nCnt = ChatBuffCnt2[cnt2] & CHATBUFF_MASK;
				memcpy(&ChatBuff2[cnt2][nCnt], &ChatBuff[mCnt], sizeof(CHATBUFF));
				ChatBuffCnt2[cnt2]++;
			}
		}
	}

	ChatBuffCompCnt = ChatBuffCnt;

	return TRUE;
}

int DisplayChatMessage3(HDC hdc, int x, int y, int StrMax, int LineMax, int Mode)
{
	int result;
	int ModeBackup = DispChatMode;
	int	ScrollBackup = ChatScrollPoint;

	DispChatMode = Mode;
	if (LineMax <= 6)
		ChatScrollPoint = 0;

	result = DisplayChatMessage2(hdc, x, y, StrMax, LineMax);

	DispChatMode = ModeBackup;
	ChatScrollPoint = ScrollBackup;
	return result;
}


int DisplayChatMessage2(HDC hdc, int x, int y, int StrMax, int LineMax)
{
	int cnt = 0;
	int chatCnt = 0;
	char* lpString = nullptr;
	int LineCnt = 0;
	int CutPos = 0;
	int len = 0;
	int start = 0;
	int end = 0;
	int fl_Count = 0;

	DWORD shColor = RGB(74, 74, 74);

	ChatBuffSort();

	LineCnt = 0;

	if (ChatScrollPoint > (CHATBUFF_MAX - 32))
		ChatScrollPoint = (CHATBUFF_MAX - 32);
	if (ChatScrollPoint < 0)
		ChatScrollPoint = 0;

	fl_Count = DispChatMode;
	if (fl_Count < 0) fl_Count = 0;

	start = ChatBuffCnt2[fl_Count] - 1 - ChatScrollPoint;
	end = ChatBuffCnt2[fl_Count] - 32 - ChatScrollPoint;

	DispChatMsgHeight = 0;

	for (cnt = start; cnt >= end; cnt--)
	{
		if (cnt >= 0)
		{
			chatCnt = cnt & CHATBUFF_MASK;

			lpString = ChatBuff2[fl_Count][chatCnt].szMessage;

			DispChatMsgHeight++;

			len = lstrlen(lpString);
			if (len > StrMax)
			{

				CutPos = GetNextLineCount(lpString, StrMax);

				SetTextColor(hdc, shColor);
				dsTextLineOut(hdc, x - 1, y - 1, lpString + CutPos, len - CutPos);
				SetIpColor(hdc, ChatBuff2[fl_Count][chatCnt].dwIP);
				dsTextLineOut(hdc, x, y, lpString + CutPos, len - CutPos);

				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;

				SetTextColor(hdc, shColor);
				dsTextLineOut(hdc, x - 1, y - 1, lpString, CutPos);
				SetIpColor(hdc, ChatBuff2[fl_Count][chatCnt].dwIP);


				char semi[MAX_PATH] = { 0 };
				char presemi[MAX_PATH] = { 0 };
				char backsemi[MAX_PATH] = { 0 };

				bool bsemi = 0;

				strcpy_s(semi, sizeof(semi), lpString);

				int k = 0, prelen = 0, lenth = 0;

				lenth = strlen(semi);

				for (int i = 0; i < lenth; i++)
				{
					backsemi[k] = semi[i];

					k++;

					if ((bsemi == 0) && (semi[i] == ':'))
					{
						strcpy_s(presemi, sizeof(presemi), backsemi);
						ZeroMemory(backsemi, MAX_PATH);
						bsemi++;
						k = 0;
					}
				}

				if (bsemi)
				{
					SIZE size;

					prelen = strlen(presemi);
					SetTextColor(hdc, RGB(100, 255, 50));
					dsTextLineOut(hdc, x, y, presemi, prelen);
					GetTextExtentPoint(hdc, presemi, prelen, &size);

					int j = 0;
					j = x + size.cx;
					SetIpColor(hdc, ChatBuff2[fl_Count][chatCnt].dwIP);
					dsTextLineOut(hdc, j, y, backsemi, CutPos - prelen);
				}
				else dsTextLineOut(hdc, x, y, lpString, CutPos);

				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;

			}
			else
			{

				SetTextColor(hdc, shColor);
				dsTextLineOut(hdc, x - 1, y - 1, lpString, len);
				SetIpColor(hdc, ChatBuff2[fl_Count][chatCnt].dwIP);

				char semi[MAX_PATH] = { 0 };
				char presemi[MAX_PATH] = { 0 };
				char backsemi[MAX_PATH] = { 0 };

				bool bsemi = 0;
				strcpy_s(semi, sizeof(semi), lpString);

				int k = 0, prelen = 0, lenth = 0;
				lenth = strlen(semi);

				for (int i = 0; i < lenth; i++)
				{
					backsemi[k] = semi[i];
					k++;
					if ((bsemi == 0) && (semi[i] == ':'))
					{
						strcpy_s(presemi, sizeof(presemi), backsemi);
						ZeroMemory(backsemi, MAX_PATH);
						bsemi++;
						k = 0;
					}
				}

				if (bsemi)
				{
					SIZE size;

					prelen = strlen(presemi);
					SetTextColor(hdc, RGB(100, 255, 50));
					dsTextLineOut(hdc, x, y, presemi, prelen);
					GetTextExtentPoint(hdc, presemi, prelen, &size);

					int j = x + size.cx;
					SetIpColor(hdc, ChatBuff2[fl_Count][chatCnt].dwIP);
					dsTextLineOut(hdc, j, y, backsemi, strlen(backsemi));
				}
				else dsTextLineOut(hdc, x, y, lpString, len);


				y -= 12;
				LineCnt++;
				if (LineCnt >= LineMax) break;
			}

		}
	}

	return TRUE;
}


int ConnectPlayer(SocketData* lpsmSock)
{
	if (ServerMode)
		return Serv_ConnectPlayer(lpsmSock);

	return TRUE;
}


int DisconnectPlayer(SocketData* lpsmSock)
{
	if (ServerMode)
		return Serv_DisconnectPlayer(lpsmSock);

	return TRUE;
}


int Ts_LastSendCounter;
DWORD	dwLastSendPosiTime = 0;
DWORD	dwLastSendPlayTime = 0;


int SendPlayDataToServer()
{
	if (smWsockServer != smWsockUserServer || AreaServerMode)
	{
		return rsMainServer.SendPlayData(lpCurPlayer);
	}

	return TRUE;
}



int ConnectOtherPlayer(DWORD dwIP)
{
	//SocketData* lpsmSock;
	//int OthPlayerCnt;

	//OthPlayerCnt = FindNewOtherPlayer();
	//if (OthPlayerCnt >= 0)
	//{
	//	lpsmSock = smConnectSock2(ConvStrIP(dwIP), TCP_GAMEPORT);
	//	if (lpsmSock)
	//	{
	//		ConnectPlayer(lpsmSock);
	//		return TRUE;
	//	}
	//}
	return FALSE;
}

DWORD WINAPI ConnectPlayThreadProc(void* pInfo)
{

	//ConnectOtherPlayer((DWORD)pInfo);

	//ExitThread(TRUE);
	return TRUE;
}

DWORD WINAPI DisconnectPlayThreadProc(void* pInfo)
{

	/*((SocketData*)pInfo)->CloseSocket();

	ExitThread(TRUE);*/
	return TRUE;
}




int CreateConnectThread(DWORD dwIP)
{
	DWORD dwMsgId;
	CreateThread(NULL, 0, ConnectPlayThreadProc, (void*)dwIP, 0, &dwMsgId);

	return TRUE;
}


int CreateDisconnectThread(SocketData* lpsmSock)
{
	DWORD dwMsgId;
	CreateThread(NULL, 0, DisconnectPlayThreadProc, (void*)lpsmSock, 0, &dwMsgId);

	return TRUE;
}



int DisconnectFarPlayer()
{
	return TRUE;
}

DWORD	dwExtendServ_RecvTime = 0;
DWORD	dwUserServ_RecvTime = 0;
DWORD	dwMainServ_RecvTime = 0;
DWORD	dwDataServ_RecvTime = 0;


int RecvPlayData(void* pData)
{


	return TRUE;
}


int PlayRecvMessageQue()
{
	return rsMainServer.RecvMessageQue();
}


int LastSendCnt;

#define	NET_SENDING_WAIT_TIME		400
#define	NET_SENDING_WAIT_TIME2		1000

int NetStandCnt = 0;
extern int GameMode;

DWORD	NetScoopTime = 2000;


int NetWorkPlay()
{
	return NULL;
}



int ThrowPutItem(sITEM* lpItem, int x, int y, int z)
{


	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (AdminCharDisable || WarningHack || !smWsockDataServer || !smWsockServer)
		return FALSE;


	if (!SendSaveThrowItem2(&lpItem->sItemInfo))
		return FALSE;

	TransThrowItem.code = OpCode::OPCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.Item, &lpItem->sItemInfo, sizeof(sITEMINFO));

	return TRUE;
}

int ThrowPutItem2(sITEMINFO* lpItem, int x, int y, int z)
{


	if ((dwRecvServerTime + 4000) < dwPlayTime || QuitSave || TransThrowItem.code)
		return FALSE;

	if (AdminCharDisable || WarningHack || !smWsockDataServer || !smWsockServer)
		return FALSE;


	if (!SendSaveThrowItem2(lpItem))
		return FALSE;

	TransThrowItem.code = OpCode::OPCODE_THROWITEM;
	TransThrowItem.size = sizeof(TRANS_ITEMINFO);
	TransThrowItem.x = x;
	TransThrowItem.y = y;
	TransThrowItem.z = z;

	memcpy(&TransThrowItem.Item, lpItem, sizeof(sITEMINFO));




	return TRUE;
}






int	ThrowPotionCount = 0;


int ThrowItemToServer(smTRANS_COMMAND_EX* lpTransCommand)
{
	smTRANS_COMMAND	smTransCommand;
	SocketData* lpsmSock;
	DWORD	dwItemCodeMask;
	int		cnt;

	if (TransThrowItem.code &&
		TransThrowItem.Item.CODE == (DWORD)lpTransCommand->WParam &&
		TransThrowItem.Item.ItemHeader.Head == (DWORD)lpTransCommand->LParam &&
		TransThrowItem.Item.ItemHeader.dwChkSum == (DWORD)lpTransCommand->SParam)
	{

		if ((TransThrowItem.Item.CODE & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1))
		{
			cInvenTory.DeleteInvenItemToServer(TransThrowItem.Item.CODE, TransThrowItem.Item.ItemHeader.Head, TransThrowItem.Item.ItemHeader.dwChkSum);


			if (FindInvenItem(TransThrowItem.Item.CODE,
				TransThrowItem.Item.ItemHeader.Head,
				TransThrowItem.Item.ItemHeader.dwChkSum) != 0)
			{

				SendInvenItemError(0, TransThrowItem.Item.CODE,
					TransThrowItem.Item.ItemHeader.Head,
					TransThrowItem.Item.ItemHeader.dwChkSum);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}
		else
		{
			if ((dwPlayTime - dwLastRecordTime) > 4000 && TransThrowItem.Item.PotionCount >= 10)
			{

				SaveGameData();
				ThrowPotionCount = 0;
			}
			else
			{
				ThrowPotionCount += TransThrowItem.Item.PotionCount;
				if (ThrowPotionCount >= 15)
				{
					ThrowPotionCount = 0;
					SaveGameData();
				}
			}
		}

		if ((TransThrowItem.Item.CODE & sinITEM_MASK2) == sinBC1)
		{

			if (TransThrowItem.Item.PotionCount == 100)
				TransThrowItem.Item.PotionCount = 200;

			if (TransThrowItem.Item.CODE == (sinBC1 | sin04) && TransThrowItem.Item.PotionCount == 200)
			{

				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = OpCode::OPCODE_PARTY_POTION;
				smTransCommand.WParam = 3000;
				smTransCommand.LParam = 3000;
				smTransCommand.SParam = 3000;
				smTransCommand.EParam = lpCurPlayer->dwObjectSerial;

				if (smWsockUserServer)
					smWsockUserServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

				SetPartyPosion(&smTransCommand);

				TransThrowItem.code = 0;
				return TRUE;
			}
		}

		if (!TransThrowItem.Item.SpecialItemFlag[0])
		{
			TransThrowItem.dwSeCode[0] = lpTransCommand->WxParam;
			TransThrowItem.dwSeCode[1] = lpTransCommand->LxParam;
			TransThrowItem.dwSeCode[2] = lpTransCommand->SxParam;
			TransThrowItem.dwSeCode[3] = lpTransCommand->ExParam;

			dwItemCodeMask = TransThrowItem.Item.CODE & sinITEM_MASK2;


			if (((dwItemCodeMask == sinGP1 || dwItemCodeMask == sinCH1 || dwItemCodeMask == sinFO1 || dwItemCodeMask == sinGP2) && TransThrowItem.Item.PotionCount == 100) ||
				(TransThrowItem.Item.CODE == (sinGG1 | sin01) && TransThrowItem.Item.ItemKindCode == OpCode::OPCODE_COLLECTMONEY) ||
				(dwItemCodeMask == sinBC1 && TransThrowItem.Item.PotionCount == 200) ||
				(dwItemCodeMask == sinBI1 && TransThrowItem.Item.PotionCount == 300) ||
				(dwItemCodeMask == sinBI2 && TransThrowItem.Item.PotionCount == 300) ||
				(dwItemCodeMask == sinBI3 && TransThrowItem.Item.PotionCount == 300) ||
				(dwItemCodeMask == sinBI4 && TransThrowItem.Item.PotionCount == 300))
			{
				lpsmSock = GetAreaServerSock();
				if (lpsmSock)
					lpsmSock->Send((char*)&TransThrowItem, TransThrowItem.size, TRUE);
				else
					smWsockServer->Send((char*)&TransThrowItem, TransThrowItem.size, TRUE);

				if (dwItemCodeMask == sinFO1)
				{

					cnt = (TransThrowItem.Item.CODE & sinITEM_MASK3) >> 8;
					cnt--;
					if (cnt >= 0 && cnt < 12)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + ForceOrbUseTime[cnt] * 1000;
						AssaParticle_ShelltomWeapon(lpCurPlayer, ForceOrbUseTime[cnt] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}

					else if (cnt >= 20 && cnt < 32)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + MagicForceOrbUseTime[cnt - 20] * 1000;

						AssaParticle_ShelltomWeapon(lpCurPlayer, MagicForceOrbUseTime[cnt - 20] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}
					else if (cnt >= 34 && cnt < 37)
					{
						lpCurPlayer->dwForceOrbCode = TransThrowItem.Item.CODE;
						lpCurPlayer->dwForceOrbTime = dwPlayTime + BillingMagicForceOrbUseTime[cnt - 34] * 1000;

						AssaParticle_ShelltomWeapon(lpCurPlayer, BillingMagicForceOrbUseTime[cnt - 34] * 70, cnt);


						SendCommandUser(smCOMMNAD_USER_FORCEORB, 0, 0, 0);
						StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
						SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
					}
				}


				if (dwItemCodeMask == sinBI1 || dwItemCodeMask == sinBI2 || dwItemCodeMask == sinBI4)
				{
					//Olho M�gico (3h)
					if (TransThrowItem.Item.CODE == (sinBI1 | sin12))
					{
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_24H);
					}
					//Po�ao EXP (12h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin13))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_24H);
					}
					//Olho M�gico (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin14))
					{
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_7D);
					}
					//Po�ao EXP (24H)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin15))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_7D);
					}
					//Presa do vampiro
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin19))
					{
						chaPremiumitem.SetVampiricCuspidTime(PRIME_ITEM_TIME_24H);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin20))
					{
						chaPremiumitem.SetVampiricCuspidTime(PRIME_ITEM_TIME_7D);
					}
					//Drena Alma
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin21))
					{
						chaPremiumitem.SetManaReducePotionValue(PRIME_ITEM_TIME_24H);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin22))
					{
						chaPremiumitem.SetManaReducePotionValue(PRIME_ITEM_TIME_7D);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin23))
					{
						cnt = (rand() % 8192) * 2;
						DWORD	dwTable = GetTableNum(cnt);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime, (dwTable >> 24) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 500, (dwTable >> 16) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 8) & 0xFF, 0, 0, lpCurPlayer);
						AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, dwTable & 0xFF, 0, 0, lpCurPlayer);
						lpCurPlayer->dwNextMotionCode = CHRMOTION_STATE_YAHOO;
						SendCommandUser(smCOMMNAD_USER_FIREFLOWER, cnt, 0, 0);
					}
					//Exp 50% 6H
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin24))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_12H);
					}
					//Exp 50% 12H
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin25))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_24H);
					}
					//Exp 50% 24H
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin79))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_7D);
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin26))
					{
						chaPremiumitem.SetMightOfAwellTime(PRIME_ITEM_TIME_24H);
						chaPremiumitem.SetMightOfAwellWeight(300);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin27))
					{
						chaPremiumitem.SetMightOfAwellTime(PRIME_ITEM_TIME_7D);
						chaPremiumitem.SetMightOfAwellWeight(300);
					}
					//Po��o Redutora de Mana (24h)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin28))
					{
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_24H);
						chaPremiumitem.SetManaReducePotionValue(30);
					}
					//Po��o Redutora de Mana (7d)
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin29))
					{
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_7D);
						chaPremiumitem.SetManaReducePotionValue(30);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin30))
					{
						chaPremiumitem.SetMightOfAwellTime(PRIME_ITEM_TIME_24H);
						chaPremiumitem.SetMightOfAwellWeight(500);
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin31))
					{
						chaPremiumitem.SetMightOfAwellTime(PRIME_ITEM_TIME_7D);
						chaPremiumitem.SetMightOfAwellWeight(500);
					}
					//
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin32))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_12H);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					//F�nix
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin33))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_24H);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					//F�nix 
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin34))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_7D);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					//Exp 100% 3Horas
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin43))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_3H);
					}
					//Exp 100% 
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin44))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_12H);
					}
					//Exp 100%
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin50))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_24H);
					}
					//Exp 100% 24Horas
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin80))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_7D);
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin51))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_PACKAGE4);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin52))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_12H);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin53))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_12H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin54))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_12H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin55))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_12H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin69))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin70))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin71))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin72))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_24H);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin80))
					{
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE5);
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin77))
					{
						chaPremiumitem.SetPhenixPetTime(PRIME_ITEM_TIME_PACKAGE5);
						cPCBANGPet.PetKind = TRUE;
						cPCBANGPet.ShowPet();
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin65))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin66))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin67))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin68))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin73))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);


						cHelpPet.PetKind = HoLowLevelPet::Type::Terry + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin74))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Nepsys + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin75))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Io + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin76))
					{
						chaPremiumitem.SetHelpPetTimeTime(PRIME_ITEM_TIME_7D);

						cHelpPet.PetKind = HoLowLevelPet::Type::Mute + 1;
						cHelpPet.PetShow = 1;
						cHelpPet.ShowPet();
					}


					else if (TransThrowItem.Item.CODE == (sinBI1 | sin78))
					{
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_7D);
					}

					else if (TransThrowItem.Item.CODE == (sinBI1 | sin83))
					{
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE5);
						chaPremiumitem.SetManaReducePotionValue(30);
					}
					//Redutora STM
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin91))
					{
						chaPremiumitem.SetStaminaReducePotionTime(PRIME_ITEM_TIME_24H);
						chaPremiumitem.SetStaminaReducePotionValue(30);
					}
					//Redutora STM 
					else if (TransThrowItem.Item.CODE == (sinBI1 | sin92))
					{
						chaPremiumitem.SetStaminaReducePotionTime(PRIME_ITEM_TIME_7D);
						chaPremiumitem.SetStaminaReducePotionValue(30);
					}




					if (TransThrowItem.Item.CODE == ((sinBI2 | sin01)))
					{
						int test = 1;
					}

					switch (TransThrowItem.Item.CODE)
					{
					case (sinBI2 | sin01):
					case (sinBI2 | sin05):
					case (sinBI2 | sin09):
					case (sinBI2 | sin23):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						break;
					case (sinBI2 | sin02):
					case (sinBI2 | sin06):
					case (sinBI2 | sin10):
					case (sinBI2 | sin24):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						break;
					case (sinBI2 | sin03):
					case (sinBI2 | sin07):
					case (sinBI2 | sin11):
					case (sinBI2 | sin25):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						break;
					case (sinBI2 | sin04):
					case (sinBI2 | sin08):
					case (sinBI2 | sin12):
						chaPremiumitem.SetThirdEyesTime(PRIME_ITEM_TIME_PACKAGE4);
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE4);
						break;
					case (sinBI2 | sin26):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin27):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin28):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(10);
						break;
					case (sinBI2 | sin29):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin30):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin31):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(20);
						break;
					case (sinBI2 | sin32):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin33):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin34):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(30);
						break;
					case (sinBI2 | sin35):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE1);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					case (sinBI2 | sin36):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE2);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					case (sinBI2 | sin37):
						chaPremiumitem.SetExpUpPotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionTime(PRIME_ITEM_TIME_PACKAGE3);
						chaPremiumitem.SetManaReducePotionValue(40);
						break;
					case (sinBI4 | sin01):
						chaPremiumitem.SetBigHeadTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin10):
						chaPremiumitem.SetAwellPowerTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin20):
						chaPremiumitem.SetMigalPowerTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin30):
						chaPremiumitem.SetHPBoosterTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin40):
						chaPremiumitem.SetMPBoosterTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin50):
						chaPremiumitem.SetSPBoosterTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin60):
						chaPremiumitem.SetRecoverSPTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin70):
						chaPremiumitem.SetBDivinaTime(PRIME_ITEM_TIME_VAMPCUSPID);
						break;
					case (sinBI4 | sin80):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(1);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin81):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(2);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin82):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(3);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin83):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(4);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin84):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(5);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin85):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(6);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin86):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(7);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin87):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(8);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin88):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(9);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin89):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(10);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin90):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(11);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin91):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(12);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin92):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(13);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin93):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(14);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin94):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(15);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin95):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(16);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin96):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(17);
						cInvenTory.SetItemToChar();
						break;
					case (sinBI4 | sin97):
						chaPremiumitem.SetForceTime(PRIME_ITEM_TIME_VAMPCUSPID);
						chaPremiumitem.SetForceType(18);
						cInvenTory.SetItemToChar();
						break;
					}
				}

			}
			else
			{
				smWsockServer->Send((char*)&TransThrowItem, TransThrowItem.size, TRUE);
			}
		}

	}

	TransThrowItem.code = 0;
	return TRUE;
}



int SendAddStartPoint(int x, int z)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_ADD_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;

	SocketData* lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}
	return NULL;
}


int SendDeleteStartPoint(int x, int z)
{
	smTRANS_COMMAND TransCommand;

	TransCommand.code = OpCode::OPCODE_DEL_STARTPOSI;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.LParam = x;
	TransCommand.WParam = z;
	TransCommand.SParam = TRUE;

	scITEM* lpItem = FindScItem(x, z);

	if (lpItem)
	{
		SocketData* lpsmSock = GetServerSock(lpItem->ServerCode);
		lpItem->Close();

		if (lpsmSock)
			return lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}

	return NULL;
}





int SendAdd_Npc(smCHAR* lpCharSample, int state)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;

	smTransPlayerInfo.code = OpCode::OPCODE_ADD_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.smCharInfo, &lpCharSample->smCharInfo, sizeof(smCHAR_INFO));
	smTransPlayerInfo.smCharInfo.State = 0;


	strcpy_s(smTransPlayerInfo.smCharInfo.szModelName2, NpcSelectedName);

	smTransPlayerInfo.smCharInfo.Life[0] = 100;
	smTransPlayerInfo.smCharInfo.Mana[0] = 100;
	smTransPlayerInfo.smCharInfo.Life[1] = 100;

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.state = state;

	SocketData* lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&smTransPlayerInfo, smTransPlayerInfo.size, TRUE);
	}

	return NULL;
}


int SendDelete_Npc(smCHAR* lpCharSample)
{
	smTRNAS_PLAYERINFO	smTransPlayerInfo;
	SocketData* lpsmSock;

	smTransPlayerInfo.code = OpCode::OPCODE_DEL_NPC;
	smTransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	memcpy(&smTransPlayerInfo.smCharInfo, &lpCharSample->smCharInfo, sizeof(smCHAR_INFO));

	smTransPlayerInfo.x = lpCharSample->pX;
	smTransPlayerInfo.y = lpCharSample->pY;
	smTransPlayerInfo.z = lpCharSample->pZ;

	smTransPlayerInfo.ax = lpCharSample->Angle.x;
	smTransPlayerInfo.ay = lpCharSample->Angle.y;
	smTransPlayerInfo.az = lpCharSample->Angle.z;

	smTransPlayerInfo.dwObjectSerial = lpCharSample->dwObjectSerial;

	lpsmSock = GetServerSock(lpCharSample->ServerCode);
	lpCharSample->Close();

	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&smTransPlayerInfo, smTransPlayerInfo.size, TRUE);
	}
	return NULL;
}


int SendGetRecordData(char* szName)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;

	if (smWsockDataServer)
	{
		smTransCharCommand.code = OpCode::OPCODE_GETRECORDDATA;
		smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);

		smTransCharCommand.WParam = dwExeCheckSum;
		smTransCharCommand.LParam = FALSE;
		smTransCharCommand.SParam = Client_Version;

		strcpy_s(smTransCharCommand.szName, szName);

		dwLoadingTime = GetCurrentTime();

		return smWsockDataServer->Send((char*)&smTransCharCommand, smTransCharCommand.size, TRUE);
	}

	return FALSE;
}

char* szCmdOpenMonster[10] = {
	"ȩ���",
	"ȩ���",
	"ȩ���",
	"ŷȣ��",
	"Ÿ��ź",
	0,0,0,0,0
};



int SendOpenMonster(int State)
{
	smTRANS_CHAR_COMMAND smTransCharCommand;
	char* szMonName = "";

	smTransCharCommand.code = OpCode::OPCODE_OPENMONSTER;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	smTransCharCommand.WParam = State;
	smTransCharCommand.LParam = 0;
	smTransCharCommand.SParam = 0;

	if (State >= 0)
	{
		szMonName = smConfig.szCmdOpenMonster[State];
		if (!szMonName[0]) szMonName = szCmdOpenMonster[State];
	}

	if (State >= 0 && szMonName)
		strcpy_s(smTransCharCommand.szName, szMonName);
	else
		smTransCharCommand.szName[0];


	SocketData* lpsmSock;
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&smTransCharCommand, smTransCharCommand.size, TRUE);
	}

	return FALSE;

}


int	CodeXorCharInfo()
{
	lpCurPlayer->smCharInfo.Exp ^= CodeXorExp;
	lpCurPlayer->smCharInfo.Exp_High ^= CodeXorExp_High;
	lpCurPlayer->smCharInfo.Life[0] ^= CodeXorLife;
	return TRUE;
}


int SaveCheckSkill()
{

	ReformSkillInfo();

	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		if (sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
		{
			if (cSkill.CheckSkillPointForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
			if (cSkill.CheckSkillMasteryForm(&sinSkill.UseSkill[j]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}


int ReformSkillInfo()
{
	for (int j = 1; j < SIN_MAX_USE_SKILL; j++)
	{
		cSkill.ReformSkillMasteryForm(&sinSkill.UseSkill[j]);
		cSkill.ReformSkillPointForm(&sinSkill.UseSkill[j]);
	}
	return TRUE;
}


int	SaveGameData()
{
	if (smWsockDataServer && !rsRecorder.dwRecordTime &&
		lpCurPlayer->smCharInfo.JOB_CODE && !AdminCharDisable && !cTrade.OpenFlag && !cWareHouse.OpenFlag && !QuitSave)
	{



		if (!WarningHack && CheckCharForm() != FALSE && SaveCheckSkill() == TRUE)
		{
			CodeXorCharInfo();
			ReformCharForm();

			rsRecorder.MakeRecordData(&lpCurPlayer->smCharInfo, cInvenTory.InvenItem, cInvenTory.InvenItemTemp, &MouseItem);
			rsRecorder.SendRecordDataToServer(smWsockDataServer);
			rsRecorder.dwRecordTime = dwPlayTime;

			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			{
				AddChatBuff("Salvando o jogo");
			}

			CodeXorCharInfo();
			ReformCharForm();
			CheckPlaySkill();
			return TRUE;
		}
	}
	return FALSE;
}


int GetSaveResult()
{
	if (rsRecorder.dwRecordTime) return FALSE;

	return TRUE;
}



smTRANS_COMMAND	smMessageCommandBuff;


int	TransUserCommand(DWORD dwCode, char* szID, char* szName)
{
	smTRANS_CHAR_COMMAND2	TransCharCommand2;

	TransCharCommand2.code = dwCode;
	TransCharCommand2.size = sizeof(smTRANS_CHAR_COMMAND2);

	if (szID)
	{
		strcpy_s(TransCharCommand2.szId, szID);
	}

	if (szName)
	{
		strcpy_s(TransCharCommand2.szName, szName);
	}

	return smWsockDataServer->Send((char*)&TransCharCommand2, TransCharCommand2.size, TRUE);
}




int	Send_GetCharInfo(DWORD dwObjectSerial, int ServerCode)
{
	smTRANS_COMMAND	TransCommand;
	SocketData* lpsmSock;

	TransCommand.code = OpCode::OPCODE_GETPLAYERINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;

	lpsmSock = GetServerSock(ServerCode);

	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}
	return FALSE;
}

#define DEADLOCK_CHECK_LIMIT_TIME		(30*1000)
#define DEADLOCK_CHECK_LIMIT_TIME2		(60*1000)
#define RECONNECT_LIMIT_TIME			(7*1000)


static DWORD dwCheckNetCount = 0;
static DWORD dwLastTransCheckTime = 0;
static int	ReconnectCount = 0;


int	TransCheckNetwork()
{
	return 0;
}


int SendAdminMode(AccountTypes type)
{
	//LOG(LOG_DEBUG, "SEND POWER USER TO SERVER");
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_AUTH_ADMIN_MODE;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = (int)type;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockDataServer && smWsockServer != smWsockDataServer)
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer && smWsockDataServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer && smWsockDataServer != smWsockExtendServer)
		smWsockExtendServer->Send((char*)&TransCommand, TransCommand.size, TRUE);


	return smWsockServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendNetworkQuality(DWORD NetworkQuality)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_NETWORK_QUALITY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = NetworkQuality;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	return smWsockServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendCheckIP(int Code, SocketData* lpsmSock)
{
	smTRANS_CHAR_COMMAND TransCharCommand;

	TransCharCommand.code = OpCode::OPCODE_CHECKIP;
	TransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	TransCharCommand.WParam = Code;
	TransCharCommand.LParam = 0;
	TransCharCommand.SParam = 0;

	strcpy_s(TransCharCommand.szName, lpsmSock->szIP);

	return smWsockDataServer->Send((char*)&TransCharCommand, TransCharCommand.size, TRUE);
}


int SendSetObjectSerial(DWORD dwObjectSerial)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->dwObjectSerial;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;

	smWsockServer->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (AreaServerMode)
	{
		if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
		if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
	}

	return TRUE;
}


int SendSetObjectSerial_First(DWORD dwObjectSerial)
{

	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->dwObjectSerial;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;



	if (smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	if (smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	return TRUE;
}


int SendContinueServer(DWORD dwObjectSerial, SocketData* lpsmSock)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_CONT_OBJSERIAL;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	return lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendSetHackUser3(int Type, int LParam, int SParam)
{
	//LOG(LOG_DEBUG, "SendSetHackUser3: Type(%d)  LParam(%d)  SParam(%d)", Type, LParam, SParam);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST2;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = SParam;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int CheckCracker()
{
	char* szName;
	char TransBuff[1024];
	int len;

	szName = FindCracker();

	if (szName)
	{

		if (smWsockDataServer)
		{
			len = lstrlen(szName) + 9;
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szName);
			((int*)TransBuff)[0] = len;
			((int*)TransBuff)[1] = OpCode::OPCODE_FINDCRACK;

			smWsockDataServer->Send(TransBuff, len, TRUE);
		}
		return TRUE;
	}
	return FALSE;
}


int CheckCracker(TRANS_FIND_CRACKER* lpTransFindCrack)
{
	char* szName;
	char TransBuff[1024];
	int len;
	char* lpBuff;

	if (lpTransFindCrack)
		szName = FindCracker(lpTransFindCrack);
	else
		szName = FindCrackCont();

	if (szName)
	{

		if (smWsockDataServer)
		{
			len = lstrlen(szName) + 9;
			strcpy_s(TransBuff + 8, sizeof(TransBuff) - 8, szName);
			((int*)TransBuff)[0] = len;
			((int*)TransBuff)[1] = OpCode::OPCODE_FINDCRACK;

			smWsockDataServer->Send(TransBuff, len, TRUE);
		}
		return TRUE;
	}

	if (lpTransFindCrack)
	{
		if (lpTransFindCrack->size > (lpTransFindCrack->FindCounter * ((int)sizeof(_CRACK_NAME)) + 16))
		{
			lpBuff = (char*)&lpTransFindCrack->CrackName[lpTransFindCrack->FindCounter];
			if (lpBuff[0])
			{

				GetNoticeUrl(lpBuff);
			}
		}
	}

	return FALSE;
}


int SendCrackWindow(HWND hWnd)
{
	//LOG(LOG_DEBUG, "SendCrackWindow");

	char* szName;
	char TransBuff[1024];
	int len;


	if (smWsockServer)
	{

		szName = TransBuff + 8;
		GetWindowText(hWnd, szName, 32);
		len = lstrlen(szName) + 9;
		((int*)TransBuff)[0] = len;
		((int*)TransBuff)[1] = OpCode::OPCODE_FINDCRACK2;

		smWsockServer->Send(TransBuff, len, TRUE);
	}
	return TRUE;
}


int SendSetHackUser(int StopGame)
{
	//LOG(LOG_DEBUG, "SendSetHackUser: StopGame(%d)", StopGame);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = StopGame;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	WarningHack = StopGame;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (WarningHack)
	{
		DisconnectServerCode = 4;
		//LOG(LOG_DEBUG, "SetDisconnectFlag: 25");
		//LOG(LOG_SERVER, "SetDisconnectFlag: 25");
		DisconnectFlag = GetCurrentTime();
	}

	return TRUE;
}


int SendSetHackUser2(int Type, int LParam)
{
	//LOG(LOG_DEBUG, "SendSetHackUser2: Type(%d)  LParam(%d)", Type, LParam);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_BLACKLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Type;
	TransCommand.LParam = LParam;
	TransCommand.SParam = 0;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int SendCopyItemUser(int CopyItemCount)
{
	//LOG(LOG_DEBUG, "SendCopyItemUser: CopyItemCount(%d)", CopyItemCount);

	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_SET_ITEMCOPYLIST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = CopyItemCount;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}


int SendSaveThrowItem(sITEMINFO* lpItemInfo)
{
	smTRANS_COMMAND	TransCommand;


	if ((lpItemInfo->CODE & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1))	return FALSE;


	TransCommand.code = OpCode::OPCODE_SAVETHROWITEM;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpItemInfo->CODE;
	TransCommand.LParam = lpItemInfo->ItemHeader.Head;
	TransCommand.SParam = lpItemInfo->ItemHeader.dwChkSum;

	if ((lpItemInfo->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
		ComparePotion();

	return smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}



int	SendRecordTradeItems(sTRADE* lpTrade)
{

	TRANS_RECORD_TRADE_ITEMS	TransRecordTradeItems;
	int cnt;

	ZeroMemory(&TransRecordTradeItems, sizeof(TRANS_RECORD_TRADE_ITEMS));

	TransRecordTradeItems.code = OpCode::OPCODE_RECORD_TRADE;
	TransRecordTradeItems.Money = lpTrade->Money - 193;
	strcpy_s(TransRecordTradeItems.szTradeUserName, cTrade.szTradeCharName);

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag && TransRecordTradeItems.ThrowItemCount < TRADE_RECV_ITEMS_MAX)
		{
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwCode = lpTrade->TradeItem[cnt].sItemInfo.CODE;
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwHead = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head;
			TransRecordTradeItems.Items[TransRecordTradeItems.ThrowItemCount].dwChkSum = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
			TransRecordTradeItems.ThrowItemCount++;
		}
	}


	TransRecordTradeItems.size = TRANS_RECORD_TRADE_DEFSIZE + TransRecordTradeItems.ThrowItemCount * sizeof(_TRANS_RECORD_TRADE_ITEM);

	return smWsockDataServer->Send((char*)&TransRecordTradeItems, TransRecordTradeItems.size, TRUE);
}


int SendSaveThrowItem2(sITEMINFO* lpItemInfo)
{
	smTRANS_COMMAND_EX	TransCommand;


	TransCommand.code = OpCode::OPCODE_SAVETHROWITEM2;
	TransCommand.size = sizeof(smTRANS_COMMAND_EX);
	TransCommand.WParam = lpItemInfo->CODE;
	TransCommand.LParam = lpItemInfo->ItemHeader.Head;
	TransCommand.SParam = lpItemInfo->ItemHeader.dwChkSum;
	TransCommand.EParam = lpItemInfo->PotionCount ^ TransCommand.SParam ^ TransCommand.code;

	TransCommand.WxParam = lpCurPlayer->smCharInfo.Money;
	TransCommand.LxParam = EncodeParam(TransCommand.WxParam);
	TransCommand.SxParam = GetTotalMoney() ^ TransCommand.LxParam;
	TransCommand.ExParam = lpItemInfo->Money;

	if ((lpItemInfo->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
		ComparePotion();


	AddInvenMoney(-lpItemInfo->Money);

	return smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendSaveMoney()
{
	smTRANS_COMMAND	TransCommand;

	if (cWareHouse.OpenFlag && CompWareHouseMoney) return FALSE;

	TransCommand.code = OpCode::OPCODE_SAVETHROWMONEY;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = lpCurPlayer->smCharInfo.Money;
	TransCommand.LParam = EncodeParam(TransCommand.WParam);
	TransCommand.SParam = GetTotalMoney() ^ TransCommand.LParam;

	return smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendCopyOtherUser(char* szName, int Mode)
{
	smTRANS_CHAR_COMMAND	TransCharCommand;
	int cnt, len;

	TransCharCommand.code = OpCode::OPCODE_GETRECORDDATA;
	TransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	TransCharCommand.WParam = dwExeCheckSum;
	TransCharCommand.LParam = Mode;
	TransCharCommand.SParam = 0;


	if (Mode == 2)
	{
		len = lstrlen(szName);
		for (cnt = 0; cnt < len; cnt++)
		{
			if (szName[cnt] == ' ')
			{
				TransCharCommand.LParam = atoi(&szName[cnt]);
				szName[cnt] = 0;
				if (TransCharCommand.LParam < 1000) TransCharCommand.LParam = Mode;
				break;
			}
		}
	}

	strcpy_s(TransCharCommand.szName, szName);

	AdminCharDisable = TRUE;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&TransCharCommand, TransCharCommand.size, TRUE);

	return NULL;
}


int SendPlayUpdateInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 0;
	TransCommand.LParam = lpCurPlayer->smCharInfo.Level;
	TransCommand.SParam = 0;
	TransCommand.EParam = 0;

	return smWsockServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int SendUpdateClanInfo()
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_UPDATE_CINFO;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = 1;
	TransCommand.LParam = lpCurPlayer->smCharInfo.Level;
	TransCommand.SParam = lpCurPlayer->smCharInfo.ClassClan;
	TransCommand.EParam = lpCurPlayer->smCharInfo.bUpdateInfo[0];

	if (smWsockServer)
		smWsockServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockExtendServer && smWsockServer != smWsockExtendServer)
		smWsockExtendServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (smWsockDataServer && smWsockServer != smWsockDataServer && rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan))
		smWsockDataServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	if (AreaServerMode)
	{
		if (lpWSockServer_Area[0]) lpWSockServer_Area[0]->Send((char*)&TransCommand, TransCommand.size, TRUE);
		if (lpWSockServer_Area[1]) lpWSockServer_Area[1]->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}

	return TRUE;
}









TRANS_SKIL_ATTACKDATA	Back_TransSkilAttackData;


int Skil_RangeAttack(int x, int y, int z, int range, int power, int TargetState)
{

	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;

	int	dRange;
	int dx, dy, dz, dist;
	smCHAR* lpChar;
	SocketData* lpsmSendSock = 0;



	Record_ClinetLogFile("������ ������Ŷ - Skil_RangeAttack ");
	quit = 1;
	return TRUE;


	mCnt = 0;

	dRange = range >> FLOATNS;
	dRange *= dRange;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (x - lpChar->pX) >> FLOATNS;
			dy = (y - lpChar->pY) >> FLOATNS;
			dz = (z - lpChar->pZ) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < dRange)
			{



				TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;


				if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
				{
					lpChar->EnableStateBar = TRUE;
				}

			}
		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD) * SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD) * mCnt + 16;

	TransSkilAttackData.x = x;
	TransSkilAttackData.y = y;
	TransSkilAttackData.z = z;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = range;
	TransSkilAttackData.Power = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);

	LastAttackDamage = power;

	memcpy(&Back_TransSkilAttackData, &TransSkilAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && mCnt > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char*)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}

	if (PkMode)
	{

		Skil_RangeAttack_User(x, y, z, range, power, TargetState);
	}

	return TRUE;
}



int Skil_RangeAttack_User(int x, int y, int z, int range, int power, int TargetState)
{
	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;

	int	dRange;
	int dx, dy, dz, dist;
	smCHAR* lpChar;
	SocketData* lpsmSendSock = 0;

	mCnt = 0;

	dRange = range >> FLOATNS;
	dRange *= dRange;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (x - lpChar->pX) >> FLOATNS;
			dy = (y - lpChar->pY) >> FLOATNS;
			dz = (z - lpChar->pZ) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < dRange)
			{

				TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;

			}
		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKUSER;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD) * SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD) * mCnt + 16;

	TransSkilAttackData.x = x;
	TransSkilAttackData.y = y;
	TransSkilAttackData.z = z;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = range;
	TransSkilAttackData.Power = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);


	if (mCnt > 0)
	{

		Record_SendDamage(smWsockUserServer, TransSkilAttackData.Power);

		smWsockUserServer->Send((char*)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}







	return TRUE;
}


int Skil_RangeBoxAttack(smCHAR* lpCurChar, RECT* lpRect, int power, int TargetState, int UseAttackRating)
{

	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	int cnt, mCnt;
	int dx, dy, dz;
	int Attack, accuracy;
	smCHAR* lpChar;
	SocketData* lpsmSendSock = 0;



	Record_ClinetLogFile("������ ������Ŷ - Skil_RangeBoxAttack ");
	quit = 1;
	return TRUE;


	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;


			GetMoveLocation(dx, dy, dz, 0, (-lpCurChar->Angle.y) & ANGCLIP, 0);

			if (GeoResult_X > lpRect->left && GeoResult_X<lpRect->right &&
				GeoResult_Z>lpRect->top && GeoResult_Z < lpRect->bottom && abs(dy) < 256)
			{

				Attack = TRUE;

				if (UseAttackRating)
				{
					accuracy = sinGetAccuracy(chrOtherPlayer[cnt].smCharInfo.Level, chrOtherPlayer[cnt].smCharInfo.Defence);
					if ((rand() % 100) > accuracy)
						Attack = FALSE;
				}

				if (Attack)
				{
					TransSkilAttackData.dwTarObjectSerial[mCnt++] = chrOtherPlayer[cnt].dwObjectSerial;


					if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
					{
						lpChar->EnableStateBar = TRUE;
					}
				}
			}

		}
	}

	TransSkilAttackData.TargetCount = mCnt;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD) * SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD) * mCnt + 16;

	TransSkilAttackData.x = lpCurChar->pX;
	TransSkilAttackData.y = lpCurChar->pY;
	TransSkilAttackData.z = lpCurChar->pZ;

	TransSkilAttackData.AttackState = TargetState;
	TransSkilAttackData.AttackSize = 0;
	TransSkilAttackData.Power = power;

	LastAttackDamage = power;

	TransSkilAttackData.dwChkSum = TransSkilAttackData.Power * 2002 +
		(TransSkilAttackData.x * TransSkilAttackData.y * TransSkilAttackData.z);


	memcpy(&Back_TransSkilAttackData, &TransSkilAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && mCnt > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char*)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}
	return TRUE;
}


int Skill_CharRangeEffect(DWORD dwSkillCode, smCHAR* lpCurChar, smCHAR* lpCharTarget, int point)
{
	int time, rs;

	switch (dwSkillCode)
	{
	case SKILL_PLAY_ROAR:
		time = Roar_Time[point - 1];

		rs = lpCharTarget->smCharInfo.Resistance[sITEMINFO_BIONIC];
		if (rs < 0) rs = 0;
		if (rs >= 100) rs = 100;
		rs = 100 - rs;
		time = (time * rs) / 100;

		if (time)
		{
			if (time > 2) time = 2;
			AssaParticle_Stune(lpCharTarget, time);
			return TRUE;
		}
		break;

	case SKILL_PLAY_SOUL_SUCKER:
		if (lpCharTarget->smCharInfo.Brood != smCHAR_MONSTER_UNDEAD &&
			((lpCharTarget->smCharInfo.Life[1] * 50) / 100) < lpCharTarget->smCharInfo.Life[0])
		{

			sinSkillEffect_Soul_Sucker(lpCurChar, lpCharTarget);
			return TRUE;
		}
		break;

	}
	return FALSE;
}



int Skil_RangeBoxEffect(smCHAR* lpCurChar, RECT* lpRect, DWORD dwSkillCode, int TargetState)
{

	int cnt, mCnt;
	int dx, dy, dz;
	smCHAR* lpChar;

	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
			lpCurChar != &chrOtherPlayer[cnt])
		{

			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;


			GetMoveLocation(dx, dy, dz, 0, (-lpCurChar->Angle.y) & ANGCLIP, 0);

			if (GeoResult_X > lpRect->left && GeoResult_X<lpRect->right &&
				GeoResult_Z>lpRect->top && GeoResult_Z < lpRect->bottom && abs(dy) < 256)
			{

				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], 0) == TRUE)
				{
					mCnt++;
				}
			}

		}
	}

	return mCnt;
}


int Skil_RangeEffect(smCHAR* lpCurChar, int Range, DWORD dwSkillCode, int TargetState, int point)
{

	int cnt, mCnt;
	int dx, dy, dz;
	smCHAR* lpChar;
	int	dRange;

	dRange = Range * Range;

	mCnt = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (mCnt >= SKIL_ATTACK_CHAR_MAX) break;
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
			lpCurChar != &chrOtherPlayer[cnt])
		{

			lpChar = &chrOtherPlayer[cnt];

			dx = (lpChar->pX - lpCurChar->pX) >> FLOATNS;
			dy = (lpChar->pY - lpCurChar->pY) >> FLOATNS;
			dz = (lpChar->pZ - lpCurChar->pZ) >> FLOATNS;

			if ((dx * dx + dy * dy + dz * dz) < dRange)
			{
				if (Skill_CharRangeEffect(dwSkillCode, lpCurChar, &chrOtherPlayer[cnt], point) == TRUE)
				{
					mCnt++;
				}
			}

		}
	}

	return mCnt;
}





DWORD EncodeParam(DWORD Param)
{
	return (Param + (Param << 4)) * 2002;
}




int QuickSendTransAttack(smCHAR* lpChar, int power, int AttackState, int Resistance)
{
	TRANS_ATTACKDATA	TransAttackData;
	SocketData* lpsmSendSock = 0;
	int pow;


	Record_ClinetLogFile("������ ������Ŷ - QuickSendTransAttack ");
	quit = 1;
	return TRUE;


	if (RestartPlayCount != 0) return FALSE;

	TransAttackData.code = OpCode::OPCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpChar->pX;
	TransAttackData.y = lpChar->pY;
	TransAttackData.z = lpChar->pZ;

	TransAttackData.AttackState = AttackState;
	TransAttackData.AttackSize = 48 * fONE;
	TransAttackData.Power = power;

	if (Resistance)
	{
		TransAttackData.AttackState |= (Resistance << 16);
		pow = Resistance >> 4;
		if (pow > 0 && pow < 512)
		{
			TransAttackData.Power += pow;
		}
	}

	TransAttackData.dwDestObjectSerial = lpCurPlayer->dwObjectSerial;
	TransAttackData.dwTarObjectSerial = lpChar->dwObjectSerial;
	TransAttackData.dwChkSum = TransAttackData.Power * 2002 +
		(TransAttackData.x * TransAttackData.y * TransAttackData.z);

	LastAttackDamage = TransAttackData.Power;


	if (lpChar->smCharInfo.Life[1] && lpChar->smCharInfo.Life[0] == lpChar->smCharInfo.Life[1])
	{
		lpChar->EnableStateBar = TRUE;
	}

	if (lpChar->ServerCode)
	{
		lpsmSendSock = GetServerSock(lpChar->ServerCode);
	}


	if (lpsmSendSock)
	{

		Record_SendDamage(lpsmSendSock, TransAttackData.Power);

		return lpsmSendSock->Send((char*)&TransAttackData, TransAttackData.size, TRUE);
	}

	return NULL;
}


int QuickSendTransAttack(smCHAR* lpChar, int power)
{
	return QuickSendTransAttack(lpChar, power, 1, 0);
}

int QuickSendTransAttack(smCHAR* lpChar, int power, int Resistance)
{
	return QuickSendTransAttack(lpChar, power, 1, Resistance);
}





int SendRequestTrade(int dwObjectSerial, int Flag)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_TRADE_REQUST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = Flag;
	TransCommand.SParam = lpCurPlayer->dwObjectSerial;

	if (smWsockUserServer)
		return smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);

	return FALSE;
}


int SendTradeItem(sTRADE* lpTrade, DWORD dwSender)
{
	int cnt;
	int len;
	int	PotionError = 0;
	TRANS_TRADEITEMS TransTradeItems;
	sTRADE	sTradeBuff;

	len = 0;


	if (CheckTrade((void*)lpTrade) == FALSE)
	{
		SendRequestTrade(dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	memcpy(&sTradeBuff, lpTrade, sizeof(sTRADE));


	PotionError = ComparePotion();

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (!sTradeBuff.TradeItem[cnt].Flag)
		{
			ZeroMemory(&sTradeBuff.TradeItem[cnt], sizeof(sITEM));
		}
		else
		{
			sTradeBuff.TradeItem[cnt].sItemInfo.ItemHeader.Head = 0;
			if (PotionError)
			{
				sTradeBuff.TradeItem[cnt].sItemInfo.PotionCount = sTradeBuff.TradeItem[cnt].sItemInfo.ItemHeader.Head + 1;
			}
			len++;
		}
	}


	len = EecodeCompress((BYTE*)&sTradeBuff, TransTradeItems.TradeBuff, sizeof(sTRADE));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems.code = OpCode::OPCODE_TRADEITEMS;
	TransTradeItems.size = len + 48;
	TransTradeItems.dwSum = 0;
	TransTradeItems.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems.dwRecver = dwSender;
	TransTradeItems.Temp[0] = 0;
	TransTradeItems.Temp[1] = 0;
	TransTradeItems.Temp[2] = 0;
	TransTradeItems.Temp[3] = 0;

	if (smWsockUserServer)
		return smWsockServer->Send((char*)&TransTradeItems, TransTradeItems.size, TRUE);

	return FALSE;
}


int RecvTradeItems(TRANS_TRADEITEMS* lpTransTradeItems, sTRADE* lpTrade)
{

	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE*)lpTrade);
	memcpy(&TransLastRecvTrade, lpTransTradeItems, lpTransTradeItems->size);
	return TRUE;
}


int SendTradeItem(DWORD dwSender)
{
	return SendTradeItem(&sTrade, dwSender);
}

int RecvTradeItems(TRANS_TRADEITEMS* lpTransTradeItems)
{
	int res;

	res = RecvTradeItems(lpTransTradeItems, &sTradeRecv);
	cTrade.LoadTradeItemIamge();
	cTrade.CheckTradeButtonOk();

	ItemPickUpFlag = 1;


	if (CheckTrade(&sTradeRecv) == FALSE)
	{
		SendRequestTrade(lpTransTradeItems->dwSender, 3);
		cTrade.CancelTradeItem();
		return FALSE;
	}

	if (sTrade.CheckFlag && !sTradeRecv.CheckFlag)
	{
		sTrade.CheckFlag = 0;
		TradeItemCancelCount++;
		if (TradeItemCancelCount >= 3)
		{

			SendRequestTrade(lpTransTradeItems->dwSender, 3);
			cTrade.CancelTradeItem();
			return FALSE;
		}
		else
		{
			cMessageBox.ShowMessage(MESSAGE_MOVE_TRADE_ITEM);
			SendTradeItem(lpTransTradeItems->dwSender);
		}
	}

	return res;
}


int SendTradeSucessKey(DWORD dwSender)
{

	return SendTradeSucessKey(&sTrade, dwSender);
}






int SendTradeSucessKey(sTRADE* lpTrade, DWORD dwSender)
{

	TRANS_TRADE_ITEMKEY	TransTradeItemKey;
	int cnt;
	int	TradeOpenFlag, CancelFlag;

	if (DisconnectFlag)
		return FALSE;

	TransTradeItemKey.code = OpCode::OPCODE_TRADE_ITEMKEY;
	TransTradeItemKey.size = sizeof(TRANS_TRADE_ITEMKEY);
	TransTradeItemKey.dwSender = lpCurPlayer->dwObjectSerial;;
	TransTradeItemKey.dwRecver = dwSender;
	TransTradeItemKey.Money = lpTrade->Money;


	TradeOpenFlag = cTrade.OpenFlag;
	cTrade.OpenFlag = 0;
	CancelFlag = 0;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag)
		{
			TransTradeItemKey.dwItemCode[cnt] = lpTrade->TradeItem[cnt].sItemInfo.CODE;
			TransTradeItemKey.dwItemKey[cnt] = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head;
			TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;

			if (FindInvenItem(lpTrade->TradeItem[cnt].sItemInfo.CODE,
				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head,
				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum) != 0)
			{

				CancelFlag = TRUE;


				SendInvenItemError(1, lpTrade->TradeItem[cnt].sItemInfo.CODE,
					lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head,
					lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum);
			}

			if ((TransTradeItemKey.dwItemCode[cnt] & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
			{

				TransTradeItemKey.dwItemSum[cnt] = lpTrade->TradeItem[cnt].sItemInfo.PotionCount & 0xFFFF;
				TransTradeItemKey.dwItemSum[cnt] |= (lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum) << 16;
				TransTradeItemKey.dwItemSum[cnt] ^= (TransTradeItemKey.dwItemSum[cnt] >> 16) ^ 0x5cbc;
			}

		}
		else
		{
			TransTradeItemKey.dwItemCode[cnt] = 0;
			TransTradeItemKey.dwItemKey[cnt] = 0;
			TransTradeItemKey.dwItemSum[cnt] = 0;
		}
	}

	cTrade.OpenFlag = TradeOpenFlag;

	if (!CancelFlag)
	{


		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&TransTradeItemKey, TransTradeItemKey.size, TRUE);



		memcpy(&LastTransTradeItemKey, &TransTradeItemKey, sizeof(TRANS_TRADE_ITEMKEY));
		dwLastTransTradeKeyTime = dwPlayTime;
	}

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}



int RecvTradeSucessKey(TRANS_TRADE_ITEMKEY* lpTransTradeItemKey, sTRADE* lpTrade)
{
	int cnt;
	sTRADE sChkTrade;
	DWORD	dwChkSum1, dwChkSum2;
	int	ItemFlag;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (TransLastRecvTrade.code)
	{

		DecodeCompress(TransLastRecvTrade.TradeBuff, (BYTE*)&sChkTrade);
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			memcpy(&lpTrade->TradeItem[cnt].sItemInfo, &sChkTrade.TradeItem[cnt].sItemInfo, sizeof(sITEMINFO));
		}
	}


	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (lpTrade->TradeItem[cnt].Flag)
		{

			dwChkSum1 = lpTransTradeItemKey->dwItemSum[cnt];
			dwChkSum2 = lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
			if ((lpTrade->TradeItem[cnt].sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
			{

				ItemFlag = 1;
				dwChkSum1 = dwChkSum1 >> 16;
				dwChkSum2 = dwChkSum2 & 0xFFFF;
			}
			else
				ItemFlag = 0;

			if (lpTransTradeItemKey->dwItemCode[cnt] == lpTrade->TradeItem[cnt].sItemInfo.CODE && dwChkSum1 == dwChkSum2)
			{


				lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head = lpTransTradeItemKey->dwItemKey[cnt];


				if (!lpTrade->TradeItem[cnt].sItemInfo.ItemHeader.Head)
					lpTrade->TradeItem[cnt].Flag = 0;
				else
				{
					if (ItemFlag == 1)
					{

						ReformItem(&lpTrade->TradeItem[cnt].sItemInfo);
					}
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			if (lpTransTradeItemKey->dwItemCode[cnt])
				return FALSE;

		}
	}



	return TRUE;
}




int SendTradeCheckItem(DWORD dwSender)
{

	TRANS_TRADE_CHECKITEM	TransTradeCheckItem;
	int cnt;

	if (DisconnectFlag)
		return FALSE;

	TransTradeCheckItem.code = OpCode::OPCODE_TRADE_READYITEM;
	TransTradeCheckItem.size = sizeof(TRANS_TRADE_CHECKITEM);
	TransTradeCheckItem.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeCheckItem.dwRecver = dwSender;

	if (sTrade.Money)
	{
		SendSaveMoney();
	}

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTrade.TradeItem[cnt].Flag)
		{
			TransTradeCheckItem.dwSendItemCode[cnt] = sTrade.TradeItem[cnt].sItemInfo.CODE;
			TransTradeCheckItem.dwSendItemSum[cnt] = sTrade.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;




			if (CheckItemForm(&sTrade.TradeItem[cnt].sItemInfo) == FALSE)
				return FALSE;

		}
		else
		{
			TransTradeCheckItem.dwSendItemCode[cnt] = 0;
			TransTradeCheckItem.dwSendItemSum[cnt] = 0;
		}
	}


	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTradeRecv.TradeItem[cnt].Flag)
		{
			TransTradeCheckItem.dwRecvItemCode[cnt] = sTradeRecv.TradeItem[cnt].sItemInfo.CODE;
			TransTradeCheckItem.dwRecvItemSum[cnt] = sTradeRecv.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum;
		}
		else
		{
			TransTradeCheckItem.dwRecvItemCode[cnt] = 0;
			TransTradeCheckItem.dwRecvItemSum[cnt] = 0;
		}
	}


	if (smWsockServer)
		smWsockServer->Send((char*)&TransTradeCheckItem, TransTradeCheckItem.size, TRUE);

	if (smWsockUserServer && smWsockServer != smWsockUserServer)
		smWsockUserServer->Send((char*)&TransTradeCheckItem, TransTradeCheckItem.size, TRUE);

	dwTradeMaskTime = dwPlayTime + 3000;

	return TRUE;
}


int RecvTradeCheckItem(TRANS_TRADE_CHECKITEM* lpTransTradeCheckItem)
{
	int cnt;

	dwTradeMaskTime = dwPlayTime + 3000;

	if (DisconnectFlag)
		return FALSE;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
	{
		if (sTrade.TradeItem[cnt].Flag)
		{
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt] != sTrade.TradeItem[cnt].sItemInfo.CODE ||
				((lpTransTradeCheckItem->dwRecvItemCode[cnt] & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwRecvItemSum[cnt] != sTrade.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum))
			{

				return FALSE;

			}
		}
		else
		{
			if (lpTransTradeCheckItem->dwRecvItemCode[cnt])
				return FALSE;
		}

		if (sTradeRecv.TradeItem[cnt].Flag)
		{
			if (lpTransTradeCheckItem->dwSendItemCode[cnt] != sTradeRecv.TradeItem[cnt].sItemInfo.CODE ||
				((lpTransTradeCheckItem->dwSendItemCode[cnt] & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1) &&
					lpTransTradeCheckItem->dwSendItemSum[cnt] != sTradeRecv.TradeItem[cnt].sItemInfo.ItemHeader.dwChkSum))
			{

				return FALSE;

			}
		}
		else
		{
			if (lpTransTradeCheckItem->dwSendItemCode[cnt])
				return FALSE;
		}
	}

	return TRUE;
}








int SendJoinPartyUser(DWORD dwObjectCode)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_PARTY_JOIN;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectCode;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	return smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
}


int	PartyButton(int Num, int Button)
{


	DWORD	dwCode;
	smTRANS_COMMAND	smTransCommand;

	if (!InterfaceParty.PartyMemberCount) return FALSE;

	dwCode = 0;

	if (Num >= 0)
		dwCode = InterfaceParty.PartyMember[Num].ChrCode;
	else
		dwCode = 0;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_PARTY_COMMAND;
	smTransCommand.WParam = dwCode;
	smTransCommand.LParam = Button;
	smTransCommand.SParam = 0;

	if (Button < 3 && InterfaceParty.PartyMember[0].ChrCode != lpCurPlayer->dwObjectSerial)
	{

		return FALSE;
	}

	return smWsockUserServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
}







int	SetTotalSubMoney(int Money)
{
	TotalSubMoney += Money;

	return TRUE;
}

int	SetTotalAddMoney(int Money)
{
	TotalAddMoney += Money;

	return TRUE;
}

int	SetTotalAddExp(int Exp)
{
	TotalAddExp += Exp;

	return TRUE;
}

int	SetTotalSubExp(int Exp)
{
	TotalSubExp += Exp;

	return TRUE;
}

int	GetTotalMoney()
{
	int m;

	m = sServerMoney[0].InputMoney + sServerMoney[1].InputMoney + sServerMoney[2].InputMoney + WareHouseSubMoney + TotalAddMoney - TotalSubMoney;

	return m;
}

int GetTotalSubExp()
{
	int m;

	m = (sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp) - (TotalAddExp - TotalSubExp);

	return m;
}

int GetTotalExp()
{
	int m;

	m = sServerExp[0].InputExp + sServerExp[1].InputExp + sServerExp[2].InputExp + TotalAddExp - TotalSubExp;

	return m;
}


int	SaveWareHouse(sWAREHOUSE* lpWareHouse, TRANS_WAREHOUSE* lpTransWareHouse)
{
	TRANS_WAREHOUSE	TransWareHouse;

	sWAREHOUSE	WareHouseCheck;
	int	CompSize;
	int cnt;
	DWORD	dwChkSum;
	char* szComp1, * szComp2;
	int	flag;

	if (lpTransWareHouse) flag = 1;
	else flag = 0;

	if (!flag && QuitSave)	return FALSE;

	for (cnt = 0; cnt < 300; cnt++)
	{
		if (!lpWareHouse->WareHouseItem[cnt].Flag)
		{
			ZeroMemory(&lpWareHouse->WareHouseItem[cnt], sizeof(sITEM));
		}
	}


	CompSize = EecodeCompress((BYTE*)lpWareHouse, (BYTE*)TransWareHouse.Data, sizeof(sWAREHOUSE), sizeof(sITEM) * 100);



	if (!flag && CompSize > (smSOCKBUFF_SIZE - 256))
		return FALSE;

	if (flag && CompSize > (smSOCKBUFF_SIZE - 140))
		return FALSE;


	DecodeCompress((BYTE*)TransWareHouse.Data, (BYTE*)&WareHouseCheck, sizeof(sWAREHOUSE));

	szComp1 = (char*)lpWareHouse;
	szComp2 = (char*)&WareHouseCheck;

	dwChkSum = 0;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
	{
		if (szComp1[cnt] != szComp2[cnt])
		{
			return FALSE;
		}
		else
		{
			dwChkSum += szComp1[cnt] * (cnt + 1);
		}
	}



	WareHouseSubMoney += (CompWareHouseMoney - lpWareHouse->Money);
	CompWareHouseMoney = 0;


	TransWareHouse.code = OpCode::OPCODE_WAREHOUSE;
	TransWareHouse.size = sizeof(TRANS_WAREHOUSE) - (sizeof(sWAREHOUSE) - CompSize);
	TransWareHouse.DataSize = CompSize;
	TransWareHouse.dwChkSum = dwChkSum;
	TransWareHouse.wVersion[0] = Version_WareHouse;
	TransWareHouse.wVersion[1] = 0;

	if (!flag)
	{

		TransWareHouse.WareHouseMoney = lpWareHouse->Money ^ (dwChkSum ^ OpCode::OPCODE_WAREHOUSE);
		TransWareHouse.UserMoney = lpCurPlayer->smCharInfo.Money ^ (dwChkSum ^ OpCode::OPCODE_WAREHOUSE);
	}

	TransWareHouse.dwTemp[0] = 0;
	TransWareHouse.dwTemp[1] = 0;
	TransWareHouse.dwTemp[2] = 0;
	TransWareHouse.dwTemp[3] = 0;
	TransWareHouse.dwTemp[4] = 0;

	dwLastWareHouseChkSum = dwChkSum;

	if (flag)
	{
		memcpy(lpTransWareHouse, &TransWareHouse, sizeof(TRANS_WAREHOUSE));
		return TRUE;
	}

	if (TransWareHouse.size > smSOCKBUFF_SIZE) TransWareHouse.size = smSOCKBUFF_SIZE;

	if (smWsockDataServer)
	{
		smWsockDataServer->Send((char*)&TransWareHouse, TransWareHouse.size, TRUE);

		SaveGameData();
		return TRUE;
	}

	return FALSE;
}

int	SaveWareHouse(sWAREHOUSE* lpWareHouse)
{
	return SaveWareHouse(lpWareHouse, 0);
}


int	LoadWareHouse(TRANS_WAREHOUSE* lpTransWareHouse, sWAREHOUSE* lpWareHouse, int flag)
{
	sWAREHOUSE	WareHouseCheck;
	int cnt;
	DWORD	dwChkSum;
	char* szComp;

	if (lpTransWareHouse->DataSize == 0)
	{

		ZeroMemory(lpWareHouse, sizeof(sWAREHOUSE));
		lpWareHouse->Money = 2023;
		lpWareHouse->Weight[0] = 197;
		CompWareHouseMoney = lpWareHouse->Money;
		return TRUE;
	}

	DecodeCompress((BYTE*)lpTransWareHouse->Data, (BYTE*)&WareHouseCheck);

	dwChkSum = 0;

	szComp = (char*)&WareHouseCheck;

	for (cnt = 0; cnt < sizeof(sWAREHOUSE); cnt++)
	{
		dwChkSum += szComp[cnt] * (cnt + 1);
	}
	if (dwChkSum == lpTransWareHouse->dwChkSum)
	{

		if (!flag && dwLastWareHouseChkSum && dwLastWareHouseChkSum != lpTransWareHouse->dwChkSum && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
		{

			return FALSE;
		}

		memcpy(lpWareHouse, &WareHouseCheck, sizeof(sWAREHOUSE));

		CompWareHouseMoney = lpWareHouse->Money;

		for (cnt = 0; cnt < 300; cnt++)
		{
			if (lpWareHouse->WareHouseItem[cnt].Flag)
			{


				if (!lpWareHouse->WareHouseItem[cnt].sItemInfo.Temp0)
					lpWareHouse->WareHouseItem[cnt].sItemInfo.Temp0 = lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwChkSum + lpWareHouse->WareHouseItem[cnt].sItemInfo.CODE;



				if (!lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwTime)
				{

					lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwTime =
						(lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.Head >> 2) ^ (lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemHeader.dwChkSum << 2);
				}


				if ((lpWareHouse->WareHouseItem[cnt].sItemInfo.CODE & sinITEM_MASK2) == sinSP1)
				{

					if (lpWareHouse->WareHouseItem[cnt].sItemInfo.PotionCount > 1)	lpWareHouse->WareHouseItem[cnt].Flag = 0;



				}

				if (DeleteEventItem_TimeOut(&lpWareHouse->WareHouseItem[cnt].sItemInfo) == TRUE)
				{

					lpWareHouse->WareHouseItem[cnt].Flag = 0;
					//wsprintf(szMsgBuff, mgItemTimeOut, lpWareHouse->WareHouseItem[cnt].sItemInfo.ItemName);
					//AddChatBuff(szMsgBuff, 0);
				}
			}
		}
		return TRUE;
	}

	return FALSE;
}


int	LoadWareHouse(TRANS_WAREHOUSE* lpTransWareHouse, sWAREHOUSE* lpWareHouse)
{
	return LoadWareHouse(lpTransWareHouse, lpWareHouse, 0);
}


int SendCollectMoney(int Money)
{


	sITEM	sItemMoney;
	int j;


	memset(&sItemMoney, 0, sizeof(sITEM));
	sItemMoney.sItemInfo.CODE = sinGG1 | sin01;
	for (j = 0; j < MAX_ITEM; j++)
	{
		if (sItem[j].CODE == sItemMoney.sItemInfo.CODE)
		{
			memcpy(&sItemMoney, &sItem[j], sizeof(sITEM));
			sItemMoney.sItemInfo.Money = Money;
			sItemMoney.sItemInfo.ItemKindCode = OpCode::OPCODE_COLLECTMONEY;
			ReformItem(&sItemMoney.sItemInfo);
			if (sinThrowItemToFeild(&sItemMoney))
			{
				AddInvenMoney(-Money);
				return TRUE;
			}
		}
	}

	return FALSE;
}


int PlayerKilling(DWORD dwObjectSerial)
{
	smTRANS_COMMAND	TransCommand;

	TransCommand.code = OpCode::OPCODE_PLAYERKILLING;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = lpCurPlayer->dwObjectSerial;
	TransCommand.SParam = 0;

	if (smWsockUserServer)
	{
		return smWsockUserServer->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}
	return FALSE;
}




int SendCraftItemToServer(void* lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER* lpCraftItem_Send = (sCRAFTITEM_SERVER*)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_CRAFTITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}


int SendWingItemToServer(void* lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER* lpCraftItem_Send = (sCRAFTITEM_SERVER*)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_WINGITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}



int SendAgingItemToServer(void* lpsCraftItem_Send)
{

	sCRAFTITEM_SERVER* lpCraftItem_Send = (sCRAFTITEM_SERVER*)lpsCraftItem_Send;

	lpCraftItem_Send->size = sizeof(sCRAFTITEM_SERVER);
	lpCraftItem_Send->code = OpCode::OPCODE_AGINGITEM;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)lpCraftItem_Send, lpCraftItem_Send->size, TRUE);
	}

	return FALSE;
}


int SendLinkCoreToServer(sITEMINFO* lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;
	int len;

	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.code = OpCode::OPCODE_MAKE_LINKCORE;
	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	TransItemInfo.x = lpCurPlayer->pX;
	TransItemInfo.y = lpCurPlayer->pY;
	TransItemInfo.z = lpCurPlayer->pZ;

	TransItemInfo.dwSeCode[0] = 0;
	TransItemInfo.dwSeCode[1] = 0;
	TransItemInfo.dwSeCode[2] = 0;
	TransItemInfo.dwSeCode[3] = 0;

	len = lstrlen(lpItem->ItemName);
	if (lpItem->ItemName[len + 1])
	{
		TransItemInfo.code = OpCode::OPCODE_USE_LINKCORE;

		if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
		{

			return FALSE;
		}

		if (smWsockServer)
			return smWsockServer->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	return FALSE;
}

int SucessLinkCore(smTRANS_COMMAND_EX* lpTransCommandEx)
{
	int x, z, cnt;

	sITEMINFO* lpItem;


	lpItem = FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);

	if (lpItem)
	{
		SendUseItemCodeToServer(lpItem);
		cInvenTory.DeleteInvenItemToServer(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam);
		ResetInvenItemCode();

		if (FindInvenItem(lpTransCommandEx->WxParam, lpTransCommandEx->LxParam, lpTransCommandEx->SxParam) != 0) return FALSE;

	}
	else
		return FALSE;


	CloseEachPlayer();

	WarpFieldNearPos(lpTransCommandEx->EParam, lpTransCommandEx->WParam, lpTransCommandEx->SParam, &x, &z);

	lpCurPlayer->SetPosi(lpTransCommandEx->WParam, lpTransCommandEx->LParam, lpTransCommandEx->SParam, 0, 0, 0);
	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;


	lpCurPlayer->OnStageField = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->OnStageField = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->OnStageField = 1;
	}

	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 48 * fONE, lpCurPlayer->pZ, EFFECT_RETURN1);
	SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	RestartPlayCount = 350;

	return TRUE;
}



int SendAgingUpgradeItemToServer(sITEMINFO* lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if (TransAgingItemFlag) return FALSE;

	TransItemInfo.code = OpCode::OPCODE_AGING_UPGRADE;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;
	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	if (smWsockDataServer)
	{
		if (smWsockDataServer->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE) == TRUE)
		{
			TransAgingItemFlag = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}





int ClearInvenPotionCount()
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].Flag && (cInvenTory.InvenItem[cnt].sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
		{
			cInvenTory.InvenItem[cnt].sItemInfo.PotionCount = 1;
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].Flag && (cInvenTory.InvenItemTemp[cnt].sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
		{
			cInvenTory.InvenItemTemp[cnt].sItemInfo.PotionCount = 1;
		}
	}

	if (cTrade.OpenFlag)
	{
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++)
		{
			if (sTrade.TradeItem[cnt].Flag && (sTrade.TradeItem[cnt].sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
			{
				sTrade.TradeItem[cnt].sItemInfo.PotionCount = 1;
			}
		}
	}

	if (MouseItem.Flag && (MouseItem.sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
		MouseItem.sItemInfo.PotionCount = 1;

	cInvenTory.ReFormPotionNum();

	SaveGameData();

	return TRUE;
}


sITEMINFO* FindItemFromCode(DWORD dwItemCode)
{
	int cnt;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].Flag && cInvenTory.InvenItem[cnt].sItemInfo.CODE == dwItemCode)
		{
			return &cInvenTory.InvenItem[cnt].sItemInfo;
		}
	}
	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].Flag && cInvenTory.InvenItemTemp[cnt].sItemInfo.CODE == dwItemCode)
		{
			return &cInvenTory.InvenItemTemp[cnt].sItemInfo;
		}
	}

	return NULL;
}



DWORD	dwLastCheckItemTime = 0;


int	SendCheckItemToServer(sITEMINFO* lpItem)
{

	TRANS_ITEMINFO	TransItemInfo;



	if ((dwLastCheckItemTime + 10000) > dwPlayTime)
	{

		return FALSE;
	}


	TransItemInfo.code = OpCode::OPCODE_CHECKITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

	TransItemInfo.x = 0;
	TransItemInfo.y = 0;
	TransItemInfo.z = 0;

	if (smWsockUserServer)
	{
		smWsockUserServer->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}
	dwLastCheckItemTime = dwPlayTime;

	return TRUE;
}


int RecvCheckItemFromServer(TRANS_ITEM_CODE* lpTransItemCode)
{

	switch (lpTransItemCode->code)
	{
	case OpCode::OPCODE_CHECKITEM:



		break;

	case OpCode::OPCODE_ERRORITEM:

		cInvenTory.DeleteInvenItemToServer(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);


		if (FindInvenItem(lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum) == 0)
		{

			SendInvenItemError(0, lpTransItemCode->dwItemCode, lpTransItemCode->dwHead, lpTransItemCode->dwChkSum);
			ResetInvenItemCode();
		}

		break;

	case OpCode::OPCODE_CLEARPOTION:

		ClearInvenPotionCount();
		break;
	}

	return TRUE;
}


int	SellItemToServer(sITEMINFO* lpItem, int Count)
{

	TRANS_ITEMINFO	TransItemInfo;

	TransItemInfo.code = OpCode::OPCODE_SHOP_SELLITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));

#ifdef _TEST_SERVER

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL] && VRKeyBuff['N'] && VRKeyBuff['B'])
	{

		lpItem->Durability[0] = lpItem->Durability[1] * 100;
	}
#endif

	TransItemInfo.x = Count;
	TransItemInfo.y = lpCurPlayer->smCharInfo.Money;
	TransItemInfo.z = 0;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}

	return FALSE;
}





int Chk_InventPosCount = 1;
DWORD	dwCheckInvenItemTime = 0;


int CheckInvenItemToServer()
{
	int cnt;

	if (dwCheckInvenItemTime > dwPlayTime) return TRUE;

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItem[cnt].ItemPosition == Chk_InventPosCount)
		{

			SendCheckItemToServer(&cInvenTory.InvenItem[cnt].sItemInfo);
		}
	}

	for (cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (cInvenTory.InvenItemTemp[cnt].ItemPosition == Chk_InventPosCount)
		{

			SendCheckItemToServer(&cInvenTory.InvenItemTemp[cnt].sItemInfo);
		}
	}

	Chk_InventPosCount++;
	dwCheckInvenItemTime = dwPlayTime + 55 * 1000;

	if (Chk_InventPosCount >= 11 || Chk_InventPosCount < 1) Chk_InventPosCount = 1;

	return TRUE;
}



HANDLE	hTimeCheckThread = 0;
int		TimeCheckCounter;

DWORD WINAPI TimeCheckThread(void* pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int		cnt;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;
	TimeCheckCounter = 0;

	while (1)
	{
		dwTime = GetCurrentTime();
		cnt = dwTime - dwLastTime;
		if (cnt > PlayTimerMax) PlayTimerMax = cnt;
		dwLastTime = dwTime;
		TimeCheckCounter++;
		Sleep(800);
	}

	ExitThread(TRUE);
	return TRUE;
}



int OpenTimeCheckThread()
{
	DWORD	dwTimeCheckThreadID;

	if (!hTimeCheckThread)
	{
		hTimeCheckThread = CreateThread(NULL, 0, TimeCheckThread, 0, 0, &dwTimeCheckThreadID);
	}

	return TRUE;
}

int	PlayTimerMax_SendingCount = 0;

int SendPlayTimerMax()
{
	smTRANS_COMMAND	smTransCommand;

	if (PlayTimerMax >= 10000 || (PlayTimerMax_SendingCount & 0x7) == 0)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_PROCESS_TIMEMAX;
		smTransCommand.WParam = PlayTimerMax;
		smTransCommand.LParam = TimeCheckCounter;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

		PlayTimerMax = 0;
	}

	PlayTimerMax_SendingCount++;

	return TRUE;
}








DWORD funcCheckMemSum(DWORD FuncPoint, int count)
{
	int cnt;
	DWORD dwSum;
	int	xcnt;
	DWORD* lpGetPrtectPoint;


	lpGetPrtectPoint = (DWORD*)FuncPoint;

	dwSum = 0;
	xcnt = 1;

	for (cnt = 0; cnt < count; cnt++)
	{
		xcnt += cnt;
		dwSum += lpGetPrtectPoint[cnt] * xcnt;
	}

	return dwSum;
}







DWORD	dwFuncList[][2] = {
	{ (DWORD)funcCheckMemSum << 1				,	512		},
	{ (DWORD)Check_PlaySubReleaseFunc << 1	,	512		},
	{ (DWORD)PlayPat3D << 1					,	2048	},
	{ (DWORD)Check_CodeSafe << 1				,	1024	},
	{ (DWORD)AddExp << 1						,	512		},
	{ (DWORD)sinSetLife << 1					,	512		},
	{ (DWORD)NetWorkPlay << 1					,	2800	},

	{ (DWORD)E_Shield_BlockRate << 1			,	(DWORD)((Meteo_UseMana - E_Shield_BlockRate) + 10) },

	{ (DWORD)Code_VRamBuffOpen << 1			,	3600	},
	{ 0,0 }
};




int	SendClientFuncPos()
{

	TRANS_CLIENT_FUNPOS	TransClientFuncPos;
	int cnt;


	ZeroMemory(&TransClientFuncPos, sizeof(TRANS_CLIENT_FUNPOS));

	TransClientFuncPos.code = OpCode::OPCODE_CLIENT_FUNCPOS;
	TransClientFuncPos.size = sizeof(TRANS_CLIENT_FUNPOS);
	TransClientFuncPos.ClientVersion = Client_Version;

	cnt = 0;
	TransClientFuncPos.dwFunc_CheckMemSum = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
	TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
	TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);


	while (1)
	{

		if (dwFuncList[cnt][0] == 0) break;
		if (cnt >= dwFUNC_VALUE_MAX)  break;

		TransClientFuncPos.dwFuncValue[cnt].dwFunc = dwFuncList[cnt][0] >> 1;
		TransClientFuncPos.dwFuncValue[cnt].dwLen = dwFuncList[cnt][1];
		TransClientFuncPos.dwFuncValue[cnt].dwChkSum = funcCheckMemSum(TransClientFuncPos.dwFuncValue[cnt].dwFunc, TransClientFuncPos.dwFuncValue[cnt].dwLen);

		cnt++;
	}

	TransClientFuncPos.FuncCount = cnt;


	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&TransClientFuncPos, TransClientFuncPos.size, TRUE);

	return FALSE;
}



int	RecvMemFuncData(TRANS_FUNC_MEMORY* TransFuncMem)
{
	smTRANS_COMMAND	smTransCommand;

	fnChkMem = (LPFN_CheckMem)((void*)TransFuncMem->szData);

	smTransCommand.size = 0;

	fnChkMem(TransFuncMem, &smTransCommand);

	if (smWsockDataServer && smTransCommand.size > 0)
		smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}




#define	RECV_TRANSITEM_QUE_MAX			256
#define	RECV_TRANSITEM_QUE_MASK			255

TRANS_ITEMINFO	Recv_TransItemInfo_Que[RECV_TRANSITEM_QUE_MAX];

int	RecvTransItemQue_Push = 0;
int	RecvTransItemQue_Pop = 0;


int	PushRecvTransItemQue(TRANS_ITEMINFO* lpTransItemInfo)
{
	int mCnt;

	mCnt = RecvTransItemQue_Push & RECV_TRANSITEM_QUE_MASK;

	memcpy(&Recv_TransItemInfo_Que[mCnt], lpTransItemInfo, sizeof(TRANS_ITEMINFO));
	RecvTransItemQue_Push++;
	RecvTransItemQue_Pop = RecvTransItemQue_Push - RECV_TRANSITEM_QUE_MASK;
	if (RecvTransItemQue_Pop < 0) RecvTransItemQue_Pop = 0;

	return TRUE;
}


TRANS_ITEMINFO* FindRecvTransItemQue(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;

		if (Recv_TransItemInfo_Que[mCnt].Item.CODE == dwCode &&
			Recv_TransItemInfo_Que[mCnt].Item.ItemHeader.Head == dwHead &&
			Recv_TransItemInfo_Que[mCnt].Item.ItemHeader.dwChkSum == dwChkSum)
		{

			return &Recv_TransItemInfo_Que[mCnt];
		}
	}

	return NULL;
}


int CheckRecvTrnsItemQue()
{
	int cnt, mCnt;

	for (cnt = RecvTransItemQue_Pop; cnt < RecvTransItemQue_Push; cnt++)
	{
		mCnt = cnt & RECV_TRANSITEM_QUE_MASK;
		if (Recv_TransItemInfo_Que[mCnt].Item.CODE) return FALSE;
	}

	return TRUE;
}


int SendUseItemCodeToServer(sITEMINFO* lpItem)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = OpCode::OPCODE_USEITEM_CODE;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND);
	smTransCommandEx.WParam = lpItem->CODE;
	smTransCommandEx.LParam = lpItem->ItemHeader.Head;
	smTransCommandEx.SParam = lpItem->ItemHeader.dwChkSum;
	smTransCommandEx.EParam = lpItem->PotionCount;

	smTransCommandEx.WxParam = 0;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)&smTransCommandEx, smTransCommandEx.size, TRUE);
	}

	return FALSE;
}


int RecvCommandUser(smTRANS_COMMAND_EX* lpTransCommandEx)
{
	smCHAR* lpChar;
	smCHAR* lpChar2;

	switch (lpTransCommandEx->WParam)
	{
	case smCOMMNAD_USER_WARP:

		StartEffect(lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam, EFFECT_RETURN1);
		SkillPlaySound(SKILL_SOUND_LEARN, lpTransCommandEx->LParam, lpTransCommandEx->SParam, lpTransCommandEx->EParam);
		break;


	case smCOMMNAD_USER_AGINGUP:

		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar)
		{
			StartEffect(lpChar->pX, lpChar->pY, lpChar->pZ, EFFECT_AGING);
			esPlaySound(7, GetDistVolume(lpChar->pX, lpChar->pY, lpChar->pZ), 1600);
		}
		break;

	case smCOMMNAD_USER_HOLY_INCANTATION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar)
		{
			AssaParticle_HolyIncantationPart(lpChar, lpTransCommandEx->SParam);
		}
		break;

	case smCOMMNAD_USER_RESURRECTION:
		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		if (lpChar)
		{
			AssaParticle_ResurrectionPart(lpChar);
		}
		break;

	case smCOMMNAD_USER_FORCEORB:

		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar)
		{
			StartSkill(lpChar->pX, lpChar->pY, lpChar->pZ, 0, 0, 0, SKILL_UP1);
			SkillPlaySound(SKILL_SOUND_LEARN, lpChar->pX, lpChar->pY, lpChar->pZ);
		}
		break;

	case smCOMMNAD_USER_VALENTO:

		lpChar = FindChrPlayer(lpTransCommandEx->LParam);
		lpChar2 = FindChrPlayer(lpTransCommandEx->SParam);
		if (lpChar && lpChar2)
		{
			sinSkillEffect_Soul_Sucker(lpChar, lpChar2);
		}
		break;

	case smCOMMNAD_USER_FIREFLOWER:
		lpChar = FindChrPlayer(lpTransCommandEx->WxParam);
		if (lpChar && lpChar != lpCurPlayer)
		{
			DWORD	dwTable = GetTableNum(lpTransCommandEx->LParam);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1000, (dwTable >> 24) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 1500, (dwTable >> 16) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2000, (dwTable >> 8) & 0xFF, 0, 0, lpChar);
			AddTimeEffect(SKILL_EFFECT_FIREFLOWER, dwPlayTime + 2500, dwTable & 0xFF, 0, 0, lpChar);
		}
		break;

	}

	return TRUE;
}


int	SendCommandUser(int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	smTransCommandEx.code = OpCode::OPCODE_COMMAND_USER;
	smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommandEx.WParam = wParam;
	smTransCommandEx.LParam = lParam;
	smTransCommandEx.SParam = sParam;
	smTransCommandEx.EParam = eParam;

	smTransCommandEx.WxParam = lpCurPlayer->dwObjectSerial;
	smTransCommandEx.LxParam = 0;
	smTransCommandEx.SxParam = 0;
	smTransCommandEx.ExParam = 0;

	if (smWsockUserServer)
	{
		return smWsockUserServer->Send((char*)&smTransCommandEx, smTransCommandEx.size, TRUE);
	}
	return FALSE;
}


int	SendCommand_AreaServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;
	SocketData* lpsmSock;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
	{
		return lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}


int	SendCommand_DataServer(DWORD dwCode, int wParam, int lParam, int sParam, int eParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = dwCode;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = wParam;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	if (smWsockDataServer)
	{
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}

struct	sDAMAGE_RECORD
{
	int	Damage;
	int	Count;
};

sDAMAGE_RECORD	sRecvDamage[3];
sDAMAGE_RECORD	sSendDamage[3];



int	Init_RecordDamage()
{
	ZeroMemory(sRecvDamage, sizeof(sDAMAGE_RECORD) * 3);
	ZeroMemory(sSendDamage, sizeof(sDAMAGE_RECORD) * 3);

	return TRUE;
}


int	Record_RecvDamage(SocketData* lpsmSock, int Damage)
{
	smTRANS_COMMAND	smTransCommand;

	if (smWsockServer == lpsmSock)
	{
		sRecvDamage[0].Damage -= Damage;
		sRecvDamage[0].Count--;

		if ((sRecvDamage[0].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[0].Count;
			smTransCommand.LParam = sRecvDamage[0].Damage;
			smTransCommand.SParam = sSendDamage[0].Count;
			smTransCommand.EParam = sSendDamage[0].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
	}
	else if (smWsockUserServer == lpsmSock)
	{
		sRecvDamage[1].Damage -= Damage;
		sRecvDamage[1].Count--;

		if ((sRecvDamage[1].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[1].Count;
			smTransCommand.LParam = sRecvDamage[1].Damage;
			smTransCommand.SParam = sSendDamage[1].Count;
			smTransCommand.EParam = sSendDamage[1].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}

	}
	else if (smWsockExtendServer == lpsmSock)
	{
		sRecvDamage[2].Damage -= Damage;
		sRecvDamage[2].Count--;

		if ((sRecvDamage[2].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[2].Count;
			smTransCommand.LParam = sRecvDamage[2].Damage;
			smTransCommand.SParam = sSendDamage[2].Count;
			smTransCommand.EParam = sSendDamage[2].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	return TRUE;
}


int	Record_SendDamage(SocketData* lpsmSock, int Damage)
{
	smTRANS_COMMAND	smTransCommand;

	if (smWsockServer == lpsmSock)
	{
		sSendDamage[0].Damage -= Damage;
		sSendDamage[0].Count--;

		if ((sRecvDamage[0].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[0].Count;
			smTransCommand.LParam = sRecvDamage[0].Damage;
			smTransCommand.SParam = sSendDamage[0].Count;
			smTransCommand.EParam = sSendDamage[0].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
	}
	else if (smWsockUserServer == lpsmSock)
	{
		sSendDamage[1].Damage -= Damage;
		sSendDamage[1].Count--;

		if ((sRecvDamage[1].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[1].Count;
			smTransCommand.LParam = sRecvDamage[1].Damage;
			smTransCommand.SParam = sSendDamage[1].Count;
			smTransCommand.EParam = sSendDamage[1].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}

	}
	else if (smWsockExtendServer == lpsmSock)
	{
		sSendDamage[2].Damage -= Damage;
		sSendDamage[2].Count--;

		if ((sRecvDamage[2].Count & 0x1FF) == 0)
		{
			smTransCommand.code = OpCode::OPCODE_REC_DAMAGEDATA;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = sRecvDamage[2].Count;
			smTransCommand.LParam = sRecvDamage[2].Damage;
			smTransCommand.SParam = sSendDamage[2].Count;
			smTransCommand.EParam = sSendDamage[2].Damage;
			if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	return TRUE;
}


int	SendPartySkillToServer(DWORD dwSkillCode, int SkillLevel, int Around, int wParam, int lParam, int sParam, int eParam)
{
	int x, y, z, dist;
	int cnt;
	int PartyCount;
	TRANS_PARTY_SKILL	TransPartySkill;
	SocketData* lpsmSock;

	TransPartySkill.code = OpCode::OPCODE_PARTY_SKILL;
	TransPartySkill.dwSkillCode = dwSkillCode;
	TransPartySkill.wParam = wParam;
	TransPartySkill.lParam = lParam;
	TransPartySkill.sParam = sParam;
	TransPartySkill.eParam = eParam;

	PartyCount = 0;

	TransPartySkill.dwPartyUser[PartyCount++] = lpCurPlayer->dwObjectSerial;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && chrOtherPlayer[cnt].PartyFlag)
		{
			x = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpCurPlayer->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
			dist = x * x + y * y + z * z;
			if (dist < (Around * Around))
			{
				TransPartySkill.dwPartyUser[PartyCount++] = chrOtherPlayer[cnt].dwObjectSerial;
			}
		}
	}

	TransPartySkill.PartyCount = PartyCount;
	TransPartySkill.Point = SkillLevel;
	TransPartySkill.size = sizeof(TRANS_PARTY_SKILL) - (8 - PartyCount) * 4;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char*)&TransPartySkill, TransPartySkill.size, TRUE);

	return TRUE;
}


int SendCancelSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	SocketData* lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_CANCEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int SendUpdateSkillToServer(DWORD dwSkillCode, int lParam, int sParam, int eParam)
{
	SocketData* lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_UPDATEL_SKILL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode;
	smTransCommand.LParam = lParam;
	smTransCommand.SParam = sParam;
	smTransCommand.EParam = eParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock) lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


int SendProcessSKillToServer(DWORD dwSkillCode, int point, int Param1, int Param2)
{

	SocketData* lpsmSock;
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = OpCode::OPCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwSkillCode | (point << 8);
	smTransCommand.LParam = lpCurPlayer->dwObjectSerial;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	smTransCommand.LParam = dm_GetCommandChkSum(&smTransCommand, lpCurPlayer->dwObjectSerial);

#ifdef _USE_DYNAMIC_ENCODE
	if (fnEncodeDamagePacket)
	{
		fnEncodeDamagePacket(&smTransCommand);

		lpsmSock = GetAreaServerSock();
		if (lpsmSock)
			lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}
#else
	dm_EncodePacket(&smTransCommand);

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
#endif

	return TRUE;


}


int RecvPartySkillFromServer(TRANS_PARTY_SKILL* lpTransPartySkill)
{
	int cnt, cnt2, cnt3;
	int time;
	int flag;


	switch (lpTransPartySkill->dwSkillCode)
	{
	case SKILL_PLAY_HOLY_VALOR:

		if (lpTransPartySkill->Point < 1 || lpTransPartySkill->Point>10) break;

		time = Holy_Valor_Time[lpTransPartySkill->Point - 1];
		for (cnt = 1; cnt < lpTransPartySkill->PartyCount; cnt++)
		{
			if (lpCurPlayer->dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
			{

				flag = 0;

				for (cnt3 = 0; cnt3 < 10; cnt3++)
				{
					if (ContinueSkill[cnt].Flag)
					{
						if (ContinueSkill[cnt].CODE == SKILL_DRASTIC_SPIRIT || ContinueSkill[cnt].CODE == SKILL_HOLY_BODY)
						{
							flag++;
						}
					}
				}

				if (flag)
				{




					SendCancelSkillToServer(lpTransPartySkill->dwSkillCode, 0, 0, 0);
				}
				else
				{

					AssaParticle_HolyValor_Member(lpCurPlayer, time);
					sSKILL sSkill;

					ZeroMemory(&sSkill, sizeof(sSKILL));
					sSkill.CODE = SKILL_HOLY_VALOR;
					sSkill.UseTime = time;
					sSkill.Flag = TRUE;
					sSkill.Point = lpTransPartySkill->Point;
					sinContinueSkillSet(&sSkill);
				}
			}
			else
			{
				for (cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
				{
					if (chrOtherPlayer[cnt2].Flag &&
						chrOtherPlayer[cnt2].dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
					{
						AssaParticle_HolyValor_Member(&chrOtherPlayer[cnt2], time);
					}
				}
			}
		}
		break;


	case SKILL_PLAY_EXTINCTION:

		for (cnt = 0; cnt < lpTransPartySkill->PartyCount; cnt++)
		{
			for (cnt2 = 0; cnt2 < OTHER_PLAYER_MAX; cnt2++)
			{
				if (chrOtherPlayer[cnt2].Flag &&
					chrOtherPlayer[cnt2].dwObjectSerial == lpTransPartySkill->dwPartyUser[cnt])
				{
					AssaParticle_Extinction(&chrOtherPlayer[cnt2]);
					SkillPlaySound(SKILL_SOUND_SKILL_EXTINTION, chrOtherPlayer[cnt2].pX, chrOtherPlayer[cnt2].pY, chrOtherPlayer[cnt2].pZ);
				}
			}
		}
		break;

	}


	return TRUE;
}

DWORD	dwLastClanUserCode = 0;


int SendClanJoinService(DWORD dwMsgCode, smCHAR* lpChar)
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

#ifdef  __CLANSUBCHIP__
	if (cldata.myPosition != 101 && cldata.myPosition != 104) return FALSE;
#else
	if (cldata.myPosition != 101) return FALSE;
#endif

	smTransCharCommand.code = OpCode::OPCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = dwMsgCode;
	smTransCharCommand.LParam = lpChar->dwObjectSerial;
	smTransCharCommand.SParam = lpCurPlayer->dwObjectSerial;
	strcpy_s(smTransCharCommand.szName, cldata.name);
	strcpy_s(smTransCharCommand.szId, UserAccount);

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&smTransCharCommand, smTransCharCommand.size, TRUE);

	return TRUE;
}


int SendJoinClan()
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	if (!dwLastClanUserCode) return FALSE;

	smTransCharCommand.code = OpCode::OPCODE_CLAN_SERVICE;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 2;
	smTransCharCommand.LParam = dwLastClanUserCode;
	smTransCharCommand.SParam = lpCurPlayer->dwObjectSerial;
	strcpy_s(smTransCharCommand.szName, lpCurPlayer->smCharInfo.szName);
	strcpy_s(smTransCharCommand.szId, UserAccount);

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&smTransCharCommand, smTransCharCommand.size, TRUE);

	return TRUE;
}


int RecvClanJoinService(smTRANS_CHAR_COMMAND2* lpTransCharCommand)
{
	smCHAR* lpChar;

	switch (lpTransCharCommand->WParam)
	{
	case 1:
		if (cldata.myPosition == 102 || cldata.myPosition == 103)
		{

			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
			{
				ClanJoin(lpTransCharCommand->szName, lpChar->smCharInfo.szName);
				OpenEachPlayer(lpChar);
				DispEachMode = TRUE;
				dwLastClanUserCode = lpTransCharCommand->SParam;
			}
		}
		break;

	case 2:
#ifdef  __CLANSUBCHIP__
		if (cldata.myPosition == 101 || cldata.myPosition == 104)
		{
#else
		if (cldata.myPosition == 101)
		{
#endif
			lpChar = FindAutoPlayer(lpTransCharCommand->SParam);
			if (lpChar)
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, lpChar->smCharInfo.JOB_CODE, lpChar->smCharInfo.Level);
			else
				menu_joinOpen_Chip(1, lpTransCharCommand->szId, lpTransCharCommand->szName, 0, 0);
		}
		break;
	}

	return TRUE;
}




DWORD	dwSkill_DivineLightning_Target[8];
int		DivineLightning_Target_Count = 0;
int		DivineLightning_FindCount = 0;


int	SkillPlay_DivineLightning_Select(smCHAR * lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	TRANS_SKIL_ATTACKDATA	TransSkilAttackData;
	SocketData* lpsmSendSock = 0;


	Record_ClinetLogFile("������ ������Ŷ - SkillPlay_DivineLightning_Select ");
	quit = 1;
	return TRUE;

	if (lpChar != lpCurPlayer) return FALSE;

	TargetCount = 0;

	LightningCount = Divine_Lightning_Num[SkillPoint - 1];

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{

		cCount = (DivineLightning_FindCount + cnt) & OTHER_PLAYER_MASK;

		if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
			lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
			chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
			chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
		{

			x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
			y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
			z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < (160 * 160))
			{
				dwSkill_DivineLightning_Target[TargetCount] = chrOtherPlayer[cCount].dwObjectSerial;
				TransSkilAttackData.dwTarObjectSerial[TargetCount] = chrOtherPlayer[cCount].dwObjectSerial;
				TargetCount++;

				if (chrOtherPlayer[cCount].smCharInfo.Life[1] && chrOtherPlayer[cCount].smCharInfo.Life[0] == chrOtherPlayer[cCount].smCharInfo.Life[1])
				{
					chrOtherPlayer[cCount].EnableStateBar = TRUE;
				}
				if (TargetCount >= LightningCount)
				{
					DivineLightning_FindCount = cCount;
					break;
				}
			}
		}
	}

	TransSkilAttackData.TargetCount = TargetCount;
	DivineLightning_Target_Count = TargetCount;

	TransSkilAttackData.code = OpCode::OPCODE_SKIL_ATTACKDATA;
	TransSkilAttackData.size = (sizeof(TRANS_SKIL_ATTACKDATA) - sizeof(DWORD) * SKIL_ATTACK_CHAR_MAX);
	TransSkilAttackData.size += sizeof(DWORD) * TargetCount + 16;

	TransSkilAttackData.x = lpChar->pX;
	TransSkilAttackData.y = lpChar->pY;
	TransSkilAttackData.z = lpChar->pZ;

	TransSkilAttackData.AttackState = 103;
	TransSkilAttackData.AttackSize = 160 * 160;
	TransSkilAttackData.Power = Divine_Lightning_Damage[SkillPoint - 1];

	lpsmSendSock = GetAreaServerSock();

	if (lpsmSendSock && TargetCount > 0)
	{

		Record_SendDamage(lpsmSendSock, TransSkilAttackData.Power);

		lpsmSendSock->Send((char*)&TransSkilAttackData, TransSkilAttackData.size, TRUE);
	}

	return TRUE;
}


int SkillPlay_DivineLightning_Effect(smCHAR * lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	smCHAR* lpTarChar;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_DivineLighting(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = Divine_Lightning_Num[SkillPoint - 1];

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt) & OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
				chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < (160 * 160))
				{
					AssaParticle_DivineLighting(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}

		if (TargetCount < LightningCount && lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < (160 * 160))
			{
				AssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}

	}


	return TargetCount;
}



int SkillPlay_MummyLord_Effect(smCHAR * lpChar, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	dRange = Range * Range;

	TargetCount = 0;

	if (lpChar->smCharInfo.Brood != smCHAR_MONSTER_USER)
	{

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER &&
				chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange)
				{
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}

		}

		if (lpChar->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
			y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
			z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dRange)
			{
				ParkAssaParticle_DivineLighting(lpCurPlayer);
				TargetCount++;
			}
		}
	}
	else
	{

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < dRange)
				{
					ParkAssaParticle_DivineLighting(&chrOtherPlayer[cnt]);
					TargetCount++;
				}

			}
		}
	}


	return TargetCount;
}



int SkillPlay_VenomSpear_Effect(smCHAR * lpChar, int SkillPoint)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int	LightningCount;
	int cCount;
	smCHAR* lpTarChar;
	int range;

	range = VenomSpear_Range[SkillPoint - 1];
	range *= range;

	TargetCount = 0;

	if (lpChar == lpCurPlayer)
	{
		for (cnt = 0; cnt < DivineLightning_Target_Count; cnt++)
		{
			lpTarChar = FindAutoPlayer(dwSkill_DivineLightning_Target[cnt]);
			if (lpTarChar)
			{
				AssaParticle_VeonmSpear(lpTarChar);
				TargetCount++;
			}
		}
	}
	else
	{
		LightningCount = Divine_Lightning_Num[SkillPoint - 1];

		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			cCount = (DivineLightning_FindCount + cnt) & OTHER_PLAYER_MASK;
			if (chrOtherPlayer[cCount].Flag && chrOtherPlayer[cCount].dwObjectSerial &&
				lpChar != &chrOtherPlayer[cCount] && chrOtherPlayer[cCount].smCharInfo.State == smCHAR_STATE_ENEMY &&
				chrOtherPlayer[cCount].smCharInfo.Brood != smCHAR_MONSTER_USER &&
				chrOtherPlayer[cCount].smCharInfo.Life[0] > 0)
			{

				x = (lpChar->pX - chrOtherPlayer[cCount].pX) >> FLOATNS;
				y = (lpChar->pY - chrOtherPlayer[cCount].pY) >> FLOATNS;
				z = (lpChar->pZ - chrOtherPlayer[cCount].pZ) >> FLOATNS;

				dist = x * x + y * y + z * z;

				if (dist < range)
				{
					AssaParticle_VeonmSpear(&chrOtherPlayer[cCount]);
					TargetCount++;
					if (TargetCount >= LightningCount)
					{
						DivineLightning_FindCount = cCount;
						break;
					}
				}
			}
		}
	}


	return TargetCount;
}


int SkillPlay_Monster_Effect(smCHAR * lpChar, int EffectKind, int Range)
{
	int cnt, TargetCount;
	int x, y, z, dist;
	int dDist = Range * Range;


	TargetCount = 0;

	x = (lpChar->pX - lpCurPlayer->pX) >> FLOATNS;
	y = (lpChar->pY - lpCurPlayer->pY) >> FLOATNS;
	z = (lpChar->pZ - lpCurPlayer->pZ) >> FLOATNS;

	dist = x * x + y * y + z * z;

	if (dist < dDist)
	{
		ParkAssaParticle_ChaosKaraSkill_User(lpCurPlayer);
		TargetCount++;
	}


	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial &&
			lpChar != &chrOtherPlayer[cnt] && chrOtherPlayer[cnt].smCharInfo.State == smCHAR_STATE_USER &&
			chrOtherPlayer[cnt].smCharInfo.Life[0] > 0)
		{
			x = (lpChar->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
			y = (lpChar->pY - chrOtherPlayer[cnt].pY) >> FLOATNS;
			z = (lpChar->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

			dist = x * x + y * y + z * z;

			if (dist < dDist)
			{
				ParkAssaParticle_ChaosKaraSkill_User(&chrOtherPlayer[cnt]);
				TargetCount++;
			}
		}
	}

	return TargetCount;
}





int RecvProcessSkill(smTRANS_COMMAND * lpTransCommand)
{
	int cnt;
	int dwSkillCode, point;
	smCHAR* lpChar, * lpChar2;
	POINT3D	Pos1, Pos2;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	point = (lpTransCommand->WParam >> 8) & 0xF;

	switch (dwSkillCode)
	{
	case SKILL_PLAY_HOLY_REFLECTION:

		sinSkillEffect_Holy_Reflection_Defense(lpCurPlayer);
		break;

	case SKILL_PLAY_ENCHANT_WEAPON:

		cnt = Enchant_Weapon_Time[point - 1];
		lpCurPlayer->EnchantEffect_Point = point;

		cSkill.SetEnchant_Weapon(cnt, point);

		switch (lpTransCommand->EParam)
		{
		case 0:
			AssaParticle_EnchantWeaponIceJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_ICE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 1:
			AssaParticle_EnchantWeaponLightJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_LIGHTING + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		case 2:
			AssaParticle_EnchantWeaponFireJang(lpCurPlayer, cnt);
			lpCurPlayer->WeaponEffect = sITEMINFO_FIRE + 1;
			lpCurPlayer->dwWeaponEffectTime = dwPlayTime + cnt * 1000;
			break;
		}
		break;

	case SKILL_PLAY_RESURRECTION:

		if (lpCurPlayer->MotionInfo && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD)
		{
			SendProcessSKillToServer(SKILL_PLAY_RESURRECTION, point, 0, 0);

			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
			StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
			SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
			CharPlaySound(lpCurPlayer);

			sinSetLife(lpCurPlayer->smCharInfo.Life[1] / 2);
			ResetEnergyGraph(4);
			lpCurPlayer->MoveFlag = FALSE;
			RestartPlayCount = 350;
			ReStartFlag = 0;
		}
		break;

	case SKILL_PLAY_VIRTUAL_LIFE:

		cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
		AssaParticle_VirtualLife(lpCurPlayer, Virtual_Life_Time[point - 1]);
		break;

	case SKILL_PLAY_LOVELY_LIFE:

		if (lpTransCommand->LParam == lpCurPlayer->dwObjectSerial)
		{
			cSkill.SetVirtualLife(Virtual_Life_Time[point - 1], point);
			AssaParticle_VirtualLife(lpCurPlayer, Virtual_Life_Time[point - 1]);
			SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
		}
		else
		{
			lpChar = FindChrPlayer(lpTransCommand->LParam);
			if (lpChar)
			{
				AssaParticle_VirtualLife(lpChar, Virtual_Life_Time[point - 1]);
				SkillPlaySound(SKILL_SOUND_SKILL_VIRTUAL_LIFE, lpChar->pX, lpChar->pY, lpChar->pZ);
			}
		}
		break;

	case SKILL_PLAY_VANISH:

		lpCurPlayer->PlayVanish = 0;
		cSkill.CancelContinueSkill(SKILL_VANISH);

		if (dwM_BlurTime) dwM_BlurTime = dwPlayTime;
		break;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:

		cSkill.SetT_Of_Valhalla(point, lpTransCommand->EParam);
		AssaParticle_TriumphOfValhalla(lpCurPlayer, T_Of_Valhalla_Time[point - 1]);
		break;

	case SKILL_PLAY_SPARK_SHIELD:



		lpChar = FindChrPlayer(lpTransCommand->LParam);
		lpChar2 = FindChrPlayer(lpTransCommand->SParam);
		if (lpChar && lpChar2)
		{

			if (lpChar->HvLeftHand.PatTool)
			{
				if (lpChar->GetToolBipPoint(&lpChar->HvLeftHand, &Pos1.x, &Pos1.y, &Pos1.z))
				{

					Pos2.x = lpChar2->pX;
					Pos2.y = lpChar2->pY + 24 * fONE;
					Pos2.z = lpChar2->pZ;

					AssaParticle_SparkShieldDefence(&Pos1, &Pos2);
					SkillPlaySound(SKILL_SOUND_SKILL_SPARK2, lpChar->pX, lpChar->pY, lpChar->pZ);
				}
			}
		}
		break;

	case SKILL_PLAY_HALL_OF_VALHALLA:

		cSkill.HellOfValhalla(Hall_Of_Valhalla_Time[point - 1], point, lpTransCommand->SParam, lpTransCommand->EParam, 1);
		SkillValhallaHallOfValhallaHandEffect(lpCurPlayer, (float)lpTransCommand->EParam);
		lpCurPlayer->dwHallOfValhallaTime = dwPlayTime + Hall_Of_Valhalla_Time[point - 1] * 1000;
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:

		cSkill.ForeceOfNature(Force_Of_Nature_Time[point - 1], point, 1);
		SkillSagittarionForceOfNature1(lpCurPlayer, (float)Force_Of_Nature_Time[point - 1]);
		lpCurPlayer->dwForceOfNatureTime = dwPlayTime + Force_Of_Nature_Time[point - 1] * 1000;
		break;


	case SKILL_PLAY_SOD_ITEM:


		switch (lpTransCommand->SParam)
		{
		case 1:
			SetBellatraFontEffect(E_BL_QUAKE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_QUAKE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 2:
			SetBellatraFontEffect(E_BL_STUN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STUN_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 3:
			SetBellatraFontEffect(E_BL_FREEZE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_FREEZE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 4:
			SetBellatraFontEffect(E_BL_RABBIE_SEAL);
			SetBellatraFontEffect(E_BL_FONT_RABBIE_SEAL);
			EffectWaveCamera(50, 3);
			SkillPlaySound(SKILL_SOUND_SKILL_DIASTROPHISM, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
			break;

		case 5:
			SetBellatraFontEffect(E_BL_STYGIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_STYGIAN_SEAL);
			break;

		case 6:
			SetBellatraFontEffect(E_BL_GUARDIAN_SEAL);
			SetBellatraFontEffect(E_BL_FONT_GUARDIAN_SEAL);
			break;

		case 7:
			SetBellatraFontEffect(E_BL_POINT_SEAL);
			SetBellatraFontEffect(E_BL_FONT_POINT_SEAL);
			break;
		}
		esPlaySound(19, 360);
		break;

	case SKILL_PLAY_HEALING:

		lpChar = FindChrPlayer(lpTransCommand->LParam);
		if (lpChar)
		{
			sinEffect_Healing2(lpChar);
			SkillPlaySound(SKILL_SOUND_SKILL_HEALING, lpChar->pX, lpChar->pY, lpChar->pZ);
		}
		break;

	case SKILL_PLAY_BLESS_SIEGE_ITEM:


		switch (lpTransCommand->SParam)
		{


		case (sinBI1 | sin05):
			lpCurPlayer->PlayInvincible = 70 * 5;
			break;
		case (sinBI1 | sin06):
			break;
		case (sinBI1 | sin07):
			break;



		case (sinBC1 | sin01):

			lpCurPlayer->PlayInvincible = 70 * 30;
			break;
		case (sinBC1 | sin02):

			break;
		case (sinBC1 | sin03):


			break;
		case (sinBC1 | sin05):
			lpCurPlayer->PlayInvincible = 70 * 5;
			break;

		case (sinBC1 | sin06):

			break;
		case (sinBC1 | sin07):

			break;
		case (sinBC1 | sin08):

			break;
		case (sinBC1 | sin09):

			break;
		case (sinBC1 | sin10):

			break;
		case (sinBC1 | sin11):

			break;
		case (sinBC1 | sin12):

			break;
		case (sinBC1 | sin13):

			break;
		case (sinBC1 | sin14):

			break;
		case (sinBC1 | sin15):

			break;
		case (sinBC1 | sin16):

			break;
		}
		break;

	}

	return TRUE;
}
















int SendClanCommandUser(SocketData * lpsmSock, DWORD	dwCode, int Param1, int Param2, CLANWONLIST * lpClanUserList, int ClanUserCount)
{

	TRANS_CLAN_COMMAND_USER	TransClanUser;
	int	cnt, len;
	DWORD	dwSpeedSum;
	int	BuffSize;

	TransClanUser.code = dwCode;

	TransClanUser.Param[0] = Param1;
	TransClanUser.Param[1] = Param2;
	TransClanUser.Param[2] = 0;
	TransClanUser.Param[3] = 0;
	TransClanUser.UserCount = ClanUserCount;

	char* lpBuff = TransClanUser.szUserBuff;

	for (cnt = 0; cnt < ClanUserCount; cnt++)
	{
		dwSpeedSum = GetSpeedSum(lpClanUserList->clanWon[cnt]);

		((DWORD*)lpBuff)[0] = dwSpeedSum;

		lpBuff += sizeof(DWORD);

		strcpy_s(lpBuff, sizeof(TransClanUser.szUserBuff), lpClanUserList->clanWon[cnt]);
		len = lstrlen(lpClanUserList->clanWon[cnt]);
		lpBuff += len + 1;
	}

	BuffSize = lpBuff - TransClanUser.szUserBuff;
	BuffSize += 16;

	TransClanUser.size = 32 + BuffSize;

	if (lpsmSock && ClanUserCount > 0)
	{
		lpsmSock->Send((char*)&TransClanUser, TransClanUser.size, TRUE);
	}

	return TRUE;
}


int	RecvClanCommand(TRANS_CLAN_COMMAND_USER * lpTransClanUser, _CLAN_USER_INFO * ClanUserInfo)
{
	int cnt;
	int cnt2;
	char* lpBuff;
	char	ch;

	lpBuff = lpTransClanUser->szUserBuff;

	if (lpTransClanUser->UserCount >= CLAN_USER_MAX) return FALSE;

	for (cnt = 0; cnt < lpTransClanUser->UserCount; cnt++)
	{
		ClanUserInfo[cnt].dwSpeedSum = ((DWORD*)lpBuff)[0];
		lpBuff += sizeof(DWORD);
		for (cnt2 = 0; cnt2 < 32; cnt2++)
		{
			ch = *lpBuff;
			ClanUserInfo[cnt].szName[cnt2] = ch;
			lpBuff++;
			if (!ch) break;
		}
		ClanUserInfo[cnt].szName[31] = 0;
	}

	return TRUE;
}


int FiltQuestItem(TRANS_ITEMINFO * lpTransItemInfo, DWORD dwPacketCode)
{
	int cnt;

	if (chaQuest.sHaQuestElementary[6].CODE != HAQUEST_CODE_ELEMENTARY_G)
	{

		cnt = cInvenTory.SearchItemCode(sinQT1 | sin16);
		if (cnt >= 1)
		{
			DeleteQuestItem(sinQT1 | sin16);
		}
		if (lpTransItemInfo->Item.CODE == (sinQT1 | sin16))
		{
			return FALSE;
		}

	}

	switch (sinQuest_ChangeJob2.CODE)
	{
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:

		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin01))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01)) return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin04)) return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin01);
			if (cnt >= 9) return FALSE;
		}
		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin02)) return FALSE;
		return TRUE;

	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:

		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin02))
		{
			if (!cInvenTory.SearchItemCode(sinMA1 | sin01)) return FALSE;
			if (cInvenTory.SearchItemCode(sinQT1 | sin05)) return FALSE;
			cnt = cInvenTory.SearchItemCode(sinMA2 | sin02);
			if (cnt >= 7) return FALSE;
		}
		if (lpTransItemInfo->Item.CODE == (sinMA2 | sin01)) return FALSE;
		return TRUE;
	}



	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin06))
	{
		if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin06);
			if (cnt >= 3) return FALSE;
			return TRUE;
		}
		return FALSE;
	}


	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin09))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin09);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin10))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin10);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}

	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin11))
	{
		if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin11);
			if (cnt >= 1) return FALSE;
			return TRUE;
		}
		return FALSE;
	}



	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin13))
	{

		if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4 && sinQuest_ChangeJob4.State == 5)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin13);
			if (cnt >= 1 || CheckAttMonsterCode(sinQuest_ChangeJob4.Kind) == FALSE)
				return FALSE;

			return TRUE;
		}
		return FALSE;
	}




	if (lpTransItemInfo->Item.CODE == (sinQT1 | sin16))
	{

		if (chaQuest.sHaQuestElementary[6].CODE == HAQUEST_CODE_ELEMENTARY_G)
		{
			cnt = cInvenTory.SearchItemCode(sinQT1 | sin16);
			if (cnt >= 1)
				return FALSE;

			if (dwPacketCode == OpCode::OPCODE_GETITEM)
			{

				char szBuff[256];

				AddChatBuff(szBuff, 6);
			}
			return TRUE;
		}
		return FALSE;
	}


	if ((lpTransItemInfo->Item.CODE & sinITEM_MASK2) == sinMA1 ||
		(lpTransItemInfo->Item.CODE & sinITEM_MASK2) == sinMA2)
	{


		return FALSE;
	}

	return TRUE;
}

POINT GetProcessModule();


int CheckProcessModule()
{
	POINT p;
	OSVERSIONINFO VersionInfo;
	BOOL Result;
	smTRANS_COMMAND	smTransCommand;


	return TRUE;

	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CLIENTINFO;

	Result = GetVersionEx(&VersionInfo);
	p = GetProcessModule();

	if (Result != FALSE)
	{
		smTransCommand.WParam = VersionInfo.dwPlatformId;
		smTransCommand.LParam = (VersionInfo.dwMajorVersion * 100) + VersionInfo.dwMinorVersion;
		smTransCommand.LParam = (smTransCommand.LParam << 16) | (VersionInfo.dwBuildNumber & 0xFFFF);
		smTransCommand.SParam = p.x;
		smTransCommand.EParam = p.y;

		smTransCommand.WParam ^= ((DWORD*)(UserAccount + 0))[0];
		smTransCommand.LParam ^= ((DWORD*)(UserAccount + 1))[0];
		smTransCommand.SParam ^= ((DWORD*)(UserAccount + 2))[0];
		smTransCommand.EParam ^= ((DWORD*)(UserAccount + 3))[0];

		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}


int SendFalconDamage(smCHAR * lpChar)
{
	DWORD point;
	int cnt;

	if (lpChar == lpCurPlayer && lpChar->chrAttackTarget)
	{
		point = ((SkillFalconPoint ^ ((DWORD)chrOtherPlayer ^ lpCurPlayer->dwObjectSerial)) + 1) << 8;
		point |= SKILL_PLAY_FALCON;
		cnt = dm_SendTransDamage(lpChar->chrAttackTarget, 0, 0, 0, 0, point, FALSE);
		DamageExp(lpChar->chrAttackTarget, cnt);
		return cnt;
	}
	return NULL;
}


int SendDancingSwordDamage(smCHAR * lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_DANCING_SWORD;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}



int SendMegneticSphereDamage(smCHAR * lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_MAGNETIC_SPHERE;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}


int SendMuspellDamage(smCHAR * lpChar)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = 1 << 8;
		point |= SKILL_PLAY_SUMMON_MUSPELL;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		if ((rand() % 2) == 0)
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK1, lpChar->pX, lpChar->pY, lpChar->pZ);
		else
			SkillPlaySound(SKILL_SOUND_SKILL_DANCING_SWORD_ATK2, lpChar->pX, lpChar->pY, lpChar->pZ);

		return cnt;
	}
	return FALSE;
}




int SendLowLevelPetDamage(smCHAR * lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}



int SendPCBangPetDamage(smCHAR * lpChar, int petType)
{
	DWORD point;
	int cnt;
	int wpDamage[2];

	if (lpChar)
	{

		wpDamage[0] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0];
		wpDamage[1] = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1];

		point = (1 + petType) << 8;
		point |= SKILL_PLAY_PET_ATTACK2;
		cnt = dm_SendTransDamage(lpChar, wpDamage[0], wpDamage[1], 0, 0, point, FALSE);
		DamageExp(lpChar, cnt);

		return cnt;
	}
	return FALSE;
}




int	SendItemExpress(DWORD	dwItemCode, char* szPassCode)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory((char*)&smTransCommand, sizeof(smTRANS_COMMAND));
	smTransCommand.code = OpCode::OPCODE_ITEM_EXPRESS;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwItemCode;

	if (szPassCode)
		smTransCommand.LParam = GetSpeedSum(szPassCode);

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendItemExpress(DWORD	dwItemCode)
{
	return	SendItemExpress(dwItemCode, 0);
}



int SendClanYahooMotion()
{
	smTRANS_COMMAND	smTransCommand;
	SocketData* lpsmSock;

	if (lpCurPlayer->smCharInfo.ClassClan)
	{
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_YAHOO_MOTION;
		smTransCommand.WParam = dwPlayTime;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		lpsmSock = GetAreaServerSock();
		if (lpsmSock)
			lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

		return TRUE;

	}
	return FALSE;
}


int	SendStarPointToServer(int Price, int Cash)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_STARPOINT;
	smTransCommand.WParam = Price;
	smTransCommand.LParam = Cash;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendGiveMoneyToServer(int Money)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_GIVEMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}


int	SendClanMoneyToServer(int Money, int Flag, int Kind)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CLANMONEY;
	smTransCommand.WParam = Money;
	smTransCommand.LParam = Flag;
	smTransCommand.SParam = Kind;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}

int	SendClanMoneyToServer(int Money, int Flag)
{
	return	SendClanMoneyToServer(Money, Flag, 0);
}


int	SendPaymentMoneyToServer(int Money, int Flag)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_PAYMENT_MONEY;
	smTransCommand.WParam = Flag;
	smTransCommand.LParam = Money;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}







int	Send_ShowMyShopItem(smCHAR * lpChar)
{
	smTRANS_COMMAND	smTransCommand;
	int	result;
	SocketData* lpsmSock;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_CALL_MYSHOP;
	smTransCommand.WParam = 0;
	smTransCommand.LParam = lpChar->dwObjectSerial;
	smTransCommand.SParam = lpCurPlayer->dwObjectSerial;
	smTransCommand.EParam = 0;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return result;
}


int	Send_MyShopItemList(smTRANS_COMMAND * lpTransCommand)
{
	int	result;
	SocketData* lpsmSock;

	TransTradeItems_MyShop.dwRecver = lpTransCommand->SParam;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char*)&TransTradeItems_MyShop, TransTradeItems_MyShop.size, TRUE);

	return result;
}



int	Recv_MyShopItemList(TRANS_TRADEITEMS * lpTransTradeItems)
{
	sMYSHOP MyShopItem;
	smCHAR* lpChar;


	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE*)&MyShopItem);


	cCharShop.RecvShopItem(&MyShopItem);


	lpChar = FindAutoPlayer(lpTransTradeItems->dwSender);

	if (lpChar && lpChar->DisplayFlag && lpChar->smCharInfo.szName[0])
	{
		OpenEachPlayer(lpChar);
		DispEachMode = TRUE;
	}

	return TRUE;
}



int	Send_PersonalShopItem(DWORD dwCharCode, void* lpShopItem)
{
	smTRANS_COMMAND_BUFF	smtBuff;


	smtBuff.smTransCommand.code = OpCode::OPCODE_MYSHOP_TRADE;
	smtBuff.smTransCommand.size = sizeof(smTRANS_COMMAND) + sizeof(sMYSHOP_ITEM_SERVER);
	smtBuff.smTransCommand.WParam = 0;
	smtBuff.smTransCommand.LParam = dwCharCode;
	smtBuff.smTransCommand.SParam = lpCurPlayer->dwObjectSerial;
	smtBuff.smTransCommand.EParam = 0;

	memcpy(smtBuff.Buff, lpShopItem, sizeof(sMYSHOP_ITEM_SERVER));

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smtBuff, smtBuff.smTransCommand.size, TRUE);

	return FALSE;
}


int	UpdateMyShopList(void* lpMyShop)
{
	sMYSHOP* lpMyShopItem = (sMYSHOP*)lpMyShop;
	int	result = 0;
	int		len;

	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));


	len = EecodeCompress((BYTE*)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems_MyShop.code = OpCode::OPCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;

	return TRUE;
}


int SendOpenPersonalTrade(char* szTradeMsg, void* lpPersTrade)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	SocketData* lpsmSock;
	int	result = 0;
	DWORD	dwCode;
	sMYSHOP* lpMyShopItem = (sMYSHOP*)lpPersTrade;
	int		len;




	ZeroMemory(&TransTradeItems_MyShop, sizeof(TRANS_TRADEITEMS));


	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));


	len = EecodeCompress((BYTE*)lpMyShopItem, TransTradeItems_MyShop.TradeBuff, sizeof(sMYSHOP));
	if (len > TRANS_TRADE_BUFF_SIZE) return FALSE;

	TransTradeItems_MyShop.code = OpCode::OPCODE_MYSHOP_ITEM;
	TransTradeItems_MyShop.size = len + 48;
	TransTradeItems_MyShop.dwSum = 0;
	TransTradeItems_MyShop.dwSender = lpCurPlayer->dwObjectSerial;
	TransTradeItems_MyShop.dwRecver = 0;
	TransTradeItems_MyShop.Temp[0] = 0;
	TransTradeItems_MyShop.Temp[1] = 0;
	TransTradeItems_MyShop.Temp[2] = 0;
	TransTradeItems_MyShop.Temp[3] = 0;


	TransChatMessage.code = OpCode::OPCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	strcpy_s(TransChatMessage.szMessage, szTradeMsg);

	dwCode = GetSpeedSum(szTradeMsg);
	TransChatMessage.dwIP = dwCode;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)




		result = lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	if (result)
	{

		wsprintf(lpCurPlayer->szTradeMessage, "%s: %s", lpCurPlayer->smCharInfo.szName, szTradeMsg);
		lpCurPlayer->dwTradeMsgCode = dwCode;
	}

	return result;
}


int SendClosePersonalTrade()
{
	TRANS_CHATMESSAGE	TransChatMessage;
	SocketData* lpsmSock;
	int	result = 0;

	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = OpCode::OPCODE_OPEN_MYSHOP;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	lpCurPlayer->dwTradeMsgCode = 0;
	lpCurPlayer->szTradeMessage[0] = 0;

	return result;
}


int SendsServerDoc(char* szTradeMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	SocketData* lpsmSock;
	int	result = 0;


	ZeroMemory(&TransChatMessage, sizeof(TRANS_CHATMESSAGE));

	TransChatMessage.code = OpCode::OPCODE_ITEMDOC;
	TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
	strcpy_s(TransChatMessage.szMessage, szTradeMsg);

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return result;
}



int DeleteEventItem_TimeOut(sITEMINFO * lpsItem)
{

	struct	tm	tm;
	time_t		ttm;
	DWORD		dwCreateTime;

	DWORD		dwItemCode;

	dwItemCode = lpsItem->CODE & sinITEM_MASK2;

	DWORD NowTime = GetPlayTime_T();

	if (lpsItem->CODE == (sinCA1 | sin01) || lpsItem->CODE == (sinCA1 | sin02) || lpsItem->CODE == (sinCA1 | sin03) ||
		lpsItem->CODE == (sinCA1 | sin04) || lpsItem->CODE == (sinCA1 | sin05) || lpsItem->CODE == (sinCA1 | sin06) ||
		lpsItem->CODE == (sinCA1 | sin08) || lpsItem->CODE == (sinCA1 | sin09) ||
		lpsItem->CODE == (sinCA1 | sin10) || lpsItem->CODE == (sinCA1 | sin11) || lpsItem->CODE == (sinCA1 | sin12) ||
		lpsItem->CODE == (sinCA2 | sin01) || lpsItem->CODE == (sinCA2 | sin02) || lpsItem->CODE == (sinCA2 | sin03) ||
		lpsItem->CODE == (sinCA2 | sin04) || lpsItem->CODE == (sinCA2 | sin05) || lpsItem->CODE == (sinCA2 | sin06) ||
		lpsItem->CODE == (sinCA2 | sin08) || lpsItem->CODE == (sinCA2 | sin09) ||
		lpsItem->CODE == (sinDB1 | sin33) || lpsItem->CODE == (sinDS1 | sin33) ||
		lpsItem->CODE == (sinOA2 | sin32) || lpsItem->CODE == (sinOR2 | sin50) ||
		lpsItem->CODE == (sinOR2 | sin53) || lpsItem->CODE == (sinOA1 | sin50) ||
		lpsItem->CODE == (sinCA2 | sin10) || lpsItem->CODE == (sinCA2 | sin11) || lpsItem->CODE == (sinCA2 | sin12))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 24 * 7) < NowTime)
			return TRUE;
	}

	if (lpsItem->CODE == (sinCA1 | sin07) || lpsItem->CODE == (sinCA2 | sin07))
	{
		if (lpsItem->dwCreateTime + (60 * 60 * 23) < NowTime)
			return TRUE;
	}

	if (lpsItem->CODE == (sinBI2 | sin81))
	{
		if (lpsItem->dwCreateTime + (60 * 30) < NowTime)
			return TRUE;
	}


	if (lpsItem->CODE != (sinOR2 | sin01) &&
		dwItemCode != sinPZ1 && dwItemCode != sinPZ2)
		return FALSE;

#ifdef _LANGUAGE_THAI_DELETE_RING
	if (lpsItem->CODE == (sinOR2 | sin01)) return TRUE;
#endif

	tm.tm_year = 2020 - 1900;
	tm.tm_mon = 4 - 1;
	tm.tm_mday = 1;
	tm.tm_hour = 15;
	tm.tm_min = 30;
	tm.tm_sec = 0;
	ttm = mktime(&tm);

	dwCreateTime = (DWORD)ttm;

	if (lpsItem->dwCreateTime < dwCreateTime) return TRUE;

	return FALSE;
}

int RecvSodGameInfomation(void* Info)
{
	smTRANS_COMMAND_SOD* lpTransCommand = (smTRANS_COMMAND_SOD*)Info;

	if (!BellatraEffectInitFlag)
	{
		CreateBellatraFontEffect();
		BellatraEffectInitFlag = TRUE;
	}

	switch (lpTransCommand->smTransCommand.WParam)
	{
	case 1:
		if (SoD_SetFontEffect.eBL_Type == E_BL_LODING)
		{
			CheckBellatraFontEffect(&SoD_SetFontEffect, TRUE);
		}

		if (lpTransCommand->smTransCommand.SParam < 0)
		{


			sSodScore.EffectStartCount = 70 * 3;
			sSodScore.EffectCode = lpTransCommand->smTransCommand.LParam + 1;
		}
		else
		{
			if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

			sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
			sSodScore.dwSoD_NextStageTime = dwPlayTime + 9000;
			sSodScore.dwSoD_CloseStageTime = dwPlayTime + 5000;
			sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

			StopBGM();
			esPlayContSound(14);
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO);

			SetBellatraFontEffect(E_BL_FONT_STAGE);
			SetBellatraFontEffect(E_BL_FONT_COMPLETE);
			SoDGateFlag = TRUE;
		}
		break;

	case 3:

		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

		sSodScore.SodNextStageNum = -1;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 8000;
		sSodScore.dwSoD_CloseStageTime = dwPlayTime + 6000;
		sSodScore.NextRound = -1;

		StopBGM();
		esPlayContSound(15);

		SetBellatraFontEffect(E_BL_FONT_STAGE);
		SetBellatraFontEffect(E_BL_FONT_FAIL);
		SoDGateFlag = TRUE;
		break;

	case 4:

		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD) break;

		sSodScore.SodNextStageNum = lpTransCommand->smTransCommand.SParam;
		sSodScore.dwSoD_NextStageTime = dwPlayTime + 7000;
		sSodScore.NextRound = lpTransCommand->smTransCommand.LParam + 1;

		StopBGM();
		esPlayContSound(16);
		lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_YAHOO);


		SetBellatraFontEffect(E_BL_FONT_CON);
		SoDGateFlag = FALSE;


		char szBuff[128];
		wsprintf(szBuff, mgSOD_Clear, lpTransCommand->smTransCommand.EParam);
		cMessageBox.ShowMessageEvent(szBuff);

		break;

	case 2:

		if (lpTransCommand->smTransCommand.LParam)
		{

			sSodScore.ScoreEffectCount = 255;

		}
		else
		{



		}

		if (!sSodScore.dwSoD_NextStageTime)
		{
			if (sSodScore.Round != lpTransCommand->smTransCommand.SParam)
			{
				switch (lpTransCommand->smTransCommand.SParam)
				{
				case 1:
					sSodScore.dwPlayTime = dwPlayTime;
					PlayBGM_Direct(BGM_CODE_SOD1);
					break;

				case 4:
					PlayBGM_Direct(BGM_CODE_SOD2);
					break;

				case 7:
					PlayBGM_Direct(BGM_CODE_SOD3);
					break;
				}
			}
			sSodScore.Round = lpTransCommand->smTransCommand.SParam;
		}

		sSodScore.dwDispTime = dwPlayTime + 10 * 1000;
		sSodScore.MyTeam = lpTransCommand->MyTeam;
		sSodScore.Score = lpTransCommand->MyScore;
		sSodScore.TeamScore[0] = lpTransCommand->TeamScore[0];
		sSodScore.TeamScore[1] = lpTransCommand->TeamScore[1];
		sSodScore.TeamScore[2] = lpTransCommand->TeamScore[2];
		sSodScore.TeamScore[3] = lpTransCommand->TeamScore[3];

		break;

	case smCODE_SOD_EFFECT:
		if (!BellatraEffectInitFlag)
		{
			CreateBellatraFontEffect();
			BellatraEffectInitFlag = TRUE;
		}
		SetBellatraFontEffect((EBL_FontEffectType)lpTransCommand->smTransCommand.LParam);
		break;

	}

	return TRUE;
}


int RecvForceOrbItem(TRANS_ITEMINFO_GROUP2 * lpTransItemGroup2)
{
	TRANS_ITEMINFO_GROUP	TransItemGroup;

	ZeroMemory(&TransItemGroup, sizeof(TRANS_ITEMINFO_GROUP));
	memcpy(&TransItemGroup, lpTransItemGroup2, TRANS_GROUPITEM_HEADER_SIZE);

	DecodeCompress((BYTE*)lpTransItemGroup2->szBuff, (BYTE*)TransItemGroup.sItemInfo, sizeof(sITEMINFO) * TRANS_GROUPITEM_MAX);



	sinRecvForceOrb(TransItemGroup.sItemInfo, TransItemGroup.ItemCount);


	return TRUE;
}


int SendQuestCommandToServer(DWORD dwQuestCode, int Param1, int Param2, int Param3)
{

	smTRANS_COMMAND	smTransCommand;
	int	result = 0;
	SocketData* lpsmSock;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = Param3;

	if (dwQuestCode >= HAQUEST_CODE_ELEMENTARY_A && dwQuestCode <= HAQUEST_CODE_FURYOFPHANTOM)
	{
		lpsmSock = smWsockDataServer;
		if (lpsmSock)
			result = lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

		return result;
	}

	lpsmSock = smWsockServer;
	if (lpsmSock)
		result = lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return result;
}


int Start_QuestArena(DWORD dwQuestCode, int Param1, int Param2)
{
	smTRANS_COMMAND	smTransCommand;
	int	result = 0;
	SocketData* lpsmSock;



	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_QUEST_COMMAND;
	smTransCommand.WParam = dwQuestCode;
	smTransCommand.LParam = QUEST_ARENA_FIELD;
	smTransCommand.SParam = Param1;
	smTransCommand.EParam = Param2;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		result = lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	if (result)
		WarpField2(QUEST_ARENA_FIELD);



	return FALSE;
}


int	SendBlessCastleToServer(smTRANS_BLESSCASTLE * lpBlessCastleSetup, int Mode)
{
	SocketData* lpsmSock;

	lpBlessCastleSetup->smTransCommand.size = sizeof(smTRANS_BLESSCASTLE);
	lpBlessCastleSetup->smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_INFO;
	lpBlessCastleSetup->smTransCommand.WParam = 1;
	lpBlessCastleSetup->smTransCommand.LParam = Mode;
	lpBlessCastleSetup->smTransCommand.SParam = 0;
	lpBlessCastleSetup->smTransCommand.EParam = 0;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		return lpsmSock->Send((char*)lpBlessCastleSetup, lpBlessCastleSetup->smTransCommand.size, TRUE);

	return FALSE;
}


int	Send_GetBlessCastleTax()
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_BLESSCASTLE_INFO;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.SParam = cSinSiege.GetTaxRate();

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return FALSE;
}

int RecvBlessCastInfo(void* lpPacket)
{
	smTRANS_BLESSCASTLE* lpBlessCastleSetup = (smTRANS_BLESSCASTLE*)lpPacket;
	rsUSER_LIST_TOP10* lpClanListTop10;

	switch (lpBlessCastleSetup->smTransCommand.WParam)
	{
	case 1:
		chaSiege.ShowSiegeMenu(lpBlessCastleSetup);
		break;

	case 2:
		lpClanListTop10 = (rsUSER_LIST_TOP10*)lpPacket;

		chaSiege.ShowSiegeScore(lpClanListTop10);
		break;
	}

	return TRUE;
}


int SetBlessCastleMaster(DWORD dwClanCode, int Mode)
{

	if (!Mode && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD)
	{

	}
	else
	{
		if (rsBlessCastle.dwMasterClan != dwClanCode)
		{

			UpdateCastleMasterClan(rsBlessCastle.dwMasterClan);
		}

		rsBlessCastle.dwMasterClan = dwClanCode;
	}

	return TRUE;
}


int	SendResistanceToServer()
{
	smTRANS_RESISTANCE	smTransResistance;
	SocketData* lpsmSock;

	dwResistance_SendingTime = dwPlayTime;

	smTransResistance.code = OpCode::OPCODE_RESISTANCE;
	smTransResistance.size = sizeof(smTRANS_RESISTANCE);
	smTransResistance.Param = 0;
	memcpy(smTransResistance.Resistance, lpCurPlayer->smCharInfo.Resistance, sizeof(short) * 8);
	smTransResistance.Absorb = lpCurPlayer->smCharInfo.Absorption;

	lpsmSock = GetAreaServerSock();
	if (lpsmSock)
		return lpsmSock->Send((char*)&smTransResistance, smTransResistance.size, TRUE);

	return FALSE;
}


int	SendPublicPollingToServer(int PollCode, int PollCnt, BYTE * bPollingData)
{
	smTRANS_COMMAND_POLLING	smTransPolling;

	ZeroMemory(&smTransPolling, sizeof(smTRANS_COMMAND_POLLING));

	smTransPolling.smTransCommand.code = OpCode::OPCODE_PUBLIC_POLLING;
	smTransPolling.smTransCommand.size = sizeof(smTRANS_COMMAND_POLLING);
	smTransPolling.smTransCommand.WParam = PollCode;
	smTransPolling.smTransCommand.LParam = PollCnt;
	memcpy(smTransPolling.bPolling, bPollingData, PollCnt);

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&smTransPolling, smTransPolling.smTransCommand.size, TRUE);


	return TRUE;
}


#ifdef _xTrap_GUARD
#include "XTrapSrc\\XTrap.h"

int XTrap_Recv(smTRANS_COMMAND * lpPacket, SocketData * lpsmSock)
{
	smTRANS_XTRAP_ADDR* lpTransXTrapAddr;
	smTRANS_XTRAP_SECURITY* lpTransXTrapSecurity;
	UCHAR KFBuf[CREATEKF_OUT_SIZE * 2] = { 0, };





	switch (lpPacket->WParam)
	{
	case smXTRAP_COMMAND_LOGIN:
		lpTransXTrapAddr = (smTRANS_XTRAP_ADDR*)lpPacket;
		lpTransXTrapSecurity = (smTRANS_XTRAP_SECURITY*)lpPacket;

		CreateKFEx(NULL, (PUCHAR)lpTransXTrapAddr->Addr, 2, KFBuf);

		lpTransXTrapSecurity->smTransCommand.size = sizeof(smTRANS_XTRAP_SECURITY);
		lpTransXTrapSecurity->smTransCommand.code = OpCode::OPCODE_XTRAP_PACKET;
		lpTransXTrapSecurity->smTransCommand.WParam = smXTRAP_COMMAND_SECURITY;
		memcpy(&lpTransXTrapSecurity->serialkey, KFBuf, CREATEKF_OUT_SIZE * 2);
		lpsmSock->Send((char*)lpTransXTrapSecurity, lpTransXTrapSecurity->smTransCommand.size, TRUE);

		break;

	case smXTRAP_COMMAND_SECURITY:
		if (lpPacket->LParam == 0) SendLogToMgr();
		DisconnectServerCode = 4;
		//LOG(LOG_DEBUG, "SetDisconnectFlag: 30");
		//LOG(LOG_SERVER, "SetDisconnectFlag: 30");
		DisconnectFlag = GetCurrentTime();
		break;

	}
	return TRUE;
};
#else
#ifdef _XTRAP_GUARD_4_CLIENT
#include "XTrapSrcD5\Client\XTrap4Client.h"	


int XTrap_Recv(smTRANS_COMMAND * lpPacket, SocketData * lpsmSock)
{
	char debug[512];
	smTRANS_XTRAP_ADDR* lpTransXTrapAddr = (smTRANS_XTRAP_ADDR*)lpPacket;

	sprintf(debug, "XTrap_Recv");
	OutputDebugString(debug);

	if (lpPacket->WParam == XTRAP_CMD_SEEDKEY)
	{
		sprintf(debug, "CMD_SEEDKEY");
		OutputDebugString(debug);

		sprintf(debug, "before : Packet Buf: %02X %02X %02X %02X %02X %02X",
			lpTransXTrapAddr->PacketBuf[0],
			lpTransXTrapAddr->PacketBuf[1],
			lpTransXTrapAddr->PacketBuf[2],
			lpTransXTrapAddr->PacketBuf[3],
			lpTransXTrapAddr->PacketBuf[4],
			lpTransXTrapAddr->PacketBuf[5]);
		OutputDebugString(debug);


		smTRANS_XTRAP_ADDR	smTransXTrapAddr;
		memset(&smTransXTrapAddr, 0, sizeof(smTransXTrapAddr));

		unsigned int usResult = 1;

		usResult = XTrap_CS_Step2((PUCHAR)lpTransXTrapAddr->PacketBuf, (PUCHAR)smTransXTrapAddr.PacketBuf,
			XTRAP_PROTECT_PE | XTRAP_PROTECT_TEXT | XTRAP_PROTECT_EXCEPT_VIRUS);


		smTransXTrapAddr.smTransCommand.size = sizeof(smTRANS_XTRAP_ADDR);
		smTransXTrapAddr.smTransCommand.code = OpCode::OPCODE_XTRAP_PACKET;
		smTransXTrapAddr.smTransCommand.WParam = XTRAP_CMD_UNIQKEY;

		if (smWsockDataServer)
			smWsockDataServer->Send((char*)&smTransXTrapAddr, smTransXTrapAddr.smTransCommand.size, TRUE);


		if (usResult == 0)
		{
		}
		else
		{
			DisconnectServerCode = 4;
			//LOG(LOG_DEBUG, "SetDisconnectFlag: 31");
			//LOG(LOG_SERVER, "SetDisconnectFlag: 31");
			DisconnectFlag = GetCurrentTime();
		}

		sprintf(debug, "after : Packet Buf: %02X %02X %02X %02X %02X %02X",
			lpTransXTrapAddr->PacketBuf[0],
			lpTransXTrapAddr->PacketBuf[1],
			lpTransXTrapAddr->PacketBuf[2],
			lpTransXTrapAddr->PacketBuf[3],
			lpTransXTrapAddr->PacketBuf[4],
			lpTransXTrapAddr->PacketBuf[5]);
		OutputDebugString(debug);

	}

	return TRUE;
};

VOID __stdcall XTrapCS_SendUniqKey(PUCHAR pUniqKey)
{
}

#else

int XTrap_Recv(smTRANS_COMMAND * lpPacket, SocketData * lpsmSock)
{
	return TRUE;
}

#endif
#endif



int	HackTrap_OpenFlagMask = 0;


int HackTrap_CheckOpenFlag()
{
	int ChkCnt = 0;


	if (cShop.OpenFlag && cShop.UseItemFlag == 0)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_SHOP) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SHOP;
			SendHackTrapToServer(100, sinNPC_SHOP);
		}
		ChkCnt++;
	}

	if (cWareHouse.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_WARE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_WARE;
			SendHackTrapToServer(100, sinNPC_WARE);
		}
		ChkCnt++;
	}
	if (cCraftItem.OpenFlag)
	{
		if (cCraftItem.ForceFlag)return false;

		if ((HackTrap_OpenFlagMask & sinNPC_MIX) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MIX;
			SendHackTrapToServer(100, sinNPC_MIX);
		}

		ChkCnt++;
	}
	if (cCraftItem.ForceFlag)
	{
		if (cCraftItem.OpenFlag)return false;

		if ((HackTrap_OpenFlagMask & sinNPC_FORCE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_FORCE;
			SendHackTrapToServer(100, sinNPC_FORCE);
		}
		ChkCnt++;
	}
	if (cAging.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_AGING) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_AGING;
			SendHackTrapToServer(100, sinNPC_AGING);
		}
		ChkCnt++;
	}


	if (SmeltingItem.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_SMELTING) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SMELTING;
			SendHackTrapToServer(100, sinNPC_SMELTING);
		}
		ChkCnt++;
	}

	if (ManufactureItem.m_OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_MANUFACTURE) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MANUFACTURE;
			SendHackTrapToServer(100, sinNPC_MANUFACTURE);
		}
		ChkCnt++;
	}


	if (cMixtureReset.OpenFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_MIXTURE_RESET) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_MIXTURE_RESET;
			SendHackTrapToServer(100, sinNPC_MIXTURE_RESET);
		}

		ChkCnt++;
	}

	if (SkillMasterFlag)
	{
		if ((HackTrap_OpenFlagMask & sinNPC_SKILL) == 0)
		{
			HackTrap_OpenFlagMask |= sinNPC_SKILL;
			SendHackTrapToServer(100, sinNPC_SKILL);
		}
		ChkCnt++;
	}

	if (!ChkCnt)
		HackTrap_OpenFlagMask = 0;

	return	TRUE;
}



int	SendHackTrapToServer(DWORD dwTrapCode, int Param)
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_HACKTRAP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = dwTrapCode;
	smTransCommand.LParam = Param;

	if (dwTrapCode == 100)
	{

		if (lpCurPlayer->OnStageField >= 0)
		{
			smTransCommand.SParam = StageField[lpCurPlayer->OnStageField]->FieldCode;
		}
		else
			return FALSE;
	}

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);


	return TRUE;
}


int SendSmeltingItemToServer(void* lpsSmeltingItem_Send)
{
	sSMELTINGITEM_SERVER* lpSmeltingItem_Send = (sSMELTINGITEM_SERVER*)lpsSmeltingItem_Send;

	lpSmeltingItem_Send->size = sizeof(sSMELTINGITEM_SERVER);
	lpSmeltingItem_Send->code = OpCode::OPCODE_SMELTINGITEM;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)lpSmeltingItem_Send, lpSmeltingItem_Send->size, TRUE);

	return FALSE;
}

int SendManufactureItemToServer(void* lpsManufactureItem_Send)
{
	SManufactureItem_Server* lpManufactureItem_Send = (SManufactureItem_Server*)lpsManufactureItem_Send;

	lpManufactureItem_Send->size = sizeof(SManufactureItem_Server);
	lpManufactureItem_Send->code = OpCode::OPCODE_MANUFACTURE;

	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)lpManufactureItem_Send, lpManufactureItem_Send->size, TRUE);

	return FALSE;
}


int SendMixtureResetItemToServer(void* lpsMixtureResetItem_Send)
{

	sMIXTURE_RESET_ITEM_SERVER* lpMixtureResetItem_Send = (sMIXTURE_RESET_ITEM_SERVER*)lpsMixtureResetItem_Send;


	lpMixtureResetItem_Send->size = sizeof(sMIXTURE_RESET_ITEM_SERVER);
	lpMixtureResetItem_Send->code = OpCode::OPCODE_MIXTURE_RESET_ITEM;


	if (smWsockDataServer)
		return smWsockDataServer->Send((char*)lpMixtureResetItem_Send, lpMixtureResetItem_Send->size, TRUE);

	return FALSE;
}

#ifdef _XIGNCODE_CLIENT


int Xigncode_Client_Start()
{
	smTRANS_COMMAND	smTransCommand;

	ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));

	smTransCommand.code = OpCode::OPCODE_XIGNCODE_START;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = TRUE;

	if (smWsockDataServer)
		smWsockDataServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}


XIGNCODE_PACKET return_packet;

int Xigncode_Client_Recv(SocketData * lpsmSock, XIGNCODE_PACKET * pack)
{

	memset(&return_packet, 0, sizeof(return_packet));

	if (ZCWAVE_Probe((char*)pack->data, (char*)return_packet.data, sizeof(return_packet.data)))
	{
		return_packet.size = sizeof(return_packet);
		return_packet.code = OpCode::OPCODE_XIGNCODE_PACKET;
		lpsmSock->Send((char*)&return_packet, return_packet.size, TRUE);
	}

	return TRUE;
}
#endif

