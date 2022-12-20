


#include "sinLinkHeader.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "..\\field.h"
#include "Server\\onserver.h"
#include "CoinShop.h"


#ifdef _XTRAP_GUARD_4_CLIENT 
#include "..\\XTrapSrcD5\\ClientExt\\XTrap4ClientExt1.h"	
#endif

#define MAX_MONEY 1000000000

//Set Boss

int LValRing = 0;
int RValRing = 0;
int KelAmulet = 0;
int LShyRing = 0;
int RShyRing = 0;
int TullaAmulet = 0;
int SetBonus1;
int SetBonus2;

int LbuttonUpCheckFlag = 0;

int sinInterHeight2 = -50;

int sinTempDamage2[2] = { 0,0 };
int sinTempAbsorb = 0;
int sinTempBlock = 0;

sITEMINFO TempLinkCoreItem;
POINT UnionCorePosi = { 0,0 };
int   sinOverWeightCnt = 0;
int sinMyShopItemPass = 0;



int nName = 0;
int nYesButton = 0;
int nNoButton = 0;
int BackUpPosX, BackUpPosY = 0;
int BackUpButton2X, BackUpButton2Y = 0;
int BackUpButton3X, BackUpButton3Y = 0;

extern float mana_regen_true;
extern float life_regen_true;
extern float stam_regen_true;

cINVENTORY	cInvenTory;

sINVENTORY_EFFECT	sInven_Effect[MAX_INVEN_PARTICLE];
sINVENTORY_EFFECT   UnionCore_Effect[100];
sINVENTORY_EFFECT   UnionCore_Effect_Bone[10];
sINVENTORY_EFFECT   UnionCore_Effect_Bomb[50];
TRANS_CHATMESSAGE	TransChatMessage;

sINVENTORY_EFFECT   ForceOrb_Effect;
int MatForceOrbEffect[8] = { 0 };
sITEM MyShopMouseItem;

sELEMENT_ATTACK	sElement_Attack;
sUNIONCORE_EFFECT   sUCore_Effect[10];

int StartX;
int StartY;

int EndX;
int EndY;

int ColorIndex;
RECT ColorRect = { 0,0,0,0 };

int CrashItemIndex[2] = { 0,0 };
int AutoSetItemIndex = 0;

int SelectInvenItemIndex = 0;

int SelectPotionIndex = 0;

int ArrowState[2] = { 0,0 };

int InvenArrowPosi = 0;

sITEM *pUsePotion = 0;

int sinLoadOK = 0;

int PotionIndex = 0;

sITEM *sinPosionItem = 0;
int BackUpItemIndex = 0;
int NotPotionFlag = 0;

char sinTestBuff[128];

int GhostPotionCheckFlag = 0;

int sinChangeSetFlag = 0;

int sinUsePotionDelayFlag = 0;
int PotionCheckNumJumpFlag = 1;


int sinUndeadAbsorb = 0;

int sinItemPickUpDelayFlag = 0;
float   sinAdd_fMagic_Mastery = 0;
int sinDamageFunction[3] = { 0,0,0 };

LPDIRECT3DTEXTURE9	lpInvenMain;

LPDIRECT3DTEXTURE9	lpUnionCoreEffect[4];

int MatUnionCoreEffect = 0;

LPDIRECT3DTEXTURE9   lpGold7 = 0;
LPDIRECT3DTEXTURE9   lpExp7 = 0;


LPDIRECT3DTEXTURE9   lpSpecialItem[2];
LPDIRECT3DTEXTURE9   lpSpecialItemInfo[2];

LPDIRECT3DTEXTURE9	lpCostumeButton;
LPDIRECT3DTEXTURE9	lpCostumeInfo;
LPDIRECT3DTEXTURE9	lpCostume;

LPDIRECT3DTEXTURE9   lpSpecialInven;


int IndiShopIconFlag = 0;


sWINGQUEST sWingQuest[MAX_WINGQUEST] = {
	#include "sinWingItem.h"
};


int SpecialItemShowFlag = 0;
int NotChangeSetItemFlag = 0;
int PuzzleOkFlag = 0;

int PuzzleOkY = 0;

int sinTestFlag2 = 0;




sINVENTORY sInven[INVENTORY_MAX_POS] = {
	{ INVENTORY_POS_RHAND  ,{ 574 + 1 , 433 + 1 , 640 , 544 } },// 0
	{ INVENTORY_POS_LHAND  ,{ 722 + 1 , 433 + 1 , 788 , 544 } },// 1
	{ INVENTORY_POS_ARMOR  ,{ 648 + 1 , 433 + 1 , 714 , 544 } }, //2
	{ INVENTORY_POS_AMULET ,{ 304 + 1 , 438 + 1 , 326 , 460 } },
	{ INVENTORY_POS_RRING  ,{ 356 + 1 , 438 + 1 , 378 , 460 } },
	{ INVENTORY_POS_LRING  ,{ 330 + 1 , 438 + 1 , 352 , 460 } },
	{ INVENTORY_POS_SHELTOM,{ 382 + 1 , 438 + 1 , 404 , 460 } },
	{ INVENTORY_POS_ARMLET ,{ 411 + 1 , 438 + 1 , 455 , 482 } },
	{ INVENTORY_POS_GLOVES ,{ 462 + 1 , 438 + 1 , 506 , 482 } },
	{ INVENTORY_POS_BOOTS  ,{ 513 + 1 , 438 + 1 , 557 , 482 } },
	{ INVENTORY_POS_POTION ,{ 495   , 565   , 495 + 26 , 565 + 26 } },
	{ INVENTORY_POS_POTION ,{ 495 + 26 , 565  , 495 + 26 + 26 , 565 + 26 } },
	{ INVENTORY_POS_POTION ,{ 495 + 26 + 26 , 565 , 495 + 26 + 26 + 26 , 565 + 26 } },
	{ INVENTORY_POS_COSTUME ,{ 648 + 1 , 433 + 1 , 714 , 544 } },
	//{INVENTORY_POS_WingRight  ,{ 535 + 1 , 488 + 1 , 557 , 510 } }, //15
	{ INVENTORY_POS_EARRINGSL  ,{ 508 + 1 , 489 + 1 , 530 , 511 } },
	{ INVENTORY_POS_EARRINGSR  ,{ 535 + 1 , 489 + 1 , 557 , 511 } },
};


int ArrowPosi[10][4] = {
	{ 26,572,26 + 22,591 },
	{ 48,572,48 + 22,591 },
	{ 519,514,538,533 },
	{ 541,514,560,533 },
	{ 266,572,266 + 22,591 },
	{ 302,467,321,486 },
	{ 120,572,120 + 20,591 },
	{ 70,572,70 + 22,591 },
	{ 98,572,98 + 22,591 },
	{ 497,514,517,545 },
};


int InvenTextPosi[2][4] = {
	{121,579,209,592},
	{322,473,404,486},

};

//Referencia level das forces

int ForceOrbUseLevel[][2] =
{
	{ 0,0 },
	{ 1,19 },   // Lucidy
	{ 1,29 },   // Sereno
	{ 1,39 },   // Fadeo
	{ 1,49 },   // Sparky
	{ 50,CHAR_LEVEL_MAX },  // Raident
	{ 50,CHAR_LEVEL_MAX },  // Transparo
	{ 50,CHAR_LEVEL_MAX },  // Murky
	{ 55,CHAR_LEVEL_MAX },  // Devine
	{ 60,CHAR_LEVEL_MAX },  // Celesto
	{ 65,CHAR_LEVEL_MAX },  // Miraje
	{ 70,CHAR_LEVEL_MAX },  // Inferna
	{ 90,CHAR_LEVEL_MAX },  // Enigma
	{ 95,CHAR_LEVEL_MAX },  // Bellum
	{ 100,CHAR_LEVEL_MAX },  // Ordo
	{ 100,CHAR_LEVEL_MAX },  // Ira
	{ 100,CHAR_LEVEL_MAX },  // Tera
	{ 100,CHAR_LEVEL_MAX },  // Tera
	{ 100,CHAR_LEVEL_MAX }  // Guardi�
};


int MagicForceOrbUseLevel[][2] = {
	{1,19},{1,29},{1,39},{1,49},{50,200},{50,200},{60,200},{70,200},{80,200},{80,200},{90,200},{90,200},
};



int BillingMagicForceOrbUseLevel[][2] = {
	{1,200},{1,200},{1,200},
};

int ForceOrbUseTime[] = { 500,500,500,500,700,900,1800,2400,3600,3600,3600,3600,3600,3600,3600,3600 };


int MagicForceOrbUseTime[] = { 500,500,500,500,700,900,1800,2400,3600,3600,3600,3600,3600,3600 };


int BillingMagicForceOrbUseTime[] = { 3600, 10800, 86400 };

int ForceOrbDamage[] = { 0,2,4,7,10,15,25,40,60,80,100,120,140,160,180,180,200,220,240 };
int ForceOrbDamagePerc[] = { 0,0,0,0,0,0,0,10,10,10,10,15,15,15,15,20,22,24,26 };

int MagicForceOrbDamage[] = { 2,4,7,10,15,25,40,60,80,100,120,140,160,180,200,220 };
int BillingMagicForceOrbDamage[] = { 0,0,0 };

int BoosterItem_UseTime[] = { 3600,10800,86400 };
int BoosterItem_DataPercent[] = { 15,15,15 };


int nSkillDelay_UseTime[] = { 300,10800,86400 };


#define NUM_COSTUMES 139

enum ECostumeClass
{
	CLASS_Male,
	CLASS_Female,
};

struct sCOSTUME
{
	char			  szItemCode[16];
	ECostumeClass	  eCostumeClass;
};

sCOSTUME saCostume[NUM_COSTUMES] =
{
	{ "ca131", CLASS_Male },
	{ "ca135", CLASS_Male },
	{ "ca143", CLASS_Male },
	{ "ca154", CLASS_Male },
	{ "ca166", CLASS_Male },
	{ "ca167", CLASS_Male },
	{ "ca185", CLASS_Male },
	{ "ca186", CLASS_Male },
	{ "ca189", CLASS_Male },
	{ "ca190", CLASS_Male },
	{ "ca193", CLASS_Male },
	{ "ca194", CLASS_Male },

	{ "ca232", CLASS_Male },
	{ "ca235", CLASS_Male },
	{ "ca243", CLASS_Male },
	{ "ca266", CLASS_Male },
	{ "ca267", CLASS_Male },
	{ "ca285", CLASS_Male },
	{ "ca286", CLASS_Male },
	{ "ca289", CLASS_Male },

	{ "ca290", CLASS_Male },
	{ "ca293", CLASS_Male },
	{ "ca294", CLASS_Male },
	{ "ca501", CLASS_Male },
	{ "ca503", CLASS_Male },
	{ "ca504", CLASS_Male },
	{ "ca507", CLASS_Male },
	{ "ca509", CLASS_Male },

	{ "ca510", CLASS_Male },
	{ "ca515", CLASS_Male },
	{ "ca517", CLASS_Male },
	{ "ca518", CLASS_Male },
	{ "ca521", CLASS_Male },
	{ "ca522", CLASS_Male },
	{ "ca525", CLASS_Male },
	{ "ca526", CLASS_Male },

	{ "ca531", CLASS_Male },
	{ "ca532", CLASS_Male },
	{ "ca535", CLASS_Male },
	{ "ca536", CLASS_Male },
	{ "ca539", CLASS_Male },
	{ "ca540", CLASS_Male },
	{ "ca543", CLASS_Male },
	{ "ca544", CLASS_Male },

	{ "ca547", CLASS_Male },
	{ "ca549", CLASS_Male },
	{ "ca601", CLASS_Male },
	{ "ca603", CLASS_Male },
	{ "ca604", CLASS_Male },
	{ "ca607", CLASS_Male },
	{ "ca609", CLASS_Male },
	{ "ca610", CLASS_Male },

	{ "ca615", CLASS_Male },
	{ "ca617", CLASS_Male },
	{ "ca618", CLASS_Male },
	{ "ca621", CLASS_Male },
	{ "ca622", CLASS_Male },
	{ "ca625", CLASS_Male },
	{ "ca626", CLASS_Male },
	{ "ca631", CLASS_Male },

	{ "ca632", CLASS_Male },
	{ "ca635", CLASS_Male },
	{ "ca636", CLASS_Male },
	{ "ca639", CLASS_Male },
	{ "ca640", CLASS_Male },
	{ "ca643", CLASS_Male },
	{ "ca644", CLASS_Male },
	{ "ca647", CLASS_Male },
	{ "ca649", CLASS_Male },

	{ "ca133", CLASS_Female },
	{ "ca137", CLASS_Female },
	{ "ca145", CLASS_Female },
	{ "ca155", CLASS_Female },
	{ "ca168", CLASS_Female },
	{ "ca169", CLASS_Female },
	{ "ca187", CLASS_Female },
	{ "ca188", CLASS_Female },
	{ "ca191", CLASS_Female },

	{ "ca192", CLASS_Female },
	{ "ca195", CLASS_Female },
	{ "ca196", CLASS_Female },
	{ "ca234", CLASS_Female },
	{ "ca237", CLASS_Female },
	{ "ca245", CLASS_Female },
	{ "ca255", CLASS_Female },
	{ "ca268", CLASS_Female },
	{ "ca269", CLASS_Female },

	{ "ca287", CLASS_Female },
	{ "ca288", CLASS_Female },
	{ "ca291", CLASS_Female },
	{ "ca292", CLASS_Female },
	{ "ca295", CLASS_Female },
	{ "ca296", CLASS_Female },
	{ "ca502", CLASS_Female },
	{ "ca505", CLASS_Female },
	{ "ca506", CLASS_Female },
	{ "ca508", CLASS_Female },
	{ "ca511", CLASS_Female },
	{ "ca512", CLASS_Female },
	{ "ca516", CLASS_Female },

	{ "ca519", CLASS_Female },
	{ "ca520", CLASS_Female },
	{ "ca523", CLASS_Female },
	{ "ca524", CLASS_Female },
	{ "ca527", CLASS_Female },
	{ "ca528", CLASS_Female },
	{ "ca533", CLASS_Female },
	{ "ca534", CLASS_Female },
	{ "ca537", CLASS_Female },
	{ "ca538", CLASS_Female },
	{ "ca541", CLASS_Female },
	{ "ca542", CLASS_Female },
	{ "ca545", CLASS_Female },

	{ "ca546", CLASS_Female },
	{ "ca548", CLASS_Female },
	{ "ca550", CLASS_Female },
	{ "ca602", CLASS_Female },
	{ "ca605", CLASS_Female },
	{ "ca606", CLASS_Female },
	{ "ca608", CLASS_Female },
	{ "ca611", CLASS_Female },
	{ "ca612", CLASS_Female },
	{ "ca616", CLASS_Female },
	{ "ca619", CLASS_Female },
	{ "ca620", CLASS_Female },
	{ "ca623", CLASS_Female },

	{ "ca624", CLASS_Female },
	{ "ca627", CLASS_Female },
	{ "ca628", CLASS_Female },
	{ "ca633", CLASS_Female },
	{ "ca634", CLASS_Female },
	{ "ca637", CLASS_Female },
	{ "ca638", CLASS_Female },
	{ "ca641", CLASS_Female },
	{ "ca642", CLASS_Female },
	{ "ca645", CLASS_Female },
	{ "ca646", CLASS_Female },
	{ "ca648", CLASS_Female },
	{ "ca650", CLASS_Female },
	
};


DWORD sinInvenColor[7] = { D3DCOLOR_RGBA(160,235,256,128) , D3DCOLOR_RGBA(255,255,255,128) ,D3DCOLOR_RGBA(255,0,0,128),
					D3DCOLOR_RGBA(255,255,255,128) , D3DCOLOR_RGBA(255,200,0,128) ,D3DCOLOR_RGBA(0,231,123,128),
					D3DCOLOR_RGBA(173,203,247,128)

};


DWORD CristalEventCODE[12] = { (sinGP1 | sin01),(sinGP1 | sin02),(sinGP1 | sin03),(sinGP1 | sin04),(sinGP1 | sin05)
						   ,(sinGP1 | sin06),(sinGP1 | sin07),(sinGP1 | sin08),(sinGP1 | sin09),
							(sinGP1 | sin11),(sinGP1 | sin12),(sinGP1 | sin13) };


DWORD WatermelonEventCODE = (sinSP1 | sin26);

DWORD ValentineEventCODE = (sinSP1 | sin35);


DWORD PristonAlphabetEventCODE[7] = { (sinSP1 | sin27), (sinSP1 | sin28), (sinSP1 | sin29),
									  (sinSP1 | sin30), (sinSP1 | sin31), (sinSP1 | sin32), (sinSP1 | sin33) };


DWORD CandydaysEventCODE = (sinSP1 | sin36);


DWORD MagicalGreenEventCODE[2] = { (sinSP1 | sin37), (sinSP1 | sin38) };


DWORD TeatOfKaraEventCODE = (sinSP1 | sin39);


DWORD FindinvestigatorEventCODE[2] = { (sinGF1 | sin07), (sinGF1 | sin08) };


cINVENTORY::cINVENTORY()
{

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
		memset(&InvenItem[i], 0, sizeof(sITEM));

	OpenFlag = 0;
	CostumeFlag = 0;
	CostumeChangeFlag = 0;
	CostumeTimer = 0;

}
cINVENTORY::~cINVENTORY()
{

}


void cINVENTORY::Init()
{
	CostumeFlag = FALSE;

	StartX = 23;
	StartY = 436;

	EndX = StartX + ((INVENTORY_BOX_ROW) * 22);
	EndY = StartY + ((INVENTORY_BOX_COL) * 22);

	Load();

	ReformCharForm();
	SearchJobAndSetting();
	CheckWeight();
	SetItemToChar();

	sinSetLife(sinChar->Life[1]);
	sinSetMana(sinChar->Mana[1]);
	sinSetStamina(sinChar->Stamina[1]);
	ReformCharForm();

	int i = 0;
	char szBuff[128];
	for (i = 0; i < 5; i++)
	{
		wsprintf(szBuff, "Image\\SinImage\\Effect\\Particle\\InvenPaticle%d.tga", i);
		MatInvenParticle[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	}
	MatUnionCoreEffect = CreateTextureMaterial("image\\Sinimage\\Effect\\InterEffect\\UC-hall.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);



	LoadCharState();


}

void cINVENTORY::Load()
{
	char szBuff[128];
	for (int i = 0; i < 4; i++)
	{
		wsprintf(szBuff, "image\\Sinimage\\Effect\\InterEffect\\UC-0%d.bmp", i + 1);
		lpUnionCoreEffect[i] = LoadDibSurfaceOffscreen(szBuff);

	}

	lpIndiShopIcon = LoadDibSurfaceOffscreen("Image\\SinImage\\indishop\\indishop_icon.bmp");
	lpMyShopIcon_T = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\inven-SaleT.bmp");

	lpMyShopIcon = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\inven-Sale.bmp");

	lpSpecialItem[0] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\QuestItem_.bmp");
	lpSpecialItem[1] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\QuestItem.bmp");

	lpCostumeButton = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\ButtonCostume.bmp");
	lpCostume = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\Costume-UI.bmp");
	lpCostumeInfo = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\Costume.bmp");

	lpSpecialItemInfo[0] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\Questitem.bmp");
	lpSpecialItemInfo[1] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\close.bmp");

	lpSpecialInven = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\QuestItembox.bmp");

	lpInvenMain = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\Inven.bmp");
	lpInvenArrow[0] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\LeftArrow.bmp");
	lpInvenArrow[1] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\RightArrow.bmp");

	lpCoverSmall = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\CoverSmall.bmp");
	lpCoverMiddle = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\CoverMiddle.bmp");
	lpCoverLarge = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\CoverLarge.bmp");

	lpPotionBack = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\PotionBack.bmp");

	lpChangeABInfo[0] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonA.bmp");
	lpChangeABInfo[1] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonB.bmp");

	lpExitInfo = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonExit.bmp");
	lpWeightInfo = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonWeight.bmp");

	lpItemABInfo[0] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonItemA.bmp");
	lpItemABInfo[1] = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\InfoBox\\ButtonItemB.bmp");

	lpShowWeaponClass[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Onehand.bmp");
	lpShowWeaponClass[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Twohand.bmp");
	lpShowWeaponClass[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Knight.bmp");
	lpShowWeaponClass[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Items\\Weapon_Wizard.bmp");


	lpPuzzleInven = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\NYEAR_00.bmp");
	lpPuzzlewidth = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\NYEAR_01.bmp");
	lpPuzzleHeight = LoadDibSurfaceOffscreen("game\\GUI\\Inventory\\NYEAR_02.bmp");

}
void cINVENTORY::InvenItemLoad()
{
	char szFilePath[256];
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (InvenItem[i].CODE == sItem[j].CODE)
				{
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

					if (!sItem[j].lpTempItem)
					{
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
					}

					InvenItem[i].lpItem = sItem[j].lpTempItem;
					break;
				}
			}
		}
		if (InvenItemTemp[i].Flag)
		{
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (InvenItemTemp[i].CODE == sItem[j].CODE)
				{
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
					if (!sItem[j].lpTempItem)
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
					InvenItemTemp[i].lpItem = sItem[j].lpTempItem;
					break;
				}
			}
		}
	}
}

void cINVENTORY::InvenItemRelease()
{
	int i = 0;
	for (i = 0; i < MAX_ITEM; i++)
	{
		if (sItem[i].lpTempItem)
		{
			sItem[i].lpTempItem->Release();
			sItem[i].lpTempItem = 0;

		}
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].lpItem)
			{
				InvenItem[i].lpItem->Release();
				InvenItem[i].lpItem = 0;
			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].lpItem)
			{
				InvenItemTemp[i].lpItem->Release();
				InvenItemTemp[i].lpItem = 0;
			}

		}

	}

}


void cINVENTORY::Release()
{
	int i;

	for (i = 0; i < 2; i++)
	{
		if (lpInvenArrow[i])
		{
			lpInvenArrow[i]->Release();
			lpInvenArrow[i] = 0;
		}
		if (lpChangeABInfo[i])
		{
			lpChangeABInfo[i]->Release();
			lpChangeABInfo[i] = 0;
		}
		if (lpItemABInfo[i])
		{
			lpItemABInfo[i]->Release();
			lpItemABInfo[i] = 0;
		}

	}
	if (lpCoverSmall)
	{
		lpCoverSmall->Release();
		lpCoverSmall = 0;
	}
	if (lpCoverMiddle)
	{
		lpCoverMiddle->Release();
		lpCoverMiddle = 0;
	}
	if (lpCoverLarge)
	{
		lpCoverLarge->Release();
		lpCoverLarge = 0;
	}
	if (lpPotionBack)
	{
		lpPotionBack->Release();
		lpPotionBack = 0;
	}
	if (lpExitInfo)
	{
		lpExitInfo->Release();
		lpExitInfo = 0;
	}
	if (lpWeightInfo)
	{
		lpWeightInfo->Release();
		lpWeightInfo = 0;
	}
	if (lpShowWeaponClass[0])
	{
		lpShowWeaponClass[0]->Release();
		lpShowWeaponClass[0] = 0;

	}

	if (lpShowWeaponClass[1])
	{
		lpShowWeaponClass[1]->Release();
		lpShowWeaponClass[1] = 0;

	}

	if (lpCostumeButton)
	{
		lpCostumeButton->Release();
		lpCostumeButton = 0;
	}


}

int CoreEffectTime = 0;
int CoreEffectFlag = 0;

ECostumeClass GetCharacterKind()
{
	if ((lpCurPlayer->smCharInfo.JOB_CODE == 1) || (lpCurPlayer->smCharInfo.JOB_CODE == 2) || (lpCurPlayer->smCharInfo.JOB_CODE == 4) || (lpCurPlayer->smCharInfo.JOB_CODE == 6) || (lpCurPlayer->smCharInfo.JOB_CODE == 7) || (lpCurPlayer->smCharInfo.JOB_CODE == 10))
		return CLASS_Male;
	else
		return CLASS_Female;

	return CLASS_Male;
}


