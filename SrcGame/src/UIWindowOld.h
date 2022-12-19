#pragma once

class UIWindowOld : public ElementOld
{
public:
	UIWindowOld(int ID, char* path, int x, int y, bool fixed = true);
	UIWindowOld(int ID, char* top, char* mid, char* bot, int x, int y, bool fixed = true);
	UIWindowOld(int ID, int x, int y, int w, int h, bool fixed = true);
	~UIWindowOld();

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnKeyDown(char Code);
	int getMidHeight() { if (getType() == 2) return bgSplit[1]->getHeight(); else return 0; }
	int getMaxY() { return iMaxY; }

	void AddElement(ElementOld* pElement);

	template<typename T>
	inline T* GetElement(int iID)
	{
		for (auto pElement : vElements)
			if (pElement->getID() == iID)
				return static_cast<T*>(pElement);
		return nullptr;
	}
private:
	UIImageOld* Background = nullptr;
	UIImageOld* bgSplit[3];
	vector<ElementOld*> vElements;
	UIVerticalScrollOld* pVerticalScroll = nullptr;

	int iMaxY = 0;
};
