#pragma once

#include <Windows.h>

enum EKeyboardEvent
{
	NoneKey,
	KeyDown,
	KeyUp,
	KeyChar,
};

class CKeyboard
{
private:
	EKeyboardEvent eEvent;
	char cKeyChar = 0;
	int iKeyPress = 0;
	void SetEvent(EKeyboardEvent eKeyEvent);
	BOOL baKeyDown[256];
	CKeyboard();

public:
	static CKeyboard* getInstance()
	{
		static CKeyboard inst;
		return &inst;
	}

	virtual ~CKeyboard();

	EKeyboardEvent GetEvent() { return eEvent; };
	char GetChar() { return cKeyChar; };
	int GetKey() { return iKeyPress; };
	BOOL IsKeyDown(int iKey);

	BOOL OnKeyPress(int iKey, BOOL bKeyDown);
	BOOL OnKeyChar(char cKey);
};


#define KEYBOARDHANDLER (CKeyboard::getInstance())
