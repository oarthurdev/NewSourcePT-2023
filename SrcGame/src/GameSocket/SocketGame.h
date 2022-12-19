#pragma once

#include "Utils/CMutex.h"
#include "socket.h"

#define KB1 (1ull * 1024ull)
#define KB2 (2ull * 1024ull)
#define KB4 (4ull * 1024ull)
#define KB8 (8ull * 1024ull)
#define KB16 (16ull * 1024ull)
#define KB32 (32ull * 1024ull)
#define KB64 (64ull * 1024ull)
#define KB128 (128ull * 1024ull)
#define KB192 (192ull * 1024ull)
#define KB256 (256ull * 1024ull)
#define KB512 (512ull * 1024ull)
#define MB1 (1ull * KB1 * KB1)
#define MB2 (2ull * KB1 * KB1)
#define MB4 (4ull * KB1 * KB1)
#define MB8 (8ull * KB1 * KB1)
#define GB1 (1ull * KB1 * MB1)
#define GB2 (2ull * KB1 * MB1)
#define GB4 (4ull * KB1 * MB1)
#define GB8 (8ull * KB1 * MB1)

#define TICKCOUNT GetTickCount()


class SocketGame
{
protected:
	HWND hWnd;

	int iMaxConnections;
	BOOL bActive = FALSE;
	BOOL bSetFull = FALSE;
	SocketData* pcaSocketData;

	CMutex* pcMutex = NULL;

public:

	int iReconnectLCOUNT = 0;
	int iReconnectGCOUNT = 0;
	BOOL bLoginServerReconnect = FALSE;
	BOOL bGameServerReconnect = FALSE;

	char szLoginIP[32];
	int iLoginPort;
	char szGameIP[32];
	int iGameServerPort;

	SocketData* pcsmWsockServeroginOld = NULL;
	SocketData* pcSocketGameOld = NULL;

	static struct PacketReceiving* psaPacketReceiving[100];
	static int iNextReceiver;

	HWND GetHWND() { return hWnd; };

	BOOL IsActive() { return bActive; };

	SocketData* GetFreeSocketData();
	int GetNumFreeSlots();

	void DisconnectOldSocket();

	SocketData* GetSocketData(const char* pszIP, int iPort);

	SocketData* Connect(const char* pszIP, int iPort);

	void SocketClose(SocketData* sd);
	void SocketPacket(SocketData* sd, struct PacketReceiving* p);

	static DWORD WINAPI ReceiveThread();
	static DWORD WINAPI Receiver(SocketData* sd);
	static DWORD WINAPI Sender(SocketData* sd);

	void Init(HWND hwnd);

	void PingConnections();

	static BOOL WINAPI CheckConnection();

	void Connected();

	void Loop();

	void Shutdown();

	virtual ~SocketGame();
};

extern SocketGame* pcSocketGame;

#define SOCKETGAME pcSocketGame

#define SOCKETCLOSE(sd) SOCKETGAME->SocketClose(sd)