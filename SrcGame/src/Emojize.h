#ifndef _EMOJI_H

#include <Windows.h>
#include <string>
#include <vector>

struct EMOJIINFO
{
	int Mat;
	char szCode[32];
	float w, h;
};

using namespace std;

class cEMOJI
{
public:
	cEMOJI();
	~cEMOJI();

	void Init();
	string handleEmoji(const string &text, int x, int y);
	int getTextSize(const string &text);
	int getCutPos(const string &text, int StrMax);

private:

	vector<EMOJIINFO*> Emojis;

	void AddEmoji(int Mat, string szCode);
	EMOJIINFO* getEmojiInfo(char* szCode);

};

extern cEMOJI cEmoji;

#endif