void cINVENTORY::Draw()
{

	int i = 0;

	DrawSprite(0, 600 - sinMoveKindInter[SIN_INVENTORY] + 56, lpInvenMain, 0, 0, 800, 200);



	if (CostumeFlag)
		DrawSprite(573, 688 - sinMoveKindInter[SIN_INVENTORY], lpCostume, 0, 0, 217, 114);

	if (nName == 1)
	{
		sinChatEnter = 0;
		cInterFace.ChatFlag = 0;

		Interface_clanmenu.DrawBox(BackStartPos.x, BackStartPos.y, 2, 3);
		dsDrawTexImage(MatHelpBoxImage[9], BackStartPos.x + 7, BackStartPos.y + 35, 180, 15, 255);


		dsDrawTexImage(MatMyShopPRBoxLine, BackStartPos.x + 28, BackStartPos.y - 120, 254, 30, 255);

		DrawSprite(BackStartPos.x + BackUpButton2X, BackStartPos.y + BackUpButton2Y - 200, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);
		DrawSprite(BackStartPos.x + BackUpButton3X, BackStartPos.y + BackUpButton3Y - 200, cMessageBox.lpButtonBox07, 0, 0, 48, 23, 1);

		if (pCursorPos.x >= BackStartPos.x + BackUpButton2X && pCursorPos.x <= BackStartPos.x + BackUpButton2X + 48 &&
			pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
		{
			nYesButton = 1;


		}
		else nYesButton = 0;


		if (pCursorPos.x >= BackStartPos.x + BackUpButton3X && pCursorPos.x <= BackStartPos.x + BackUpButton3X + 48 &&
			pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
		{

			nNoButton = 1;

			nName = 0;
			isDrawClanMenu = 0;
			SetIME_Mode(0);
			cInterFace.ChatFlag = 0;
			sinChatEnter = 0;
			sinMessageBoxShowFlag = 0;
			hFocusWnd = 0;
			cInterFace.ChatFlag = 0;

		}
		else nNoButton = 0;

		if (nYesButton == 0) DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y - 200 + 3, cMessageBox.lpButtonYesGlay07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BackUpButton2X + 7, BackStartPos.y + BackUpButton2Y - 200 + 3, cMessageBox.lpButtonYes07, 0, 0, 32, 16, 1);

		if (nNoButton == 0) DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y - 200 + 3, cMessageBox.lpButtonNoGlay07, 0, 0, 32, 16, 1);
		else DrawSprite(BackStartPos.x + BackUpButton3X + 7, BackStartPos.y + BackUpButton3Y - 200 + 3, cMessageBox.lpButtonNo07, 0, 0, 32, 16, 1);



	}


	//Traje
	for (i = 0; i < 3; i++)
	{
		if (CostumeFlag)
		{
			if (i == 0 || i == 2)
				continue;
			if (i == 1 && sInven[i].Position != INVENTORY_POS_COSTUME)
				continue;
		}

		if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].Flag)
			DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverLarge, 0, 0, 66, 110);
	}

	if (CostumeFlag && sInven[13].ItemIndex)
		DrawSprite(sInven[13].Rect.left, sInven[13].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverLarge, 0, 0, 66, 110);

	for (i = 3; i < 7; i++)
	{
		if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].Flag)
			DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverSmall, 0, 0, 22, 22);
	}


	for (i = 7; i < 10; i++)
	{
		if (sInven[i].ItemIndex && InvenItem[sInven[i].ItemIndex - 1].Flag)
			DrawSprite(sInven[i].Rect.left, sInven[i].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCoverMiddle, 0, 0, 44, 44);
	}


	if (ArrowState[0])
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
	else
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);

	if (ArrowState[1])
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
	else
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);

	DrawSprite(sInven[10].Rect.left, sInven[10].Rect.top, lpPotionBack, 0, 0, 77, 25);



	if (!SpecialItemShowFlag)
	{
		DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[0], 0, 0, 20, 20);
	}
	else
	{
		for (i = 0; i < 6; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				DrawSprite(StartX + (i * 44), StartY + (j * 44) + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialInven, 0, 0, 44, 44);
			}
		}

		DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
	}


	switch (ColorIndex)
	{
	case SET_ITEM_CHECK_COLOR:
		if (MouseItem.Flag)
		{
			dsDrawColorBox(sinInvenColor[0], ColorRect.left, ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), ColorRect.right, ColorRect.bottom);
		}
		break;
	case OVERLAP_ITEM_COLOR:
		if (CrashItemIndex[0])
		{
			dsDrawColorBox(sinInvenColor[1], InvenItem[CrashItemIndex[0] - 1].x,
				InvenItem[CrashItemIndex[0] - 1].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[CrashItemIndex[0] - 1].w, InvenItem[CrashItemIndex[0] - 1].h);
		}

		break;
	case NOT_SETTING_COLOR:
		dsDrawColorBox(sinInvenColor[2], ColorRect.left, ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), ColorRect.right, ColorRect.bottom);
		break;

	case NOT_USE_COLOR:
		dsDrawColorBox(sinInvenColor[2], ColorRect.left, ColorRect.top + (256 - sinMoveKindInter[SIN_INVENTORY]), ColorRect.right, ColorRect.bottom);
		break;

	case OVERLAP_BOX_COLOR:
		if (CrashItemIndex[0])
		{
			dsDrawColorBox(sinInvenColor[1], sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.left, sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
				sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.right - sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.left,
				sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.bottom - sInven[InvenItem[CrashItemIndex[0] - 1].ItemPosition - 1].Rect.top);
		}

		break;
	case SELECT_ITEM_COLOR:
		if (!SelectInvenItemIndex)break;
		if (InvenItem[SelectInvenItemIndex - 1].ItemPosition)
		{
			dsDrawColorBox(sinInvenColor[4], sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.left, sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
				sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.right - sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.left,
				sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.bottom - sInven[InvenItem[SelectInvenItemIndex - 1].ItemPosition - 1].Rect.top);

		}
		else
		{
			dsDrawColorBox(sinInvenColor[4], InvenItem[SelectInvenItemIndex - 1].x,
				InvenItem[SelectInvenItemIndex - 1].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[SelectInvenItemIndex - 1].w, InvenItem[SelectInvenItemIndex - 1].h);
		}

		break;

	}


	for (i = 0; i < 10; i++)
	{
		if (sUCore_Effect[i].Flag && sUCore_Effect[i].Time > 0)
		{
			dsDrawTexImage(sUCore_Effect[i].MatNum, sUCore_Effect[i].x, sUCore_Effect[i].y, sUCore_Effect[i].w,
				sUCore_Effect[i].h, sUCore_Effect[i].Alpha);
		}
	}


	for (int cnt = 0; cnt < INVENTORY_MAXITEM; cnt++)
	{
		if (InvenItem[cnt].Flag == 1)
		{

			if ((InvenItem[cnt].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (InvenItem[cnt].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
			{
				DrawSprite(StartX + (22 * 8), sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 2, lpPuzzleInven, 0, 0, 88, 88);
			}

			if (InvenItem[cnt].sItemInfo.NotUseFlag && !MyShopItemIndex[cnt])
			{
				dsDrawColorBox(sinInvenColor[2], InvenItem[cnt].x, InvenItem[cnt].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[cnt].w, InvenItem[cnt].h);
				if (InvenItem[cnt].ItemPosition != 0)
				{
					dsDrawColorBox(sinInvenColor[2], sInven[InvenItem[cnt].ItemPosition - 1].Rect.left, sInven[InvenItem[cnt].ItemPosition - 1].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]),
						sInven[InvenItem[cnt].ItemPosition - 1].Rect.right - sInven[InvenItem[cnt].ItemPosition - 1].Rect.left,
						sInven[InvenItem[cnt].ItemPosition - 1].Rect.bottom - sInven[InvenItem[cnt].ItemPosition - 1].Rect.top);
				}
			}
		}
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{

			if (InvenItem[i].ItemPosition != 11 && InvenItem[i].ItemPosition != 12 && InvenItem[i].ItemPosition != 13)
			{

				if (MyShopItemIndex[i])
				{
					dsDrawColorBox(D3DCOLOR_RGBA(45, 133, 255, 180), InvenItem[i].x, InvenItem[i].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[i].w, InvenItem[i].h);
				}

				if (CostumeFlag)
				{
					if (InvenItem[i].ItemPosition - 1 >= 0 && InvenItem[i].ItemPosition - 1 < INVENTORY_MAX_POS)
					{
						if (sInven[InvenItem[i].ItemPosition - 1].Position == INVENTORY_POS_ARMOR)
							continue;
						else if (sInven[InvenItem[i].ItemPosition - 1].Position == INVENTORY_POS_LHAND)
							continue;
						else if (sInven[InvenItem[i].ItemPosition - 1].Position == INVENTORY_POS_RHAND)
							continue;
					}
				}
				else
				{
					if (InvenItem[i].ItemPosition - 1 >= 0 && InvenItem[i].ItemPosition - 1 < INVENTORY_MAX_POS)
					{
						if (sInven[InvenItem[i].ItemPosition - 1].Position == INVENTORY_POS_COSTUME)
							continue;
					}
				}

				DrawSprite(InvenItem[i].x, InvenItem[i].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[i].lpItem, 0, 0, InvenItem[i].w, InvenItem[i].h);

				if (!InvenItem[i].lpItem)
				{
					if (InvenItem[i].x > 10)
					{
						dsDrawColorBox(D3DCOLOR_RGBA(125 + (i * 10), 125 + (i * 10), 255 + (i * 10), 125 + (i * 10)), InvenItem[i].x, InvenItem[i].y + (256 - sinMoveKindInter[SIN_INVENTORY]), InvenItem[i].w, InvenItem[i].h);
					}

				}
				if ((InvenItem[i].CODE & sinITEM_MASK2) == sinFO1)
				{
					DrawForceOrbEffect(InvenItem[i].x, InvenItem[i].y + (256 - sinMoveKindInter[SIN_INVENTORY]));
				}
			}
			else
			{
				DrawSprite(InvenItem[i].x, InvenItem[i].y, InvenItem[i].lpItem, 0, 0, InvenItem[i].w, InvenItem[i].h);
			}
		}
	}


	if (PuzzleOkFlag)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 0, 30), StartX + (22 * 8), sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 2, 88, 88);

		dsDrawColorBox(D3DCOLOR_RGBA(255, 123, 0, 180), StartX + (22 * 8), PuzzleOkY + sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 4, 88, 2);
		dsDrawColorBox(D3DCOLOR_RGBA(255, 123, 0, 180), StartX + (22 * 8), (80 - PuzzleOkY) + sInven[0].Rect.top + (256 - sinMoveKindInter[SIN_INVENTORY]) + 4, 88, 2);


	}

	int len = 0;
	if (CoreEffectFlag == 0)
	{
		CoreEffectTime++;
	}
	else
		CoreEffectTime--;

	if (CoreEffectTime > 38)
		CoreEffectFlag = 1;
	else if (CoreEffectTime < 1)
		CoreEffectFlag = 0;


	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].sItemInfo.CODE == (sinEC1 | sin05))
			{
				len = lstrlen(InvenItem[i].sItemInfo.ItemName);
				if (InvenItem[i].sItemInfo.ItemName[len + 1] != NULL)
				{
					DrawSprite(InvenItem[i].x, InvenItem[i].y + (256 - sinMoveKindInter[SIN_INVENTORY]), lpUnionCoreEffect[CoreEffectTime / 10], 0, 0, 44, 22);

				}
			}
		}
	}


	if (CostumeFlag)
		DrawSprite(ArrowPosi[9][0], ArrowPosi[9][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCostumeButton, 0, 0, 20, 20);

	switch (InvenArrowPosi)
	{
	case 1:
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[0][0], ArrowPosi[0][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpItemABInfo[0], 0, 0, 57, 27);

		break;
	case 2:
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[1][0], ArrowPosi[1][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpItemABInfo[1], 0, 0, 57, 27);

		break;
	case 3:
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[0], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[2][0], ArrowPosi[2][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpChangeABInfo[0], 0, 0, 70, 27);
		break;
	case 4:
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpInvenArrow[1], 0, 0, 20, 20);
		DrawSprite(ArrowPosi[3][0], ArrowPosi[3][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpChangeABInfo[1], 0, 0, 70, 27);
		break;

	case 5:
		DrawSprite(ArrowPosi[4][0], ArrowPosi[4][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(ArrowPosi[4][0] - 8, ArrowPosi[4][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpExitInfo, 0, 0, 47, 27);
		break;
	case 6:

		break;
	case 8:
		if (!SpecialItemShowFlag)
		{
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItemInfo[0], 0, 0, 100, 27);
		}
		else
		{
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItem[1], 0, 0, 20, 20);
			DrawSprite(ArrowPosi[7][0], ArrowPosi[7][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpSpecialItemInfo[1], 0, 0, 70, 27);
		}
		break;
	case 9:
		DrawSprite(ArrowPosi[8][0], ArrowPosi[8][1] + (256 - sinMoveKindInter[SIN_INVENTORY]), lpMyShopIcon, 0, 0, 20, 20);
		DrawSprite(ArrowPosi[8][0] - 39, ArrowPosi[8][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpMyShopIcon_T, 0, 0, 100, 26);

		break;
	case 10:
		DrawSprite(ArrowPosi[9][0], ArrowPosi[9][1] - 27 + (256 - sinMoveKindInter[SIN_INVENTORY]), lpCostumeInfo, 0, 0, 80, 27);

		break;

	}

	if (sinSkill.pLeftSkill)
	{
		if (sinSkill.pLeftSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top,
				cSkill.lpSkillButton[sinSkill.pLeftSkill->Position - 1], 0, 0, 40, 40);
		else
			DrawSprite(sLeftRightSkill[0].BoxRect.left, sLeftRightSkill[0].BoxRect.top,
				cSkill.lpSkillButton_Gray[sinSkill.pLeftSkill->Position - 1], 0, 0, 40, 40);

	}
	if (sinSkill.pRightSkill)
	{
		if (sinSkill.pRightSkill->UseSkillFlag)
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top,
				cSkill.lpSkillButton[sinSkill.pRightSkill->Position - 1], 0, 0, 40, 40);
		else
			DrawSprite(sLeftRightSkill[1].BoxRect.left, sLeftRightSkill[1].BoxRect.top,
				cSkill.lpSkillButton_Gray[sinSkill.pRightSkill->Position - 1], 0, 0, 40, 40);
	}




	for (i = 0; i < 100; i++)
	{
		if (UnionCore_Effect[i].Flag)
		{
			cInvenTory.sinDrawInvenTexImage(&UnionCore_Effect[i].InvenFace);
		}
	}

	for (i = 0; i < 50; i++)
	{
		if (UnionCore_Effect_Bomb[i].Flag)
		{
			cInvenTory.sinDrawInvenTexImage(&UnionCore_Effect_Bomb[i].InvenFace);


		}
	}

	if (IndiShopIconFlag)
	{
		DrawSprite(225, 570, lpIndiShopIcon, 0, 0, 27, 25);
		DrawSprite(225 - 35, 570 - 27, cShop.lpMyShop_T, 0, 0, 100, 26);

	}


}

int InvenMainCount = 0;
int SetDelayFlag = 0;
bool bGiftBoxDelay = false;
DWORD dwUsePotionDelayTime = 0;
DWORD dwCheckHackCharStateTime = 0;
DWORD dwCheckHackCharStateFlag = 0;
DWORD dwCheckPickUpItemTime = 0;
int	  CharToItemFirstFlag = 0;
DWORD CharToItemFirstTime = 0;
DWORD dwUseCristalDelayTime = 0;
int   sinUseCristalDelayFlag = 0;


DWORD dwCheckAutoMouseTime = 0;

int   CheckPosiFlag = 0;
#define   CHECKAUTOMOUSE_DISTANCE		(200*200)
#define   CHECKAUTOMOUSE_SETITEM_MAX	500
#define   CHECKAUTOMOUSE_TIME			(70*60*30)




int   CheckX = 0, CheckZ = 0;
int   CheckResultX = 0, CheckResultZ = 0;

DWORD dwPuzzleOkTime = 0;
int ReversEffectFlag = 0;
DWORD dwForceOrbTime = 0;
int   ForceOrbEffectIndex = 0;

void cINVENTORY::Main()
{
	dwForceOrbTime++;
	if (dwForceOrbTime > 8)
	{
		dwForceOrbTime = 0;
		ForceOrbEffectIndex++;
		if (ForceOrbEffectIndex > 7)
			ForceOrbEffectIndex = 0;
	}

	if (PuzzleOkFlag)
	{
		dwPuzzleOkTime++;
		if (dwPuzzleOkTime > 2)
		{
			dwPuzzleOkTime = 0;
			if (PuzzleOkY > 82)ReversEffectFlag = 1;
			if (ReversEffectFlag)
			{
				PuzzleOkY--;
				if (PuzzleOkY <= 0)
					ReversEffectFlag = 0;
			}
			else PuzzleOkY++;

		}
	}
	else
	{
		PuzzleOkY = 0;
		dwPuzzleOkTime = 0;
	}





	int dist = 0;

	if (!CheckPosiFlag)
	{
		CheckX = lpCurPlayer->pX;
		CheckZ = lpCurPlayer->pZ;
		CheckPosiFlag = 1;
	}

	dwCheckAutoMouseTime++;
	if (dwCheckAutoMouseTime >= CHECKAUTOMOUSE_TIME)
	{
		if (sinOverWeightCnt > CHECKAUTOMOUSE_SETITEM_MAX)
		{
			CheckResultX = (lpCurPlayer->pX - CheckX) >> FLOATNS;
			CheckResultZ = (lpCurPlayer->pZ - CheckZ) >> FLOATNS;
			dist = CheckResultX * CheckResultX + CheckResultZ * CheckResultZ;
			if (CHECKAUTOMOUSE_DISTANCE >= dist)
			{

				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}
			else
			{

				sinOverWeightCnt = 0;
				CheckPosiFlag = 0;
				dwCheckAutoMouseTime = 0;
			}

		}
		else
		{
			sinOverWeightCnt = 0;
			CheckPosiFlag = 0;
			dwCheckAutoMouseTime = 0;
		}

	}

	if (sinUseCristalDelayFlag)
	{
		dwUseCristalDelayTime++;
		if (dwUseCristalDelayTime > 70)
		{
			sinUseCristalDelayFlag = 0;
			dwUseCristalDelayTime = 0;
		}
	}

	UnionCoreParticleProcess();

	dwCheckHackCharStateTime++;
	if (dwCheckHackCharStateTime >= 30 * 70)
	{
		SetItemToChar(TRUE);
		dwCheckHackCharStateTime = 0;

	}


	if (sinUsePotionDelayFlag)
	{
		dwUsePotionDelayTime++;
		if (dwUsePotionDelayTime > 50)
		{
			dwUsePotionDelayTime = 0;
			sinUsePotionDelayFlag = 0;

		}

	}

	if (SetDelayFlag)
	{
		InvenMainCount++;
		if (InvenMainCount >= 70)
		{
			SetDelayFlag = 0;
			InvenMainCount = 0;
		}

	}



	if (nName)
	{
		BackUpButton2X = 35;
		BackUpButton2Y = 157;
		BackUpButton3X = 115;
		BackUpButton3Y = 157;

		BackUpPosX = BackStartPos.x;
		BackUpPosY = BackStartPos.y;


		if (pCursorPos.x >= BackStartPos.x + BackUpButton2X && pCursorPos.x <= BackStartPos.x + BackUpButton2X + 48 &&
			pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
		{
			nYesButton = 1;
		}


		if (pCursorPos.x >= BackStartPos.x + BackUpButton3X && pCursorPos.x <= BackStartPos.x + BackUpButton3X + 48 &&
			pCursorPos.y >= BackStartPos.y + BackUpButton2Y - 30 && pCursorPos.y <= BackStartPos.y + BackUpButton2Y - 7)
		{

			nNoButton = 1;
		}

		BackStartPos.x = BackUpPosX;
		BackStartPos.y = BackUpPosY;

	}


	if (bGiftBoxDelay)
	{
		InvenMainCount++;
		if (InvenMainCount >= 140)
		{
			bGiftBoxDelay = false;
			InvenMainCount = 0;
		}
	}
	InvenArrowPosi = 0;
	int i = 0;
	if (OpenFlag)
		for (i = 0; i < 10; i++)
			if (ArrowPosi[i][0] < pCursorPos.x  && ArrowPosi[i][2] > pCursorPos.x  &&
				ArrowPosi[i][1] < pCursorPos.y  && ArrowPosi[i][3] > pCursorPos.y)
				InvenArrowPosi = i + 1;


	for (i = 0; i < 3; i++)
	{
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  &&
			sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
		{
			cHelpPet.PetMessage("*Potion_ShortKey", 0);

		}
	}


	PickUpInvenItem(pCursorPos.x, pCursorPos.y);

	int BackdsDrawOffsetArray = 0;

	if (MouseItem.Flag)
	{
		SetInvenItemAreaCheck(&MouseItem);
		sinItemPickUpDelayFlag = 1;

	}
	if (sinItemPickUpDelayFlag)
	{
		dwCheckPickUpItemTime++;
		if (dwCheckPickUpItemTime > 70)
		{
			sinItemPickUpDelayFlag = 0;
			dwCheckPickUpItemTime = 0;
		}

	}
	else
	{
		sinItemPickUpDelayFlag = 0;
		dwCheckPickUpItemTime = 0;
	}

	if (!PotionCheckNumJumpFlag)
		CheckPotionNumForm();


	if (OpenFlag)
	{


	}


	if (!CharToItemFirstFlag)
	{
		CharToItemFirstTime++;
		if (CharToItemFirstTime >= 70 * 3)
		{
			SetItemToChar(0);
			SetItemToChar();
			CharToItemFirstFlag = 1;
		}
	}

}

void cINVENTORY::Close()
{
	Release();
}

#include "Language\\language.h"

int sinButtonFlag = 0;

void cINVENTORY::LButtonDown(int x, int y)
{


	if (nYesButton == 1)
	{
		strcpy_s(cInvenTory.szSendDoc, cInvenTory.szDoc);
		nName = 0;
		isDrawClanMenu = 0;
		SetIME_Mode(0);
		cInterFace.ChatFlag = 0;
		sinChatEnter = 0;
		sinMessageBoxShowFlag = 0;
		hFocusWnd = 0;
		cInterFace.ChatFlag = 0;
		SendsServerDoc(cInvenTory.szSendDoc);
	}

	if (nNoButton == 1)
	{
		nName = 0;
		isDrawClanMenu = 0;
		SetIME_Mode(0);
		cInterFace.ChatFlag = 0;
		sinChatEnter = 0;
		sinMessageBoxShowFlag = 0;
		hFocusWnd = 0;
		cInterFace.ChatFlag = 0;
	}


	int i = 0;
	for (i = 0; i < 3; i++)
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  &&
			sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
		{
			cHelpPet.PetMessage("*Potion_ShortKey", 1);

		}



	if (InvenArrowPosi == 9)
	{
		if (!MouseItem.Flag)
		{
			cInterFace.CheckAllBox(SIN_MYSHOP);
		}

	}


	if (InvenArrowPosi == 10)
	{
		if (!MouseItem.Flag)
		{
			setCostumer();
		}
	}


	if (bGiftBoxDelay) return;

	if (InvenArrowPosi == 8)
	{
		if (!cTrade.OpenFlag && !cWareHouse.OpenFlag && !cCraftItem.OpenFlag && !cMyShop.OpenFlag && !cCharShop.OpenFlag && !MyShopSendButton)
			ChangeSpecialItem();

	}
	if (InvenArrowPosi == 5)
	{
		OpenFlag = 0;

	}
	if (InvenArrowPosi == 7)
	{
		if (!MouseItem.Flag)
		{

			if (!cTrade.OpenFlag && !cMyShop.OpenFlag && !MyShopSendButton && !cCharShop.OpenFlag && !sSinWarpGate.ShowFlag)
				cMessageBox.ShowMessage2(MESSAGE_THROW_MONEY);
			if (cWareHouse.OpenFlag)
				cMessageBox.ShowMessage2(MESSAGE_MOVE_MONEY_MOVE);

		}
	}

	if (InvenArrowPosi && InvenArrowPosi < 5)
	{
		if (!cTrade.OpenFlag)
		{
			if (sinButtonFlag == InvenArrowPosi)return;
			sinButtonFlag = InvenArrowPosi;
			if (InvenArrowPosi <= 2)
				ChangeABItem(InvenArrowPosi);
			if (InvenArrowPosi >= 3)
				sinChangeSetFlag = InvenArrowPosi;
		}

	}

	if (sinCraftItemStartFlag || StartInterEffectAging2)
	{
		return;
	}
	else if ((ManufactureItem.m_OpenFlag || SmeltingItem.OpenFlag) && MixCancelButtonDelayFlag)
	{
		return;
	}
	if (MouseItem.Flag)
	{
		if (cInvenTory.OpenFlag && MouseItem.sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
		{
			if (ColorIndex == OVERLAP_ITEM_COLOR || ColorIndex == SET_ITEM_CHECK_COLOR)
			{
				if (!SpecialItemShowFlag)
				{
					cInvenTory.UnionCoreParticle2(MouseItem.x, MouseItem.y);
					sinPlaySound(SIN_SOUND_EAT_POTION2);
				}
				SetSpecialItem(&MouseItem);
				MouseItem.Flag = 0;
				ReFormInvenItem();
				ReformCharForm();
				return;
			}

		}



		if (SpecialItemShowFlag)return;
		if (SetDelayFlag)return;


		if (!sSinWarpGate.ShowFlag)
			ThrowInvenItemToField(&MouseItem);


		if (ColorIndex == NO_BOX_COLOR || ColorIndex == NOT_SETTING_COLOR)return;
		if (!CheckSetOk(&MouseItem))
			return;
		if (MouseItem.Class == ITEM_CLASS_POTION)
		{
			if (!MouseSetPotion(&MouseItem))
			{
				if (MouseItem.Flag)
				{
					NoSettingThrowItem(&MouseItem);
				}

			}
			else
				CheckWeight();

		}
		else
		{
			if (!ChangeInvenItem(&MouseItem))
			{
				if (MouseItem.ItemPosition)
				{

					if (sInven[MouseItem.ItemPosition - 1].ItemIndex && InvenItem[sInven[MouseItem.ItemPosition - 1].ItemIndex - 1].Flag)
					{
						return;
					}


				}
				if (!LastSetInvenItem(&MouseItem))
				{
					if (MouseItem.Flag)
					{
						if ((MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
							(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
							(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinQT1 ||
							(MouseItem.sItemInfo.CODE & sinITEM_MASK2) == sinQW1)
						{

						}
						else
						{
							NoSettingThrowItem(&MouseItem);
						}
					}
				}
			}
		}
	}
	else
	{


		if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK ||
			lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)return;

		pMessageItem = 0;
		CheckInvenItemForm();
		if (cMyShop.OpenFlag)
		{
			PickUpInvenItem(pCursorPos.x, pCursorPos.y, 2);
		}
		else
		{
			if (!MyShopSendButton && !cCharShop.OpenFlag && !sSinWarpGate.ShowFlag)
			{
				PickUpInvenItem(pCursorPos.x, pCursorPos.y, 1);
			}
		}

		ReFormInvenItem();
		if (MouseItem.Flag)
		{
			if (MouseItem.Class != ITEM_CLASS_POTION)
			{
				CopyItemClear(&MouseItem);
			}
		}
	}
	if (MouseItem.Flag)
		LbuttonUpCheckFlag = 1;


}

void cINVENTORY::LButtonUp(int x, int y)
{
	LbuttonUpCheckFlag = 0;
	sinMyShopItemPass = 0;
}


DWORD dwBoosterItemCode[] = { sin21,sin22,sin23,sin24,sin25,sin26,sin27,sin28,sin29,0 };
DWORD dwCastlItemCODE[] = { sin01,sin02,sin03,sin04,sin05,sin06,sin07,sin08,sin09,sin10,sin11,sin12,sin13,sin14,sin15,sin16,0 };
DWORD dwNotUseVillageItemCODE[3] = { (sinBI1 | sin05),(sinBI1 | sin06),(sinBI1 | sin07) };
DWORD dwNotUseItemCODE[6][3] = { {SCROLL_INVULNERABILITY,(sinBC1 | sin01),1},{SCROLL_CRITICAL,(sinBC1 | sin02),2},{SCROLL_EVASION,(sinBC1 | sin03),3},
							  {SCROLL_P_INVULNERABILITY,(sinBI1 | sin05),1},{SCROLL_P_CRITICAL,(sinBI1 | sin06),2},{SCROLL_P_EVASION,(sinBI1 | sin07),3} };

DWORD dwSkillDelayItemCode[] = { sin30,sin31,sin32, 0 };

#include <iostream>

using namespace std;

extern int AgingLevelSheltomIndex[4][3];
extern POINT AgingLevelSheltomXY[4][3];

DWORD DelayTime = 0;

void cINVENTORY::RButtonDown(int x, int y)
{
	int Index = SelectInvenItemIndex - 1;

	if (MouseItem.Flag || sinItemPickUpDelayFlag)
	{
		return;
	}


	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (sInven[i + 10].Rect.left < pCursorPos.x  && sInven[i + 10].Rect.right > pCursorPos.x  &&
			sInven[i + 10].Rect.top < pCursorPos.y  && sInven[i + 10].Rect.bottom > pCursorPos.y)
		{
			cHelpPet.PetMessage("*Potion_ShortKey", 2);
		}
	}
	for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
	{
		if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			return;
	}

	if (MouseItem.Flag)
	{
		return;
	}

	if (cAging.OpenFlag) 
	{
		if (SelectInvenItemIndex)
		{
			int Index = SelectInvenItemIndex - 1;

			sITEM & Item = InvenItem[Index];
			POINT MousePosition = { Item.x + 11, Item.y + 11 };

			if ((InvenItem[Index].CODE & sinITEM_MASK2) == sinBI1)
			{
				POINT PremiumArea = { 159, 268 + sinInterHeight2 };

				if (cAging.isAgeableItem(&Item))
				{
					if (cAging.isStoneAreaEmpty())
					{
						cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);

						MouseItem.x = PremiumArea.x;
						MouseItem.y = PremiumArea.y;

						if (cAging.SetAgingItemAreaCheck(&MouseItem))
							cCraftItem.LastSetCraftItem(&MouseItem, 3);
					}
					else
					{
						cMessageBox.ShowMessage("J� existe uma pedra especial de aging.");
					}
				}
				else
				{
					cMessageBox.ShowMessage("Este item n�o pode ser usado no Aging.");
				}
			}
			else if ((InvenItem[Index].CODE & sinITEM_MASK2) == sinOS1)
			{
				
				bool isEmpty = false;
				int i = 0;
				for (i = 0; i < 12; i++)
				{
					if (cAging.isSheltomAreaEmpty(&Item, i))
					{
						isEmpty = true;
						break;
					}
				}
				if (isEmpty)
				{
					int PosX = 218 + ((i % 3) * 22);
					int PosY = (193 + sinInterHeight2) + ((i / 3) * 22);

					if (cAging.isAgeableItem(&Item))
					{
						cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);

						
						MouseItem.x = PosX;
						MouseItem.y = PosY;

						if (cAging.SetAgingItemAreaCheck(&MouseItem))
						{
							cCraftItem.LastSetCraftItem(&MouseItem, 1);
							cAging.CheckItem(&MouseItem);
						}
					}
					else
					{
						cMessageBox.ShowMessage("Este item n�o pode ser usado no aging.");
					}
				}
				else
				{
					cMessageBox.ShowMessage("Sheltom incompat�vel ou n�o h� espa�o livre.");
				}
			}
			else if (cAging.isAgeableItem(&Item))
			{
				int Price = ((Item.sItemInfo.ItemAgingNum[0] + 1) * Item.sItemInfo.Price) / 2;
				if (cShop.haBuyMoneyCheck(Price) > 0)
				{
					if (cAging.isItemAreaEmpty())
					{
						cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

						int StartX = 58;
						int StartY = 193 + sinInterHeight2;
						int MaxX = StartX + (3 * 22);
						int MaxY = StartY + (4 * 22);

						MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
						MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

						if (cAging.SetAgingItemAreaCheck(&MouseItem))
						{
							cCraftItem.LastSetCraftItem(&MouseItem, 1);
							cAging.CheckItem(&MouseItem);
						}
					}
					else
					{
						cMessageBox.ShowMessage("J� existe um item na janela de aging.");
					}
				}
				else
				{
					cMessageBox.ShowMessage("Ouro insuficiente.");
				}
			}
			else
			{
				cMessageBox.ShowMessage("Este item n�o pode ser usado no Aging.");
			}
		}
	}
	else if (cCraftItem.OpenFlag) 
	{
		if (SelectInvenItemIndex)
		{
			int Index = SelectInvenItemIndex - 1;

			sITEM & Item = InvenItem[Index];
			POINT MousePosition = { Item.x + 11, Item.y + 11 };

			if ((InvenItem[Index].CODE & sinITEM_MASK2) == sinOS1 || (InvenItem[Index].CODE & sinITEM_MASK2) == sinSE1)
			{
				
				bool isEmpty = false;

				int i = 0;
				for (i = 0; i < 12; i++)
				{
					if (cCraftItem.isSheltomAreaEmpty(&Item, i))
					{
						isEmpty = true;
						break;
					}
				}

				if (isEmpty)
				{
					int PosX = 218 + ((i % 3) * 22);
					int PosY = (193 + sinInterHeight2) + ((i / 3) * 22);

					if (cCraftItem.isMixableItem(&Item))
					{
						cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);

						
						MouseItem.x = PosX;
						MouseItem.y = PosY;

						if (cCraftItem.SetCraftItemAreaCheck(&MouseItem))
						{
							cCraftItem.LastSetCraftItem(&MouseItem, 0);
						}
					}
					else
					{
						cMessageBox.ShowMessage("Este item n�o pode ser usado no mix.");
					}
				}
				else
				{
					cMessageBox.ShowMessage("Sheltom incompat�vel ou n�o h� espa�o livre.");
				}
			}
			else if (cCraftItem.isMixableItem(&Item))
			{
				int Price = Item.sItemInfo.Price;

				if (cShop.haBuyMoneyCheck(Price) > 0)
				{
					if (cCraftItem.isItemAreaEmpty())
					{
						cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

						int StartX = 58;
						int StartY = 193 + sinInterHeight2;
						int MaxX = StartX + (3 * 22);
						int MaxY = StartY + (4 * 22);

						MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
						MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

						if (cCraftItem.SetCraftItemAreaCheck(&MouseItem))
						{
							cCraftItem.LastSetCraftItem(&MouseItem, 0);
						}
					}
					else
					{
						cMessageBox.ShowMessage("J� existe um item na janela de Mix.");
					}
				}
				else
				{
					cMessageBox.ShowMessage("Ouro insuficiente.");
				}
			}
			else
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_CRAFT_ITEM);
			}
		}
	}
	//Clique direito para enviar itens do invent�rio para o mix reset
	else if (cMixtureReset.OpenFlag)
	{
		if (SelectInvenItemIndex)
		{
			sITEM& Item = InvenItem[Index];
			POINT MousePosition = { Item.x + 11, Item.y + 11 };

			if (InvenItem[Index].CODE == (sinBI1 | sin89))// (Mix/Aging) Reset
			{
				if (sMixtureResetItem.MixtureResetItem[0].sItemInfo.ItemKindCode == ITEM_KIND_AGING ||
					sMixtureResetItem.MixtureResetItem[0].sItemInfo.ItemKindCode == ITEM_KIND_CRAFT)
				{
					if (sinChar->Money < 5000000)
					{
						cMessageBox.ShowMessage("Ouro insuficiente");
					}

					else
					{
						cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

						int StartX = AgingLevelSheltomXY[0][0].x + 23;;
						int StartY = AgingLevelSheltomXY[0][0].y + 31;
						int MaxX = StartX + 22;
						int MaxY = StartY + 22;

						MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
						MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

						cMixtureReset.LastSetMixtureResetItem(&MouseItem, 1);
						MixtureResetCheckFlag = 1;
					}
				}
				else
				{
					cMessageBox.ShowMessage("Este item n�o est� com Aging/Mix.");
				}
			}
			else if (InvenItem[Index].CODE == (sinBI3 | sin88))// Cadeado
			{
				if (!sMixtureResetItem.MixtureResetItem[0].sItemInfo.ItemLocked)
				{

					if (sinChar->Money < 5000000)
					{
						cMessageBox.ShowMessage("Ouro insuficiente");
					}
					else
					{
						cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

						int StartX = AgingLevelSheltomXY[0][0].x + 23;;
						int StartY = AgingLevelSheltomXY[0][0].y + 31;
						int MaxX = StartX + 22;
						int MaxY = StartY + 22;

						MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
						MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

						cMixtureReset.LastSetMixtureResetItem(&MouseItem, 1);
						MixtureResetCheckFlag = 1;
					}
				}
				else
				{
					cMessageBox.ShowMessage("Este item j� est� vinculado.");
				}
			}
			else if (InvenItem[Index].CODE == (sinBI3 | sin87))// Chave
			{
				if (sMixtureResetItem.MixtureResetItem[0].sItemInfo.ItemLocked)
				{
					if (sinChar->Money < 5000000)
					{
						cMessageBox.ShowMessage("Ouro insuficiente");
					}
					else
					{
						cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

						int StartX = AgingLevelSheltomXY[0][0].x + 23;;
						int StartY = AgingLevelSheltomXY[0][0].y + 31;
						int MaxX = StartX + 22;
						int MaxY = StartY + 22;

						MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
						MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

						cMixtureReset.LastSetMixtureResetItem(&MouseItem, 1);
						MixtureResetCheckFlag = 1;
					}
				}
				else
				{
					cMessageBox.ShowMessage("Este item n�o est� vinculado.");
				}
			}
			
			else if (InvenItem[Index].Class == ITEM_CLASS_WEAPON_ONE ||
				InvenItem[Index].Class == ITEM_CLASS_WEAPON_TWO ||
				InvenItem[Index].Class == ITEM_CLASS_ARMOR ||
				InvenItem[Index].Class == ITEM_CLASS_BOOTS ||
				InvenItem[Index].Class == ITEM_CLASS_GLOVES ||
				InvenItem[Index].Class == ITEM_CLASS_SHIELDS ||
				InvenItem[Index].Class == ITEM_CLASS_RING ||
				InvenItem[Index].Class == ITEM_CLASS_SHELTOM ||
				InvenItem[Index].Class == ITEM_CLASS_AMULET ||
				InvenItem[Index].Class == ITEM_CLASS_ARMLET ||
				InvenItem[Index].Class == ITEM_CLASS_MAGICIAL_STUFFS)
			{
				cInvenTory.PickUpInvenItem(Item.x + 1, Item.y + 1, TRUE);

				int StartX = 58;
				int StartY = 193 + sinInterHeight2;
				int MaxX = StartX + (3 * 22);
				int MaxY = StartY + (4 * 22);

				MouseItem.SetX = StartX + ((MaxX - StartX) - MouseItem.w) / 2;
				MouseItem.SetY = StartY + ((MaxY - StartY) - MouseItem.h) / 2;

				cMixtureReset.LastSetMixtureResetItem(&MouseItem, 2);
			}
		}
	}
	else if (cShop.OpenFlag)
	{
		if (SelectInvenItemIndex)
		{

			sITEM & Item = InvenItem[SelectInvenItemIndex - 1];
			POINT MousePosition = { Item.x + 11, Item.y + 11 };
			if (cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE))
			{
				if (cShop.CheckHighRankItem(&MouseItem))
				{
					MouseItem.Flag = 0;
					ResetInvenItemCode();
					cMessageBox.ShowMessage3(MESSAGE_SELL_HIGHRANK_ITEM, MouseItem.sItemInfo.ItemName);
				}
				else cShop.SellItemToShop(&MouseItem);
			}
		}
	}
	else if (cWareHouse.OpenFlag)
	{
		cWareHouse.SendItemToIven(x, y, 1);
		if (SelectInvenItemIndex)
		{
			sITEM & Item = InvenItem[SelectInvenItemIndex - 1];
			POINT MousePosition = { Item.x + 11, Item.y + 11 };
			int cntx, cnty;
			RECT	rect = { 0, 0, 0, 0 };
			int		flag = 0;
			int StartX = 21;
			int StartY = 86;
			int cx = (22 * 9) - Item.w;
			int cy = (22 * 9) - Item.h;

			for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
			{
				for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
				{
					flag = 0;
					for (int i = cWareHouse.Page * 100; i < cWareHouse.Page * 100 + 100; i++)
					{
						if (sWareHouse.WareHouseItem[i].Flag)
						{
							rect.left = sWareHouse.WareHouseItem[i].x;
							rect.right = sWareHouse.WareHouseItem[i].x + sWareHouse.WareHouseItem[i].w;
							rect.top = sWareHouse.WareHouseItem[i].y;
							rect.bottom = sWareHouse.WareHouseItem[i].y + sWareHouse.WareHouseItem[i].h;

							if (cntx > rect.left - Item.w && cntx< rect.right &&
								cnty > rect.top - Item.h && cnty < rect.bottom)
								flag++;
						}
					}
					if (flag == 0)
					{
						cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);
						MouseItem.SetX = cntx;
						MouseItem.SetY = cnty;
						cWareHouse.LastSetWareHouseItem(&MouseItem);
						return;
					}
				}
			}
		}
	}
	else if (cTrade.OpenFlag) { // trade com bot�o direito
	if (SelectInvenItemIndex) {
		sITEM& Item = InvenItem[Index];
		POINT MousePosition = { Item.x + 11, Item.y + 11 };

		if (cTrade.IsItemOkay(&Item)) {
			POINT Pos = { 0 };
			if (cTrade.GetEmptyArea(&Item, &Pos)) {
				cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);

				Item.SetX = Pos.x;
				Item.SetY = Pos.y;

				MouseItem.SetX = Item.SetX;
				MouseItem.SetY = Item.SetY;

				MouseItem.x = Item.SetX + 1;
				MouseItem.y = Item.SetY + 1;

				if (cTrade.SetTradeItemAreaCheck(&MouseItem))
					cTrade.LastSetTradeItem(&MouseItem);
			}
		}
	}
	return;
	}
	char szBuff[128] = { 0 };

	if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag || cShop.OpenFlag || cMixtureReset.OpenFlag ||
		cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag)return;
	UsePotion(x, y);

	if (SelectInvenItemIndex)
	{
		cHelpPet.PetMessage("*InvenTory_Item", 2);

		if ((InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
		{
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount <= 1)
			{
				if (sinChar->Money >= 1000)
				{
					ChangePuzzle(&InvenItem[SelectInvenItemIndex - 1]);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
			}
		}

		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinFO1)
		{
			if (((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) >= sin01) && ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) <= sin14))
				UseForceOrb(&InvenItem[SelectInvenItemIndex - 1]);
			else if (((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) >= sin21) && ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) <= sin34))
				UseMagicForceOrb(&InvenItem[SelectInvenItemIndex - 1]);
			else if (((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) >= sin35) && ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) <= sin37))
				UseBillingMagicForceOrb(&InvenItem[SelectInvenItemIndex - 1]);
		}


		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinEC1)
		{
			UseEcore(&InvenItem[SelectInvenItemIndex - 1]);
		}

		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinSP1)
		{

			if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin16))
			{
				return;
			}

			if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin05) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin06) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin07) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin08) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin09) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin10))
			{
				sITEM temp;
				temp = InvenItem[SelectInvenItemIndex - 1];
				if (!CheckInvenEmpty(&temp))
				{
					cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
					return;
				}
				if (sinChar->Weight[0] + 10 >= sinChar->Weight[1])
				{
					cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
					return;
				}
				bGiftBoxDelay = true;
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
					sinUsePotionDelayFlag = 1;
				}
			}
			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin34))
			{
				UseCapsuleItem(&InvenItem[SelectInvenItemIndex - 1]);
			}
			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin15))
			{
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
				}
			}
			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin26))
			{
				return;
			}
			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin27) || InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin28) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin29) || InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin30) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin31) || InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin32) ||
				InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin33))
			{
				return;
			}

			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin35))
			{
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
				}
			}

			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin36))
			{
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
				}
			}

			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin37) || InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin38))
			{
				return;
			}

			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin39))
			{
				return;
			}


			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin40))
			{
				if (lpCurPlayer->smCharInfo.dwEventTime_T)
				{
					cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
					return;
				}
				UseSoccerBallPotionItem(&InvenItem[SelectInvenItemIndex - 1]);
			}


			else if (InvenItem[SelectInvenItemIndex - 1].CODE == (sinSP1 | sin42))
			{
				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
				}
			}

			else
			{

				if (sinActionPotion())
				{
					pUsePotion = &InvenItem[SelectInvenItemIndex - 1];

				}
			}
		}

		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinGP1)
		{

			if (DelayTime && (GetCurrentTime() - DelayTime < 15000)) {

				if (chaPremiumitem.haItemUseDelayFlag)
				{
					cMessageBox.ShowMessage("Aguarde 15 segundos para usar un novo cristal");
					return;
				}

				return;
			}
			else
			{
				DelayTime = GetCurrentTime();
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin17) ||
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin18) ||
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin19) ||
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin20))
			{
				if (chaPremiumitem.haItemUseDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}
			}
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.Level > sinChar->Level)return;


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin10) ||
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinGP1 | sin22))
			{
				if (!sinChar->ClassClan || cldata.stats[0] != '1')
				{
					cMessageBox.ShowMessage(MESSAGE_USE_REGULAR_CLAN_ONLY);
					return;
				}
				else
				{
					if (!sinUseCristalDelayFlag)sinUseCristalDelayFlag = 1;
					else return;
				}
			}
			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount = 100;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
				chaPremiumitem.haItemUseDelayFlag = true;

			}
		}



		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinGP2)
		{

			if (chaPremiumitem.haItemUseDelayFlag)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
				return;
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.Level > sinChar->Level)return;

			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount = 100;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
				chaPremiumitem.haItemUseDelayFlag = true;

			}
		}


		for (i = 0; i < 6; i++)
		{
			if (cSkill.SearchContiueSkillCODE(dwNotUseItemCODE[i][0]))
			{
				for (int j = 0; j < 6; j++)
				{
					if (InvenItem[SelectInvenItemIndex - 1].CODE == dwNotUseItemCODE[j][1] && dwNotUseItemCODE[j][1] != dwNotUseItemCODE[i][1])
					{
						if (dwNotUseItemCODE[j][2] == dwNotUseItemCODE[i][2])
						{
							cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
							return;
						}
					}
				}
			}
		}

		if ((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK2) == sinBI1)
		{
			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE &&
				((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK3) >= sin16) && ((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK3) <= sin18))
			{
				return;
			}
		}
		if ((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK2) == sinBI2)
		{
			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE &&
				((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK3) >= sin13) && ((InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK3) <= sin45))
			{
				return;
			}
		}

		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinBC1)
		{

			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State != FIELD_STATE_VILLAGE &&
				(InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin18)
			{
				return;
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBC1 | sin05))
			{
				return;
			}
			for (i = 0; i < 18; i++)
			{
				if ((InvenItem[SelectInvenItemIndex - 1].CODE&sinITEM_MASK3) == dwCastlItemCODE[i])
				{
					chaSiege.SetCastleItemSkill(i + 1);
					SetItemToChar();
					break;
				}
			}


			if (((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) >= sin21) && ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) <= sin29))
				cSkill.UseBoosterItem(&InvenItem[SelectInvenItemIndex - 1]);


			if (((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) >= sin30))
				cSkill.UseSkillDelayItem(&InvenItem[SelectInvenItemIndex - 1]);

			if (haCastleSkillUseFlag != 1)return;

			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount = 200;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}

		}
		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinBI1 || (InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinBI2 ||
			(InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinBI3 || (InvenItem[SelectInvenItemIndex - 1].CODE & sinITEM_MASK2) == sinBI4)
		{
			chaPremiumitem.TelePortCore.ItemIndex = 0;

			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
			{

				for (int i = 0; i < 3; i++)
				{
					if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == dwNotUseVillageItemCODE[i])
						return;
				}
			}



			iEventBuyItemKind = 0;

			/*if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin45))
			{
				if (sinChar->Level <= 154)
				{
					DeleteInvenItemToServer(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE, InvenItem[SelectInvenItemIndex - 1].sItemInfo.ItemHeader.Head, InvenItem[SelectInvenItemIndex - 1].sItemInfo.ItemHeader.dwChkSum);
					CheckCharForm();
					sinChar->Level++;
					SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
					CodeXorCharInfo_Exp();
					StartEffect(lpCurPlayer->pX, lpCurPlayer->pY + 32 * fONE, lpCurPlayer->pZ, EFFECT_LEVELUP1);
					esPlaySound(7, 400);
					ReformCharForm();
				}
			}*/

			//Force
			//For�a Lucidy
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin80))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(180);
			}
			//For�a Sereneo
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin81))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(181);
			}
			//For�a Fadeo
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin82))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(182);
			}
			//For�a Sparky
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin83))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(183);
			}
			//For�a Raident
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin84))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(184);
			}
			//For�a Transparo
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin85))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(185);
			}
			//For�a Murky
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin86))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(186);
			}
			//For�a Devine
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin87))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(187);
			}
			//For�a Celesto
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin88))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(188);
			}
			//For�a Mirage
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin89))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(189);
			}
			//For�a Inferna
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin90))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(190);
			}
			//For�a Enigma
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin91))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(191);
			}
			//For�a Bellum
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin92))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(192);
			}
			//For�a Ordo
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin93))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(193);
			}
			//For�a Vita
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin94))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(194);
			}
			//For�a Ira
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin95))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(195);
			}
			//For�a Tera
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin96))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(196);
			}
			//For�a Guardi�
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin97))
			{
				if (!ForceLevelCheck(InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE))
					return;

				if (chaPremiumitem.m_ForceTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}
				chaPremiumitem.UsePremiumItem(197);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin01))
			{
				if (chaPremiumitem.m_BigHeadTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(171);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin10))
			{
				if (chaPremiumitem.m_AwellPowerTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(172);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin20))
			{
				if (chaPremiumitem.m_MigalPoweTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(173);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin30))
			{
				if (chaPremiumitem.m_HPBoosterTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(174);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin40))
			{
				if (chaPremiumitem.m_MPBoosterTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(175);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin50))
			{
				if (chaPremiumitem.m_SPBoosterTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(176);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin60))
			{
				if (chaPremiumitem.m_RecoverSPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(177);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI4 | sin70))
			{
				if (chaPremiumitem.m_BDivinaTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(178);
			}
			
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin01))
				chaPremiumitem.UsePremiumItem(1);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin02))
				chaPremiumitem.UsePremiumItem(2);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin03))
				chaPremiumitem.UsePremiumItem(3);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin04))
				return;

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin05))
				chaPremiumitem.UsePremiumItem(5);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin06))
			{
				for (i = 0; i < MAX_CONTINUE_SKILL; i++)
				{
					if (ContinueSkill[i].CODE == SCROLL_P_EVASION)
					{
						if (ContinueSkill[i].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
							return;
						}
					}
				}
				chaPremiumitem.UsePremiumItem(6);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin07))
			{
				for (i = 0; i < MAX_CONTINUE_SKILL; i++)
				{
					if (ContinueSkill[i].CODE == SCROLL_P_CRITICAL)
					{
						if (ContinueSkill[i].Flag)
						{
							cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
							return;
						}
					}
				}
				chaPremiumitem.UsePremiumItem(7);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin08))
			{
				chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
				chaPremiumitem.UsePremiumItem(8);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin09))
			{
				chaPremiumitem.UsePremiumItem(9);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin10))
				chaPremiumitem.UsePremiumItem(10);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin11))
				chaPremiumitem.UsePremiumItem(11);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin12))
			{
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(12);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin13))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(13);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin14))
			{
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(14);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin15))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(15);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin16))
				chaPremiumitem.UsePremiumItem(16);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin17))
				chaPremiumitem.UsePremiumItem(17);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin18))
				chaPremiumitem.UsePremiumItem(18);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin19))
			{
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(19);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin20))
			{
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(20);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin21))
			{
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(21);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin22))
			{
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(22);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin23))
			{

				chaPremiumitem.UsePremiumItem(23);

			}



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin01))
				chaPremiumitem.UsePremiumItem(24);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin02))
				chaPremiumitem.UsePremiumItem(25);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin03))
				chaPremiumitem.UsePremiumItem(26);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin04))
				chaPremiumitem.UsePremiumItem(27);


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin05))
				chaPremiumitem.UsePremiumItem(28);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin06))
				chaPremiumitem.UsePremiumItem(29);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin07))
				chaPremiumitem.UsePremiumItem(30);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin08))
				chaPremiumitem.UsePremiumItem(31);


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin09))
				chaPremiumitem.UsePremiumItem(32);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin10))
				chaPremiumitem.UsePremiumItem(33);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin11))
				chaPremiumitem.UsePremiumItem(34);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin12))
				chaPremiumitem.UsePremiumItem(35);


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin13))
				chaPremiumitem.UsePremiumItem(36);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin14))
				chaPremiumitem.UsePremiumItem(37);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin15))
				chaPremiumitem.UsePremiumItem(38);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin16))
				chaPremiumitem.UsePremiumItem(39);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin17))
				chaPremiumitem.UsePremiumItem(40);



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin18))
				chaPremiumitem.UsePremiumItem(41);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin19))
				chaPremiumitem.UsePremiumItem(42);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin20))
				chaPremiumitem.UsePremiumItem(43);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin21))
				chaPremiumitem.UsePremiumItem(44);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin22))
				chaPremiumitem.UsePremiumItem(45);



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin24))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}
				chaPremiumitem.UsePremiumItem(46);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin25))
				chaPremiumitem.UsePremiumItem(47);



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin26))
			{
				chaPremiumitem.UsePremiumItem(48);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin27))
			{
				chaPremiumitem.UsePremiumItem(49);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin28))
			{
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(50);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin29))
			{
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(51);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin26))
			{
				chaPremiumitem.UsePremiumItem(52);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin27))
			{
				chaPremiumitem.UsePremiumItem(53);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin28))
			{
				chaPremiumitem.UsePremiumItem(54);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin29))
			{
				chaPremiumitem.UsePremiumItem(55);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin30))
			{
				chaPremiumitem.UsePremiumItem(56);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin31))
			{
				chaPremiumitem.UsePremiumItem(57);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin32))
			{
				chaPremiumitem.UsePremiumItem(58);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin33))
			{
				chaPremiumitem.UsePremiumItem(59);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin34))
			{
				chaPremiumitem.UsePremiumItem(60);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin35))
			{
				chaPremiumitem.UsePremiumItem(61);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin36))
			{
				chaPremiumitem.UsePremiumItem(62);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin37))
			{
				chaPremiumitem.UsePremiumItem(63);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin30))
			{
				chaPremiumitem.UsePremiumItem(64);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin31))
			{
				chaPremiumitem.UsePremiumItem(65);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin23))
			{
				chaPremiumitem.UsePremiumItem(66);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin24))
			{
				chaPremiumitem.UsePremiumItem(67);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin25))
			{
				chaPremiumitem.UsePremiumItem(68);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin32))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(69);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin33))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(70);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin34))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(71);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin36))
			{

				if (!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(73);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin37))
			{

				if (!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(74);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin38))
			{

				if (!cInvenTory.InvenItem[sInven[2].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(75);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin39))
			{
				if (cSkill.CheckMaturedSkill(1) == FALSE)
				{

					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(76);

			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin40))
			{
				if (cSkill.CheckMaturedSkill(2) == FALSE)
				{

					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(77);

			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin41))
			{
				if (cSkill.CheckMaturedSkill(3) == 0)
				{

					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_MATURESKILL);
					return;
				}
				chaPremiumitem.UsePremiumItem(78);

			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin42))
			{


				if (StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM ||
					StageField[lpCurPlayer->OnStageField]->FieldCode == START_FIELD_NUM ||
					StageField[lpCurPlayer->OnStageField]->FieldCode == START_FIELD_MORYON ||
					StageField[lpCurPlayer->OnStageField]->FieldCode == rsCASTLE_FIELD ||
					StageField[lpCurPlayer->OnStageField]->FieldCode == rsSOD_FIELD ||
					StageField[lpCurPlayer->OnStageField]->FieldCode == 29)
				{
					cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
					return;
				}
				iEventBuyItemKind = 79;
				chaPremiumitem.Using_SelectInvenItemIndex = SelectInvenItemIndex - 1;
				cMessageBox.ShowMessage3(MESSAGE_EVENT_ITEMOK, InvenItem[SelectInvenItemIndex - 1].sItemInfo.ItemName);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin43))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(80);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin44))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(81);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin45))
				chaPremiumitem.UsePremiumItem(82);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin46))
				chaPremiumitem.UsePremiumItem(83);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin47))
				chaPremiumitem.UsePremiumItem(84);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin48))
				chaPremiumitem.UsePremiumItem(85);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin49))
				chaPremiumitem.UsePremiumItem(86);


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin50))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(87);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin51))
			{
				chaPremiumitem.UsePremiumItem(88);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin60))
			{
				chaPremiumitem.UsePremiumItem(97);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin52))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(99);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin53))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(100);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin54))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(101);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin55))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}
				chaPremiumitem.UsePremiumItem(102);
			}



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin69))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(103);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin70))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(104);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin71))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(105);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin72))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(106);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin80))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(107);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin77))
			{
				chaPremiumitem.UsePremiumItem(108);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin65))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(109);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin66))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(110);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin67))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(111);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin68))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(112);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin62))
			{

				if (!cInvenTory.InvenItem[sInven[7].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[7].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(113);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin63))
			{

				if (!cInvenTory.InvenItem[sInven[8].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[8].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(114);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin64))
			{

				if (!cInvenTory.InvenItem[sInven[9].ItemIndex - 1].Flag ||
					!cInvenTory.InvenItem[sInven[9].ItemIndex - 1].sItemInfo.ItemAgingNum[1])
				{
					cMessageBox.ShowMessage(MESSAGE_HAVE_NOT_AGINGITEM);
					return;
				}
				chaPremiumitem.UsePremiumItem(115);
			}



			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin84))
			{
				chaPremiumitem.UsePremiumItem(116);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin73))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(117);


			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin74))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(118);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin75))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(119);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin76))
			{
				if (sinChar->Level < 10)
				{
					cMessageBox.ShowMessage(MESSAGE_PET_USE_LEVEL);
					return;
				}
				chaPremiumitem.UsePremiumItem(120);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin78))
			{
				if (chaPremiumitem.m_ThirdEyesTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(121);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin85))
			{
				chaPremiumitem.UsePremiumItem(122);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin79))
			{
				if (chaPremiumitem.m_ExpUpPotionTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(123);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin81))
			{
				if (chaPremiumitem.m_VampiricCuspidTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(124);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin82))
			{
				if (chaPremiumitem.m_ManaRechargingPTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(125);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin83))
			{
				if (chaPremiumitem.m_ManaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(126);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin86))
			{
				if (chaPremiumitem.m_VampiricCuspidEXTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(127);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin87))
			{
				if (chaPremiumitem.m_VampiricCuspidEXTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(128);
			}


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin88))
			{
				if (chaPremiumitem.m_VampiricCuspidEXTime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				chaPremiumitem.UsePremiumItem(129);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin89))
				chaPremiumitem.UsePremiumItem(130);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin90))
				chaPremiumitem.UsePremiumItem(131);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin91))
			{
				if (chaPremiumitem.m_StaminaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(132);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin92))
			{
				if (chaPremiumitem.m_StaminaReducePotiontime > 0)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					return;
				}

				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				chaPremiumitem.UsePremiumItem(133);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin93))
			{
				if (sinChar->Level > 19)
				{
					chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
					chaPremiumitem.UsePremiumItem(134);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin94))
			{
				if (sinChar->Level > 19)
				{
					chaPremiumitem.TelePortCore.ItemIndex = SelectInvenItemIndex - 1;
					chaPremiumitem.UsePremiumItem(135);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin95))
				chaPremiumitem.UsePremiumItem(136);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin96))
				chaPremiumitem.UsePremiumItem(137);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin97))
				chaPremiumitem.UsePremiumItem(138);

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI1 | sin98))
				chaPremiumitem.UsePremiumItem(139);


			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin40))
				chaPremiumitem.UsePremiumItem(140);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin41))
				chaPremiumitem.UsePremiumItem(141);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin42))
				chaPremiumitem.UsePremiumItem(142);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin43))
				chaPremiumitem.UsePremiumItem(143);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin44))
				chaPremiumitem.UsePremiumItem(144);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin45))
				chaPremiumitem.UsePremiumItem(145);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin46))
				chaPremiumitem.UsePremiumItem(146);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin47))
				chaPremiumitem.UsePremiumItem(147);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin48))
				chaPremiumitem.UsePremiumItem(148);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin49))
				chaPremiumitem.UsePremiumItem(149);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin50))
				chaPremiumitem.UsePremiumItem(150);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin51))
				chaPremiumitem.UsePremiumItem(151);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin52))
				chaPremiumitem.UsePremiumItem(152);
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin53))
				chaPremiumitem.UsePremiumItem(153);
			

		

			//aging
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin90))
				chaPremiumitem.UsePremiumItem(161);//age+15
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin91))
				chaPremiumitem.UsePremiumItem(162);//age+16
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin92))
				chaPremiumitem.UsePremiumItem(163);//age+17
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin93))
				chaPremiumitem.UsePremiumItem(164);//age+18

			
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin20))
			{
				chaPremiumitem.UsePremiumItem(165);
			}
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin21))
			{
				chaPremiumitem.UsePremiumItem(166);
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin89))
			{
				if (sinChar->Level > 149)
				{
					chaPremiumitem.UsePremiumItem(153);
				}
				else
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
			}

			
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin90))
			{
				sSKILL elixirIRA;

				for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
				{
					if (ContinueSkill[i].Flag)
					{
						if (ContinueSkill[i].CODE == ELIXIR_IRA)
						{
							return;
						}
						if (ContinueSkill[i].CODE == ELIXIR_GLORIA)
						{
							return;
						}
					}
				}

				for (int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if (sSkill[j].CODE == ELIXIR_IRA)
					{
						memcpy(&elixirIRA, &sSkill[j], sizeof(sSKILL));
						elixirIRA.UseTime = 3600;
						sinContinueSkillSet(&elixirIRA);
						chaPremiumitem.UsePremiumItem(9);
						break;
					}
				}
			}
			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin91))
			{
				sSKILL elixirGLORIA;

				for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
				{
					if (ContinueSkill[i].Flag)
					{
						if (ContinueSkill[i].CODE == ELIXIR_GLORIA)
						{
							return;
						}
						if (ContinueSkill[i].CODE == ELIXIR_IRA)
						{
							return;
						}
					}
				}

				for (int j = 0; j < SIN_MAX_SKILL; j++)
				{
					if (sSkill[j].CODE == ELIXIR_GLORIA)
					{
						memcpy(&elixirGLORIA, &sSkill[j], sizeof(sSKILL));
						elixirGLORIA.UseTime = 3600;
						sinContinueSkillSet(&elixirGLORIA);
						chaPremiumitem.UsePremiumItem(9);
						break;
					}
				}
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin02))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin02;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			 if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI2 | sin83))
				return;

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin03))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin03;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin04))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin04;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin05))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin05;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin06))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin06;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin07))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin07;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin08))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin08;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin09))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin09;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin10))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin10;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin11))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin11;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin12))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin12;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin13))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin13;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin14))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin14;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin15))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin15;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin16))
			{
				if (chaPremiumitem.bUpdateTimeDelayFlag)
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_DELAYTIME);
					return;
				}

				haCastleSkillUseFlag = 1;

				smTRANS_COMMAND smPacket;

				smPacket.code = OpCode::OPCODE_USEITEM_CODE;
				smPacket.WParam = sinBI3 | sin16;
				smPacket.EParam = 0;
				smPacket.size = sizeof(smPacket);

				extern SocketData* smWsockDataServer;

				if (smWsockDataServer)
				{
					smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
				};
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin17))
			{
				haCastleSkillUseFlag = 1;
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin18)) {
				haCastleSkillUseFlag = 1;
			}

			if (InvenItem[SelectInvenItemIndex - 1].sItemInfo.CODE == (sinBI3 | sin19)) {
				haCastleSkillUseFlag = 1;
			}

			if (haCastleSkillUseFlag != 1)return;


			if (!sinItemPickUpDelayFlag)
			{
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount = 300;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
				SaveGameData();
			}


		}


		int UseFlag2 = 0;


		if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK2) == sinCH1)
		{
			if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE) return;

			for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
			{
				if (ContinueSkill[i].Flag)
				{
					if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
					{
						return;
					}
				}
			}

