#ifndef _SHOW_DMG
#define _SHOW_DMG

#include <Windows.h>
#include <vector>

class cSHOW_DMG
{
public:
	struct sDMG
	{
		int Dmg;
		int Time;
		DWORD objSerial;
		int Type;
	};

	static cSHOW_DMG* getInstance();
	void AddDmg(int Dmg, DWORD Serial, int Type);
	void DrawDmg(DWORD TargetSerial, int x, int y);

private:
	std::vector<sDMG*> Damages;
};

#endif // _SHOW_DMG