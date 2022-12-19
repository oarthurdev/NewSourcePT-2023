#include "sinbaram\\sinlinkheader.h"
#include "FontImage.h"
#include "field.h"
#include "Drawsub.h"

void Battle::Init()
{
	cImages[0] = CreateTextureMaterial("game\\images\\Battle\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\Battle\\button.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[2] = CreateTextureMaterial("game\\images\\Battle\\close.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[3] = CreateTextureMaterial("game\\images\\Battle\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[4] = CreateTextureMaterial("game\\images\\Battle\\drops.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[5] = CreateTextureMaterial("game\\images\\Battle\\rewards.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//Arena Drops
	cImages[6] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item1.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[7] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item2.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[8] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item3.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[9] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item4.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[10] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item5.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[11] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item6.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[12] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item7.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[13] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item8.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//cImages[14] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item9.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//cImages[15] = CreateTextureMaterial("game\\images\\Battle\\items\\arena_item10.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//Hp Boss
	cImages[16] = CreateTextureMaterial("game\\images\\Battle\\life.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[17] = CreateTextureMaterial("game\\images\\Battle\\life_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	//Boss Mundo drops
	cImages[18] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item1.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[19] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item2.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[20] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item3.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[21] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item4.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[22] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item5.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[23] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item6.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[24] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item7.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[25] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item8.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[26] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item9.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[15] = CreateTextureMaterial("game\\images\\Battle\\items\\boss_item10.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	LifePercent = 0;
	IsBoss = false;
}

void Battle::DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void Battle::Draw()
{
	if (IsBoss && NowHP > 0)
	{
	//Verificando se o personagem est� em bless..
	unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;
	//FontType = 2;
	if (stage == 33)
	{
		char szBuff[256];
		dsDrawTexImage(cImages[16], WinSizeX / 2 - 237, 90, 474, 58, 255);
		dsDrawTexImage(cImages[17], WinSizeX / 2 - 191, 112, int((386.f / 100.f)*(float)LifePercent), 16, 255);
		wsprintf(szBuff, "%d%s", (int)LifePercent, "%");
		SetFontTextColor(RGB(255, 255, 255));
		SIZE size;
		GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
		dsTextLineOut(0,WinSizeX / 2 - 237 + 237 - size.cx / 2, 111, szBuff, lstrlen(szBuff));

	}
	else {

		char szBuff[256];
		dsDrawTexImage(cImages[16], WinSizeX / 2 - 237, 30, 474, 58, 255);
		dsDrawTexImage(cImages[17], WinSizeX / 2 - 191, 52, int((386.f / 100.f)*(float)LifePercent), 16, 255);
		wsprintf(szBuff, "%d%s", (int)LifePercent, "%");
		SetFontTextColor(RGB(255, 255, 255));
		SIZE size;
		GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
		dsTextLineOut(0,WinSizeX / 2 - 237 + 237 - size.cx / 2, 51, szBuff, lstrlen(szBuff));
	}

	//FontType = 0;
}
	/*if (IsBoss && NowHP > 0)
	{
		char szBuff[256];
		dsDrawTexImage(cImages[16], WinSizeX / 2 - 237, 30, 474, 58, 255);
		dsDrawTexImage(cImages[17], WinSizeX / 2 - 191, 52, int((386.f / 100.f)*(float)LifePercent), 16, 255);
		wsprintf(szBuff, "%d%s", (int)LifePercent,"%");
		SetFontTextColor(RGB(255, 255, 255));
		SIZE size;
		GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
		dsTextLineOut(0,WinSizeX / 2 - 237 + 237 - size.cx / 2, 51, szBuff, lstrlen(szBuff));
	}*/

	if (fOpen)
	{
		char szBuff[256];
		int WinX = 40, WinY = 70;
		DrawImage(cImages[0], WinX, WinY, 316, 362);
		if (MouseAction(WinX + 74, WinY + 321, 172, 36))
			DrawImage(cImages[1], WinX + 74, WinY + 321, 172, 36);
		if (MouseAction(WinX + 298, WinY + 7, 12, 12))
			DrawImage(cImages[2], WinX + 298, WinY + 7, 12, 12);
		SIZE size, size2;
		//FontType = 2;
		SetFontOpacity(205);
		SetFontTextColor(RGB(255, 255, 255));
		if (EventBattleArena == 0 || EventBattleArena == 2)
			lstrcpy(szBuff, "Priston Tale");
		if (EventBattleArena == 1)
			lstrcpy(szBuff, "Battle Arena");
		if (EventBattleArena == 3)
			lstrcpy(szBuff, "Boss Mundo");
		GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
		dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 15, szBuff, strlen(szBuff));
		SetFontOpacity(255);
		SetFontTextColor(RGB(127, 126, 126));

		if (EventBattleArena == 0 || EventBattleArena == 2)
		{
			//FontType = 0;
			wsprintf(szBuff, "Ol� %s, n�o temos nenhum evento dispon�vel", lpCurPlayer->smCharInfo.szName);
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 100, szBuff, strlen(szBuff));
			lstrcpy(szBuff, "no momento confira os hor�rios abaixo:");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 120, szBuff, strlen(szBuff));
			//FontType = 1;
			lstrcpy(szBuff, "20:00:Battle Arena");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			lstrcpy(szBuff, "20:00:");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size2);
			SetFontTextColor(RGB(175, 174, 170));
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 150, szBuff, strlen(szBuff));
			lstrcpy(szBuff, "Battle Arena");
			SetFontTextColor(RGB(229, 225, 156));
			dsTextLineOut(0,WinX + (158 - size.cx / 2) + size2.cx, WinY + 150, szBuff, strlen(szBuff));
			lstrcpy(szBuff, "19:00:Boss Mundo");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			lstrcpy(szBuff, "19:00:");
			SetFontTextColor(RGB(175, 174, 170));
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size2);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 170, szBuff, strlen(szBuff));
			lstrcpy(szBuff, "Boss Mundo");
			SetFontTextColor(RGB(13, 219, 27));
			dsTextLineOut(0,WinX + (158 - size.cx / 2) + size2.cx, WinY + 170, szBuff, strlen(szBuff));
			//FontType = 0;
		}
		else if (EventBattleArena == 1 || EventBattleArena == 3)
		{
			//FontType = 1;
			SetFontTextColor(RGB(229, 225, 156));
			wsprintf(szBuff, "Voc� est� preparado para essa batalha?");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 140, szBuff, strlen(szBuff));
			SetFontTextColor(RGB(127, 126, 126));
			wsprintf(szBuff, "Veja abaixo as poss�veis recompensas");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 160, szBuff, strlen(szBuff));
			wsprintf(szBuff, "dos eventos.");
			GetFontTextExtentPoint(0,szBuff, strlen(szBuff), &size);
			dsTextLineOut(0,WinX + (158 - size.cx / 2), WinY + 180, szBuff, strlen(szBuff));
			//FontType = 0;
		}

		if (EventBattleArena == 0 || EventBattleArena == 2)
			DrawImage(cImages[3], WinX + 15, WinY + 210, 287, 86);
		else if (EventBattleArena == 1)
		{
			DrawImage(cImages[4], WinX + 3, WinY + 200, 310, 110);
			DrawImage(cImages[6], WinX + 39, WinY + 226, 38, 39);
			DrawImage(cImages[7], WinX + 89, WinY + 226, 38, 39);
			DrawImage(cImages[8], WinX + 139, WinY + 226, 38, 39);
			DrawImage(cImages[9], WinX + 189, WinY + 226, 38, 39);
			DrawImage(cImages[10], WinX + 239, WinY + 226, 38, 39);
			DrawImage(cImages[11], WinX + 39, WinY + 271, 38, 39);
			DrawImage(cImages[12], WinX + 89, WinY + 271, 38, 39);
			DrawImage(cImages[13], WinX + 139, WinY + 271, 38, 39);
			DrawImage(cImages[26], WinX + 189, WinY + 271, 38, 39);
			DrawImage(cImages[15], WinX + 239, WinY + 271, 38, 39);
		}
		else if (EventBattleArena == 3)
		{
			DrawImage(cImages[5], WinX + 3, WinY + 200, 310, 110);
			DrawImage(cImages[18], WinX + 39, WinY + 226, 38, 39);
			DrawImage(cImages[19], WinX + 89, WinY + 226, 38, 39);
			DrawImage(cImages[20], WinX + 139, WinY + 226, 38, 39);
			DrawImage(cImages[21], WinX + 189, WinY + 226, 38, 39);
			DrawImage(cImages[22], WinX + 239, WinY + 226, 38, 39);
			DrawImage(cImages[23], WinX + 39, WinY + 271, 38, 39);
			DrawImage(cImages[24], WinX + 89, WinY + 271, 38, 39);
			DrawImage(cImages[25], WinX + 139, WinY + 271, 38, 39);
			DrawImage(cImages[26], WinX + 189, WinY + 271, 38, 39);
			DrawImage(cImages[15], WinX + 239, WinY + 271, 38, 39);
		}
	}
}

