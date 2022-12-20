
#include "smlib3d\\smd3d.h"
#include "cracker.h"
#include "GameSocket/smwsock.h"
#include "character.h"
#include "avictrl.h"
#include "playmain.h"
#include "Sound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "sinbaram\\sinlinkheader.h"
#include "hobaram\\holinkheader.h"

#include "field.h"
#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "Language\\language.h"

#include "damage.h"
#include "AreaServer.h"

#include "Server\onserver.h"
#include "Settings\Settings.h"
#include "DXFont.h"
#include "DXSelectGlow.h"
#include "cSkinChanger.h"
#include "CoinShop_T.h"

extern int WinSizeX;
extern int WinSizeY;
extern HWND hwnd;
extern int MouseButton[3];


int LoadFieldMap(int PosNum, sFIELD* lpField, smSTAGE3D* lpStage);



smSTAGE3D* smStage = 0;
smSTAGE3D* smGameStage[2] = { 0,0 };
sFIELD* StageField[2] = { 0,0 };


rsRECORD_DBASE	rsRecorder;

char szGameStageName[2][64];
DWORD			dwPlayTime = 0;
DWORD			dwMemError = 8080;

int	smStageCount = 0;
int SkipNextField = 0;

int	NightDayTime = 0;

int invPlayerArmor = 0;

DWORD	dwBattleTime = 0;
DWORD	dwBattleQuitTime = 0;
DWORD	dwCloseBoxTime = 0;

int		RestartPlayCount = 0;

DWORD SkillFalconPoint;

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;
int	BackColor_R = 0;
int	BackColor_G = 0;
int	BackColor_B = 0;

int	BackColor_mR = 0;
int	BackColor_mG = 0;
int	BackColor_mB = 0;

int	DarkLevel_Fix = 0;

int	DarkLightRange = 180 * fONE;

DWORD	dwGameWorldTime = 0;
DWORD	dwGameHour = 12;
DWORD	dwGameMin = 0;
DWORD	dwGameTimeOffset = 0;

int DarkLight = 0;


int WeatherMode = 0;
int Thunder = 0;


int	PkMode = 0;

int DispApp_SkillPoint = 0;

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;

int	RecordFailCount = 0;


int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;



DWORD	AutoMouse_LastCheckTime = 0;
DWORD	AutoMouse_StartCheckTime = 0;
int		AutoMouse_WM_Count = 0;
int 	AutoMouse_Distance = 0;
int		AutoMouse_Attack_Count = 0;





smPAT3D* PatArrow;

smPAT3D* PatEffectShield = 0;

smPAT3D* PatSparkShield = 0;

smPAT3D* PatDivineShield = 0;

smPAT3D* PatGodlyShield = 0;

smPAT3D* PatCrown = 0;

smPAT3D* PatCrown2 = 0;

smPAT3D* PatCrown3 = 0;

smPAT3D* PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };



smPAT3D* PatIceFoot[ICE_FOOT_PAT_MAX];


int	Moving_DblClick = 0;
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;



smCHAR* lpCurPlayer = 0;

DWORD	dwRotPlayDelayTime = 0;




scITEM	scItems[DISP_ITEM_MAX];

smCHAR	chrOtherPlayer[OTHER_PLAYER_MAX];

smCHAR_INFO	smCharInfo_Back;


int	MatEachBox;
int	MatEachMenuBox;
int MatEnergyBox[2];
int MatLight[4];

int	MatEachTradeButton[2];
int MatMonBroodImage[8];


smTRANS_COMMAND	sPartyPosion;
DWORD			dwPartyPosionTime;

LPDIRECT3DTEXTURE9	lpDDS_ParTradeButton[4][2];
LPDIRECT3DTEXTURE9	lpDDS_ParTradeToolTip[4];



char* szFlame[8] = {
	"image\\flame1.bmp",
	"image\\flame2.bmp",
	"image\\flame3.bmp",
	"image\\flame4.bmp",
	"image\\flame5.bmp",
	"image\\flame6.bmp",
	"image\\flame7.bmp",
	"image\\flame8.bmp"
};

char* szShine[] = {
	"image\\shine0.bmp",
	"image\\shine2.bmp",
	"image\\shine4.bmp",
	"image\\shine6.bmp",
	"image\\shine8.bmp",
	""
};

char* szBlood1[] = {
	"image\\blood\\b1_001.tga",
	"image\\blood\\b1_002.tga",
	"image\\blood\\b1_003.tga",
	"image\\blood\\b1_004.tga"
};

char* szBlood2[] = {
	"image\\blood\\b2_001.tga",
	"image\\blood\\b2_002.tga",
	"image\\blood\\b2_003.tga",
	"image\\blood\\b2_004.tga"
};


char* szShadowImageFile = "image\\bshadow.bmp";




char* g_IceFootImageFileBuff[ICE_FOOT_PAT_MAX] =
{
	"image\\mk-r.tga",
	"image\\mk-l.tga",
};





void InitStageLoader()
{
	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;
	smGameStage[0] = 0;
	smGameStage[1] = 0;
}


smSTAGE3D* LoadStageFromField(sFIELD* lpField, sFIELD* lpSecondField)
{
	smSTAGE3D* lpstg;
	char* szStageFile;
	int cnt;
	int	Bip;
	char	szBuff[128];

	szStageFile = lpField->szName;

	if (lpField == StageField[0])
		return smGameStage[0];
	if (lpField == StageField[1])
		return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	AddLoaderStage(lpstg, szStageFile);

	if (!lpstg->StageObject)
	{


		wsprintf(szBuff, "Stage Loading Error ( %s )", szStageFile);
		Record_ClinetLogFile(szBuff);
		delete lpstg;
		return NULL;
	}


	for (cnt = 0; cnt < lpField->StgObjCount; cnt++)
	{
		Bip = lpField->GetStageObjectName(cnt, szBuff, sizeof(szBuff));
		if (szBuff[0])
		{
			if (Bip)
				lpstg->StageObject->AddObjectFile(szBuff, szBuff);
			else
				lpstg->StageObject->AddObjectFile(szBuff);
		}
	}

	if (lpField->StgObjCount && GRAPHICDEVICE)
	{
		ReadTextures();
		lpstg->smMaterialGroup->CheckMatreialTextureSwap();
	}

	if (lpSecondField && lpSecondField == StageField[0])
	{
		if (smGameStage[1])
			delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;
		LoadFieldMap(1, lpField, lpstg);
	}
	else
	{
		if (!lpSecondField || lpSecondField == StageField[1])
		{
			if (smGameStage[0])
				delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;
			LoadFieldMap(0, lpField, lpstg);
		}
	}


	if (StageField[0])
		strcpy_s(szGameStageName[0], StageField[0]->szName);

	if (StageField[1])
		strcpy_s(szGameStageName[1], StageField[1]->szName);


	DWORD	dwTime = GetCurrentTime();

	if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime)
		dwLastRecvGameServerTime = dwTime;
	if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime)
		dwLastRecvGameServerTime2 = dwTime;
	if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime)
		dwLastRecvGameServerTime3 = dwTime;
	if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime)
		dwLastRecvGameServerTime4 = dwTime;


	return lpstg;
}


smSTAGE3D* LoadStageFromField2(sFIELD* lpField, sFIELD* lpSecondField)
{
	smSTAGE3D* lpstg;
	char* szStageFile;
	int cnt;
	int Bip;
	char szBuff[128];


	szStageFile = lpField->szName;

	if (lpField == StageField[0]) return smGameStage[0];
	if (lpField == StageField[1]) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;






	AddLoaderStage(lpstg, szStageFile);

	if (!lpstg->StageObject)
	{


		wsprintf(szBuff, "Stage Loading Error ( %s )", szStageFile);
		Record_ClinetLogFile(szBuff);
		delete lpstg;
		return NULL;
	}


	for (cnt = 0; cnt < lpField->StgObjCount; cnt++)
	{
		Bip = lpField->GetStageObjectName(cnt, szBuff, sizeof(szBuff));
		if (szBuff[0])
		{
			if (Bip)
				lpstg->StageObject->AddObjectFile(szBuff, szBuff);
			else
				lpstg->StageObject->AddObjectFile(szBuff);
		}
	}

	if (lpField->StgObjCount && GRAPHICDEVICE)
	{
		ReadTextures();
		lpstg->smMaterialGroup->CheckMatreialTextureSwap();
	}



	if (lpSecondField && lpSecondField == StageField[0])
	{
		if (smGameStage[1]) delete smGameStage[1];
		smGameStage[1] = lpstg;
		StageField[1] = lpField;

		LoadFieldMap(1, lpField, lpstg);
	}
	else
	{
		if (!lpSecondField || lpSecondField == StageField[1])
		{
			if (smGameStage[0]) delete smGameStage[0];
			smGameStage[0] = lpstg;
			StageField[0] = lpField;

			LoadFieldMap(0, lpField, lpstg);
		}
	}

	if (StageField[0]) strcpy_s(szGameStageName[0], StageField[0]->szName);
	if (StageField[1]) strcpy_s(szGameStageName[1], StageField[1]->szName);

	DWORD	dwTime = GetCurrentTime();
	if (dwLastRecvGameServerTime && dwLastRecvGameServerTime < dwTime) dwLastRecvGameServerTime = dwTime;
	if (dwLastRecvGameServerTime2 && dwLastRecvGameServerTime2 < dwTime) dwLastRecvGameServerTime2 = dwTime;
	if (dwLastRecvGameServerTime3 && dwLastRecvGameServerTime3 < dwTime) dwLastRecvGameServerTime3 = dwTime;
	if (dwLastRecvGameServerTime4 && dwLastRecvGameServerTime4 < dwTime) dwLastRecvGameServerTime4 = dwTime;

	return lpstg;
}


smSTAGE3D* LoadStage(char* szStageFile)
{
	smSTAGE3D* lpstg;

	if (lstrcmpi(szGameStageName[0], szStageFile) == 0) return smGameStage[0];
	if (lstrcmpi(szGameStageName[1], szStageFile) == 0) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	AddLoaderStage(lpstg, szStageFile);

	smStageCount = (smStageCount + 1) & 1;

	if (smGameStage[smStageCount]) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;

	return lpstg;
}


smSTAGE3D* LoadStage2(char* szStageFile)
{
	smSTAGE3D* lpstg;

	if (lstrcmpi(szGameStageName[0], szStageFile) == 0) return smGameStage[0];
	if (lstrcmpi(szGameStageName[1], szStageFile) == 0) return smGameStage[1];

	lpstg = new smSTAGE3D;


	lpstg->VectLight.x = smConfig.MapLightVector.x;
	lpstg->VectLight.y = smConfig.MapLightVector.y;
	lpstg->VectLight.z = smConfig.MapLightVector.z;

	lpstg->Bright = smConfig.MapBright;
	lpstg->Contrast = smConfig.MapContrast;


	smSTAGE3D_ReadASE(szStageFile, lpstg);
	lpstg->Head = TRUE;

	smStageCount = (smStageCount + 1) & 1;

	if (smGameStage[smStageCount]) delete smGameStage[smStageCount];

	smGameStage[smStageCount] = lpstg;

	return lpstg;
}


int PlayCounter = 0;

char PlayerName[64] = { 0,0,0,0 };


void InitStage()
{


	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;










	InitFieldMap();


	InitField();

	if (GameStartField < 0)
	{

		StartField();
	}
	else
	{







		if (CharacterPosX == PrisonX && CharacterPosZ == PrisonZ)
		{

			WarpPrisonField((int*)&smConfig.Posi_Player.x, (int*)&smConfig.Posi_Player.y);
		}
		else
		{
			WarpFieldNearPos(GameStartField, CharacterPosX, CharacterPosZ, (int*)&smConfig.Posi_Player.x, (int*)&smConfig.Posi_Player.y);
		}
	}



	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;



	LoadFieldMap(0, StageField[0], smGameStage[0]);


}

void CloseStage()
{



	if (smGameStage[1]) delete smGameStage[1];
	if (smGameStage[0]) delete smGameStage[0];

}


struct _DRAW_LIGHTLIST
{
	smLIGHT3D* smLight;
	int			x, y, z;
};


_DRAW_LIGHTLIST	DrawLight[64];
_DRAW_LIGHTLIST	DrawLightSmall[64];
int DrawLightCnt;
int DrawLightSmallCnt;

//BOOL  SameSpecFilterDropItem(scITEM * item)
//{
//	BOOL bCanView = FALSE;
//	char szBuff[32];
//	wsprintf(szBuff, "%d %d", item->iClass, cItem.GetJobCode(item->iClass));
//	
//	switch (cItem.GetJobCode(item->iClass))
//	{
//	case 1:
//		bCanView = cSettings::GetInstance()->cFS;
//		break;
//	case 2:
//		bCanView = cSettings::GetInstance()->cMS;
//		break;
//	case 3:
//		bCanView = cSettings::GetInstance()->cAS;
//		break;
//	case 4:
//		bCanView = cSettings::GetInstance()->cPS;
//		break;
//	case 5:
//		bCanView = cSettings::GetInstance()->cATS;
//		break;
//	case 6:
//		bCanView = cSettings::GetInstance()->cKS;
//		break;
//	case 7:
//		bCanView = cSettings::GetInstance()->cMGS;
//		break;
//	case 8:
//		bCanView = cSettings::GetInstance()->cPRS;
//		break;
//	case 9:
//		bCanView = cSettings::GetInstance()->cASS;
//		break;
//	case 10:
//		bCanView = cSettings::GetInstance()->cSH;
//		break;
//	default:
//		bCanView = cSettings::GetInstance()->cNaked;
//		break;
//	}
//
//	if (((item->ItemCode & sinITEM_MASK1) == 0x04000000) || ((item->ItemCode & sinITEM_MASK2) == sinGG1))
//		bCanView = TRUE;
//
//	return bCanView;
//}

//BOOL CanViewDropItem(scITEM * item)
//{
//	if (cSettings::GetInstance()->cFilter)
//	{
//		BOOL bRet = FALSE;
//
//		if ((item->ItemCode & sinITEM_MASK1) == 0x04000000)
//		{
//			if ((item->ItemCode & sinITEM_MASK2) == sinPL1)
//				if (cSettings::GetInstance()->cHP)
//					bRet = TRUE;
//			if ((item->ItemCode & sinITEM_MASK2) == sinPM1)
//				if (cSettings::GetInstance()->cMP)
//					bRet = TRUE;
//			if ((item->ItemCode & sinITEM_MASK2) == sinPS1)
//				if (cSettings::GetInstance()->cSP)
//					bRet = TRUE;
//		}
//		else if (item->ItemCode == 0x05010100)
//		{
//			if (cSettings::GetInstance()->cGold)
//				bRet = TRUE;
//		}
//		else if ((item->ItemCode & sinITEM_MASK2) == sinOA1)
//		{
//			if (cSettings::GetInstance()->cAmulets)
//				bRet = TRUE;
//		}
//		else if (((item->ItemCode & sinITEM_MASK2) == sinOR1) || ((item->ItemCode & sinITEM_MASK2) == sinOR2))
//		{
//			if (cSettings::GetInstance()->cRings)
//				bRet = TRUE;
//		}
//		else if ((item->ItemCode & sinITEM_MASK2) == sinOS1)
//		{
//			if (cSettings::GetInstance()->cSheltoms)
//				bRet = TRUE;
//		}
//		else if ((item->ItemCode & sinITEM_MASK2) == sinFO1)
//		{
//			if (cSettings::GetInstance()->cForce)
//				bRet = TRUE;
//		}
//		else if (((item->ItemCode & sinITEM_MASK2) == sinBI1) || ((item->ItemCode & sinITEM_MASK2) == sinBI2))
//		{
//			if (cSettings::GetInstance()->cPremiums)
//				bRet = TRUE;
//		}
//		else if ((item->ItemCode & sinITEM_MASK2) == sinGP1)
//		{
//			if (cSettings::GetInstance()->cCrystal)
//				bRet = TRUE;
//		}
//		else if (((item->ItemCode & sinITEM_MASK1) == 0x02000000) || ((item->ItemCode & sinITEM_MASK2) == sinOM1))
//		{
//			if (cSettings::GetInstance()->cDefItem)
//				bRet = TRUE;
//		}
//		else if (((item->ItemCode & sinITEM_MASK1) == 0x01000000) || ((item->ItemCode & sinITEM_MASK2) == sinOA2))
//		{
//			if (cSettings::GetInstance()->cOffItem)
//				bRet = TRUE;
//		}
//		else if (cSettings::GetInstance()->cElse)
//			bRet = TRUE;
//
//		if (bRet)
//		{
//			if (cSettings::GetInstance()->cFilterSpec)
//				bRet = SameSpecFilterDropItem(item);
//		}
//
//		return bRet;
//	}
//
//	return TRUE;
//}

