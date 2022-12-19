#pragma once

#include <Windows.h>
#include "global_def.h"
#include "Utils/Mutex.h"
#include "smPacket.h"

#define WM_SOCKETACCEPT		WM_USER + 101
#define WM_SOCKETPACKET		WM_USER + 102
#define WM_SOCKETCLOSE		WM_USER + 103

#define WNDPROC_SOCKETCLOSE( window, socketdata )			( PostMessageA( window, WM_SOCKETCLOSE, (WPARAM)socketdata, (LPARAM)NULL ) )


struct PacketSending
{
	union
	{
		BOOL bInUse;
		UINT uCount;
	};
	UINT uSize;
	BYTE baPacket[smSOCKBUFF_SIZE];

	PacketSending()
	{
		bInUse = FALSE;
		uCount = 0;
		uSize = 0;
		ZeroMemory(baPacket, sizeof(baPacket));
	}
};

struct PacketReceiving
{
	BOOL bInUse;
	BOOL bDelete;
	BYTE baPacket[smSOCKBUFF_SIZE];

	PacketReceiving()
	{
		bInUse = FALSE;
		bDelete = FALSE;
		ZeroMemory(baPacket, sizeof(baPacket));
	}
};

class SocketData
{
public:
	//Attributes
	SocketData* pcThis;

	//Status Flags
	bool bInUse;
	bool bConnecting;
	bool bConnected;
	bool bReserved;

	//This Socket Information
	SOCKET s;
	Player* ud;

	//Remote Host
	char szIP[32];
	long lIP;
	int iPort;

	//Time last Received Packet
	DWORD dwTimeLastPacketReceived;

	//Receiving Packets
	UINT iDefReceivePacket;
	UINT iMaxReceivePacket;
	HANDLE hReceiveThread;
	HANDLE hReceiveThreadSignal;
	CMutex* pcReceiveMutex;
	UINT iReceiveWheel;
	PacketReceiving* psaPacketReceiving;

	//Sending Packets
	UINT iDefSendPacket;
	UINT iMaxSendPacket;
	HANDLE hSendEvent;
	HANDLE hSendThread;
	HANDLE hSendThreadSignal;
	CMutex* pcSendMutex;
	UINT iSendWheel;
	UINT iSendingWheel;
	PacketSending* psaPacketSending;
	BOOL bBlockSend;
	DWORD dwBulkThreadId;
	PacketSending sBulkPacket;

	//Pinging
	bool bPing;
	DWORD dwPingTime;
	int iPing;

	//Counting
	UINT iCountIN;
	UINT iCountOUT;
	UINT iCountOUTB;

	//Error Handling
	int iRecvRet;
	int iRecvEC;
	int iSendRet;
	int iSendEC;

	BOOL bKeepAlive;

public:
	//Operations
	SocketData();
	~SocketData();

	void Prepare(UINT iMaxSendPacket, UINT iMaxReceivePacket);

	//Initializing
	void Init();
	void UnInit();

	//Connection
	bool Connect(const char* pszIP, int iPort);
	void Open(SOCKET s, sockaddr_in* addr);
	void Ping(DWORD dwTime);
	void Close();

	//Receiving
	PacketReceiving* FreePacketReceiving();
	void FreePacketReceiving(PacketReceiving* pp);

	PacketReceiving* ReceivePacket();

	//Sending
	PacketSending* NextPacketSending();
	void FreePacketSending(PacketSending* pp);

private:
	//Inner Packet Sending Methods
	BOOL Send(BYTE* pbData, UINT uSize);
	BOOL SendData(BYTE* pbData, UINT uSize);

	//Automatic Bulk Sending
	PacketSending* FindAutomaticBulk(UINT uSizeNeeded);

public:
	//Packet Sending Method that should only be used from Sending Thread
	BOOL Send(PacketSending* pp);

	//Packet Sending Methods that should be used from outside
	BOOL SendPacket(Packet* p, BOOL bEncrypted = FALSE);
	BOOL SendPacketBlank(DWORD iHeader, BOOL bEncrypted = FALSE);

	//Legacy support
	BOOL Send(char* Buff, int size, int Flag = false);
	BOOL Send2(char* Buff, int size, int Flag = false);
	BOOL Send3(char* Buff, int size, int Flag = false);

	//Forced Bulk Sending
	BOOL StartBulkSend();
	BOOL FlushBulkSend();
	BOOL StopBulkSend();

	//Getters & Setters
	void SetPing(int i) { iPing = i; bPing = false; }
	int GetPing(DWORD dwTime);

};
