#ifndef _SMWSOCK_HEADER
#define _SMWSOCK_HEADER

#include <array>
#include <Windows.h>
#include "NetType.h"

void InitGameSocket(int ThreadMode = 0);

void smEnterCSectionSocket();

void smLeaveCSectionSocket();

typedef DWORD(*LPFN_EncodePacket)(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff);
typedef DWORD(*LPFN_DecodePacket)(BYTE* lpPacket, BYTE* lpDecBuff);

extern LPFN_EncodePacket fnEncodePacket;
extern LPFN_DecodePacket fnDecodePacket;

#define	POS_ENC_START	0x0
#define	POS_ENC_PACCODE 0xB
#define POS_ENC_XOR		0x74

#define	POS_DEC_START	0xA0
#define	POS_DEC_XOR		0x11A

#define	ENC_PACKET_ASM_SIZE	0x150

extern BYTE smwsock_EncodePacket_AsmCode[ENC_PACKET_ASM_SIZE];

#include "SocketServer.h"

#endif