#ifdef _LANGUAGE_ENGLISH
			if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin01)
			{
				switch (sinChar->JOB_CODE)
				{
				case JOBCODE_MECHANICIAN:
				case JOBCODE_FIGHTER:
				case JOBCODE_PIKEMAN:
				case JOBCODE_KNIGHT:
				case JOBCODE_MAGICIAN:
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_MALE);

					break;
				case JOBCODE_ARCHER:
				case JOBCODE_ATALANTA:
				case JOBCODE_PRIESTESS:
					UseFlag2 = 1;
					break;
				}
			}
			else if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin02)
			{
				switch (sinChar->JOB_CODE)
				{
				case JOBCODE_ARCHER:
				case JOBCODE_ATALANTA:
				case JOBCODE_PRIESTESS:
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_FEMALE);

					break;
				case JOBCODE_MECHANICIAN:
				case JOBCODE_FIGHTER:
				case JOBCODE_PIKEMAN:
				case JOBCODE_KNIGHT:
				case JOBCODE_MAGICIAN:
					UseFlag2 = 1;
					break;
				}
			}
#else
			if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin01 ||
				(InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin02)
			{
				switch (sinChar->JOB_CODE)
				{
				case JOBCODE_ARCHER:
				case JOBCODE_ATALANTA:
				case JOBCODE_PRIESTESS:
				case JOBCODE_ASSASSINE:
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_FEMALE);

					break;
				case JOBCODE_MECHANICIAN:
				case JOBCODE_FIGHTER:
				case JOBCODE_PIKEMAN:
				case JOBCODE_KNIGHT:
				case JOBCODE_MAGICIAN:
				case JOBCODE_SHAMAN:
					UseFlag2 = 1;

					break;
				}
			}
#endif

			if ((InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin03 ||
				(InvenItem[SelectInvenItemIndex - 1].CODE &sinITEM_MASK3) == sin04)
			{
				switch (sinChar->JOB_CODE)
				{
				case JOBCODE_ARCHER:
				case JOBCODE_ATALANTA:
				case JOBCODE_PRIESTESS:
				case JOBCODE_ASSASSINE:
					UseFlag2 = 1;

					break;
				case JOBCODE_MECHANICIAN:
				case JOBCODE_FIGHTER:
				case JOBCODE_PIKEMAN:
				case JOBCODE_KNIGHT:
				case JOBCODE_MAGICIAN:
				case JOBCODE_SHAMAN:
					cMessageBox.ShowMessage(MESSAGE_NOT_USE_MALE);
					break;

				}

			}


			if (cItem.GetItemLimitTime(&InvenItem[SelectInvenItemIndex - 1]) == FALSE)
			{
				wsprintf(szBuff, "%s : %s", sinChar->szName, sinDeadCandyEat);
				SendChatMessageToServer(szBuff);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				sinUsePotionDelayFlag = 1;
				UseFlag2 = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}

			if (!sinItemPickUpDelayFlag && UseFlag2)
			{
				InvenItem[SelectInvenItemIndex - 1].sItemInfo.PotionCount = 100;
				sinThrowItemToFeild(&InvenItem[SelectInvenItemIndex - 1]);
				InvenItem[SelectInvenItemIndex - 1].Flag = 0;
				cInvenTory.CheckWeight();
				ReFormInvenItem();
			}
		}

	}
	ReFormPotionNum();

}

void cINVENTORY::RButtonUp(int x, int y)
{

}

void cINVENTORY::KeyDown()
{

	sITEM TempPotion;

	memset(&TempPotion, 0, sizeof(sITEM));
	int CountTemp = 0;
	int sArrowPosi = 0;
	char szKeyBuff[3] = { '1','2','3' };

	if (sinGetKeyClick('V'))
	{
		cHelpPet.PetMessage("*InvenTory", 3);
		if (cInvenTory.OpenFlag)cInvenTory.OpenFlag = SIN_CLOSE;
		else cInvenTory.OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_INVENTORY);
		if (cInvenTory.OpenFlag)
		{
			if (!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}

	}

	//Traje
	if (sinGetKeyClick('T'))
	{
		setCostumer();
	}
	

	int TempPotionCount = 0;




	for (int i = 0; i < 3; i++)
	{
		if (sinGetKeyClick(szKeyBuff[i]))
		{
			if (SelectPotionIndex)
			{
				if (VRKeyBuff[VK_SHIFT])
				{
					if (MouseItem.Flag)break;
					if (MyShopSendButton || cMyShop.OpenFlag)break;
					if (InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount <= 0)
					{
						InvenItem[SelectPotionIndex - 1].Flag = 0;
						ReFormInvenItem();
						ReFormPotionNum();
						break;

					}
					if (sInven[i + 10].ItemIndex)
					{
						if (InvenItem[sInven[i + 10].ItemIndex - 1].CODE == InvenItem[SelectPotionIndex - 1].CODE)
						{
							TempPotionCount = InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount;
							for (int p = 0; p < TempPotionCount; p++)
							{
								if (sinChar->Potion_Space > InvenItem[sInven[i + 10].ItemIndex - 1].sItemInfo.PotionCount)
								{
									InvenItem[sInven[i + 10].ItemIndex - 1].sItemInfo.PotionCount++;
									InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount--;
									sinPlaySound(InvenItem[SelectPotionIndex - 1].SoundIndex);
									if (InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount <= 0)
									{
										InvenItem[SelectPotionIndex - 1].Flag = 0;
										break;
									}
								}
							}
						}
					}
					else
					{
						memcpy(&TempPotion, &InvenItem[SelectPotionIndex - 1], sizeof(sITEM));
						TempPotion.SetX = sInven[i + 10].Rect.left + (((sInven[i + 10].Rect.right - sInven[i + 10].Rect.left) - InvenItem[SelectPotionIndex - 1].w) / 2);
						TempPotion.SetY = sInven[i + 10].Rect.top + (((sInven[i + 10].Rect.bottom - sInven[i + 10].Rect.top) - InvenItem[SelectPotionIndex - 1].h) / 2);

						TempPotion.sItemInfo.PotionCount = 0;
						TempPotion.Flag = 1;
						TempPotion.ItemPosition = i + 10 + 1;
						CountTemp = InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount;
						for (int f = 0; f < CountTemp; f++)
						{
							if (sinChar->Potion_Space > TempPotion.sItemInfo.PotionCount)
							{
								TempPotion.sItemInfo.PotionCount++;
								InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount--;
								if (InvenItem[SelectPotionIndex - 1].sItemInfo.PotionCount <= 0)
								{
									InvenItem[SelectPotionIndex - 1].Flag = 0;
									break;
								}

							}

						}
						LastSetInvenItem(&TempPotion, 1);
					}

				}

				else
				{
					if (VRKeyBuff[VK_SHIFT])break;
					if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag)break;
					if (sInven[i + 10].ItemIndex)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[sInven[i + 10].ItemIndex - 1];
							break;
						}
					}
				}

			}
			else
			{
				if (VRKeyBuff[VK_SHIFT])break;
				if (cWareHouse.OpenFlag || cTrade.OpenFlag || cCraftItem.OpenFlag)break;
				if (sInven[i + 10].ItemIndex)
				{
					if (sinActionPotion())
					{
						cHelpPet.PetMessage("*Potion_ShortKey", 3 + i);
						pUsePotion = &InvenItem[sInven[i + 10].ItemIndex - 1];
						break;
					}
				}
			}
		}
	}

	if (!cTrade.OpenFlag && !sinUsePotionDelayFlag)
	{

		if (sinGetKeyClick('E'))
		{
			if (ArrowState[0] == 0)
			{
				sArrowPosi = 2;
			}
			else
			{
				sArrowPosi = 1;
			}
			sinButtonFlag = sArrowPosi;
			SelectInvenItemIndex = 0;
			ChangeABItem(sArrowPosi);
		}
		if (sinGetKeyClick('W'))
		{
			/*if (GetTickCount() - CostumeTimer < 2000)
			{
				extern cMESSAGEBOX cMessageBox;
				cMessageBox.ShowMessageEvent("Aguarde 2 segundos para poder trocar o slot!");
			}
			else*/
			if (ArrowState[1] == 0) {
				sArrowPosi = 4;
				CostumeTimer = GetTickCount();
			}
			else {
				sArrowPosi = 3;
				CostumeTimer = GetTickCount();
			}
			sinButtonFlag = sArrowPosi;

			sinChangeSetFlag = sArrowPosi;

			SetItemToChar();


		}
	}
}



int cINVENTORY::LoadItemInfo()
{
	int i;

	int TempItemIndex[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int TempItemIndex2[15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	char szFilePath[256];

	sITEM sinTempItem;
	int TEstFlag = 1;
	int cnt = 0;


	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItemTemp[i].Flag)
		{
			sinSetSpecialItemCode(&InvenItemTemp[i].sItemInfo);
		}
		if (InvenItem[i].Flag)
		{
			sinSetSpecialItemCode(&InvenItem[i].sItemInfo);
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (InvenItem[i].sItemInfo.CODE == sItem[j].CODE)
				{
					memcpy(&sinTempItem, &sItem[j], sizeof(sITEM));
					memcpy(&sinTempItem.sItemInfo, &InvenItem[i].sItemInfo, sizeof(sITEMINFO));
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

					if (!sItem[j].lpTempItem)
					{
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);

						if (!sItem[j].lpTempItem)
							TEstFlag = 0;
					}
					if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
					{
						if (InvenItem[i].sItemInfo.PotionCount <= 1)
						{

							for (cnt = 0; cnt < MAX_ITEM; cnt++)
							{
								if (sItem[cnt].sItemInfo.CODE == (sinPZ1 | sin00))
									break;
							}
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[cnt].ItemFilePath, sItem[cnt].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sinTempItem.w = sItem[cnt].w;
							sinTempItem.h = sItem[cnt].h;
						}
						else
						{
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sinTempItem.w = sItem[j].w;
							sinTempItem.h = sItem[j].h;
						}
					}

					sinTempItem.lpItem = sItem[j].lpTempItem;
					sinTempItem.x = InvenItem[i].x;
					sinTempItem.y = InvenItem[i].y;
					sinTempItem.ItemPosition = InvenItem[i].ItemPosition;
					sinTempItem.Flag = 1;
					memcpy(&InvenItem[i], &sinTempItem, sizeof(sITEM));
					if (InvenItem[i].ItemPosition)
					{
						sInven[InvenItem[i].ItemPosition - 1].ItemIndex = i + 1;
						if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[i].CODE&sinITEM_MASK2) == sinWD1)

						{
							sinSetCharItem(InvenItem[i].CODE, 2, TRUE);
							sinSetCharItem(InvenItem[i].CODE, 4, TRUE);
						}
						else

						{
							
							sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, TRUE);
						}
					}
					break;
				}
			}
		}
	}

	for (i = 0; i < 84; i++)
	{
		if (InvenItemTemp[i].Flag)
		{
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (InvenItemTemp[i].sItemInfo.CODE == sItem[j].CODE)
				{
					memcpy(&sinTempItem, &sItem[j], sizeof(sITEM));
					memcpy(&sinTempItem.sItemInfo, &InvenItemTemp[i].sItemInfo, sizeof(sITEMINFO));
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

					if (!sItem[j].lpTempItem)
					{
						sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);

						if (!sItem[j].lpTempItem)
						{
							TEstFlag = 0;
						}
					}


					if ((InvenItemTemp[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (InvenItemTemp[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
					{
						if (InvenItemTemp[i].sItemInfo.PotionCount <= 1)
						{

							for (cnt = 0; cnt < MAX_ITEM; cnt++)
							{
								if (sItem[cnt].sItemInfo.CODE == (sinPZ1 | sin00))
									break;
							}
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[cnt].ItemFilePath, sItem[cnt].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sinTempItem.w = sItem[cnt].w;
							sinTempItem.h = sItem[cnt].h;
						}
						else
						{
							wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
							sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
							sinTempItem.w = sItem[j].w;
							sinTempItem.h = sItem[j].h;
						}
					}

					sinTempItem.lpItem = sItem[j].lpTempItem;
					sinTempItem.x = InvenItemTemp[i].x;
					sinTempItem.y = InvenItemTemp[i].y;
					sinTempItem.ItemPosition = InvenItemTemp[i].ItemPosition;
					sinTempItem.Flag = 1;
					memcpy(&InvenItemTemp[i], &sinTempItem, sizeof(sITEM));
					break;
				}
			}
		}
	}


	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItemTemp[i].Flag)
		{
			cItem.GetItemLimitTime(&InvenItemTemp[i]);

			if (InvenItemTemp[i].x < StartX || InvenItemTemp[i].x > 800 || InvenItemTemp[i].y < StartY || InvenItemTemp[i].y > 600)
				ReSetPotionXY(&InvenItemTemp[i], 1);

			if (InvenItemTemp[i].ItemPosition)
			{
				if (!TempItemIndex2[InvenItemTemp[i].ItemPosition])
				{
					TempItemIndex2[InvenItemTemp[i].ItemPosition] = i + 1;
				}
				else
				{
					InvenItemTemp[i].Flag = 0;
					InvenItemTemp[TempItemIndex2[InvenItemTemp[i].ItemPosition] - 1].Flag = 0;
				}
			}

			if (InvenItemTemp[i].ItemPosition == 2)
			{
				if (InvenItemTemp[i].Class == ITEM_CLASS_WEAPON_TWO)
					break;
			}

			if (!CheckItemForm(&InvenItemTemp[i].sItemInfo))
			{
				SendSetHackUser(FALSE);
				InvenItemTemp[i].Flag = 0;
			}



		}
	}

	bool ArmorFlag = false;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			cItem.GetItemLimitTime(&InvenItem[i]);
			if (InvenItem[i].x < StartX || InvenItem[i].x > 800 || InvenItem[i].y < StartY || InvenItem[i].y > 600)
				ReSetPotionXY(&InvenItem[i]);

			if (InvenItem[i].ItemPosition > 0)
			{
				if (InvenItem[i].ItemPosition >= 15)
					continue;


				if (InvenItem[i].ItemPosition == 3)
					ArmorFlag = true;

				if (!TempItemIndex[InvenItem[i].ItemPosition])
				{
					TempItemIndex[InvenItem[i].ItemPosition] = i + 1;
				}
				else
				{
					InvenItem[i].Flag = 0;
					InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].Flag = 0;
					if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].Class == ITEM_CLASS_WEAPON_TWO)
					{
						if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].ItemPosition == 1)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].CODE == InvenItem[sInven[1].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
								sInven[1].ItemIndex = 0;
							}
						}
						if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].ItemPosition == 2)
						{
							if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].CODE == InvenItem[sInven[0].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
								sInven[0].ItemIndex = 0;
							}
						}
					}
					if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].ItemPosition)
						sInven[TempItemIndex[InvenItem[i].ItemPosition] - 1].ItemIndex = 0;

					if (InvenItem[i].SetModelPosi)
					{
						if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[i].CODE&sinITEM_MASK2) == sinWD1)
						{
							sinSetCharItem(InvenItem[i].CODE, 2, FALSE);
							sinSetCharItem(InvenItem[i].CODE, 4, FALSE);
						}
						else
							sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

					}

					if (InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].SetModelPosi)
					{
						sinSetCharItem(InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].CODE, InvenItem[TempItemIndex[InvenItem[i].ItemPosition] - 1].SetModelPosi, FALSE);
					}

					if (InvenItem[i].ItemPosition)
						sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;

					if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
					{
						if (InvenItem[i].ItemPosition == 1)
						{
							if (InvenItem[i].CODE == InvenItem[sInven[1].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
								sInven[1].ItemIndex = 0;

							}
						}
						if (InvenItem[i].ItemPosition == 2)
						{
							if (InvenItem[i].CODE == InvenItem[sInven[0].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
								sInven[0].ItemIndex = 0;
							}
						}
					}
				}


				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (InvenItem[i].ItemPosition == 1)
					{
						if (InvenItem[i].CODE != InvenItem[sInven[1].ItemIndex - 1].CODE)
						{
							InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
							InvenItem[i].Flag = 0;
							sInven[1].ItemIndex = 0;
							sInven[0].ItemIndex = 0;
							if (InvenItem[i].SetModelPosi)
							{
									sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
							}
						}
					}
					if (InvenItem[i].ItemPosition == 2)
					{
						if (InvenItem[i].CODE != InvenItem[sInven[0].ItemIndex - 1].CODE)
						{
							InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
							InvenItem[i].Flag = 0;
							sInven[0].ItemIndex = 0;
							sInven[1].ItemIndex = 0;
							if (InvenItem[i].SetModelPosi)
							{

									sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
							}
						}
					}
				}
			}


			if (!InvenItem[i].lpItem)
				cMessageBox.ShowMessage(MESSAGE_NOTEXIT_ITEMIMAGE);




			if (InvenItem[i].ItemPosition == 2)
			{
				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
					continue;
			}

			if (!CheckItemForm(&InvenItem[i].sItemInfo))
			{
				SendSetHackUser(FALSE);
				InvenItem[i].Flag = 0;
				if (InvenItem[i].ItemPosition)
				{
					sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
					sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;

				}
				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
				{
					InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
					sInven[1].ItemIndex = 0;
				}
			}
		}

	}

	if (!ArmorFlag)
		sinSetCharItem(NULL, INVENTORY_POS_ARMOR, FALSE);

	ReformCharForm();
	LoadCharState();

	SearchJobAndSetting();
	ReFormInvenItem();

	CheckWeight();

	cSkill.SearchUseSkill();
	SetItemToChar();

	ReFormPotionNum();
	PotionCheckNumJumpFlag = 0;
	CheckRequireItem();


	if (MouseItem.Flag)
	{
		for (int j = 0; j < MAX_ITEM; j++)
		{
			if (MouseItem.sItemInfo.CODE == sItem[j].CODE)
			{
				memcpy(&sinTempItem, &sItem[j], sizeof(sITEM));
				memcpy(&sinTempItem.sItemInfo, &MouseItem.sItemInfo, sizeof(sITEMINFO));
				wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

				if (!sItem[j].lpTempItem)
				{
					sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
				}

				sinTempItem.lpItem = sItem[j].lpTempItem;
				sinTempItem.x = MouseItem.x;
				sinTempItem.y = MouseItem.y;
				sinTempItem.ItemPosition = MouseItem.ItemPosition;
				sinTempItem.Flag = 1;
				ReFormInvenItem();
				memcpy(&MouseItem, &sinTempItem, sizeof(sITEM));
				cInvenTory.AutoSetInvenItem(&MouseItem);
				break;
			}
		}
	}


	CheckResetInvenItem();
	cSkill.InitReformSkillPointForm();
	ReFormMousePotionNum();
	CheckSpecialItemPosi();
	ChangeSpecialItem(2);
	CheckChangeJob_QuestItem();
	CheckPuzzle();
	cHelpPet.CheckPetData();
	cPCBANGPet.CheckPetData();
	ReSetQuestItemPosi();
	return TRUE;
}


int cINVENTORY::ReSetQuestItemPosi()
{

	sITEM *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if (pItem->x > 1000 && pItem->x < 2000)
		{
			pItem->x += 9000;
		}
	}
	return TRUE;
}

int cINVENTORY::SetSpecialItem(sITEM *pItem)
{
	if (pItem->sItemInfo.SpecialItemFlag[1] != ITEM_KIND_SPECIAL)return FALSE;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (44 * 6) - pItem->w;
	cy = (44 * 3) - pItem->h;

	int TempWidth = 0;
	if (SpecialItemShowFlag)
	{
		TempWidth = 0;
	}
	else
		TempWidth = 10000;


	for (cntx = (StartX + TempWidth); cntx <= StartX + TempWidth + cx; cntx += 44)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 44)
		{
			flag = 0;
			for (int i = 84; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].Flag && InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
				{
					if (InvenItem[i].x < TempWidth)
					{
						rect.left = InvenItem[i].x + TempWidth;
						rect.right = InvenItem[i].x + TempWidth + InvenItem[i].w;
					}
					else
					{
						rect.left = InvenItem[i].x;
						rect.right = InvenItem[i].x + InvenItem[i].w;
					}
					rect.top = InvenItem[i].y;
					rect.bottom = InvenItem[i].y + InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->SetX = cntx + ((44 - pItem->w) / 2);
				pItem->SetY = cnty + ((44 - pItem->h) / 2);
				pItem->ItemPosition = 0;

				for (int j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (InvenItem[j].Flag == 0)
					{
						CheckInvenItemForm();
						memcpy(&InvenItem[j], pItem, sizeof(sITEM));
						InvenItem[j].x = pItem->SetX;
						InvenItem[j].y = pItem->SetY;
						ReFormInvenItem();
						SetItemToChar();
						sinPlaySound(InvenItem[j].SoundIndex);
						CheckWeight();


						SendCheckItemToServer(&InvenItem[j].sItemInfo);
						CheckDamage();
						ReFormPotionNum();
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}


int cINVENTORY::AutoSetInvenItem(sITEM *pItem, int PostBox)
{
	char szBuff[128];

	if (SetSpecialItem(pItem))
		return TRUE;

	ChangeSpecialItem(2);



	if (!PostBox)
	{
		if (!CheckSetOk(pItem, 1))
			return FALSE;
	}


	if (PostBox == 2)
	{
		pItem->SetX = StartX + (22 * 8);
		pItem->SetY = StartY;
		if (LastSetInvenItem(pItem, 1))
		{
			wsprintf(szBuff, "%s %s", pItem->sItemInfo.ItemName, RecvItemTT);
			cMessageBox.ShowMessageEvent(szBuff);
			return TRUE;
		}
	}

	if (PostBox == 3)
	{
		wsprintf(szBuff, "%s %s", pItem->sItemInfo.ItemName, RecvItemTT);
		cMessageBox.ShowMessageEvent(szBuff);
	}


	if (AutoSetPotion(pItem))
		return TRUE;


	for (int i = 0; i < INVENTORY_MAX_POS; i++)
	{
		if (pItem->Class & sInven[i].Position)
		{
			if (!sInven[i].ItemIndex)
			{
				if (sInven[i].ItemIndex)
					break;


				if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (sInven[0].ItemIndex || sInven[1].ItemIndex)
						break;
				}


				if (pItem->sItemInfo.NotUseFlag)
					break;

				pItem->SetX = sInven[i].Rect.left + (((sInven[i].Rect.right - sInven[i].Rect.left) - pItem->w) / 2);
				pItem->SetY = sInven[i].Rect.top + (((sInven[i].Rect.bottom - sInven[i].Rect.top) - pItem->h) / 2);
				pItem->ItemPosition = i + 1;

				if (LastSetInvenItem(pItem, 1))
					return TRUE;
			}
		}
	}


	if (InvenEmptyAearCheck(pItem))
		return TRUE;


	cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);

	sinOverWeightCnt++;

	return FALSE;
}


int cINVENTORY::InvenEmptyAearCheck(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	if (AutoSetPotionToBox(pItem))return TRUE;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].Flag)
				{
					rect.left = InvenItem[i].x;
					rect.right = InvenItem[i].x + InvenItem[i].w;
					rect.top = InvenItem[i].y;
					rect.bottom = InvenItem[i].y + InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}

			}
			if (flag == 0)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				LastSetInvenItem(pItem, 1);
				return TRUE;
			}
		}
	}
	return FALSE;
}


int cINVENTORY::LastSetInvenItem(sITEM *pItem, int AutoSet)
{
	int PassFlag = 0;
	if (!AutoSet)
		if (!InvenNotOpenCheck(pItem))return FALSE;

	for (int j = 0; j < INVENTORY_MAXITEM; j++)
	{
		if (InvenItem[j].Flag == 0)
		{
			if (sinPosionItem)
			{
				if (sinPosionItem->sItemInfo.ItemHeader.Head == InvenItem[j].sItemInfo.ItemHeader.Head)
					continue;

			}
			CheckInvenItemForm();
			memcpy(&InvenItem[j], pItem, sizeof(sITEM));
			InvenItem[j].x = pItem->SetX;
			InvenItem[j].y = pItem->SetY;
			if (InvenItem[j].ItemPosition)
			{
				SetTwoHandItem(&InvenItem[j]);
				sInven[InvenItem[j].ItemPosition - 1].ItemIndex = j + 1;
				if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[j].CODE&sinITEM_MASK2) == sinWD1)
				{
					sinSetCharItem(InvenItem[j].CODE, 2, TRUE);
					sinSetCharItem(InvenItem[j].CODE, 4, TRUE);
				}
				else
				{
					sinSetCharItem(InvenItem[j].CODE, pItem->SetModelPosi, TRUE);
				}
			}
			pItem->Flag = 0;
			ReFormInvenItem();
			SetItemToChar();
			sinPlaySound(InvenItem[j].SoundIndex);
			CheckWeight();

			if (InvenItem[j].x < StartX || InvenItem[j].x > 800 || InvenItem[j].y < StartY || InvenItem[j].y > 600)
			{
				AutoSetInvenItem(&InvenItem[j]);
			}


			SendCheckItemToServer(&InvenItem[j].sItemInfo);
			CheckDamage();
			ReFormPotionNum();


			CheckPuzzle();
			return TRUE;

		}
	}
	ReFormInvenItem();
	return FALSE;
}




int cINVENTORY::UsePotion(int x, int y)
{
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].x < x  && InvenItem[i].x + InvenItem[i].w > x  &&
				InvenItem[i].y < y  && InvenItem[i].y + InvenItem[i].h > y)
			{
				if (InvenItem[i].ItemPosition == 11 || InvenItem[i].ItemPosition == 12 || InvenItem[i].ItemPosition == 13)
				{
					if (InvenItem[i].Class == ITEM_CLASS_POTION)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[i];
							sinUsePotionDelayFlag = 1;
						}

					}

				}
				else
				{
					if (!OpenFlag)break;
					if (InvenItem[i].Class == ITEM_CLASS_POTION)
					{
						if (sinActionPotion())
						{
							pUsePotion = &InvenItem[i];
							sinUsePotionDelayFlag = 1;
						}
					}
				}
			}
		}
	}
	ReFormPotionNum();
	return FALSE;

}

int cINVENTORY::ReSettingPotion()
{
	sITEM TempPotionItem;
	int i = 0, j = 0, cnt = 0;

	memset(&TempPotionItem, 0, sizeof(sITEM));
	for (i = 10; i < 13; i++)
	{
		if (sInven[i].ItemIndex)
		{
			if (InvenItem[sInven[i].ItemIndex - 1].Flag)
			{
				memcpy(&TempPotionItem, &InvenItem[sInven[i].ItemIndex - 1], sizeof(sITEM));
				cnt = TempPotionItem.sItemInfo.PotionCount;
				if (sinChar->Potion_Space < InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount)
				{
					TempPotionItem.sItemInfo.PotionCount = InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount - sinChar->Potion_Space;
					InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount -= TempPotionItem.sItemInfo.PotionCount;
					if (!InvenEmptyAearCheck(&TempPotionItem))
					{
						NoSettingThrowItem(&TempPotionItem);
					}

				}
			}

		}

	}
	ReFormPotionNum();

	return TRUE;
}

int BackUpX, BackUpY, BackUpPosi = 0;

