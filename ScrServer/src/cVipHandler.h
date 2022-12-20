#pragma once
class cVipHandler
{
public:
	static cVipHandler* getInstance() { static cVipHandler instance; return &instance; };


	void InsertDB(rsPLAYINFO* lpPlayInfo, int IdVip, int time);
	void IsVIp(rsPLAYINFO* lpPlayInfo);

	bool returnVip(rsPLAYINFO* lpPlayInfo);
	int IdVip;

};


#define VIPHANDLER cVipHandler::getInstance()