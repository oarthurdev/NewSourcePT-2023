#include "SocketGame.h"
//#include "Scene/SceneManager.h"
//#include "Core/Model/socket/opcodes.h"
#include "netplay.h"
#include "Utils/CMutex.h"

DWORD dwReconnectLoginServerCount = 0;
DWORD dwTimePacket = 0;
BOOL bCanCheckConnection = FALSE;
extern int                    iLoginServerPingID;
extern int                    iGameServerPingID;
struct PacketReceiving* SocketGame::psaPacketReceiving[100];
int SocketGame::iNextReceiver;

extern SocketData* smWsockServer;
extern SocketData* smWsockDataServer;
extern SocketData* smWsockUserServer;
extern SocketData* smWsockExtendServer;

extern void RecvMessage(SocketData* pcSocketData, char* psPacket);

SocketGame* pcSocketGame = NULL;

int SocketGame::GetNumFreeSlots()
{
	int iFreeSlots = 0;
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (!sd->bInUse)
			iFreeSlots++;
	}
	return iFreeSlots;
}

SocketData* SocketGame::GetFreeSocketData()
{
	SocketData* r = NULL;
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (!sd->bInUse)
		{
			sd->Init();
			r = sd;
			break;
		}
	}
	return r;
}

SocketData* SocketGame::GetSocketData(const char* pszIP, int iPort)
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (sd->bInUse && !lstrcmpi(sd->szIP, pszIP) && sd->iPort == iPort)
		{
			return sd;
		}
	}
	return NULL;
}
void SocketGame::DisconnectOldSocket()
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (!sd->bInUse && sd->bConnected)
		{
			SOCKETGAME->SocketClose(sd);
		}
	}
}

SocketData* SocketGame::Connect(const char* pszIP, int iPort)
{
	SocketData* sd = NULL;
	if ((sd = SOCKETGAME->GetSocketData(pszIP, iPort)) == NULL)
	{
		sd = SOCKETGAME->GetFreeSocketData();
		if (sd)
		{
			if (!sd->Connect(pszIP, iPort))
			{
				sd->UnInit();
				return NULL;
			}
		}
	}

	return sd;
}

void SocketGame::SocketClose(SocketData* sd)
{
	if ((sd) && (sd->bInUse))
	{
		while (sd->bConnecting)
			Sleep(2500);

		sd->Close();
		sd->UnInit();
	}
}

void SocketGame::SocketPacket(SocketData* sd, PacketReceiving* p)
{
	pcMutex->Lock(5000);
	Packet* psPacket = (Packet*)p->baPacket;
	int len = psPacket->size;
	if (len > 0x2000)
		return;

	RecvMessage(sd, (char*)p->baPacket);

	sd->dwTimeLastPacketReceived = GetCurrentTime();
	sd->FreePacketReceiving(p);
	pcMutex->Unlock();
}

DWORD WINAPI SocketGame::ReceiveThread()
{
	return TRUE;
}

DWORD WINAPI SocketGame::Receiver(SocketData* sd)
{
	SocketGame* m = SOCKETGAME;
	HWND hWnd = m->GetHWND();
	PacketReceiving* p;

	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(hWnd, WM_SOCKETPACKET, (WPARAM)sd, (LPARAM)p);
		}
		sd->bBlockSend = TRUE;
		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				WNDPROC_SOCKETCLOSE(hWnd, sd);
			}
		}
	} while (m->IsActive());
	return TRUE;
}

DWORD WINAPI SocketGame::Sender(SocketData* sd)
{
	SocketGame* m = SOCKETGAME;
	HWND hWnd = m->GetHWND();
	PacketSending* p;
	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);
		if (!m->IsActive())
			break;
		while ((p = sd->NextPacketSending()) != NULL)
		{
			//Post Packet Message
			if (!sd->Send(p))
			{
				sd->FreePacketSending(p);
				break;
			}
			sd->FreePacketSending(p);
		}
	} while (m->IsActive());
	return TRUE;
}

void SocketGame::Init(HWND hwnd)
{
	hWnd = hwnd;
	pcMutex = new CMutex("Socket Game");

	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	bActive = TRUE;
	iMaxConnections = 2;
	pcaSocketData = new SocketData[iMaxConnections]();

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = FALSE;
		sd->Prepare(500, 500);
		sd->hReceiveThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&SocketGame::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&SocketGame::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}
	bActive = TRUE;
}

BOOL WINAPI SocketGame::CheckConnection()
{
	static DWORD dwTimeCheckL = 0;
	static DWORD dwTimeCheckG = 0;

	//Login Server
	if (SOCKETGAME)
	{
		SocketData* sd = smWsockServer;
		if (sd)
		{
			if (SOCKETGAME->szLoginIP[0] == 0)
			{
				lstrcpy(SOCKETGAME->szLoginIP, sd->szIP);
				SOCKETGAME->iLoginPort = sd->iPort;
			}
			if ((sd->dwTimeLastPacketReceived + 20000) < TICKCOUNT)
			{
				SOCKETGAME->bLoginServerReconnect = TRUE;
			}
		}
		else
			SOCKETGAME->bLoginServerReconnect = TRUE;
	}

	//Game Server
	if (SOCKETGAME)
	{
		SocketData* sd = smWsockServer;

		if (sd)
		{
			if (SOCKETGAME->szGameIP[0] == 0)
			{
				lstrcpy(SOCKETGAME->szGameIP, sd->szIP);
				SOCKETGAME->iGameServerPort = sd->iPort;
			}
			if ((sd->dwTimeLastPacketReceived + 20000) < TICKCOUNT)
			{
				SOCKETGAME->bGameServerReconnect = TRUE;
			}
		}
		else
		{
			SOCKETGAME->bGameServerReconnect = TRUE;
		}


		if (SOCKETGAME->bLoginServerReconnect)
		{
			DisconnectServerCode = 1;
			DisconnectFlag = TICKCOUNT;
		}
	}

	
	return TRUE;
}
void SocketGame::Connected()
{
	bCanCheckConnection = TRUE;
}

extern int GameMode;

void SocketGame::Loop()
{
	if (GameMode == 2)
	{
		if (bCanCheckConnection)
			SOCKETGAME->CheckConnection();

		PingConnections();
	}
}
void SocketGame::Shutdown()
{
	bActive = FALSE;
}

void SocketGame::PingConnections()
{
	static DWORD dwTick = 0;

	if ((TICKCOUNT - dwTick) >= 1000)
	{
		if (smWsockServer)
		{
			PacketPing s;
			s.size = sizeof(PacketPing);
			s.code = OpCode::MSG_PING;
			s.dwTick = TICKCOUNT;
			smWsockServer->Send((char*)&s, s.size, true);
		}

		dwTick = TICKCOUNT;
	}
}

SocketGame::~SocketGame()
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		TerminateThread(sd->hReceiveThread, 0);
		TerminateThread(sd->hSendThread, 0);
	}
	DELETA(pcaSocketData);
}

