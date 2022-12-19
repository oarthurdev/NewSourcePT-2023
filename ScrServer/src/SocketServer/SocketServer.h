#pragma once

#include <unordered_map>
#include <Windows.h>
#include "socket.h"
#include "Utils/Mutex.h"

using namespace std;

#define SOCKETACCEPT(s,a) SocketServer::GetInstance()->SocketAccept(s,a);
#define SOCKETPACKET(s,p) SocketServer::GetInstance()->SocketPacket(s,p);
#define SOCKETCLOSE(s) SocketServer::GetInstance()->SocketClose(s);

class SocketServer
{
protected:
	HWND hWnd;
	WSADATA sWsaData;
	SOCKET sListenSocket = INVALID_SOCKET;
	int iMaxConnections;
	BOOL bActive = FALSE;
	BOOL bSetFull = FALSE;
	SocketData* pcaSocketData;
	CMutex* pcMutex = NULL;
	CMutex* pcSocketCloseMutex = nullptr;
	CMutex* pcReconnectMutex = NULL;

	HANDLE hEventSocket;
	int iNextSocket;
	unordered_map<DWORD, Player&> vReconnectInfo;

public:
	HANDLE hListener;
	static SocketServer* pcInstance;
	static SocketServer* GetInstance() { return SocketServer::pcInstance; };
	CMutex* GetMutex() { return pcMutex; };
	static void CreateInstance() { SocketServer::pcInstance = new SocketServer(); };
	HWND GetHWND() { return hWnd; };
	BOOL IsActive() { return bActive; };
	BOOL IsFull() { return bSetFull; };
	void SetFull(BOOL b) { bSetFull = b; };

	SocketData* GetFreeSocketData();
	int GetNumFreeSlots();

	SocketData* GetSocketData(const char* pszIP, int iPort);

	void SocketAccept(SOCKET s, sockaddr_in* addr);
	void SocketPacket(SocketData* sd, PacketReceiving* p);
	void SocketClose(SocketData* sd);

	SocketServer();
	virtual ~SocketServer();

	static DWORD WINAPI Sender(SocketData* sd);
	static DWORD WINAPI Receiver(SocketData* sd);
	static DWORD WINAPI Listener(SOCKET* ls);

	void Load();

	BOOL Init(HWND hwnd);

	void Listen(int iPort);

	void OnReadHandler(SOCKET s, DWORD dwParam);

	HANDLE GetHandleEventSocket() { return hEventSocket; }

	void AddReconnectUser(SocketData* sd);
	bool TryReconnectUser(SocketData* sd, char* szName, DWORD dwNewSerial);
	void CleanReconnectUsers();
	void RemoveReconnectByAccount(string Account);
};

#define SOCKETMUTEX (SocketServer::GetInstance()->GetMutex())
#define SOCKETSERVER (SocketServer::GetInstance())

