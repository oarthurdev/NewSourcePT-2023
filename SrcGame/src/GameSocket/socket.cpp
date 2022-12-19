//#include "sinbaram/sinLinkHeader.h"

#include "Utils/CMutex.h"
#include "socket.h"

const BOOL SOCKET_NODELAY = TRUE;

const int RCVWND_SIZE = 0x800000;
const int SNDWND_SIZE = 0x800000;

SocketData::SocketData()
{
	bInUse = false;
	bConnecting = false;
	bConnected = false;

	//Sending
	iDefSendPacket = 0;
	iMaxSendPacket = 0;
	iSendWheel = 0;
	iSendingWheel = 0;
	psaPacketSending = NULL;

	bBlockSend = TRUE;

	dwBulkThreadId = 0;
	sBulkPacket.bInUse = FALSE;

	//Receiving
	iDefReceivePacket = 0;
	iMaxReceivePacket = 0;
	iReceiveWheel = 0;
	psaPacketReceiving = NULL;

	hReceiveThreadSignal = CreateEvent(NULL, FALSE, FALSE, NULL);
	pcReceiveMutex = new CMutex("Socket Receive");
	hSendEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hSendThreadSignal = CreateEvent(NULL, FALSE, FALSE, NULL);
	pcSendMutex = new CMutex("Socket Send");
}

SocketData::~SocketData()
{
	DELET(pcSendMutex);
	CloseHandle(hSendThreadSignal);
	CloseHandle(hSendEvent);
	DELET(pcReceiveMutex);
	CloseHandle(hReceiveThreadSignal);

	DELETA(psaPacketReceiving);

	DELETA(psaPacketSending);
}

void SocketData::Prepare(UINT iMaxSendPacket, UINT iMaxReceivePacket)
{
	DELETA(psaPacketReceiving);

	DELETA(psaPacketSending);

	if (this->iDefReceivePacket == 0)
	{
		//Only default the first time
		this->iDefReceivePacket = iMaxReceivePacket;
	}

	if (this->iDefSendPacket == 0)
	{
		//Only default the first time
		this->iDefSendPacket = iMaxSendPacket;
	}

	this->iMaxSendPacket = iMaxSendPacket;
	this->iSendWheel = 0;
	this->iSendingWheel = 0;
	this->psaPacketSending = new PacketSending[iMaxSendPacket];

	this->iMaxReceivePacket = iMaxReceivePacket;
	this->iReceiveWheel = 0;
	this->psaPacketReceiving = new PacketReceiving[iMaxReceivePacket];
}

void SocketData::Init()
{
	bInUse = true;
	bConnecting = false;
	bConnected = false;

	//Sending
	iSendWheel = 0;
	iSendingWheel = 0;

	for (UINT i = 0; i < iMaxSendPacket; i++)
	{
		PacketSending* pp = psaPacketSending + i;

		ZeroMemory(pp, sizeof(PacketSending));

		pp->bInUse = FALSE;
	}

	dwBulkThreadId = 0;
	sBulkPacket.bInUse = FALSE;

	//Receiving
	iReceiveWheel = 0;

	for (UINT i = 0; i < iMaxReceivePacket; i++)
	{
		PacketReceiving* pp = psaPacketReceiving + i;

		ZeroMemory(pp, sizeof(PacketReceiving));

		pp->bInUse = FALSE;
	}

	iRecvRet = -10;
	iRecvEC = -10;
	iSendRet = -10;
	iSendEC = -10;

	bKeepAlive = FALSE;
}

void SocketData::UnInit()
{
	bConnected = false;
	bConnecting = false;
	bInUse = false;
}

