#pragma once

#include "UILinkerOld.h"

class cSorteio
{
public:
	static cSorteio * GetInstance() { static cSorteio instance; return &instance; };
	~cSorteio();

	void Open() { return pWindow1->show(); };
	void Close() { return pWindow1->hide(); };
	void ConfirmSorteio();
	void Init();
	void Draw();
	bool isOpen() { return ((pWindow1 && pWindow1->isVisible()) ? true : false); }

	void BuildImages();
	bool OnMouseClick(bool flag = false);
	void RecvKeysFromServer(smTRANS_COMMAND * lpTransCommand);

	enum
	{
		WindowMain,
		Buttons,
		Header,
		ImageItens,
		CLOSE,
		Text,
		_Keys,
	};
private:
	UIWindowOld* pWindow1;
	int BaseX, BaseY;
	int Keys;
};

#define Sorteio cSorteio::GetInstance()
