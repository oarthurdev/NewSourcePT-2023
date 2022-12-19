#pragma once

class UITextOld : public ElementOld
{
public:
	UITextOld(int iID, char* Text, int x, int y, bool bold = false);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	void AddChar(char Code);
	void RemoveChar(int count = 1);

	void setText(string text);
	string getText() { return string(szText); }

private:
	char szText[255];
	bool bBold;
	int iFontHandler = -1;
};

extern char* FormatString(char* fmt, ...);