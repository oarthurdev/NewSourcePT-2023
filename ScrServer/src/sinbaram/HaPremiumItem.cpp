
#include "sinLinkHeader.h"
#include "..\\field.h"
#include "..\\AreaServer.h"

#include <string>

using namespace std;

cHaPremiumItem  chaPremiumitem;


#define  TELEPORT_FIELDMAX 38
int TelePort_FieldNum[TELEPORT_FIELDMAX][3] = {
	// EXPLICA��O DA FUN��O DO CORE M�GICO
	// EXPLICANDO A PRIMEIRA LINHA, { 0, 20, 0 }, 0 = Posi��o na lista do Core M�gico, 20 = Field 20, 0 = Level para entrar.
	//{ 0, 20, 0 }, // Estrada dos Ventos
	{ 1, 19, 0 }, // Vale Tranquilo
	{ 2, 17, 0 }, // Floresta dos Esp�ritos
	{ 3, 0, 0 }, // Mata das Ac�cias
	{ 4, 2, 0 }, // Jardim da Liberdade
	{ 5, 4, 0 }, // Refugio dos Ancioes
	{ 6, 5, 0 }, // Castelo dos Perdidos
	{ 7, 7, 0 },  // Terra Maldita
	{ 8, 8, 0 }, // Terra Esquecida
	{ 9, 10, 0 }, // Oasis
	{ 10, 11, 55 }, // Campo de Batalha
	{ 11, 12, 55 }, // Terra Proibida
	{ 12, 25, 55 }, // Caverna das Abelhas
	{ 13, 24, 55 }, // Caverna dos Cogumelos
	{ 14, 26, 65 }, // Santu�rio Sombrio 
	{ 15, 13, 40 }, // Calabou�o Antigo 1� Andar 
	{ 16, 14, 50 }, // Calabou�o Antigo 2� Andar
	{ 17, 15, 60 }, // Calabou�o Antigo 3� Andar
	{ 18, 22, 70 }, // Templo Maldito 1� Andar 
	{ 19, 23, 75 }, // Templo Maldito 2� Andar 
	{ 20, 42, 80 }, // Templo Maldito 3� Andar
	{ 21, 34, 70 }, // Lago da Gan�ncia
	{ 22, 27, 80 }, // Estrada de Ferro do Caos
	{ 23, 28, 85 }, // Cora��o de Perum
	{ 24, 29, 90 }, // Eura
	{ 25, 31, 90 }, // Vale Gallubia
	{ 26, 35, 90 }, // Santu�rio Congelado
	{ 27, 36, 90 }, // Covil de Kelvezu 
	{ 28, 37, 95 }, // Ilha Perdida
	{ 29, 38, 100 }, // Templo Perdido
	{ 30, 40, 105 }, // Torre Sem Fim 1o Andar
	{ 31, 41, 110 }, // Torre Sem Fim 2� Andar 
	{ 32, 43, 121 }, // Torre Sem Fim 3� Andar
	{ 33, 44, 125 }, // Mina de Gelo 1� Andar 
	{ 34, 46, 132 }, // Laborat�rio Secreto
	{ 35, 47, 132 }, // Arma Secreta 
	{ 36, 48, 132 }, // Abismo do Mar 1� Andar
	{ 37, 49, 132 } // Abismo do Mar 2� andar
};



char *haTeleport_Field[] = {
	"image\\Sinimage\\help\\haTeleport_Field.sin",
};

cHaPremiumItem::cHaPremiumItem()
{
	TelePortCore.PageButtonFlag[0] = 0;
	TelePortCore.PageButtonFlag[1] = 0;
	TelePortCore.FieldIndex[0] = 0;
	TelePortCore.FieldIndex[1] = 0;
	TelePortCore.PageIndex = 0;
	Using_ItemKind = 0;
	Using_SelectInvenItemIndex = 0;
	int i;
	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		UpKeepItem[i].PosiX = 0;
		UpKeepItem[i].PosiY = 0;
		UpKeepItem[i].Visible = false;
		UpKeepItem[i].IconTime[0] = 0;
		UpKeepItem[i].IconTime[1] = 0;
		UpKeepItem[i].Alpha = 255;
		UpKeepItem[i].Alphakind = 0;
		UpKeepItem[i].Per = 0;
		memset(UpKeepItem[i].Id, NULL, sizeof(UpKeepItem[i].Id));
	}

	UseClickPremiumItemFlag = false;


	m_ThirdEyesTime = 0;
	m_ExpUpPotionTime = 0;
	m_VampiricCuspidTime = 0;
	m_ManaRechargingPTime = 0;
	m_ManaReducePotiontime = 0;
	m_ManaReducePotionValue = 0;
	m_MightofAwellTime = 0;
	m_MightofAwellWeight = 0;
	m_PhenixPetTime = 0;
	m_HelpPetTime = 0;
	m_VampiricCuspidEXTime = 0;
	m_StaminaReducePotiontime = 0;
	m_StaminaReducePotionValue = 0;
	m_BigHeadTime = 0;
	m_AwellPowerTime = 0;
	m_MigalPoweTime = 0;
	m_HPBoosterTime = 0;
	m_MPBoosterTime = 0;
	m_SPBoosterTime = 0;
	m_RecoverSPTime = 0;
	m_BDivinaTime = 0;
	m_ForceTime = 0;
	m_ForceType = 0;

}

cHaPremiumItem::~cHaPremiumItem()
{







}


