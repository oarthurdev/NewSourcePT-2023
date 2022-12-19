#pragma once

struct LOADEDIMAGE
{
	LPDIRECT3DTEXTURE9 Image;
	char ImagePath[255];
};

enum EDrawStyle
{
	EDRAW_Adjust,
	EDRAW_Repeat,
};

class UIImageOld : public ElementOld
{
public:
	UIImageOld(int iID, char* path, int x, int y, int w = 0, int h = 0);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

	int getTrueWidth() { return trueWidth; }
	int getTrueHeight() { return trueHeight; }
	void setStartX(int start) { startX = start; }
	void setStartY(int start) { startY = start; }

	void setHoverFunc(std::function<void()> func) { fHover = func; }

	void SetImage(char* path);
	void setDrawStyle(EDrawStyle estyle) { eDrawStyle = estyle; }

private:
	LPDIRECT3DTEXTURE9 Image;

	int trueWidth;
	int trueHeight;
	int startX;
	int startY;
	EDrawStyle eDrawStyle = EDRAW_Adjust;

	std::function<void()> fHover;
};

extern void ClearLoadedImages();