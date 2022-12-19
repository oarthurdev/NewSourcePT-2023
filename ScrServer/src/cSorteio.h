#pragma once

//class rsPLAYINFO;
#include "smPacket.h"
class cSorteio
{
public:
	static cSorteio * getInstance() { static cSorteio instance; return &instance; };

	
	void SendSorteio(rsPLAYINFO * lpPlayInfo);
	void OpenNpcSorteio(rsPLAYINFO* lpPlayInfo);
	void RecvGetItemKeys(rsPLAYINFO * lpPlayInfo);
};

#define Sorteio cSorteio::getInstance()