void cHaPremiumItem::init()
{

	UpKeepItemTGAImage[0] = CreateTextureMaterial("image\\Sinimage\\Premium\\ThirdEyes.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[1] = CreateTextureMaterial("image\\Sinimage\\Premium\\ExpUpPotion.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[2] = CreateTextureMaterial("image\\Sinimage\\Premium\\Vampiric.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[3] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Rechar.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	UpKeepItemTGAImage[4] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Might.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[5] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Reduce.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[6] = CreateTextureMaterial("image\\Sinimage\\Premium\\M_Phoenix.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[7] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_terry-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[8] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_nepsys-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[9] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet_io-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[10] = CreateTextureMaterial("image\\Sinimage\\Premium\\Pet-mute-pose.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[11] = CreateTextureMaterial("image\\Sinimage\\Premium\\Vampiric_EX.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	UpKeepItemTGAImage[12] = CreateTextureMaterial("image\\Sinimage\\Premium\\S_Reduce.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	lpUpKeepItemBackImage[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\ThirdEyes_Back.bmp");
	lpUpKeepItemBackImage[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\ExpUpPotion_Back.bmp");
	lpUpKeepItemBackImage[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\Vampiric_back.bmp");
	lpUpKeepItemBackImage[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Rechar_back.bmp");

	lpUpKeepItemBackImage[4] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Might_back.bmp");
	lpUpKeepItemBackImage[5] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Reduce_back.bmp");
	lpUpKeepItemBackImage[6] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[7] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[8] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[9] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[10] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\M_Phoenix_back.BMP");
	lpUpKeepItemBackImage[11] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\Vampiric_back_EX.bmp");
	lpUpKeepItemBackImage[12] = LoadDibSurfaceOffscreen("image\\Sinimage\\Premium\\S_Reduce_back.bmp");

	haItemUseDelayFlag = false;
}


int ItemUseLeftPosi[SINUPKEEPITEM_MAX][2] = {
	{8,80},{8,116},{8,152},{8,188},{8,224},{8,260},{8,296}, {8, 332}
};
DWORD dwDelayTime = 0;
void cHaPremiumItem::Main()
{

	if(chaPremiumitem.haItemUseDelayFlag == true)
	{
		dwDelayTime++;
		if(dwDelayTime > 210)
		{
			chaPremiumitem.haItemUseDelayFlag = false;
			dwDelayTime = 0;
		}
	}



	int i, cnt = 0;
	UseClickPremiumItemFlag = false;
	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{

		if(UpKeepItem[i].IconTime[0] < UpKeepItem[i].IconTime[1])
		{
			if(UpKeepItem[i].Visible == true)
			{
				if(UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 0)
				{
					UpKeepItem[i].Visible = false;
					CheckUpKeepItem();
				}
				cnt++;

				DWORD NowTime = GetPlayTime_T();
				switch(UpKeepItem[i].TGAImageNumber)
				{
					case nsPremiumItem::THIRD_EYES:
					if(m_ThirdEyesTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::EXPUP_POTION:
					if(m_ExpUpPotionTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::VAMPIRIC_CUS:
					if(m_VampiricCuspidTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;


					case nsPremiumItem::VAMPIRIC_CUS_EX:
					if(m_VampiricCuspidEXTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;


					case nsPremiumItem::MANA_RECHAR_P:
					if(m_ManaRechargingPTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::MIGHT_OF_AWELL:
					if(m_MightofAwellTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::MANA_REDUCE_P:
					if(m_ManaReducePotiontime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::PHENIX_PET:
					if(m_PhenixPetTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::HELP_PET_TERRY:
					if(m_HelpPetTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::HELP_PET_NEPSYS:
					if(m_HelpPetTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::HELP_PET_IO:
					if(m_HelpPetTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::HELP_PET_MUTE:
					if(m_HelpPetTime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
					case nsPremiumItem::STAMINA_REDUCE_P:
					if(m_StaminaReducePotiontime > 0)
					{
						UpKeepItem[i].IconTime[0] = NowTime;
					}
					break;
				}
			}
		}
		else
			UpKeepItem[i].Visible = false;
		if(UpKeepItem[i].Visible == true)
		{

			if(UpKeepItem[i].PosiY > ItemUseLeftPosi[cnt - 1][1])
				UpKeepItem[i].PosiY -= 1;
			else
			{
				UpKeepItem[i].PosiY = ItemUseLeftPosi[cnt - 1][1];
				UpKeepItem[i].PosiX = ItemUseLeftPosi[cnt - 1][0];
			}

			if(pCursorPos.x > UpKeepItem[i].PosiX && pCursorPos.x < UpKeepItem[i].PosiX + 30 &&
			   pCursorPos.y > UpKeepItem[i].PosiY && pCursorPos.y < UpKeepItem[i].PosiY + 30)
			{
				UpKeepItem[i].Infoflag = true;
				UseClickPremiumItemFlag = true;
			}
			else
			{
				UpKeepItem[i].Infoflag = false;
				UseClickPremiumItemFlag = false;
			}
		}
	}

	switch(Using_ItemKind)
	{
		case 8:
		if(pCursorPos.x > 100 && pCursorPos.x < 100 + 20 &&
		   pCursorPos.y > 365 && pCursorPos.y < 365 + 20)
			TelePortCore.PageButtonFlag[0] = 1;
		else if(pCursorPos.x > 330 && pCursorPos.x < 330 + 20 &&
				pCursorPos.y > 365 && pCursorPos.y < 365 + 20)
			TelePortCore.PageButtonFlag[1] = 1;
		else
		{
			TelePortCore.PageButtonFlag[0] = 0;
			TelePortCore.PageButtonFlag[1] = 0;
		}
		break;
	}
}

void cHaPremiumItem::Draw()
{

	switch(Using_ItemKind)
	{
		case 8:
		if(TelePortCore.PageButtonFlag[0])
			DrawSprite(100, 365, chaQuest.lpQuestButtonImage[2], 0, 0, 20, 20);
		else
			DrawSprite(100, 365, chaQuest.lpQuestButtonImage[0], 0, 0, 20, 20);
		if(TelePortCore.PageButtonFlag[1])
			DrawSprite(330, 365, chaQuest.lpQuestButtonImage[3], 0, 0, 20, 20);
		else
			DrawSprite(330, 365, chaQuest.lpQuestButtonImage[1], 0, 0, 20, 20);
	}
}

DWORD dwKeepItemTime[6] = { 0, SINITEM_TIME_1HOURS, SINITEM_TIME_3HOURS, SINITEM_TIME_ONEDAY, SINITEM_TIME_SEVENDAY, SINITEM_TIME_30DAY };

int  cHaPremiumItem::CheckTime(DWORD CurrentTime)
{


	for(int i = 0; i < 5; i++)
	{
		if(dwKeepItemTime[i] < CurrentTime  &&  CurrentTime < dwKeepItemTime[i + 1])
		{
			return i + 1;
		}
	}

	return false;
}

void cHaPremiumItem::DrawUp()
{

	int i;
	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if(UpKeepItem[i].Visible == true)
		{
			dsDrawTexImage(UpKeepItemTGAImage[UpKeepItem[i].TGAImageNumber - 1], UpKeepItem[i].PosiX, UpKeepItem[i].PosiY, 32, 32, UpKeepItem[i].Alpha);

			if(UpKeepItem[i].Infoflag == true)
			{
				InfoBox(UpKeepItem[i].PosiX + 30, UpKeepItem[i].PosiY, 10, 6);
			}

			int    MinLen = 0;
			DWORD  dwCurrentTime = UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0];
			switch(UpKeepItem[i].TGAImageNumber)
			{
				case nsPremiumItem::THIRD_EYES:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_ThirdEyesTime = 0;
				}

				break;
				case nsPremiumItem::EXPUP_POTION:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_ExpUpPotionTime = 0;
				}

				break;
				case nsPremiumItem::MIGHT_OF_AWELL:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}
				break;
				case nsPremiumItem::MANA_REDUCE_P:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;

				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_ManaReducePotiontime = 0;
					chaPremiumitem.m_ManaReducePotionValue = 0;
					chaPremiumitem.SetManaReducePotionTime(chaPremiumitem.m_ManaReducePotiontime);
				}
				break;


				case nsPremiumItem::VAMPIRIC_CUS:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;

				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_VampiricCuspidTime = 0;
				}
				break;


				case nsPremiumItem::VAMPIRIC_CUS_EX:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;

				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_VampiricCuspidEXTime = 0;
				}
				break;


				case nsPremiumItem::MANA_RECHAR_P:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_ManaRechargingPTime = 0;
					chaPremiumitem.SetManaRechargingPTime(chaPremiumitem.m_ManaRechargingPTime);
				}
				break;

				case nsPremiumItem::STAMINA_REDUCE_P:
				switch(CheckTime(dwCurrentTime))
				{
					case 1:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_1HOURS / 32));
					break;
					case 2:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_3HOURS / 32));
					break;
					case 3:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_ONEDAY / 32));
					break;
					case 4:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_SEVENDAY / 32));
					break;
					case 5:
					MinLen = (32 - (dwCurrentTime) / (SINITEM_TIME_30DAY / 32));
					break;
				}

				if(dwCurrentTime <= 0)
				{
					chaPremiumitem.m_StaminaReducePotiontime = 0;
					chaPremiumitem.m_StaminaReducePotionValue = 0;
					chaPremiumitem.SetStaminaReducePotionTime(chaPremiumitem.m_StaminaReducePotiontime);
				}
				break;
			}

			if(UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 10)
			{
				if(UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_NEPSYS ||
				   UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_IO || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_MUTE)
				{
					if(UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 0)
					{
						chaPremiumitem.UpKeepItem[i].PosiX = 0;
						chaPremiumitem.UpKeepItem[i].PosiY = 0;
						chaPremiumitem.UpKeepItem[i].Visible = false;
						chaPremiumitem.UpKeepItem[i].TGAImageNumber = 0;
						chaPremiumitem.UpKeepItem[i].IconTime[0] = 0;
						chaPremiumitem.UpKeepItem[i].IconTime[1] = 0;
						chaPremiumitem.UpKeepItem[i].Alpha = 255;
						chaPremiumitem.UpKeepItem[i].Alphakind = 0;
						chaPremiumitem.UpKeepItem[i].Per = 0;
						memset(chaPremiumitem.UpKeepItem[i].Id, NULL, sizeof(chaPremiumitem.UpKeepItem[i].Id));

						m_HelpPetTime = 0;

						sinChar->GravityScroolCheck[1] = 0;
						cHelpPet.ClosePet();
					}
				}

				if(UpKeepItem[i].Alpha == 255)
					UpKeepItem[i].Alphakind = 1;
				if(UpKeepItem[i].Alpha == 50)
					UpKeepItem[i].Alphakind = 2;
			}
			else
			{
				if(UpKeepItem[i].Alpha == 0)
				{
					UpKeepItem[i].Alphakind = 0;
				}
			}
			if(UpKeepItem[i].Alphakind == 0)
			{
				DrawSprite(UpKeepItem[i].PosiX, UpKeepItem[i].PosiY + (32 - MinLen), lpUpKeepItemBackImage[UpKeepItem[i].TGAImageNumber - 1], 0, 32 - MinLen, 32, 32);
			}

			switch(UpKeepItem[i].Alphakind)
			{
				case 0:
				if(UpKeepItem[i].Alpha < 255)
					UpKeepItem[i].Alpha++;
				else
					UpKeepItem[i].Alpha = 255;
				break;
				case 1:
				if(UpKeepItem[i].Alpha > 50)
					UpKeepItem[i].Alpha -= 5;
				else
					UpKeepItem[i].Alpha = 50;
				break;
				case 2:
				if(UpKeepItem[i].Alpha < 255)
					UpKeepItem[i].Alpha += 5;
				else
					UpKeepItem[i].Alpha = 255;
				break;
			}
		}
	}
}

void cHaPremiumItem::LButtonDown(int x, int y)
{

	if(TelePortCore.PageButtonFlag[1])
	{
		if(TelePortCore.PageIndex < 3)
			TelePortCore.PageIndex++;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, RGBA_MAKE(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
	}
	if(TelePortCore.PageButtonFlag[0])
	{
		if(0 < TelePortCore.PageIndex)
			TelePortCore.PageIndex--;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, RGBA_MAKE(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
	}
}

void cHaPremiumItem::LButtonUp(int x, int y)
{

}
DWORD dwPremiumItemCode[] = { (sinBI1 | sin01),(sinBI1 | sin02),(sinBI1 | sin03),(sinBI1 | sin04),(sinBI1 | sin05),(sinBI1 | sin06),(sinBI1 | sin07) };

int cHaPremiumItem::UsePremiumItem(int kind)
{
	Using_ItemKind = 0;
	switch(kind)
	{
		case 1:
		cCharStatus.InitCharStatus(1);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 2:
		cSkill.InitSkillPoint(1);
		haCastleSkillUseFlag = 1;
		break;
		case 3:
		cSkill.InitSkillPoint(1);
		cCharStatus.InitCharStatus(1);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 5:
		SetPremiumItemSkill(1);
		cInvenTory.SetItemToChar();
		break;
		case 6:
		SetPremiumItemSkill(2);
		break;
		case 7:
		SetPremiumItemSkill(3);
		break;
		case 8:
		if(!CheckWindowOpen())break;
		Using_ItemKind = kind;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y,
							 RGBA_MAKE(0, 15, 128, 125), haTeleport_Field[TelePortCore.PageIndex]);
		haCastleSkillUseFlag = 0;
		HelpBoxKindIndex = 0;

		break;
		case 9:
		haCastleSkillUseFlag = 1;
		break;
		case 10:
		case 11:
		haCastleSkillUseFlag = 0;
		break;
		case 12:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_12HOURS, true, UpKeepItemName[0], 50);

		break;
		case 13:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 30);

		break;
		case 14:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 50);

		break;
		case 15:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 30);

		break;
		case 16:
		if(UseHairtintPotion(1))
			haCastleSkillUseFlag = 1;
		break;
		case 17:
		if(UseHairtintPotion(2))
			haCastleSkillUseFlag = 1;
		break;
		case 18:
		if(UseHairtintPotion(3))
			haCastleSkillUseFlag = 1;
		break;
		case 19:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, SINITEM_TIME_12HOURS, true, UpKeepItemName[2]);
		SetVampiricCuspidTime(SINITEM_TIME_12HOURS);
		break;
		case 20:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, SINITEM_TIME_ONEDAY, true, UpKeepItemName[2]);
		SetVampiricCuspidTime(SINITEM_TIME_ONEDAY);
		break;
		case 21:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, SINITEM_TIME_12HOURS, true, UpKeepItemName[3]);
		SetManaRechargingPTime(SINITEM_TIME_12HOURS);
		break;
		case 22:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[3]);
		SetManaRechargingPTime(SINITEM_TIME_ONEDAY);
		break;
		case 23:
		haCastleSkillUseFlag = 1;
		break;

		case 24:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_12HOURS, true, UpKeepItemName[0], 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 10);

		break;
		case 25:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 10);

		break;
		case 26:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 10);

		break;
		case 27:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[0], 20, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 10);

		break;
		case 28:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 20);

		break;
		case 29:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[0], 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 20);

		break;
		case 30:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[0], 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 20);


		break;
		case 31:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_30DAY, true, UpKeepItemName[0], 30, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, UpKeepItemName[1], 20);

		break;

		case 32:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_12HOURS, true, UpKeepItemName[0], 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 30);

		break;

		case 33:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 30);

		break;
		case 34:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[0], 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 30);

		break;
		case 35:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_30DAY, true, UpKeepItemName[0], 40, 1))
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, UpKeepItemName[1], 30);
		break;


		case 36:
		if(UseHairtintPotion(4))
			haCastleSkillUseFlag = 1;
		break;
		case 37:
		if(UseHairtintPotion(5))
			haCastleSkillUseFlag = 1;
		break;
		case 38:
		if(UseHairtintPotion(6))
			haCastleSkillUseFlag = 1;
		break;
		case 39:
		if(
			UseHairtintPotion(7))
			haCastleSkillUseFlag = 1;
		break;
		case 40:
		if(UseHairtintPotion(8))
			haCastleSkillUseFlag = 1;
		break;



		case 41:
		if(UseHairtintPotion(9))
			haCastleSkillUseFlag = 1;
		break;
		case 42:
		if(UseHairtintPotion(10))
			haCastleSkillUseFlag = 1;
		break;
		case 43:
		if(UseHairtintPotion(11))
			haCastleSkillUseFlag = 1;
		break;
		case 44:
		if(UseHairtintPotion(12))
			haCastleSkillUseFlag = 1;
		break;
		case 45:
		if(UseHairtintPotion(13))
			haCastleSkillUseFlag = 1;
		break;


		case 46:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 50);

		break;
		case 47:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 50);
		break;
		case 48:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[4], 300);
		break;
		case 49:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_30DAY, true, UpKeepItemName[4], 300);
		break;
		case 50:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[5], 30);
		break;
		case 51:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[5], 30);
		break;
		case 52:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_12HOURS, true, UpKeepItemName[5], 10, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 10);
		}
		break;
		case 53:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_12HOURS, true, UpKeepItemName[5], 10, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 10);
		}
		break;
		case 54:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_12HOURS, true, UpKeepItemName[5], 10, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 10);
		}
		break;
		case 55:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_12HOURS, true, UpKeepItemName[5], 20, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_12HOURS, true, UpKeepItemName[1], 20);
		}
		break;
		case 56:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[5], 20, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 20);
		}
		break;
		case 57:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[5], 20, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 20);
		}
		break;
		case 58:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, UpKeepItemName[5], 30, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, UpKeepItemName[1], 30);
		}
		break;
		case 59:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[5], 30, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 30);
		}
		break;
		case 60:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[5], 30, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 30);
		}
		break;
		case 61:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_3HOURS, true, UpKeepItemName[5], 40, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_3HOURS, true, UpKeepItemName[1], 40);
		}
		break;
		case 62:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[5], 40, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 40);
		}
		break;
		case 63:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[5], 40, 2))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 40);
		}
		break;
		case 64:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[4], 500);
		break;
		case 65:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_ONEDAY, true, UpKeepItemName[4], 500);
		break;
		case 66:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 50, 1))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 40);
		}
		break;
		case 67:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 50, 1))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 40);
		}
		break;
		case 68:
		haCastleSkillUseFlag = 1;
		if(SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_ONEDAY, true, UpKeepItemName[0], 50, 1))
		{
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 40);
		}
		break;
		case 69:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[6], 30);


		break;
		case 70:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[6], 30);
		break;
		case 71:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_3HOURS, true, UpKeepItemName[6], 30);
		break;



		case 73:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(0);
		break;
		case 74:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(1);
		break;
		case 75:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(2);
		break;
		case 76:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(1);
		break;
		case 77:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(2);
		break;
		case 78:
		haCastleSkillUseFlag = 1;
		UseSkillMaster(3);
		break;
		case 79:
		haCastleSkillUseFlag = 1;
		cInvenTory.InvenItem[Using_SelectInvenItemIndex].sItemInfo.PotionCount = 300;
		sinThrowItemToFeild(&cInvenTory.InvenItem[Using_SelectInvenItemIndex]);
		cInvenTory.InvenItem[Using_SelectInvenItemIndex].Flag = 0;
		cInvenTory.CheckWeight();
		cInvenTory.ReFormInvenItem();
		SaveGameData();
		UseMoveShop();
		break;
		case 80:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_ONEDAY, true, UpKeepItemName[1], 100);
		break;
		case 81:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[1], 100);
		break;
		case 82:
		cCharStatus.InitCharStatus_Attribute(1);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 83:
		cCharStatus.InitCharStatus_Attribute(2);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 84:
		cCharStatus.InitCharStatus_Attribute(3);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 85:
		cCharStatus.InitCharStatus_Attribute(4);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 86:
		cCharStatus.InitCharStatus_Attribute(5);
		cInvenTory.SetItemToChar();
		if(sinChar->Life[1] < sinGetLife())
		{
			sinSetLife(sinChar->Life[1]);
			ReformCharForm();
			ResetEnergyGraph(4);
		}
		haCastleSkillUseFlag = 1;
		break;
		case 87:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_30DAY, true, UpKeepItemName[1], 100);
		break;
		case 88:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30);
		break;

		/*case 95:
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30);
			break;
		case 96:
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30);
			break;
		case 97:
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30);
			break;
		case 98:
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30);
			break;
			*/

		haCastleSkillUseFlag = 0;
		break;
		case 99:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_30DAY, true, UpKeepItemName[7], 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
		case 100:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_30DAY, true, UpKeepItemName[8], 30, 3);
		break;
		case 101:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_30DAY, true, UpKeepItemName[9], 30, 3);
		break;
		case 102:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_30DAY, true, UpKeepItemName[10], 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;

		case 103:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_ONEDAY, true, UpKeepItemName[7], 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
		case 104:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_ONEDAY, true, UpKeepItemName[8], 30, 3);
		break;
		case 105:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_ONEDAY, true, UpKeepItemName[9], 30, 3);
		break;
		case 106:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_ONEDAY, true, UpKeepItemName[10], 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;

		case 107:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_1HOURS, true, UpKeepItemName[1], 100);
		break;

		case 108:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::PHENIX_PET, SINITEM_TIME_1HOURS, true, UpKeepItemName[6], 30);
		break;

		case 109:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[7], 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
		case 110:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[8], 30, 3);
		break;
		case 111:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[9], 30, 3);
		break;
		case 112:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[10], 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;
		case 113:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(3);
		break;
		case 114:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(4);
		break;
		case 115:
		haCastleSkillUseFlag = 1;
		UseAgingMaster(5);
		break;

		case 116:

		if(sinChar->GravityScroolCheck[0] == 5)
		{
			cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLFAIL);
			return FALSE;
		}

		cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLOK);

		sinChar->GravityScroolCheck[0] += 1;


		cCharStatus.UseGravityScrool();
		cInvenTory.SetItemToChar();
		ReformCharForm();

		haCastleSkillUseFlag = 1;

		break;


		case 117:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_1HOURS, true, UpKeepItemName[7], 30, 3);
		sinChar->GravityScroolCheck[1] = 1;
		break;
		case 118:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_1HOURS, true, UpKeepItemName[8], 30, 3);
		break;
		case 119:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_IO, SINITEM_TIME_1HOURS, true, UpKeepItemName[9], 30, 3);
		break;
		case 120:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_1HOURS, true, UpKeepItemName[10], 30, 3);
		sinChar->GravityScroolCheck[1] = 2;
		break;

		case 121:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::THIRD_EYES, SINITEM_TIME_1HOURS, true, UpKeepItemName[0], 50);

		break;

		case 122:
		haCastleSkillUseFlag = 0;
		break;

		case 123:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::EXPUP_POTION, SINITEM_TIME_1HOURS, true, UpKeepItemName[1], 50);
		break;

		case 124:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS, SINITEM_TIME_1HOURS, true, UpKeepItemName[2]);
		SetVampiricCuspidTime(SINITEM_TIME_1HOURS);
		break;

		case 125:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P, SINITEM_TIME_1HOURS, true, UpKeepItemName[3]);
		SetManaRechargingPTime(SINITEM_TIME_1HOURS);
		break;

		case 126:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_1HOURS, true, UpKeepItemName[5], 30);
		break;

		case 127:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX, SINITEM_TIME_1HOURS, true, UpKeepItemName[11]);
		SetVampiricCuspidEXTime(SINITEM_TIME_1HOURS);
		break;

		case 128:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX, SINITEM_TIME_3HOURS, true, UpKeepItemName[11]);
		SetVampiricCuspidEXTime(SINITEM_TIME_3HOURS);
		break;

		case 129:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX, SINITEM_TIME_ONEDAY, true, UpKeepItemName[11]);
		SetVampiricCuspidEXTime(SINITEM_TIME_ONEDAY);
		break;
		case 130:
		haCastleSkillUseFlag = 0;
		break;
		case 131:
		haCastleSkillUseFlag = 0;
		break;
		case 132:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[12], 30);
		break;
		case 133:
		haCastleSkillUseFlag = 1;
		SetUpKeepItem(nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[12], 30);
		break;
		case 145:
			haCastleSkillUseFlag = 1;
			break;
		case 149:
			if (UseHairtintPotion(19))
				haCastleSkillUseFlag = 1;
			break;
	}
	return TRUE;
}

