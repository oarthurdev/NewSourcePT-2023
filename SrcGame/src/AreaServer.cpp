#include "smlib3d\\smd3d.h"
#include "character.h"
#include "Sound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"

#include "hobaram\\holinkheader.h"
#include "sinbaram\\sinlinkheader.h"

#include "effectsnd.h"
#include "playsub.h"
#include "skillsub.h"
#include "Language\\language.h"

#include "AreaServer.h"

TRANS_SEVER_MAP	TransAreaServer;
int	AreaServerMode = 0;

HANDLE	hAreaServerContol_Thread = 0;
DWORD	dwAreaServerContol_ID = 0;

CRITICAL_SECTION	cSection_Main;

SocketData* lpWSockServer_Area[2] = { 0,0 };
SocketData* lpWSockServer_DispArea[2] = { 0,0 };
SocketData* lpWSockServer_AreaTemp = 0;



int AreaSetObjectSerial(SocketData* lpsmSock)
{


	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));

	SetMaxDamage(&TransPlayerInfo.smCharInfo);

	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = OpCode::OPCODE_PLAYERINFO2;
	TransPlayerInfo.dwObjectSerial = lpCurPlayer->dwObjectSerial;

	TransPlayerInfo.x = lpCurPlayer->pX;
	TransPlayerInfo.y = lpCurPlayer->pY;
	TransPlayerInfo.z = lpCurPlayer->pZ;

	lpsmSock->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);

	return TRUE;
}


DWORD	dwDebugAreaIP[4];
DWORD	dwDebugAreaCount = 0;
DWORD	dwDebugAreaConnCount = 0;
DWORD	dwDebugAreaStep = 0;

