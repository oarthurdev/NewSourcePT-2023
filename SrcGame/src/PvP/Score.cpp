#include "Score.h"
#include <string>
#include "FontImage.h"
#include "smLib3d\smDsx.h"
#include "playmain.h"
#include "character.h"
#include "field.h"
#include "hobaram\\holinkheader.h"
#include "sinbaram\\sinlinkheader.h"
#include "Settings\Settings.h"

extern int haSiegeBoardFlag;

Score::Score()
{
	}

Score::~Score()
{

}




void Score::sendAlert()
{
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;

	extern BOOL bReiPVP;
	static unsigned int tick = 0;
	static bool sent = false;

	if (stage == 33 && bReiPVP)
	{

		if((GetTickCount() - tick) > 120000 && !sent)
		{
			smTRANS_COMMAND smPacket;
			smPacket.code = OpCode::SEND_ALERT_PVP;
			smPacket.WParam = 0;
			smPacket.EParam = 0;
			smPacket.size = sizeof(smPacket);

			extern SocketData *smWsockDataServer;

			if(smWsockDataServer)
			{
				smWsockDataServer->Send((char *)&smPacket, smPacket.size, TRUE);
			}

			tick = GetTickCount();
			sent = true;
		}
	}
	else
	{
		if((GetTickCount() - tick) > 120000 && sent)
		{
			sent = !sent;
		}
	}


}

bool Score::drawZone()
{
	int zPosition = lpCurPlayer->pZ >> 0x8;
	char* text = nullptr;
	COLORREF colour = NULL;

	//if(zPosition >= -23840)
	//{
	//	text = "Zona Segura";
	//	colour = D3DCOLOR_RGBA(0, 210, 14, 255); 
	//}
	//else if(zPosition >= -24059 && zPosition < -23840)
	//{
	//	text = "Zona de Perigo";
	//	colour = D3DCOLOR_RGBA(255, 210, 14, 255); 
	//}
	//else
	//{
	//	text = "Zona de Batalha";
	//	colour = D3DCOLOR_RGBA(220, 0, 0, 255); 
	//}

	//DrawFontImage(text, smScreenWidth / 2 - 100, 30, colour, 0.8f);

	//return true;
	int widthPVP;

	if (zPosition >= -23840)
	{
		text = "Zona Segura";
		colour = D3DCOLOR_RGBA(0, 210, 14, 255); // VERDE
		widthPVP = 75;
	}
	else if (zPosition >= -24059 && zPosition < -23840)
	{
		text = "Zona de Perigo";
		colour = D3DCOLOR_RGBA(255, 210, 14, 255); // AMARELO
		widthPVP = 90;
	}
	else
	{
		text = "Zona de Batalha";
		colour = D3DCOLOR_RGBA(220, 0, 0, 255); // VERMELHO
		widthPVP = 95;
	}

	DrawFontImage(text, SETTINGSHANDLER->getWidth() / 2 - widthPVP, 40, colour, 0.8f);

	return true;
}

bool Score::drawScore()
{
	/*DrawFontImage("Pontos de Batalha", smScreenWidth / 2 - 100, 60, D3DCOLOR_RGBA(255, 255, 255, 255), 0.7f);*/
	/*DrawFontImage(const_cast<char*>(std::to_string(lpCurPlayer->sBlessCastle_Damage[1]).c_str()), smScreenWidth / 2 - 40, 90, D3DCOLOR_RGBA(220, 0, 0, 255), 0.7f);*/
	DrawFontImage(const_cast<char*>(std::to_string(lpCurPlayer->sBlessCastle_Damage[1]).c_str()), SETTINGSHANDLER->getWidth() / 2 + 15, 9, D3DCOLOR_RGBA(220, 0, 0, 255), 0.7f);
	return true;
}

bool Score::drawImgPVP()
{
	extern int	imgPVP;


	int WinX = (WinSizeX / 2) - 160, WinY = 0;
	dsDrawTexImage(imgPVP, WinX, WinY, 300 - 1, 80 - 1, 255);
	//dsDrawTexImage(imgPVP, Settings::getInstance()->getWidth() / 2 - 140, 0, 300, 80, 255);
	return true;
}

bool Score::draw()
{
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;
	bool result = false;

	if(stage == 33 && !haSiegeBoardFlag)
	{
		drawImgPVP();
		drawZone();
		drawScore();

		result = true;
	}


	sendAlert();

	return result;
}