int cHaPremiumItem::SetPremiumItemSkill(int kind)
{

	haCastleSkillUseFlag = 0;
	DWORD SkillCODE;
	int   SkillTime;
	switch(kind)
	{
		case 1:
		SkillCODE = SCROLL_P_INVULNERABILITY;
		SkillTime = 3;
		break;
		case 2:
		SkillCODE = SCROLL_P_CRITICAL;
		SkillTime = 60 * 60;
		break;
		case 3:
		SkillCODE = SCROLL_P_EVASION;
		SkillTime = 60 * 60;
		break;
	}

	sSKILL TempSkill;

	if(cSkill.SearchContiueSkillCODE(SkillCODE) == SkillCODE && SkillCODE != 0)
	{
		cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
		haCastleSkillUseFlag = 0;
		return TRUE;
	}
	haCastleSkillUseFlag = 1;

	for(int j = 0; j < SIN_MAX_SKILL; j++)
	{
		if(sSkill[j].CODE == SkillCODE)
		{
			memcpy(&TempSkill, &sSkill[j], sizeof(sSKILL));
			TempSkill.UseTime = SkillTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}
	return TRUE;
}

int cHaPremiumItem::UseTeleportScrollItem(short ItemIndex)
{
	if(!chaPremiumitem.TelePortCore.FieldIndex[1])return FALSE;

	if(StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_ROOM)
	{
		cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM);
		return FALSE;
	}

	int i;
	for(i = 0; i < TELEPORT_FIELDMAX; i++)
	{
		if((chaPremiumitem.TelePortCore.FieldIndex[1] - 1) == TelePort_FieldNum[i][0])
		{

			if(TelePort_FieldNum[i][2] <= sinChar->Level)
			{


				WarpField2(TelePort_FieldNum[i][1]);
				cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].sItemInfo.PotionCount = 300;
				sinThrowItemToFeild(&cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex]);
				cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].Flag = 0;
				cInvenTory.CheckWeight();
				cInvenTory.ReFormInvenItem();

			}

			else
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL);
		}
	}
	return TRUE;
}

