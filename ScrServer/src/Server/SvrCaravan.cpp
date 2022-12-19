#include "sinbaram\\sinlinkheader.h"
#include "field.h"
#include "SvrCaravan.h"
#include "onserver.h"

extern smCHAR *OpenMonsterFromName(char *szName, int x, int y, int z, rsPLAYINFO *lpPlayInfo);
extern int chrMonsterCnt;
extern smCHAR_INFO chrMonsterList[400];

CCaravanaHandler cCaravanaHandler;

CCaravanaHandler * CCaravanaHandler::getInstance()
{
	return &cCaravanaHandler;
}

void CCaravanaHandler::StartPremium(rsPLAYINFO * lpPlayInfo, DWORD dwTime)
{
	smTRANS_COMMAND sPacket;
	sPacket.code = START_CARAVAN;
	sPacket.size = sizeof(sPacket);
	sPacket.WParam = lpPlayInfo->dwTime_PrimeItem_Caravan = dwTime;
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);

	AddCaravan(lpPlayInfo);
}

void CCaravanaHandler::AddCaravan(rsPLAYINFO* lpPlayInfo)
{
	if (lpPlayInfo->Position.Area < 0 ||
		lpPlayInfo->Position.Area > STAGE_AREA_MAX ||
		lpPlayInfo->Position.Area == rsCASTLE_FIELD)
		return;


	STG_CHAR_INFO StgCharInfo;
	STG_AREA* lpStgArea = &StageArea[lpPlayInfo->Position.Area];
	StgCharInfo.PosiState = smCHAR_STATE_NPC;
	StgCharInfo.smCharInfo.Life[0] = 100;
	StgCharInfo.smCharInfo.Mana[0] = 100;
	StgCharInfo.smCharInfo.Life[1] = 100;
	StgCharInfo.smCharInfo.State = TRUE;

	for (int cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if (lstrcmp(chrMonsterList[cnt].szName, "Caravana") == 0)
		{
			memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
			break;
		}
	}

	lpStgArea->EvnMonster = TRUE;
	smCHAR* lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
	if (lpChar)
	{
		lpChar->pX = lpPlayInfo->Position.x;
		lpChar->pY = lpPlayInfo->Position.y;
		lpChar->pZ = lpPlayInfo->Position.z;
		lpChar->DistAroundDbl = 0;
		lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
		lpChar->TargetMoveCount = 0;
		lpChar->lpMasterPlayInfo = lpPlayInfo;
		lpChar->smMonsterInfo.dwAutoCharCode = 0;
		lpChar->HoSkillCode = -1;
		lpChar->HoSkillMode = 0;
		lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
		lpChar->smCharInfo.State = smCHAR_STATE_NPC;
		wsprintf(lpChar->smCharInfo.szName, "Caravana de %s", lpPlayInfo->getName().c_str());
		lstrcpy(lpChar->smCharInfo.szModelName2 + 1, lpPlayInfo->smCharInfo.szName);
		lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;
		lpChar->dwUpdateCharInfoTime = 0;

		lpPlayInfo->lpLinkChar = lpChar;
		lpPlayInfo->lpCharCaravan = lpChar;
		lpPlayInfo->dwCaravanCode = lpChar->dwObjectSerial;
		lpChar->Clan_CastleMasterFlag = FALSE;
	}
}

void CCaravanaHandler::DelCaravan(smCHAR* lpChar)
{
	rsPLAYINFO* lpPlayInfo = lpChar->lpMasterPlayInfo;
	STG_AREA* lpStgArea = (STG_AREA*)lpChar->lpExt1;
	if (lpPlayInfo->lpsmSock)
	{
		lpChar->Close();
		lpStgArea->MonsterCount--;
		lpStgArea->DeleteMonTable(lpChar);
		lpPlayInfo->lpCharCaravan = 0;
		lpPlayInfo->dwCaravanCode = 0;
	}
}
