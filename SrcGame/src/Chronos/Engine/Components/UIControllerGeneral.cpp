
#include "UIControllerGeneral.h"
#include "TestUI.h"
#include "CDamageInfo.h"

CUIControllerGeneral::CUIControllerGeneral()
{
}

CUIControllerGeneral::~CUIControllerGeneral()
{
}

void CUIControllerGeneral::CallpFunction(DWORD pFunction, DWORD pClass)
{
	tfnCallUIDraw CallUIDraw = (tfnCallUIDraw)pFunction;
	CallUIDraw(pClass);
}

void CUIControllerGeneral::Init()
{
}

BOOL CUIControllerGeneral::OnMouseClick(CMouse* pcMouse)
{
	BOOL bRet = FALSE;


	return bRet;
}

void CUIControllerGeneral::Render()
{
	WRITEDWORD(DrawOffsetArray, 2);
	CallpFunction(pfnCharStatusDraw, pcCharStatus);
	CallpFunction(pfnCharStatusDrawText, pcCharStatus);

	WRITEDWORD(DrawOffsetArray, 2);
	CallpFunction(pfnSkillDraw, pcSkill);

	WRITEDWORD(DrawOffsetArray, 2);
	CallpFunction(pfnInventoryDraw, pcInventory);
	CallpFunction(pfnInventoryDrawText, pcInventory);

	WRITEDWORD(DrawOffsetArray, 2);
	CallpFunction(pfnInterfaceDraw, pcInterface);
	CallpFunction(pfnInterfaceDrawText, pcInterface);

	if (Game::GetGameMode() == GAMEMODE_InGame)
		GAMESCREEN->Render2D();

	DAMAGEINFOHANDLER->Render();

	WRITEDWORD(DrawOffsetArray, 0);
	TIMERSKILLHANDLER->DrawTimer();

	WRITEDWORD(DrawOffsetArray, 0);
	CallpFunction(pfnShopDraw, pcShop);
	CallpFunction(pfnShopDrawText, pcShop);

	CallpFunction(pfnTradeDraw, pcTrade);
	CallpFunction(pfnTradeDrawText, pcTrade);

	CallpFunction(pfnSocketItemDraw, pcItemSocket);

	WRITEDWORD(DrawOffsetArray, 0);
	CallpFunction(pfnHelpDraw, pcHelp);
	CallpFunction(pfnHelpDrawText, pcHelp);

	CallpFunction(pfnWarpGateDraw, pcWapgate);
	CallpFunction(pfnWarpGateDrawText, pcWapgate);

	CALL(pfnInterfaceEffectDraw);
	WRITEDWORD(DrawOffsetArray, 0);
	CALL(pfnClanMenuDraw);

	WRITEDWORD(DrawOffsetArray, 2);
	CallpFunction(pfnSkillTextDraw, pcSkill);

	WRITEDWORD(DrawOffsetArray, 0);
	CallpFunction(pfnHelpPetDraw, pcHelpPet);
	CallpFunction(pfnHelpPetDrawText, pcHelpPet);

	CallpFunction(pfnPhoenixPetDraw, pcPhoenixPet);
	CallpFunction(pfnPhoenixPetDrawText, pcPhoenixPet);

	CallpFunction(pfnSodDraw, pcSod);
	CallpFunction(pfnSodDrawText, pcSod);

	CallpFunction(pfnSiegeDraw, pcSiege);
	CallpFunction(pfnSiegeDrawText, pcSiege);

	CallpFunction(pfnQuestDraw, pcQuest);

	CallpFunction(pfnPremiumDraw, pcPremiumItem);
	CallpFunction(pfnPremiumDrawText, pcPremiumItem);

	CallpFunction(pfnMessageBoxDraw, pcMessageBox);
	CallpFunction(pfnMessageBoxDrawText, pcMessageBox);

	WRITEDWORD(DrawOffsetArray, 0);

	//Render Skills
	if (READDWORD(0x0367E83C) > 0)
	{
		//FSP
		if (READDWORD(0x0367E054) > 0)
		{
			FONTHANDLER->Draw(0, RECT{ 229, (RESOLUTION_HEIGHT + 56) - WINDOW_SKILLMOVE + 175, 0, 0 }, FormatString("%d", CHARACTERGAME->GetFSP()), DT_NOCLIP, -1);
		}
		else
		{
			//SP & EP
			FONTHANDLER->Draw(0, RECT{ 201, (RESOLUTION_HEIGHT + 56) - WINDOW_SKILLMOVE + 175, 0, 0 }, FormatString("%d", READDWORD(0x03673B70)), DT_NOCLIP, -1);
			FONTHANDLER->Draw(0, RECT{ 244, (RESOLUTION_HEIGHT + 56) - WINDOW_SKILLMOVE + 175, 0, 0 }, FormatString("%d", READDWORD(0x03673B74)), DT_NOCLIP, -1);
		}
	}

	if (READDWORD(0x367DE9C) > 0)
	{
		if (CHARACTERGAME->GetFSP() > 0)
			FONTHANDLER->Draw(0, RECT{ 112, 275, 0, 0 }, FormatString("Fortress Skill Points: %d", CHARACTERGAME->GetFSP()), DT_NOCLIP, D3DCOLOR_XRGB(230, 170, 40));

		int iPoints = READDWORD(0x03673B70) + READDWORD(0x03673B74) + CHARACTERGAME->GetFSP();

		if (iPoints <= 0)
		{
			FONTHANDLER->Draw(0, RECT{ 112, 235, 0, 0 }, "Not enough skill points", DT_NOCLIP, D3DCOLOR_XRGB(220, 0, 0));
			FONTHANDLER->Draw(0, RECT{ 112, 255, 0, 0 }, "to train new skills", DT_NOCLIP, D3DCOLOR_XRGB(220, 0, 0));
		}
	}
}

void CUIControllerGeneral::OnDrawClanInfo(int iX)
{

}