bool SocketData::Connect(const char* pszIP, int iPort)
{
	bool ret = false;

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s != INVALID_SOCKET)
	{
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(pszIP);
		sin.sin_port = htons(iPort);

		lstrcpy(this->szIP, pszIP);
		this->iPort = iPort;
		bConnecting = true;

		if (connect(s, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
		{
			Open(s, &sin);

			ret = true;
		}

		bConnecting = false;
	}

	return ret;
}

void SocketData::Open(SOCKET s, sockaddr_in* addr)
{
	this->s = s;
	this->lIP = addr->sin_addr.s_addr;
	this->iPort = ntohs(addr->sin_port);
	lstrcpy(this->szIP, inet_ntoa(addr->sin_addr));

	dwTimeLastPacketReceived = 0;

	bPing = false;
	iPing = 0;
	iCountIN = 0;
	iCountOUT = 0;
	iCountOUTB = 0;

	bConnected = true;

	iRecvRet = -10;
	iRecvEC = -10;
	iSendRet = -10;
	iSendEC = -10;

	bKeepAlive = FALSE;

	//Nagle Algorithm
	setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char*)&SOCKET_NODELAY, sizeof(BOOL));

	//Set Receive and Send Window sizes
	setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char*)&RCVWND_SIZE, sizeof(int));
	setsockopt(s, SOL_SOCKET, SO_SNDBUF, (char*)&SNDWND_SIZE, sizeof(int));

	ResetEvent(hSendEvent);

	SetEvent(hReceiveThreadSignal);
	SetEvent(hSendThreadSignal);

	bBlockSend = FALSE;
}

void SocketData::Ping(DWORD dwTime)
{
	bPing = true;
	dwPingTime = dwTime;

	PacketPing p;
	p.size = sizeof(p);
	p.code = OpCode::MSG_PING;
	p.dwTime = dwTime;

	SendPacket(&p);
}

void SocketData::Close()
{
	bConnected = false;
	bBlockSend = TRUE;

	SetEvent(hSendEvent);

	closesocket(s);
}

PacketReceiving* SocketData::FreePacketReceiving()
{
	pcReceiveMutex->Lock();

	int iFree = iReceiveWheel % iMaxReceivePacket;

	PacketReceiving* ret = psaPacketReceiving + iFree;

	if (ret->bInUse == FALSE)
	{
		ret->bInUse = TRUE;
		ret->bDelete = FALSE;

		iReceiveWheel++;

		pcReceiveMutex->Unlock();
	}
	else
	{
		pcReceiveMutex->Unlock();

		ret = new PacketReceiving;
		ret->bInUse = TRUE;
		ret->bDelete = TRUE;
	}

	return ret;
}

void SocketData::FreePacketReceiving(PacketReceiving* pp)
{
	if (pp->bDelete == FALSE)
	{
		pcReceiveMutex->Lock();

		pp->bInUse = FALSE;

		pcReceiveMutex->Unlock();
	}
	else
	{
		delete pp;
	}
}

PacketReceiving* SocketData::ReceivePacket()
{
	WORD offset = 0;

	PacketReceiving* pp = FreePacketReceiving();

	if (pp == NULL)
	{
		iRecvRet = -1;
		iRecvEC = -1;
		return NULL;
	}

	BYTE* baReceiveBuffer = pp->baPacket;

	int iBytesReceived = 0;
	while ((iBytesReceived = recv(s, (char*)(baReceiveBuffer + offset), sizeof(WORD) - offset, 0)) > 0)
	{
		offset += iBytesReceived;

		if (offset < sizeof(WORD))
			continue;

		WORD sPacketLength = *(WORD*)baReceiveBuffer;

		if (sPacketLength < sizeof(Packet))
		{
			iBytesReceived = 0;
			offset = 0;
			continue;
		}

		if (sPacketLength > smSOCKBUFF_SIZE)
		{
			//WRITEDBG("ReceivePacket() ERROR: %d Bytes Expected, Max %d!", sPacketLength, smSOCKBUFF_SIZE);
			iRecvEC = 0x6A6A;
			FreePacketReceiving(pp);
			return NULL;
		}

		while ((iBytesReceived = recv(s, (char*)(baReceiveBuffer + offset), sPacketLength - offset, 0)) > 0)
		{
			offset += iBytesReceived;

			if (offset == sPacketLength)
				return pp;
			else if (offset > sPacketLength)
			{
				//WRITEDBG("ReceivePacket() ERROR: offset %d > sPacketLength %d", offset, sPacketLength);
				iRecvEC = 0x6A6A;
				FreePacketReceiving(pp);
				return NULL;
			}
		}

		break;
	}

	iRecvRet = iBytesReceived;
	iRecvEC = WSAGetLastError();

	iCountIN += iBytesReceived;

	FreePacketReceiving(pp);
	return NULL;
}

