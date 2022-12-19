#include "Emojize.h"
#include "sinbaram\sinLinkHeader.h"

cEMOJI cEmoji;

cEMOJI::cEMOJI()
{

}

cEMOJI::~cEMOJI()
{
	for (auto Emoji : Emojis)
		if (Emoji)
			delete Emoji;

	Emojis.clear();
}

void cEMOJI::AddEmoji(int Mat, string szCode)
{
	EMOJIINFO* newEmoji = new EMOJIINFO;

	if (newEmoji)
	{
		newEmoji->Mat = Mat;
		wsprintf(newEmoji->szCode, "(%s)", szCode.c_str());
		newEmoji->w = 16;
		newEmoji->h = 16;

		Emojis.push_back(newEmoji);
	}
}

void cEMOJI::Init()
{

	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL    bResult = TRUE;
	char TexturePath[256];

	hSrch = FindFirstFile("game\\emoji\\*.png", &wfd);

	while (bResult)
	{
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (strlen(wfd.cFileName) > 3)
			{
				std::string filename(wfd.cFileName);
				filename[filename.find('.')] = 0;
				wsprintf(TexturePath, "game\\emoji\\%s", wfd.cFileName);
				AddEmoji(CreateTextureMaterial(TexturePath, 0, 0, 0, 0, SMMAT_BLEND_ALPHA), filename);
			}
		}

		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);
}

EMOJIINFO* cEMOJI::getEmojiInfo(char* szCode)
{
	for (auto Emoji : Emojis)
	{
		if (Emoji && Emoji->Mat && !lstrcmpi(szCode, Emoji->szCode))
		{
			return Emoji;
		}
	}

	return 0;
}
#include <iostream>
int cEMOJI::getTextSize(const std::string &text)
{
	string formated(text);
	char word[255];
	int count = std::count(formated.begin(), formated.end(), '(');

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			auto found = formated.find('(');
			if (found != string::npos)
			{
				auto found2 = formated.find(')', found + 1);
				if (found2 != string::npos)
				{
					formated.copy(word, found2 - found, found);
					auto Emoji = getEmojiInfo(word);
					if (Emoji)
					{
						formated.replace(formated.begin() + found, formated.begin() + found2 + 1, "    ");
					}
				}
			}
		}
	}

	return formated.length();
}

int cEMOJI::getCutPos(const std::string &text, int StrMax)
{
	if (text.length() < (unsigned int)StrMax)
		return 0;

	bool bfound = false;
	int lastfound = 0;

	for (int i = 0; i < StrMax; i++)
	{
		if ((!bfound && text[i] == '(') || (bfound && text[i] == ')'))
		{
			bfound = !bfound;
			lastfound = i;
		}
	}

	if (bfound)
		return lastfound;

	return StrMax;
}

string cEMOJI::handleEmoji(const std::string &text, int x, int y)
{
	string formated(text);
	char word[255] = {};
	int count = std::count(formated.begin(), formated.end(), '(');

	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			auto found = formated.find('(');
			if (found != string::npos)
			{
				auto found2 = formated.find(')', found + 1);
				if (found2 != string::npos)
				{
					formated.copy(word, found2 - found + 1, found);
					auto Emoji = getEmojiInfo(word);
					if (Emoji)
					{
						formated.replace(formated.begin() + found, formated.begin() + found2 + 1, "    ");
						SIZE size = {};
						GetFontTextExtentPoint(0, formated.c_str(), found, &size);
						dsDrawTexImageFloat(Emoji->Mat, x + size.cx, y, 14, 14, 255);
					}
				}
			}
		}
	}

	return formated;
}