DWORD WINAPI AreaServer_ControlThread(void* pInfo)
{
	/*HANDLE	hThread;
	DWORD	dwTime;


	DWORD	dwSvrIP[2];
	int		SvrCode;
	DWORD	dwIP, dwIP_Back;

	int		MainStageNum;
	int		BackStageNum;
	char	szBuff[256];
	char	*lpBuff;
	int		Counter = 0;
	sFIELD	*StgField[2];

	SocketData	*lpsmSock;


	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();

	while(1)
	{

		dwDebugAreaStep = 1;

		Sleep(1000);

		dwDebugAreaStep = 2;

		if(quit) break;

		StgField[0] = StageField[0];
		StgField[1] = StageField[1];
		if(!StgField[0]) StgField[0] = StgField[1];
		if(!StgField[1]) StgField[1] = StgField[0];

		dwDebugAreaStep = 3;

		if(lpCurPlayer->OnStageField >= 0 && StgField[0] && StgField[1])
		{

			dwDebugAreaStep = 4;

			EnterCriticalSection(&cSection_Main);

			dwDebugAreaStep = 5;

			MainStageNum = Counter & 1;
			BackStageNum = (Counter + 1) & 1;

			SvrCode = StgField[MainStageNum]->FieldCode;
			dwIP = TransAreaServer.dwIP[SvrCode];

			dwIP_Back = TransAreaServer.dwIP[StgField[BackStageNum]->FieldCode];

			if(lpWSockServer_Area[0]) dwSvrIP[0] = lpWSockServer_Area[0]->lIP;
			else dwSvrIP[0] = 0;

			if(lpWSockServer_Area[1]) dwSvrIP[1] = lpWSockServer_Area[1]->lIP;
			else dwSvrIP[1] = 0;

			dwDebugAreaStep = 6;

			if(dwSvrIP[0])
			{
				if(dwSvrIP[0] != dwIP && dwSvrIP[0] != dwIP_Back)
				{
					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						wsprintf(szBuff, "Area shutdown server (%s)", lpWSockServer_Area[0]->szIP);
						AddChatBuff(szBuff, 0);
					}

					lpWSockServer_Area[0]->CloseSocket();
					lpWSockServer_Area[0] = 0;
					dwSvrIP[0] = 0;
				}
			}

			if(dwSvrIP[1])
			{
				if(dwSvrIP[1] != dwIP && dwSvrIP[1] != dwIP_Back)
				{
					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						wsprintf(szBuff, "Area shutdown server (%s)", lpWSockServer_Area[1]->szIP);
						AddChatBuff(szBuff, 0);
					}

					lpWSockServer_Area[1]->CloseSocket();
					lpWSockServer_Area[1] = 0;
					dwSvrIP[1] = 0;
				}
			}


			dwDebugAreaStep = 7;

			dwDebugAreaIP[0] = dwIP;
			dwDebugAreaIP[1] = dwSvrIP[0];
			dwDebugAreaIP[2] = dwSvrIP[1];

			LeaveCriticalSection(&cSection_Main);

			dwDebugAreaStep = 8;

			if(dwIP != dwSvrIP[0] && dwIP != dwSvrIP[1])
			{


				dwDebugAreaStep = 9;

				dwDebugAreaConnCount++;

				lpBuff = ConvStrIP(dwIP);
				lpWSockServer_AreaTemp = smConnectSock3(lpBuff, HOST_PORT);


				dwDebugAreaStep = 10;

				if(quit) break;


				dwDebugAreaStep = 11;

				if(lpWSockServer_AreaTemp)
				{

					dwDebugAreaStep = 12;

					EnterCriticalSection(&cSection_Main);

					dwDebugAreaStep = 13;

					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						wsprintf(szBuff, "Region Server Connection (%s)", lpBuff);
						AddChatBuff(szBuff, 0);
					}


					lpsmSock = lpWSockServer_Area[MainStageNum];
					lpWSockServer_Area[MainStageNum] = lpWSockServer_AreaTemp;

					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						wsprintf(szBuff, "Local server settings (%d)", MainStageNum);
						AddChatBuff(szBuff, 0);
					}

					dwDebugAreaStep = 14;



					AreaSetObjectSerial(lpWSockServer_AreaTemp);


					dwDebugAreaStep = 15;

					if(lpsmSock)
					{
						if(!lpWSockServer_Area[BackStageNum])
						{
							lpWSockServer_Area[BackStageNum] = lpsmSock;
						}
						else
						{
							if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
							{
								wsprintf(szBuff, "지역서버 종료 (%s)", lpsmSock->szIP);
								AddChatBuff(szBuff, 0);
							}

							lpsmSock->CloseSocket();
						}
					}
					lpWSockServer_AreaTemp = 0;

					dwDebugAreaStep = 16;

					LeaveCriticalSection(&cSection_Main);
				}
				else
				{
					dwDebugAreaStep = 17;

					EnterCriticalSection(&cSection_Main);

					dwDebugAreaStep = 18;

					if(smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						wsprintf(szBuff, "지역서버 연결실패 (%s)", lpBuff);
						AddChatBuff(szBuff, 0);
					}
					LeaveCriticalSection(&cSection_Main);

					dwDebugAreaStep = 19;

				}
			}

			dwDebugAreaCount++;

			dwDebugAreaStep = 20;

			EnterCriticalSection(&cSection_Main);

			dwDebugAreaStep = 21;

			if(dwIP && dwIP == dwIP_Back)
			{
				if(lpWSockServer_Area[0] && lpWSockServer_Area[0]->lIP == dwIP)
				{
					lpWSockServer_DispArea[0] = lpWSockServer_Area[0];
					lpWSockServer_DispArea[1] = lpWSockServer_Area[0];
				}
				if(lpWSockServer_Area[1] && lpWSockServer_Area[1]->lIP == dwIP)
				{
					lpWSockServer_DispArea[0] = lpWSockServer_Area[1];
					lpWSockServer_DispArea[1] = lpWSockServer_Area[1];
				}
			}
			else
			{
				lpWSockServer_DispArea[0] = lpWSockServer_Area[0];
				lpWSockServer_DispArea[1] = lpWSockServer_Area[1];
			}

			dwDebugAreaStep = 22;

			LeaveCriticalSection(&cSection_Main);

			dwDebugAreaStep = 23;

		}


		dwDebugAreaStep = 24;

		Counter++;
	}

	dwDebugAreaStep = 25;*/

	ExitThread(TRUE);
	return TRUE;
}


int RecvAreaServerMap(TRANS_SEVER_MAP* lpTransServerMap)
{
	ZeroMemory(&TransAreaServer, sizeof(TRANS_SEVER_MAP));
	memcpy(&TransAreaServer, lpTransServerMap, lpTransServerMap->size);
	AreaServerMode = TRUE;
	if (!hAreaServerContol_Thread)
		hAreaServerContol_Thread = CreateThread(NULL, 0, AreaServer_ControlThread, 0, 0, &dwAreaServerContol_ID);
	return TRUE;
}