int cINVENTORY::MouseSetPotion(sITEM *pItem)
{

	int i = 0, cnt;
	sITEM TempPotionItem;
	sinPosionItem = 0;

	if (!pItem->Flag)
		return FALSE;

	BackUpItemIndex = 0;
	if (CrashItemIndex[0])
	{
		if (pMessageItem)
		{
			BackUpX = pMessageItem->x;
			BackUpY = pMessageItem->y;
			BackUpPosi = pMessageItem->ItemPosition;
			sinPosionItem = &InvenItem[CrashItemIndex[0] - 1];
			BackUpItemIndex = CrashItemIndex[0];

		}
		if (pItem->ItemPosition)
		{
			memcpy(&TempPotionItem, pItem, sizeof(sITEM));
			if (pItem->CODE == InvenItem[CrashItemIndex[0] - 1].CODE)
			{
				cnt = pItem->sItemInfo.PotionCount;
				for (i = 0; i < cnt; i++)
				{
					if (sinChar->Potion_Space > InvenItem[CrashItemIndex[0] - 1].sItemInfo.PotionCount)
					{
						InvenItem[CrashItemIndex[0] - 1].sItemInfo.PotionCount++;
						pItem->sItemInfo.PotionCount--;
						if (pItem->sItemInfo.PotionCount <= 0)
						{
							pItem->Flag = 0;
							sinPlaySound(pItem->SoundIndex);
							ReFormPotionNum();
							return TRUE;
						}
					}
					else
					{
						if (InvenEmptyAearCheck(pItem))
						{
							ReFormPotionNum();
							return TRUE;
						}
						else
						{
							ResetPotion2();
							if (sinThrowItemToFeild(pItem))
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
							else
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return FALSE;

							}
						}

					}
				}

			}
			else
			{
				memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(sITEM));
				InvenItem[CrashItemIndex[0] - 1].Flag = 0;
				if (sinPosionItem)
					sinPosionItem->Flag = 0;
				TempPotionItem.sItemInfo.PotionCount = 0;
				cnt = pItem->sItemInfo.PotionCount;
				for (i = 0; i < cnt; i++)
				{
					if (sinChar->Potion_Space < pItem->sItemInfo.PotionCount)
					{
						pItem->sItemInfo.PotionCount--;
						TempPotionItem.sItemInfo.PotionCount++;
					}
					else
					{
						ReFormInvenItem();
						if (LastSetInvenItem(pItem))
						{
							if (TempPotionItem.sItemInfo.PotionCount > 0)
							{
								if (InvenEmptyAearCheck(&TempPotionItem))
								{
									memcpy(pItem, &TempItem, sizeof(sITEM));
									pMessageItem = sinPosionItem;
									pMessageItem->x = BackUpX;
									pMessageItem->y = BackUpY;
									pMessageItem->ItemPosition = BackUpPosi;
									sinPosionItem = 0;
									ReFormPotionNum();
									return TRUE;
								}
								else
								{

									memcpy(pItem, &TempItem, sizeof(sITEM));
									if (sinPosionItem)
									{
										pMessageItem = sinPosionItem;
										pMessageItem->x = BackUpX;
										pMessageItem->y = BackUpY;
										pMessageItem->ItemPosition = BackUpPosi;
										sinPosionItem = 0;
									}
									sinThrowItemToFeild(&TempPotionItem);
									ReFormPotionNum();
									return TRUE;
								}
							}
							memcpy(pItem, &TempItem, sizeof(sITEM));
							if (sinPosionItem)
							{
								pMessageItem = sinPosionItem;
								pMessageItem->x = BackUpX;
								pMessageItem->y = BackUpY;
								pMessageItem->ItemPosition = BackUpPosi;
								sinPosionItem = 0;
							}
							ReFormPotionNum();
							return TRUE;
						}
						else
						{
							ReFormPotionNum();
							return FALSE;
						}

					}

				}

			}

		}
		else
		{
			if (pItem->CODE == InvenItem[CrashItemIndex[0] - 1].CODE)
			{

				if (!cInvenTory.OpenFlag)
				{
					SendSetHackUser2(1960, 3);
					return TRUE;
				}

				InvenItem[CrashItemIndex[0] - 1].sItemInfo.PotionCount += pItem->sItemInfo.PotionCount;
				pItem->Flag = 0;
				sinPlaySound(pItem->SoundIndex);
				ReFormPotionNum();
				return TRUE;
			}
			else
			{
				memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(sITEM));
				InvenItem[CrashItemIndex[0] - 1].Flag = 0;

				TempItem.x = pItem->x;
				TempItem.y = pItem->y;
				ReFormInvenItem();
				LastSetInvenItem(pItem);
				memcpy(pItem, &TempItem, sizeof(sITEM));
				if (sinPosionItem)
				{
					pMessageItem = sinPosionItem;
					pMessageItem->x = BackUpX;
					pMessageItem->y = BackUpY;
					pMessageItem->ItemPosition = BackUpPosi;
					sinPosionItem = 0;

				}
				ReFormPotionNum();
				return TRUE;
			}
		}
	}
	else
	{
		if (pItem->ItemPosition)
		{
			memcpy(&TempPotionItem, pItem, sizeof(sITEM));
			TempPotionItem.sItemInfo.PotionCount = 0;
			cnt = pItem->sItemInfo.PotionCount;
			for (i = 0; i < cnt; i++)
			{
				if (sinChar->Potion_Space < pItem->sItemInfo.PotionCount)
				{
					pItem->sItemInfo.PotionCount--;
					TempPotionItem.sItemInfo.PotionCount++;

				}
				else
				{
					ReFormInvenItem();
					if (LastSetInvenItem(pItem))
					{
						if (TempPotionItem.sItemInfo.PotionCount > 0)
						{
							if (InvenEmptyAearCheck(&TempPotionItem))
							{
								ReFormPotionNum();
								return TRUE;
							}
							else
							{

								sinThrowItemToFeild(&TempPotionItem);
								ReFormPotionNum();
								return FALSE;
							}
						}
						ReFormPotionNum();
						return TRUE;
					}
					else
					{
						ReFormPotionNum();
						return FALSE;
					}
				}
			}
		}
		else
		{
			ReFormInvenItem();
			if (LastSetInvenItem(pItem))
			{
				ReFormPotionNum();
				return TRUE;
			}

		}

	}
	ReFormPotionNum();
	return FALSE;
}

int cINVENTORY::AutoSetPotionToBox(sITEM *pItem)
{

	if (pItem->Class != ITEM_CLASS_POTION)return FALSE;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (pItem->CODE == InvenItem[i].CODE)
			{
				if (InvenItem[i].ItemPosition)continue;
				InvenItem[i].sItemInfo.PotionCount += pItem->sItemInfo.PotionCount;
				pItem->Flag = 0;
				sinPlaySound(pItem->SoundIndex);

				if (InvenItem[i].x < 3 || InvenItem[i].y < 10)
					ReSetPotionXY(&InvenItem[i]);
				ReformCharForm();
				cInvenTory.ReFormPotionNum();

				return TRUE;

			}
		}
	}

	return FALSE;
}

int cINVENTORY::AutoSetPotion(sITEM *pItem)
{

	int i = 0, j = 0, cnt = 0;
	sITEM TempPotion;

	if (pItem->Class != ITEM_CLASS_POTION)
		return FALSE;

	for (i = 0; i < INVENTORY_MAX_POS; i++)
	{
		if (pItem->Class & sInven[i].Position)
		{
			if (sInven[i].ItemIndex)
			{
				if (pItem->CODE == InvenItem[sInven[i].ItemIndex - 1].CODE)
				{
					if (sinChar->Potion_Space == InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount)
						continue;

					cnt = pItem->sItemInfo.PotionCount;
					for (j = 0; j < cnt; j++)
					{
						if (sinChar->Potion_Space > InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount)
						{
							InvenItem[sInven[i].ItemIndex - 1].sItemInfo.PotionCount++;
							pItem->sItemInfo.PotionCount--;
							sinPlaySound(pItem->SoundIndex);
							if (pItem->sItemInfo.PotionCount <= 0)
							{
								pItem->Flag = 0;
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
						}
						else
						{
							if (InvenEmptyAearCheck(pItem))
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
							else
							{
								ResetPotion2();
								if (sinThrowItemToFeild(pItem))
								{
									ReformCharForm();
									cInvenTory.ReFormPotionNum();
									return TRUE;
								}
							}
						}
					}
				}
				else
					continue;

			}
			else
			{
				pItem->SetX = sInven[i].Rect.left + (((sInven[i].Rect.right - sInven[i].Rect.left) - pItem->w) / 2);
				pItem->SetY = sInven[i].Rect.top + (((sInven[i].Rect.bottom - sInven[i].Rect.top) - pItem->h) / 2);

				cnt = pItem->sItemInfo.PotionCount;


				pItem->ItemPosition = i + 1;
				memcpy(&TempPotion, pItem, sizeof(sITEM));
				TempPotion.sItemInfo.PotionCount = 0;
				for (j = 0; j < cnt; j++)
				{
					if (sinChar->Potion_Space < pItem->sItemInfo.PotionCount)
					{
						pItem->sItemInfo.PotionCount--;
						TempPotion.sItemInfo.PotionCount++;

					}
					else
					{
						if (LastSetInvenItem(pItem, 1))
						{
							if (TempPotion.sItemInfo.PotionCount > 0)
							{
								if (InvenEmptyAearCheck(&TempPotion))
								{
									ReformCharForm();
									cInvenTory.ReFormPotionNum();
									return TRUE;
								}
							}
							else
							{
								ReformCharForm();
								cInvenTory.ReFormPotionNum();
								return TRUE;
							}
						}

					}
				}
			}
		}
	}

	return FALSE;
}




int cINVENTORY::ClearTwoHandPosiAndItem(sITEM *pItem)
{
	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (sInven[0].ItemIndex)
		{
			InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
			sInven[0].ItemIndex = 0;
			if (InvenItem[sInven[0].ItemIndex - 1].ItemPosition)
			{
				if (InvenItem[sInven[0].ItemIndex - 1].SetModelPosi)

				{
					sinSetCharItem(InvenItem[sInven[0].ItemIndex - 1].CODE, InvenItem[sInven[0].ItemIndex - 1].SetModelPosi, FALSE);
				}

			}

		}
		if (sInven[1].ItemIndex)
		{
			InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
			sInven[1].ItemIndex = 0;
			if (InvenItem[sInven[1].ItemIndex - 1].ItemPosition)
			{
				if (InvenItem[sInven[1].ItemIndex - 1].SetModelPosi)
				{
					sinSetCharItem(InvenItem[sInven[1].ItemIndex - 1].CODE, InvenItem[sInven[1].ItemIndex - 1].SetModelPosi, FALSE);
				}
			}
		}
	}
	return TRUE;
}

int cINVENTORY::SetTwoHandItem(sITEM *pItem)
{

	sITEM TempTwoHandItem;

	memset(&TempTwoHandItem, 0, sizeof(sITEM));

	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (pItem->ItemPosition == 2)
		{
			pItem->ItemPosition = 1;
			pItem->x = sInven[0].Rect.left + (((sInven[0].Rect.right - sInven[0].Rect.left) - pItem->w) / 2);
			pItem->y = sInven[0].Rect.top + (((sInven[0].Rect.bottom - sInven[0].Rect.top) - pItem->h) / 2);
		}

		TempTwoHandItem.x = sInven[1].Rect.left + (((sInven[1].Rect.right - sInven[1].Rect.left) - pItem->w) / 2);
		TempTwoHandItem.y = sInven[1].Rect.top + (((sInven[1].Rect.bottom - sInven[1].Rect.top) - pItem->h) / 2);
		TempTwoHandItem.w = pItem->w;
		TempTwoHandItem.h = pItem->h;
		TempTwoHandItem.ItemPosition = 2;
		TempTwoHandItem.Class = pItem->Class;
		TempTwoHandItem.sItemInfo.CODE = pItem->CODE;
		TempTwoHandItem.sItemInfo.Price = pItem->sItemInfo.Price;
		memcpy(&TempTwoHandItem.lpItem, &pItem->lpItem, sizeof(LPDIRECT3DTEXTURE9));
		TempTwoHandItem.Flag = 1;
		for (int j = 0; j < INVENTORY_MAXITEM; j++)
		{
			if (InvenItem[j].Flag == 0)
			{
				memcpy(&InvenItem[j], &TempTwoHandItem, sizeof(sITEM));
				sInven[1].ItemIndex = j + 1;
				break;
			}
		}
	}

	return TRUE;
}

int cINVENTORY::PickUpTwoHandItem(sITEM *pItem)
{

	sITEM TempPickItem;
	memset(&TempPickItem, 0, sizeof(sITEM));

	if (pItem->ItemPosition)
	{
		if (sInven[0].ItemIndex && sInven[1].ItemIndex)
		{
			memcpy(&TempPickItem, &InvenItem[sInven[0].ItemIndex - 1], sizeof(sITEM));
			InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
			InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
			sInven[0].ItemIndex = 0;
			sInven[1].ItemIndex = 0;
			memcpy(pItem, &TempPickItem, sizeof(sITEM));
			ReFormInvenItem();
			ReformCharForm();
			ReFormPotionNum();
			return TRUE;
		}
	}
	return FALSE;
}


int cINVENTORY::OverlapTwoHandItem(sITEM *pItem)
{
	AutoSetItemIndex = 0;
	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (sInven[1].ItemIndex)
		{
			if (InvenItem[sInven[1].ItemIndex - 1].Class != ITEM_CLASS_WEAPON_TWO)
			{
				if (pItem->ItemPosition == 1)
				{
					if (sInven[1].ItemIndex)
						AutoSetItemIndex = sInven[1].ItemIndex;
				}
				if (pItem->ItemPosition == 2)
				{
					if (sInven[0].ItemIndex)
						AutoSetItemIndex = sInven[0].ItemIndex;
				}
			}
		}
	}
	return TRUE;

}


int cINVENTORY::OverlapTwoHandSwitch(sITEM *pItem)
{
	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (pItem->ItemPosition == 1)
			if (sInven[1].ItemIndex)
				CrashItemIndex[0] = sInven[1].ItemIndex;
		if (pItem->ItemPosition == 2)
			if (sInven[0].ItemIndex)
				CrashItemIndex[0] = sInven[0].ItemIndex;

	}
	return TRUE;
}


int cINVENTORY::InvenNotOpenCheck(sITEM *pItem)
{
	if (!OpenFlag)
		if (pItem->ItemPosition != 11 && pItem->ItemPosition != 12 && pItem->ItemPosition != 13)
			return FALSE;
	return TRUE;
}

int cINVENTORY::PickUpInvenItem(int x, int y, int PickUpFlag)
{
	NotPotionFlag = 0;
	sITEMPRICE sinItemPriceTemp;
	SelectInvenItemIndex = 0;
	SelectPotionIndex = 0;
	int kk = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].x < x  && InvenItem[i].x + InvenItem[i].w > x  &&
				InvenItem[i].y < y  && InvenItem[i].y + InvenItem[i].h > y)
			{
				if (!InvenNotOpenCheck(&InvenItem[i]))return FALSE;
				if (PickUpFlag == 1)
				{
					if (x >= sInven[0].Rect.left && x <= sInven[1].Rect.right)
					{
						if (y >= sInven[0].Rect.top && y <= sInven[1].Rect.bottom)
						{
							if (CostumeFlag)
							{
								if (InvenItem[i].Class != ITEM_CLASS_COSTUME)
									continue;
							}
							else
							{
								if (InvenItem[i].Class == ITEM_CLASS_COSTUME)
									continue;
							}
						}
					}

					if (MyShopItemIndex[i])return FALSE;

					if (InvenItem[i].ItemPosition)
					{
						if (sinChar->Weight[0] > sinChar->Weight[1])
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
							sinOverWeightCnt++;
							return FALSE;
						}
					}

					if (!InvenItem[i].lpItem)
					{
						cMessageBox.ShowMessage(MESSAGE_NOTEXIT_ITEMIMAGE);
						return FALSE;
					}







					for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
					{
						if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
							return FALSE;
					}


					if (CursorClass == SIN_CURSOR_REPAIR)
					{
						sinItemPriceTemp = GetInvenItemPrice(&InvenItem[i]);
						if (RepairInvenItem(&InvenItem[i], sinItemPriceTemp.RepairCost))
						{
							sinPlaySound(SIN_SOUND_REPAIR_ITEM);
						}
						return TRUE;
					}

					InvenItem[i].OldX = InvenItem[i].x;
					InvenItem[i].OldY = InvenItem[i].y;
					pMessageItem = &InvenItem[i];
					PotionIndex = i + 1;
					BackUpItemIndex = i + 1;

					if (CursorClass == SIN_CURSOR_SELL)
					{

						if (!InvenItem[i].sItemInfo.ItemHeader.dwChkSum)return TRUE;


						for (kk = 0; kk < NotSell_Item_CODECnt; kk++)
						{
							if (NotSell_Item_CODE[kk] == InvenItem[i].sItemInfo.CODE)return TRUE;

						}
						for (kk = 0; kk < NotSell_Item_MASKCnt; kk++)
						{
							if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == NotSell_Item_MASK[kk])return TRUE;

						}
						for (kk = 0; kk < NotSell_Item_KINDCnt; kk++)
						{
							if (NotSell_Item_KIND[kk] == InvenItem[i].sItemInfo.ItemKindCode)return TRUE;

						}

						if (InvenItem[i].Class == ITEM_CLASS_POTION ||
							InvenItem[i].sItemInfo.CODE == (sinGF1 | sin01))
						{


							return TRUE;


						}
						else
						{
							if (!cShop.SellItemToShop(&InvenItem[i]))
								return TRUE;
						}

					}
					else
					{
						if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
						{
							PickUpTwoHandItem(&InvenItem[i]);
						}
						memcpy(&MouseItem, &InvenItem[i], sizeof(sITEM));

					}

					InvenItem[i].Flag = 0;
					if (InvenItem[i].ItemPosition)
					{
						if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[i].CODE&sinITEM_MASK2) == sinWD1)
						{
							sinSetCharItem(InvenItem[i].CODE, 2, FALSE);
							sinSetCharItem(InvenItem[i].CODE, 4, FALSE);
						}
						else
						
							sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
						sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;

					}
					ReFormInvenItem();
					CheckWeight();
					SetItemToChar();
					sinPlaySound(InvenItem[i].SoundIndex);
					ColorIndex = 0;

					CheckPuzzle();
					cHelpPet.PetMessage("*InvenTory_Item", 1);
					return TRUE;
				}

				else if (PickUpFlag == 2)
				{
					if (MyShopSendButton)return FALSE;
					if (MyShopItemIndex[i])return FALSE;
					if (InvenItem[i].ItemPosition)return FALSE;

					if (InvenItem[i].sItemInfo.ItemLocked)
					{
						cMessageBox.ShowMessageEvent("Este item n�o pode ser vendido.");
						return FALSE;
					}

					if (InvenItem[i].sItemInfo.CODE == (sinGF1 | sin01))return FALSE;



					if (InvenItem[i].sItemInfo.CODE == (sinOR2 | sin33))return FALSE;


					if (InvenItem[i].sItemInfo.CODE == (sinOA1 | sin36))return FALSE;


					if (InvenItem[i].sItemInfo.CODE == (sinOA1 | sin37))return FALSE;


					for (kk = 0; kk < NotSell_Item_CODECnt; kk++)
					{
						if (NotSell_Item_CODE[kk] == InvenItem[i].sItemInfo.CODE)return FALSE;

					}
					for (kk = 0; kk < NotSell_Item_MASKCnt; kk++)
					{
						if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == NotSell_Item_MASK[kk])return FALSE;

					}
					for (kk = 0; kk < NotSell_Item_KINDCnt; kk++)
					{
						if (NotSell_Item_KIND[kk] == InvenItem[i].sItemInfo.ItemKindCode)return FALSE;

					}

					memcpy(&MyShopMouseItem, &InvenItem[i], sizeof(sITEM));
					memset(&MyShopMouseItem.sItemInfo, 0, sizeof(sITEMINFO));


					MyShopMouseItem.sItemInfo.PotionCount = InvenItem[i].sItemInfo.PotionCount;
					MyShopMouseItem.sItemInfo.ItemHeader = InvenItem[i].sItemInfo.ItemHeader;
					MyShopMouseItem.sItemInfo.Index = i + 1;
					sinMyShopItemPass = 1;

				}
				else
				{
					if (x >= sInven[0].Rect.left && x <= sInven[1].Rect.right)
					{
						if (y >= sInven[0].Rect.top && y <= sInven[1].Rect.bottom)
						{
							if (CostumeFlag)
							{
								if (InvenItem[i].Class != ITEM_CLASS_COSTUME)
									continue;
							}
							else
							{
								if (InvenItem[i].Class == ITEM_CLASS_COSTUME)
									continue;
							}
						}
					}

					if (InvenItem[i].Class == ITEM_CLASS_POTION)
					{
						if (!InvenItem[i].ItemPosition)
							SelectPotionIndex = i + 1;
					}

					cItem.GetItemLimitTime(&InvenItem[i]);
					SelectInvenItemIndex = i + 1;
					ColorIndex = SELECT_ITEM_COLOR;
					sinShowItemInfoFlag = 2;
					cHelpPet.PetMessage("*InvenTory_Item", 0);


					if (cMyShop.OpenFlag)
						cItem.ShowItemInfo(&InvenItem[i], 2, i);
					else
						cItem.ShowItemInfo(&InvenItem[i], 2);
				}
			}
		}
	}
	return FALSE;
}


int cINVENTORY::SetInvenItemAreaCheck(sITEM *pItem)
{

	int i, j;
	ColorIndex = 0;
	CrashItemIndex[0] = 0;
	CrashItemIndex[1] = 0;
	AutoSetItemIndex = 0;


	if (!cInvenTory.OpenFlag)return FALSE;
	for (i = 0; i < INVENTORY_MAX_POS; i++)
	{

		if (CostumeFlag)
		{
			if (i >= 0 && i <= 2)
				continue;
		}
		else
		{
			if (i == 13)
				continue;
		}


		if (CheckInvenPos(pItem->x + 11, pItem->y + 11, pItem->x + pItem->w - 11, pItem->y + pItem->h - 11, sInven[i].Rect))
		{
			ColorRect.left = sInven[i].Rect.left;
			ColorRect.top = sInven[i].Rect.top;
			ColorRect.right = sInven[i].Rect.right - sInven[i].Rect.left;
			ColorRect.bottom = sInven[i].Rect.bottom - sInven[i].Rect.top;
			pItem->SetX = sInven[i].Rect.left + ((ColorRect.right - pItem->w) / 2);
			pItem->SetY = ColorRect.top + ((ColorRect.bottom - pItem->h) / 2);
			pItem->ItemPosition = i + 1;

			if (!(sInven[i].Position & pItem->Class))
			{
				ColorIndex = NOT_SETTING_COLOR;
				return FALSE;
			}
			if (pItem->sItemInfo.NotUseFlag)
			{
				ColorIndex = NOT_USE_COLOR;
				return FALSE;

			}


			if (CrashItemIndex[0] = CrashInvenItem(ColorRect))
			{
				OverlapTwoHandItem(pItem);
				ColorIndex = OVERLAP_BOX_COLOR;
				return TRUE;
			}
			OverlapTwoHandSwitch(pItem);
			ColorIndex = SET_ITEM_CHECK_COLOR;
			return TRUE;
		}

	}


	for (i = pItem->x + 11; i < pItem->x + pItem->w; i += 22)
	{
		for (j = pItem->y + 11; j < pItem->y + pItem->h; j += 22)
		{
			if (StartX <= i && EndX > i && StartY <= j && EndY > j)
			{
				ColorRect.left = StartX + (((i - StartX) / 22) * 22);
				ColorRect.top = StartY + (((j - StartY) / 22) * 22);
				ColorRect.right = pItem->w;
				ColorRect.bottom = pItem->h;
				if (EndX < (ColorRect.left + ColorRect.right) - 11 || EndY < (ColorRect.top + ColorRect.bottom) - 11)
				{
					InitColorRect();
					return FALSE;
				}
				pItem->SetX = ColorRect.left;
				pItem->SetY = ColorRect.top;
				pItem->ItemPosition = 0;
				ColorIndex = SET_ITEM_CHECK_COLOR;



				if (CrashItemIndex[0] = CrashInvenItem(ColorRect))
				{


					if (CrashItemIndex[1] = CrashInvenItem(ColorRect, CrashItemIndex[0]))
					{
						ColorIndex = NOT_SETTING_COLOR;
						CrashItemIndex[1] = 0;
						return FALSE;

					}
					ColorIndex = OVERLAP_ITEM_COLOR;
					return TRUE;
				}
				return TRUE;
			}

		}

	}

	return TRUE;
}


int cINVENTORY::InitColorRect()
{
	ColorRect.left = 0;
	ColorRect.top = 0;
	ColorRect.right = 0;
	ColorRect.bottom = 0;
	return TRUE;

}


int cINVENTORY::CrashInvenItem(RECT &desRect, int PassItemIndex)
{

	RECT rect;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (PassItemIndex != 0)
				if (PassItemIndex == i + 1)continue;
			rect.left = InvenItem[i].x;
			rect.right = InvenItem[i].x + InvenItem[i].w;
			rect.top = InvenItem[i].y;
			rect.bottom = InvenItem[i].y + InvenItem[i].h;

			if (desRect.left > rect.left - desRect.right  && desRect.left < rect.right &&
				desRect.top > rect.top - desRect.bottom && desRect.top < rect.bottom)
			{
				if (CostumeFlag && InvenItem[i].ItemPosition == 3)
					continue;
				if (!CostumeFlag && InvenItem[i].ItemPosition == 14)
					continue;

				return i + 1;
			}
		}
	}

	return FALSE;

}


int cINVENTORY::CheckInvenPos(int x, int y, int lx, int ly, RECT &rect)
{
	if (x <= rect.left)
	{
		if (rect.left >= lx)return FALSE;
	}
	else
	{
		if (x >= rect.right)return FALSE;
	}

	if (y <= rect.top)
	{
		if (rect.top >= ly)return FALSE;
	}
	else
	{
		if (y >= rect.bottom)return FALSE;
	}

	return TRUE;

}

int cINVENTORY::ChangeInvenItem(sITEM *pItem)
{
	int BackUpX = 0, BackUpY = 0, BackUpPosi = 0;

	for (int j = 0; j < SIN_MAX_HELP_NUMBER; j++)
	{
		if (sSinHelp[j].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			return TRUE;
			if (NoSettingThrowItem(&MouseItem))
				return FALSE;
		}
	}





	if (lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_ATTACK || lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_SKILL)
	{



		{
			return FALSE;
		}
	}
	if (!InvenNotOpenCheck(pItem)) return FALSE;
	if (CrashItemIndex[0])
	{
		CheckInvenItemForm();
		if (InvenItem[CrashItemIndex[0] - 1].Class == ITEM_CLASS_POTION)
		{
			if (pMessageItem)
			{
				BackUpX = pMessageItem->x;
				BackUpY = pMessageItem->y;
				BackUpPosi = pMessageItem->ItemPosition;
				sinPosionItem = &InvenItem[CrashItemIndex[0] - 1];
				BackUpItemIndex = CrashItemIndex[0];
			}
		}

		if (InvenItem[CrashItemIndex[0] - 1].Class == ITEM_CLASS_WEAPON_TWO)
			PickUpTwoHandItem(&InvenItem[CrashItemIndex[0] - 1]);

		memcpy(&TempItem, &InvenItem[CrashItemIndex[0] - 1], sizeof(sITEM));
		if (InvenItem[CrashItemIndex[0] - 1].ItemPosition)
			sinSetCharItem(InvenItem[CrashItemIndex[0] - 1].CODE, InvenItem[CrashItemIndex[0] - 1].SetModelPosi, FALSE);
		InvenItem[CrashItemIndex[0] - 1].Flag = 0;
		TempItem.x = pItem->x;
		TempItem.y = pItem->y;
		if (AutoSetItemIndex)
		{
			ReFormInvenItem();
			sinSetCharItem(InvenItem[AutoSetItemIndex - 1].CODE, InvenItem[AutoSetItemIndex - 1].SetModelPosi, FALSE);
			if (!InvenEmptyAearCheck(&InvenItem[AutoSetItemIndex - 1]))
			{
				if (AutoSetItemIndex)
					NoSettingThrowItem(&InvenItem[AutoSetItemIndex - 1], 1);
			}
		}

		ReFormInvenItem();
		LastSetInvenItem(pItem);
		memcpy(pItem, &TempItem, sizeof(sITEM));
		if (sinPosionItem)
		{
			if (InvenItem[CrashItemIndex[0] - 1].Class == ITEM_CLASS_POTION)
			{
				pMessageItem = sinPosionItem;
				pMessageItem->x = BackUpX;
				pMessageItem->y = BackUpY;
				pMessageItem->ItemPosition = BackUpPosi;
				sinPosionItem = 0;
			}

		}
		ReFormInvenItem();
		return TRUE;

	}

	return FALSE;
}


int cINVENTORY::NoSettingThrowItem(sITEM *pItem, int Flag)
{

	if (!pItem)return FALSE;
	if (!pItem->Flag)return FALSE;
	if (!Flag)
	{
		if (cTrade.OpenFlag || cWareHouse.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)return FALSE;
	}
	if (!pItem->sItemInfo.ItemHeader.Head || pItem->sItemInfo.ItemHeader.Head < 0)return FALSE;
	if (pItem->sItemInfo.CODE == (sinGF1 | sin01))return FALSE;


	int kk = 0;

	for (kk = 0; kk < NotDrow_Item_CODECnt; kk++)
	{
		if (NotDrow_Item_CODE[kk] == pItem->sItemInfo.CODE)return FALSE;

	}
	for (kk = 0; kk < NotDrow_Item_MASKCnt; kk++)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotDrow_Item_MASK[kk])return FALSE;

	}
	for (kk = 0; kk < NotDrow_Item_KINDCnt; kk++)
	{
		if (NotDrow_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)return FALSE;

	}

	if (sinThrowItemToFeild(pItem))
	{
		sinPlaySound(pItem->SoundIndex);
		pItem->Flag = 0;
	}
	else
	{
		pItem->Flag = 0;

	}

	return TRUE;
}


int cINVENTORY::ThrowInvenItemToField(sITEM *pItem)
{



	if (cTrade.OpenFlag || cWareHouse.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag)
		return TRUE;

	if (sMessageBox3[MESSAGE_TELEPORT_CORE].Flag)return TRUE;
	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			return TRUE;
		}

	}

	int kk = 0;

	for (kk = 0; kk < NotDrow_Item_CODECnt; kk++)
	{
		if (NotDrow_Item_CODE[kk] == pItem->sItemInfo.CODE)return TRUE;

	}
	for (kk = 0; kk < NotDrow_Item_MASKCnt; kk++)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotDrow_Item_MASK[kk])return TRUE;

	}
	for (kk = 0; kk < NotDrow_Item_KINDCnt; kk++)
	{
		if (NotDrow_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)return TRUE;

	}


	if (cCraftItem.OpenFlag)
	{
		if (0 < pCursorPos.x && 256 + 128 > pCursorPos.x &&
			130 < pCursorPos.y && 130 + (22 * 10) > pCursorPos.y)
		{
			return TRUE;

		}

	}
	if (pItem->sItemInfo.CODE == (sinGF1 | sin01))return TRUE;



	if (cShop.OpenFlag)
	{





		int kk = 0;
		if (18 < pCursorPos.x && 18 + (22 * 10) > pCursorPos.x &&
			134 + sinInterHeight2 < pCursorPos.y && 134 + (22 * 10) + sinInterHeight2 > pCursorPos.y)
		{

			for (kk = 0; kk < NotSell_Item_CODECnt; kk++)
			{
				if (NotSell_Item_CODE[kk] == pItem->sItemInfo.CODE)return TRUE;

			}
			for (kk = 0; kk < NotSell_Item_MASKCnt; kk++)
			{
				if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == NotSell_Item_MASK[kk])return TRUE;

			}
			for (kk = 0; kk < NotSell_Item_KINDCnt; kk++)
			{
				if (NotSell_Item_KIND[kk] == pItem->sItemInfo.ItemKindCode)return TRUE;

			}

			if (pItem->Class == ITEM_CLASS_POTION)
			{
				return TRUE;
			}

			if (pItem->sItemInfo.ItemLocked)
			{
				cMessageBox.ShowMessage("Item vinculado n�o pode ser vendido.");
				return FALSE;
			}

			else
			{
				if (cShop.CheckHighRankItem(pItem))
				{
					CursorClass = 1;
					pItem->Flag = 0;
					ResetInvenItemCode();
					cMessageBox.ShowMessage3(MESSAGE_SELL_HIGHRANK_ITEM, pItem->sItemInfo.ItemName);

				}
				else cShop.SellItemToShop(pItem);
			}

		}
	}
	else
	{
		if (pItem->sItemInfo.SpecialItemFlag[0] == CHECK_COPY_ITEM ||
			pItem->sItemInfo.SpecialItemFlag[0] == CHECK_GIVE_ITEM ||
			pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA1 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinQW1 ||


			(pItem->sItemInfo.CODE == (sinDA1 | sin31)) ||
			(pItem->sItemInfo.CODE == (sinDA2 | sin31)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin32)) ||
			(pItem->sItemInfo.CODE == (sinDA2 | sin32)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinDA2 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin34)) || (pItem->sItemInfo.CODE == (sinDA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin35)) || (pItem->sItemInfo.CODE == (sinDA2 | sin35)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin36)) || (pItem->sItemInfo.CODE == (sinDA2 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin37)) || (pItem->sItemInfo.CODE == (sinDA2 | sin37)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin38)) || (pItem->sItemInfo.CODE == (sinDA2 | sin38)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin39)) || (pItem->sItemInfo.CODE == (sinDA2 | sin39)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin40)) || (pItem->sItemInfo.CODE == (sinDA2 | sin40)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin41)) || (pItem->sItemInfo.CODE == (sinDA2 | sin41)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin42)) || (pItem->sItemInfo.CODE == (sinDA2 | sin42)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin43)) || (pItem->sItemInfo.CODE == (sinDA2 | sin43)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin44)) || (pItem->sItemInfo.CODE == (sinDA2 | sin44)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin45)) || (pItem->sItemInfo.CODE == (sinDA2 | sin45)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin46)) || (pItem->sItemInfo.CODE == (sinDA2 | sin46)) ||

			(pItem->sItemInfo.CODE == (sinOR2 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin36)) ||
			(pItem->sItemInfo.CODE == (sinOA1 | sin37)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin33)) ||
			(pItem->sItemInfo.CODE == (sinDB1 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinOA2 | sin34)) ||
			(pItem->sItemInfo.CODE == (sinBI1 | sin84)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin54)) || (pItem->sItemInfo.CODE == (sinDA2 | sin54)) ||
			(pItem->sItemInfo.CODE == (sinDA1 | sin55)) || (pItem->sItemInfo.CODE == (sinDA2 | sin55)) ||
			(pItem->sItemInfo.CODE == (sinGF1 | sin07)) || (pItem->sItemInfo.CODE == (sinGF1 | sin08))
			)
		{
			return TRUE;

		}

	}


	if (cShop.OpenFlag)
		return TRUE;


	if (!pItem->Flag)return FALSE;
	if (OpenFlag)
	{


		if (pItem->y + pItem->h < (600) - 180)
		{

			if (pItem->Class == ITEM_CLASS_POTION)
			{
				if (pItem->sItemInfo.PotionCount == 1)
				{
					if (sinThrowItemToFeild(pItem))
					{
						sinPlaySound(pItem->SoundIndex);
						pItem->Flag = 0;
						ReFormPotionNum();
						return TRUE;
					}

				}
				if (pMessageItem)
				{
					if (GhostPotionCheckFlag)
					{
						if (sinThrowItemToFeild(pItem))
						{
							sinPlaySound(pItem->SoundIndex);
							pItem->Flag = 0;
							GhostPotionCheckFlag = 0;
							ReFormPotionNum();
							return TRUE;

						}

					}
					cMessageBox.ShowMessage2(MESSAGE_THROW_ITEM);
					pItem->Flag = 0;
					pMessageItem->Flag = 1;
					sInven[pMessageItem->ItemPosition - 1].ItemIndex = BackUpItemIndex;
					CheckOverlapItem(pMessageItem, BackUpItemIndex);
					ReSettingPotion();
					CheckWeight();
					ReFormPotionNum();
					if (pMessageItem->ItemPosition)
						sInven[pMessageItem->ItemPosition - 1].ItemIndex = PotionIndex;
					return TRUE;
				}
			}
			if (sinThrowItemToFeild(pItem))
			{
				sinPlaySound(pItem->SoundIndex);
				pItem->Flag = 0;
			}

		}
	}
	else
	{
		if (pItem->y + pItem->h < 540)
		{

			if (pItem->Class == ITEM_CLASS_POTION)
			{
				if (pItem->sItemInfo.PotionCount == 1)
				{
					if (sinThrowItemToFeild(pItem))
					{
						sinPlaySound(pItem->SoundIndex);
						pItem->Flag = 0;
						return TRUE;
					}
				}

				if (pMessageItem)
				{
					if (GhostPotionCheckFlag)
					{
						if (sinThrowItemToFeild(pItem))
						{
							sinPlaySound(pItem->SoundIndex);
							pItem->Flag = 0;
							GhostPotionCheckFlag = 0;
							ReFormPotionNum();
							return TRUE;
						}
					}
					cMessageBox.ShowMessage2(MESSAGE_THROW_ITEM);
					pItem->Flag = 0;
					pMessageItem->Flag = 1;
					sInven[pMessageItem->ItemPosition - 1].ItemIndex = BackUpItemIndex;
					CheckOverlapItem(pMessageItem, BackUpItemIndex);
					ReSettingPotion();
					CheckWeight();
					ReFormPotionNum();
					if (pMessageItem->ItemPosition)
						sInven[pMessageItem->ItemPosition - 1].ItemIndex = PotionIndex;
					return TRUE;
				}
			}
			if (sinThrowItemToFeild(pItem))
			{
				sinPlaySound(pItem->SoundIndex);
				pItem->Flag = 0;
			}

		}
	}
	return TRUE;
}


int cINVENTORY::CharOnlySetItem(sITEM *pItem)
{

	for (int i = 0; i < NUM_COSTUMES; i++)
	{
		if (strcmpi(saCostume[i].szItemCode, pItem->LastCategory) == 0 && strlen(saCostume[i].szItemCode) > 0)
		{
			if (saCostume[i].eCostumeClass != GetCharacterKind())
			{
				pItem->sItemInfo.NotUseFlag = 1;
				break;
			}
		}
	}
	

	if (sinChar->JOB_CODE == 7 || sinChar->JOB_CODE == 8 || sinChar->JOB_CODE == 10)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA1)
		{
			pItem->sItemInfo.NotUseFlag = 1;

		}
	}
	else
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinDA2 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinOM1)
		{
			pItem->sItemInfo.NotUseFlag = 1;

		}
	}

	if (sinChar->JOB_CODE == 9)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWA1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWH1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWT1 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWP1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWS1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWS2 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWM1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWN1)
		{
			pItem->sItemInfo.NotUseFlag = 1;
		}
	}

	if (sinChar->JOB_CODE == 10)
	{
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWA1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWC1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWH1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWT1 ||
			(pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWP1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWS1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWS2 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWM1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWD1)
		{
			pItem->sItemInfo.NotUseFlag = 1;
		}
	}

	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWD1 && sinChar->JOB_CODE != 9)
	{
		pItem->sItemInfo.NotUseFlag = 1;
	}

	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinWN1 && sinChar->JOB_CODE != 10)
	{
		pItem->sItemInfo.NotUseFlag = 1;
	}

	return TRUE;
}


int cINVENTORY::CheckRequireItem()
{
	int NotUseItemFlag = 0;
	int i;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].sItemInfo.Level > sinChar->Level)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.Strength > sinChar->Strength)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.Talent > sinChar->Talent)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.Spirit > sinChar->Spirit)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.Health > sinChar->Health)NotUseItemFlag = 1;
			if (InvenItem[i].sItemInfo.BattleLevel > CharBattleLevel)NotUseItemFlag = 1;
			if (DeleteEventItem_TimeOut(&InvenItem[i].sItemInfo) == TRUE) NotUseItemFlag = 1;
			if (NotUseItemFlag)
			{
				InvenItem[i].sItemInfo.NotUseFlag = 1;
				NotUseItemFlag = 0;
			}
			else
				InvenItem[i].sItemInfo.NotUseFlag = 0;
			CharOnlySetItem(&InvenItem[i]);
			if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinFO1)
			{
				int j = 0;
				for (j = 0; j < 14; j++)
				{
					if ((InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) == SheltomCode2[j] || (InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) == MagicSheltomCode[j])
					{
						break;
					}
				}
				if ((InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) < sin21)
				{
					if (sinChar->Level < ForceOrbUseLevel[j][0] ||
						sinChar->Level > ForceOrbUseLevel[j][1])
					{
						InvenItem[i].sItemInfo.NotUseFlag = 1;
						NotUseItemFlag = 0;

					}
					else
					{
						InvenItem[i].sItemInfo.NotUseFlag = 0;

					}
				}
				else if ((InvenItem[i].sItemInfo.CODE&sinITEM_MASK3) < sin35)
				{
					if (sinChar->Level < MagicForceOrbUseLevel[j][0] ||
						sinChar->Level > MagicForceOrbUseLevel[j][1])
					{
						InvenItem[i].sItemInfo.NotUseFlag = 1;
						NotUseItemFlag = 0;

					}
					else
					{
						InvenItem[i].sItemInfo.NotUseFlag = 0;

					}
				}
			}

		}

	}
	return TRUE;
}


