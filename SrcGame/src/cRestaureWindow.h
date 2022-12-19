#pragma once

struct RESTAURE_ITEM
{
	int CoinPrice;
	sITEM psItem;
};

class cRESTAURE
{
public:

	cRESTAURE() { OpenFlag = false; }
	~cRESTAURE() {}

	void Load();
	void Draw();
	bool LButtonDown();
	void Open();
	void Close();
	void Restaure();
	void SwitchItem(int Side);
	void RecvRestaureList(RESTAURE_LIST* lpRestaureList);

	bool OpenFlag;
	int itemIndex = 0;
	int itemCount = 0;
	vector<RESTAURE_ITEM*> vItems;
	bool resetList = false;

	enum
	{
		BACKGROUND,
		CLOSE,
		LEFT,
		RIGHT,
		RESTAURE,
		MAX_MAT,
	};

	int Mat[MAX_MAT];
	int BaseX, BaseY;
};

extern cRESTAURE cRestaure;