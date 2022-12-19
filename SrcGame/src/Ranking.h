#pragma once


class RankGame {

public:
	static RankGame* GetInstance() { static RankGame instance; return &instance; };
	void Open() { rFopen = true; };
	void Close() { rFopen = false; };
	bool IsOpen() { return rFopen; };
	
	void init();
	void Draw();
	bool MouseAction(int x, int y, int w, int h);
	void DrawImage(int Mat, int x, int y, int w, int h);
	void Button();
private:
	void DrawRankingPlayer(char Name[10][32], int Level[10], int Classe[10]);
	int DrawRankingPVP(char Name[10][32], int Level[10], int Classe[10], int Kills[10], int Deads[10]);
	int DrawRankingClans(char NameClan[10][32], char LiderClan[10][32], int MembrosClan[10]);
	int DrawRankingSodClans(char NameClan[10][32], char LiderClan[10][32], int Points[10]);
	int DrawRankingSodPlayers(char Name[10][32], int Classe[10], char Clan[10][32], int Points[10]);
	int rFopen;
	int img[9];
	int imgClasse[11];
	enum image { BACKGROUND, BTRANKPLAYER, BTRANKPVP, BTRANKSODCLAN, BTRANKSODPLAYER, BTRANKLISTCLAN, BTCLOSE };
	enum classe { FS = 1, MS, AS, PIKE, ATS, KS, MGS, PRS, ASS, SHA };
};