bool Battle::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Battle::Button()
{
	if (fOpen)
	{
		int WinX = 40, WinY = 70;
		if (MouseAction(WinX + 298, WinY + 7, 12, 12))
			Close();

		if (EventBattleArena == 1 || EventBattleArena == 3)
		{
			if (MouseAction(WinX + 74, WinY + 321, 172, 36))
				cMessageBox.ShowMessage3(MESSAGE_BATTLE_ARENA, "Deseja entrar?");
		}

	}
}

void Battle::BossInfo(const smCHAR_INFO & smCharInfo)
{

	if (smCharInfo.Life[1] == 0 && smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT || smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU || smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA || smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_MUNDO || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_TULLA || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_SHY || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_DRAXOS || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_MIDRANDA || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_GREEDY || smCharInfo.dwCharSoundCode == snCHAR_SOUND_B_WLORD || smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT || smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL)
	{
		IsBoss = true;
		NowHP = (float)smCharInfo.Life[0];
		MaxHP = (float)smCharInfo.Life[1];
		LifePercent = (NowHP / MaxHP) * 100;
		
	}
	else IsBoss = false;

}

bool Battle::isBoss(const smCHAR_INFO & smCharInfo)
{
	return (strstr(smCharInfo.szName, "Midranda") || strstr(smCharInfo.szName, "Yagditha") || strstr(smCharInfo.szName, "Draxos") || strstr(smCharInfo.szName, "Greedy") ||
		strstr(smCharInfo.szName, "Tulla") || strstr(smCharInfo.szName, "Furia") || strstr(smCharInfo.szName, "Babel") || strstr(smCharInfo.szName, "Valento") ||
		strstr(smCharInfo.szName, "Kelvezu") || strstr(smCharInfo.szName, "Devil Shy") || strstr(smCharInfo.szName, "Mokova"));
}

int Gladiador()
{
	smTRANS_COMMAND smPacket;
	smPacket.code = OpCode::OPCODE_USEITEM_CODE;
	smPacket.WParam = sinBI2 | sin81;
	smPacket.EParam = 0;
	smPacket.size = sizeof(smPacket);

	extern SocketData* smWsockDataServer;

	if (smWsockDataServer)
	{
		smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
	};
	return TRUE;
}

int NotGladiador()
{
	smTRANS_COMMAND smPacket;
	smPacket.code = OpCode::OPCODE_USEITEM_CODE;
	smPacket.WParam = sinBI2 | sin88;
	smPacket.EParam = 0;
	smPacket.size = sizeof(smPacket);

	extern SocketData* smWsockDataServer;

	if (smWsockDataServer)
	{
		smWsockDataServer->Send((char*)& smPacket, smPacket.size, TRUE);
	};
	return TRUE;
}