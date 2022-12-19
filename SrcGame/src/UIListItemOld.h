#pragma once

enum ListEvents
{
	LISTEVENT_None,

	LISTEVENT_Select,
	LISTEVENT_Unselect,
};

class UIListItemOld : public ElementOld
{
public:
	UIListItemOld() {}
	UIListItemOld(int ID, char* path, char* path_, int x, int y, bool hover = true, bool selected = false);

	~UIListItemOld()
	{
		for (auto pElement : vElements)
			delete pElement;

		vElements.clear();
	}

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	void RenderWindows(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	void OnMouseClickWindows(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMoveWindows(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseScrollWindows(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnKeyDown(char Code);
	bool OnKeyChar(char Code);

	void RegisterEvent(ListEvents eEvent, std::function<void()> callback);

	void OnSelect();
	void OnUnselect();

	void AddElement(ElementOld* pElement);

	template<typename T>
	inline T* GetElement(int iID)
	{
		for (auto pElement : vElements)
			if (pElement->getID() == iID)
				return static_cast<T*>(pElement);
		return nullptr;
	}

protected:
	UIImageOld* Image;
	UIImageOld* Image_;

	std::function<void()> SelectCallback;
	std::function<void()> UnselectCallback;

	vector<ElementOld*> vElements;
};