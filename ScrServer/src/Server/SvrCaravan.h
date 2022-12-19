#pragma once


class CCaravanaHandler
{
private:

public:
	static CCaravanaHandler* getInstance();
	void StartPremium(rsPLAYINFO* lpPlayInfo, DWORD dwTime);
	void AddCaravan(rsPLAYINFO* lpPlayInfo);
	void DelCaravan(smCHAR* lpChar);
};

#define CARAVANHANDLER CCaravanaHandler::getInstance()