int cINVENTORY::CheckRequireItemToSet(sITEM *pItem)
{
	int NotUseItemFlag = 0;

	if (pItem->sItemInfo.Level > sinChar->Level)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Strength > sinChar->Strength)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Talent > sinChar->Talent)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Spirit > sinChar->Spirit)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Health > sinChar->Health)NotUseItemFlag = 1;
	if (pItem->sItemInfo.BattleLevel > CharBattleLevel)NotUseItemFlag = 1;
	if (NotUseItemFlag)
	{
		pItem->sItemInfo.NotUseFlag = 1;
		NotUseItemFlag = 0;
	}
	else
	{
		pItem->sItemInfo.NotUseFlag = 0;


	}
	CharOnlySetItem(pItem);
	return TRUE;

}


int cINVENTORY::DrawInvenText()
{
	HDC	hdc = NULL;
	char strBuff[128];
	char strCoin[128] = { 0 };
	memset(strBuff, 0, sizeof(strBuff));
	
	//SelectObject(hdc, sinFont);
	
	SetFontTextColor( RGB(255, 255, 255));

	POINT NoImageMessagePosi = { 0,0 };
	int i = 0;

	if (OpenFlag)
	{
		NumLineComa(sinChar->Money, strBuff);
		dsTextLineOut(0, CheckEditSize(InvenTextPosi[0][0] + 26, InvenTextPosi[0][2], strBuff), InvenTextPosi[0][1] + (250 - sinMoveKindInter[SIN_INVENTORY]),
			strBuff, lstrlen(strBuff));

	NumLineComa(cCoinShop.Coin, strCoin);
		wsprintf(strBuff,  "%s Coins", strCoin);
		dsTextLineOut(0,390, 495, strBuff, lstrlen(strBuff));
		
		wsprintf(strBuff, "%d/%d", sinChar->Weight[0], sinChar->Weight[1]);	
		dsTextLineOut(0, CheckEditSize(InvenTextPosi[1][0], InvenTextPosi[1][2], strBuff), InvenTextPosi[1][1] + (250 - sinMoveKindInter[SIN_INVENTORY]),
			strBuff, lstrlen(strBuff));
	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{

			if (!InvenItem[i].lpItem)
			{
				if (InvenItem[i].x > 10)
				{
					NoImageMessagePosi.x = InvenItem[i].x + (InvenItem[i].w / 2) - 5;
					NoImageMessagePosi.y = InvenItem[i].y + (InvenItem[i].h / 2) - 20;
					strcpy_s(strBuff, "NO");
					dsTextLineOut(0, NoImageMessagePosi.x, NoImageMessagePosi.y + (250 - sinMoveKindInter[SIN_INVENTORY]), strBuff, lstrlen(strBuff));

					NoImageMessagePosi.x = InvenItem[i].x + (InvenItem[i].w / 2) - 15;
					NoImageMessagePosi.y = InvenItem[i].y + (InvenItem[i].h / 2) - 13;
					strcpy_s(strBuff, "IMAGE");
					dsTextLineOut(0, NoImageMessagePosi.x, NoImageMessagePosi.y + (250 - sinMoveKindInter[SIN_INVENTORY]) + 20, strBuff, lstrlen(strBuff));
				}
			}
			if (InvenItem[i].Class == ITEM_CLASS_POTION)
			{
				wsprintf(strBuff, "%d", InvenItem[i].sItemInfo.PotionCount);
				if (InvenItem[i].ItemPosition == 11 || InvenItem[i].ItemPosition == 12 || InvenItem[i].ItemPosition == 13)
				{
					dsTextLineOut(0, InvenItem[i].x, InvenItem[i].y, strBuff, lstrlen(strBuff));
				}
				else
				{
					if (OpenFlag)
						dsTextLineOut(0, InvenItem[i].x, InvenItem[i].y + (250 - sinMoveKindInter[SIN_INVENTORY]) + 5, strBuff, lstrlen(strBuff));
				}
			}
		}
	}


	int BackUpPosX = 0;
	int BackUpPosY = 0;
	int Start = 0, End = 0, Conut = 0;
	char szBuff2[128];



	if (nName == 1)
	{






		//SelectObject(hdc, sinBoldFont);
		
		SetFontTextColor( RGB(65, 177, 240));
		dsTextLineOut(0, BackStartPos.x + 60, BackStartPos.y, "Name", lstrlen("Name"));


		SetIME_Mode(1);
		hFocusWnd = hTextWnd;
		cInterFace.ChatFlag = 0;
		sinChatEnter = 0;
		sinMessageBoxShowFlag = 1;

		hFocusWnd = hTextWnd;
		GetWindowText(hFocusWnd, cInvenTory.szDoc, 20);


		//SelectObject(hdc, sinFont);
		
		SetFontTextColor( RGB(255, 255, 255));


		int len = 0;
		int line = 1;
		len = lstrlen(cInvenTory.szDoc);

		line += (len / 20);

		for (int i = 0; i < len; i++)
		{
			memset(szBuff2, 0, sizeof(szBuff2));
			while (1)
			{
				if (cInvenTory.szDoc[End] == NULL)break;
				if (cInvenTory.szDoc[End] & 0x80)
				{
					End += 2;
					Conut += 2;
				}
				else
				{
					End++;
					Conut++;
				}
				if (Conut > 20)break;
			}
			memcpy(szBuff2, &cInvenTory.szDoc[Start], End - Start);

			dsTextLineOut(0, BackStartPos.x + 32, BackStartPos.y + (i * 20) - 110, szBuff2, lstrlen(szBuff2));

			if (cInvenTory.szDoc[End] != NULL)
			{
				if (cInvenTory.szDoc[End] == ' ')
					End += 1;
				Start = End;
				Conut = 0;

			}
			else break;
		}


	}







	

	return TRUE;
}


int cINVENTORY::SearchJobAndSetting()
{
	int cnt;

	JobName[0] = 0;

	cnt = 0;


	while (1)
	{
		if (JobDataBase[cnt].JobCode == 0) break;
		if (JobDataBase[cnt].JobCode == sinChar->JOB_CODE)
		{
			sinJobList = GetJobDataCode(sinChar->JOB_CODE, sinChar->ChangeJob);
			strcpy_s(JobName, sinJobList->szName2);
			sinChar->JobBitMask = JobDataBase[cnt].JobBitCode;
			sinChar->LifeFunction = JobDataBase[cnt].LifeFunction;
			sinChar->ManaFunction = JobDataBase[cnt].ManaFunction;
			sinChar->StaminaFunction = JobDataBase[cnt].StaminaFunction;
			sinDamageFunction[0] = JobDataBase[cnt].DamageFunction[0];
			sinDamageFunction[1] = JobDataBase[cnt].DamageFunction[1];
			sinDamageFunction[2] = JobDataBase[cnt].DamageFunction[2];

			break;
		}
		cnt++;
	}
	return TRUE;

}
extern BOOL bReiPVP;

int cINVENTORY::SetItemToChar(int CheckHackFlag)
{


	memset(&sElement_Attack, 0, sizeof(sELEMENT_ATTACK));
	CheckCharForm();

	sinTempDamage2[0] = 0;
	sinTempDamage2[1] = 0;

	int cnt = 0;
	int sinAttack_Rating = 0;
	int sinAttack_Damage[2] = { 0,0 };
	int sinCritical = 0;
	int sinDefense = 0;
	float sinAbsorption = 0;
	int   sinTempAbsorption = 0;
	float sinTempAbsorption2 = 0;
	float sinBlock_Rate = 0;
	int sinWeight = 0;
	float sinMoveSpeed = 0;
	int sinWeaponSpeed = 0;
	int sinShooting_Range = 0;
	int sinSight = 0;
	int sinResistance[8] = { 0,0,0,0,0,0,0,0 };
	int sinPotion_Space = 2;
	int sinSkillMasteryItem = 0;


	int sinSkillDamage[2] = { 0,0 };
	int sinSkillResistance[8] = { 0,0,0,0,0,0,0,0 };
	int sinSkillWeaponSpeed = 0;


	int sinCharItemDamage = 0;


	float	sinAdd_fAbsorb = 0;
	int     sinAdd_Defence = 0;
	float   sinAdd_fSpeed = 0;
	float   sinAdd_fBlock_Rating = 0;
	int     sinAdd_Attack_Speed = 0;
	int     sinAdd_Critical_Hit = 0;
	int     sinAdd_Shooting_Range = 0;
	short	sinAdd_Resistance[8] = { 0,0,0,0,0,0,0,0 };



	short	sinLev_Attack_Resistance[8] = { 0,0,0,0,0,0,0,0 };
	int		sinLev_Mana = 0;
	int		sinLev_Life = 0;
	int     sinLev_Attack_Rating = 0;
	short	sinLev_Damage[2] = { 0,0 };

	float	sinPer_Mana_Regen = 0;
	float	sinPer_Life_Regen = 0;
	float 	sinPer_Stamina_Regen = 0;

	float fstrength, fhealth, ftalent, fLevel, fMaxWeight, fNowWeight, fSpirit, fDexterity;
	float fAttack_Rating, fDefense;


	sinAdd_fMagic_Mastery = 0;

	int vlLife = 0;
	int boosterLife = 0;

	float sinfIncreLife = 0;
	float sinfIncreMana = 0;
	float sinfIncreStamina = 0;

	float sinfRegenLife = 0;
	float sinfRegenMana = 0;
	float sinfRegenStamina = 0;



	sinUndeadAbsorb = 0;


	int InvenCheckItem[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	sITEM sinTempItem;
	memset(&sinTempItem, 0, sizeof(sITEM));

	int CountAbsorbItem = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].ItemPosition)
			{
				if (InvenItem[i].sItemInfo.CODE > sinPM1)continue;
				if (InvenItem[i].sItemInfo.NotUseFlag)continue;


				if (!CheckRequireItemToSet2(&InvenItem[i]))continue;

				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO || InvenItem[i].Class == ITEM_CLASS_WING)
					if (InvenItem[i].sItemInfo.ItemHeader.dwChkSum == 0)continue;

				if (!InvenCheckItem[InvenItem[i].ItemPosition])
				{
					InvenCheckItem[InvenItem[i].ItemPosition] = i + 1;
				}
				else
					continue;


				if (!CheckItemForm(&InvenItem[i].sItemInfo))
				{
					SendSetHackUser(1);
					InvenItem[i].Flag = 0;
					if (InvenItem[i].ItemPosition)
					{
						sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;
						sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

					}
					if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
					{
						InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
						sInven[1].ItemIndex = 0;
					}
					else if (InvenItem[i].Class == ITEM_CLASS_WING)
					{
						InvenItem[sInven[15].ItemIndex - 1].Flag = 0;
						sInven[15].ItemIndex = 0;
					}
					continue;
				}


				sinAttack_Rating += InvenItem[i].sItemInfo.Attack_Rating;
				sinAttack_Damage[0] += InvenItem[i].sItemInfo.Damage[0];
				sinAttack_Damage[1] += InvenItem[i].sItemInfo.Damage[1];
				sinCritical += InvenItem[i].sItemInfo.Critical_Hit;
				sinDefense += InvenItem[i].sItemInfo.Defence;

				sinTempAbsorption = (int)(GetItemAbsorb(&InvenItem[i].sItemInfo)*10.000001f);
				sinTempAbsorption2 = ((float)sinTempAbsorption / 10.0f);
				sinTempAbsorption2 += 0.000001f;

				if (InvenItem[i].sItemInfo.fAbsorb)
				{
					CountAbsorbItem++;

				}

				sinAbsorption += sinTempAbsorption2;


				sinBlock_Rate += InvenItem[i].sItemInfo.fBlock_Rating;
				sinMoveSpeed += InvenItem[i].sItemInfo.fSpeed;


				if (CheckQuestItemDownFlag && InvenItem[i].sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON)
				{
					sinWeaponSpeed += InvenItem[i].sItemInfo.Attack_Speed - 2;
				}
				else
					sinWeaponSpeed += InvenItem[i].sItemInfo.Attack_Speed;

				sinShooting_Range += InvenItem[i].sItemInfo.Shooting_Range;
				sinSight += InvenItem[i].sItemInfo.Sight;
				sinfRegenLife += InvenItem[i].sItemInfo.fLife_Regen;
				sinfRegenMana += InvenItem[i].sItemInfo.fMana_Regen;
				sinfRegenStamina += InvenItem[i].sItemInfo.fStamina_Regen;
				sinAdd_fMagic_Mastery = InvenItem[i].sItemInfo.fMagic_Mastery;

				sinfIncreLife += InvenItem[i].sItemInfo.fIncrease_Life;
				sinfIncreMana += InvenItem[i].sItemInfo.fIncrease_Mana;
				sinfIncreStamina += InvenItem[i].sItemInfo.fIncrease_Stamina;
				if (InvenItem[i].sItemInfo.Potion_Space)
				{

					if (DeleteEventItem_TimeOut(&InvenItem[i].sItemInfo) == TRUE)
					{
						sinPotion_Space = 2;
					}
					else
						sinPotion_Space = InvenItem[i].sItemInfo.Potion_Space;
				}

				if (sinChar->JobBitMask & InvenItem[i].sItemInfo.JobCodeMask)
				{
					sinTempAbsorption = (int)(InvenItem[i].sItemInfo.JobItem.Add_fAbsorb*10.000001f);
					sinTempAbsorption2 = ((float)sinTempAbsorption / 10.0f);
					sinTempAbsorption2 += 0.000001f;
					sinAdd_fAbsorb += sinTempAbsorption2;

					if (InvenItem[i].sItemInfo.JobItem.Add_fAbsorb)
					{
						CountAbsorbItem++;

					}


					sinAdd_Defence += InvenItem[i].sItemInfo.JobItem.Add_Defence;
					sinAdd_fSpeed += InvenItem[i].sItemInfo.JobItem.Add_fSpeed;
					sinAdd_fBlock_Rating += InvenItem[i].sItemInfo.JobItem.Add_fBlock_Rating;
					sinAdd_Attack_Speed += InvenItem[i].sItemInfo.JobItem.Add_Attack_Speed;
					sinAdd_Critical_Hit += InvenItem[i].sItemInfo.JobItem.Add_Critical_Hit;
					sinAdd_Shooting_Range += InvenItem[i].sItemInfo.JobItem.Add_Shooting_Range;
					sinAdd_fMagic_Mastery += InvenItem[i].sItemInfo.JobItem.Add_fMagic_Mastery;

					if (InvenItem[i].sItemInfo.JobItem.Lev_Mana)
						sinLev_Mana += (sinChar->Level / InvenItem[i].sItemInfo.JobItem.Lev_Mana);
					if (InvenItem[i].sItemInfo.JobItem.Lev_Life)
						sinLev_Life += (sinChar->Level / InvenItem[i].sItemInfo.JobItem.Lev_Life);
					if (InvenItem[i].sItemInfo.JobItem.Lev_Attack_Rating)
						sinLev_Attack_Rating += (sinChar->Level / InvenItem[i].sItemInfo.JobItem.Lev_Attack_Rating);


					if (InvenItem[i].sItemInfo.JobItem.Lev_Damage[1])
						sinLev_Damage[1] += (sinChar->Level / InvenItem[i].sItemInfo.JobItem.Lev_Damage[1]);
					if (InvenItem[i].sItemInfo.JobItem.Per_Mana_Regen)
						sinPer_Mana_Regen += (InvenItem[i].sItemInfo.JobItem.Per_Mana_Regen / 2.0f);
					if (InvenItem[i].sItemInfo.JobItem.Per_Life_Regen)
						sinPer_Life_Regen += (InvenItem[i].sItemInfo.JobItem.Per_Life_Regen / 2.0f);
					if (InvenItem[i].sItemInfo.JobItem.Per_Stamina_Regen)
						sinPer_Stamina_Regen += (InvenItem[i].sItemInfo.JobItem.Per_Stamina_Regen / 2.0f);

					for (int t = 0; t < 8; t++)
					{
						sinAdd_Resistance[t] += (int)InvenItem[i].sItemInfo.JobItem.Add_Resistance[t];
						if (InvenItem[i].sItemInfo.JobItem.Lev_Attack_Resistance[t])
							sinLev_Attack_Resistance[t] += (int)InvenItem[i].sItemInfo.JobItem.Lev_Attack_Resistance[t] +
							(sinChar->Level / InvenItem[i].sItemInfo.JobItem.Lev_Attack_Resistance[t]);

					}
				}
				for (int j = 0; j < 8; j++)
					sinResistance[j] += (int)InvenItem[i].sItemInfo.Resistance[j];

			}

		}
	}



	float TempSkillData = 0;
	float TempDamage[2] = { 0,0 };
	int   TempAttack_Rating = 0;
	int   TempDefense = 0;
	int   TempDefense2 = 0;
	int   TempWeaponSpeed = 0;
	float TempCritical = 0;

	if (sInven[0].ItemIndex)
	{
		float TempDamage2[2] = { (float)cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[0], (float)cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Damage[1] };
		TempAttack_Rating = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Attack_Rating;
		memcpy(TempDamage, TempDamage2, sizeof(float) * 2);
		TempWeaponSpeed = cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Attack_Speed;
		if (sinChar->JobBitMask & cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.JobCodeMask)
		{
			TempWeaponSpeed += cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.JobItem.Add_Attack_Speed;

		}
		TempCritical = (float)cInvenTory.InvenItem[sInven[0].ItemIndex - 1].sItemInfo.Critical_Hit;


	}


	int MetalArmor = 0;
	if (sInven[2].ItemIndex)
	{
		TempDefense = cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItemInfo.Defence;
		if (sinChar->JobBitMask & cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItemInfo.JobCodeMask)
		{
			TempDefense += cInvenTory.InvenItem[sInven[2].ItemIndex - 1].sItemInfo.JobItem.Add_Defence;
			MetalArmor = 1;

		}

	}

	if (sInven[1].ItemIndex)
	{
		TempDefense2 = cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.Defence;
		if (sinChar->JobBitMask & cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.JobCodeMask)
		{
			TempDefense2 += cInvenTory.InvenItem[sInven[1].ItemIndex - 1].sItemInfo.JobItem.Add_Defence;


		}

	}

	//Set Boss #1
	if (cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItemInfo.CODE == (sinOR2 | sin05)) {
		LValRing = 1;
	}
	else { LValRing = 0; }
	if (cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItemInfo.CODE == (sinOR2 | sin05)) {
		RValRing = 1;
	}
	else { RValRing = 0; }
	if (cInvenTory.InvenItem[sInven[3].ItemIndex - 1].sItemInfo.CODE == (sinOA1 | sin30)) {
		KelAmulet = 1;
	}
	else { KelAmulet = 0; }

	//Set Boss #2
	if (cInvenTory.InvenItem[sInven[4].ItemIndex - 1].sItemInfo.CODE == (sinOR2 | sin48)) {
		LShyRing = 1;
	}
	else { LShyRing = 0; }
	if (cInvenTory.InvenItem[sInven[5].ItemIndex - 1].sItemInfo.CODE == (sinOR2 | sin48)) {
		RShyRing = 1;
	}
	else { RShyRing = 0; }
	if (cInvenTory.InvenItem[sInven[3].ItemIndex - 1].sItemInfo.CODE == (sinOA1 | sin44)) {
		TullaAmulet = 1;
	}
	else { TullaAmulet = 0; }

	SetBonus1 = (LValRing + RValRing + KelAmulet);//Set Boss #1
	SetBonus2 = (LShyRing + RShyRing + TullaAmulet);//Set Boss #2
	float BonusHP1 = SetBoss1Bonus2 + 0.f;
	float BonusHP2 = SetBoss2Bonus2 + 0.f;
	//Bonus #1
	if (SetBonus1 >= 2)
	{

		sinAdd_Defence += SetBoss1Bonus1;

	}
	if (SetBonus1 >= 3)
	{
		sinfIncreLife += BonusHP1;
		SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
	}

	//Bonus #2
	if (SetBonus2 >= 2)
	{
		sinAdd_Defence += SetBoss2Bonus1;
	}
	//Bonus #2
	if (SetBonus2 >= 3)
	{
		sinfIncreLife += BonusHP2;
		SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
	}

	int sinSkillTimeDamage[2] = { 0,0 };
	sinTempBlock = 0;
	sinTempAbsorb = 0;

	int Count2 = 0;
	int Point2 = 0;
	int p = 0;
	int Flag3 = 0;
	int Flag4 = 0;


	SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_WHITE;


	for (int i = 0; i < 10; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
			case SKILL_EXTREME_SHIELD:
				sinTempBlock += ContinueSkill[i].PlusState[0];

				break;
			case SKILL_PHYSICAL_ABSORB:

				sinTempAbsorb += ContinueSkill[i].PlusState[0];
				break;
			case SKILL_AUTOMATION:
				if (sinWS1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2) ||
					sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
				{

					sinTempDamage2[0] += (int)(((float)Automation_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[0]);
					sinTempDamage2[1] += (int)(((float)Automation_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[1]);
					sinSkillWeaponSpeed += ContinueSkill[i].PlusState[0];
					SendProcessSKillToServer(SKILL_PLAY_AUTOMATION, ContinueSkill[i].Point, 0, 0);
				}
				else
					SendCancelSkillToServer(SKILL_PLAY_AUTOMATION, ContinueSkill[i].Point, 0, 0);

				break;
			case SKILL_MAXIMIZE:
				SendProcessSKillToServer(SKILL_PLAY_MAXIMIZE, ContinueSkill[i].Point, 0, 0);
				sinTempDamage2[1] += (int)(((float)ContinueSkill[i].PlusState[0] / 100.0f)*TempDamage[1]);

				break;
			case SKILL_WINDY:
				if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
				{
					sinAttack_Rating += (Windy_Attack_Rating[ContinueSkill[i].Point - 1] * TempAttack_Rating) / 100;
					sinShooting_Range += 30;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;

				}
				else
				{
					ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
				}
				break;
			case SKILL_METAL_ARMOR:
				if (MetalArmor)
				{

					sinDefense += (Metal_Armor_Defense[ContinueSkill[i].Point - 1] * (TempDefense)) / 100;
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;

					Point2 = cSkill.GetSkillPoint(SKILL_PHYSICAL_ABSORB);
					if (Point2)
					{
						sinTempAbsorb += (int)(((P_Absorb[Point2 - 1][0] + P_Absorb[Point2 - 1][1])*1.2f) / 2);
					}
				}
				break;
			case SKILL_SPARK_SHIELD:
				if (sInven[1].ItemIndex)
				{
					if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE&sinITEM_MASK2))
					{
						sinDefense += Spark_Shield_Defense[ContinueSkill[i].Point - 1];
					}
				}
				break;
			case SKILL_SWIFT_AXE:
				if (sInven[0].ItemIndex)
				{
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
					{
						sinSkillWeaponSpeed += (int)((Swift_Axe_Speed[ContinueSkill[i].Point - 1] * TempWeaponSpeed) / 100);
						Flag4 = 1;
					}
				}




				break;

			case SKILL_A_MIDRANDA:
				if (sInven[0].ItemIndex)
				{
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[0] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
					{
						sinSkillWeaponSpeed += (int)((AdventMidranda_Speed[ContinueSkill[i].Point - 1] * TempWeaponSpeed) / 100);
						Flag4 = 1;
					}
				}
				break;

			case SKILL_TRIUMPH_OF_VALHALLA:

				sinTempDamage2[1] += (T_Of_Valhalla_Damage[ContinueSkill[i].Point - 1] + (SetT_Of_ValhallaLV / 4)) / (SetT_Of_ValhallaFlag + 1);
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
			case SKILL_SPIRIT_ELEMENTAL:
				sinfRegenMana += Spirit_Elemental_RegenMana[ContinueSkill[i].Point - 1];
				/*sinTempDamage2[0] += (int)(((float)Spirit_Elemental_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[0]);
				sinTempDamage2[1] += (int)(((float)Spirit_Elemental_Damage[ContinueSkill[i].Point - 1] / 100)*TempDamage[1]);
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;*/
				break;
			case SKILL_GOLDEN_FALCON:
				sinfRegenLife += Golden_Falcon_LifeRegen[ContinueSkill[i].Point - 1];
				break;
			case SKILL_VIRTUAL_LIFE:
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_PINK;
				break;
			case SKILL_DIVINE_INHALATION:
				sinTempBlock += D_Inhalation_Block[ContinueSkill[i].Point - 1];
				break;
			case SKILL_MAGNETIC_SPHERE:

				break;
			case SKILL_BERSERKER:
				sinTempDamage2[0] += Berserker_AddAttack[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += Berserker_AddAttack[ContinueSkill[i].Point - 1];
				sinTempAbsorb += Berserker_SubAbsorb[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
				break;
			case SKILL_ASSASSIN_EYE:

				break;
			case SKILL_FORCE_OF_NATURE:
				sinTempDamage2[0] += Force_Of_Nature_AddDamage[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinTempDamage2[1] += Force_Of_Nature_AddDamage[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinAttack_Rating += Force_Of_Nature_AddHit[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
				break;

			case SKILL_GODLY_SHIELD:
				if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE &sinITEM_MASK2))
					SendProcessSKillToServer(SKILL_PLAY_GODLY_SHIELD, ContinueSkill[i].Point, 0, 0);
				else
					SendCancelSkillToServer(SKILL_PLAY_GODLY_SHIELD, ContinueSkill[i].Point, 0, 0);
				break;

			case SKILL_GOD_BLESS:
				sinTempDamage2[0] += God_Bless_AddDamage[ContinueSkill[i].Point - 1];
				sinTempDamage2[1] += God_Bless_AddDamage[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
			case SKILL_HALL_OF_VALHALLA:
				if (SetT_Of_ValhallaPOINT)
				{
					sinTempDamage2[1] += (T_Of_Valhalla_Damage[SetT_Of_ValhallaPOINT - 1] + (SetH_Of_ValhallaLV / 4)) / ContinueSkill[i].Flag;
					SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				}
				break;
			case SKILL_COMPULSION:
				sinTempAbsorb += Compulsion_AddAbsorb[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_R_MAKER:
				sinTempAbsorb += RainMaker_Absorb[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_FROST_JAVELIN:
				if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
				{
					sinTempDamage2[0] += Frost_Javelin_IceAddDamage[ContinueSkill[i].Point - 1][0];
					sinTempDamage2[1] += Frost_Javelin_IceAddDamage[ContinueSkill[i].Point - 1][1];
				}
				else
				{
					ContinueSkill[i].CheckTime = ContinueSkill[i].UseTime * 70;
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
					SendCancelSkillToServer(SKILL_PLAY_FROST_JAVELIN, 0, 0, 0);
				}
				break;
			case CLANSKILL_ABSORB:
				sinTempAbsorb += 20;
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
				break;
			case SCROLL_INVULNERABILITY:
			case SCROLL_P_INVULNERABILITY:
				sinTempDamage2[0] -= (sinChar->Attack_Damage[0] * 100);
				sinTempDamage2[1] -= (sinChar->Attack_Damage[1] * 100);
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;
				break;

			case SOD_SKILL_GOLD:
				sinfIncreLife += 100.0f;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;

			case SOD_SKILL_SILVER:
				sinfIncreLife += 60.0f;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;

			case SOD_SKILL_BRONZE:
				sinfIncreLife += 30.0f;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;
			/*case PLAYER_TOP:
				sinfIncreLife += 30.0f;			

				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;*/

			case REIPVP:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 5) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 5) / 100;
				//sinfIncreLife += 150.0f;

				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				break;

			case HIGH_LEVEL_MERIT_SKILL:
				sinfIncreLife += 30.0f;
				sinfIncreMana += 30.0f;
				sinfIncreStamina += 30.0f;
				//sinAdd_Attack_Speed += 1;
				

				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_GOLD;
				break;

			case PLAYER_VIP:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * IsVIP.atk) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * IsVIP.atk) / 100;
				sinfIncreLife += lpCurPlayer->smCharInfo.Life[1] * IsVIP.hp / 100;
				sinfIncreMana += lpCurPlayer->smCharInfo.Mana[1] * IsVIP.mp / 100;
				sinfIncreStamina += lpCurPlayer->smCharInfo.Stamina[1] * IsVIP.res / 100;

				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_GOLD;
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_GOLD;
				break;

			/*case PLAYER_ARENA:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 5) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 5) / 100;

				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;*/

			case ELIXIR_IRA:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 3) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 3) / 100;

				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;

			case ELIXIR_GLORIA:
				sinfIncreLife += 150.0f;
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_PINK;

				break;

			

			case BOOSTER_ITEM_LIFE:
				SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_PINK;

				if (AddBoosterLife)
				{
					if (!LifeFlag)
					{
						tempLife[0] = ((sinChar->Life[1] + AddVirtualLife[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						LifeFlag = 1;
					}
					else if (sinChar->Level != tempLife[1])
					{
						tempLife[0] = ((sinChar->Life[1] + AddVirtualLife[0] - tempLife[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempLife[1] = sinChar->Level;
					}
					else if (!AddVirtualLife[1] && LifeFlag == 1)
					{
						sinChar->Life[1] -= tempLife[0];
						tempLife[0] = (sinChar->Life[1] * (short)BoosterItem_DataPercent[0]) / 100;
					}

					sinfIncreLife = sinfIncreLife + tempLife[0];

				}
				else
					tempLife[0] = 0;

				break;


			case BOOSTER_ITEM_MANA:
				SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_PINK;

				if (AddVirtualMana[1])
				{
					if (!ManaFlag)
					{
						tempMana[0] = (sinChar->Mana[1] * (short)BoosterItem_DataPercent[0]) / 100;
						ManaFlag = 1;
					}
					else if (sinChar->Level != tempMana[1])
					{
						tempMana[0] = ((sinChar->Mana[1] - tempMana[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempMana[1] = sinChar->Level;
					}

					sinfIncreMana = sinfIncreMana + tempMana[0];
				}
				else
					tempMana[0] = 0;

				break;
			case BOOSTER_ITEM_STAMINA:
				SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_PINK;

				if (AddVirtualStamina[1])
				{
					if (!StaminaFlag)
					{
						tempStamina[0] = (sinChar->Stamina[1] * (short)BoosterItem_DataPercent[0]) / 100;
						StaminaFlag = 1;
					}
					else if (sinChar->Level != tempStamina[1])
					{
						tempStamina[0] = ((sinChar->Stamina[1] - tempStamina[0]) * (short)BoosterItem_DataPercent[0]) / 100;
						tempStamina[1] = sinChar->Level;
					}

					sinfIncreStamina = sinfIncreStamina + tempStamina[0];

				}
				else
					tempStamina[0] = 0;

				break;

			}
		}
	}

	if (chaPremiumitem.m_BigHeadTime > 0)
	{
		sinTempDamage2[0] += (sinChar->Attack_Damage[0] * 10) / 100;
		sinTempDamage2[1] += (sinChar->Attack_Damage[1] * 10) / 100;
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_BLUE;
	}

	if (chaPremiumitem.m_ForceTime > 0)
	{
		switch (chaPremiumitem.m_ForceType)
		{
		case 1:
			sinTempDamage2[0] += 2;
			sinTempDamage2[1] += 2;
			break;

		case 2:
			sinTempDamage2[0] += 4;
			sinTempDamage2[1] += 4;
			break;

		case 3:
			sinTempDamage2[0] += 7;
			sinTempDamage2[1] += 7;
			break;

		case 4:
			sinTempDamage2[0] += 10;
			sinTempDamage2[1] += 10;
			break;

		case 5:
			sinTempDamage2[0] += 15;
			sinTempDamage2[1] += 15;
			break;

		case 6:
			sinTempDamage2[0] += 25;
			sinTempDamage2[1] += 25;
			break;

		case 7:
			sinTempDamage2[0] += 40;
			sinTempDamage2[1] += 40;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 10) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 10) / 100;
			break;

		case 8:
			sinTempDamage2[0] += 60;
			sinTempDamage2[1] += 60;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 10) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 10) / 100;
			break;

		case 9:
			sinTempDamage2[0] += 80;
			sinTempDamage2[1] += 80;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 10) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 10) / 100;
			break;

		case 10:
			sinTempDamage2[0] += 100;
			sinTempDamage2[1] += 100;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 10) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 10) / 100;
			break;

		case 11:
			sinTempDamage2[0] += 120;
			sinTempDamage2[1] += 120;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 15) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 15) / 100;
			break;

		case 12:
			sinTempDamage2[0] += 140;
			sinTempDamage2[1] += 140;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 15) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 15) / 100;
			break;

		case 13:
			sinTempDamage2[0] += 160;
			sinTempDamage2[1] += 160;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 15) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 15) / 100;
			break;

		case 14:
			sinTempDamage2[0] += 180;
			sinTempDamage2[1] += 180;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 15) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 15) / 100;
			break;

		case 15:
			sinTempDamage2[0] += 180;
			sinTempDamage2[1] += 180;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 20) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 20) / 100;
			break;

		case 16:
			sinTempDamage2[0] += 200;
			sinTempDamage2[1] += 200;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 22) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 22) / 100;
			break;

		case 17:
			sinTempDamage2[0] += 220;
			sinTempDamage2[1] += 220;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 24) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 24) / 100;
			break;

		case 18:
			sinTempDamage2[0] += 240;
			sinTempDamage2[1] += 240;
			sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 26) / 100;
			sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 26) / 100;
			break;
		}
		AssaParticle_ShelltomWeapon(lpCurPlayer, (DWORD)60 * 60 * 1 * 1000, chaPremiumitem.m_ForceType);
	}


	for (int i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{
			switch (sinSkill.UseSkill[i].CODE)
			{
			case SKILL_POISON_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_POISON] = PlusPoison[sinSkill.UseSkill[i].Point - 1];

				break;
			case SKILL_ICE_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_ICE] = PlusIce[sinSkill.UseSkill[i].Point - 1];

				break;
			case SKILL_FIRE_ATTRIBUTE:
				sinSkillResistance[sITEMINFO_FIRE] = PlusFire[sinSkill.UseSkill[i].Point - 1];

				break;
			}
		}
	}


	int TempDivide = 1;
	for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
			case SKILL_ZENITH:
				if (ContinueSkill[i].PartyFlag)TempDivide = 2;
				sinSkillResistance[sITEMINFO_BIONIC] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_FIRE] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_ICE] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_LIGHTING] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				sinSkillResistance[sITEMINFO_POISON] += Zenith_Element[ContinueSkill[i].Point - 1] / TempDivide;
				break;
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		sinChar->Resistance[i] = sinResistance[i] + sinAdd_Resistance[i] + sinSkillResistance[i];

	}


	for (int i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{





			for (cnt = 0; cnt < 8; cnt++)
			{
				switch (sinSkill.UseSkill[i].CODE)
				{
				case SKILL_MELEE_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_SHOOTING_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);

						}
					}
					break;
				case SKILL_WEAPONE_DEFENCE_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							if (sInven[1].ItemIndex)
								if (sinDS1 == (cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE&sinITEM_MASK2))
									break;

							sinBlock_Rate += W_D_Mastery_Block[sinSkill.UseSkill[i].Point - 1];

						}
					}
					break;
				case SKILL_DIONS_EYE:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
							sinAttack_Rating += (D_Eye_Attack_Rate[sinSkill.UseSkill[i].Point - 1] * TempAttack_Rating) / 100;
					}

					break;

				case SKILL_THROWING_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}
					}
					break;
				case SKILL_MECHANIC_WEAPON:
					if (sInven[0].ItemIndex)
					{
						if (sinChar->JobBitMask & InvenItem[sInven[0].ItemIndex - 1].sItemInfo.JobCodeMask)
						{
							sinSkillDamage[0] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}

						if (InvenItem[sInven[0].ItemIndex - 1].sItemInfo.UniqueItem == 2)
						{
							sinSkillDamage[0] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)M_Weapon_Mastey[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);
						}

					}
					break;
				case SKILL_CRITICAL_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinCritical += Critical_Mastery_Critical[sinSkill.UseSkill[i].Point - 1];

						}
					}
					break;
				case SKILL_SWORD_MASTERY:
					if (sInven[0].ItemIndex)
					{
						if (sinSkill.UseSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinSkillDamage[0] = (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[0]);
							sinSkillDamage[1] = (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[i].Point - 1] / 100)*TempDamage[1]);

						}
					}
					break;
				case SKILL_EVASION_MASTERY:


					break;
				}
			}
		}
	}

	//Dano Char
	switch (sinChar->JOB_CODE)
	{
	case JOBCODE_FIGHTER:
		if (sinWA1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_MECHANICIAN:
		if (sInven[0].ItemIndex)
		{
			if (sinChar->JobBitMask & InvenItem[sInven[0].ItemIndex - 1].sItemInfo.JobCodeMask)
				sinCharItemDamage = sinChar->Level / 6;

			if (InvenItem[sInven[0].ItemIndex - 1].sItemInfo.UniqueItem == 2)
				sinCharItemDamage = sinChar->Level / 6;
		}
		break;

	case JOBCODE_ARCHER:
		if (sinWS1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_PIKEMAN:
		if (sinWP1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_KNIGHT:
		if (sinWS2 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_ATALANTA:
		if (sinWT1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_PRIESTESS:
		if (sinWM1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;

	case JOBCODE_MAGICIAN:
		if (sinWM1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;
	case JOBCODE_ASSASSINE:
		if (sinWD1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;
	case JOBCODE_SHAMAN:
		if (sinWN1 == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
			sinCharItemDamage = sinChar->Level / 6;
		break;
	

	}
	int TempChangeDamageFlag = 0;
	int TempChangeAbsorbFlag = 0;

	for (int i = 0; i < 10; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			for (cnt = 0; cnt < 8; cnt++)
			{
				switch (ContinueSkill[i].CODE)
				{
				case SKILL_AUTOMATION:
				case SKILL_MAXIMIZE:
					if (ContinueSkill[i].Skill_Info.UseWeaponCode[cnt] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
					{
						TempChangeDamageFlag = 1;
					}
					break;
				case SKILL_METAL_ARMOR:
					if (MetalArmor)
					{
						TempChangeAbsorbFlag = 1;

					}
					break;
				case SKILL_PHYSICAL_ABSORB:
					TempChangeAbsorbFlag = 1;
					break;
				case SKILL_FORCE_ORB:
					TempChangeDamageFlag = 1;
					break;
				case SKILL_COMPULSION:
					TempChangeAbsorbFlag = 1;
					break;
				case CLANSKILL_ABSORB:
					TempChangeAbsorbFlag = 1;
					break;
				case CLANSKILL_ATTACK:
					TempChangeDamageFlag = 1;
					break;
				case BC_SKILL_SILVER:
					TempChangeDamageFlag = 1;
					break;
				case BC_SKILL_BRONZE:
					TempChangeDamageFlag = 1;
					break;
				case SCROLL_INVULNERABILITY:
					TempChangeDamageFlag = 1;
					break;
				}
			}
		}
	}


	if (sinChar->dwEventTime_T && sinChar->SizeLevel > 1)
	{
		TempChangeDamageFlag = 1;
	}


	if (sinCharItemDamage)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
	else if (TempChangeDamageFlag)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
	else SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_WHITE;


	if (TempChangeAbsorbFlag)
		SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_BLUE;
	else SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;

	if (chaPremiumitem.m_BigHeadTime > 0)
	{
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_BLUE;
	}

	sinChar->Potion_Space = sinPotion_Space;

	fstrength = (float)sinChar->Strength;
	fhealth = (float)sinChar->Health;
	ftalent = (float)sinChar->Talent;
	fSpirit = (float)sinChar->Spirit;
	fDexterity = (float)sinChar->Dexterity;
	fLevel = (float)sinChar->Level;



	sinChar->Attack_Rating = (int)((sinAttack_Rating + (fDexterity*3.1) + (fLevel*1.9) + (ftalent*1.5)) + sinLev_Attack_Rating);

	if (sinDamageFunction[0] == 1 && !sInven[0].ItemIndex)
	{
		sinChar->Attack_Damage[0] = 1 + ((sinChar->Strength + 130) / 130) + ((sinChar->Talent + sinChar->Dexterity) / 40) + sinLev_Damage[0];
		sinChar->Attack_Damage[1] = 2 + ((sinChar->Strength + 130) / 130) + ((sinChar->Talent + sinChar->Dexterity) / 35) + sinLev_Damage[1];
	}
	if ((sinDamageFunction[0] == 2 || sinDamageFunction[0] == 3 || sinDamageFunction[0] == 4) && !sInven[0].ItemIndex)
	{
		sinChar->Attack_Damage[0] = 1 + ((sinChar->Strength + 200) / 200) + ((sinChar->Talent + sinChar->Dexterity) / 50) + sinLev_Damage[0];
		sinChar->Attack_Damage[1] = 2 + ((sinChar->Strength + 200) / 200) + ((sinChar->Talent + sinChar->Dexterity) / 45) + sinLev_Damage[1];
	}


	if ((sinDamageFunction[0] == 1 && (InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 1 || InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 3)))
	{
		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Strength + 130) / 130) +
			((sinChar->Talent + sinChar->Dexterity) / 40) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Strength + 130) / 130) +
			((sinChar->Talent + sinChar->Dexterity) / 40) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if ((sinDamageFunction[0] == 2 && (InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 1 || InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 3)))
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Strength + 150) / 150) +
			((sinChar->Talent + sinChar->Dexterity) / 45) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Strength + 150) / 150) +
			((sinChar->Talent + sinChar->Dexterity) / 45) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if ((sinDamageFunction[0] == 3 && (InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 1 || InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 3)))
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Strength + 190) / 190) +
			((sinChar->Talent + sinChar->Dexterity) / 50) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Strength + 190) / 190) +
			((sinChar->Talent + sinChar->Dexterity) / 50) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}

	if (sinDamageFunction[1] == 1 && InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 2)
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Dexterity + 130) / 130) +
			((sinChar->Talent + sinChar->Strength) / 40) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Dexterity + 130) / 130) +
			((sinChar->Talent + sinChar->Strength) / 40) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if (sinDamageFunction[1] == 2 && InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 2)
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Dexterity + 190) / 190) +
			((sinChar->Talent + sinChar->Strength) / 50) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Dexterity + 190) / 190) +
			((sinChar->Talent + sinChar->Strength) / 50) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}

	if (sinDamageFunction[2] == 1 && InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 3)
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Spirit + 150) / 150) +
			((sinChar->Talent) / 30) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Spirit + 150) / 150) +
			((sinChar->Talent) / 30) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	if (sinDamageFunction[2] == 2 && InvenItem[sInven[0].ItemIndex - 1].WeaponClass == 3)
	{

		sinChar->Attack_Damage[0] = 1 + (sinAttack_Damage[0] * (sinChar->Spirit + 170) / 170) +
			((sinChar->Talent) / 30) + sinLev_Damage[0] + sinSkillDamage[0] + sinCharItemDamage + ((sinAttack_Damage[0] + sinAttack_Damage[1]) / 16);
		sinChar->Attack_Damage[1] = 3 + (sinAttack_Damage[1] * (sinChar->Spirit + 170) / 170) +
			((sinChar->Talent) / 30) + sinLev_Damage[1] + sinSkillDamage[1] + sinCharItemDamage;
	}
	sinChar->Attack_Damage[0] += 1;
	sinChar->Attack_Damage[1] += 1;


