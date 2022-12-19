#include "FontImage.h"
#include "sinbaram\\sinlinkheader.h"


char NameRank[10][32];
char NameClanRank[10][32];
int LevelRank[10];
int ClasseRank[10];
int KillsRank[10];
char liderClanRank[10][32];
int pointsClanRank[10];
int pointsRank[10];
int membrosclanRank[10];
int DeadsRank[10];


int Option = 0;
int contador;
int Type = 0;
enum OnRank { RANKPLAYER = 1, RANKPVP, RANKSODPLAYER, RANKSODCLAN, RANKLISTCLAN };
void RankGame::init() {

	img[BACKGROUND] = CreateTextureMaterial("game\\ranking\\background.TGA", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTRANKPLAYER] = CreateTextureMaterial("game\\ranking\\btn_ranklvl.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTRANKPVP] = CreateTextureMaterial("game\\ranking\\btn_rankbp.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTRANKSODCLAN] = CreateTextureMaterial("game\\ranking\\btn_ranksodclan.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTRANKSODPLAYER] = CreateTextureMaterial("game\\ranking\\btn_ranksodplayer.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTRANKLISTCLAN] = CreateTextureMaterial("game\\ranking\\btn_clanlist.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[BTCLOSE] = CreateTextureMaterial("game\\ranking\\close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[PIKE] = CreateTextureMaterial("game\\ranking\\Class\\ps.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[MS] = CreateTextureMaterial("game\\ranking\\Class\\ms.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[FS] = CreateTextureMaterial("game\\ranking\\Class\\fs.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[AS] = CreateTextureMaterial("game\\ranking\\Class\\as.BMP", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[ATS] = CreateTextureMaterial("game\\ranking\\Class\\ata.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[MGS] = CreateTextureMaterial("game\\ranking\\Class\\mg.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[KS] = CreateTextureMaterial("game\\ranking\\Class\\ks.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[PRS] = CreateTextureMaterial("game\\ranking\\Class\\prs.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[ASS] = CreateTextureMaterial("game\\ranking\\Class\\ass.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgClasse[SHA] = CreateTextureMaterial("game\\ranking\\Class\\sha.bmp", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	img[8] = CreateTextureMaterial("game\\ranking\\line.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}


void RankGame::Draw() {
	int wx = 219;
	int wy = 166;
	
	if (rFopen) {
		DrawImage(img[BACKGROUND], 140, 50, 644, 521);

		if (Type == 6) {
			DrawFontText(460, 153, "Sin Resultados", RGB(185, 206, 255),0);
		}
		if (Option == 0) {
			DrawRankingPlayer(NameRank, LevelRank, ClasseRank);
			DrawImage(img[BTRANKPLAYER], 186, 150, 186, 47);

		}
		if (Option == RANKPLAYER && Type == 1) {
			DrawRankingPlayer(NameRank, LevelRank, ClasseRank);
			DrawImage(img[BTRANKPLAYER], 186, 150, 186, 47);
		}
		else if (Option == RANKPVP && Type == 2) {
			DrawRankingPVP(NameRank, LevelRank, ClasseRank, KillsRank, DeadsRank);
			DrawImage(img[BTRANKPVP], 186, 201, 186, 47);
		}
		else if (Option == RANKSODCLAN && Type == 4) {
			DrawRankingSodClans(NameClanRank, liderClanRank, pointsClanRank);
			DrawImage(img[BTRANKSODCLAN], 186, 301, 186, 47);
		}
		else if (Option == RANKSODPLAYER && Type == 3) {
			DrawRankingSodPlayers(NameRank, ClasseRank, NameClanRank, pointsRank);
			DrawImage(img[BTRANKSODPLAYER], 186, 251, 186, 47);
		}
		else if (Option == RANKLISTCLAN && Type == 5) {
			DrawRankingClans(NameClanRank, liderClanRank, membrosclanRank);
			DrawImage(img[BTRANKLISTCLAN], 186, 351, 186, 47);
		}

	}
}

void RankGame::DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}


bool RankGame::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}




void RankGame::DrawRankingPlayer(char Name[10][32], int Level[10], int Classe[10]) {
	
		int y = 10;
		char rank1[10][50];
		char rankn[10][50];
		char Levelr[10][50];

		
		DrawFontText(410, 147, "Nick", RGB(185, 206, 255),3);
		DrawFontText(600, 147, "Nível", RGB(185, 206, 255), 3);
		DrawFontText(357, 147, "Nº", RGB(185, 206, 255), 3);
		
		for (int i = 0; i < contador; i++) {
			wsprintf(rank1[i], "#%d", i+1);
			wsprintf(rankn[i], "%s", Name[i]);
			wsprintf(Levelr[i], "%d", Level[i]);
			DrawImage(imgClasse[Classe[i]], 380, 155 + y, 22, 22);
			DrawImage(img[8], 355, 155 + y + 20, 300, 4);
			DrawFontText(357, 157 + y, rank1[i], RGB(255, 235, 0), 3);
			DrawFontText(410, 157 + y, rankn[i], RGB(255, 255, 255), 3);
			DrawFontText(600, 157 + y, Levelr[i], RGB(100, 255, 100), 3);
			y += 30;
		}
	
}
int RankGame::DrawRankingPVP(char Name[10][32], int Level[10], int Classe[10], int Kills[10], int Deads[10]) {

	if (rFopen) {
		int y = 10;
		char rank1[10][50];
		char rankn[10][50];
		char Levelr[10][10];
		char BPr[10][10];
		char DPr[10][10];

		DrawFontText(410, 147, "Nick", RGB(185, 206, 255), 3);
		DrawFontText(500, 147, "Nível", RGB(185, 206, 255), 3);
		DrawFontText(555, 147, "Matou", RGB(185, 206, 255), 3);
		DrawFontText(613, 147, "Morreu", RGB(185, 206, 255), 3);
		DrawFontText(357, 147, "Nº", RGB(185, 206, 255), 3);
		for (int i = 0; i < contador; i++) {
			wsprintf(rank1[i], "#%d", i + 1);
			wsprintf(rankn[i], "%s", Name[i]);
			wsprintf(Levelr[i], "%d", Level[i]);
			wsprintf(BPr[i], "%d", Kills[i]);
			wsprintf(DPr[i], "%d", Deads[i]);
			if (lstrlen(rankn[i]) > 0) {
				DrawImage(imgClasse[Classe[i]], 380, 155 + y, 22, 22);
				DrawImage(img[8], 355, 155 + y + 20, 300, 4);
				DrawFontText(357, 157 + y, rank1[i], RGB(255, 235, 0), 3);
				DrawFontText(410, 157 + y, Name[i], RGB(255, 255, 255), 3);
				DrawFontText(500, 157 + y, Levelr[i], RGB(255, 255, 255), 3);
				DrawFontText(555, 157 + y, BPr[i], RGB(100, 255, 100), 3);
				DrawFontText(613, 157 + y, DPr[i], RGB(255, 100, 100), 3);
				y += 30;
			}
		}
	}
	return 0;
}

int RankGame::DrawRankingClans(char NameClan[10][32], char LiderClan[10][32], int MembrosClan[10]) {
	if (rFopen) {
		int y = 10;
		char rank1[10][50];
		char Levelr[10][50];

		DrawFontText(357, 147, "Nº", RGB(185, 206, 255), 3);
		DrawFontText(390, 147, "Clan", RGB(185, 206, 255), 3);
		DrawFontText(495, 147, "Lider", RGB(185, 206, 255), 3);
		DrawFontText(600, 147, "Membros", RGB(185, 206, 255), 3);

		for (int i = 0; i < contador; i++) {

			wsprintf(rank1[i], "#%d", i + 1);
			wsprintf(Levelr[i], "%d", MembrosClan[i]);
				DrawImage(img[8], 355, 155 + y + 20, 300, 4);
				DrawFontText(357, 157 + y, rank1[i], RGB(255, 235, 0), 3);
				DrawFontText(390, 157 + y, NameClan[i], RGB(255, 255, 255), 3);
				DrawFontText(495, 157 + y, LiderClan[i], RGB(255, 255, 255), 3);
				DrawFontText(620, 157 + y, Levelr[i], RGB(255, 255, 255), 3);
				y += 30;
			
		}
	}
	return 0;
}

int RankGame::DrawRankingSodClans(char NameClan[10][32], char LiderClan[10][32], int Points[10]) {

	if (rFopen) {
		int y = 10;
		char rank1[10][50];
		char Levelr[10][50];

		DrawFontText(357, 147, "Nº", RGB(185, 206, 255), 3);
		DrawFontText(390, 147, "Clan", RGB(185, 206, 255), 3);
		DrawFontText(495, 147, "Lider", RGB(185, 206, 255), 3);
		DrawFontText(600, 147, "pontos", RGB(185, 206, 255), 3);

		for (int i = 0; i < contador; i++) {

			wsprintf(rank1[i], "#%d", i + 1);
			wsprintf(Levelr[i], "%d", Points[i]);
			DrawImage(img[8], 355, 155 + y + 20, 300, 4);
			DrawFontText(357, 157 + y, rank1[i], RGB(255, 235, 0), 3);
			DrawFontText(390, 157 + y, NameClan[i], RGB(255, 255, 255), 3);
			DrawFontText(495, 157 + y, LiderClan[i], RGB(255, 255, 255), 3);
			DrawFontText(600, 157 + y, Levelr[i], RGB(255, 255, 255), 3);
			y += 30;

		}
	}

	return 0;
}

int RankGame::DrawRankingSodPlayers(char Name[10][32], int Classe[10], char Clan[10][32], int Points[10]) {
	if (rFopen) {
		int y = 10;
		char rank1[10][50];
		char Levelr[10][50];

		DrawFontText(357, 147, "Nº", RGB(185, 206, 255), 3);
		DrawFontText(410, 147, "Nick", RGB(185, 206, 255), 3);
		DrawFontText(600, 147, "pontos", RGB(185, 206, 255), 3);

		for (int i = 0; i < contador; i++) {

			wsprintf(rank1[i], "#%d", i + 1);
			wsprintf(Levelr[i], "%d", Points[i]);
			DrawImage(img[8], 355, 155 + y + 20, 300, 4);
			DrawFontText(357, 157 + y, rank1[i], RGB(255, 235, 0), 3);
			DrawImage(imgClasse[Classe[i]], 380, 155 + y, 22, 22);
			DrawFontText(410, 157 + y, Name[i], RGB(255, 255, 255), 3);
			DrawFontText(600, 157 + y, Levelr[i], RGB(255, 255, 255), 3);
			y += 30;

		}
	}

	return 0;
}

void RankGame::Button()
{

	smTRANS_COMMAND smPacket;



	if (rFopen)
	{
		int WinX = 140, WinY = 50;
		if (MouseAction(702, 90, 20, 20)) {
			Close();
			Option = 1;
		}
		if (MouseAction(219, 166, 98, 25)) {
			Option = 1;
			smPacket.WParam = 1;
		}
		if (MouseAction(219, 216, 98, 25)) {
			Option = 2;
			smPacket.WParam = 2;
		}
		if (MouseAction(219, 266, 98, 25)) {
			Option = 3;
			smPacket.WParam = 3;
		}
		if (MouseAction(219, 316, 98, 25)) {
			smPacket.WParam = 4;
			Option = 4;
		}
		if (MouseAction(219, 366, 98, 25)) {
			smPacket.WParam = 5;
			Option = 5;
		}

	}
	smPacket.code = OpCode::OPCODE_RANKINGSEND;
	smPacket.EParam = 0;
	smPacket.size = sizeof(smPacket);
	extern SocketData* smWsockDataServer;
	if (smWsockDataServer)
	{
		smWsockDataServer->Send((char*)&smPacket, smPacket.size, TRUE);
	};
}