#pragma once

class cSKINCHANGER
{
public:
	void Init();
	void Draw();
	bool LButtonDown();
	void Open();
	void Close();
	bool isOpen() { return OpenFlag; }
	bool SetSkinChangerItemAreaCheck(sITEM* pItem, int Pos);

private:
	bool OpenFlag;
	int BaseX, BaseY;

	LPDIRECT3DTEXTURE9 lpBackground;
	LPDIRECT3DTEXTURE9 lpButton;

	sITEM scItem;
	sITEM scStone;

	bool isCompatible(sITEM* pItem, sITEM* pStone);
	LPDIRECT3DTEXTURE9 GetItemImage(sITEM* pItem);
	sITEM* GetItem(DWORD CODE);
};

extern cSKINCHANGER cSkinChanger;