int DrawLightImage(smSTAGE3D* lpStage, int x, int y, int z)
{




	POINT	Pos;
	RECT	Rect;

	int cnt, cnt2;
	int dx, dy, dz, dist;
	int tz;




	int x1, y1, z1, x2, y2, z2, x3, y3, z3;
	smRENDFACE* rendface;
	smRENDVERTEX* rv;
	int flg;






	int type;


	for (cnt = 0; cnt < lpStage->nLight; cnt++)
	{

		type = lpStage->smLight[cnt].type;

		if ((type & smLIGHT_TYPE_LENS) &&
			(!(lpStage->smLight[cnt].type & smLIGHT_TYPE_NIGHT) || NightDayTime))
		{

			dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
			dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
			dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < DIST_TRANSLEVEL_LOW && abs(dx) < 64 * 38 && abs(dz) < 64 * 38)
			{
				if (tz = smRender.GetRect2D(lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,
					0, 0, &Rect, &Pos))
				{

					if (Pos.x > 0 && Pos.x < WinSizeX && Pos.y>0 && Pos.y < WinSizeY)
					{
						tz -= 64 * fONE;

						if (tz > (64 * 22 * fONE))
						{
							DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
							DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
							DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
							DrawLightSmall[DrawLightSmallCnt].z = tz;
							DrawLightSmallCnt++;
						}
						else
						{

							for (cnt2 = 0; cnt2 < smRender.nRendFace; cnt2++)
							{
								if (!(smRender.RendFace[cnt2].ClipStatus & SMCLIP_DISPLAYOUT))
								{
									rendface = &smRender.RendFace[cnt2];

									rv = rendface->lpRendVertex[0];
									x1 = (int)rv->xy[0];
									y1 = (int)rv->xy[1];
									z1 = rv->tz;
									rv = rendface->lpRendVertex[1];
									x2 = (int)rv->xy[0];
									y2 = (int)rv->xy[1];
									z2 = rv->tz;
									rv = rendface->lpRendVertex[2];
									x3 = (int)rv->xy[0];
									y3 = (int)rv->xy[1];
									z3 = rv->tz;

									flg = 0;
									if (tz > z1 && tz > z2 && tz > z3)
									{

										if (Pos.x < x1 && Pos.x < x2 && Pos.x < x3) flg++;
										if (Pos.x > x1 && Pos.x > x2 && Pos.x > x3) flg++;
										if (Pos.y < y1 && Pos.y < y2 && Pos.y < y3) flg++;
										if (Pos.y > y1 && Pos.y > y2 && Pos.y > y3) flg++;
										if (flg == 0) break;



									}
								}

							}

							if (cnt2 >= smRender.nRendFace)
							{
								DrawLight[DrawLightCnt].smLight = &lpStage->smLight[cnt];
								DrawLight[DrawLightCnt].x = Pos.x;
								DrawLight[DrawLightCnt].y = Pos.y;
								DrawLight[DrawLightCnt].z = tz;
								DrawLightCnt++;
							}
							else
							{
								DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
								DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
								DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
								DrawLightSmall[DrawLightSmallCnt].z = tz;
								DrawLightSmallCnt++;
							}

						}

					}
				}
			}
		}
	}

	return TRUE;
}

int DrawLightImage()
{
	smFACE2D face2d;
	int size;
	smRENDFACE* RendFace;
	int cnt;

	smRender.SetMaterialGroup(smMaterialGroup);

	smRender.Init();

	for (cnt = 0; cnt < DrawLightSmallCnt; cnt++)
	{

		size = 40 * fONE;


		if (size > 0)
		{

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLightSmall[cnt].smLight->x;
			face2d.y = DrawLightSmall[cnt].smLight->y;
			face2d.z = DrawLightSmall[cnt].smLight->z;
			face2d.MatNum = MatLight[1];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if (smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}


	smRender.Init();

	for (cnt = 0; cnt < DrawLightCnt; cnt++)
	{
		size = 160 * fONE;



		if (size > 0)
		{

			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLight[cnt].smLight->x;
			face2d.y = DrawLight[cnt].smLight->y;
			face2d.z = DrawLight[cnt].smLight->z;
			face2d.MatNum = MatLight[0];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if (smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		for (cnt = 0; cnt < smRender.nRendVertex; cnt++)
		{
			smRender.RendVertex[cnt].zb = 0.001f;
		}

		smRender.RenderD3D();

	}


	return TRUE;

}

int SetStageDynLight(smSTAGE3D* lpStage, int x, int y, int z)
{

	int cnt;
	int dx, dy, dz, dist;
	int type;


	for (cnt = 0; cnt < lpStage->nLight; cnt++)
	{

		dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
		dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
		dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
		dist = dx * dx + dy * dy + dz * dz;




		type = lpStage->smLight[cnt].type;

		if (dist < 0x300000 && (type & smLIGHT_TYPE_DYNAMIC) && abs(dx) < 0x2000 && abs(dz) < 0x2000)
		{
			if ((lpStage->smLight[cnt].type & smLIGHT_TYPE_NIGHT) && NightDayTime)
			{



				smRender.AddDynamicLight(lpStage->smLight[cnt].type,
					lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,
					lpStage->smLight[cnt].r, lpStage->smLight[cnt].g, lpStage->smLight[cnt].b,
					0, lpStage->smLight[cnt].Range);

			}
			else
			{
				if (DarkLevel > 0)
				{


					smRender.AddDynamicLight(lpStage->smLight[cnt].type,
						lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z,

						(lpStage->smLight[cnt].r * DarkLevel) >> 8,
						(lpStage->smLight[cnt].g * DarkLevel) >> 8,
						(lpStage->smLight[cnt].b * DarkLevel) >> 8,
						0, lpStage->smLight[cnt].Range);

				}
			}
		}
	}

	return TRUE;

}




int doop = 0;



int DisplayStage(int x, int y, int z, int angX, int angY, int angZ)
{

	int cnt;
	int r, g, b, l;



	DrawLightCnt = 0;
	DrawLightSmallCnt = 0;


	smRender.ZWriteAuto = TRUE;


	for (cnt = 0; cnt < 2; cnt++)
	{
		if (smGameStage[cnt])
		{



			if (DarkLevel > 0 && StageField[cnt]->State == FIELD_STATE_VILLAGE)
			{

				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;
				l = smRender.nRendLight;

				smRender.Color_R >>= 1;
				smRender.Color_G >>= 1;
				smRender.Color_B >>= 1;

				if (smRender.nRendLight > 0 && smRender.smRendLight[0].Range == DarkLightRange)
				{
					smRender.smRendLight[0].Range = 0;
					l = 1;
				}
				else
					l = 0;

				if (smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{




					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;

				if (l) smRender.smRendLight[0].Range = DarkLightRange;



			}
			else
			{
				if (smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{



					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}
			}

		}
	}




	smRender.ZWriteAuto = FALSE;

	if ((MaterialFrame & 0x3F) == 0)
	{


		CheckInvenItemCode();
	}

	return TRUE;
}



void CreatePatIceFoot(int Num, int sizeX, int sizeZ)
{
	int MatShadow = CreateTextureMaterial(g_IceFootImageFileBuff[Num], 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	smTPOINT tPoint[4];
	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;

	smOBJ3D* objIceFoot = new smOBJ3D(4, 2);
	objIceFoot->AddVertex(-sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(-sizeX, sizeZ, 0);
	objIceFoot->AddVertex(sizeX, sizeZ, 0);

	objIceFoot->AddFace(0, 1, 2, &tPoint[2], &tPoint[3], &tPoint[0]);
	objIceFoot->AddFace(2, 1, 3, &tPoint[0], &tPoint[3], &tPoint[1]);
	objIceFoot->ZeroNormals();

	objIceFoot->SetFaceMaterial(0, MatShadow);
	objIceFoot->SetFaceMaterial(1, MatShadow);

	PatIceFoot[Num] = new smPAT3D;
	PatIceFoot[Num]->AddObject(objIceFoot);
}


void CreatePatShadow(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[4];
	smOBJ3D* objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;


	objShadow = new smOBJ3D(4, 2);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);
	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 2, &tPoint[0], &tPoint[1], &tPoint[2]);
	objShadow->AddFace(2, 1, 3, &tPoint[2], &tPoint[1], &tPoint[3]);
	objShadow->ZeroNormals();

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}

void CreatePatShadow2(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[9];
	smOBJ3D* objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 128;
	tPoint[1].v = 0;
	tPoint[2].u = 256;
	tPoint[2].v = 0;

	tPoint[3].u = 0;
	tPoint[3].v = 128;
	tPoint[4].u = 128;
	tPoint[4].v = 128;
	tPoint[5].u = 256;
	tPoint[5].v = 128;

	tPoint[6].u = 0;
	tPoint[6].v = 256;
	tPoint[7].u = 128;
	tPoint[7].v = 256;
	tPoint[8].u = 256;
	tPoint[8].v = 256;


	objShadow = new smOBJ3D(9, 8);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(0, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);

	objShadow->AddVertex(-sizeX, 0, 0);
	objShadow->AddVertex(0, 0, 0);
	objShadow->AddVertex(sizeX, 0, 0);

	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(0, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 3, &tPoint[0], &tPoint[1], &tPoint[3]);
	objShadow->AddFace(3, 1, 4, &tPoint[3], &tPoint[1], &tPoint[4]);

	objShadow->AddFace(1, 2, 4, &tPoint[0], &tPoint[2], &tPoint[4]);
	objShadow->AddFace(4, 2, 5, &tPoint[4], &tPoint[2], &tPoint[5]);

	objShadow->AddFace(3, 4, 6, &tPoint[3], &tPoint[4], &tPoint[6]);
	objShadow->AddFace(6, 4, 7, &tPoint[6], &tPoint[4], &tPoint[7]);

	objShadow->AddFace(4, 5, 7, &tPoint[4], &tPoint[5], &tPoint[7]);
	objShadow->AddFace(7, 5, 8, &tPoint[7], &tPoint[5], &tPoint[8]);

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);
	objShadow->SetFaceMaterial(2, MatShadow);
	objShadow->SetFaceMaterial(3, MatShadow);
	objShadow->SetFaceMaterial(4, MatShadow);
	objShadow->SetFaceMaterial(5, MatShadow);
	objShadow->SetFaceMaterial(6, MatShadow);
	objShadow->SetFaceMaterial(7, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}



int AdminCharMode = 0;

int AdminCharDisable = 0;


static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;


static char* SetDirectoryFromFile(char* filename)
{
	int len;
	int cnt;

	strcpy_s(szDataDirectory, filename);

	len = lstrlen(szDataDirectory);

	for (cnt = len; cnt >= 0; cnt--)
		if (szDataDirectory[cnt] == '\\') break;

	szDataDirectory[cnt + 1] = NULL;

	return szDataDirectory;
}


int SetCharFileList(char* szCharFile)
{
	CharFileCnt = 0;
	char szFindPath[256];

	SetDirectoryFromFile(szCharFile);

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	strcpy_s(szFindPath, szDataDirectory);
	lstrcat(szFindPath, "\\*.ini");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;
	}
	while (1)
	{
		strcpy_s(szCharFileList[CharFileCnt], szDataDirectory);
		lstrcat(szCharFileList[CharFileCnt], fd.cFileName);
		CharFileCnt++;

		if (FindNextFile(hFindHandle, &fd) == FALSE)
			break;
		if (CharFileCnt > 255)
			break;
	}
	FindClose(hFindHandle);

	return TRUE;
}

void SetNextPlayerPattern()
{
	if (lpCurPlayer->PatLoading)
		return;


	AdminCharDisable = TRUE;

	if (AdminCharMode)
	{
		memcpy(&lpCurPlayer->smCharInfo, &smCharInfo_Back, sizeof(smCHAR_INFO));
		ReformCharForm();
		AdminCharMode = 0;
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName, lpCurPlayer->smCharInfo.szModelName2);
		lpCurPlayer->DisplayTools = TRUE;
		return;
	}

	AdminCharMode = 0;
	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szCharFileList[CharPlayCnt], lpCurPlayer->smCharInfo.szModelName2);
	lpCurPlayer->DisplayTools = TRUE;

	CharPlayCnt++;
	if (CharPlayCnt >= CharFileCnt) CharPlayCnt = 0;
}

void SetPlayerBodyPattern(char* szBodyFile)
{
	char szBuff[256];

	if (lpCurPlayer->PatLoading)
		return;

	wsprintf(szBuff, "char\\tmABCD\\%s.ini", szBodyFile);
	FILE* fp = fopen(szBuff, "rb");
	if (!fp) return;
	fclose(fp);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szBuff, lpCurPlayer->smCharInfo.szModelName2);
	lpCurPlayer->DisplayTools = TRUE;
}

void SetPlayerPattern(char* szFile)
{
	if (lpCurPlayer->PatLoading)
		return;

	FILE* fp = fopen(szFile, "rb");
	if (!fp) return;
	fclose(fp);

	lpCurPlayer->PatLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szFile, 0);
	lpCurPlayer->DisplayTools = TRUE;

	ReformCharForm();

	lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
	SendSetObjectSerial(lpCurPlayer->dwObjectSerial);

}

char szNpcFileList[64][64];
int NpcFileCnt;
int NpcPlayCnt = 0;

char* NpcSelectedName = 0;


int SetNpcFileList(char* szNpcDirectory)
{
	NpcFileCnt = 0;
	char szFindPath[256];



	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	strcpy_s(szFindPath, szNpcDirectory);
	lstrcat(szFindPath, "*.npc");


	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;

	}
	while (1)
	{
		strcpy_s(szNpcFileList[NpcFileCnt], szNpcDirectory);
		lstrcat(szNpcFileList[NpcFileCnt], fd.cFileName);
		NpcFileCnt++;

		if (FindNextFile(hFindHandle, &fd) == FALSE)
			break;
		if (NpcFileCnt > 64)
			break;

	}
	FindClose(hFindHandle);

	return TRUE;
}

void SetNextNpcPattern()
{
	if (lpCurPlayer->PatLoading)
		return;

	if (AdminCharMode == 0)
		memcpy(&smCharInfo_Back, &lpCurPlayer->smCharInfo, sizeof(smCHAR_INFO));


	AdminCharDisable = TRUE;

	AdminCharMode = 1;


	lpCurPlayer->smCharInfo.dwCharSoundCode = 0;


	if (smCharDecode(szNpcFileList[NpcPlayCnt], &lpCurPlayer->smCharInfo, 0))
	{
		lpCurPlayer->PatLoading = TRUE;
		AddLoaderPattern(lpCurPlayer, lpCurPlayer->smCharInfo.szModelName);

		lpCurPlayer->DisplayTools = FALSE;
		lpCurPlayer->smCharInfo.SizeLevel = 1;

		NpcSelectedName = szNpcFileList[NpcPlayCnt];

		NpcPlayCnt++;
		if (NpcPlayCnt >= NpcFileCnt) NpcPlayCnt = 0;
	}
	ReformCharForm();
}


int LaunchPartyPostion()
{
	int x, y, z, dist, ddist;
	int cnt;
	smCHAR* lpChar;

	x = lpCurPlayer->pX;
	y = lpCurPlayer->pY + 48 * fONE;
	z = lpCurPlayer->pZ;

	if (sPartyPosion.code == OpCode::OPCODE_PARTY_POTION)
	{

		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
				StartEffect(x, y, z, EFFECT_POTION1);
			}
			if (sPartyPosion.LParam)
			{
				sinSetMana(sinGetMana() + sPartyPosion.LParam);
				StartEffect(x, y, z, EFFECT_POTION2);
			}
			if (sPartyPosion.SParam)
			{
				sinSetStamina(sinGetStamina() + sPartyPosion.SParam);
				StartEffect(x, y, z, EFFECT_POTION3);
			}
			ResetEnergyGraph(3);
			ReformCharForm();
			sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(x, y, z));

		}



		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && chrOtherPlayer[cnt].PartyFlag &&
				chrOtherPlayer[cnt].dwObjectSerial != sPartyPosion.EParam &&
				chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD &&
				chrOtherPlayer[cnt].RendSucess)
			{

				x = chrOtherPlayer[cnt].pX;
				y = chrOtherPlayer[cnt].pY + 48 * fONE;
				z = chrOtherPlayer[cnt].pZ;

				if (sPartyPosion.WParam) 	StartEffect(x, y, z, EFFECT_POTION1);
				if (sPartyPosion.LParam) 	StartEffect(x, y, z, EFFECT_POTION2);
				if (sPartyPosion.SParam) 	StartEffect(x, y, z, EFFECT_POTION3);
			}
		}


	}

	switch (sPartyPosion.code)
	{
	case OpCode::OPCODE_HEALING:

		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;

	case OpCode::OPCODE_GRAND_HEALING:

		if (sPartyPosion.EParam == lpCurPlayer->dwObjectSerial)
		{
			lpChar = lpCurPlayer;
		}
		else
			lpChar = FindAutoPlayer(sPartyPosion.EParam);

		if (!lpChar) break;

		ddist = sPartyPosion.SParam * sPartyPosion.SParam;

		x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
		y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
		z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;
		dist = x * x + y * y + z * z;
		if (dist < ddist && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{

			if (sPartyPosion.LParam)
			{
				CheckCharForm();
				sinSetLife(sinGetLife() + sPartyPosion.LParam);
				ResetEnergyGraph(0);
				ReformCharForm();
			}

			if (lpChar != lpCurPlayer)
				sinSkillEffect_Great_Healing_Party(lpCurPlayer);
		}



		for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
		{
			if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].dwObjectSerial && lpChar != &chrOtherPlayer[cnt] &&
				chrOtherPlayer[cnt].PartyFlag && chrOtherPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD)
			{

				x = (chrOtherPlayer[cnt].pX - lpChar->pX) >> FLOATNS;
				y = (chrOtherPlayer[cnt].pY - lpChar->pY) >> FLOATNS;
				z = (chrOtherPlayer[cnt].pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + y * y + z * z;

				if (dist < ddist)
				{
					sinSkillEffect_Great_Healing_Party(&chrOtherPlayer[cnt]);
				}
			}
		}
		break;

	case OpCode::OPCODE_VAMPRIC_CUSPID:
		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;


	case OpCode::OPCODE_VAMPRIC_CUSPID_EX:
		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;

	case OpCode::OPCODE_MANA_RECHARGING:
		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetMana(sinGetMana() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(1);
			ReformCharForm();
		}
		break;


	case OpCode::OPCODE_RES_RECHARGING:
		if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DEAD)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetStamina(sinGetStamina() + sPartyPosion.WParam);
			}
			ResetEnergyGraph(2);
			ReformCharForm();
		}
		break;
	}




	sPartyPosion.code = 0;
	dwPartyPosionTime = 0;


	return TRUE;
}


