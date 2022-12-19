#pragma once

class UIHorizontalScrollOld : public ElementOld
{
public:
	UIHorizontalScrollOld(int iID, int x, int y, int minValue, int maxValue, int startValue = -1);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

	void setMin(int min) { Minimum = min; }
	int getMin() { return Minimum; }

	void setMax(int max) { Maximum = max; }
	int getMax() { return Maximum; }

	void setValue(int val) { val >= Maximum ? Value = Maximum : val <= Minimum ? Value = Minimum : Value = val;; updateBar(); updateButtonPos(); }
	int getValue() { return Value; }

private:
	UIImageOld* ScrollBar = nullptr;
	UIImageOld* ScrollBarBg = nullptr;
	UIImageOld* ScrollButton = nullptr;

	int Minimum = 0;
	int Maximum = 0;
	int Value = 0;

	bool bTrackX = false;;

	void updateBar();
	void updateButtonPos(int iX);
	void updateButtonPos() { ScrollButton->setX(ScrollBar->getX() + ScrollBar->getWidth() - 10); }
};