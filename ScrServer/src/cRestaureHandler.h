#pragma once

class cRESTAURE
{
public:

	void RecvGetRestaure(rsPLAYINFO* lpPlayInfo);
	void InsertAgingFailed(rsPLAYINFO* lpPlayInfo, char * ItemName, int ItemAging, int Head, int dwChkSum);
	void RestaureItem(rsPLAYINFO* lpPlayInfo, DWORD Head, DWORD dwChkSum, int coinType, DWORD StoneCode, DWORD StoneHead, DWORD StoneSum);
};

extern cRESTAURE cRestaure;