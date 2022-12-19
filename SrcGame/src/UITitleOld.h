#pragma once

class UITitleOld : public ElementOld
{
public:
	UITitleOld(int iID, char* left, char* middle, char* right, int x, int y, char* text, bool bold = false, DWORD dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

	void setText(string text);

private:
	UIImageOld* Left;
	UIImageOld* Right;
	UIImageOld* Middle;
	UITextOld* Text;
};
