#include "smlib3d\\smd3d.h"
#include "SocketServer/smwsock.h"

#include "character.h"
#include "Sound\\dxwav.h"
#include "particle.h"
#include "fileread.h"
#include "playmain.h"
#include "drawsub.h"
#include "netplay.h"
#include "field.h"
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
	return 0;
}


int RecvAreaServerMap(TRANS_SEVER_MAP* lpTransServerMap)
{

	ZeroMemory(&TransAreaServer, sizeof(TRANS_SEVER_MAP));
	memcpy(&TransAreaServer, lpTransServerMap, lpTransServerMap->size);
	AreaServerMode = TRUE;

	if (!hAreaServerContol_Thread)
	{

		hAreaServerContol_Thread = CreateThread(NULL, 0, AreaServer_ControlThread, 0, 0, &dwAreaServerContol_ID);

	}


	return TRUE;
}
