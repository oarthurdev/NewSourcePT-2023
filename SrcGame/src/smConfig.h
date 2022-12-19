#pragma once

#include <Windows.h>
#include "smLib3d/smType.h"

struct PowerUser
{
	AccountTypes sec;
	bool auth;

	PowerUser()
	{
		sec = AccountTypes::SEC_PLAYER;
		auth = false;
	}
};

//¡¾a¨¬¡í ¨ù©øA¢´ ¡¾¢¬A¢ÒA¨ù
struct smCONFIG {

	int	WinMode;					//E¡©¢¬e ¢¬©£¥ìa
	POINT	ScreenSize;					//E¡©¢¬e C¨ª¡ío¥ì¥ì
	DWORD	ScreenColorBit;				//¡ío¡ío ¨¬n¨¡¢ç


	int		TextureQuality;				//A¨ª¨ö¨¬AA C¡ÆAu
	int		BGM_Mode;					//©öe¡Æ©¡ A¨ö¨úC ¡íc¢¯e 
	int		NetworkQuality;				//©ø¡¿¨¡¢ç¢¯oA¨Ï C¡ÆAu
	int		WeatherSwitch;				// pluto C¨ª¢¯U ¨¬n

	char	szFile_BackGround[2][64];	//©öe¡Æ©¡ E¡©¢¬e
	char	szFile_Menu[64];			//¢¬¨­¢¥¨¬ E¡©¢¬e
	char	szFile_Player[64];			// AOAI¡Æ©ª
	POINT	Posi_Player;
	char	szFile_Enemy[64];			// ©ø¨£¡íU©ø©£
	POINT	Posi_Enemy;

	char	szFile_Stage[64];				//AoCu
	POINT	Posi_Stage;						//AoCu ¨öAAU A¡×A¢®
	char	szFile_StageObject[100][64];	//AoCu¢¯¢® ¢¯A¢Òo¡Æ¢®¢¥A ¢¯A¨¬eA¡×¨¡¢ç
	int		StageObjCnt;					//AoCu ¢¯A¨¬eA¡×¨¡¢ç ¡Æ©ö¨ùo

	//######################################################################################
	//AU ¨ù¨¬ AU : ¢¯A ¢¯¥ì ¨ù¢ç
	int		IsStageAniObject[100];
	//######################################################################################

	//¨öA¡¾O ¢¬E ¨¬O¡¤? ¢¯A¢Ò¡×¢¬¢¬ Au¢¯e¥ìE
	int		MapBright;						//©öa¡¾a
	int		MapContrast;					//¨ù¡¾¢¬i¥ì¥ì
	POINT3D	MapLightVector;					//¨¬¢´AI

	char	szServerIP[32];					//¨ù¡©©öoAO¨ùO
	DWORD	dwServerPort;					//¨ù¡©©öo¨¡¡À¨¡¢ç
	char	szDataServerIP[32];				//¥ì¡ÍAIA¢¬ ¨ù¡©©öoAO¨ùO
	DWORD	dwDataServerPort;				//¥ì¡ÍAIA¢¬ ¨ù¡©©öo¨¡¡À¨¡¢ç
	char	szUserServerIP[32];				//A?Au ¨ù¡©©öoAO¨ùO
	DWORD	dwUserServerPort;				//A?Au ¨ù¡©©öo¨¡¡À¨¡¢ç
	char	szExtendServerIP[32];			//E¢çAa ¨ù¡©©öoAO¨ùO
	DWORD	dwExtendServerPort;				//E¢çAa ¨ù¡©©öo¨¡¡À¨¡¢ç

	DWORD	DebugMode;						//¥ì©£©öo¡¾e ¢¬©£¥ìa ¨ù©øA¢´


	char	szCmdOpenMonster[CONFIG_KEY_MONSTER_MAX][32];		//¡íy¨ù¨¬¨öAA©ø ¢¬o¨ö¨¬AI AI¢¬¡×
	int		CmdMonsterCount;
	PowerUser security;

	void setSecurity(AccountTypes security)
	{
		this->security.sec = security;
	}

	AccountTypes getSecurity() const
	{
		return this->security.sec;
	}

	void setSecurityAuth(bool value)
	{
		this->security.auth = value;
	}

	bool isSecurityAuth() const
	{
		return this->security.auth;
	}

	smCONFIG()
	{
		ZeroMemory(szFile_BackGround, sizeof(szFile_BackGround));
		ZeroMemory(szFile_Menu, sizeof(szFile_Menu));
		ZeroMemory(szFile_Player, sizeof(szFile_Player));
		Posi_Player.x = 0;
		Posi_Player.y = 0;
		ZeroMemory(szFile_Enemy, sizeof(szFile_Enemy));
		Posi_Enemy.x = 0;
		Posi_Enemy.y = 0;
		ZeroMemory(szFile_Stage, sizeof(szFile_Stage));
		Posi_Stage.x = 0;
		Posi_Stage.y = 0;
		ZeroMemory(szFile_StageObject, sizeof(szFile_StageObject));
		StageObjCnt = 0;
		ZeroMemory(IsStageAniObject, sizeof(IsStageAniObject));
		MapBright = DEFAULT_BRIGHT;
		MapContrast = DEFAULT_CONTRAST;
		MapLightVector.x = fONE;
		MapLightVector.y = -fONE;
		MapLightVector.z = fONE / 2;
		security.sec = AccountTypes::SEC_PLAYER;
		security.auth = false;
		ZeroMemory(IsStageAniObject, sizeof(szCmdOpenMonster));
		CmdMonsterCount = 0;
	}
};