PacketSending* SocketData::NextPacketSending()
{
	while (bConnected)
	{
		pcSendMutex->Lock();

		if (iSendWheel > iSendingWheel)
		{
			PacketSending* ps = psaPacketSending + (iSendingWheel % iMaxSendPacket);

			if (ps->bInUse)
			{
				iSendingWheel++;

				pcSendMutex->Unlock();

				return ps;
			}
		}

		pcSendMutex->Unlock();

		WaitForSingleObject(hSendEvent, INFINITE);
	}

	return NULL;
}

void SocketData::FreePacketSending(PacketSending* pp)
{
	pcSendMutex->Lock();

	pp->bInUse = FALSE;

	pcSendMutex->Unlock();
}

BOOL SocketData::Send(BYTE* pbData, UINT uSize)
{
	UINT uDataSent = 0;
	while (uSize > uDataSent)
	{
		int iSendVal = send(s, (const char*)(pbData + uDataSent), uSize - uDataSent, 0);

		if (iSendVal < 0)
		{
			DWORD dwError = WSAGetLastError();

			iSendEC = dwError;
			//WRITEDBG("send() failed (%d)", dwError);
			return FALSE;
		}

		uDataSent += iSendVal;
	}

	iCountOUT++;

	return TRUE;
}

BOOL SocketData::SendData(BYTE* pbData, UINT uSize)
{
	//WRITEDBG( "SocketData::SendPacket( 0x%04X )", uSize );

	if (bBlockSend)
		return FALSE;

	if (uSize == 0)
		return TRUE;

	if (uSize > smSOCKBUFF_SIZE)
		return FALSE;

	pcSendMutex->Lock();

	//Use Automatic Bulking if possible and enabled
	PacketSending* ps = FindAutomaticBulk(uSize);

	if (ps)
	{
		CopyMemory(ps->baPacket + ps->uSize, pbData, uSize);
		ps->uSize += uSize;

		pcSendMutex->Unlock();

		return TRUE;
	}
	else
	{
		ps = psaPacketSending + (iSendWheel % iMaxSendPacket);

		//Should not be in use..
		if (!ps->bInUse)
		{
			ps->bInUse = TRUE;
			ps->uSize = uSize;
			CopyMemory(ps->baPacket, pbData, uSize);

			iSendWheel++;

			SetEvent(hSendEvent);

			pcSendMutex->Unlock();

			return TRUE;
		}
	}

	pcSendMutex->Unlock();

	return FALSE;
}

PacketSending* SocketData::FindAutomaticBulk(UINT uSizeNeeded)
{
	//Automatically Bulk to the last Waiting Packet to send, if available
	if (iSendWheel > iSendingWheel)
	{
		UINT iWaitingSend = iSendWheel - 1;

		PacketSending* ps = psaPacketSending + (iWaitingSend % iMaxSendPacket);

		//This Waiting Packet to send should be in use..
		if (ps->bInUse)
		{
			//Enough Space Available to use for Packet requesting to Bulk?
			if ((ps->uSize + uSizeNeeded) <= smSOCKBUFF_SIZE)
				return ps;
		}
	}

	return NULL;
}

BOOL SocketData::Send(PacketSending* pp)
{
	//WRITEDBG( "SocketData::Send() Size[%d]", pp->uSize );

	//Encrypted all Packets contained (more than 1 if PacketSending is used in Bulking)
	UINT uPosition = 0;
	while (uPosition < pp->uSize)
	{
		Packet* psPacket = (Packet*)(pp->baPacket + uPosition);

		uPosition += psPacket->size;
		iCountOUT += psPacket->size;

		iCountOUTB++;
	}

	//Send all Packets contained (more than 1 if Bulked)
	Send(pp->baPacket, pp->uSize);

	return TRUE;
}

