#include <string>
#include "SocketServer.h"
#include "Utils/Mutex.h"
#include "global_def.h"
#include "Utils/Debug.h"
#include "Utils/String.h"

extern int AddNewPlayInfo(SocketData* pcSocketData);
extern CRITICAL_SECTION	cSerSection;
extern int RecvMessage(SocketData* pcSocketData, char* psPacket);
extern int RecordLog(const char* szLogName, const char* szMessage);

SocketServer* SocketServer::pcInstance = NULL;



SocketServer::SocketServer()
{
	hWnd = NULL;
	bActive = FALSE;
	bSetFull = FALSE;
	pcaSocketData = nullptr;
	hEventSocket = NULL;
	iNextSocket = 0;
	vReconnectInfo.clear();
	sListenSocket = INVALID_SOCKET;
	iMaxConnections = 0;
	pcMutex = new CMutex();
	pcReconnectMutex = new CMutex();
	pcSocketCloseMutex = new CMutex();

	hListener = NULL;
}


SocketServer::~SocketServer()
{
	CloseHandle(hEventSocket);
	DELET(pcMutex);
	DELET(pcReconnectMutex);
	DELET(pcSocketCloseMutex);
}

int SocketServer::GetNumFreeSlots()
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

SocketData* SocketServer::GetFreeSocketData()
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

SocketData* SocketServer::GetSocketData(const char* pszIP, int iPort)
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (sd->bInUse && sd->bConnected && !lstrcmpi(sd->szIP, pszIP) && sd->iPort == iPort)
			return sd;
	}
	return NULL;
}

void SocketServer::SocketAccept(SOCKET s, sockaddr_in* addr)
{
	// Mutex Area
	EnterCriticalSection(&cSerSection);

	SocketData* sd = NULL;
	BOOL bAccepted = FALSE;

	if (IsFull() == FALSE)
	{
		BOOL bPass = TRUE;

		if (bPass)
		{
			if ((sd = GetFreeSocketData()))
			{
				sd->ud = NULL;

				CleanReconnectUsers();
				
				sd->Open(s, addr);

				AddNewPlayInfo(sd);				

				bAccepted = TRUE;
			}
		}
	}

	if (!bAccepted)
	{
		if (sd)
		{
			sd->UnInit();

			sd = NULL;
		}

		closesocket(s);
	}

	LeaveCriticalSection(&cSerSection);
}

void SocketServer::SocketPacket(SocketData* sd, PacketReceiving* p)
{
	pcMutex->Lock(5000);
	if (sd)
	{
		Player* ud = sd->ud;

		if (ud && ud->lpsmSock)
		{
			RecvMessage(sd, (char*)p->baPacket);
		}
		else
			WNDPROC_SOCKETCLOSE(hWnd, sd);

		sd->FreePacketReceiving(p);
		sd->dwTimeLastPacketReceived = GetCurrentTime();
	}
	if (pcMutex->Unlock())
	{
		//WRITEDBG( "Socket Packet [%d][0x%08X]", p->baPacket, p->sPacket.iHeader );
	}
}

void SocketServer::SocketClose(SocketData* sd)
{
	pcSocketCloseMutex->Lock(5005);

	if (sd && sd->bInUse)
	{
		sd->Close();
		sd->UnInit();
	}
	pcSocketCloseMutex->Unlock();
}

void SocketServer::Load()
{
	iMaxConnections = 300;

	pcaSocketData = new SocketData[iMaxConnections]();

	hEventSocket = CreateEvent(NULL, FALSE, FALSE, NULL);

	iNextSocket = 0;

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = FALSE;
		sd->Prepare(64, 64);
		sd->hReceiveThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&SocketServer::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&SocketServer::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}

	bActive = TRUE;
}