int cHaPremiumItem::CheckWindowOpen()
{
	haCastleSkillUseFlag = 0;
	if(cWareHouse.OpenFlag)return false;
	if(cTrade.OpenFlag)return false;
	if(cAging.OpenFlag)return false;
	if(cCraftItem.OpenFlag)return false;
	if(sSinWarpGate.ShowFlag)return false;
	if(cSinHelp.NPCTeleportFlag)return false;
	if(isDrawClanMenu)return false;
	if(haMovieFlag)return false;

	if(SmeltingItem.OpenFlag)
	{
		return false;
	}

	if(ManufactureItem.m_OpenFlag)
	{
		return false;
	}
	if(cMixtureReset.OpenFlag)	return false;
	return true;
}

int cHaPremiumItem::CheckUpKeepItem()
{
	int i;

	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if(UpKeepItem[i].Visible == false)
		{
			if(UpKeepItem[i + 1].Visible == true)
			{
				memcpy(&UpKeepItem[i], &UpKeepItem[i + 1], sizeof(sUpKeepItem));
				UpKeepItem[i + 1].Visible = false;
				break;
			}
		}
	}
	return true;
}

int cHaPremiumItem::SetUpKeepItem(int kind, DWORD dwTime, bool visible, char* id, int Percent, short ItemType)
{
	haCastleSkillUseFlag = 0;
	int i;

	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if(m_VampiricCuspidEXTime > 0 && UpKeepItem[i].Visible == false)
		{
			if(UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS_EX)
			{
				UpKeepItem[i].TGAImageNumber = 0;
				UpKeepItem[i].Visible = false;
				haCastleSkillUseFlag = 0;

			}
		}

		if((UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS_EX || UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS) && (m_VampiricCuspidEXTime > 0 || m_VampiricCuspidTime > 0))
		{
			if(kind == 3 || kind == 12)
			{
				cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
				haCastleSkillUseFlag = 0;
				return  FALSE;
			}
		}
	}



	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if(UpKeepItem[i].Visible == false)
		{

			UpKeepItem[i].TGAImageNumber = kind;
			UpKeepItem[i].Visible = true;
			UpKeepItem[i].IconTime[0] = 1;
			UpKeepItem[i].IconTime[1] = GetPlayTime_T() + dwTime;
			UpKeepItem[i].Alpha = 0;
			UpKeepItem[i].Alphakind = 0;
			UpKeepItem[i].Per = Percent;

			strcpy(UpKeepItem[i].Id, id);
			haCastleSkillUseFlag = 1;
			return TRUE;
		}
		else
		{




			switch(ItemType)
			{
				case 0:
				if(UpKeepItem[i].TGAImageNumber == kind)
				{
					cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
					haCastleSkillUseFlag = 0;
					return FALSE;
				}

				break;
				case 1:
				for(int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{
					if(UpKeepItem[j].TGAImageNumber == THIRD_EYES || UpKeepItem[j].TGAImageNumber == EXPUP_POTION)
					{
						cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
				case 2:
				for(int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{
					if(UpKeepItem[j].TGAImageNumber == MANA_REDUCE_P || UpKeepItem[j].TGAImageNumber == EXPUP_POTION)
					{
						cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
				case 3:
				for(int j = 0; j < SINUPKEEPITEM_MAX; j++)
				{


					if(cHelpPet.PetShow == 1)
					{
						cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
						haCastleSkillUseFlag = 0;
						return  FALSE;
					}
				}
				break;
			}
		}
	}
	return TRUE;

}

void cHaPremiumItem::InfoBox(int PoisX, int PosiY, int Width, int Height)
{
	int i, j;
	for(i = 0; i < Width; i++)
	{
		for(j = 0; j < Height; j++)
		{
			if(i == 0 && j == 0)
				dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(j == 0 && i != 0 && i + 1 < Width)
				dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(j == 0 && i + 1 == Width)
				dsDrawTexImage(cItem.MatItemInfoBox_TopRight, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(i == 0 && j != 0 && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Left, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(i != 0 && j != 0 && i + 1 != Width && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Center, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(i + 1 == Width && j != 0 && j + 1 != Height)
				dsDrawTexImage(cItem.MatItemInfoBox_Right, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(i == 0 && j + 1 == Height)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(i != 0 && j + 1 == Height && i + 1 != Width)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
			if(j + 1 == Height && i + 1 == Width)
				dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, PoisX + (i * 16), PosiY + (j * 16), 16, 16, 255);
		}
	}
}

int cHaPremiumItem::DrawText()
{
	HDC	hdc = NULL;
	//renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject(hdc, sinBoldFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	char strBuff[32];
	memset(strBuff, 0, sizeof(strBuff));
	int i, cnt = 0;
	for(i = 0; i < SINUPKEEPITEM_MAX; i++)
	{
		if(cSinHelp.sinGetHelpShowFlag())break;
		if(!CheckWindowOpen())break;
		if(UpKeepItem[i].Visible == true)
		{
			if(UpKeepItem[i].Infoflag == true)
			{
				dsTextLineOut(hdc, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20, UpKeepItem[i].Id, strlen(UpKeepItem[i].Id));
				SelectObject(hdc, sinFont);
				SetTextColor(hdc, RGB(50, 250, 50));
				switch(UpKeepItem[i].TGAImageNumber)
				{
					case nsPremiumItem::THIRD_EYES:
					wsprintf(strBuff, UpKeepItemDoc[1], UpKeepItem[i].Per, "%");
					break;
					case nsPremiumItem::EXPUP_POTION:
					wsprintf(strBuff, UpKeepItemDoc[2], UpKeepItem[i].Per, "%");
					break;
					case nsPremiumItem::VAMPIRIC_CUS:
					wsprintf(strBuff, UpKeepItemDoc[4]);
					break;
					case nsPremiumItem::MANA_RECHAR_P:
					wsprintf(strBuff, UpKeepItemDoc[5]);
					break;
					case nsPremiumItem::MIGHT_OF_AWELL:
					wsprintf(strBuff, UpKeepItemDoc[6], UpKeepItem[i].Per);
					break;
					case nsPremiumItem::MANA_REDUCE_P:
					wsprintf(strBuff, UpKeepItemDoc[7], UpKeepItem[i].Per, "%");
					break;
					case nsPremiumItem::HELP_PET_TERRY:
					wsprintf(strBuff, UpKeepItemDoc[8]);
					break;
					case nsPremiumItem::HELP_PET_NEPSYS:
					wsprintf(strBuff, UpKeepItemDoc[9]);
					break;
					case nsPremiumItem::HELP_PET_IO:
					wsprintf(strBuff, UpKeepItemDoc[10]);
					break;
					case nsPremiumItem::HELP_PET_MUTE:
					wsprintf(strBuff, UpKeepItemDoc[11]);
					break;
					case nsPremiumItem::VAMPIRIC_CUS_EX:
					wsprintf(strBuff, UpKeepItemDoc[12]);
					break;
					case nsPremiumItem::STAMINA_REDUCE_P:
					wsprintf(strBuff, UpKeepItemDoc[13], UpKeepItem[i].Per, "%");
					break;


				}

				dsTextLineOut(hdc, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20 + 30, strBuff, strlen(strBuff));

				wsprintf(strBuff, UpKeepItemDoc[0], (UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0]) / 60);
				dsTextLineOut(hdc, UpKeepItem[i].PosiX + 50, UpKeepItem[i].PosiY + 20 + 46, strBuff, strlen(strBuff));


			}
		}
	}

	//renderDevice.lpDDSBack->ReleaseDC(hdc);
	return TRUE;
}

int cHaPremiumItem::UseHairtintPotion(int ItemKind)
{
	switch (ItemKind) {
	case 1:
		if (ChangeHairModel(0))
			return TRUE;
		break;
	case 2:
		if (ChangeHairModel(1))
			return TRUE;
		break;
	case 3:
		if (ChangeHairModel(2))
			return TRUE;
		break;
	case 4:
		if (ChangeHairModel(3))
			return TRUE;
		break;
	case 5:
		if (ChangeHairModel(4))
			return TRUE;
		break;
	case 6:
		if (ChangeHairModel(5))
			return TRUE;
		break;
	case 7:
		if (ChangeHairModel(6))
			return TRUE;
		break;
	case 8:
		if (ChangeHairModel(7))
			return TRUE;
		break;

	case 9:
		if (ChangeHairModel(8))
			return TRUE;
		break;
	case 10:
		if (ChangeHairModel(9))
			return TRUE;
		break;
	case 11:
		if (ChangeHairModel(10))
			return TRUE;
		break;
	case 12:
		if (ChangeHairModel(11))
			return TRUE;
		break;
	case 13:
		if (ChangeHairModel(12))
			return TRUE;
		break;
	case 14:
		if (ChangeHairModel(17))
			return TRUE;
		break;
	case 15:
		if (ChangeHairModel(18))
			return TRUE;
		break;
	case 16:
		if (ChangeHairModel(19))
			return TRUE;
		break;
	case 17:
		if (ChangeHairModel(20))
			return TRUE;
		break;
	case 18:
		if (ChangeHairModel(21))
			return TRUE;
		break;
	case 19:
		if (ChangeHairModel(23))
			return TRUE;
		break;


	}
	cMessageBox.ShowMessage(MESSAGE_NOT_HAIRTINTPOTION);
	return FALSE;
}


int cHaPremiumItem::UseAgingMaster(int ItemKind)
{
	switch(ItemKind)
	{
		case 0:
		sinCheckAgingLevel(SIN_AGING_ATTACK, true);
		sinCheckAgingLevel(SIN_AGING_CRITICAL, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
		case 1:
		if((cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE &sinITEM_MASK2) == sinDS1)
		{
			sinCheckAgingLevel(SIN_AGING_BLOCK, true);
			ReformCharForm();
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		else if((cInvenTory.InvenItem[sInven[1].ItemIndex - 1].CODE &sinITEM_MASK2) == sinOM1)
		{
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, true);
			ReformCharForm();
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		break;
		case 2:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
		case 3:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
		case 4:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
		case 5:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, true);
		ReformCharForm();
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	}

	return TRUE;
}


int cHaPremiumItem::UseSkillMaster(int ItemKind)
{
	switch(ItemKind)
	{
		case 1:
		for(int j = 1; j < 5; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
		case 2:
		for(int j = 5; j < 9; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
		case 3:
		for(int j = 9; j < 13; j++)
		{
			if(sinSkill.UseSkill[j].UseSkillCount < 10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0, j);
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		sinEffect_Agony(lpCurPlayer);
		break;
	}

	return TRUE;
}


int cHaPremiumItem::UseMoveShop()
{
	if(cShop.OpenFlag == SIN_CLOSE)
	{
		sinShopKind = 1;
		cShop.OpenFlag = SIN_OPEN;
		cShop.UseItemFlag = 1;
	}
	else
	{
		cShop.OpenFlag = SIN_CLOSE;
		cShop.UseItemFlag = 0;
	}

	return TRUE;
}
