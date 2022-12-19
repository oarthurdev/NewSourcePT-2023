#pragma once

class UIButtonOld : public ElementOld
{
public:
	UIButtonOld(int ID, char* path, char* path_, int x, int y, bool hover = true, bool selected = false, std::function<void()> callback = 0);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

private:
	UIImageOld* Image;
	UIImageOld* Image_;

	std::function<void()> Activation;
};