DWORD WINAPI SocketServer::Sender(SocketData* sd)
{
	SocketServer* m = GetInstance();

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketSending* p = nullptr;

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

DWORD WINAPI SocketServer::Receiver(SocketData* sd)
{
	SocketServer* m = GetInstance();

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketReceiving* p;
		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(GetInstance()->GetHWND(), WM_SOCKETPACKET, (WPARAM)sd, (LPARAM)p);
		}

		sd->bBlockSend = TRUE;

		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				if (sd->ud && sd->ud->dwObjectSerial && sd->ud->TransInfoFlag && sd->ud->getAccount().length() && sd->ud->getName().length())
					SOCKETSERVER->AddReconnectUser(sd);

				//Anti-DDoS
				if (sd->iRecvEC == 0x6A6A)
				{

					//m->AddBanIP(sd->lIP);
				}
				else
				{
					static char szLogDC[64] = { 0 };
					STRINGFORMAT(szLogDC, "SocketServer::Receiver() [%d]", sd->iRecvEC);
					//LOGSERVER->LogSocketClose(sd, szLogDC, _ReturnAddress());
				}

				WNDPROC_SOCKETCLOSE(m->GetHWND(), sd);
			}
		}

	} while (m->IsActive());

	return TRUE;
}

DWORD WINAPI SocketServer::Listener(SOCKET* ls)
{
	SOCKET s = *ls;
	SocketServer* pc = GetInstance();

	sockaddr_in* sout = new sockaddr_in;
	int len = sizeof(sockaddr_in);

	while (pc->IsActive())
	{
		SOCKET n = INVALID_SOCKET;
		if ((n = accept(s, (SOCKADDR*)sout, &len)) != INVALID_SOCKET)
		{
			//Send Accept Message
			SendMessageA(pc->GetHWND(), WM_SOCKETACCEPT, n, (LPARAM)sout);
		}
	}
	delete sout;

	return TRUE;
}