#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func12_Protect(&(sinChar->Attack_Damage), sizeof(sinChar->Attack_Damage));
	XTrap_CE1_Func13_Free(&(sinChar->Attack_Damage), sizeof(sinChar->Attack_Damage));
#endif


	if (ViewDamagePercent)
	{
		sinTempDamage2[0] += (sinChar->Attack_Damage[0] * ViewDamagePercent) / 100;
		sinTempDamage2[1] += (sinChar->Attack_Damage[1] * ViewDamagePercent) / 100;
	}
	else if (ViewDamageNum)
	{
		sinTempDamage2[0] += ViewDamageNum;
		sinTempDamage2[1] += ViewDamageNum;
	}


	if (chaPremiumitem.m_AwellPowerTime > 0)
	{
		sinCritical += 5;
	}

	sinChar->Critical_Hit = sinCritical + sinAdd_Critical_Hit;


	if (sinChar->Critical_Hit > 50)sinChar->Critical_Hit = 50;
	float fagi = (float)sinChar->Dexterity;
	fstrength = (float)sinChar->Strength;
	fhealth = (float)sinChar->Health;
	ftalent = (float)sinChar->Talent;
	fSpirit = (float)sinChar->Spirit;


	sinChar->Defence = (int)((fDexterity / 2) + (ftalent / 4) + fLevel * 1.4 + sinDefense) + sinAdd_Defence;
	fDefense = (float)sinChar->Defence;



	CountAbsorbItem /= 2;
	if (CountAbsorbItem > 2) CountAbsorbItem = 2;
	sinChar->Absorption = (int)((fDefense / 100 + (fLevel / 10) + sinAbsorption + sinAdd_fAbsorb) + ((fstrength + ftalent) / 40)) + 1 + CountAbsorbItem;

	sinChar->Shooting_Range = sinShooting_Range + sinAdd_Shooting_Range;


	sinChar->Sight = sinSight + 180;


	sinChar->Chance_Block = (int)(sinBlock_Rate + sinAdd_fBlock_Rating);


	if (chaPremiumitem.m_MightofAwellTime > 0)
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth * 1.5) + fLevel * 3) + 60 + 1000);
	}
	else
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth * 1.5) + fLevel * 3) + 60);
	}

	fMaxWeight = (float)sinChar->Weight[1];
	fNowWeight = (float)sinChar->Weight[0];


	if (sinChar->GravityScroolCheck[0] == 0)
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth * 1.5) + fLevel * 3) + 60);

	}

	if (sinChar->GravityScroolCheck[0] > 0)
	{
		sinChar->Weight[1] = (short)(((fstrength * 2) + (fhealth * 1.5) + fLevel * 3) + 60) + (sinChar->GravityScroolCheck[0]) * 50;

	}

	fMaxWeight = (float)sinChar->Weight[1];
	fNowWeight = (float)sinChar->Weight[0];
	// AGILIDADE DAR PESO
	sinChar->Weight[1] += static_cast<short>(fagi * 1);
	sinChar->Weight[1] += static_cast<short>(fSpirit * 1);


	if (chaPremiumitem.m_MightofAwellTime > 0)
	{
		sinChar->Weight[1] += 1000;
	}


	fAttack_Rating = (float)sinChar->Attack_Rating;


	int Accuracy_Temp;
	while (1)
	{
		if (Accuracy_Table[cnt][0] == 0)break;
		Accuracy_Temp = sinChar->Attack_Rating;
		if (Accuracy_Temp > Accuracy_Table[cnt][0] && Accuracy_Temp < Accuracy_Table[cnt + 1][0])
		{
			sinChar->Accuracy = Accuracy_Table[cnt + 1][1];
			break;

		}
		cnt++;
	}

	if (chaPremiumitem.m_BDivinaTime > 0)
	{
		sinMoveSpeed += 5;
	}

	sinChar->Move_Speed = (int)((((((ftalent + fhealth + fLevel + 60) / 150) - (fNowWeight / fMaxWeight))) + sinMoveSpeed) + sinAdd_fSpeed);
	sinChar->Move_Speed += 1;


#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func11_Protect(&(sinChar->Life), sizeof(sinChar->Life));
#endif

	switch (sinChar->LifeFunction)
	{
	case 1://FS
		sinChar->Life[1] = (short)(fLevel * 2.1 + ((fhealth * 2.4) + (fstrength * 0.8)) - 10);
		sinChar->Life[1] += (short)(sinLev_Life + sinfIncreLife);

		boosterLife = (sinChar->Life[1] * 10) / 100;;//Valor Fixo de adicional

		for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				vlLife = (sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
			}
		}
		break;
	case 2:
		sinChar->Life[1] = (short)(fLevel * 2.1 + ((fhealth * 2.2) + (fstrength * 0.6)) - 5);
		sinChar->Life[1] += (short)(sinLev_Life + sinfIncreLife);

		boosterLife = (sinChar->Life[1] * 10) / 100;;//Valor Fixo de adicional

		for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				vlLife = (sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
			}
		}
		break;
	case 3:
		sinChar->Life[1] = (short)(fLevel * 1.8 + ((fhealth * 2.1) + (fstrength * 0.3)));
		sinChar->Life[1] += (short)(sinLev_Life + sinfIncreLife);

		boosterLife = (sinChar->Life[1] * 10) / 100;;//Valor Fixo de adicional

		for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				vlLife = (sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
			}
		}
		break;
	case 4:
		sinChar->Life[1] = (short)((fLevel * 1.5) + (fhealth * 2.1));
		sinChar->Life[1] += (short)(sinLev_Life + sinfIncreLife);

		boosterLife = (sinChar->Life[1] * 10) / 100;;//Valor Fixo de adicional

		for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				vlLife = (sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
			}
		}
		break;
	case 5:
		sinChar->Life[1] = (short)((fLevel * 1.5) + (fhealth * 1.9));
		sinChar->Life[1] += (short)(sinLev_Life + sinfIncreLife);

		boosterLife = (sinChar->Life[1] * 10) / 100;;//Valor Fixo de adicional

		for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
		{
			if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
			{
				vlLife = (sinChar->Life[1] * Virtual_Life_Percent[ContinueSkill[i].Point - 1]) / 100;
			}
		}
		break;

	}

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (ContinueSkill[i].CODE == SKILL_VIRTUAL_LIFE)
		{
			sinChar->Life[1] += vlLife;
			SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_RED;
		}
	}

	if (chaPremiumitem.m_HPBoosterTime > 0)
	{
		SkillTextColor[SIN2_LIFE] = SIN_TEXT_COLOR_RED;
		sinChar->Life[1] += boosterLife;
	}

	if (chaPremiumitem.m_MPBoosterTime > 0)
	{
		SkillTextColor[SIN2_MANA] = SIN_TEXT_COLOR_BLUE;
		sinfIncreMana += (sinChar->Mana[1] * 10) / 100;
	}

	if (chaPremiumitem.m_SPBoosterTime > 0)
	{
		SkillTextColor[SIN2_STAMINA] = SIN_TEXT_COLOR_GREEN;
		sinfIncreStamina += (sinChar->Stamina[1] * 10) / 100;
	}


	if (!sinQuest_ChangeJob3.CODE && !SearchItemCode(0, ITEM_KIND_QUEST_WEAPON) &&
		sinChar->ChangeJob >= 2 && sinChar->Level >= 40)
	{
		sinChar->Life[1] += 15;
	}


	if ((sinQuest_levelLog & QUESTBIT_LEVEL_90) == QUESTBIT_LEVEL_90)
	{
		if (sinChar->Level >= 90)
		{
			sinChar->Life[1] += 40;
		}

	}
#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func12_Protect(&(sinChar->Life), sizeof(sinChar->Life));
	XTrap_CE1_Func13_Free(&(sinChar->Life), sizeof(sinChar->Life));
#endif










#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func11_Protect(&(sinChar->Mana), sizeof(sinChar->Mana));
#endif


	switch (sinChar->ManaFunction)
	{
	case 1:
		sinChar->Mana[1] = (short)((fLevel * 1.5f + (fSpirit*3.8f)));
		sinChar->Mana[1] += (short)(sinfIncreMana);
		break;
	case 2:
		sinChar->Mana[1] = (short)(sinChar->Level * 0.9f + (sinChar->Spirit*2.7f));
		sinChar->Mana[1] += (short)(sinLev_Mana + sinfIncreMana);
		break;
	case 3:
		sinChar->Mana[1] = (short)(sinChar->Level * 0.6f + (sinChar->Spirit*2.2f));
		sinChar->Mana[1] += (short)(sinLev_Mana + sinfIncreMana);
		break;

	}

#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func12_Protect(&(sinChar->Mana), sizeof(sinChar->Mana));
	XTrap_CE1_Func13_Free(&(sinChar->Mana), sizeof(sinChar->Mana));
#endif









#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func11_Protect(&(sinChar->Stamina), sizeof(sinChar->Stamina));

#endif


	sinChar->Stamina[1] = (short)((fhealth*1.4) + (fstrength + ftalent) / 2 + (fLevel*2.3) + 80 + fSpirit);
	sinChar->Stamina[1] += ((short)(sinfIncreStamina));

#ifdef _XTRAP_GUARD_4_CLIENT 
	XTrap_CE1_Func12_Protect(&(sinChar->Stamina), sizeof(sinChar->Stamina));

	XTrap_CE1_Func13_Free(&(sinChar->Stamina), sizeof(sinChar->Stamina));

#endif



	mana_regen_true = sinfRegenMana + sinPer_Mana_Regen;
	life_regen_true = sinfRegenLife + sinPer_Life_Regen;
	stam_regen_true = sinfRegenStamina + sinPer_Stamina_Regen;

	sinChar->Life_Regen = sinfRegenLife + sinPer_Life_Regen;
	sinChar->Mana_Regen = sinfRegenMana + sinPer_Mana_Regen;
	sinChar->Stamina_Regen = sinfRegenStamina + sinPer_Stamina_Regen;


	sinChar->Attack_Speed = sinWeaponSpeed + sinAdd_Attack_Speed + sinSkillWeaponSpeed;



	for (int i = 1; i < MAX_USESKILL; i++)
	{
		if (sinSkill.UseSkill[i].Flag && sinSkill.UseSkill[i].Point)
		{
			switch (sinSkill.UseSkill[i].CODE)
			{
			case SKILL_PHYSICAL_TRANING:
				TempSkillData = (((float)P_Traning_Stamina[sinSkill.UseSkill[i].Point - 1])*(float)sinChar->Stamina[1] / 100.0f);
				sinChar->Stamina[1] += (short)TempSkillData;
				break;
			case SKILL_FIRE_JAVELIN:
				sElement_Attack.Fire[0] += Fire_Javelin_Damage[sinSkill.UseSkill[i].Point - 1][0];
				sElement_Attack.Fire[1] += Fire_Javelin_Damage[sinSkill.UseSkill[i].Point - 1][1];
				break;
			case SKILL_MEDITATION:
				sinChar->Mana_Regen += Meditation_Regen[sinSkill.UseSkill[i].Point - 1];
				mana_regen_true += Meditation_Regen[sinSkill.UseSkill[i].Point - 1];
				break;
			case SKILL_MENTAL_MASTERY:
				TempSkillData = (float)((float)(Mental_Mastery_Mana[sinSkill.UseSkill[i].Point - 1])*((float)sinChar->Mana[1] / 100.0f));
				sinChar->Mana[1] += (short)TempSkillData;
				break;
			case SKILL_BOOST_HEALTH:
				sinChar->Life[1] += (short)Boost_Health_Life[sinSkill.UseSkill[i].Point - 1];

				break;

			}
		}
	}




	SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;

	int OrbDamageTemp2 = 0;

	for (int i = 0; i < MAX_CONTINUE_SKILL; i++)
	{
		if (ContinueSkill[i].Flag)
		{
			switch (ContinueSkill[i].CODE)
			{
			case SKILL_HOLY_BODY:
				TempSkillData = ((float)HolyBody_Absorb[ContinueSkill[i].Point - 1] / 100.0f);
				sinUndeadAbsorb = (int)((float)sinChar->Absorption*TempSkillData);
				break;
			case SKILL_DRASTIC_SPIRIT:
				TempSkillData = ((float)Drastic_Spirit_Defense[ContinueSkill[i].Point - 1] / 100.0f);
				sinChar->Defence += (int)((float)sinChar->Defence * TempSkillData);
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				break;
			case SKILL_SPARK_SHIELD:
			case SKILL_METAL_ARMOR:
				if (MetalArmor)
				{
					SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_BLUE;
				}
				break;
			case SKILL_CONCENTRATION:
				for (p = 0; p < 8; p++)
				{
					if (sInven[0].ItemIndex)
					{
						if (ContinueSkill[i].Skill_Info.UseWeaponCode[p] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinChar->Attack_Rating += Concentration_AttackRate[ContinueSkill[i].Point - 1];
							SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
							Flag3 = 1;
							break;
						}
					}

				}
				if (!Flag3)
				{


					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
				}
				break;

			case SKILL_A_MIGAL:

				sinChar->Attack_Rating += AdventMigal_AttackRate[ContinueSkill[i].Point - 1];
				SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;

				for (p = 0; p < 8; p++)
				{
					if (sInven[0].ItemIndex)
					{
						if (ContinueSkill[i].Skill_Info.UseWeaponCode[p] == (cInvenTory.InvenItem[sInven[0].ItemIndex - 1].CODE&sinITEM_MASK2))
						{
							sinChar->Attack_Rating += AdventMigal_AttackRate[ContinueSkill[i].Point - 1];
							SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_ORANGE;
							Flag3 = 1;
							break;
						}
					}

				}
				if (!Flag3)
				{
					SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
				}
				break;

			case SKILL_SPIRIT_ELEMENTAL:

				sinfRegenMana += Spirit_Elemental_RegenMana[ContinueSkill[i].Point - 1];
				sinTempDamage2[0] += (sinTempDamage2[0] * Spirit_Elemental_Damage[ContinueSkill[i].Point - 1]) / 100;
				sinTempDamage2[1] += (sinTempDamage2[1] * Spirit_Elemental_Damage[ContinueSkill[i].Point - 1]) / 100;

				sinChar->Attack_Damage[0] += (sinChar->Attack_Damage[0] * Spirit_Elemental_Damage[ContinueSkill[i].Point - 1]) / 100;
				sinChar->Attack_Damage[1] += (sinChar->Attack_Damage[1] * Spirit_Elemental_Damage[ContinueSkill[i].Point - 1]) / 100;


				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_ORANGE;;
				break;


			case SKILL_FORCE_ORB:

				if (ContinueSkill[i].ElementIndex == 1000)
				{

					OrbDamageTemp2 = (sinChar->Attack_Damage[0] + ((sinChar->Attack_Damage[1] - sinChar->Attack_Damage[0]) / 2)) / 15;
					sinTempDamage2[0] += OrbDamageTemp2;
					sinTempDamage2[1] += OrbDamageTemp2;
				}
				else
				{

					if (ContinueSkill[i].Point >= 7 && ContinueSkill[i].Point <= 10)
					{
						OrbDamageTemp2 = (sinChar->Attack_Damage[0] + ((sinChar->Attack_Damage[1] - sinChar->Attack_Damage[0]) / 2)) / 10;
						sinTempDamage2[0] += OrbDamageTemp2;
						sinTempDamage2[1] += OrbDamageTemp2;
					}
					else if (ContinueSkill[i].Point == 11)
					{
						OrbDamageTemp2 = (((sinChar->Attack_Damage[1] + sinChar->Attack_Damage[0]) / 2) * 15) / 100;
						sinTempDamage2[0] += OrbDamageTemp2;
						sinTempDamage2[1] += OrbDamageTemp2;
					}
					else if (ContinueSkill[i].Point == 12)
					{
						OrbDamageTemp2 = (((sinChar->Attack_Damage[1] + sinChar->Attack_Damage[0]) / 2) * 20) / 100;
						sinTempDamage2[0] += OrbDamageTemp2;
						sinTempDamage2[1] += OrbDamageTemp2;
					}
					else if (ContinueSkill[i].Point == 13)
					{
						OrbDamageTemp2 = (((sinChar->Attack_Damage[1] + sinChar->Attack_Damage[0]) / 2) * 25) / 100;
						sinTempDamage2[0] += OrbDamageTemp2;
						sinTempDamage2[1] += OrbDamageTemp2;
					}
					else if (ContinueSkill[i].Point == 14)
					{
						OrbDamageTemp2 = (((sinChar->Attack_Damage[1] + sinChar->Attack_Damage[0]) / 2) * 30) / 100;
						sinTempDamage2[0] += OrbDamageTemp2;
						sinTempDamage2[1] += OrbDamageTemp2;
					}
					sinTempDamage2[0] += ForceOrbDamage[ContinueSkill[i].Point - 1];
					sinTempDamage2[1] += ForceOrbDamage[ContinueSkill[i].Point - 1];
				}
				break;
			case SKILL_REGENERATION_FIELD:
				sinChar->Mana_Regen += Regeneration_Field_ManaRegen[ContinueSkill[i].Point - 1] / ContinueSkill[i].Flag;
				sinChar->Life_Regen += Regeneration_Field_LifeRegen[ContinueSkill[i].Point - 1];
				mana_regen_true += Regeneration_Field_ManaRegen[ContinueSkill[i].Point - 1];
				life_regen_true += Regeneration_Field_LifeRegen[ContinueSkill[i].Point - 1];
				break;
			case SKILL_BERSERKER:
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
				break;
			case SCROLL_INVULNERABILITY:
			case SCROLL_P_INVULNERABILITY:
				sinTempDamage2[0] -= (sinChar->Attack_Damage[0] * 100);
				sinTempDamage2[1] -= (sinChar->Attack_Damage[1] * 100);
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;
				break;
			case CLANSKILL_ATTACK:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 10) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 10) / 100;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;

			case BC_SKILL_SILVER:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 5) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 5) / 100;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;

			case BC_SKILL_BRONZE:
				sinTempDamage2[0] += (int)(sinChar->Attack_Damage[0] * 3) / 100;
				sinTempDamage2[1] += (int)(sinChar->Attack_Damage[1] * 3) / 100;
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_GOLD;
				break;
			}
		}
	}



	if (chaPremiumitem.m_HelpPetTime > 0 && sinChar->GravityScroolCheck[1] == 2)
	{
		sinTempDamage2[0] += (sinTempDamage2[0] * 10) / 100;
		sinTempDamage2[1] += (sinTempDamage2[1] * 10) / 100;
	}


	if (sinQuest_Level90_2.CODE && sinQuest_Level90_2.State >= 2)
	{
		sinTempDamage2[0] = (sinTempDamage2[0] * 70) / 100;
		sinTempDamage2[1] = (sinTempDamage2[1] * 70) / 100;

		sinChar->Attack_Damage[0] = (sinChar->Attack_Damage[0] * 70) / 100;
		sinChar->Attack_Damage[1] = (sinChar->Attack_Damage[1] * 70) / 100;

	}


	CheckRequireItem();

	ReformCharForm();


	ReSettingPotion();




	if (!CheckHackFlag)
		memcpy(&sinCharDisplay, sinChar, sizeof(smCHAR_INFO));
	else
		HackCharStateCheck(sinChar, &sinCharDisplay);

	return TRUE;
}


void cINVENTORY::LoadCharState()
{

	if (!sinChar->ArrowPosi[0])sinChar->ArrowPosi[0] = 1;
	if (!sinChar->ArrowPosi[1])sinChar->ArrowPosi[1] = 3;


	if (sinChar->ArrowPosi[0] == 1)
		ArrowState[0] = 0;
	if (sinChar->ArrowPosi[0] == 2)
		ArrowState[0] = 1;
	if (sinChar->ArrowPosi[1] == 3)
		ArrowState[1] = 0;
	if (sinChar->ArrowPosi[1] == 4)
		ArrowState[1] = 1;

	OldLevel = sinChar->Level;
	OldLevelTemp = OldLevel + 176;
	sinLoadOK = 1;

}


int cINVENTORY::ChangeABItem(int Posi)
{
	SetDelayFlag = 1;


	if (NotChangeSetItemFlag)return TRUE;
	if (cMyShop.OpenFlag)return FALSE;
	if (MyShopSendButton)return FALSE;
	if (ChangeSpecialItem(1))return TRUE;

	if (cWareHouse.OpenFlag)
	{


		if (MouseItem.Flag)
			return TRUE;
	}

	if (sMessageBox3[MESSAGE_SELL_HIGHRANK_ITEM].Flag)return TRUE;
	if (SpecialItemShowFlag)return TRUE;


	CheckInvenItemForm();

	int desPosi;
	int i, j, t;


	if (sMessageBox3[MESSAGE_TELEPORT_CORE].Flag)return TRUE;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			return TRUE;
		}

	}


	if (sinCraftItemStartFlag || StartInterEffectAging2)
	{
		return TRUE;
	}
	else if ((ManufactureItem.m_OpenFlag || SmeltingItem.OpenFlag) && MixCancelButtonDelayFlag)
	{
		return TRUE;
	}



	if (Posi <= 2)desPosi = 1;
	if (Posi > 2)desPosi = 2;

	if (Posi == 1)
	{
		ArrowState[0] = 0;
		sinChar->ArrowPosi[0] = 1;

	}
	if (Posi == 2)
	{
		ArrowState[0] = 1;
		sinChar->ArrowPosi[0] = 2;

	}
	if (Posi == 3)
	{
		ArrowState[1] = 0;
		sinChar->ArrowPosi[1] = 3;

	}
	if (Posi == 4)
	{
		ArrowState[1] = 1;
		sinChar->ArrowPosi[1] = 4;

	}

	switch (desPosi)
	{
	case 1:
		memcpy(&BackUpInvenItemTemp, &InvenItemTemp, sizeof(sITEM) * 80);
		for (t = 0; t < 80; t++)InvenItemTemp[t].Flag = 0;
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].ItemPosition == 0)
				{
					for (j = 0; j < 80; j++)
					{
						if (!InvenItemTemp[j].Flag)
						{
							memcpy(&InvenItemTemp[j], &InvenItem[i], sizeof(sITEM));
							InvenItem[i].Flag = 0;
							break;
						}
					}
				}
			}
		}
		for (i = 0; i < 80; i++)
		{
			if (BackUpInvenItemTemp[i].Flag)
			{
				for (j = 0; j < 80; j++)
				{
					if (!InvenItem[j].Flag)
					{
						memcpy(&InvenItem[j], &BackUpInvenItemTemp[i], sizeof(sITEM));
						BackUpInvenItemTemp[i].Flag = 0;
						break;

					}

				}

			}

		}

		break;

	case 2:
		ContinueSkillCancelFlag = 1;
		memcpy(&BackUpInvenItemTemp[80], &InvenItemTemp[80], sizeof(sITEM) * 2);
		for (t = 80; t < 82; t++)InvenItemTemp[t].Flag = 0;
		for (i = 0; i < 80; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].ItemPosition == 1 || InvenItem[i].ItemPosition == 2)
				{
					for (j = 80; j < 82; j++)
					{
						if (!InvenItemTemp[j].Flag)
						{
							memcpy(&InvenItemTemp[j], &InvenItem[i], sizeof(sITEM));
							InvenItem[i].Flag = 0;
							sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;
							if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[i].CODE&sinITEM_MASK2) == sinWD1)
							{
								sinSetCharItem(InvenItem[i].CODE, 2, FALSE);
								sinSetCharItem(InvenItem[i].CODE, 4, FALSE);
							}
							else
							
								sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
							break;
						}
					}
				}
			}
		}

		for (i = 80; i < 82; i++)
		{
			if (BackUpInvenItemTemp[i].Flag)
			{
				for (j = 0; j < 80; j++)
				{
					if (!InvenItem[j].Flag)
					{
						memcpy(&InvenItem[j], &BackUpInvenItemTemp[i], sizeof(sITEM));
						BackUpInvenItemTemp[i].Flag = 0;
						sInven[InvenItem[j].ItemPosition - 1].ItemIndex = j + 1;
						if (lpCurPlayer->smCharInfo.JOB_CODE == 9 && (InvenItem[j].CODE&sinITEM_MASK2) == sinWD1)
						{
							sinSetCharItem(InvenItem[j].CODE, 2, TRUE);
							sinSetCharItem(InvenItem[j].CODE, 4, TRUE);
						}
						else
							sinSetCharItem(InvenItem[j].CODE, InvenItem[j].SetModelPosi, TRUE);
						if (InvenItem[j].SoundIndex)
							sinPlaySound(InvenItem[j].SoundIndex);
						break;

					}

				}

			}

		}
		SetItemToChar();
		break;
	}


	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].ItemPosition)
			{

				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (InvenItem[i].ItemPosition == 1)
					{
						if (InvenItem[i].sItemInfo.CODE != InvenItem[sInven[1].ItemIndex - 1].sItemInfo.CODE)
						{
							InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
							InvenItem[i].Flag = 0;
							sInven[1].ItemIndex = 0;
							sInven[0].ItemIndex = 0;
							if (InvenItem[i].SetModelPosi)
							{
								sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
							}
						}
					}
					if (InvenItem[i].ItemPosition == 2)
					{
						if (InvenItem[i].sItemInfo.CODE != InvenItem[sInven[0].ItemIndex - 1].sItemInfo.CODE)
						{
							InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
							InvenItem[i].Flag = 0;
							sInven[0].ItemIndex = 0;
							sInven[1].ItemIndex = 0;
							if (InvenItem[i].SetModelPosi)
								
								sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

						}
					}
				}
			}
		}
	}


	if (MouseItem.Flag)
	{
		if (MouseItem.Class == ITEM_CLASS_POTION)
		{
			GhostPotionCheckFlag = 1;

		}
		else
			GhostPotionCheckFlag = 0;

	}
	else
		GhostPotionCheckFlag = 0;

	CheckRequireItem();
	ReFormInvenItem();
	cInvenTory.CheckPuzzle();
	return TRUE;
}

int cINVENTORY::ChangeACItem(bool Costume)
{
	SetItemToChar();
	if (Costume)
	{
		int Index = sInven[13].ItemIndex;

		if (Index)
		{
			sITEM & Item = InvenItem[Index - 1];
			sinSetCharItem(Item.CODE, Item.SetModelPosi, TRUE);
		}
		else
		{
			sinSetCharItem(NULL, INVENTORY_POS_ARMOR, TRUE);
		}
	}
	else
	{
		int Index = sInven[2].ItemIndex;

		if (Index)
		{
			sITEM & Item = InvenItem[Index - 1];
			sinSetCharItem(Item.CODE, Item.SetModelPosi, TRUE);
		}
		else
		{
			sinSetCharItem(NULL, INVENTORY_POS_COSTUME, TRUE);
		}
	}
	CheckRequireItem();
	ReFormInvenItem();
	return TRUE;
}



sITEMPRICE cINVENTORY::GetInvenItemPrice(sITEM *pItem)
{

	sITEMPRICE sinItemPrice;

	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (pItem->ItemPosition)
		{
			pItem = &InvenItem[sInven[0].ItemIndex - 1];

		}
	}

	float Dur[2];
	float Price;

	Dur[0] = pItem->sItemInfo.Durability[0];
	Dur[1] = pItem->sItemInfo.Durability[1];
	Price = (float)pItem->sItemInfo.Price;
	if (Dur[0] == 0)Dur[0] = 1;
	if (Dur[1] == 0)Dur[1] = 1;

	sinItemPrice.PureSellPrice = (int)((Price*(Dur[0] / Dur[1])) + (Price - (Price*(Dur[0] / Dur[1])))*0.25);

	sinItemPrice.SellPrice = (int)sinItemPrice.PureSellPrice / 5;

	sinItemPrice.RepairCost = (pItem->sItemInfo.Price - sinItemPrice.PureSellPrice) / 8;

	//Divisao pre�o venda item
	if ((pItem ->CODE & sinITEM_MASK2) == sinGB1) {
		sinItemPrice.SellPrice = (int)sinItemPrice.PureSellPrice;
	}

	return sinItemPrice;

}


int cINVENTORY::RepairInvenItem(sITEM *pItem, int RepairCost)
{
	if (pItem->Class == ITEM_CLASS_WEAPON_TWO)
	{
		if (pItem->ItemPosition)
		{
			pItem = &InvenItem[sInven[0].ItemIndex - 1];

		}
	}

	CheckCharForm();

	if (!pItem->sItemInfo.Durability[1])return FALSE;
	if (sinChar->Money - RepairCost > 0)
	{
		if (pItem->sItemInfo.Durability[0] < pItem->sItemInfo.Durability[1])
		{

			sinMinusMoney(RepairCost);
			pItem->sItemInfo.Durability[0] = pItem->sItemInfo.Durability[1];
			ReformCharForm();
			SendSaveMoney();
			return TRUE;
		}
	}
	return FALSE;

}


void cINVENTORY::CheckWeight()
{

	CheckCharForm();

	sinChar->Weight[0] = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].Class == ITEM_CLASS_POTION)
			{
				if (InvenItem[i].sItemInfo.PotionCount < 0)continue;
				sinChar->Weight[0] += InvenItem[i].sItemInfo.PotionCount;
				continue;

			}
			if (InvenItem[i].sItemInfo.Weight < 0)continue;
			sinChar->Weight[0] += InvenItem[i].sItemInfo.Weight;
		}
	}
	for (int j = 0; j < INVENTORY_MAXITEM; j++)
	{
		if (InvenItemTemp[j].Flag)
		{
			if (InvenItemTemp[j].Class == ITEM_CLASS_POTION)
			{
				if (InvenItemTemp[j].sItemInfo.PotionCount < 0)continue;
				sinChar->Weight[0] += InvenItemTemp[j].sItemInfo.PotionCount;
				continue;

			}
			if (InvenItemTemp[j].sItemInfo.Weight < 0)continue;
			sinChar->Weight[0] += InvenItemTemp[j].sItemInfo.Weight;
		}
	}

	ReformCharForm();

}


int cINVENTORY::CheckSetOk(sITEM *pItem, int AutoFlag)
{
	CheckWeight();
	if (pItem->Class == ITEM_CLASS_POTION)
	{
		if (sinChar->Weight[0] + pItem->sItemInfo.PotionCount > sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			sinOverWeightCnt++;
			return FALSE;
		}

	}
	else
	{
		
		if (sinChar->Weight[0] + pItem->sItemInfo.Weight > sinChar->Weight[1])
		{
			if (pItem->sItemInfo.ItemKindCode != ITEM_KIND_QUEST_WEAPON)
			{		
				
				cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
				sinOverWeightCnt++;
				return FALSE;
			}
		}
	}
	if (!AutoFlag)
	{
		if (pItem->ItemPosition)
		{
			if (pItem->sItemInfo.NotUseFlag)
			{
				cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
				return FALSE;
			}
		}
	}
	return TRUE;
}


int cINVENTORY::CopyItemClear(sITEM *pItem)
{

	int CopyItemCnt = 0;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (CompareItems(&pItem->sItemInfo, &InvenItem[i].sItemInfo))
			{

				InvenItem[i].Flag = 0;
				if (InvenItem[i].ItemPosition)
				{
					sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;
					sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);
					ClearTwoHandPosiAndItem(&InvenItem[i]);

				}
				CopyItemCnt++;


			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (CompareItems(&pItem->sItemInfo, &InvenItemTemp[i].sItemInfo))
			{
				InvenItemTemp[i].Flag = 0;
				if (InvenItemTemp[i].Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (InvenItemTemp[i].ItemPosition == 1 || InvenItemTemp[i].ItemPosition == 2)
					{
						for (int k = 0; k < INVENTORY_MAXITEM; k++)
						{
							if (InvenItemTemp[k].Flag)
							{
								if (InvenItemTemp[k].ItemPosition == 1 || InvenItemTemp[k].ItemPosition == 2)
								{
									if (InvenItemTemp[i].sItemInfo.CODE == InvenItemTemp[k].sItemInfo.CODE)
									{
										InvenItemTemp[k].Flag = 0;
									}
								}
							}
						}
					}
				}
				CopyItemCnt++;
			}
		}
	}
	if (CopyItemCnt)
	{
		SendCopyItemUser(CopyItemCnt);
		CopyItemCnt = 0;
	}
	return TRUE;

}

POINT ResultSize;


POINT cINVENTORY::CheckImageSize(LPDIRECT3DTEXTURE9 lpdd)
{
	ResultSize.x = 0;
	ResultSize.y = 0;
	D3DSURFACE_DESC	ddTemp;
	memset(&ddTemp, 0, sizeof(D3DSURFACE_DESC));
	lpdd->GetLevelDesc(0, &ddTemp);
	ResultSize.y = ddTemp.Height;
	ResultSize.x = ddTemp.Width;
	return ResultSize;
}


int cINVENTORY::ImsiCheckItemImageSize()
{
	sITEM TestItem;
	POINT TestPoint = { 0,0 };
	char szFilePath[256];
	sinTestBuff[0] = 0;
	for (int j = 0; j < MAX_ITEM; j++)
	{
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
		memcpy(&TestItem, &sItem[j], sizeof(sITEM));
		TestItem.lpItem = LoadDibSurfaceOffscreen(szFilePath);
		TestPoint.x = 0;
		TestPoint.y = 0;
		if (TestItem.lpItem)
		{
			TestPoint = CheckImageSize(TestItem.lpItem);
			if (TestPoint.x != sItem[j].w || TestPoint.y != sItem[j].h)
			{
				strcpy_s(sinTestBuff, sItem[j].LastCategory);
			}

		}

	}
	return TRUE;
}


int cINVENTORY::CheckOverlapItem(sITEM *pItem, int PassItemIndex)
{
	int ReSetXYFlag = 0;
	if (!pItem)return FALSE;
	if (pItem->ItemPosition)
	{
		if (pItem->ItemPosition < 11)
		{
			sInven[pItem->ItemPosition - 1].ItemIndex = 0;
			pItem->ItemPosition = 0;
			ReSetXYFlag = 1;
		}
		else
			ReSetXYFlag = 0;
	}

	RECT Rect;
	int  TempPosiFlag = 0;
	Rect.left = pItem->x;
	Rect.top = pItem->y;
	Rect.right = pItem->w;
	Rect.bottom = pItem->h;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;



	if (CrashInvenItem(Rect, PassItemIndex) || ReSetXYFlag)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItem[i].Flag)
					{
						rect.left = InvenItem[i].x;
						rect.right = InvenItem[i].x + InvenItem[i].w;
						rect.top = InvenItem[i].y;
						rect.bottom = InvenItem[i].y + InvenItem[i].h;

						if (cntx > rect.left - pItem->w && cntx< rect.right &&
							cnty > rect.top - pItem->h && cnty < rect.bottom)
							flag++;
					}
				}
				if (flag == 0)
				{
					pItem->x = cntx;
					pItem->y = cnty;
					sInven[pItem->ItemPosition - 1].ItemIndex = 0;
					pItem->ItemPosition = 0;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}