int SetPartyPosion(smTRANS_COMMAND* lpTransCommand)
{
	if (dwPartyPosionTime)
	{

		LaunchPartyPostion();
	}

	dwPartyPosionTime = dwPlayTime + 1000;
	memcpy(&sPartyPosion, lpTransCommand, sizeof(smTRANS_COMMAND));

	return TRUE;
}



char szPlayerCode[32];
int CharacterJob = 0;

char* szAnimShieldEffectFile[] = {
	"Weapons\\test1.tga",
	"Weapons\\test2.tga",
	"Weapons\\test3.tga",
	"Weapons\\test2.tga"
};

char* szBangImage = "weapons\\bang2.bmp";
char* szClowImage = "weapons\\crown.tga";

extern	char* szNpcInfoPath;

DWORD	dwSoD_ResultTime = 0;

sBILLING_INFO* sBiInfo = 0;

int InitPat3D()
{
	int cnt, cnt2, size;
	POINT3D Posi, Angle;


	DWORD nsize = 62;

	if (!sBiInfo)
	{
		sBiInfo = new sBILLING_INFO;
		ZeroMemory(sBiInfo, sizeof(sBILLING_INFO));
	}

	if (PlayerName[0] == 0)
		GetComputerName(PlayerName, &nsize);

	InterfaceParty.chatbuild_INIfiles();


	rsRecorder.dwRecordTime = 0;
	rsRecorder.dwNextRecordTime = GetCurrentTime() + 10 * 60 * 1000;



#ifdef	_LANGUAGE_THAI		
	cInterFace.sInterFlags.CameraAutoFlag = 0;
#else	
	cInterFace.sInterFlags.CameraAutoFlag = 2;
#endif	

	cInterFace.sInterFlags.MapOnFlag = TRUE;
	cInterFace.sInterFlags.RunFlag = TRUE;

	if (((GetCurrentTime() >> 4) & 1) == 0) strcpy_s(szPlayerCode, "p");
	else strcpy_s(szPlayerCode, "f");



	CreatePatIceFoot(0, 6 * fONE, 6 * fONE);
	CreatePatIceFoot(1, 6 * fONE, 6 * fONE);



	CreatePatShadow(0, 12 * fONE, 10 * fONE);
	CreatePatShadow(1, 17 * fONE, 14 * fONE);
	CreatePatShadow2(2, 26 * fONE, 20 * fONE);
	CreatePatShadow2(3, 38 * fONE, 30 * fONE);




	Posi.x = smConfig.Posi_Player.x;
	Posi.z = smConfig.Posi_Player.y;
	Posi.y = 0;
	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;


	invPlayerArmor = 0;



	//SetCharFileList("char\\tmABCD\\a001.ini");



#ifdef _W_SERVER

	//SetNpcFileList(szNpcInfoPath);
#endif
	//Loading
//	LoadOftenArmor();
//	LoadOftenFace();
	LoadOftenItem();
	//	LoadOftenNpc();
	//	LoadOftenModels();


	sinChar = &lpCurPlayer->smCharInfo;

	CheckCharForm();


	if (CharacterName1[0])
	{
		cnt = NewCharInfo.Dexterity + NewCharInfo.Health + NewCharInfo.Spirit + NewCharInfo.Strength + NewCharInfo.Talent;

		lpCurPlayer->smCharInfo.JOB_CODE = NewCharInfo.JobCode;

		if (cnt < 103)
		{

			lpCurPlayer->smCharInfo.Dexterity = NewCharInfo.Dexterity;
			lpCurPlayer->smCharInfo.Health = NewCharInfo.Health;
			lpCurPlayer->smCharInfo.Spirit = NewCharInfo.Spirit;
			lpCurPlayer->smCharInfo.Strength = NewCharInfo.Strength;
			lpCurPlayer->smCharInfo.Talent = NewCharInfo.Talent;
		}
		else
		{
			lpCurPlayer->smCharInfo.Dexterity = 1;
			lpCurPlayer->smCharInfo.Health = 8;
			lpCurPlayer->smCharInfo.Spirit = 1;
			lpCurPlayer->smCharInfo.Strength = 8;
			lpCurPlayer->smCharInfo.Talent = 1;
			lpCurPlayer->smCharInfo.StatePoint = 0;
		}
	}


	if (CharacterName1[0])
	{
		SetLoadPattern(lpCurPlayer, CharacterName1, CharacterName2, &Posi, &Angle);

		cnt2 = 0;
		for (cnt = 0; cnt < (int)lpCurPlayer->smMotionInfo->MotionCount; cnt++)
		{
			if (lpCurPlayer->smMotionInfo->MotionInfo[cnt].State == CHRMOTION_STATE_DEAD)
			{

				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;
				if (size > 8) cnt2++;
			}

			if (lpCurPlayer->smMotionInfo->MotionInfo[cnt].State == CHRMOTION_STATE_ATTACK)
			{
				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;

				if (size < 40 && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
				{
					DisconnectFlag = GetCurrentTime();
					quit = TRUE;
				}
			}
		}

		if (cnt2 == 0 && smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
		{

			DisconnectFlag = GetCurrentTime();
			quit = TRUE;
		}
	}
	else
		SetLoadPattern(lpCurPlayer, smConfig.szFile_Player, 0, &Posi, &Angle);


	lpCurPlayer->smCharInfo.Level = 1;

	lpCurPlayer->smCharInfo.Attack_Damage[0] = 5;
	lpCurPlayer->smCharInfo.Attack_Damage[1] = 10;

	strcpy_s(lpCurPlayer->smCharInfo.szName, PlayerName);
	lpCurPlayer->smCharInfo.State = smCHAR_STATE_USER;
	lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);

	lpCurPlayer->smCharInfo.SizeLevel = 1;
	lpCurPlayer->PatSizeLevel = 1;

	lpCurPlayer->smCharInfo.Attack_Rating = 100;
	lpCurPlayer->smCharInfo.Next_Exp = 1000;

	lpCurPlayer->smMonsterInfo.dwAutoCharCode = 0;

	lpCurPlayer->smCharInfo.Life[0] = 1000;
	lpCurPlayer->smCharInfo.Life[1] = 1000;

	lpCurPlayer->MoveMode = TRUE;
	lpCurPlayer->MoveCnt = 0;

	PkMode = 0;

	ReformCharForm();



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


	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		chrOtherPlayer[cnt].Init();
	}


	smMATERIAL* mat;

	smASE_SetPhysique(0);
	PatArrow = smASE_Read("weapons\\arrow.ase");
	PatEffectShield = smASE_Read("weapons\\Test8.ASE");
	PatSparkShield = smASE_Read("weapons\\Mc3_sparkShield.ASE");
	PatDivineShield = smASE_Read("weapons\\Nt3_DivineI.ASE");
	PatGodlyShield = smASE_Read("weapons\\Godly_Shield.ASE");
	PatCrown = smASE_Read("weapons\\Crown.ASE");
	PatCrown2 = smASE_Read("weapons\\Crown2.ASE");
	PatCrown3 = smASE_Read("weapons\\Crown3.ASE");

	if (PatEffectShield)
	{
		PatEffectShield->Frame = 0;

		mat = PatEffectShield->smMaterialGroup->FindMaterialFromTextureName(szBangImage);
		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;


		}
	}

	if (PatCrown)
	{
		PatCrown->Frame = 0;

		mat = PatCrown->smMaterialGroup->FindMaterialFromTextureName(szClowImage);

		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}

	if (PatCrown2)
	{
		PatCrown2->Frame = 0;

		mat = PatCrown2->smMaterialGroup->FindMaterialFromTextureName("weapons\\crown2.tga");

		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}

	if (PatCrown3)
	{
		PatCrown3->Frame = 0;

		mat = PatCrown3->smMaterialGroup->FindMaterialFromTextureName("weapons\\crown3.tga");

		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}

	smASE_SetPhysique(0);


	MatEachBox = CreateTextureMaterial("image\\cw.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	MatEachMenuBox = CreateTextureMaterial("image\\cw-1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[0] = CreateTextureMaterial("image\\CW-trade0.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[1] = CreateTextureMaterial("image\\CW-trade1.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

#ifdef	_NEW_PARTRADE


	lpDDS_ParTradeButton[0][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c5_.bmp");
	lpDDS_ParTradeButton[0][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c5.bmp");

	lpDDS_ParTradeButton[1][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c1_.bmp");
	lpDDS_ParTradeButton[1][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c1.bmp");

	lpDDS_ParTradeButton[2][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c2_.bmp");
	lpDDS_ParTradeButton[2][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c2.bmp");

	lpDDS_ParTradeButton[3][0] = LoadDibSurfaceOffscreen("image\\party\\icon_clan_.bmp");
	lpDDS_ParTradeButton[3][1] = LoadDibSurfaceOffscreen("image\\party\\icon_clan.bmp");


	lpDDS_ParTradeToolTip[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c5.bmp");
	lpDDS_ParTradeToolTip[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c1.bmp");
	lpDDS_ParTradeToolTip[2] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c0.bmp");
	lpDDS_ParTradeToolTip[3] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c10.bmp");


#endif


	MatEnergyBox[0] = CreateTextureMaterial("image\\Energy_Red.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatEnergyBox[1] = CreateTextureMaterial("image\\Energy_Blue.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	MatLight[0] = CreateTextureMaterial("image\\glow01.bmp", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[0]].SelfIllum = TRUE;
	MatLight[1] = CreateTextureMaterial("image\\glow02.bmp", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[1]].SelfIllum = TRUE;

	MatMonBroodImage[0] = CreateTextureMaterial("image\\M_Nm.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[1] = CreateTextureMaterial("image\\M_Mt.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[2] = CreateTextureMaterial("image\\M_Un.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[3] = CreateTextureMaterial("image\\M_D.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[4] = CreateTextureMaterial("image\\M_mc.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	InitWeatherSystem();


	InitParticle();

	InitDynLight();

	UseEtherCoreCode = 0;

	dwPartyPosionTime = 0;


	InitTimeEffect();

#ifdef	_SET_PROCTECT_MEM2

	cnt = Check_PlaySubReleaseFunc();
	if (cnt)
	{
		SendSetHackUser2(1120, cnt);
	}
#endif

	ResetEnergyGraph(3);
	ResetInvenItemCode();
	ResetInvenMoney();

	CheckDLL_Module();

	ZeroMemory(&rsBlessCastle, sizeof(rsBLESS_CASTLE));

	return TRUE;

}

int ClosePat3D()
{
	int cnt;

	ClosePatterns();



	if (PatArrow)
	{
		delete PatArrow;
		PatArrow = NULL;
	}

	if (PatEffectShield)
	{
		delete PatEffectShield;
		PatEffectShield = NULL;
	}




	for (cnt = 0; cnt < ICE_FOOT_PAT_MAX; cnt++)
	{
		if (PatIceFoot[cnt])
		{
			delete PatIceFoot[cnt];
			PatIceFoot[cnt] = NULL;
		}
	}



	for (cnt = SHADOW_PAT_MAX - 1; cnt >= 0; cnt--)
		if (PatShadow[cnt]) delete PatShadow[cnt];


	if (lpDDS_ParTradeButton[0][0])	lpDDS_ParTradeButton[0][0]->Release();
	if (lpDDS_ParTradeButton[0][1])	lpDDS_ParTradeButton[0][1]->Release();
	if (lpDDS_ParTradeButton[1][0])	lpDDS_ParTradeButton[1][0]->Release();
	if (lpDDS_ParTradeButton[1][1])	lpDDS_ParTradeButton[1][1]->Release();
	if (lpDDS_ParTradeButton[2][0])	lpDDS_ParTradeButton[2][0]->Release();
	if (lpDDS_ParTradeButton[2][1])	lpDDS_ParTradeButton[2][1]->Release();
	if (lpDDS_ParTradeButton[3][0])	lpDDS_ParTradeButton[3][0]->Release();
	if (lpDDS_ParTradeButton[3][1])	lpDDS_ParTradeButton[3][1]->Release();

	if (lpDDS_ParTradeToolTip[0])	lpDDS_ParTradeToolTip[0]->Release();
	if (lpDDS_ParTradeToolTip[1])	lpDDS_ParTradeToolTip[1]->Release();
	if (lpDDS_ParTradeToolTip[2])	lpDDS_ParTradeToolTip[2]->Release();
	if (lpDDS_ParTradeToolTip[3])	lpDDS_ParTradeToolTip[3]->Release();

	if (sBiInfo) delete sBiInfo;

	return TRUE;
}

int PartCnt = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton = 0;

smCHAR* lpCharSelPlayer = 0;
smCHAR* lpCharMsTrace = 0;

scITEM* lpSelItem = 0;
scITEM* lpMsTraceItem = 0;

int AttFlag = 0;
int	AttCancel;
int	AttAutoCont = 0;


int TraceAttackPlay()
{
	if (lpCharSelPlayer)
	{
		MsTraceMode = TRUE;
		lpCharMsTrace = lpCharSelPlayer;
		AttFlag = TRUE;
		if (VRKeyBuff[VK_SHIFT] && lpCharSelPlayer->smCharInfo.State == smCHAR_STATE_ENEMY) AttAutoCont = TRUE;
		else AttAutoCont = FALSE;


		if (VRKeyBuff['O'] && smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
			SkillWarriorBetserker(lpCharSelPlayer, 15);

		return TRUE;
	}

	if (lpSelItem)
	{
		MsTraceMode = TRUE;
		lpMsTraceItem = lpSelItem;
		return TRUE;
	}

	return FALSE;

}


int CancelAttack()
{
	SelMouseButton = 0;
	MsTraceMode = FALSE;
	lpCharMsTrace = 0;
	lpMsTraceItem = 0;
	AttFlag = 0;

	return TRUE;
}


int	DamageExp(smCHAR* lpChar, int AttackDamage)
{
	int AttackResult;


	if (AttackDamage && lpChar->smCharInfo.State == smCHAR_STATE_ENEMY &&
		lpChar->smCharInfo.Brood != smCHAR_MONSTER_USER && lpChar->smCharInfo.Life[0] > 0)
	{

		AttackResult = (AttackDamage << 8) / lpChar->smCharInfo.Life[1];
		if (AttackResult > 256) AttackResult = 256;
		AttackResult = (lpChar->smCharInfo.Exp * AttackResult) >> 8;
		AttackResult /= 10;
		if (AttackResult <= 0) AttackResult = 1;
		lpCurPlayer->AttackExp = AttackResult;
	}

	return TRUE;
}

#define AUTO_DEAD_COUNT		(70*60*8)
int AutoDeathCounter = 0;
int FixedWidth = 200;
DWORD	dwClassDelayTime = 0;



int PlayPat3D()
{


	int cnt;
	int attack;
	int	attack_UserMonster;
	int	attack_RegState;

	int wx, wz, x, z;
	int	attackMode;
	sSKILL* lpAttackSkill;
	SocketData* lpsmSock;
	int	skFlag;

#ifdef	_WINMODE_DEBUG

	if (SkipNextField)
	{
		if (SkipNextField == 1)
		{
			WarpNextField(&wx, &wz);
			lpCurPlayer->SetPosi(wx, 0, wz, 0, 0, 0);
			SkipNextField = 0;
			TraceCameraPosi.x = lpCurPlayer->pX;
			TraceCameraPosi.y = lpCurPlayer->pY;
			TraceCameraPosi.z = lpCurPlayer->pZ;
			TraceTargetPosi.x = lpCurPlayer->pX;
			TraceTargetPosi.y = lpCurPlayer->pY;
			TraceTargetPosi.z = lpCurPlayer->pZ;
		}
		else
		{

			WarpCustomField(&wx, &wz);
			lpCurPlayer->SetPosi(wx, 0, wz, 0, 0, 0);
			SkipNextField = 0;
			TraceCameraPosi.x = lpCurPlayer->pX;
			TraceCameraPosi.y = lpCurPlayer->pY;
			TraceCameraPosi.z = lpCurPlayer->pZ;
			TraceTargetPosi.x = lpCurPlayer->pX;
			TraceTargetPosi.y = lpCurPlayer->pY;
			TraceTargetPosi.z = lpCurPlayer->pZ;

		}
	}

#endif





	lpCurPlayer->Main();

	EachPlayerMain();


	AutoDeathCounter++;

	if (PkMode > 0) PkMode--;

#ifdef _LANGUAGE_BRAZIL
	if (VRKeyBuff[VK_CONTROL]) PkMode = FALSE;
#else
	if (VRKeyBuff[VK_CONTROL]) PkMode = TRUE;
#endif

	else PkMode = FALSE;



	if (lpCurPlayer->PlayStunCount)
	{
		if (MsTraceMode)
		{
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_WALK || lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_RUN)
		{
			lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		lpCurPlayer->dwNextMotionCode = 0;
		lpCurPlayer->MotionLoop = 0;
	}


	if (MsTraceMode && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT &&
		lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_SKILL)
	{

		attackMode = FALSE;
		AttCancel = FALSE;
		attack_UserMonster = FALSE;

		CheckPlaySubFunc2();

		if ((MsTraceCount & 0x1F) == 0)
		{


			lpCurPlayer->MoveFlag = TRUE;
			lpCurPlayer->Angle.y = GetMouseSelAngle();
		}

		int AttackRange = 0;
		int	AttackResult = 0;

		lpAttackSkill = 0;

		switch (SelMouseButton)
		{
		case 1:
			if (sinSkill.pLeftSkill && sinSkill.pLeftSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pLeftSkill;
			break;
		case 2:
			if (sinSkill.pRightSkill && sinSkill.pRightSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pRightSkill;
			break;
		}


		if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
			lpAttackSkill = 0;

		if (lpCharMsTrace)
		{
			if (lpCharMsTrace->smCharInfo.Life[0] <= 0 ||
				(lpCharMsTrace->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime ||
				cTrade.OpenFlag)
			{

				CancelAttack();
			}
			else
			{

				if (!MouseButton[0] && !MouseButton[1]) AttFlag = 0;

				if (lpCurPlayer->smCharInfo.State == smCHAR_STATE_ENEMY)
				{

					attackMode = TRUE;
				}
				else
				{
					if (PkMode)
						attackMode = TRUE;

				}

				if (lpCharMsTrace->smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU)
				{
					AttackRange = 130 * fONE;
				}
				else
					AttackRange = 50 * fONE;

				if (lpCurPlayer->dwActionItemCode)
				{
					AttackRange += lpCurPlayer->AttackToolRange;
				}


				if (lpCurPlayer->ShootingMode && lpCharMsTrace->smCharInfo.State)
				{
					if (lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER || attackMode)
						AttackRange = lpCurPlayer->smCharInfo.Shooting_Range * fONE;




				}

				if (lpCharMsTrace->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
					AttackRange += 40 * fONE;

				attack = lpCharMsTrace->smCharInfo.State;

				if (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER)
				{
					if (!attackMode ||
						(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE))
						attack = 0;
				}

				if (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_ENEMY && lpCharMsTrace->smCharInfo.Brood == smCHAR_MONSTER_USER)
				{
					if (!PkMode)
					{
						attack_UserMonster = TRUE;;
						attack = 0;
					}
				}

				if (lpAttackSkill)
				{
					if (lpAttackSkill->CODE == SKILL_HEALING || lpAttackSkill->CODE == SKILL_ENCHANT_WEAPON ||
						lpAttackSkill->CODE == SKILL_VIRTUAL_LIFE || lpAttackSkill->CODE == SKILL_TRIUMPH_OF_VALHALLA)
					{
						if (attack_UserMonster && lpAttackSkill->CODE == SKILL_HEALING)
							attack_UserMonster = 0;

						skFlag = 1;
					}
					else
						skFlag = 0;

					if ((lpCharMsTrace->smCharInfo.State == smCHAR_STATE_ENEMY && !attack_UserMonster) ||
						(PkMode && lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER) || skFlag)
					{


						cnt = GetSkillDistRange(lpAttackSkill, AttackRange, attack);
						if (cnt)
							AttackRange = cnt;

						attack = 0;
					}
				}

				if (!lpCurPlayer->ShootingFlag &&
					lpCurPlayer->PlayAttackFromPosi(
						lpCharMsTrace->pX,
						lpCharMsTrace->pY,
						lpCharMsTrace->pZ,
						AttackRange, attack) == TRUE &&
					lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_EAT)
				{


					LastAttackDamage = 0;
					AutoMouse_Attack_Count++;

					if (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_USER)
					{
						if (lpCharMsTrace->dwTradeMsgCode)
						{
							Send_ShowMyShopItem(lpCharMsTrace);
						}
						else
						{
							EachTradeButton = 1;

#ifdef  __CLANSUBCHIP__
							if ((cldata.myPosition == 101 || cldata.myPosition == 104) && !lpCharMsTrace->smCharInfo.ClassClan)
#else
							if (cldata.myPosition == 101 && !lpCharMsTrace->smCharInfo.ClassClan)
#endif
								EachTradeButtonMode = TRUE;
							else
								EachTradeButtonMode = FALSE;
						}

					}
					else
					{
						EachTradeButton = 0;
					}

					if (!lpCharMsTrace->smCharInfo.State)
					{
						OpenEachPlayer(lpCharMsTrace);
						DispEachMode = TRUE;
					}

					lpCurPlayer->chrAttackTarget = lpCharMsTrace;
					lpCurPlayer->AttackExp = 0;

					lpCurPlayer->AttackCritcal = FALSE;


					if (!attack_UserMonster &&
						(lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER ||
							(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE)))
					{

						AttackResult = TRUE;


						if (!PlaySkillAttack(lpAttackSkill, lpCharMsTrace))
						{

							if (attack || lpCharMsTrace->smCharInfo.State != smCHAR_STATE_USER)
							{

								if (lpCurPlayer->ShootingMode && lpCharMsTrace->smCharInfo.State != smCHAR_STATE_NPC)
								{
									if (lpCurPlayer->CheckShootingTest(lpCharMsTrace) == TRUE)
									{

										AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, 0,
											lpCurPlayer->AttackSkil, TRUE);

									}
									else
									{
										lpCurPlayer->AttackCritcal = -1;
										lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_STAND);
									}
								}
								else
								{
									attack_RegState = 0;

									if (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_NPC)
									{
										if (sinQuest_ChangeJob2.CODE)
										{

											attack_RegState = (sinQuest_ChangeJob2.CODE << 16);
											if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M ||
												sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
											{

												if (!cInvenTory.SearchItemCode(sinMA1 | sin01) &&
													!cInvenTory.SearchItemCode(sinQT1 | sin04) &&
													!cInvenTory.SearchItemCode(sinQT1 | sin05))
													attack_RegState |= 1;

											}
										}


										if (dwClassDelayTime < dwPlayTime)
										{
											if (lpCharMsTrace->smCharInfo.wPlayClass[0])
											{
												switch (lpCharMsTrace->smCharInfo.wPlayClass[0])
												{

												case 1001:
													if (lpCurPlayer->smCharInfo.JOB_CODE <= 4 || lpCurPlayer->smCharInfo.JOB_CODE == 9)
														sinCheckLevelQuest30();
													break;
												case 1002:
													if (lpCurPlayer->smCharInfo.JOB_CODE > 4 && lpCurPlayer->smCharInfo.JOB_CODE != 9)
														sinCheckLevelQuest30();
													break;
												case 1003:
													if (lpCurPlayer->smCharInfo.JOB_CODE <= 4 || lpCurPlayer->smCharInfo.JOB_CODE == 9)
														sinCheckLevelQuest55();
													break;
												case 1004:
													if (lpCurPlayer->smCharInfo.JOB_CODE > 4 && lpCurPlayer->smCharInfo.JOB_CODE != 9)
														sinCheckLevelQuest55_2();
													break;
												case 1005:
													sinCheckLevelQuest70();
													sinCheckLevelQuest80();
													sinCheckLevelQuest85();
													break;
												case 1006:
													sinCheckLevelQuest90();
													break;

												case 1010:
													sinCheckLevelQuest80_2(0);
													break;
												case 1011:
													sinCheckLevelQuest80_2(1);
													break;
												case 1012:
													sinCheckLevelQuest80_2(0);
													sinCheckLevelQuest90_2(0);
													break;
												case 1013:
													sinCheckLevelQuest90_2(1);
													chaQuest.showFuryQuest();
													break;
												//case 1023:
												//	cSkinChanger.Open();
													break;
												case 1024:
													cCoinShop_T.Open();
													break;
												}


												HaCheckQuestNpc(lpCharMsTrace->smCharInfo.wPlayClass[0]);

												dwClassDelayTime = dwPlayTime + 1000 * 5;
											}
										}


									}


									AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, attack_RegState,
										lpCurPlayer->AttackSkil, TRUE);

								}


								if ((AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_LIGHTING + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_ICE + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_FIRE + 1))
									&& lpCurPlayer->EnchantEffect_Point > 0 && lpCurPlayer->EnchantEffect_Point <= 10)
								{


									if (lpCurPlayer->AttackCritcal >= 0)
									{

										dm_SelectRange(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 50, TRUE);

										dm_SendRangeDamage(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 0, 0, 0, 0, 0,
											(SKILL_PLAY_ENCHANT_WEAPON | (lpCurPlayer->EnchantEffect_Point << 8)));
									}
								}
							}
							if (!lpAttackSkill && !AttackResult)
							{
								lpCurPlayer->AttackCritcal = -1;
							}
							else
							{

								DamageExp(lpCharMsTrace, AttackResult);
							}
						}
					}


					if (!AttackResult)	lpCurPlayer->AttackCritcal = -1;

					if (!AttCancel)
					{

						lpCurPlayer->MoveFlag = FALSE;
						lpCurPlayer->CriticalLog = lpCurPlayer->AttackCritcal;

						if (lpCharMsTrace && (lpCharMsTrace->smCharInfo.State == smCHAR_STATE_NPC || lpCharMsTrace->dwTradeMsgCode))
						{
							MouseButton[0] = 0;
							MouseButton[1] = 0;
							AttAutoCont = FALSE;
						}

						if (!AttFlag && !AttAutoCont)
						{
							MsTraceMode = 0;
							lpCharMsTrace = 0;
						}
					}
				}
				else
				{
					if (!lpCharMsTrace->Flag || lpCharMsTrace->MotionInfo->State == CHRMOTION_STATE_DEAD)
					{
						lpCharMsTrace = NULL;
						MsTraceMode = 0;
						lpCurPlayer->MoveFlag = FALSE;
						AttAutoCont = FALSE;
					}
				}
			}
		}

		if (lpMsTraceItem)
		{
			if (lpCurPlayer->PlayAttackFromPosi(
				lpMsTraceItem->pX,
				lpMsTraceItem->pY,
				lpMsTraceItem->pZ,
				8000, FALSE) == TRUE)
			{


				smTRANS_ACITON_ITEM		TransActionItem;
				char	szBuff[64];
				int		len;

				TransActionItem.code = OpCode::OPCODE_PUTITEM;
				TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);

				TransActionItem.x = lpMsTraceItem->pX;
				TransActionItem.y = lpMsTraceItem->pY;
				TransActionItem.z = lpMsTraceItem->pZ;
				TransActionItem.lpStgArea = lpMsTraceItem->lpStgArea;



				if (CheckRecvTrnsItemQue() == TRUE)
				{

					cnt = 0;

					if ((lpMsTraceItem->ItemCode & sinITEM_MASK2) == sinCH1)
					{
						switch (lpMsTraceItem->ItemCode)
						{
#ifdef _LANGUAGE_ENGLISH
						case (sinCH1 | sin01):
							if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ATALANTA ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_MALE);
								cnt = 1;
							}
							break;
						case (sinCH1 | sin02):
							if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_FIGHTER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_FEMALE);
								cnt = 1;
							}
							break;

#else
						case (sinCH1 | sin01):
						case (sinCH1 | sin02):

							if (lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ATALANTA &&
								lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ARCHER &&
								lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_PRIESTESS
								&& lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_FEMALE);
								cnt = 1;
							}
							break;
#endif
						case (sinCH1 | sin03):
						case (sinCH1 | sin04):

							if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ATALANTA ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS ||
								lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE)
							{

								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_MALE);
								cnt = 1;

							}
							break;


						}
					}

					if (!cnt)
					{
						if (lpMsTraceItem->ItemCode == (sinGG1 | sin01))
						{
							strcpy_s(szBuff, lpMsTraceItem->szName);
							len = lstrlen(szBuff);
							for (cnt = 0; cnt < len; cnt++)
							{
								if (szBuff[cnt] < '0' || szBuff[cnt]>'9')
								{
									szBuff[cnt] = 0;
									break;
								}
							}
							cnt = atoi(szBuff);
							if (cInvenTory.CheckMoneyLimit(cnt) == TRUE)
							{
								lpsmSock = GetServerSock(lpMsTraceItem->ServerCode);
								if (lpsmSock)
								{
									lpsmSock->Send((char*)&TransActionItem, TransActionItem.size, TRUE);
								}
							}
						}
						else
						{
							lpsmSock = GetServerSock(lpMsTraceItem->ServerCode);
							if (lpsmSock)
							{
								lpsmSock->Send((char*)&TransActionItem, TransActionItem.size, TRUE);
							}
						}
					}
				}

				MsTraceMode = 0;
				lpMsTraceItem = NULL;
				lpCurPlayer->MoveFlag = FALSE;
				MouseButton[0] = 0;
			}
			else
			{
				if (!lpMsTraceItem->Flag)
				{
					lpMsTraceItem = NULL;
					MsTraceMode = 0;
					lpCurPlayer->MoveFlag = FALSE;
				}
			}
		}


	}
	MsTraceCount++;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag)
		{
			chrOtherPlayer[cnt].Main();
			if (chrOtherPlayer[cnt].dwTarget)
			{
				if (lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_DAMAGE &&
					chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_ATTACK)

					lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
			}
		}
	}


#ifdef _WINMODE_DEBUG



	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_SHIFT] && !VRKeyBuff[VK_CONTROL])
	{

		if (VRKeyBuff[VK_F4])
		{
			SetNextPlayerPattern();
			VRKeyBuff[VK_F4] = 0;
		}
		if (VRKeyBuff[VK_F3])
		{
			SetNextNpcPattern();
			VRKeyBuff[VK_F3] = 0;
		}
	}
#endif

	MainFieldMap();

	PlayParticle();

	DynLightMain();

	BGMain();


	BGM_Main();


	SodScoreMain();


	PlayCounter++;

	FieldMain(lpCurPlayer->pX, 0, lpCurPlayer->pZ);


	int fldSky, fflag;

	int	RainTime = 0x200;
	int	RainLength = 60 * 7;
	int	BackSel = 0;

	fldSky = -1;
	fflag = 0;

	if ((PlayCounter & 0xFF) == 0 && lpCurPlayer->dwObjectSerial)
	{




		if (dwSoD_ResultTime < dwPlayTime)
		{

			dwSoD_ResultTime = dwPlayTime + 12000;
			if (cSinHelp.GetSodRankBoxState() == TRUE)
			{
				SendCommand_AreaServer(OpCode::OPCODE_SOD_RESULT2, 0, 0, 0, 0);
			}
		}

		if (cldata.myPosition)
		{
			if (lpCurPlayer->smCharInfo.ClassClan != cldata.intClanMark)
			{
#ifdef  __CLANSUBCHIP__				
				if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
				{
#else
				if (cldata.myPosition == 100 || cldata.myPosition == 101)
				{
#endif

					lpCurPlayer->smCharInfo.ClassClan = cldata.intClanMark;
					lpCurPlayer->dwClanManageBit = cldata.CNFlag;
					lpCurPlayer->smCharInfo.bUpdateInfo[0]++;
					SendUpdateClanInfo();







				}
				else
				{
					cldata.intClanMark = 0;
					lpCurPlayer->smCharInfo.ClassClan = 0;
					lpCurPlayer->smCharInfo.bUpdateInfo[0]++;

					SendUpdateClanInfo();
				}
			}
		}


		if (lpCurPlayer->smCharInfo.wPlayerKilling[0] > 0)
		{
			lpCurPlayer->smCharInfo.wPlayerKilling[0]--;
			if (lpCurPlayer->smCharInfo.wPlayerKilling[0] == 0)
			{


				lpCurPlayer->MoveFlag = FALSE;
				WarpStartField(&x, &z);
				lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;
				lpCurPlayer->SetMotionFromCode(CHRMOTION_STATE_RESTART);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
				SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
				CharPlaySound(lpCurPlayer);


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
			}
		}


		if (WeatherMode == 0)
		{
			if (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_NIGHT)
			{
				BackSel = 2;
			}
			else
			{
				if (dwGameHour >= GAME_HOUR_DAY && dwGameHour < GAME_HOUR_GLOW)
					BackSel = 0;
				else
					BackSel = 1;
			}
		}


		if (lpCurPlayer->OnStageField >= 0)
		{

			if (StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD)
			{

				cnt = rsGetSoD_AreaCode(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
				switch (cnt)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					fldSky = FIELD_BACKIMAGE_SODNONE;
					break;

				case 4:
					fldSky = FIELD_BACKIMAGE_SODSUN;
					break;
				case 5:
					fldSky = FIELD_BACKIMAGE_SODMOON;
					break;
				case 6:
					fldSky = FIELD_BACKIMAGE_SODSKY;
					break;
				}
				if (cnt == 2)
					esPlayEffectBgm(4);
				else
					esPlayEffectBgm(3);

				if (fldSky >= 0) ChangeSky(fldSky);
			}
			else if (StageField[lpCurPlayer->OnStageField]->FieldCode == BabelPlayField && dwBabelPlayTime > dwPlayTime)
			{

				ChangeSky(FIELD_BACKIMAGE_IRONBOSS);
				esPlayEffectBgm(11);
			}
			else
			{
				fldSky = StageField[lpCurPlayer->OnStageField]->BackImageCode[BackSel];

				if (!WeatherMode && fldSky >= 0) ChangeSky(fldSky);

				if (WeatherMode == 0)
				{
					switch (StageField[lpCurPlayer->OnStageField]->State)
					{

					case FIELD_STATE_RUIN:
						esPlayEffectBgm(3);
						break;

					case FIELD_STATE_DESERT:
						esPlayEffectBgm(4);
						break;

					case FIELD_STATE_DUNGEON:
						if (StageField[lpCurPlayer->OnStageField]->FieldCode <= 16 ||
							StageField[lpCurPlayer->OnStageField]->FieldCode == 32)
						{
							esPlayEffectBgm(5);
							break;
						}
						if (StageField[lpCurPlayer->OnStageField]->FieldCode <= 23)
						{
							esPlayEffectBgm(6);
							break;
						}
						if (StageField[lpCurPlayer->OnStageField]->FieldCode <= 25)
						{
							esPlayEffectBgm(7);
							break;
						}
						if (StageField[lpCurPlayer->OnStageField]->FieldCode <= 26)
						{
							esPlayEffectBgm(8);
							break;
						}
						break;


					case FIELD_STATE_FOREST:
						if (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS)
						{
							esPlayEffectBgm(2);
						}
						else
						{
							esPlayEffectBgm(1);
						}
						break;

					case FIELD_STATE_VILLAGE:
						esPlayEffectBgm(0);
						break;

					case FIELD_STATE_ROOM:
						esPlayEffectBgm(-1);
						break;

					case FIELD_STATE_IRON:
						esPlayEffectBgm(9);
						break;

					case FIELD_STATE_ICE:
						esPlayEffectBgm(12);
						break;

					}
				}
				else
					esPlayEffectBgm(-1);

				if (StageField[lpCurPlayer->OnStageField]->BackMusicCode)
					ChangeBGM(StageField[lpCurPlayer->OnStageField]->BackMusicCode);
			}

		}
	}

	if ((PlayCounter & 0x3) == 0)
	{

		if (StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_ROOM &&
			(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS ||
				StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON))
		{
			NightDayTime = 1;
		}
		else
		{
			NightDayTime = 0;
		}

		cnt = DarkLight;
		if (DarkLevel < cnt)
			DarkLevel++;
		if (DarkLevel > cnt)
			DarkLevel--;

		if ((PlayCounter & 0x7) == 0)
		{
			if (BackColor_mR < BackColor_R) BackColor_R--;
			if (BackColor_mR > BackColor_R) BackColor_R++;

			if (BackColor_mG < BackColor_G) BackColor_G--;
			if (BackColor_mG > BackColor_G) BackColor_G++;

			if (BackColor_mB < BackColor_B) BackColor_B--;
			if (BackColor_mB > BackColor_B) BackColor_B++;
		}

		if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		{
			if (DarkLevel_Fix)
				DarkLevel = DarkLevel_Fix;
		}

		if ((PlayCounter & 0xFF) == 0)
		{
			Ptect_GetAttackCount();

			if ((PlayCounter & 0xFFF) == 0)
			{
				if ((PlayCounter & 0x3FFF) == 0)
					SendUsingItemListToServer2();
				else
					SendUsingItemListToServer();
			}

			if (SETTINGSHANDLER->getWeather())
			{
				cnt = dwGameWorldTime & 0x1FFF;

				if (cnt > RainTime && cnt < (RainTime + RainLength))
				{
					if (cnt > RainTime + 60 && cnt < (RainTime + RainLength - 60))
					{
						if (WeatherMode != 2 && (lpCurPlayer->OnStageField >= 0 &&
							StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_DUNGEON &&
							StageField[lpCurPlayer->OnStageField]->FieldCode != rsSOD_FIELD &&
							StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_ICE))
						{

							PlayWav(1, 1, 400, 2205);
							WeatherMode = 2;
							ChangeSky(0);
						}
					}
					else
					{
						switch (WeatherMode)
						{
						case 0:
							ChangeSky(0);
							break;
						case 2:
							StopWav(1);
							break;
						}

						WeatherMode = 1;
					}
				}
				else
					WeatherMode = 0;
			}


			if (lpCurPlayer->smCharInfo.dwEventTime_T)
			{
				if (GetPlayTime_T() > lpCurPlayer->smCharInfo.dwEventTime_T)
				{

					ChangeBigHeadMode(0, 0);
					StartSkill(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 0, 0, 0, SKILL_UP1);
					SkillPlaySound(SKILL_SOUND_LEARN, lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);


					cnt = PlayerArmor;
					PlayerArmor = -1;
					SetPlayerArmor(cnt, -1);

					cInvenTory.IncreViewDamage(0);

					if (RestartPlayCount < 350) RestartPlayCount = 350;
				}
			}


			if (rsRecorder.dwNextRecordTime < dwPlayTime)
			{

				if (GetSaveResult() == TRUE)
				{

					SaveGameData();

				}
			}
			if (rsRecorder.dwRecordTime && (rsRecorder.dwRecordTime + 1000 * 8) < dwPlayTime)
			{
#ifdef _WINMODE_DEBUG
				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("SaveGame TimeOut / Retry SaveGame");
#endif
				RecordFailCount++;

				rsRecorder.dwRecordTime = 0;

				SaveGameData();
			}


			if (!DisconnectFlag && RecordFailCount >= 6)
			{

				SendSetHackUser2(2700, RecordFailCount);
				DisconnectFlag = dwPlayTime;
#ifdef _WINMODE_DEBUG
				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR) AddChatBuff("SaveGame Failed over times");
#endif
			}


			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_FOREST &&
				(dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS) && (PlayCounter & 0x1FF) == 0)
			{

				if (((dwPlayTime >> 3) & 1) == 0)
				{
					StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_BANDI1);
				}
			}
		}


		if (lpCurPlayer->OnStageField >= 0)
		{

			StageField[lpCurPlayer->OnStageField]->PlayAmbient();
		}
		else
		{
			if (ResetLastVolumeDist() > 800)
			{
				esPlayObjectSound2(-1, 0, 0, 0, 0);
			}
		}


	}



	dsMenuCursorPos(&pCursorPos, 4);

	MainInterfaceParty();
	dsMenuCursorPos(&pCursorPos, 0);



	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField])
	{
		StageField[lpCurPlayer->OnStageField]->CheckWarpGate(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);
	}

	if (RestartPlayCount > 0) RestartPlayCount--;


	if ((PlayCounter & 0xFFF) == 0)
	{


		CheckCracker(NULL);

		CheckCharForm();

		if (!lpCurPlayer->HoSkillCode && !lpCurPlayer->dwDispAppSkill)
		{

			if (!dwRotPlayDelayTime || dwRotPlayDelayTime < dwPlayTime)
			{
				smCHAR* lpTempChar;
				smCHAR* lpOldChar;

				lpOldChar = lpCurPlayer;

				lpTempChar = SelectRotPlayer(lpCurPlayer);
				if (lpTempChar)
				{
					lpCurPlayer = lpTempChar;
					sinChar = &lpCurPlayer->smCharInfo;


					for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
					{
						if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].chrAttackTarget == lpOldChar)
							chrOtherPlayer[cnt].chrAttackTarget = lpCurPlayer;
					}

				}
			}
		}
		else
		{
			dwRotPlayDelayTime = dwPlayTime + 30 * 1000;
		}

		CheckEnergyGraphError();
	}


	TimeEffectMain();

	CheckEnergyGraph();