BOOL SocketServer::Init(HWND hwnd)
{
	hWnd = hwnd;

	Listen(SERVER_TCP_PORT);
	return TRUE;
}
void SocketServer::Listen(int iPort)
{
	int iStatus = 0;
	// Start
	if ((iStatus = WSAStartup(MAKEWORD(2, 2), &sWsaData)) != 0)
	{
		WRITEDBG("SocketServer::Init()WSAStartup():: %d", iStatus);
		return;
	}

	if ((sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
	{
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(iPort);

		if (::bind(sListenSocket, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
		{
			if (listen(sListenSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				WRITEDBG("SocketServer::Init()listen():: %d", WSAGetLastError());
				closesocket(sListenSocket);
				sListenSocket = INVALID_SOCKET;
				return;
			}
		}
		else
		{
			WRITEDBG("SocketServer::Init()bind():: %d", WSAGetLastError());
			closesocket(sListenSocket);
			sListenSocket = INVALID_SOCKET;
			return;
		}
	}
	else
	{
		WRITEDBG("SocketServer::Init()socket():: %d", WSAGetLastError());
		return;
	}

	bActive = TRUE;

	// Success
	hListener = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)Listener, &sListenSocket, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	Load();

}

void SocketServer::OnReadHandler(SOCKET s, DWORD dwParam)
{
	// Find Socket
	SocketData* sd = NULL;
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* p = pcaSocketData + i;
		if (p->bInUse && p->s == s)
		{
			sd = p;
			break;
		}
	}

	if (sd)
	{
		switch (dwParam)
		{
		case FD_READ:
			//    SetEvent( sd->hReceiveThreadSignal );
			break;

		case FD_CLOSE:
			//LOGSERVER->LogSocketClose(sd, "SocketServer::OnReadHandler()", _ReturnAddress());
			WNDPROC_SOCKETCLOSE(SOCKETSERVER->GetHWND(), sd);
			break;

		default:
			break;
		}
	}
}

void SocketServer::AddReconnectUser(SocketData* sd)
{
	return;

	pcReconnectMutex->Lock(5001);
	if (sd && sd->ud)
	{
		Player* lpPlayInfo = sd->ud;

		if (lpPlayInfo->dwObjectSerial)
		{
			auto it = vReconnectInfo.find(lpPlayInfo->dwObjectSerial);

			if (it == vReconnectInfo.end())
			{
				Player sPlayInfo = {};

				memcpy(&sPlayInfo, lpPlayInfo, sizeof(Player));
				sPlayInfo.lpsmSock = 0;

				if (lpPlayInfo->lpRecordDataBuff)
				{
					sPlayInfo.lpRecordDataBuff = new char[srRECORD_MEMORY_SIZE]();
					memcpy(sPlayInfo.lpRecordDataBuff, lpPlayInfo->lpRecordDataBuff, srRECORD_MEMORY_SIZE);
				}

				vReconnectInfo.emplace(lpPlayInfo->dwObjectSerial, sPlayInfo);
				RecordLog("RECONNECT", FormatString("IP %s - ID %s - Name %s - AddReconnectUser", sd->szIP, lpPlayInfo->getAccount().c_str(), lpPlayInfo->getName().c_str()));
			}
			else
			{
				char buff[255] = { 0 };
				wsprintf(buff, "add reconnect fail %s %d", lpPlayInfo->getName().c_str(), lpPlayInfo->dwObjectSerial);
				RecordLog("teste", buff);
			}
		}
	}
	pcReconnectMutex->Unlock();
}

bool SocketServer::TryReconnectUser(SocketData* sd, char* szName, DWORD dwNewSerial)
{
	if (!dwNewSerial)
		return false;

	bool bRet = false;
	pcReconnectMutex->Lock(5002);
	if (sd && sd->ud && !sd->ud->TransInfoFlag)
	{
		Player* lpPlayInfo = sd->ud;
		//auto it = vReconnectInfo.find(dwObjectSerial);
		DWORD serial = 0;
		for (auto it : vReconnectInfo)
		{
			if (!lstrcmpi(it.second.getName().c_str(), szName))
			{
				serial = it.first;
				break;
			}
		}

		auto it = vReconnectInfo.find(serial);

		if (it != vReconnectInfo.end())
		{
			Player& sBackupInfo = it->second;
			char* lpBuff = lpPlayInfo->lpRecordDataBuff;

			memcpy(lpPlayInfo, &sBackupInfo, sizeof(Player));
			lpPlayInfo->lpsmSock = sd;
			lpPlayInfo->lpRecordDataBuff = lpBuff;
			if (lpPlayInfo->lpRecordDataBuff && sBackupInfo.lpRecordDataBuff)
				memcpy(lpPlayInfo->lpRecordDataBuff, sBackupInfo.lpRecordDataBuff, srRECORD_MEMORY_SIZE);

			lpPlayInfo->dwObjectSerial = lpPlayInfo->smCharInfo.dwObjectSerial = dwNewSerial;

			delete[] sBackupInfo.lpRecordDataBuff;
			vReconnectInfo.erase(it);
			bRet = true;
			char buff[255];
			wsprintf(buff, "try reconnect success %s %d", szName, lpPlayInfo->dwObjectSerial);
			RecordLog("teste", buff);
		}
		else
		{
			char buff[255];
			wsprintf(buff, "try reconnect fail %s %d", szName, lpPlayInfo->dwObjectSerial);
			RecordLog("teste", buff);
		}
	}
	pcReconnectMutex->Unlock();
	return bRet;
}

extern DWORD dwPlayServTime;

void SocketServer::CleanReconnectUsers()
{
	pcReconnectMutex->Lock(5003);

	vector<DWORD> vDelets;

	for (auto it : vReconnectInfo)
	{
		if (it.second.dwLastRecvTime + (90 * 1000) < dwPlayServTime)
		{
			char buff[255];
			wsprintf(buff, "clean reconnect success %s", it.second.getName().c_str());
			RecordLog("teste", buff);
			vDelets.push_back(it.first);
		}
	}

	for (auto delet : vDelets)
		vReconnectInfo.erase(delet);

	pcReconnectMutex->Unlock();
}

void SocketServer::RemoveReconnectByAccount(string Account)
{
	pcReconnectMutex->Lock(5006);
	for (auto it : vReconnectInfo)
	{
		if (!it.second.getAccount().compare(Account))
		{
			vReconnectInfo.erase(it.first);
			break;
		}
	}
	pcReconnectMutex->Unlock();
}
