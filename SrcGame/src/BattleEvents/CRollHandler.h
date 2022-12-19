#pragma once

#include "CRollWindow.h"

class CRollHandler
{
public:
	static CRollHandler* getInstance();

	void Render();
	bool OnMouseClick(bool flag);
	void OnMouseMove();

	bool isInsideRoll();

	void HandlePacket(PacketRollInfo* psPacket);
	void HandlePacket(smTRANS_COMMAND* psPacket);
	void Resize();

private:
	unordered_map<DWORD, CRollWindow*> vRolls;
	map<int, bool> vPos;
};

#define ROLLHANDLER CRollHandler::getInstance()