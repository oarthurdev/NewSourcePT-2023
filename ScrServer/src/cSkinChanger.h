#pragma once

class cSKINCHANGER
{
public:
	void RecvSkinChange(SKINCHANGE_INFO* psPacket, rsPLAYINFO* lpPlayInfo);
	bool OpenSkinChange(rsPLAYINFO* lpPlayInfo);
};

extern cSKINCHANGER cSkinChanger;