#ifdef	_SET_PROCTECT_MEM2

	if ((PlayCounter & 0x7FF) == 0)
	{

		cnt = Check_PlaySubReleaseFunc();
		if (cnt)
		{
			SendSetHackUser2(1120, cnt);
		}
	}
#endif


	if (dwPartyPosionTime && dwPartyPosionTime < dwPlayTime)
	{

		LaunchPartyPostion();
	}



	if ((PlayCounter & 0x1FF) == 0)
	{
		CheckEnergyGraphError();

		if (AutoMouse_StartCheckTime)
		{
			if ((AutoMouse_StartCheckTime + 30000) < dwPlayTime)
			{

				if (AutoMouse_Distance > 20000 && AutoMouse_Attack_Count > 20 && AutoMouse_WM_Count > 110 && (AutoMouse_LastCheckTime + 30 * 60 * 1000) < dwPlayTime)
				{
					AutoMouse_LastCheckTime = dwPlayTime;

					SendSetHackUser2(8100, AutoMouse_WM_Count);

					if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
					{
						AddChatBuff(">Warning AutoMouse", 0);
					}
				}


				AutoMouse_StartCheckTime = dwPlayTime;
				AutoMouse_WM_Count = 0;
				AutoMouse_Distance = 0;
				AutoMouse_Attack_Count = 0;
			}
		}
		else
		{
			AutoMouse_StartCheckTime = dwPlayTime;
			AutoMouse_WM_Count = 0;
			AutoMouse_Distance = 0;
			AutoMouse_Attack_Count = 0;
		}


	}

	HackTrap_CheckOpenFlag();

