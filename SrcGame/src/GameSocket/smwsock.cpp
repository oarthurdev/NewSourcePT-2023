//#define _WIN32_WINNT    0x0403  
//#define _WIN32_WINDOWS  0x0403

#include "nettype.h"
#include <windows.h>
#include <io.h>
#include <stdio.h>         
#include <string.h>        
#include <memory.h>
#include <process.h>
#include "GameSocket/smwsock.h"
#include "SocketGame.h"

#pragma comment(lib, "wsock32.lib")


void InitGameSocket(HWND hwnd, int ThreadMode)
{
	SOCKETGAME = new SocketGame();
	SOCKETGAME->Init(hwnd);
}

LPFN_EncodePacket	fnEncodePacket = 0;
LPFN_DecodePacket	fnDecodePacket = 0;

BYTE smwsock_EncodePacket_AsmCode[ENC_PACKET_ASM_SIZE];