int cINVENTORY::ReSetPotionXY(sITEM *pItem, int kind)
{

	RECT Rect;
	Rect.left = pItem->x;
	Rect.top = pItem->y;
	Rect.right = pItem->w;
	Rect.bottom = pItem->h;

	int cntx, cnty;
	int cx, cy;

	RECT	rect;
	int		flag;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;



	if (kind == 1)
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItemTemp[i].Flag)
					{
						rect.left = InvenItemTemp[i].x;
						rect.right = InvenItemTemp[i].x + InvenItemTemp[i].w;
						rect.top = InvenItemTemp[i].y;
						rect.bottom = InvenItemTemp[i].y + InvenItemTemp[i].h;

						if (cntx > rect.left - pItem->w && cntx< rect.right &&
							cnty > rect.top - pItem->h && cnty < rect.bottom)
							flag++;
					}
				}
				if (flag == 0)
				{
					pItem->x = cntx;
					pItem->y = cnty;

					pItem->ItemPosition = 0;
					return TRUE;
				}

			}
		}
	}
	else
	{
		for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
		{
			for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
			{
				flag = 0;
				for (int i = 0; i < INVENTORY_MAXITEM; i++)
				{
					if (InvenItem[i].Flag)
					{
						rect.left = InvenItem[i].x;
						rect.right = InvenItem[i].x + InvenItem[i].w;
						rect.top = InvenItem[i].y;
						rect.bottom = InvenItem[i].y + InvenItem[i].h;

						if (cntx > rect.left - pItem->w && cntx< rect.right &&
							cnty > rect.top - pItem->h && cnty < rect.bottom)
							flag++;
					}
				}
				if (flag == 0)
				{
					pItem->x = cntx;
					pItem->y = cnty;
					sInven[pItem->ItemPosition - 2].ItemIndex = 0;
					pItem->ItemPosition = 0;
					return TRUE;
				}

			}
		}
	}
	return FALSE;

}


int cINVENTORY::UseEcore(sITEM *pItem)
{
	char szLinkName[24];
	int len = lstrlen(pItem->sItemInfo.ItemName);
	if (sinItemPickUpDelayFlag)return FALSE;

	if (pItem->sItemInfo.CODE == (sinEC1 | sin01) && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
	{
		cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
		return FALSE;
	}

	if (pItem->sItemInfo.CODE == (sinEC1 | sin05))
	{
		if (sinChar->ClassClan)
		{

			if (cldata.stats[0] == '1')
			{
				if (pItem->sItemInfo.ItemName[len + 1] == NULL)
				{


					UnionCorePosi.x = pItem->x;
					UnionCorePosi.y = pItem->y;
					memset(&TempLinkCoreItem, 0, sizeof(sITEMINFO));
					memcpy(&TempLinkCoreItem, &pItem->sItemInfo, sizeof(sITEMINFO));
					cMessageBox.ShowMessage3(MESSAGE_LINKCORE, "");

				}
				else
				{
					strcpy_s(szLinkName, &pItem->sItemInfo.ItemName[len + 1]);
					if (stricmp(sinChar->szName, szLinkName) != 0)
					{
						SendLinkCoreToServer(&pItem->sItemInfo);
					}
				}
			}
			else
			{
				cMessageBox.ShowMessage(MESSAGE_USE_REGULAR_CLAN_ONLY);
			}
		}
		else
		{
			cMessageBox.ShowMessage(MESSAGE_USE_CLAN_ONLY);
		}
	}
	else
	{
		CheckInvenItemForm();
		ActionEtherCore(pItem);
		pItem->Flag = 0;
		CheckWeight();
		ReFormInvenItem();
	}
	sinUsePotionDelayFlag = 1;
	return TRUE;
}


int cINVENTORY::EatSongPyeun(sITEM *pItem)
{

	if ((pItem->CODE & sinITEM_MASK3) == sin05 || (pItem->CODE & sinITEM_MASK3) == sin06 || (pItem->CODE & sinITEM_MASK3) == sin07 ||
		(pItem->CODE & sinITEM_MASK3) == sin08 || (pItem->CODE & sinITEM_MASK3) == sin09 || (pItem->CODE & sinITEM_MASK3) == sin10)
	{
		ReFormInvenItem();
		sinUsePotionDelayFlag = 1;
		return TRUE;
	}
	char szBuff[128];


	if (cItem.GetItemLimitTime(pItem) == FALSE)
	{


		wsprintf(szBuff, "%s : %s", sinChar->szName, sinDeadSongPyeunEat);
		SendChatMessageToServer(szBuff);
		ReFormInvenItem();
		sinUsePotionDelayFlag = 1;
		return FALSE;
	}
	int TempRandPotion = 0;
	int ResultPotion = 0;
	int Life = 0, Mana = 0, Stamina = 0;



	TempRandPotion = pItem->sItemInfo.Life[1] - pItem->sItemInfo.Life[0];
	ResultPotion = pItem->sItemInfo.Life[0] + (rand() % TempRandPotion);
	sinSetLife((sinGetLife() + ResultPotion));
	Life = (sinGetLife() + ResultPotion);

	TempRandPotion = pItem->sItemInfo.Mana[1] - pItem->sItemInfo.Mana[0];
	ResultPotion = pItem->sItemInfo.Mana[0] + (rand() % TempRandPotion);
	sinSetMana((sinGetMana() + ResultPotion));
	Mana = (sinGetLife() + ResultPotion);

	TempRandPotion = pItem->sItemInfo.Stamina[1] - pItem->sItemInfo.Stamina[0];
	ResultPotion = pItem->sItemInfo.Stamina[0] + (rand() % TempRandPotion);
	sinSetStamina((sinGetStamina() + ResultPotion));
	Stamina = (sinGetLife() + ResultPotion);

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_PARTY_POTION;
	smTransCommand.WParam = Life;
	smTransCommand.LParam = Mana;
	smTransCommand.SParam = Stamina;
	smTransCommand.EParam = lpCurPlayer->dwObjectSerial;

	if (smWsockUserServer && InterfaceParty.PartyMemberCount)
		smWsockUserServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);


	ReFormInvenItem();
	sinUsePotionDelayFlag = 1;


	return TRUE;

}


int cINVENTORY::ResetMouseItem()
{
	if (MouseItem.Flag)
	{
		if (cInvenTory.AutoSetInvenItem(&MouseItem))
		{
			MouseItem.Flag = 0;
		}
	}

	return TRUE;
}


int cINVENTORY::CheckInvenItemForm()
{

	DWORD TempCheckDataSum = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].Class != ITEM_CLASS_POTION)
			{

				TempCheckDataSum += (i + 1)*InvenItem[i].y;
				TempCheckDataSum += (i + 1)*InvenItem[i].Class;
				TempCheckDataSum += InvenItem[i].sItemInfo.ItemHeader.dwChkSum;
				TempCheckDataSum += InvenItem[i].sItemInfo.ItemHeader.Head;
			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].Class != ITEM_CLASS_POTION)
			{

				TempCheckDataSum += (i + 1)*InvenItemTemp[i].y;
				TempCheckDataSum += (i + 1)*InvenItemTemp[i].Class;
				TempCheckDataSum += InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum;
				TempCheckDataSum += InvenItemTemp[i].sItemInfo.ItemHeader.Head;
			}

		}

	}
	if (TempCheckDataSum != InvenDataCheckSum)
	{
		SendSetHackUser(2);


	}
	return TRUE;
}


int cINVENTORY::ReFormInvenItem()
{
	DWORD Temp = 0;
	InvenDataCheckSum = 0;

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].Class != ITEM_CLASS_POTION)
			{

				InvenDataCheckSum += (i + 1)*InvenItem[i].y;
				InvenDataCheckSum += (i + 1)*InvenItem[i].Class;
				InvenDataCheckSum += InvenItem[i].sItemInfo.ItemHeader.dwChkSum;
				InvenDataCheckSum += InvenItem[i].sItemInfo.ItemHeader.Head;
			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].Class != ITEM_CLASS_POTION)
			{

				InvenDataCheckSum += (i + 1)*InvenItemTemp[i].y;
				InvenDataCheckSum += (i + 1)*InvenItemTemp[i].Class;
				InvenDataCheckSum += InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum;
				InvenDataCheckSum += InvenItemTemp[i].sItemInfo.ItemHeader.Head;
			}

		}

	}
	Temp = InvenDataCheckSum;

	return TRUE;

}


int cINVENTORY::CheckMoneyLimit(int Money)
{

	int CheckMoney = 0;
	if (sinChar->Level <= 10)
	{
		if ((sinChar->Money + Money) <= 200000)
			return TRUE;

	}
	else
	{
		switch (sinChar->ChangeJob)
		{
		case 0:
			if ((sinChar->Money + Money) <= (sinChar->Level * 200000) - 1800000)
				return TRUE;
			break;

		case 1:
			if ((sinChar->Money + Money) <= 10000000)return TRUE;
			break;
		case 2:
			if ((sinChar->Money + Money) <= 50000000)return TRUE;

			break;

		case 3:
			if ((sinChar->Money + Money) <= MAX_MONEY)return TRUE;
			break;
		
		}
	}

	cMessageBox.ShowMessage(MESSAGE_OVER_MONEY);
	return FALSE;



}


int sinPotionNum[4] = { 0,0,0,0 };
int CheckPotionNum[4] = { 0,0,0,0 };

int cINVENTORY::ReFormPotionNum()
{
	PotionCheckNumJumpFlag = 1;

	for (int j = 0; j < 4; j++)
	{
		sinPotionNum[j] = 0;

	}
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].Class == ITEM_CLASS_POTION)
			{
				switch (InvenItem[i].CODE & sinITEM_MASK3)
				{
				case sin01:
					sinPotionNum[0] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin02:
					sinPotionNum[1] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin03:
					sinPotionNum[2] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin04:
					sinPotionNum[3] += InvenItem[i].sItemInfo.PotionCount;

					break;
				}
			}
		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].Class == ITEM_CLASS_POTION)
			{
				switch (InvenItemTemp[i].CODE & sinITEM_MASK3)
				{
				case sin01:
					sinPotionNum[0] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin02:
					sinPotionNum[1] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin03:
					sinPotionNum[2] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin04:
					sinPotionNum[3] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				}
			}
		}
	}

	PotionCheckNumJumpFlag = 0;
	return TRUE;
}


DWORD PotionCheckDelayTime = 0;

int cINVENTORY::CheckPotionNumForm()
{


	for (int k = 0; k < 4; k++)
	{
		CheckPotionNum[k] = 0;

	}
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].Class == ITEM_CLASS_POTION)
			{
				switch (InvenItem[i].CODE & sinITEM_MASK3)
				{
				case sin01:
					CheckPotionNum[0] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin02:
					CheckPotionNum[1] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin03:
					CheckPotionNum[2] += InvenItem[i].sItemInfo.PotionCount;

					break;
				case sin04:
					CheckPotionNum[3] += InvenItem[i].sItemInfo.PotionCount;

					break;
				}
			}
		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].Class == ITEM_CLASS_POTION)
			{
				switch (InvenItemTemp[i].CODE & sinITEM_MASK3)
				{
				case sin01:
					CheckPotionNum[0] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin02:
					CheckPotionNum[1] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin03:
					CheckPotionNum[2] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				case sin04:
					CheckPotionNum[3] += InvenItemTemp[i].sItemInfo.PotionCount;

					break;
				}
			}
		}
	}


	for (int j = 0; j < 4; j++)
	{
		if (CheckPotionNum[j] != sinPotionNum[j])
		{

			SendSetHackUser2(1510, j);
		}
	}
	return TRUE;

}


int cINVENTORY::CheckSpecialItem(sITEM *pItem)
{

	if (pItem->sItemInfo.ItemKindCode == ITEM_KIND_QUEST || pItem->sItemInfo.UniqueItem)
		return FALSE;


	return TRUE;
}




int dwInvenParticleShowTime = 0;

int cINVENTORY::ShowInvenEffectParticle()
{
	dwInvenParticleShowTime++;
	if (dwInvenParticleShowTime <= 5)return FALSE;
	dwInvenParticleShowTime = 0;

	int TempX, TempY;

	if (MouseItem.Flag)
	{
		if (MouseItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST || MouseItem.sItemInfo.UniqueItem)
		{
			TempX = rand() % MouseItem.w;
			TempY = rand() % MouseItem.h;
			SetInvenParticle(MouseItem.x + TempX, MouseItem.y + TempY, SIN_EFFECT_SHOW_INVEN);

		}
	}

	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{



			if (InvenItem[i].sItemInfo.ItemKindCode == ITEM_KIND_QUEST || InvenItem[i].sItemInfo.UniqueItem)
			{
				TempX = rand() % InvenItem[i].w;
				TempY = rand() % InvenItem[i].h;
				SetInvenParticle(InvenItem[i].x + TempX, InvenItem[i].y + TempY, SIN_EFFECT_SHOW_INVEN);

				if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (i == sInven[0].ItemIndex - 1)
					{
						TempX = rand() % (sInven[1].Rect.right - 10 - sInven[1].Rect.left + 10);
						TempY = rand() % (sInven[1].Rect.bottom - 10 - sInven[1].Rect.top + 10);
						SetInvenParticle(sInven[1].Rect.left + TempX, sInven[1].Rect.top + TempY, SIN_EFFECT_SHOW_INVEN);
					}

				}

			}
		}
	}


	for (int i = 0; i < MAX_TRADE_ITEM; i++)
	{
		if (sTrade.TradeItem[i].Flag)
		{
			if (sTrade.TradeItem[i].sItemInfo.UniqueItem)
			{
				TempX = rand() % sTrade.TradeItem[i].w;
				TempY = rand() % sTrade.TradeItem[i].h;
				SetInvenParticle(sTrade.TradeItem[i].x + TempX, sTrade.TradeItem[i].y + TempY, SIN_EFFECT_SHOW_TRADE);

			}
		}
		if (sTradeRecv.TradeItem[i].Flag)
		{
			if (sTradeRecv.TradeItem[i].sItemInfo.UniqueItem)
			{
				TempX = rand() % sTradeRecv.TradeItem[i].w;
				TempY = rand() % sTradeRecv.TradeItem[i].h;
				SetInvenParticle(sTradeRecv.TradeItem[i].x + TempX, sTradeRecv.TradeItem[i].y + TempY, SIN_EFFECT_SHOW_TRADE);

			}
		}

	}


	for (int i = cWareHouse.Page * 100; i < cWareHouse.Page * 100 + 100; i++)
	{
		if (sWareHouse.WareHouseItem[i].Flag)
		{
			if (sWareHouse.WareHouseItem[i].sItemInfo.UniqueItem)
			{
				TempX = rand() % sWareHouse.WareHouseItem[i].w;
				TempY = rand() % sWareHouse.WareHouseItem[i].h;
				SetInvenParticle(sWareHouse.WareHouseItem[i].x + TempX, sWareHouse.WareHouseItem[i].y + TempY, SIN_EFFECT_SHOW_WAREHOUSE);
			}
		}
	}
	return TRUE;
}


int cINVENTORY::SetInvenParticle(int x, int y, int Kind)
{

	int i, k;
	int TempSize;
	int Count = 0;

	for (i = 0; i < MAX_INVEN_PARTICLE; i++)
	{
		if (!sInven_Effect[i].Time)
		{
			sInven_Effect[i].Kind = Kind;
			sInven_Effect[i].Time = 1;
			sInven_Effect[i].Max_Time = rand() % 20 + 3;

			sInven_Effect[i].InvenFace.x = x;
			sInven_Effect[i].InvenFace.y = y;
			TempSize = rand() % 13 + 1;
			sInven_Effect[i].InvenFace.width = TempSize;
			sInven_Effect[i].InvenFace.height = TempSize;


			sInven_Effect[i].Speed.y = rand() % 12 + 3;

			if (Kind == SIN_EFFECT_SHOW_GYUNGFUM)
			{
				sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[4];



				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand() % 55 + 200;
				sInven_Effect[i].FadeType = 1;
				if (sInven_Effect[i].InvenFace.width > 5)
				{
					sInven_Effect[i].InvenFace.width -= 2;
					sInven_Effect[i].InvenFace.height -= 2;

				}
				if (sInven_Effect[i].InvenFace.width < 5)
				{
					memset(&sInven_Effect[i], 0, sizeof(sINVENTORY_EFFECT));

				}

			}
			else
			{
				sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[0];



				sInven_Effect[i].InvenFace.r = 255;
				sInven_Effect[i].InvenFace.g = 255;
				sInven_Effect[i].InvenFace.b = 255;
				sInven_Effect[i].InvenFace.Transparency = rand() % 55 + 200;
				sInven_Effect[i].FadeType = 1;
			}

			if (Kind == 1)
			{
				for (k = 0; k < MAX_INVEN_PARTICLE; k++)
				{
					if (!sInven_Effect[k].Time)
					{
						Count++;
						if (Count > 2)
						{
							Count = 0;
							break;

						}
						memcpy(&sInven_Effect[k], &sInven_Effect[i], sizeof(sINVENTORY_EFFECT));
					}

				}
			}
			break;
		}

	}

	return TRUE;
}

DWORD dwInvenParticleMoveTime = 0;

int cINVENTORY::MoveInvenParticle()
{
	dwInvenParticleMoveTime++;
	if (dwInvenParticleMoveTime <= 5)return FALSE;
	dwInvenParticleMoveTime = 0;

	int i = 0;
	for (i = 0; i < MAX_INVEN_PARTICLE; i++)
	{
		if (sInven_Effect[i].Time)
		{
			sInven_Effect[i].Time++;

			sInven_Effect[i].InvenFace.y -= sInven_Effect[i].Speed.y;

			if (sInven_Effect[i].FadeType == 1)
				sInven_Effect[i].InvenFace.Transparency += 14;
			if (sInven_Effect[i].FadeType == 2)
				sInven_Effect[i].InvenFace.Transparency -= 30;

			if (sInven_Effect[i].InvenFace.Transparency >= 255)
				sInven_Effect[i].FadeType = 2;

			if (sInven_Effect[i].InvenFace.Transparency <= 0)
				sInven_Effect[i].Time = 0;

			if (sInven_Effect[i].Kind != SIN_EFFECT_SHOW_GYUNGFUM)
			{
				if ((sInven_Effect[i].Time % 5) == 0)
				{
					sInven_Effect[i].AniCount++;
					if (sInven_Effect[i].AniCount > 3)sInven_Effect[i].AniCount = 0;
					sInven_Effect[i].InvenFace.MatNum = MatInvenParticle[sInven_Effect[i].AniCount];

				}
			}

			if (sInven_Effect[i].InvenFace.Transparency <= 0)sInven_Effect[i].Time = 0;

		}

	}

	return TRUE;
}


int cINVENTORY::sinDrawInvenTexImage(smFACE2D *Face)
{
	D3DTLVERTEX tlVertex[4];
	int cnt;
	int x, y;
	x = Face->x;
	y = Face->y;
	dsGetDrawOffset(&x, &y);
	for (cnt = 0; cnt < 4; cnt++)

	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(Face->r, Face->g, Face->b, Face->Transparency);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}
	tlVertex[0].sx = (float)x;
	tlVertex[0].sy = (float)y;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;
	tlVertex[1].sx = (float)x + (float)Face->width;
	tlVertex[1].sy = (float)y;
	tlVertex[1].tu = 1;
	tlVertex[1].tv = 0;
	tlVertex[2].sx = (float)x;
	tlVertex[2].sy = (float)y + (float)Face->height;
	tlVertex[2].tu = 0;
	tlVertex[2].tv = 1;
	tlVertex[3].sx = ((float)x + (float)Face->width);
	tlVertex[3].sy = ((float)y + (float)Face->height);
	tlVertex[3].tu = 1;
	tlVertex[3].tv = 1;
	DrawTexture(smMaterial[Face->MatNum].smTexture[0]->lpD3DTexture, tlVertex, true);
	return TRUE;
}


int cINVENTORY::CheckSetEmptyArea(sITEM *pItem)
{
	int cntx, cnty;
	int cx, cy;

	RECT	rect = { 0,0,0,0 };
	int		flag = 0;

	cx = (22 * INVENTORY_BOX_ROW) - pItem->w;
	cy = (22 * INVENTORY_BOX_COL) - pItem->h;


	for (cntx = StartX; cntx <= StartX + cx; cntx += 22)
	{
		for (cnty = StartY; cnty <= StartY + cy; cnty += 22)
		{
			flag = 0;
			for (int i = 0; i < INVENTORY_MAXITEM; i++)
			{
				if (InvenItem[i].Flag)
				{
					rect.left = InvenItem[i].x;
					rect.right = InvenItem[i].x + InvenItem[i].w;
					rect.top = InvenItem[i].y;
					rect.bottom = InvenItem[i].y + InvenItem[i].h;

					if (cntx > rect.left - pItem->w && cntx< rect.right &&
						cnty > rect.top - pItem->h && cnty < rect.bottom)
						flag++;
				}
			}
			if (flag == 0)
			{
				pItem->SetX = cntx;
				pItem->SetY = cnty;
				pItem->ItemPosition = 0;
				return TRUE;

			}
		}
	}

	return FALSE;

}


int cINVENTORY::ResetInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum, DWORD Time)
{
	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].CODE == CODE &&
				InvenItem[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItem[i].sItemInfo.ItemHeader.dwChkSum == CheckSum)
			{
				InvenItem[i].sItemInfo.ItemHeader.dwTime = Time;
				return TRUE;

			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].CODE == CODE &&
				InvenItemTemp[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum == CheckSum)
			{
				InvenItemTemp[i].sItemInfo.ItemHeader.dwTime = Time;
				return TRUE;

			}

		}
	}
	return FALSE;
}


int cINVENTORY::DeleteInvenItemToServer(DWORD CODE, DWORD Head, DWORD CheckSum)
{


	if (MouseItem.Flag && MouseItem.CODE == CODE &&
		MouseItem.sItemInfo.ItemHeader.Head == Head &&
		MouseItem.sItemInfo.ItemHeader.dwChkSum == CheckSum)
	{
		MouseItem.Flag = 0;
	}

	int i = 0;
	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].CODE == CODE &&
				InvenItem[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItem[i].sItemInfo.ItemHeader.dwChkSum == CheckSum)
			{
				InvenItem[i].Flag = 0;
				if (InvenItem[i].ItemPosition)
				{

					if (InvenItem[i].Class == ITEM_CLASS_WEAPON_TWO)
					{
						if (InvenItem[i].ItemPosition == 1)
						{
							if (InvenItem[i].CODE != InvenItem[sInven[1].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
								InvenItem[i].Flag = 0;
								sInven[1].ItemIndex = 0;
								sInven[0].ItemIndex = 0;
								if (InvenItem[i].SetModelPosi)
									sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

							}
						}
						if (InvenItem[i].ItemPosition == 2)
						{
							if (InvenItem[i].CODE != InvenItem[sInven[0].ItemIndex - 1].CODE)
							{
								InvenItem[sInven[0].ItemIndex - 1].Flag = 0;
								InvenItem[i].Flag = 0;
								sInven[0].ItemIndex = 0;
								sInven[1].ItemIndex = 0;
								if (InvenItem[i].SetModelPosi)
									sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

							}
						}

					}
					sInven[InvenItem[i].ItemPosition - 1].ItemIndex = 0;
					if (InvenItem[i].SetModelPosi)
						sinSetCharItem(InvenItem[i].CODE, InvenItem[i].SetModelPosi, FALSE);

				}
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				SetItemToChar();
				break;

			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].CODE == CODE &&
				InvenItemTemp[i].sItemInfo.ItemHeader.Head == Head &&
				InvenItemTemp[i].sItemInfo.ItemHeader.dwChkSum == CheckSum)
			{
				InvenItemTemp[i].Flag = 0;
				ReFormInvenItem();
				ReformCharForm();
				ReFormPotionNum();
				SetItemToChar();
				break;

			}
		}
	}


	if (!sInven[0].ItemIndex)
	{
		if (sInven[1].ItemIndex)
		{
			if (InvenItem[sInven[1].ItemIndex - 1].Flag)
			{
				if (InvenItem[sInven[1].ItemIndex - 1].Class == ITEM_CLASS_WEAPON_TWO)
				{
					if (!InvenItem[sInven[1].ItemIndex - 1].sItemInfo.ItemHeader.Head)
					{
						InvenItem[sInven[1].ItemIndex - 1].Flag = 0;
						sInven[1].ItemIndex = 0;
						ReFormInvenItem();
						ReformCharForm();
						ReFormPotionNum();
						SetItemToChar();
					}
				}
			}
		}
	}
	cInvenTory.CheckWeight();
	return TRUE;
}


int cINVENTORY::HackCharStateCheck(smCHAR_INFO *pChar_Info, smCHAR_INFO *desChar_Info)
{
	int HackFlag = 0;

	if (pChar_Info->Attack_Damage[0] < desChar_Info->Attack_Damage[0])
	{
		HackFlag = 1;

	}
	if (pChar_Info->Attack_Damage[1] < desChar_Info->Attack_Damage[1])
	{
		HackFlag = 1;

	}
	if (pChar_Info->Defence < desChar_Info->Defence)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Absorption < desChar_Info->Absorption)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Accuracy < desChar_Info->Accuracy)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Attack_Speed < desChar_Info->Attack_Speed)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Chance_Block < desChar_Info->Chance_Block)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Critical_Hit < desChar_Info->Critical_Hit)
	{
		HackFlag = 1;

	}
	if (pChar_Info->Shooting_Range < desChar_Info->Shooting_Range)
	{
		HackFlag = 1;

	}
	if (HackFlag)
	{
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = OpCode::OPCODE_FIX_ATTACK;
		smTransCommand.WParam = pChar_Info->Attack_Damage[1];
		smTransCommand.LParam = pChar_Info->Defence;
		smTransCommand.SParam = (int)(pChar_Info->Absorption * 256);
		smTransCommand.EParam = 0;
		if (smWsockDataServer)
			smWsockDataServer->Send((char *)&smTransCommand, smTransCommand.size, TRUE);

		return FALSE;
	}
	return TRUE;
}


int cINVENTORY::CheckResetInvenItem()
{
	RECT rect;
	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].ItemPosition)
			{
				if (!sInven[InvenItem[i].ItemPosition - 1].ItemIndex || sInven[InvenItem[i].ItemPosition - 1].ItemIndex - 1 != i)continue;
				rect.left = sInven[InvenItem[i].ItemPosition - 1].Rect.left;
				rect.top = sInven[InvenItem[i].ItemPosition - 1].Rect.top;
				rect.right = sInven[InvenItem[i].ItemPosition - 1].Rect.right;
				rect.bottom = sInven[InvenItem[i].ItemPosition - 1].Rect.bottom;

				if (InvenItem[i].x <	rect.left || InvenItem[i].y < rect.top ||
					InvenItem[i].x + InvenItem[i].w > rect.right + 2 || InvenItem[i].y + InvenItem[i].h > rect.bottom + 2)
				{

					InvenItem[i].x = rect.left + (((rect.right - rect.left) - InvenItem[i].w) / 2);
					InvenItem[i].y = rect.top + (((rect.bottom - rect.top) - InvenItem[i].h) / 2);
					ReFormInvenItem();
				}
			}

		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].ItemPosition)
			{
				rect.left = sInven[InvenItemTemp[i].ItemPosition - 1].Rect.left;
				rect.top = sInven[InvenItemTemp[i].ItemPosition - 1].Rect.top;
				rect.right = sInven[InvenItemTemp[i].ItemPosition - 1].Rect.right;
				rect.bottom = sInven[InvenItemTemp[i].ItemPosition - 1].Rect.bottom;

				if (InvenItemTemp[i].x <	rect.left || InvenItemTemp[i].y < rect.top ||
					InvenItemTemp[i].x + InvenItemTemp[i].w > rect.right + 2 || InvenItemTemp[i].y + InvenItemTemp[i].h > rect.bottom + 2)
				{

					InvenItemTemp[i].x = rect.left + (((rect.right - rect.left) - InvenItemTemp[i].w) / 2);
					InvenItemTemp[i].y = rect.top + (((rect.bottom - rect.top) - InvenItemTemp[i].h) / 2);
					ReFormInvenItem();

				}
			}
		}
	}
	return TRUE;
}


int cINVENTORY::SearchItemCode(DWORD CODE, int KindFlag)
{
	int ItemCount = 0;
	if (CODE)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)ItemCount++;
			}
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)ItemCount++;
			}
		}
		return ItemCount;
	}

	if (KindFlag)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].sItemInfo.ItemKindCode == KindFlag)ItemCount++;
			}
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].sItemInfo.ItemKindCode == KindFlag)ItemCount++;
			}
		}
		return ItemCount;
	}
	return FALSE;
}


int cINVENTORY::CheckDamage()
{
	int Damage[2] = { 0,0 };
	int Critical = 0;
	int SendDamage[2] = { 0,0 };
	int SendCritical = 0;
	int RealDamage[2] = { 0,0 };
	int RealSendCritical = 0;

	int i = 0, j = 0, k = 0, t = 0;

	DWORD WeaponCode[9] = { sinWA1,sinWS1,sinWP1,sinWS2,sinWT1,sinWM1,sinWM1,sinWD1,sinWN1 };
	int   CharCode[9] = { JOBCODE_FIGHTER, JOBCODE_ARCHER, JOBCODE_PIKEMAN, JOBCODE_KNIGHT, JOBCODE_ATALANTA, JOBCODE_PRIESTESS, JOBCODE_MAGICIAN,JOBCODE_ASSASSINE,JOB_CODE_SHAMAN };

	sITEM *pItem = 0;
	pItem = new sITEM;
	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		Damage[0] = 0; Damage[1] = 0; Critical = 0;
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			if (InvenItem[i].NotUseFlag)continue;
			memcpy(pItem, &InvenItem[i], sizeof(sITEM));

		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			if (InvenItemTemp[i - 100].NotUseFlag)continue;
			memcpy(pItem, &InvenItemTemp[i - 100], sizeof(sITEM));
		}
		if (pItem->sItemInfo.Damage[0] || pItem->sItemInfo.Damage[1] || pItem->sItemInfo.Critical_Hit)
		{
			Damage[0] += pItem->sItemInfo.Damage[0];
			Damage[1] += pItem->sItemInfo.Damage[1];
			Critical += pItem->sItemInfo.Critical_Hit;


			if ((sinDamageFunction[0] == 1 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3)))
			{
				SendDamage[0] = 1 + (Damage[0] * (sinChar->Strength + 130) / 130) +
					((sinChar->Talent + sinChar->Dexterity) / 40) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Strength + 130) / 130) +
					((sinChar->Talent + sinChar->Dexterity) / 40);
			}

			if ((sinDamageFunction[0] == 2 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3)))
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Strength + 150) / 150) +
					((sinChar->Talent + sinChar->Dexterity) / 45) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Strength + 150) / 150) +
					((sinChar->Talent + sinChar->Dexterity) / 45);
			}
			if ((sinDamageFunction[0] == 3 && (pItem->WeaponClass == 1 || pItem->WeaponClass == 3)))
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Strength + 190) / 190) +
					((sinChar->Talent + sinChar->Dexterity) / 50) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Strength + 190) / 190) +
					((sinChar->Talent + sinChar->Dexterity) / 50);
			}
			if (sinDamageFunction[1] == 1 && pItem->WeaponClass == 2)
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Dexterity + 130) / 130) +
					((sinChar->Talent + sinChar->Strength) / 40) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Dexterity + 130) / 130) +
					((sinChar->Talent + sinChar->Strength) / 40);
			}

			if (sinDamageFunction[1] == 2 && pItem->WeaponClass == 2)
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Dexterity + 190) / 190) +
					((sinChar->Talent + sinChar->Strength) / 50) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Dexterity + 190) / 190) +
					((sinChar->Talent + sinChar->Strength) / 50);
			}



			if (sinDamageFunction[2] == 1 && pItem->WeaponClass == 3)
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Spirit + 150) / 150) +
					((sinChar->Talent) / 30) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Spirit + 150) / 150) +
					((sinChar->Talent) / 30);
			}

			if (sinDamageFunction[2] == 2 && pItem->WeaponClass == 3)
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Spirit + 180) / 180) +
					((sinChar->Talent) / 30);
				SendDamage[1] = 2 + (Damage[1] * (sinChar->Spirit + 180) / 180) +
					((sinChar->Talent) / 25);
			}
			if (sinDamageFunction[2] == 2 && pItem->WeaponClass == 3)
			{

				SendDamage[0] = 1 + (Damage[0] * (sinChar->Spirit + 170) / 170) +
					((sinChar->Talent) / 30) + ((Damage[0] + Damage[1]) / 16);
				SendDamage[1] = 3 + (Damage[1] * (sinChar->Spirit + 170) / 170) +
					((sinChar->Talent) / 30);
			}


			for (j = 0; j < 9; j++)
			{
				if (CharCode[j] == sinChar->JOB_CODE)
				{
					if (WeaponCode[j] == (pItem->sItemInfo.CODE & sinITEM_MASK2))
					{
						SendDamage[0] += sinChar->Level / 6;
						SendDamage[1] += sinChar->Level / 6;
					}
				}
			}

			if (sinChar->JOB_CODE == JOBCODE_MECHANICIAN)
			{
				if (sinChar->JobBitMask & pItem->sItemInfo.JobCodeMask)
				{
					SendDamage[0] += sinChar->Level / 6;
					SendDamage[1] += sinChar->Level / 6;
				}
			}




			for (k = 1; k < MAX_USESKILL; k++)
			{
				if (sinSkill.UseSkill[k].Flag && sinSkill.UseSkill[k].Point)
				{

					for (t = 0; t < 8; t++)
					{
						switch (sinSkill.UseSkill[k].CODE)
						{
						case SKILL_MELEE_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2))
							{
								SendDamage[0] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[0]);
								SendDamage[1] += (int)(((float)Melee_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[1]);
							}
							break;
						case SKILL_SHOOTING_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2))
							{
								SendDamage[0] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[0]);
								SendDamage[1] += (int)(((float)S_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[1]);

							}
							break;
						case SKILL_THROWING_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2))
							{
								SendDamage[0] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[0]);
								SendDamage[1] += (int)(((float)T_Mastery_Damage[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[1]);
							}
							break;
						case SKILL_CRITICAL_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2))
							{
								Critical += Critical_Mastery_Critical[sinSkill.UseSkill[k].Point - 1];

							}
							break;
						case SKILL_SWORD_MASTERY:
							if (sinSkill.UseSkill[k].Skill_Info.UseWeaponCode[t] == (pItem->sItemInfo.CODE&sinITEM_MASK2))
							{
								SendDamage[0] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[0]);
								SendDamage[1] += (int)(((float)Sword_Mastery_DamagePercent[sinSkill.UseSkill[k].Point - 1] / 100)*pItem->sItemInfo.Damage[1]);

							}
							break;

						}
					}
				}
			}


			if (sinChar->JobBitMask & pItem->sItemInfo.JobCodeMask)
			{
				if (pItem->sItemInfo.JobItem.Lev_Damage[1])
					SendDamage[1] += (sinChar->Level / pItem->sItemInfo.JobItem.Lev_Damage[1]);
				if (pItem->sItemInfo.JobItem.Add_Critical_Hit)
					Critical += pItem->sItemInfo.JobItem.Add_Critical_Hit;
			}
			SendCritical = Critical;
			SendDamage[0] += 1;
			SendDamage[1] += 1;

			if (RealDamage[0] < SendDamage[0])
			{
				RealDamage[0] = SendDamage[0];
			}
			if (RealDamage[1] < SendDamage[1])
			{
				RealDamage[1] = SendDamage[1];
			}
			if (RealSendCritical < SendCritical)
				RealSendCritical = SendCritical;
		}
	}


	SendMaxDamageToServer(RealDamage[0], RealDamage[1], RealSendCritical);
	return TRUE;
}


int cINVENTORY::ClearQuestItem()
{
	sITEM *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinMA2)
		{
			pItem->Flag = 0;
		}
	}
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}


int cINVENTORY::DeleteCoupleRing()
{
	sITEM *pItem = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			pItem = &InvenItemTemp[i - 100];
		}
		if (pItem->sItemInfo.CODE == (sinSP1 | sin16))
		{
			pItem->Flag = 0;
			break;
		}
	}
	cInvenTory.ReFormInvenItem();
	ResetInvenItemCode();
	return TRUE;
}


int cINVENTORY::RecvLinkCore(sITEMINFO *pItemInfo)
{
	sITEMINFO *pItemInfo2 = 0;
	for (int i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			pItemInfo2 = &InvenItem[i].sItemInfo;
		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			pItemInfo2 = &InvenItemTemp[i - 100].sItemInfo;
		}
		if (pItemInfo->BackUpChkSum == pItemInfo2->BackUpChkSum &&
			pItemInfo->BackUpKey == pItemInfo2->BackUpKey &&
			pItemInfo->CODE == pItemInfo2->CODE)
		{
			memcpy(pItemInfo2, pItemInfo, sizeof(sITEMINFO));
			CheckWeight();
			ReFormInvenItem();
			return TRUE;

		}
	}
	return FALSE;
}

int sinMousePotionNum[4] = { 0,0,0,0 };
int ChecMousekPotionNum[4] = { 0,0,0,0 };