#ifdef _TEST_SERVER

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && VRKeyBuff[VK_CONTROL] && VRKeyBuff['N'] && sinGetKeyClick('M'))
	{



		if (!ParkPlaying)
			Play_ParkPlayer("mms:
		else
				Stop_ParkPlayer();

	}
#endif

	return TRUE;
}

extern int BGMatNum[2];
extern int RestoreTexFlag;
extern POINT	pCursorPos;



int GetMouseSelAngle()
{
	int x1, x2, z1, z2;

	if (lpCharMsTrace)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpCharMsTrace->pX >> FLOATNS;
		z2 = lpCharMsTrace->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	if (lpMsTraceItem)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpMsTraceItem->pX >> FLOATNS;
		z2 = lpMsTraceItem->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	return -1;
}


int GetCharAngle(smCHAR * lpChar1, smCHAR * lpChar2)
{
	int x1, x2, z1, z2;

	x1 = lpChar1->pX >> FLOATNS;
	z1 = lpChar1->pZ >> FLOATNS;

	x2 = lpChar2->pX >> FLOATNS;
	z2 = lpChar2->pZ >> FLOATNS;

	return GetRadian2D(x1, z1, x2, z2);
}


int testframe = 0;
int	LastRendSucessCount = 0;
int	DispCharLimitMode = 0;

#define	DISP_CHAR_LIMIT			20
#define	DISP_CHAR_LIMIT_MAX		30
#define	DISP_CHAR_NEAR_DIST		( (10*64)*(10*64) )

int DrawPat3D(int x, int y, int z, int ax, int ay, int az)
{



	int cnt;
	int SelZ;
	int sez;
	RECT	rect;
	RECT	SelRect;
	POINT	SelPos;
	RECT* lpRect;

	smCHAR* lpSelChar;
	scITEM* lpItem;
	int		dx, dz;
	int		pow;

	POINT	sPos;
	int		RendSucessCount;
	int		DispFlag;
	int		r, g, b;
	DWORD	dwDispAppSKill;


	dwDispAppSKill = lpCurPlayer->dwDispAppSkill;
	lpCurPlayer->dwDispAppSkill = 0;

	for (cnt = 0; cnt < 10; cnt++)
	{
		if (ContinueSkill[cnt].Flag)
		{
			switch (ContinueSkill[cnt].CODE)
			{
			case SKILL_EXTREME_SHIELD:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_EXTREME_SHIELD;
				break;

			case SKILL_PHYSICAL_ABSORB:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				break;

			case SKILL_AUTOMATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;

			case SKILL_MAXIMIZE:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;

			case SKILL_CRITICAL_HIT:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;

			case SKILL_HOLY_BODY:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_HOLY_BODY;
				DispApp_SkillPoint = ContinueSkill[cnt].Point;
				break;

			case SKILL_ZENITH:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;

			case SKILL_SPARK_SHIELD:
			case SKILL_DIVINE_INHALATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_SPARK_SHIELD;
				break;

			case SKILL_GODLY_SHIELD:
			case SKILL_FROST_JAVELIN:
			case SKILL_SUMMON_MUSPELL:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_GODLY_SHIELD;
				break;
			}
		}
	}


	if ((lpCurPlayer->dwDispAppSkill & SKILL_APPMASK_PHYSICAL_ABSORB) == 0 && (dwDispAppSKill & SKILL_APPMASK_PHYSICAL_ABSORB) != 0)
	{
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);
	}

	if ((lpCurPlayer->dwDispAppSkill & SKILL_APPMASK_AUTOMATION) == 0 && (dwDispAppSKill & SKILL_APPMASK_AUTOMATION) != 0)
	{
		SkillStopSound(SKILL_SOUND_SKILL_AUTOMATION3);
	}

	if ((lpCurPlayer->dwDispAppSkill & SKILL_APPMASK_HOLY_BODY) == 0 && (dwDispAppSKill & SKILL_APPMASK_HOLY_BODY) != 0)
	{
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);
	}






	SelZ = 65536 * 16384;

	smRender.SetCameraPosi(x, y, z, x, ay, az);
	if (smGameStage[0])
		SetStageDynLight(smGameStage[0], x, y, z);
	if (smGameStage[1])
		SetStageDynLight(smGameStage[1], x, y, z);



	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	if (!DebugPlayer)
	{

		cnt = RestartPlayCount;
		if (lpCurPlayer->PlayInvincible > 0) cnt = lpCurPlayer->PlayInvincible;

		if (cnt && (cnt & 0x10) == 0)
		{
			r = smRender.Color_R;
			g = smRender.Color_G;
			b = smRender.Color_B;

			smRender.Color_R += 80;
			smRender.Color_B += 80;



			lpCurPlayer->Draw();

			smRender.Color_R = r;
			smRender.Color_G = g;
			smRender.Color_B = b;

		}
		else
		{
			if (lpCurPlayer->PlayVanish <= 0) lpCurPlayer->Draw();
		}


		if (rsBlessCastle.dwMasterClan && lpCurPlayer->smCharInfo.ClassClan)
			SetClanMaster_Player(rsBlessCastle.dwMasterClan);

	}

	lpSelChar = 0;
	RendSucessCount = 0;

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].DisplayAlpha == 0)
		{

			DispFlag = TRUE;

			if (DispCharLimitMode)
			{

				dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
				if ((dx * dx + dz * dz) > DISP_CHAR_NEAR_DIST) DispFlag = FALSE;
			}

			if (DispFlag)
			{

				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;


				if (lpCurPlayer->HoSkillCode && chrOtherPlayer[cnt].smCharInfo.Life[0])
				{
					switch (lpCurPlayer->HoSkillCode)
					{
					case SKILL_SCOUT_HAWK:
						pow = GetSkillPower(lpCurPlayer, &chrOtherPlayer[cnt], 0, 0, 0);
						if (pow)
						{


							pow = DarkLevel >> 2;
							smRender.Color_R += 40 + pow;
							smRender.Color_G += 40 + pow;
							smRender.Color_B += 100 + pow;

						}
						break;
					}
				}

				DWORD dwOutlineEffectColor = 0;

				if (lpCharSelPlayer && lpCharSelPlayer == &chrOtherPlayer[cnt])
				{
					smRender.Color_R = r + 40;
					smRender.Color_G = g + 60;
					smRender.Color_B = b + 60;


					if (lpCharSelPlayer->smCharInfo.State == smCHAR_STATE_NPC)
					{
						//Green
						dwOutlineEffectColor = D3DCOLOR_ARGB(255, 0, 255, 100);
					}
					else if (lpCharSelPlayer->smCharInfo.State == smCHAR_STATE_USER)
					{
						//White
						dwOutlineEffectColor = D3DCOLOR_ARGB(255, 255, 255, 255);
					}
					else
					{
						//Red
						dwOutlineEffectColor = D3DCOLOR_ARGB(255, 255, 30, 0);
					}

					/*	int ix = (lpCharSelPlayer->pX - smCHAR_CameraX) >> FLOATNS;
						int iy = (lpCharSelPlayer->pY - smCHAR_CameraY) >> FLOATNS;
						int iz = (lpCharSelPlayer->pZ - smCHAR_CameraZ) >> FLOATNS;

						int Dist = (int)sqrt(ix*ix + iy * iy + iz * iz);
						smRender.SetD3D_OutLine(1, Dist, 1.4f, 0, OutLineColor);*/


				}

				if (!chrOtherPlayer[cnt].RenderLatter && chrOtherPlayer[cnt].AttackIce == 0 && chrOtherPlayer[cnt].RendAlpha == 0 && chrOtherPlayer[cnt].PlayVanish <= 0)
				{


					if (chrOtherPlayer[cnt].PlayInvincible && (chrOtherPlayer[cnt].PlayInvincible & 0x10) == 0)
					{
						smRender.Color_R += 80;
						smRender.Color_B += 80;
					}

					if (dwOutlineEffectColor > 0)
					{
						DX::cSelectGlow1.Begin(dwOutlineEffectColor, TRUE);
						chrOtherPlayer[cnt].Draw();
						DX::cSelectGlow1.End(TRUE);
						DX::cSelectGlow1.Begin(dwOutlineEffectColor, FALSE);
						chrOtherPlayer[cnt].Draw();
						DX::cSelectGlow1.End(FALSE);
					}

					chrOtherPlayer[cnt].Draw();
				}
				else
				{
					if (dwOutlineEffectColor > 0)
					{
						DX::cSelectGlow1.Begin(dwOutlineEffectColor, TRUE);
						chrOtherPlayer[cnt].VirtualDraw();
						DX::cSelectGlow1.End(TRUE);
						DX::cSelectGlow1.Begin(dwOutlineEffectColor, FALSE);
						chrOtherPlayer[cnt].VirtualDraw();
						DX::cSelectGlow1.End(FALSE);
					}

					chrOtherPlayer[cnt].VirtualDraw();
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;



				smRender.SetD3D_OutLine(0);


				if (chrOtherPlayer[cnt].RendSucess)
				{

					RendSucessCount++;

					sez = chrOtherPlayer[cnt].RendPoint.z;
					lpRect = &chrOtherPlayer[cnt].RendRect2D;

					if (chrOtherPlayer[cnt].smCharInfo.Life[0] > 0 && sez > (96 * fONE) && sez < SelZ &&
						lpRect->left<pCursorPos.x && lpRect->right>pCursorPos.x &&
						lpRect->top<pCursorPos.y && lpRect->bottom>pCursorPos.y)
					{

						SelZ = sez;
						lpSelChar = &chrOtherPlayer[cnt];
					}
				}
			}
			else
			{
				chrOtherPlayer[cnt].RendSucess = FALSE;
				RendSucessCount++;
			}
		}
	}


	LastRendSucessCount = RendSucessCount;


	if (DispCharLimitMode)
	{
		if (RendSucessCount < DISP_CHAR_LIMIT)
			DispCharLimitMode = FALSE;
	}
	else
	{
		if (RendSucessCount > DISP_CHAR_LIMIT_MAX)
			DispCharLimitMode = TRUE;
	}

	if (VRKeyBuff['A'])
	{
		lpSelChar = 0;
		SelZ = 65536 * 16384;
	}


	lpItem = 0;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (scItems[cnt].Flag)
		{
			if (scItems[cnt].ItemCode != 0 || DisplayDebug)
			{
				scItems[cnt].Draw();

				smRender.SetCameraPosi(x, y, z, ax, ay, az);

				sez = smRender.GetRect2D(scItems[cnt].pX, scItems[cnt].pY + (16 * fONE), scItems[cnt].pZ,
					32 * fONE, 32 * fONE, &rect, &sPos);

				scItems[cnt].RendPoint.x = sPos.x;
				scItems[cnt].RendPoint.y = sPos.y;
				scItems[cnt].RendPoint.z = sez;

				if (sez > 0 && sez < SelZ &&
					rect.left<pCursorPos.x && rect.right>pCursorPos.x &&
					rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
				{

					SelZ = sez;
					lpItem = &scItems[cnt];
					memcpy(&SelRect, &rect, sizeof(RECT));
					memcpy(&SelPos, &sPos, sizeof(POINT));

					DWORD dwColor = D3DCOLOR_XRGB(255, 255, 0);
					DX::cSelectGlow2.Begin(dwColor, TRUE);
					scItems[cnt].Draw();
					DX::cSelectGlow2.End(TRUE);
					DX::cSelectGlow2.Begin(dwColor, FALSE);
					scItems[cnt].Draw();
					DX::cSelectGlow2.End(FALSE);
				}
			}

		}
	}

	if (lpSelChar)
	{
		lpCharSelPlayer = lpSelChar;
		lpItem = 0;
	}
	else
		lpCharSelPlayer = 0;

	if (lpItem)
	{
		lpSelItem = lpItem;
		memcpy(&MsSelRect, &SelRect, sizeof(RECT));
		memcpy(&MsSelPos, &SelPos, sizeof(POINT));
	}
	else
		lpSelItem = 0;



	if (cShop.OpenFlag || cCharShop.OpenFlag)
	{

		lpCharSelPlayer = 0;
		lpSelItem = 0;

		if (CursorClass == SIN_CURSOR_ATTACK ||
			CursorClass == SIN_CURSOR_TALK ||
			CursorClass == SIN_CURSOR_GETITEM2 ||
			CursorClass == SIN_CURSOR_GETITEM1)
		{

			CursorClass = 1;
		}
		return TRUE;
	}

	if (MouseItem.Flag)
	{
		CursorClass = 0;
	}
	else
	{
		CursorClass = 1;

		if (lpCharSelPlayer)
		{
			switch (lpCharSelPlayer->smCharInfo.State)
			{
			case smCHAR_STATE_ENEMY:

				CursorClass = SIN_CURSOR_ATTACK;
				break;
			case smCHAR_STATE_USER:
				break;
			case smCHAR_STATE_NPC:
				CursorClass = SIN_CURSOR_TALK;
				break;
			}
		}

		if (lpSelItem)
		{
			if (MouseButton[0])
				CursorClass = SIN_CURSOR_GETITEM2;
			else
				CursorClass = SIN_CURSOR_GETITEM1;
		}
	}

	return TRUE;
}