BOOL SocketData::SendPacket(Packet* p, BOOL bEncrypted)
{
	//WRITEDBG( "SocketData::SendPacket( [0x%04X][0x%08X] )", p->iLength, p->iHeader );

	if (p->size > smSOCKBUFF_SIZE)
		return FALSE;

	pcSendMutex->Lock();

	//Is Forced Bulk Sending Activated? (not sent until flushed)
	if (sBulkPacket.uCount > 0)
	{
		//Bulk Sending Initiating Thread is same as current Thread?
		if (dwBulkThreadId == GetCurrentThreadId())
		{
			pcSendMutex->Unlock();

			UINT uNewSize = sBulkPacket.uSize + p->size;

			if (uNewSize > smSOCKBUFF_SIZE)
			{
				if (FlushBulkSend() == FALSE)
					return FALSE;
			}

			UINT uPosition = sBulkPacket.uSize;

			CopyMemory(sBulkPacket.baPacket + uPosition, p, p->size);

			sBulkPacket.uSize = uPosition + p->size;

			return TRUE;
		}
	}

	//No Forced Bulk Sending.. so Send seperately or if possible Bulk automatically (sent instantly)
	BOOL bRet = SendData((BYTE*)p, p->size);

	pcSendMutex->Unlock();

	return bRet;
}

BOOL SocketData::SendPacketBlank(DWORD iHeader, BOOL bEncrypted)
{
	Packet s;
	s.size = sizeof(s);
	s.code = static_cast<OpCode>(iHeader);

	return SendPacket(&s, bEncrypted);
}

BOOL SocketData::Send(char* Buff, int size, int Flag)
{
	return SendPacket((Packet*)Buff);
}

BOOL SocketData::Send2(char* Buff, int size, int Flag)
{
	return Send(Buff, size, Flag);
}

BOOL SocketData::Send3(char* Buff, int size, int Flag)
{
	return Send(Buff, size, Flag);
}

BOOL SocketData::StartBulkSend()
{
	pcSendMutex->Lock();

	if (sBulkPacket.uCount > 0)
	{
		if (dwBulkThreadId != GetCurrentThreadId())
		{
			pcSendMutex->Unlock();

			return FALSE;
		}

		sBulkPacket.uCount++;

		pcSendMutex->Unlock();

		return TRUE;
	}

	dwBulkThreadId = GetCurrentThreadId();

	sBulkPacket.uCount = 1;
	sBulkPacket.uSize = 0;

	pcSendMutex->Unlock();

	return TRUE;
}

BOOL SocketData::FlushBulkSend()
{
	pcSendMutex->Lock();

	if (sBulkPacket.uCount == 0)
	{
		pcSendMutex->Unlock();

		return FALSE;
	}

	if (dwBulkThreadId != GetCurrentThreadId())
	{
		pcSendMutex->Unlock();

		return FALSE;
	}

	if (sBulkPacket.uSize > 0)
	{
		if (SendData(sBulkPacket.baPacket, sBulkPacket.uSize) == FALSE)
		{
			pcSendMutex->Unlock();

			return FALSE;
		}

		sBulkPacket.uSize = 0;
	}

	pcSendMutex->Unlock();

	return TRUE;
}

BOOL SocketData::StopBulkSend()
{
	pcSendMutex->Lock();

	if (sBulkPacket.uCount == 0)
	{
		pcSendMutex->Unlock();

		return FALSE;
	}

	if (dwBulkThreadId != GetCurrentThreadId())
	{
		pcSendMutex->Unlock();

		return FALSE;
	}

	sBulkPacket.uCount--;

	if (sBulkPacket.uCount == 0)
	{
		//Flush
		if (sBulkPacket.uSize > 0)
		{
			SendData(sBulkPacket.baPacket, sBulkPacket.uSize);

			sBulkPacket.uSize = 0;
		}
	}

	pcSendMutex->Unlock();

	return TRUE;
}

int SocketData::GetPing(DWORD dwTime)
{
	if (bPing)
		return dwTime - dwPingTime;

	return iPing;
}