int cINVENTORY::CheckMousePotionNumForm()
{
	for (int k = 0; k < 4; k++)
	{
		ChecMousekPotionNum[k] = 0;

	}

	if (MouseItem.Flag)
	{
		if (MouseItem.Class == ITEM_CLASS_POTION)
		{
			switch (MouseItem.sItemInfo.CODE & sinITEM_MASK3)
			{
			case sin01:
				ChecMousekPotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin02:
				ChecMousekPotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin03:
				ChecMousekPotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin04:
				ChecMousekPotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		if (ChecMousekPotionNum[j] != sinMousePotionNum[j])
		{

			SendSetHackUser2(1510, j);


		}

	}

	return TRUE;
}


int cINVENTORY::ReFormMousePotionNum()
{
	for (int j = 0; j < 4; j++)
	{
		sinMousePotionNum[j] = 0;

	}
	if (MouseItem.Flag)
	{
		if (MouseItem.Class == ITEM_CLASS_POTION)
		{
			switch (MouseItem.sItemInfo.CODE & sinITEM_MASK3)
			{
			case sin01:
				sinMousePotionNum[0] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin02:
				sinMousePotionNum[1] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin03:
				sinMousePotionNum[2] += MouseItem.sItemInfo.PotionCount;

				break;
			case sin04:
				sinMousePotionNum[3] += MouseItem.sItemInfo.PotionCount;

				break;
			}
		}
	}
	return TRUE;
}


int cINVENTORY::SetUnionCoreEffect(int x, int y)
{
	for (int i = 0; i < 10; i++)
	{
		if (!UnionCore_Effect_Bone[i].Flag)
		{
			UnionCore_Effect_Bone[i].DesPosi.x = x + 22;
			UnionCore_Effect_Bone[i].DesPosi.y = y;
			UnionCore_Effect_Bone[i].Flag = 1;
			UnionCore_Effect_Bone[i].Posi.y -= 350;


			UnionCore_Effect_Bone[i].InvenFace.MatNum = *(int *)AssaSearchRes("par2.tga", SMMAT_BLEND_ALPHA);






			UnionCore_Effect_Bone[i].Max_Time = 100;
			UnionCore_Effect_Bone[i].InvenFace.r = 255;
			UnionCore_Effect_Bone[i].InvenFace.g = 255;
			UnionCore_Effect_Bone[i].InvenFace.b = 255;
			UnionCore_Effect_Bone[i].InvenFace.Transparency = 255;
			UnionCore_Effect_Bone[i].InvenFace.height = 32;
			UnionCore_Effect_Bone[i].InvenFace.width = 32;
			UnionCore_Effect_Bone[i].InvenFace.TexRect = sinTexRect;
			UnionCore_Effect_Bone[i].Flag = 1;

		}
	}
	return TRUE;
}

int cINVENTORY::UnionCoreParticleProcess()
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		if (UnionCore_Effect_Bone[i].Flag)
		{
			UnionCore_Effect_Bone[i].Time += GetRandomPos(1, 3);
			UnionCore_Effect_Bone[i].Posi.y += 30;
			UnionCore_Effect_Bone[i].InvenFace.y = UnionCore_Effect_Bone[i].Posi.y;
			UnionCore_Effect_Bone[i].Posi.x = UnionCore_Effect_Bone[i].DesPosi.x - 5;
			UnionCore_Effect_Bone[i].InvenFace.x = UnionCore_Effect_Bone[i].Posi.x;

			if (UnionCore_Effect_Bone[i].Posi.y <= UnionCore_Effect_Bone[i].DesPosi.y - 10)
				UnionCoreParticle(UnionCore_Effect_Bone[i].Posi.x, UnionCore_Effect_Bone[i].Posi.y);

			if (UnionCore_Effect_Bone[i].Posi.y >= UnionCore_Effect_Bone[i].DesPosi.y)
			{
				UnionCoreParticle2(UnionCore_Effect_Bone[i].InvenFace.x, UnionCore_Effect_Bone[i].InvenFace.y);
				memset(&UnionCore_Effect_Bone[i], 0, sizeof(sINVENTORY_EFFECT));

			}
		}
	}


	for (i = 0; i < 100; i++)
	{
		if (UnionCore_Effect[i].Flag)
		{
			UnionCore_Effect[i].Time++;
			if (UnionCore_Effect[i].Direction == 1)
				UnionCore_Effect[i].InvenFace.x -= GetRandomPos(0, 1);
			else UnionCore_Effect[i].InvenFace.x += GetRandomPos(0, 1);





			if (UnionCore_Effect[i].Time >= UnionCore_Effect[i].Max_Time)
			{
				memset(&UnionCore_Effect[i], 0, sizeof(sINVENTORY_EFFECT));
			}
		}
	}


	for (i = 0; i < 50; i++)
	{
		if (UnionCore_Effect_Bomb[i].Flag)
		{
			UnionCore_Effect_Bomb[i].Time++;









			if (UnionCore_Effect_Bomb[i].Time >= UnionCore_Effect_Bomb[i].Max_Time)
			{
				memset(&UnionCore_Effect_Bomb[i], 0, sizeof(sINVENTORY_EFFECT));
			}

		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (sUCore_Effect[i].Flag)
		{
			sUCore_Effect[i].Time++;
			if (sUCore_Effect[i].Time > 0)
			{
				sUCore_Effect[i].h += 2;
				sUCore_Effect[i].w += 2;
				sUCore_Effect[i].x--;
				sUCore_Effect[i].y--;
				sUCore_Effect[i].Alpha -= 6;
			}

			if (sUCore_Effect[i].Time > sUCore_Effect[i].Max_Time)
			{
				memset(&sUCore_Effect[i], 0, sizeof(sUNIONCORE_EFFECT));
			}
		}
	}




	return TRUE;
}

int cINVENTORY::UnionCoreParticle(int x, int y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!UnionCore_Effect[i].Flag)
		{

			UnionCore_Effect[i].InvenFace.MatNum = *(int *)AssaSearchRes("par2.tga", SMMAT_BLEND_ALPHA);
			UnionCore_Effect[i].InvenFace.x = x + GetRandomPos(-3, 3);
			UnionCore_Effect[i].InvenFace.y = y + GetRandomPos(-15, 15);
			UnionCore_Effect[i].Max_Time = GetRandomPos(8, 15);
			UnionCore_Effect[i].InvenFace.r = 255;
			UnionCore_Effect[i].InvenFace.g = 255;
			UnionCore_Effect[i].InvenFace.b = 255;
			UnionCore_Effect[i].InvenFace.Transparency = 255;
			UnionCore_Effect[i].InvenFace.height = GetRandomPos(10, 11);
			UnionCore_Effect[i].InvenFace.width = UnionCore_Effect[i].InvenFace.height;
			UnionCore_Effect[i].InvenFace.TexRect = sinTexRect;
			UnionCore_Effect[i].Flag = 1;
			if ((i % 2) == 0)
				UnionCore_Effect[i].Direction = 1;
			else UnionCore_Effect[i].Direction = -1;

			break;

		}
	}
	return TRUE;
}


int cINVENTORY::UnionCoreParticle2(int x, int y, int Flag)
{

	int Count = 0;
	for (int i = 0; i < 10; i++)
	{
		if (!sUCore_Effect[i].Flag)
		{
			if (Flag)
				sUCore_Effect[i].MatNum = MatInterEffectAging[0];
			else
				sUCore_Effect[i].MatNum = MatUnionCoreEffect;

			sUCore_Effect[i].x = x + 12;
			sUCore_Effect[i].y = y;
			sUCore_Effect[i].Max_Time = 40;
			sUCore_Effect[i].Alpha = 255;
			sUCore_Effect[i].w = 20;
			sUCore_Effect[i].h = 20;
			sUCore_Effect[i].Flag = 1;

			Count++;
			if (Count > 1)break;

		}
	}



	return TRUE;
}


int cINVENTORY::CheckInvenEmpty(sITEM *pItem)
{
	if (pItem->CODE == (sinGG1 | sin01) || pItem->CODE == (sinGG1 | sin02))
	{
		return TRUE;
	}

	char szFilePath[256];

	for (int j = 0; j < MAX_ITEM; j++)
	{
		if (pItem->CODE == sItem[j].CODE)
		{
			wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);

			if (!sItem[j].lpTempItem)
			{
				sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
			}

			pItem->lpItem = sItem[j].lpTempItem;
			pItem->w = sItem[j].w;
			pItem->h = sItem[j].h;
		}

	}

	memcpy(&cTrade.CheckItem, &cInvenTory.InvenItem, sizeof(sITEM) * 100);

	if (cTrade.TradeCheckEmptyArea(pItem))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


int cINVENTORY::LoadMoneyExpImage(sITEM *pItem)
{

	if (pItem->CODE == (sinGG1 | sin01))
	{
		if (!lpGold7)lpGold7 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Gold7.bmp");
		pItem->lpItem = lpGold7;

	}
	if (pItem->CODE == (sinGG1 | sin02))
	{
		if (!lpExp7)lpExp7 = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Exp7.bmp");
		pItem->lpItem = lpExp7;

	}
	pItem->w = 44;
	pItem->h = 44;
	return TRUE;
}


int cINVENTORY::SetInvenToItemInfo(sITEMINFO *pItemInfo)
{


	if (pItemInfo->CODE == (sinGG1 | sin01))
	{
		CheckCharForm();
		sinPlusMoney(pItemInfo->Money);
		ReformCharForm();
		SendSaveMoney();
		sinPlaySound(SIN_SOUND_COIN);
		return TRUE;
	}


	if (pItemInfo->CODE == (sinGG1 | sin02))
	{
		AddExp(pItemInfo->Money);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		return TRUE;

	}


	sITEM TempItem;
	if (LoadItemImage(pItemInfo, &TempItem))
	{
		if (cInvenTory.CheckRequireItemToSet(&TempItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
			{
				TempItem.Flag = 0;
				return FALSE;
			}
		}
	}
	return TRUE;
}


int cINVENTORY::sinWingQuestNpc()
{

	sITEM *pItem = 0;
	int   Index = 0;
	int   i = 0;

	WingItemQuestIndex = 0;
	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!InvenItem[i].Flag)continue;
			pItem = &InvenItem[i];
		}
		else
		{
			if (!InvenItemTemp[i - 100].Flag)continue;
			pItem = &InvenItemTemp[i - 100];
		}
		switch (pItem->sItemInfo.CODE)
		{
		case (sinQW1 | sin01):
			Index = 1;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(sITEM));

			break;
		case (sinQW1 | sin02):
			Index = 2;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(sITEM));

			break;
		case (sinQW1 | sin03):
			Index = 3;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(sITEM));
			break;
		case (sinQW1 | sin04):
			Index = 4;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(sITEM));
			break;
		case (sinQW1 | sin05):
			Index = 5;
			memcpy(&sWingItem_Send.DesCraftItem, pItem, sizeof(sITEM));
			break;
		case (sinQW1 | sin06):
			if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
				if (WingItemQuestIndex = 1000)
					cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_b[6]);
			return FALSE;

			break;
		}
	}
	int CodeCount = 0;
	int ItemCount = 0;

	for (int j = 0; j < 6; j++)
	{
		if (sWingQuest[Index].NeedItemCode[j])
		{
			CodeCount++;
			for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
			{
				if (i < 100)
				{
					if (!InvenItem[i].Flag)continue;
					pItem = &InvenItem[i];
				}
				else
				{
					if (!InvenItemTemp[i - 100].Flag)continue;
					pItem = &InvenItemTemp[i - 100];
				}
				if (sWingQuest[Index].NeedItemCode[j] == pItem->sItemInfo.CODE)
				{
					sWingItem_Send.SheltomCode[ItemCount] = pItem->sItemInfo.CODE;
					sWingItem_Send.Head[ItemCount] = pItem->sItemInfo.ItemHeader.Head;
					sWingItem_Send.CheckSum[ItemCount] = pItem->sItemInfo.ItemHeader.dwChkSum;
					ItemCount++;
					break;
				}
			}
		}
	}


	if (CodeCount == ItemCount && sinChar->Money >= sWingQuest[Index].Money)
	{
		WingItemQuestIndex = Index;
		sWingItem_Send.Index = Index;
		sWingItem_Send.Money = sWingQuest[Index].Money;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_b[Index]);
	}
	else
	{
		WingItemQuestIndex = 1000;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_a[Index]);
	}

	return TRUE;
}


int cINVENTORY::CheckRequireItemToSet2(sITEM *pItem)
{
	int NotUseItemFlag = 0;

	if (pItem->sItemInfo.Level > sinChar->Level)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Dexterity > sinChar->Dexterity)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Strength > sinChar->Strength)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Talent > sinChar->Talent)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Spirit > sinChar->Spirit)NotUseItemFlag = 1;
	if (pItem->sItemInfo.Health > sinChar->Health)NotUseItemFlag = 1;
	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinFO1)
	{
		int i = 0;
		for (i = 0; i < 15; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == SheltomCode2[i])
			{
				break;
			}
		}
		if (sinChar->Level < ForceOrbUseLevel[i][0] ||
			sinChar->Level > ForceOrbUseLevel[i][1])
		{
			NotUseItemFlag = 1;
		}
		else
		{
			NotUseItemFlag = 0;

		}

	}

	if (NotUseItemFlag)
	{
		return FALSE;
	}
	return TRUE;
}


int cINVENTORY::CheckSpecialItemPosi()
{
	int j = 0;
	for (int i = 0; i < 84; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
			{
				for (j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (!InvenItem[j].Flag)
					{
						memcpy(&InvenItem[j], &InvenItem[i], sizeof(sITEM));
						memset(&InvenItem[i], 0, sizeof(sITEM));

					}
				}
			}
		}
		if (InvenItemTemp[i].Flag)
		{
			if (InvenItemTemp[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
			{
				for (j = 84; j < INVENTORY_MAXITEM; j++)
				{
					if (!InvenItem[j].Flag)
					{
						memcpy(&InvenItem[j], &InvenItemTemp[i], sizeof(sITEM));
						memset(&InvenItemTemp[i], 0, sizeof(sITEM));

					}
				}
			}
		}

	}
	ReFormInvenItem();
	ReformCharForm();
	ReFormPotionNum();
	SetItemToChar();
	return TRUE;
}


int cINVENTORY::ChangeSpecialItem(int Flag)
{
	if (Flag == 1)
	{
		if (SpecialItemShowFlag)
		{
			SpecialItemShowFlag = 0;

		}
		else return FALSE;
	}
	else if (Flag == 2)
	{
		SpecialItemShowFlag = 0;

	}
	else SpecialItemShowFlag ^= 1;



	for (int i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if (SpecialItemShowFlag)
			{
				if (InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
				{
					if (InvenItem[i].x > 10000)
					{
						InvenItem[i].x -= 10000;
					}
				}
				else
				{
					if (!InvenItem[i].ItemPosition && InvenItem[i].x < 10000)
					{
						InvenItem[i].x += 10000;
					}
				}
			}
			else
			{
				if (InvenItem[i].sItemInfo.SpecialItemFlag[1] == ITEM_KIND_SPECIAL)
				{
					if (InvenItem[i].x < 10000)
					{
						InvenItem[i].x += 10000;
					}
				}
				else
				{
					if (!InvenItem[i].ItemPosition)
					{
						if (InvenItem[i].x > 10000)
						{
							InvenItem[i].x -= 10000;
						}
					}
				}
			}
		}
	}
	return TRUE;
}


int cINVENTORY::SearchItemIndex(DWORD CODE, int KindFlag)
{
	int i = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					return i + 1;

				}
			}
		}
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					return 100 + i + 1;
				}
			}
		}
	}

	if (KindFlag)
	{
		for (int i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].sItemInfo.ItemKindCode == KindFlag)
				{
					return i + 1;

				}
			}
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].sItemInfo.ItemKindCode == KindFlag)
				{
					return 100 + i + 1;

				}
			}
		}
	}
	return FALSE;
}


int WatermelonEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int ValentineEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int CandydaysEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int MagicalGreenEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };
int MagicalGreenEmeraldEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int TearOfKaraEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int FindinvestigatorNineEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };
int FindinvestigatorTaleEventItemIndex[INVENTORY_MAXITEM * 2] = { 0, };


int cINVENTORY::CheckItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					WatermelonEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckValentineItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					ValentineEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckCandyItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					CandydaysEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckMagicalGreenItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckMagicalGreenItemEmeraldCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					MagicalGreenEmeraldEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckTearOfKaraItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					TearOfKaraEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckFindinvestigatorNineItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorNineEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::CheckFindinvestigatorTaleItemCount(DWORD CODE)
{
	int i = 0;
	int item_count = 0;
	if (CODE)
	{
		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItem[i].Flag)
			{
				if (InvenItem[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count - 1] = i + 1;
				}
			}
		}

		for (i = 0; i < INVENTORY_MAXITEM; i++)
		{
			if (InvenItemTemp[i].Flag)
			{
				if (InvenItemTemp[i].CODE == CODE)
				{
					item_count++;
					FindinvestigatorTaleEventItemIndex[item_count - 1] = 100 + i + 1;
				}
			}
		}
	}

	return item_count;
}


int cINVENTORY::ChangePuzzle(sITEM *pItem)
{
	char szTestBuff2[256];
	szTestBuff2[0] = 0;
	if ((pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 || (pItem->sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
	{
		if (pItem->sItemInfo.PotionCount <= 1)
		{
			pItem->sItemInfo.PotionCount = 2;
			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (pItem->sItemInfo.CODE == sItem[j].CODE)
				{
					CheckInvenItemForm();

					wsprintf(szTestBuff2, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
					sItem[j].lpTempItem = LoadDibSurfaceOffscreen(szTestBuff2);
					pItem->lpItem = sItem[j].lpTempItem;
					pItem->w = sItem[j].w;
					pItem->h = sItem[j].h;
					pItem->CODE = sItem[j].CODE;
					CheckWeight();
					ReFormInvenItem();
					sinMinusMoney(1000);
					ReformCharForm();
					SendSaveMoney();
					sinUsePotionDelayFlag = 1;
					cInvenTory.UnionCoreParticle2(pItem->x, pItem->y, 1);
					cInvenTory.UnionCoreParticle2(pItem->x, pItem->y, 1);
					cInvenTory.UnionCoreParticle2(pItem->x, pItem->y, 1);

					sinPlaySound(SIN_SOUND_EAT_POTION2);
					SaveGameData();
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

DWORD CheckPuzzleIndex[4][4] = {
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};


DWORD CheckPuzzleIndex2[4][4] = {
	{sin01,0,sin02,0},
	{sin03,sin04,0,sin06},
	{0,sin05,0,0},
	{sin07,0,sin08,0},
};

DWORD CheckPuzzleX[4] = { 8,9,10,11 };
int   PuzzleIndex[8] = { 0, };


int cINVENTORY::CheckPuzzle()
{
	int Count = 0;
	int Count2 = 0;
	int i, j, k;
	PuzzleOkFlag = 0;
	for (int p = 0; p < 8; p++)
	{
		PuzzleIndex[p] = 0;

	}

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (InvenItem[i].Flag)
		{
			if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1)
			{
				for (j = 0; j < 4; j++)
				{
					for (k = 0; k < 4; k++)
					{
						if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK3) == CheckPuzzleIndex[j][k])
						{
							if ((StartX + (CheckPuzzleX[k] * 22)) == InvenItem[i].x &&
								(StartY + (j * 22)) == InvenItem[i].y)
							{
								PuzzleIndex[Count] = i + 1;
								Count++;

							}
						}
					}
				}
			}

			if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
			{
				for (j = 0; j < 4; j++)
				{
					for (k = 0; k < 4; k++)
					{
						if ((InvenItem[i].sItemInfo.CODE & sinITEM_MASK3) == CheckPuzzleIndex2[j][k])
						{
							if ((StartX + (CheckPuzzleX[k] * 22)) == InvenItem[i].x &&
								(StartY + (j * 22)) == InvenItem[i].y)
							{
								PuzzleIndex[Count2] = i + 1;
								Count2++;

							}
						}
					}
				}
			}
		}
	}
	if (Count == 8 || Count2 == 8)
	{


		PuzzleOkFlag = 1;

	}
	return TRUE;
}


int cINVENTORY::CheckEventItem()
{

	int ItemIndex = SearchItemIndex((sinGF1 | sin02), 0);
	if (ItemIndex && ItemIndex < 100)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_EVENTITEM_SEND, BabelHorn);
		return TRUE;
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), BabelEventDoc);
	cMessageBox.ShowMessage3(MESSAGE_FALLGAME, FallGameName);
	return TRUE;
}


int cINVENTORY::SendEventItem()
{
	int Count = 0;
	int ItemIndex = 0;
	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin02), 0);
	if (ItemIndex && ItemIndex < 100)
	{
		if (sinChar->Weight[0] + 30 > sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;

		}
		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItemInfo.CODE;
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.Head;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.dwChkSum;
	}

	sWingItem_Send.DocIndex = 2;
	return TRUE;

}


int cINVENTORY::CheckFoxEventItem()
{

	int ItemIndex = SearchItemIndex((sinGF1 | sin03), 0);
	int ItemIndex2 = SearchItemIndex((sinGF1 | sin04), 0);

	if (ItemIndex && ItemIndex < 100 && ItemIndex2 && ItemIndex2 < 100)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_FOXEVENTITEM_SEND, NineTailFoxItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), NineTailFoxDoc);
	return TRUE;
}


int cINVENTORY::SendFoxEventItem()
{
	int Count = 0;
	int ItemIndex = 0;
	int ItemIndex2 = 0;
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin03), 0);
	ItemIndex2 = SearchItemIndex((sinGF1 | sin04), 0);
	if (ItemIndex && ItemIndex < 100 && ItemIndex2 && ItemIndex2 < 100)
	{
		if (sinChar->Weight[0] + 100 > sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;

		}

		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItemInfo.CODE;
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.Head;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.dwChkSum;

		sWingItem_Send.SheltomCode[1] = InvenItem[ItemIndex2 - 1].sItemInfo.CODE;
		sWingItem_Send.Head[1] = InvenItem[ItemIndex2 - 1].sItemInfo.ItemHeader.Head;
		sWingItem_Send.CheckSum[1] = InvenItem[ItemIndex2 - 1].sItemInfo.ItemHeader.dwChkSum;

	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;

}


int cINVENTORY::CheckChristMasEventItem()
{

	int ItemIndex = SearchItemIndex((sinGF1 | sin05), 0);

	if (ItemIndex && ItemIndex < 100)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);

	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), StarDustDoc);
	return TRUE;
}


int cINVENTORY::SendChristmasEventItem()
{
	int Count = 0;
	int ItemIndex = 0;

	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;


	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));

	ItemIndex = SearchItemIndex((sinGF1 | sin05), 0);

	if (ItemIndex && ItemIndex < 100)
	{
		if (sinChar->Weight[0] + 100 > sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;

		}

		if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
			return FALSE;
		}
		sWingItem_Send.SheltomCode[0] = InvenItem[ItemIndex - 1].sItemInfo.CODE;
		sWingItem_Send.Head[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.Head;
		sWingItem_Send.CheckSum[0] = InvenItem[ItemIndex - 1].sItemInfo.ItemHeader.dwChkSum;

	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;


}


int cINVENTORY::CheckSendPuzzle()
{
	int Count = 0;
	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
	for (int i = 0; i < 8; i++)
	{
		if (PuzzleIndex[i] && InvenItem[PuzzleIndex[i] - 1].Flag)
		{
			if ((InvenItem[PuzzleIndex[i] - 1].sItemInfo.CODE & sinITEM_MASK2) == sinPZ1 ||
				(InvenItem[PuzzleIndex[i] - 1].sItemInfo.CODE & sinITEM_MASK2) == sinPZ2)
			{
				sWingItem_Send.SheltomCode[i] = InvenItem[PuzzleIndex[i] - 1].sItemInfo.CODE;
				sWingItem_Send.Head[i] = InvenItem[PuzzleIndex[i] - 1].sItemInfo.ItemHeader.Head;
				sWingItem_Send.CheckSum[i] = InvenItem[PuzzleIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;
				Count++;
			}
		}
	}
	if (Count == 8)
	{

		DWORD Temp = 0;
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				if (j == k)continue;
				if (sWingItem_Send.SheltomCode[j] == sWingItem_Send.SheltomCode[k])
				{
					cMessageBox.ShowMessage(MESSAGE_FAILD_PUZZLE);
					return FALSE;

				}
			}
		}
	}
	else
	{
		cMessageBox.ShowMessage(MESSAGE_FAILD_PUZZLE);
		return FALSE;
	}
	if (sinChar->Weight[0] + 120 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;

	}
	sWingItem_Send.DocIndex = 1;
	return TRUE;
}

int cINVENTORY::SendPuzzleNpc()
{

	if (PuzzleOkFlag)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_PUZZLE_SEND, PuzzleEvent5);
	}
	else
	{
		WingItemQuestIndex = 1000;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_WING, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), WingQuestFilePath_a[6]);
	}
	return TRUE;
}


int cINVENTORY::IncreViewDamage(int Persent, int Num)
{
	ViewDamagePercent = Persent;
	ViewDamageNum = Num;
	SetItemToChar();
	return TRUE;
}


int cINVENTORY::DrawForceOrbEffect(int x, int y)
{


	int i = 0;
	char *Path = "image\\Sinimage\\Effect\\ForceOrb\\P_0%d.tga";
	char szBuff[128];
	if (!MatForceOrbEffect[0])
	{
		for (i = 0; i < 8; i++)
		{
			wsprintf(szBuff, Path, i + 1);
			MatForceOrbEffect[i] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

		}
		ReadTextures();
	}



	ForceOrb_Effect.InvenFace.MatNum = MatForceOrbEffect[ForceOrbEffectIndex];
	ForceOrb_Effect.InvenFace.x = x - 5;
	ForceOrb_Effect.InvenFace.y = y - 5;
	ForceOrb_Effect.InvenFace.r = 255;
	ForceOrb_Effect.InvenFace.g = 255;
	ForceOrb_Effect.InvenFace.b = 255;
	ForceOrb_Effect.InvenFace.Transparency = 255;
	ForceOrb_Effect.InvenFace.height = 32;
	ForceOrb_Effect.InvenFace.width = 32;
	ForceOrb_Effect.InvenFace.TexRect = sinTexRect;

	sinDrawInvenTexImage(&ForceOrb_Effect.InvenFace);
	return TRUE;
}


int cINVENTORY::UseForceOrb(sITEM *pItem, int Flag)
{

	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		return FALSE;


	if (sinItemPickUpDelayFlag)return FALSE;
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	int i = 0;
	if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
	{
		for (i = 0; i < 14; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == SheltomCode2[i])
			{
				if (sinChar->Level >= ForceOrbUseLevel[i][0] &&
					sinChar->Level <= ForceOrbUseLevel[i][1])
				{
					UseFlag = i + 1;
				}
			}
		}

		if (!UseFlag)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB);
			return FALSE;

		}
	}
	else
	{
		for (i = 0; i < 14; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == SheltomCode2[i])
			{
				UseFlag = i + 1;

			}
		}
	}

	if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB2);
		return FALSE;
	}




	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.UseTime = ForceOrbUseTime[UseFlag - 1];
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	pItem->sItemInfo.PotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->Flag = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}


int cINVENTORY::UseMagicForceOrb(sITEM *pItem, int Flag)
{
	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		return FALSE;


	if (sinItemPickUpDelayFlag)return FALSE;
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	int i = 0;
	if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
	{
		for (i = 0; i < 12; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == MagicSheltomCode[i])
			{
				if (sinChar->Level >= ForceOrbUseLevel[i][0] && sinChar->Level <= ForceOrbUseLevel[i][1])
				{
					UseFlag = i + 1;
				}
			}
		}

		if (!UseFlag)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB);
			return FALSE;

		}
	}
	else
	{
		for (i = 0; i < 12; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == MagicSheltomCode[i])
			{
				UseFlag = i + 1;

			}
		}
	}

	if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB2);
		return FALSE;
	}


	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128] = { 0 };
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.ElementIndex = 2000;
	TempSkill.UseTime = MagicForceOrbUseTime[UseFlag - 1];
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	pItem->sItemInfo.PotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->Flag = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}


int cINVENTORY::UseBillingMagicForceOrb(sITEM *pItem, int Flag)
{
	if (lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_VILLAGE)
		return FALSE;


	if (sinItemPickUpDelayFlag)return FALSE;
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	int i = 0;
	if (smConfig.getSecurity() < AccountTypes::SEC_MODERATOR)
	{
		for (i = 0; i < 3; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == BillingMagicSheltomCode[i])
			{
				if (sinChar->Level >= BillingMagicForceOrbUseLevel[i][0] && sinChar->Level <= BillingMagicForceOrbUseLevel[i][1])
				{
					UseFlag = i + 1;
				}
			}
		}

		if (!UseFlag)
		{
			cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB);
			return FALSE;

		}
	}
	else
	{
		for (i = 0; i < 3; i++)
		{
			if ((pItem->CODE&sinITEM_MASK3) == BillingMagicSheltomCode[i])
			{
				UseFlag = i + 1;

			}
		}
	}

	if (cSkill.SearchContiueSkill(SKILL_FORCE_ORB))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_USE_FORCEORB2);
		return FALSE;
	}


	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatBillingMagicForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag + 34);
		MatBillingMagicForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.ElementIndex = 1000;
	TempSkill.UseTime = BillingMagicForceOrbUseTime[UseFlag - 1];
	TempSkill.MatIcon = MatBillingMagicForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	pItem->sItemInfo.PotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->Flag = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}


int cINVENTORY::SetMagicForceOrb(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	for (int i = 0; i < 14; i++)
	{
		if ((ItemCODE&sinITEM_MASK3) == MagicSheltomCode[i])
		{
			UseFlag = i + 1;
		}
	}

	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag + 20);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.ElementIndex = 2000;
	TempSkill.UseTime = MagicForceOrbUseTime[UseFlag - 1];
	TempSkill.CheckTime = (MagicForceOrbUseTime[UseFlag - 1] * 70) - (Time * 70);
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	return TRUE;

}


int cINVENTORY::SetBillingMagicForceOrb(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	for (int i = 0; i < 3; i++)
	{
		if ((ItemCODE&sinITEM_MASK3) == BillingMagicSheltomCode[i])
		{
			UseFlag = i + 1;
		}
	}

	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag + 34);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.ElementIndex = 1000;
	TempSkill.UseTime = BillingMagicForceOrbUseTime[UseFlag - 1];
	TempSkill.CheckTime = (BillingMagicForceOrbUseTime[UseFlag - 1] * 70) - (Time * 70);
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	return TRUE;

}


int cINVENTORY::SetForceOrb(DWORD ItemCODE, int Time)
{
	int UseFlag = 0;
	sSKILL TempSkill;
	memset(&TempSkill, 0, sizeof(sSKILL));

	for (int i = 0; i < 14; i++)
	{
		if ((ItemCODE&sinITEM_MASK3) == SheltomCode2[i])
		{
			UseFlag = i + 1;

		}
	}
	char *Path = "image\\Sinimage\\skill\\ForceOrb\\FOS_0%d.tga";
	char szBuff[128];
	if (!MatForceOrb[UseFlag - 1])
	{
		wsprintf(szBuff, Path, UseFlag);
		MatForceOrb[UseFlag - 1] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}


	TempSkill.CODE = SKILL_FORCE_ORB;
	TempSkill.Point = UseFlag;
	TempSkill.UseTime = ForceOrbUseTime[UseFlag - 1];
	TempSkill.CheckTime = (ForceOrbUseTime[UseFlag - 1] * 70) - (Time * 70);
	TempSkill.MatIcon = MatForceOrb[UseFlag - 1];
	sinContinueSkillSet(&TempSkill);
	return TRUE;
}


int cINVENTORY::UseCapsuleItem(sITEM *pItem)
{

	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	if (pItem->CODE == (sinSP1 | sin34))
	{
		if (sinChar->Weight[0] + 5 >= sinChar->Weight[1])
		{
			cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
			return FALSE;
		}
	}

	bGiftBoxDelay = true;


	if (sinActionPotion())
	{
		pUsePotion = &InvenItem[SelectInvenItemIndex - 1];
		cInvenTory.ReFormInvenItem();
		cInvenTory.CheckWeight();
		sinUsePotionDelayFlag = 1;
	}

	return TRUE;
}

int CristalEventItemIndex[7] = { 0, };

int PristonAlphabetEventItemIndex[7] = { 0, };


int cINVENTORY::CheckCristalEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		CristalEventItemIndex[i] = 0;
	}


	for (i = 0; i < 12; i++)
	{
		if (cnt < 7)
		{
			if (CristalEventItemIndex[cnt] == 0)
			{
				CristalEventItemIndex[cnt] = SearchItemIndex(CristalEventCODE[i], 0);
			}
			if (CristalEventItemIndex[cnt] != 0)
				cnt++;
		}
	}

	if (cnt == 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_CRISTALEVENTITEM_SEND, CristalItem);

	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), CristalEventDoc);

	return TRUE;
}


int cINVENTORY::SendCristalEventItem()
{

	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 100 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (CristalEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[CristalEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (CristalEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[CristalEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[CristalEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[CristalEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::CheckWatermelonEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		WatermelonEventItemIndex[i] = 0;
	}

	cnt = CheckItemCount(WatermelonEventCODE);


	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_WATERMELON_EVENTITEM, StarItem);



	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), StarDoc);



	return TRUE;
}


int cINVENTORY::CheckValentineEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		ValentineEventItemIndex[i] = 0;
	}

	cnt = CheckValentineItemCount(ValentineEventCODE);


	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_VALENTINE_EVENTITEM, ValentineItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), ValentineDoc);


	return TRUE;
}


int cINVENTORY::CheckCandydaysEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		CandydaysEventItemIndex[i] = 0;
	}

	cnt = CheckCandyItemCount(CandydaysEventCODE);


	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_CANDYDAYS_EVENTITEM, CandydaysItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), CandydaysDoc);


	return TRUE;
}


int cINVENTORY::CheckMagicalGreenEventItem()
{
	int i, cnt = 0, cnt2 = 0;
	for (i = 0; i < 7; i++)
	{
		MagicalGreenEventItemIndex[i] = 0;
		MagicalGreenEmeraldEventItemIndex[i] = 0;
	}

	cnt = CheckMagicalGreenItemCount(MagicalGreenEventCODE[0]);
	cnt2 = CheckMagicalGreenItemEmeraldCount(MagicalGreenEventCODE[1]);


	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_MAGICALGREEN_EVENTITEM, MagicalGreenJadeItem);
	}

	else if (cnt2 >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_MAGICALGREEN_EVENTITEM_EMERALD, MagicalGreenEmeraldItem);
	}

	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), MagicalGreenDoc);


	return TRUE;
}


int cINVENTORY::CheckTearOfKaraEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		TearOfKaraEventItemIndex[i] = 0;
	}

	cnt = CheckTearOfKaraItemCount(TeatOfKaraEventCODE);


	if (cnt >= 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_TEAROFKARA_EVENTITEM, TearOfKaraItem);
	}
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), TearOfKaraDoc);


	return TRUE;
}


int cINVENTORY::CheckFindinvestigatorEventItem()
{
	int i, cnt = 0, cnt2 = 0;

	for (i = 0; i < 1; i++)
	{
		FindinvestigatorNineEventItemIndex[i] = 0;
		FindinvestigatorTaleEventItemIndex[i] = 0;
	}

	cnt = CheckFindinvestigatorNineItemCount(FindinvestigatorEventCODE[0]);
	cnt2 = CheckFindinvestigatorTaleItemCount(FindinvestigatorEventCODE[1]);


	if (cnt == 0 && cnt2 == 0)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FIND_EVENTITEM, FindinvestigatorItem);

	}


	else if (cnt == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_2Doc);
	}


	else if (cnt == 0 && cnt2 == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator1_3Doc);
	}

	return TRUE;
}


int cINVENTORY::CheckFindinvestigatorKamiuEventItem()
{
	int i, cnt = 0;

	for (i = 0; i < 1; i++)
	{
		FindinvestigatorNineEventItemIndex[i] = 0;
	}

	cnt = CheckFindinvestigatorNineItemCount(FindinvestigatorEventCODE[0]);


	if (cnt == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator2_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FINDKAMIU_EVENTITEM, FindinvestigatorNineItem);
	}


	else if (cnt == 0)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator2_2Doc);
	}



	return TRUE;
}


int cINVENTORY::CheckFindinvestigatorEtoEventItem()
{
	int i, cnt = 0;

	for (i = 0; i < 1; i++)
	{
		FindinvestigatorTaleEventItemIndex[i] = 0;
	}

	cnt = CheckFindinvestigatorTaleItemCount(FindinvestigatorEventCODE[1]);


	if (cnt == 1)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator3_1Doc);
		cMessageBox.ShowMessage3(MESSAGE_FINDETO_EVENTITEM, FindinvestigatorTaleItem);
	}


	else if (cnt == 0)
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), Findinvestigator3_2Doc);
	}



	return TRUE;
}


int cINVENTORY::SendWatermelonEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 10 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (WatermelonEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[WatermelonEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (WatermelonEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[WatermelonEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendValentineEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 50 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (ValentineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[ValentineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (ValentineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[ValentineEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::CheckPristonAlphabetEventItem()
{
	int i, cnt = 0;
	for (i = 0; i < 7; i++)
	{
		PristonAlphabetEventItemIndex[i] = 0;
	}



	for (i = 0; i < 7; i++)
	{
		if (cnt < 7)
		{
			if (PristonAlphabetEventItemIndex[cnt] == 0)
			{
				PristonAlphabetEventItemIndex[cnt] = SearchItemIndex(PristonAlphabetEventCODE[i], 0);
			}
			if (PristonAlphabetEventItemIndex[cnt] != 0)
				cnt++;
		}
	}



	if (cnt == 7)
	{
		cInterFace.CheckAllBox(SIN_INVENTORY);
		cMessageBox.ShowMessage3(MESSAGE_PRISTON_ALPHABET_EVENTITEM, PristonAlphabetItem);

	}
	else
	{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_BABEL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), PristonAlphabetDoc);
	}
	return TRUE;
}


int cINVENTORY::SendPristonAlphabetEventItem()
{

	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 20 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (PristonAlphabetEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[PristonAlphabetEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (PristonAlphabetEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[PristonAlphabetEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendCandydaysEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 50 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (CandydaysEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[CandydaysEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (CandydaysEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[CandydaysEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendMagicalGreenEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 70 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (MagicalGreenEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[MagicalGreenEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (MagicalGreenEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[MagicalGreenEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendMagicalGreenEmeraldEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 3;
	TempItem.h = 22 * 4;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 70 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (MagicalGreenEmeraldEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[MagicalGreenEmeraldEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (MagicalGreenEmeraldEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[MagicalGreenEmeraldEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendTearOfKaraEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 10 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 7; i++)
	{
		if (TearOfKaraEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[TearOfKaraEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (TearOfKaraEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[TearOfKaraEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::UseSoccerBallPotionItem(sITEM *pItem)
{
	pItem->sItemInfo.PotionCount = 100;
	sinThrowItemToFeild(pItem);
	pItem->Flag = 0;

	cInvenTory.SetItemToChar();
	cInvenTory.ReFormInvenItem();
	cInvenTory.CheckWeight();
	sinUsePotionDelayFlag = 1;
	sinPlaySound(SIN_SOUND_EAT_POTION2);

	return TRUE;
}


int cINVENTORY::SendFindinvestigatorNineEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));



	if (sinChar->Weight[0] + 5 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorNineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (FindinvestigatorNineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendFindinvestigatorTaleEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 5 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorNineEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorNineEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (FindinvestigatorNineEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorNineEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}


int cINVENTORY::SendFindinvestigatorTaleEtoEventItem()
{
	sITEM TempItem;
	TempItem.w = 22 * 2;
	TempItem.h = 22 * 2;

	memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));


	if (sinChar->Weight[0] + 10 > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return FALSE;
	}

	if (!cCraftItem.CraftCheckEmptyArea(&TempItem))
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
		return FALSE;
	}

	for (int i = 0; i < 1; i++)
	{
		if (FindinvestigatorTaleEventItemIndex[i] > 100)
		{
			sWingItem_Send.SheltomCode[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItemTemp[FindinvestigatorTaleEventItemIndex[i] - 100 - 1].sItemInfo.ItemHeader.dwChkSum;
			continue;
		}
		if (FindinvestigatorTaleEventItemIndex[i])
		{
			sWingItem_Send.SheltomCode[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItemInfo.CODE;
			sWingItem_Send.Head[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItemInfo.ItemHeader.Head;
			sWingItem_Send.CheckSum[i] = InvenItem[FindinvestigatorTaleEventItemIndex[i] - 1].sItemInfo.ItemHeader.dwChkSum;

		}
	}
	sWingItem_Send.DocIndex = 2;
	return TRUE;
}

int cINVENTORY::ForceLevelCheck(DWORD	CODE)
{
	int j = 0;
	for (j = 0; j < 19; j++)
	{
		if ((CODE & sinITEM_MASK3) == ForceCode2[j])
		{
			break;
		}
	}
	if (sinChar->Level < ForceOrbUseLevel[j][0] ||
		sinChar->Level > ForceOrbUseLevel[j][1])
	{
		return FALSE;
	}

	return TRUE;
}