int DrawPat3D_Alpha()
{
	int cnt;
	int DispFlag;
	int dx, dz;
	int ap;
	int	RendFalg;
	int BackFrame;
	int cnt2;



	if (lpCurPlayer->PlayVanish > 0)
	{
		ap = lpCurPlayer->DisplayAlpha;
		lpCurPlayer->DisplayAlpha = -160;

		if (lpCurPlayer->PlayVague)
		{
			SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
			lpCurPlayer->DisplayAlpha = -60;
		}
		lpCurPlayer->Draw();

		SetItem2PassTexture(-1);
		lpCurPlayer->DisplayAlpha = ap;
	}

	if ((lpCurPlayer->AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)
	{
		ap = lpCurPlayer->DisplayAlpha;
		BackFrame = lpCurPlayer->frame;
		lpCurPlayer->DisplayAlpha = -140;
		for (cnt2 = 0; cnt2 < 6; cnt2++)
		{
			lpCurPlayer->frame -= 160 * 2;
			if (lpCurPlayer->frame > (lpCurPlayer->MotionInfo->StartFrame * 160))
			{
				lpCurPlayer->Draw();
			}
			lpCurPlayer->DisplayAlpha -= 20;
		}
		lpCurPlayer->frame = BackFrame;
		lpCurPlayer->DisplayAlpha = ap;
	}

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag)
		{
			RendFalg = 0;
			if (chrOtherPlayer[cnt].DisplayAlpha != 0 || chrOtherPlayer[cnt].RendAlpha != 0 || chrOtherPlayer[cnt].AttackIce != 0 || chrOtherPlayer[cnt].RenderLatter || chrOtherPlayer[cnt].PlayVanish)
			{
				DispFlag = TRUE;

				if (DispCharLimitMode && chrOtherPlayer[cnt].AttackIce == 0)
				{

					dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
					dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
					if ((dx * dx + dz * dz) > DISP_CHAR_NEAR_DIST) DispFlag = FALSE;
				}

				if (chrOtherPlayer[cnt].PlayVanish > 0 && lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD)
				{

					if (lpCharSelPlayer != &chrOtherPlayer[cnt])
					{
						dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
						dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
						if ((dx * dx + dz * dz) > DIST_TRANSLEVEL_NEAR) DispFlag = FALSE;
					}
				}

				if (DispFlag)
				{


					if (lpCharSelPlayer && lpCharSelPlayer == &chrOtherPlayer[cnt])
					{
						DWORD OutLineColor;
						switch (lpCharSelPlayer->smCharInfo.State)
						{
						case smCHAR_STATE_USER:
							OutLineColor = D3DCOLOR_RGBA(0, 255, 100, 255);
							break;

						case smCHAR_STATE_NPC:
							OutLineColor = D3DCOLOR_RGBA(0, 255, 100, 255);
							break;
						case smCHAR_STATE_ENEMY:
							OutLineColor = D3DCOLOR_RGBA(0, 255, 100, 255);
							break;

						default:
							OutLineColor = D3DCOLOR_RGBA(255, 30, 0, 255);
							break;
						}

						int ix = (lpCharSelPlayer->pX - smCHAR_CameraX) >> FLOATNS;
						int iy = (lpCharSelPlayer->pY - smCHAR_CameraY) >> FLOATNS;
						int iz = (lpCharSelPlayer->pZ - smCHAR_CameraZ) >> FLOATNS;

						int Dist = (int)sqrt(ix * ix + iy * iy + iz * iz);
						smRender.SetD3D_OutLine(1, Dist, 1.4f, 0, OutLineColor);
					}


					ap = chrOtherPlayer[cnt].DisplayAlpha;

					if (chrOtherPlayer[cnt].PlayVanish > 0)
					{
						chrOtherPlayer[cnt].DisplayAlpha = -160;
						if (chrOtherPlayer[cnt].PlayVague) SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
					}

					if (chrOtherPlayer[cnt].RendAlpha && ap > chrOtherPlayer[cnt].RendAlpha)
					{

						chrOtherPlayer[cnt].DisplayAlpha = chrOtherPlayer[cnt].RendAlpha;

						if (chrOtherPlayer[cnt].MotionInfo->State >= 0x100 &&
							(chrOtherPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_ILLUSIONKNIGHT || chrOtherPlayer[cnt].PlayVanish > 0))
						{
							chrOtherPlayer[cnt].DisplayAlpha = ap;
						}

						chrOtherPlayer[cnt].Draw();
						chrOtherPlayer[cnt].DisplayAlpha = ap;

					}
					else
					{
						chrOtherPlayer[cnt].Draw();
					}
					RendFalg++;

					SetItem2PassTexture(-1);
					chrOtherPlayer[cnt].DisplayAlpha = ap;


					smRender.SetD3D_OutLine(0);


				}
			}

			if (RendFalg == 0)
			{
				if ((chrOtherPlayer[cnt].AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && chrOtherPlayer[cnt].MotionInfo->State == CHRMOTION_STATE_SKILL)
				{
					ap = chrOtherPlayer[cnt].DisplayAlpha;
					BackFrame = chrOtherPlayer[cnt].frame;
					chrOtherPlayer[cnt].DisplayAlpha = -160;
					for (cnt2 = 0; cnt2 < 4; cnt2++)
					{
						chrOtherPlayer[cnt].frame -= 160 * 4;
						if (chrOtherPlayer[cnt].frame > (chrOtherPlayer[cnt].MotionInfo->StartFrame * 160))
						{
							chrOtherPlayer[cnt].Draw();
						}
					}
					chrOtherPlayer[cnt].frame = BackFrame;
					chrOtherPlayer[cnt].DisplayAlpha = ap;
				}
			}
		}
	}

	return TRUE;
}


int DrawPatShadow(int x, int y, int z, int ax, int ay, int az)
{
	int cnt;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);





	cnt = 0;

	lpCurPlayer->DrawShadow();


	if (lpCurPlayer->OnStageField >= 0)
	{
		if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ICE)
			lpCurPlayer->DrawIceFoot();
	}


	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].DisplayAlpha == 0 && chrOtherPlayer[cnt].RendAlpha == 0)
		{
			chrOtherPlayer[cnt].DrawShadow();
		}
	}



	return TRUE;
}

extern BYTE VRKeyBuff[256];

int Draw2DCounter = 0;

int DrawPat2D(int x, int y, int z, int ax, int ay, int az)
{





	int cnt;

	if (lpCurPlayer->Pattern == 0) return FALSE;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	smRender.SetMaterialGroup(smMaterialGroup);

	for (cnt = 0; cnt < OTHER_PLAYER_MAX; cnt++)
	{
		if (chrOtherPlayer[cnt].Flag)
		{
			chrOtherPlayer[cnt].DrawMotionBlur();
		}
	}

	lpCurPlayer->DrawMotionBlur();

	DrawParticle(x, y, z, ax, ay, az);





	Draw2DCounter++;


	DrawLightImage();

	DrawWeather(ax);


	return TRUE;

}

extern int ViewPointLen;

extern DWORD smBackColor;

int BGFace[2][3] = {
	{ 0 ,  1 , 2 },
	{ 1 ,  3 , 2 }
};


LPDIRECT3DTEXTURE9* hBGTexture;
LPDIRECT3DTEXTURE9* hBGTexture2;
smOBJ3D* smBackGround;

LPDIRECT3DTEXTURE9* BackVideoSurface;
int BackVideoFrame;
int LastFrame;

int BGMatNum[2];


#include "pbackground.h"

smBACKGROUND	smBackMesh[2];
smBACKGROUND* lpCurrentBG;


int InitBackGround()
{




	lpCurrentBG = 0;

	ChangeSky(0);

	return TRUE;
}

int CloseBackGround()
{

	smBackMesh[1].Close();
	smBackMesh[0].Close();
	return TRUE;

}

int BgFrame = 0;

int BGMain()
{
	smBackMesh[0].Main();
	smBackMesh[1].Main();

	if (lpCurrentBG && lpCurrentBG->FadeShowCount == 0)
	{
		if (&smBackMesh[0] != lpCurrentBG && smBackMesh[0].smObjBG)
			smBackMesh[0].Close();

		if (&smBackMesh[1] != lpCurrentBG && smBackMesh[1].smObjBG)
			smBackMesh[1].Close();
	}

	return TRUE;
}

int ChangeBG(int BgNum)
{

	if (!lpCurrentBG)
	{
		smBackMesh[0].Init(BgNum);
		lpCurrentBG = &smBackMesh[0];
		if (smBackMesh[0].lpMaterialGroup)
			smBackMesh[0].lpMaterialGroup->ReadTextures();

		smBackMesh[0].FadeShowCount = 0;

		return TRUE;
	}

	if (lpCurrentBG->BackGroundNum == BgNum) return FALSE;

	if (&smBackMesh[0] != lpCurrentBG && !smBackMesh[0].smObjBG)
	{
		smBackMesh[0].Init(BgNum);
		lpCurrentBG = &smBackMesh[0];
		if (smBackMesh[0].lpMaterialGroup)
			smBackMesh[0].lpMaterialGroup->ReadTextures();
		return TRUE;
	}

	if (&smBackMesh[1] != lpCurrentBG && !smBackMesh[1].smObjBG)
	{
		smBackMesh[1].Init(BgNum);
		lpCurrentBG = &smBackMesh[1];
		if (smBackMesh[1].lpMaterialGroup)
			smBackMesh[1].lpMaterialGroup->ReadTextures();
		return TRUE;
	}

	return FALSE;
}

int DrawBG(int x, int y, int z, int ax, int ay, int az)
{


	if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_DUNGEON) return TRUE;
	if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM) return TRUE;

	GRAPHICDEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);

	if (smBackMesh[0].FadeShowCount > smBackMesh[1].FadeShowCount)
	{
		smBackMesh[0].Draw(x, y, z, ax, ay, az);
		smBackMesh[1].Draw(x, y, z, ax, ay, az);
	}
	else
	{
		smBackMesh[1].Draw(x, y, z, ax, ay, az);
		smBackMesh[0].Draw(x, y, z, ax, ay, az);
	}

	GRAPHICDEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);

	return TRUE;
}


RECT	PartyTradeButtonRect[4] = {
	{	00,0, 20, 20	},
	{	25,0, 20, 20	},
	{	50,0, 20, 20	},
	{	75,0, 20, 20	}
};

RECT	PartyTradeToolTipRect = { 1,18,70,28 };

POINT	PartyButtonPoint = { -1, -1 };


int GetPartyTradeButtonPos(int x, int y)
{
	int cnt, sx;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if (PartyButtonPoint.x < 0) return -1;

	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if (EachTradeButtonMode)
	{
		AdjustX = -10; MaxCnt = 4;
	}
	else
	{
		AdjustX = 0; MaxCnt = 3;
	}

	for (cnt = 0; cnt < MaxCnt; cnt++)
	{
		sx = PartyTradeButtonRect[cnt].left + AdjustX + wx;
		if (sx<x && (sx + PartyTradeButtonRect[cnt].right)>x &&
			PartyTradeButtonRect[cnt].top + wy<y && (PartyTradeButtonRect[cnt].top + wy + PartyTradeButtonRect[cnt].bottom)>y)
		{

			return cnt;

		}
	}

	return -1;
}


int DisplayPartyTradeButton()
{

	int SelNum;
	int cnt;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if (PartyButtonPoint.x < 0) return -1;
	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if (EachTradeButtonMode)
	{
		AdjustX = -10; MaxCnt = 4;
	}
	else
	{
		AdjustX = 0; MaxCnt = 3;
	}

	SelNum = GetPartyTradeButtonPos(pCursorPos.x, pCursorPos.y);

	for (cnt = 0; cnt < MaxCnt; cnt++)
	{
		if (SelNum == cnt)
		{
			if (lpDDS_ParTradeButton[cnt][1])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][1], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
		else
		{
			if (lpDDS_ParTradeButton[cnt][0])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][0], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
	}

	if (SelNum >= 0)
	{
		if (lpDDS_ParTradeToolTip[SelNum])
		{
			DrawSprite(PartyTradeButtonRect[SelNum].left - 60 + AdjustX + wx, PartyTradeToolTipRect.top + wy,
				lpDDS_ParTradeToolTip[SelNum], 0, 0, PartyTradeToolTipRect.right, PartyTradeToolTipRect.bottom);
		}
	}

	return TRUE;
}



smCHAR	chrEachPlayer;
smCHAR* chrEachMaster = 0;
int		EachTradeButton = 0;
int		EachTradeButtonMode = 0;
RECT	RectTradeButton;

POINT3D EachCameraPos;
int	DispEachMode = 0;



int FindBipPoint(smPAT3D * lpPat, char* szObjNodeName, int frame, int* nX, int* nY, int* nZ);


int OpenEachPlayer(smCHAR * lpChar)
{
	if (!lpChar || !lpChar->Flag || !lpChar->DisplayFlag) return FALSE;
	if (EachTradeButton) return FALSE;

	memcpy(&chrEachPlayer, lpChar, sizeof(smCHAR));
	chrEachPlayer.SetMotionFromCode(CHRMOTION_STATE_STAND);
	chrEachPlayer.ActionPattern = 101;
	chrEachMaster = lpChar;

	chrEachPlayer.Flag = TRUE;

	if (FindBipPoint(chrEachPlayer.AnimPattern, "Bip01 Head", chrEachPlayer.frame,
		&EachCameraPos.x, &EachCameraPos.y, &EachCameraPos.z) == NULL)
	{

		EachCameraPos.y = chrEachPlayer.PatHeight - 10 * fONE;
		EachCameraPos.x = 0;
		EachCameraPos.z = 0;
	}


	if (lpChar->smCharInfo.State == smCHAR_STATE_ENEMY || lpChar->smCharInfo.State == smCHAR_STATE_NPC)
	{
		EachCameraPos.y += lpChar->smCharInfo.ArrowPosi[0] * fONE;
		EachCameraPos.z += lpChar->smCharInfo.ArrowPosi[1] * fONE;


	}

	return TRUE;
}


int CloseEachPlayer()
{
	chrEachPlayer.Flag = 0;
	chrEachMaster = 0;
	EachTradeButton = 0;

	return TRUE;
}


