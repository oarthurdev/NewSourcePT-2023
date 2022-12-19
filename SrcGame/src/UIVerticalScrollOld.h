#pragma once

class UIVerticalScrollOld : public ElementOld
{
public:
	UIVerticalScrollOld(int iID, int x, int y, int w, int h, int minValue, int maxValue);

	void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseClick(CLICKS Type, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseMove(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);
	bool OnMouseScroll(int zDelta, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

	void setMin(int min) { Minimum = min; }
	int getMin() { return Minimum; }

	void setMax(int max) { Maximum = max; }
	int getMax() { return Maximum; }

	void setValue(int val) { val >= Maximum ? Value = Maximum : val <= Minimum ? Value = Minimum : Value = val; }
	int getValue() { return Value; }

	void setHeight(int val);

	void updateButtonPosByValue();

private:
	UIImageOld* ScrollBarBg;
	UIImageOld* ScrollButton;

	int Minimum;
	int Maximum;
	int Value;

	bool bTrackY = false;;

	void updateButtonPos(int iY);
};