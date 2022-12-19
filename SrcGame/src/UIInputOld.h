#pragma once

enum EActivate
{
	EACTIVATE_Click,
	EACTIVATE_Key,
	EACTIVATE_Both,
};

class UIInputOld : public ElementOld
{
public:
	UIInputOld(int iID, char* path, int x, int y, int w = 0, char* active_path = nullptr);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnKeyDown(char Code);
	bool OnKeyChar(char Code);

	bool isActive() { return bActive; }
	void setActive(bool active);

	void setEnabled(bool enabled) { bEnabled = enabled; }
	bool getEnabled() { return bEnabled; }

	void setText(string text);
	string getText() { return TrueText; }

	void setActivationMethod(EActivate activate) { eActivate = activate; }

	void Bind(char Code, function<void()> func);

	void setTextArea(int x, int y, int w, int h);

	void setCursor(bool cursor) { bCursor = cursor; }
	bool getCursor() { return bCursor; }

	void setFilter(bool filter) { bFilter = filter; }

	void setDisableClear(bool disable) { bDisableWhenClear = disable; }
	bool getDisableClear() { return bDisableWhenClear; }

private:
	bool bActive = false;
	bool bEnabled = true;
	UIWindowOld* pWindow = 0;
	UIImageOld* Background = 0;
	UIImageOld* Background_ = 0;
	UITextOld* Cursor = 0;
	UITextOld* InputText = 0;
	DWORD frametime = 0;
	EActivate eActivate;
	bool bCursor = true;
	bool bDisableWhenClear = false;
	bool bFilter = false;
	string TrueText;

	unordered_map<char, function<void()>> vKeyBinds;
};