int EachPlayerMain()
{
	if (!chrEachMaster || !chrEachMaster->Flag || chrEachMaster->dwObjectSerial != chrEachPlayer.dwObjectSerial ||
		chrEachMaster->Pattern != chrEachPlayer.Pattern)
	{
		CloseEachPlayer();
		return TRUE;
	}

	if (chrEachPlayer.Flag)
	{



		if (DispEachMode)
		{
			if (chrEachPlayer.TalkSoundSum && chrEachPlayer.TalkSoundSum != g_PlayTalkSoundSum)
			{
				PlayTalkSound();
				chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
			}
			else if (chrEachPlayer.TalkPattern && chrEachPlayer.TalkFrame == 0)
			{
				if (IsPlayTalkSound())
					chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
				else
					chrEachPlayer.AutoChangeTalkMotion(FACIAL_MOTION_FILE);
			}
		}
		else
		{
			if (IsPlayTalkSound())
				StopTalkSound();

			chrEachPlayer.TalkSoundSum = 0;
			g_PlayTalkSoundSum = 0;
		}


		chrEachPlayer.Main();


		if (chrEachMaster && chrEachMaster->smCharInfo.State == smCHAR_STATE_NPC)
		{
			if (chrEachMaster->MotionInfo->State == CHRMOTION_STATE_ATTACK && chrEachPlayer.MotionInfo->State == CHRMOTION_STATE_STAND)
				chrEachPlayer.SetMotionFromCode(CHRMOTION_STATE_ATTACK);
		}

		if (chrEachMaster->MotionInfo->State == CHRMOTION_STATE_DEAD && chrEachMaster->FrameCounter > 0x50)
			CloseEachPlayer();

	}

	return TRUE;
}

int DrawClanMark_EachBox(LPDIRECT3DTEXTURE9 clanMark, int x, int y)
{
	RECT ddRect;

	ddRect.left = 0;
	ddRect.right = 16;
	ddRect.top = 0;
	ddRect.bottom = 16;

	if (clanMark)
		DrawSprite(x, y, clanMark, 0, 0, 16, 16, true);

	return TRUE;
}

#include "cTarget.h"
#include "CoinShop.h"


int DrawEachPlayer(float fx, float fy, int SizeMode)
{
	int x, y, z, w, h;
	int mx, my, he;
	POINT3D angle;

	int dist, len;
	HDC	hdc = NULL;
	DWORD	dwColor;
	int		ObjSizeBack;
	int		ModeFlag;
	int		ClanX, ClanY, ClanLen;

	if (chrEachPlayer.Flag && chrEachMaster && chrEachMaster->Flag)
	{
		chrEachPlayer.pX = 0;
		chrEachPlayer.pY = 0;
		chrEachPlayer.pZ = 0;

		chrEachPlayer.Angle.x = 0;
		chrEachPlayer.Angle.y = 0;
		chrEachPlayer.Angle.z = 0;



		if (!SizeMode)
		{
			cTarget.Draw(chrEachMaster);
		}
		else
		{
			mx = MidX;
			my = MidY;

			MidX = (int)((float)WinSizeX * fx);
			MidY = (int)((float)WinSizeY * fy);

			int chrHeight;

			if (chrEachPlayer.smCharInfo.State <= TRUE)
				chrHeight = chrEachPlayer.PatHeight - 8 * fONE;
			else
				chrHeight = chrEachPlayer.PatHeight;

			h = (int)((float)WinSizeY / 2);
			w = (int)((float)WinSizeY * 1.34f / 4);

			w += 20;
			h += 20;

			smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 3;
			smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 2;

			dist = 30 * fONE;
			he = -1 * fONE;

			dist += EachCameraPos.y;


			if (MatEachBox >= 0)
			{

				dsDrawTexImage(MatEachBox, MidX - (w >> 1), MidY - (h >> 1), w, h, 255, 0);//Background da anima��o do npc

				if (!SizeMode)
				{
					if (EachTradeButton)
					{

#ifdef	_NEW_PARTRADE


						PartyButtonPoint.y = MidY + (h >> 1);

						if (EachTradeButtonMode)
						{
							dsDrawTexImage(MatEachMenuBox, MidX - 60, MidY + (h >> 1) - 6, 120, 50, 255, 0);
							PartyButtonPoint.x = MidX - 46;
						}
						else
						{
							dsDrawTexImage(MatEachMenuBox, MidX - 50, MidY + (h >> 1) - 6, 100, 50, 255, 0);
							PartyButtonPoint.x = MidX - 36;
						}




#else

						dsDrawTexImage(MatEachMenuBox, MidX - 50, MidY + 56, 100, 60, 255, 0);

						RectTradeButton.left = MidX - 32;
						RectTradeButton.right = MidX + 32;
						RectTradeButton.top = MidY + 62;
						RectTradeButton.bottom = MidY + 62 + 32;

						if (pCursorPos.x > RectTradeButton.left && pCursorPos.x<RectTradeButton.right &&
							pCursorPos.y>RectTradeButton.top && pCursorPos.y < RectTradeButton.bottom)
						{
							dsDrawTexImage(MatEachTradeButton[1], MidX - 32, MidY + 62, 64, 32, 255, 0);
							EachTradeButton = 2;
						}
						else
						{
							dsDrawTexImage(MatEachTradeButton[0], MidX - 32, MidY + 62, 64, 32, 255, 0);
							EachTradeButton = 1;
						}
#endif
					}
					else
					{
					}

				}

			}

			GRAPHICENGINE->GetDevice()->Clear(0, 0, 2, smBackColor, 1.0f, 0);

			smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + he, dist + EachCameraPos.z, 0, ANGLE_180, 0);

			if (chrEachMaster->MotionInfo->State >= 0x100)
				ModeFlag = TRUE;
			else
				ModeFlag = FALSE;


			if (ModeFlag && chrEachMaster->smCharInfo.State == smCHAR_STATE_NPC && chrEachPlayer.MotionInfo->State == CHRMOTION_STATE_ATTACK)
				ModeFlag = FALSE;


			if (ModeFlag)
			{
				x = chrEachMaster->pX;
				y = chrEachMaster->pY;
				z = chrEachMaster->pZ;
				memcpy(&angle, &chrEachMaster->Angle, sizeof(POINT3D));

				chrEachMaster->pX = 0;
				chrEachMaster->pY = 0;
				chrEachMaster->pZ = 0;
				ZeroMemory(&chrEachMaster->Angle, sizeof(POINT3D));


				ObjSizeBack = chrEachMaster->smCharInfo.wPlayClass[1];
				chrEachMaster->smCharInfo.wPlayClass[1] = 0;

				chrEachMaster->Draw();

				if (ObjSizeBack)
					chrEachMaster->smCharInfo.wPlayClass[1] = ObjSizeBack;

				if (!SizeMode && chrEachMaster->smCharInfo.State && !EachTradeButton)
				{

					chrEachMaster->DrawStateBar(MidX - (w >> 1) + 5, MidY - (h >> 1) + h + 2);

				}

				chrEachMaster->pX = x;
				chrEachMaster->pY = y;
				chrEachMaster->pZ = z;

				memcpy(&chrEachMaster->Angle, &angle, sizeof(POINT3D));
			}
			else
			{
				chrEachPlayer.AttackAnger = chrEachMaster->AttackAnger;

				ObjSizeBack = chrEachPlayer.smCharInfo.wPlayClass[1];
				chrEachPlayer.smCharInfo.wPlayClass[1] = 0;

				chrEachPlayer.Draw();

				chrEachPlayer.smCharInfo.wPlayClass[1] = ObjSizeBack;

				if (!SizeMode && chrEachMaster->smCharInfo.State)
				{

					chrEachMaster->DrawStateBar(MidX - (w >> 1) + 5, MidY - (h >> 1) + h + 2);

				}
			}

			if (SizeMode)
			{

				if (chrEachPlayer.szChatMessage[0])
				{
					dist = lstrlen(chrEachPlayer.szChatMessage);
					if (dist > 34) dist = 34;
					dist >>= 1;
					dist *= 8;
					dist -= 8;

					DrawMessage(MidX - dist, MidY - (h >> 1) + h + 8, chrEachPlayer.szChatMessage, 36, BOX_ONE);
				}
				else
				{
					if (chrEachMaster->szChatMessage[0])
						strcpy_s(chrEachPlayer.szChatMessage, chrEachMaster->szChatMessage);
				}


				len = lstrlen(chrEachPlayer.smCharInfo.szName);
				dist = len >> 1;
				dist *= 8;
				dist -= 8;

				SIZE sizecheck;
				sizecheck.cx = 0;
				sizecheck.cy = 0;
				GetFontTextExtentPoint(NULL, chrEachPlayer.smCharInfo.szName, lstrlen(chrEachPlayer.smCharInfo.szName), &sizecheck);
				dist = sizecheck.cx >> 1;

				SetFontTextColor(RGB(0, 0, 0));
				dsTextLineOut(NULL, MidX - dist + 1, MidY - (h >> 1) + h - 33, chrEachPlayer.smCharInfo.szName, len);
				SetFontTextColor(RGB(255, 255, 180));
				dsTextLineOut(NULL, MidX - dist, MidY - (h >> 1) + h - 32, chrEachPlayer.smCharInfo.szName, len);


			}
			else
			{
				if (!EachTradeButton)
				{
					if (lpCurPlayer->OnStageField >= 0 &&
						StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
					{
						if (chrEachMaster->smCharInfo.State == smCHAR_STATE_USER || chrEachMaster->PkMode_CharState == smCHAR_STATE_USER)
							chaSiege.ShowPickUserKillPoint(MidX - 32, MidY + (h >> 1) + 10, chrEachMaster->sBlessCastle_Damage[1]);
					}
				}

				if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
				{
					ClanLen = lstrlen(ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName);

					ClanX = MidX - 26;
					ClanY = MidY - (h >> 1) + 8;

					DrawClanMark_EachBox(ClanInfo[chrEachPlayer.ClanInfoNum].hClanMark, ClanX - 18, ClanY);

					if (ClanLen < 12)
						ClanX += (12 - ClanLen) << 1;

					ClanY += 2;

					if (pCursorPos.x > (MidX - (w >> 1)) && pCursorPos.y < (MidY + (h >> 1)) && ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanReport[0])
						DrawClanMessage((MidX - (w >> 1)), 14, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanReport, 42, RGB(255, 255, 255));
				}
				else
					ClanLen = 0;

				if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_ENEMY && !chrEachPlayer.smCharInfo.ClassClan)
				{
					len = 0;
					switch (chrEachPlayer.smCharInfo.Brood)
					{
					case smCHAR_MONSTER_MUTANT:
						len = 1;
						break;
					case smCHAR_MONSTER_UNDEAD:
						len = 2;
						break;
					case smCHAR_MONSTER_DEMON:
						len = 3;
						break;
					case smCHAR_MONSTER_MECHANIC:
						len = 4;
						break;

					case smCHAR_MONSTER_USER:
						len = -1;
						break;
					}
					if (len >= 0)
						dsDrawTexImage(MatMonBroodImage[len], MidX + (w / 2) - 24, MidY - (h / 2) + 8, 16, 16, 255, 0);
				}


				len = lstrlen(chrEachPlayer.smCharInfo.szName);
				dist = len >> 1;
				dist *= 8;
				dist -= 8;

				SIZE sizecheck;
				sizecheck.cx = 0;
				sizecheck.cy = 0;
				GetFontTextExtentPoint(NULL, chrEachPlayer.smCharInfo.szName, lstrlen(chrEachPlayer.smCharInfo.szName), &sizecheck);
				dist = sizecheck.cx >> 1;

				SetFontTextColor(RGB(0, 0, 0));
				dsTextLineOut(NULL, MidX - dist + 1, MidY - (h >> 1) + h - 17, chrEachPlayer.smCharInfo.szName, len);

				dwColor = RGB(255, 255, 255);

				switch (chrEachPlayer.smCharInfo.State)
				{
				case TRUE:
					dwColor = RGB(255, 160, 120);
					break;
				case FALSE:
					dwColor = RGB(255, 255, 180);
					break;
				}

				SetFontTextColor(dwColor);

				dsTextLineOut(NULL, MidX - dist, MidY - (h >> 1) + h - 16, chrEachPlayer.smCharInfo.szName, len);

				if (ClanLen)
				{
					SetFontTextColor((0, 0, 0));
					dsTextLineOut(NULL, ClanX + 1, ClanY + 1, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName, ClanLen);
					SetFontTextColor((150, 255, 200));
					dsTextLineOut(NULL, ClanX, ClanY, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName, ClanLen);
				}

				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && cInterFace.sInterFlags.MapOnFlag)
				{
					dwColor = RGB(255, 255, 255);
					SetFontTextColor(dwColor);

#ifdef GAME_GM
					char szBuff[256];

					int ly = SETTINGSHANDLER->getHeight() / 5 + 15;

					wsprintf(szBuff, "N�vel: %d", chrEachPlayer.smCharInfo.Level);


					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Ataque: %d-%d", chrEachPlayer.smCharInfo.Attack_Damage[0], chrEachPlayer.smCharInfo.Attack_Damage[1]);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Defesa: %d", chrEachPlayer.smCharInfo.Defence);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Absor��o: %d", chrEachPlayer.smCharInfo.Absorption);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Dinheiro: %d", chrEachPlayer.smCharInfo.Money);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "EXP: %d", chrEachPlayer.smCharInfo.Exp);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Precis�o: %d", sinGetAccuracy(chrEachPlayer.smCharInfo.Level, chrEachPlayer.smCharInfo.Defence));
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Cr�tico: %d", sinGetCritical(chrEachPlayer.smCharInfo.Level));
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Atualiza��o: %d", chrEachPlayer.smCharInfo.bUpdateInfo[0]);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;
					wsprintf(szBuff, "Cl�: %d(%d)", chrEachPlayer.smCharInfo.ClassClan, chrEachMaster->ClanInfoNum);
					dsTextLineOut(NULL, MidX - 50, ly, szBuff, lstrlen(szBuff));
					ly += 16;

					if (DisplayDebug)
					{

						wsprintf(szBuff, "Frame   :%d", chrEachMaster->frame);
						dsTextLineOut(NULL, MidX - 100, ly, szBuff, lstrlen(szBuff));
						ly += 16;

						wsprintf(szBuff, "RcvMoton:%d,%d", (chrEachMaster->PlayBuffCnt & PLAYBUFF_MASK), (chrEachMaster->PlayBuffPosi_End & PLAYBUFF_MASK));
						dsTextLineOut(NULL, MidX - 100, ly, szBuff, lstrlen(szBuff));
						ly += 16;

						wsprintf(szBuff, "User Code :%d", chrEachMaster->dwObjectSerial);
						dsTextLineOut(NULL, MidX - 100, ly, szBuff, lstrlen(szBuff));
						ly += 16;
					}
