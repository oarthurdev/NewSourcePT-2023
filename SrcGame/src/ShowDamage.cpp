#include "sinbaram\sinLinkHeader.h"
#include "ShowDamage.h"
#include "Font\\newFont.h"
#include "Settings/Settings.h"

extern int DrawFontImage(char *lpStr, int xPos, int yPos, DWORD rgba, float fRatio);
cSHOW_DMG showDmg;

cSHOW_DMG* cSHOW_DMG::getInstance()
{
	return &showDmg;
}

void cSHOW_DMG::AddDmg(int Dmg, DWORD Serial, int Type)
{
	if (!SETTINGSHANDLER->getDamageDebug())
		return;

	sDMG* newDmg = new sDMG;

	if (newDmg)
	{
		newDmg->Dmg = Dmg;
		newDmg->Time = GetCurrentTime() + 1000;
		newDmg->objSerial = Serial;
		newDmg->Type = Type;
		
		Damages.push_back(newDmg);
	}
}

void cSHOW_DMG::DrawDmg(DWORD TargetSerial, int x, int y)
{
	char szBuff[255];

	for (std::vector<sDMG*>::iterator it = Damages.begin(); it < Damages.end(); it++)
	{
		sDMG* DmgInfo = (*it);
		if (DmgInfo && DmgInfo->objSerial == TargetSerial)
		{
			int Time = DmgInfo->Time - GetCurrentTime();
			if (Time > 0)
			{
				BMPFonts Type;
				switch (DmgInfo->Type)
				{
				case 0:
					Type = BMPFonts::BLUE_FONT;
					break;

				case 1:
					Type = BMPFonts::ORANGE_FONT;
					break;

				case 2: 
					Type = BMPFonts::RED_FONT;
					break;
				}
				

				wsprintf(szBuff, "%d", DmgInfo->Dmg);

				int Alpha = (Time * 255) / 1000;
				int TextWidth = BmpFont[Type]->GetTextWidth(szBuff);

				BmpFont[Type]->DrawBmpFont((float)(x - TextWidth / 2), (float)(y - 63 + (Time / 16)), szBuff, lstrlen(szBuff)/*, D3DCOLOR_RGBA(255, 185, 0, Alpha)*/);
				//DrawFontImage(szBuff, (x - TextWidth / 2), (y - 63 + (Time / 16)), dwColor, 1.f);
			}
			else{
				delete DmgInfo;
				Damages.erase(it);
			}
		}
	}
}