#endif
				}

			}



			MidX = mx;
			MidY = my;

			smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
					}
				}

	if (chrEachMaster && chrEachMaster->ActionPattern == 99)
	{
		if ((chrEachMaster->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
		{
			CloseEachPlayer();
			return TRUE;
		}
	}

	if (lpCharMsTrace)
	{
		if (chrEachMaster != lpCharMsTrace)
		{
			EachTradeButton = 0;
			OpenEachPlayer(lpCharMsTrace);
			DispEachMode = 0;
		}
	}
	else
	{
		if (lpCharSelPlayer && (chrEachMaster != lpCharSelPlayer) && (chrEachMaster != &chrPartyPlayer) && !DispEachMode)
		{
			OpenEachPlayer(lpCharSelPlayer);
			DispEachMode = 0;
		}
	}

	if (EachTradeButton && chrEachMaster)
	{

		if (GetTradeDistance(chrEachMaster) == FALSE)
			EachTradeButton = 0;
	}

	return FALSE;
			}
//
//int DrawEachPlayer(float fx, float fy, int SizeMode)
//{
//	int x, y, z, w, h;
//	int mx, my, he;
//	POINT3D angle;
//
//	int dist, len;
//	HDC	hdc = NULL;
//	DWORD	dwColor;
//	int		ObjSizeBack;
//	int		ModeFlag;
//	int		ClanX, ClanY, ClanLen;
//
//	if (cCoinShop.isOpen())
//		return TRUE;
//
//	if (chrEachPlayer.Flag && chrEachMaster && chrEachMaster->Flag)
//	{
//		chrEachPlayer.pX = 0;
//		chrEachPlayer.pY = 0;
//		chrEachPlayer.pZ = 0;
//
//		chrEachPlayer.Angle.x = 0;
//		chrEachPlayer.Angle.y = 0;
//		chrEachPlayer.Angle.z = 0;
//
//		/*mx = MidX;
//		my = MidY;
//
//		MidX = (int)((float)WinSizeX * fx);
//		MidY = (int)((float)WinSizeY * fy);
//
//		int chrHeight;
//
//		if (chrEachPlayer.smCharInfo.State <= TRUE)
//			chrHeight = chrEachPlayer.PatHeight - 8 * fONE;
//		else
//			chrHeight = chrEachPlayer.PatHeight;*/
//
//		if (!SizeMode)
//		{
//			cTarget.Draw(chrEachMaster);
//
//			/*h = (int)((float)WinSizeY / 2);
//			w = (int)((float)WinSizeY*1.34f / 4);
//
//			w += 20;
//			h += 20;
//
//			smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 3;
//			smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 2;
//
//			dist = 30 * fONE;
//			he = -1 * fONE;*/
//		}
//		else
//		{
//
//			/mx = MidX;
//		my = MidY;
//
//			h = (int)((float)WinSizeY / 6);
//			w = (int)((float)WinSizeY*1.34f / 8);
//
//			w += 10;
//			h += 10;
//
//			smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 4;
//
//			smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 6;
//
//			dist = 100 * fONE;
//			he = 3 * fONE;
//		}
//
//		dist += EachCameraPos.y;
//
//
//			if (MatEachBox >= 0)
//			{
//				//GRAPHICDEVICE->BeginScene();
//
//				dsDrawTexImage(MatEachBox, MidX - (w >> 1), MidY - (h >> 1), w, h, 255, 0);
//
//				if (!SizeMode)
//				{
//					if (EachTradeButton)
//					{
//
//#ifdef	_NEW_PARTRADE
//
//
//						PartyButtonPoint.y = MidY + (h >> 1);
//
//						if (EachTradeButtonMode)
//						{
//							dsDrawTexImage(MatEachMenuBox, MidX - 60, MidY + (h >> 1) - 6, 120, 50, 255, 0);
//							PartyButtonPoint.x = MidX - 46;
//						}
//						else
//						{
//							dsDrawTexImage(MatEachMenuBox, MidX - 50, MidY + (h >> 1) - 6, 100, 50, 255, 0);
//							PartyButtonPoint.x = MidX - 36;
//						}
//
//
//
//
//#else
//
//						dsDrawTexImage(MatEachMenuBox, MidX - 50, MidY + 56, 100, 60, 255, 0);
//
//						RectTradeButton.left = MidX - 32;
//						RectTradeButton.right = MidX + 32;
//						RectTradeButton.top = MidY + 62;
//						RectTradeButton.bottom = MidY + 62 + 32;
//
//						if (pCursorPos.x > RectTradeButton.left && pCursorPos.x<RectTradeButton.right &&
//							pCursorPos.y>RectTradeButton.top && pCursorPos.y < RectTradeButton.bottom)
//						{
//							dsDrawTexImage(MatEachTradeButton[1], MidX - 32, MidY + 62, 64, 32, 255, 0);
//							EachTradeButton = 2;
//						}
//						else
//						{
//							dsDrawTexImage(MatEachTradeButton[0], MidX - 32, MidY + 62, 64, 32, 255, 0);
//							EachTradeButton = 1;
//						}
//#endif
//					}
//					else
//					{
//					}
//
//				}
//
//				//GRAPHICDEVICE->EndScene();
//			}
//
//			GRAPHICDEVICE->Clear(0, 0, 2, smBackColor, 1.0f, 0);
//
//			smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + he, dist + EachCameraPos.z, 0, ANGLE_180, 0);
//
//			if (chrEachMaster->MotionInfo->State >= 0x100)
//				ModeFlag = TRUE;
//			else
//				ModeFlag = FALSE;
//
//
//			if (ModeFlag && chrEachMaster->smCharInfo.State == smCHAR_STATE_NPC && chrEachPlayer.MotionInfo->State == CHRMOTION_STATE_ATTACK)
//				ModeFlag = FALSE;
//
//
//			if (ModeFlag)
//			{
//				x = chrEachMaster->pX;
//				y = chrEachMaster->pY;
//				z = chrEachMaster->pZ;
//				memcpy(&angle, &chrEachMaster->Angle, sizeof(POINT3D));
//
//				chrEachMaster->pX = 0;
//				chrEachMaster->pY = 0;
//				chrEachMaster->pZ = 0;
//				ZeroMemory(&chrEachMaster->Angle, sizeof(POINT3D));
//
//
//				ObjSizeBack = chrEachMaster->smCharInfo.wPlayClass[1];
//				chrEachMaster->smCharInfo.wPlayClass[1] = 0;
//
//				chrEachMaster->Draw();
//
//				if (ObjSizeBack)
//					chrEachMaster->smCharInfo.wPlayClass[1] = ObjSizeBack;
//
//				if (!SizeMode && chrEachMaster->smCharInfo.State && !EachTradeButton)
//				{
//					//GRAPHICDEVICE->BeginScene();
//
//					chrEachMaster->DrawStateBar(MidX - (w >> 1) + 5, MidY - (h >> 1) + h + 2);
//					//GRAPHICDEVICE->EndScene();
//
//				}
//
//				chrEachMaster->pX = x;
//				chrEachMaster->pY = y;
//				chrEachMaster->pZ = z;
//
//				memcpy(&chrEachMaster->Angle, &angle, sizeof(POINT3D));
//			}
//			else
//			{
//				chrEachPlayer.AttackAnger = chrEachMaster->AttackAnger;
//
//				ObjSizeBack = chrEachPlayer.smCharInfo.wPlayClass[1];
//				chrEachPlayer.smCharInfo.wPlayClass[1] = 0;
//
//				chrEachPlayer.Draw();
//
//				chrEachPlayer.smCharInfo.wPlayClass[1] = ObjSizeBack;
//
//				if (!SizeMode && chrEachMaster->smCharInfo.State)
//				{
//					//GRAPHICDEVICE->BeginScene();
//					chrEachMaster->DrawStateBar(MidX - (w >> 1) + 5, MidY - (h >> 1) + h + 2);
//					//GRAPHICDEVICE->EndScene();
//
//				}
//			}
//
//			if (SizeMode)
//			{
//
//				if (chrEachPlayer.szChatMessage[0])
//				{
//					dist = lstrlen(chrEachPlayer.szChatMessage);
//					if (dist > 34) dist = 34;
//					dist >>= 1;
//					dist *= 8;
//					dist -= 8;
//
//					DrawMessage(MidX - dist, MidY - (h >> 1) + h + 8, chrEachPlayer.szChatMessage, 36, BOX_ONE);
//				}
//				else
//				{
//					if (chrEachMaster->szChatMessage[0])
//						strcpy_s(chrEachPlayer.szChatMessage, chrEachMaster->szChatMessage);
//				}
//
//				//GRAPHICDEVICE->lpDDSBack->GetDC(&hdc);
//			//	SelectObject(hdc, hFont);
//			//	SetBkMode(hdc, TRANSPARENT);
//
//				len = lstrlen(chrEachPlayer.smCharInfo.szName);
//				dist = len >> 1;
//				dist *= 8;
//				dist -= 8;
//
//				SIZE sizecheck;
//				sizecheck.cx = 0;
//				sizecheck.cy = 0;
//				GetFontTextExtentPoint32(hdc, chrEachPlayer.smCharInfo.szName, lstrlen(chrEachPlayer.smCharInfo.szName), &sizecheck);
//				dist = sizecheck.cx >> 1;
//
//				SetFontTextColor( RGB(0, 0, 0));
//				dsTextLineOut(0, MidX - dist + 1, MidY - (h >> 1) + h - 33, chrEachPlayer.smCharInfo.szName, len);
//				SetFontTextColor( RGB(255, 255, 180));
//				dsTextLineOut(0, MidX - dist, MidY - (h >> 1) + h - 32, chrEachPlayer.smCharInfo.szName, len);
//
//				//GRAPHICDEVICE->lpDDSBack->ReleaseDC(hdc);
//
//			}
//			else
//			{
//				if (!EachTradeButton)
//				{
//					if (lpCurPlayer->OnStageField >= 0 &&
//						StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
//					{
//						if (chrEachMaster->smCharInfo.State == smCHAR_STATE_USER || chrEachMaster->PkMode_CharState == smCHAR_STATE_USER)
//							chaSiege.ShowPickUserKillPoint(MidX - 32, MidY + (h >> 1) + 10, chrEachMaster->sBlessCastle_Damage[1]);
//					}
//				}
//
//				if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
//				{
//					ClanLen = lstrlen(ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName);
//
//					ClanX = MidX - 26;
//					ClanY = MidY - (h >> 1) + 8;
//
//					//GRAPHICDEVICE->BeginScene();
//					DrawClanMark_EachBox(ClanInfo[chrEachPlayer.ClanInfoNum].hClanMark, ClanX - 18, ClanY);
//					//GRAPHICDEVICE->EndScene();
//
//					if (ClanLen < 12)
//						ClanX += (12 - ClanLen) << 1;
//
//					ClanY += 2;
//
//					if (pCursorPos.x > (MidX - (w >> 1)) && pCursorPos.y < (MidY + (h >> 1)) && ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanReport[0])
//						DrawClanMessage((MidX - (w >> 1)), 14, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanReport, 42, RGB(255, 255, 255));
//				}
//				else
//					ClanLen = 0;
//
//				if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_ENEMY && !chrEachPlayer.smCharInfo.ClassClan)
//				{
//					len = 0;
//					switch (chrEachPlayer.smCharInfo.Brood)
//					{
//					case smCHAR_MONSTER_MUTANT:
//						len = 1;
//						break;
//					case smCHAR_MONSTER_UNDEAD:
//						len = 2;
//						break;
//					case smCHAR_MONSTER_DEMON:
//						len = 3;
//						break;
//					case smCHAR_MONSTER_MECHANIC:
//						len = 4;
//						break;
//
//					case smCHAR_MONSTER_USER:
//						len = -1;
//						break;
//					}
//					if (len >= 0)
//						dsDrawTexImage(MatMonBroodImage[len], MidX + (w / 2) - 24, MidY - (h / 2) + 8, 16, 16, 255, 0);
//				}
//
//				//GRAPHICDEVICE->lpDDSBack->GetDC(&hdc);
//			//	SelectObject(hdc, hFont);
//			//	SetBkMode(hdc, TRANSPARENT);
//
//				len = lstrlen(chrEachPlayer.smCharInfo.szName);
//				dist = len >> 1;
//				dist *= 8;
//				dist -= 8;
//
//				SIZE sizecheck;
//				sizecheck.cx = 0;
//				sizecheck.cy = 0;
//				GetFontTextExtentPoint32(hdc, chrEachPlayer.smCharInfo.szName, lstrlen(chrEachPlayer.smCharInfo.szName), &sizecheck);
//				dist = sizecheck.cx >> 1;
//
//				SetFontTextColor( RGB(0, 0, 0));
//				dsTextLineOut(0,MidX - dist + 1, MidY - (h >> 1) + h - 17, chrEachPlayer.smCharInfo.szName, len);
//
//				dwColor = RGB(255, 255, 255);
//
//				switch (chrEachPlayer.smCharInfo.State)
//				{
//				case TRUE:
//					dwColor = RGB(255, 160, 120);
//					break;
//				case FALSE:
//					dwColor = RGB(255, 255, 180);
//					break;
//				}
//
//				SetFontTextColor(dwColor);
//
//				dsTextLineOut(0,MidX - dist, MidY - (h >> 1) + h - 16, chrEachPlayer.smCharInfo.szName, len);
//
//				if (ClanLen)
//				{
//					SetFontTextColor( RGB(0, 0, 0));
//					dsTextLineOut(0,ClanX + 1, ClanY + 1, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName, ClanLen);
//					SetFontTextColor(RGB(150, 255, 200));
//					dsTextLineOut(0,ClanX, ClanY, ClanInfo[chrEachPlayer.ClanInfoNum].ClanInfoHeader.ClanName, ClanLen);
//				}
//
//				//Configurar porcentagem de life no mob
//				if (chrEachMaster->smCharInfo.State == smCHAR_STATE_ENEMY)
//				{
//					char BuffLocal[256];
//
//					int refTela = smScreenHeight / 5 + 15;
//
//					float life = (((float)chrEachMaster->smCharInfo.Life[0] / (float)chrEachMaster->smCharInfo.Life[1]) * (float)100);
//
//					double life2;
//					int life3;
//
//					if (life > 1)
//					{
//						life2 = fmod(life, (int)life);
//						life3 = (int)(life2 * 100);
//						if (life2 > 0.1f)
//						{
//							wsprintf(BuffLocal, "%d.%d%s", (int)life, life3, "%");
//						}
//						else
//						{
//							wsprintf(BuffLocal, "%d.0%d%s", (int)life, life3, "%");
//						}
//
//					}
//					else
//					{
//						life3 = (int)(life * 100);
//
//						wsprintf(BuffLocal, "0.%d%s", life3, "%");
//					}
//
//					dwColor = RGB(255, 255, 255);
//
//					FontType = 2;
//					SetFontTextColor(dwColor);
//
//					unsigned int stageChar = StageField[lpCurPlayer->OnStageField]->FieldCode;
//
//					if (!Battle::GetInstance()->isBoss(chrEachMaster->smCharInfo))
//					{
//						dsTextLineOut(0,MidX - 22, refTela - 17, BuffLocal, lstrlen(BuffLocal));
//					}
//					FontType = 0;
//
//				}
//
//				if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR && cInterFace.sInterFlags.MapOnFlag)
//				{
//					dwColor = RGB(255, 255, 255);
//					SetFontTextColor( dwColor);
//
//#ifdef _WINMODE_DEBUG
//					char szBuff[256];
//
//					int ly = smScreenHeight / 5 + 15;
//
//					wsprintf(szBuff, "N�vel: %d", chrEachPlayer.smCharInfo.Level);
//
//
//					dsTextLineOut(0,MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Ataque: %d-%d", chrEachPlayer.smCharInfo.Attack_Damage[0], chrEachPlayer.smCharInfo.Attack_Damage[1]);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Defesa: %d", chrEachPlayer.smCharInfo.Defence);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Absor��o: %d", chrEachPlayer.smCharInfo.Absorption);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Dinheiro: %d", chrEachPlayer.smCharInfo.Money);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "EXP: %d", chrEachPlayer.smCharInfo.Exp);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Precis�o: %d", sinGetAccuracy(chrEachPlayer.smCharInfo.Level, chrEachPlayer.smCharInfo.Defence));
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Cr�tico: %d", sinGetCritical(chrEachPlayer.smCharInfo.Level));
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Atualiza��o: %d", chrEachPlayer.smCharInfo.bUpdateInfo[0]);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//					wsprintf(szBuff, "Cl�: %d(%d)", chrEachPlayer.smCharInfo.ClassClan, chrEachMaster->ClanInfoNum);
//					dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff));
//					ly += 16;
//
//					if (DisplayDebug)
//					{
//
//						wsprintf(szBuff, "Frame   :%d", chrEachMaster->frame);
//						dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff));
//						ly += 16;
//
//						wsprintf(szBuff, "RcvMoton:%d,%d", (chrEachMaster->PlayBuffCnt & PLAYBUFF_MASK), (chrEachMaster->PlayBuffPosi_End & PLAYBUFF_MASK));
//						dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff));
//						ly += 16;
//
//						wsprintf(szBuff, "User Code :%d", chrEachMaster->dwObjectSerial);
//						dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff));
//						ly += 16;
//					}
//#endif
//				}
//
//
//
//				//GRAPHICDEVICE->lpDDSBack->ReleaseDC(hdc);
//			}
//
//			//MidX = mx;
//			//MidY = my;
//
//			//if(Settings::getInstance()->isWideScreen())
//			//{
//			//	smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
//			//}
//			//else
//			//{
//			//	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
//
//
//			MidX = mx;
//			MidY = my;
//
//			smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
//			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
//					}
//
//	if (chrEachMaster && chrEachMaster->ActionPattern == 99)
//	{
//		if ((chrEachMaster->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
//		{
//			CloseEachPlayer();
//			return TRUE;
//		}
//	}
//
//	if (lpCharMsTrace)
//	{
//		if (chrEachMaster != lpCharMsTrace)
//		{
//			EachTradeButton = 0;
//			OpenEachPlayer(lpCharMsTrace);
//			DispEachMode = 0;
//		}
//	}
//	else
//	{
//		if (lpCharSelPlayer && (chrEachMaster != lpCharSelPlayer) && (chrEachMaster != &chrPartyPlayer) && !DispEachMode)
//		{
//			OpenEachPlayer(lpCharSelPlayer);
//			DispEachMode = 0;
//		}
//	}
//
//	if (EachTradeButton && chrEachMaster)
//	{
//
//		if (GetTradeDistance(chrEachMaster) == FALSE)
//			EachTradeButton = 0;
//	}
//
//	return FALSE;
//}
//


int FindBipPoint(smPAT3D * lpPat, char* szObjNodeName, int frame, int* nX, int* nY, int* nZ)
{
	smOBJ3D* lpObj = lpPat->GetObjectFromName(szObjNodeName);
	if (!lpObj) return FALSE;


	smMATRIX* mWorld;
	POINT3D angle;

	ZeroMemory(&angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180) & ANGCLIP;

	mWorld = &lpObj->mWorld;

	AnimObjectTree(lpObj, frame, angle.x, angle.y, angle.z);

	*nX = mWorld->_41;
	*nZ = mWorld->_42;
	*nY = mWorld->_43;

	return TRUE;
}


int Record_ClinetLogFile(char* szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, "game.log", st.wMonth, st.wDay);

	hFile = CreateFile("game.log", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d-%d (%d:%d:%d) - %s", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if (szBuff[len - 1] != '\n')
	{
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}


#include "TJBOY\\park\\ParkDXplayer.h"

int ParkPlayInit = 0;
int ParkPlayMode = 0;
int ParkPlaying = 0;
RECT ParkPlayRect;


int Init_ParkPlayer()
{

	ParkPlayInit = TRUE;
	ParkDXPlay.InitPlayer();
	ParkPlayMode = 0;
	ParkPlaying = 0;
	ParkPlayRect.left = 0;
	ParkPlayRect.top = 0;
	ParkPlayRect.right = WinSizeX;
	ParkPlayRect.bottom = WinSizeY;

	return TRUE;



}


int Play_ParkPlayer(char* szPath, int x, int y, int w, int h, int PlayMode)
{
	if (ParkPlaying)
		Stop_ParkPlayer();

	Init_ParkPlayer();

	if (ParkDXPlay.LoadPlayerFile(hwnd, szPath))
	{
		ParkDXPlay.PlaySize(x, y, w, h);
		ParkDXPlay.PlayPlayer();
		ParkPlayMode = PlayMode;
		ParkPlaying = TRUE;

		ParkPlayRect.left = x;
		ParkPlayRect.top = y;
		ParkPlayRect.right = x + w;
		ParkPlayRect.bottom = y + h;

		return TRUE;
	}

	return FALSE;
}


int Stop_ParkPlayer()
{
	ParkDXPlay.StopPlayer();
	ParkPlayMode = 0;
	ParkPlaying = FALSE;

	return TRUE;
}
