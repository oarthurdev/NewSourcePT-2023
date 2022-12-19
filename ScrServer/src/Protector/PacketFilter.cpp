//#include "StdAfx.h"
#include "PacketFilter.h"

PacketFilter::PacketFilter(const char* Packet, const size_t Length) : m_Packet(Packet), m_Length(Length)
{
}

PacketFilter::~PacketFilter()
{
}

bool PacketFilter::IsSafeToProcess() const
{
	if (m_Packet == nullptr || m_Length < 8 || m_Length > smSOCKBUFF_SIZE)
		return false;

	LPCSTR PacketBuffer = nullptr;
	DWORD PacketCode = ((DWORD*)m_Packet)[1];

	if (PacketCode == OpCode::OPCODE_SYSTEM)
		return false;

	if (PacketCode == OpCode::OPCODE_CHATMESSAGE || PacketCode == OpCode::OPCODE_PARTY_CHATMSG)
	{
		PacketBuffer = &m_Packet[8];

		if (strlen(PacketBuffer) > 255)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_TRANSPLAYDATA)
	{
		if (m_Length > TRANS_BUFF_SIZE)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_RECORDDATA)
	{
		TRANS_RECORD_DATAS* TransRecord = (TRANS_RECORD_DATAS*)m_Packet;

		if (TransRecord->Count < 0 || TransRecord->Count > 100 ||
			TransRecord->TransSize < 0 || TransRecord->TransSize > sizeof(TransRecord->szData))
			return false;

		if (TransRecord->TransSize + (TransRecord->Count * TRANS_RECORD_LEN) >= sizeof(TRANS_RECORD_DATA))
			return false;

	}
	else if (PacketCode == OpCode::OPCODE_GETRECORDDATA)
	{
		smTRANS_CHAR_COMMAND* TransCharCommand = (smTRANS_CHAR_COMMAND*)m_Packet;
		if (strlen(TransCharCommand->szName) > 31)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_INSRECORDDATA ||
		PacketCode == OpCode::OPCODE_DELRECORDDATA ||
		PacketCode == OpCode::OPCODE_ISRECORDDATA ||
		PacketCode == OpCode::OPCODE_USER_ID)
	{
		smTRANS_CHAR_COMMAND2* TransCharCommand = (smTRANS_CHAR_COMMAND2*)m_Packet;
		if (strlen(TransCharCommand->szId) > 31 ||
			strlen(TransCharCommand->szName) > 31)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_SAVETHROWITEMS)
	{
		TRANS_THROW_ITEMS* ThrowItems = (TRANS_THROW_ITEMS*)m_Packet;
		if (ThrowItems->ThrowItemCount > 64)
			return false;
	}
	/*else if (PacketCode == OpCode::OPCODE_MODULE_WARNIG)
	{
		TRANS_CHATMESSAGE * ChatMessage = (TRANS_CHATMESSAGE *)m_Packet;
		if (ChatMessage->dwIP > 255)
			return false;
	}*/
	else if (PacketCode == OpCode::OPCODE_OPENMONSTER || PacketCode == OpCode::OPCODE_CHECKIP)
	{
		smTRANS_CHAR_COMMAND* TransCharCommand = (smTRANS_CHAR_COMMAND*)m_Packet;
		if (strlen(TransCharCommand->szName) > 31)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_PARTY_PLAYUPDATE)
	{
		TRANS_PARTY_PLAYINFO* PartyPlayInfo = (TRANS_PARTY_PLAYINFO*)m_Packet;
		if (PartyPlayInfo->PartyUserCount > 6)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_AGINGITEM)
	{
		sCRAFTITEM_SERVER* AgingItem = (sCRAFTITEM_SERVER*)m_Packet;
		if (AgingItem->DesCraftItem.sItemInfo.ItemAgingNum[0] < 0 ||
			AgingItem->DesCraftItem.sItemInfo.ItemAgingNum[0] > MAX_AGING)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_WINGITEM)
	{
		sCRAFTITEM_SERVER* WingItem = (sCRAFTITEM_SERVER*)m_Packet;
		if (WingItem->Index < 0 || WingItem->Index > 10)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_INVEN_POSITION || PacketCode == OpCode::OPCODE_INVEN_POSITION2)
	{
		TRANS_USINGITEM* UsingItem = (TRANS_USINGITEM*)m_Packet;
		if (UsingItem->ItemListCount > 16)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_PARTY_SKILL)
	{
		TRANS_PARTY_SKILL* PartySkill = (TRANS_PARTY_SKILL*)m_Packet;
		if (PartySkill->PartyCount > 8)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_OPENLIVE || PacketCode == OpCode::OPCODE_AGING_DATA)
	{
		return false;
	}
	else if (PacketCode == OpCode::OPCODE_REC_ADMIN_COMMAND)
	{
		TRANS_CHATMESSAGE* ChatMessage = (TRANS_CHATMESSAGE*)m_Packet;
		if (strlen(ChatMessage->szMessage) > 255)
			return false;
	}
	else if (PacketCode == OpCode::OPCODE_HACKTRAP)
	{
		smTRANS_COMMAND* TransCommand = (smTRANS_COMMAND*)m_Packet;
		if (TransCommand->SParam > 50 || TransCommand->SParam < 0)
			return false;
	}

	return true;
}

void PacketFilter::LogPacket(rsPLAYINFO* Player) const
{
	if (Player && Player->lpsmSock)
	{
		std::ofstream LogFile;

		std::time_t tt = std::time(0);
		std::tm ttm = *std::localtime(&tt);

		char szFileName[256] = { 0 };
		sprintf_s(szFileName, "LogFile\\(Protector)%d-%d.log", ttm.tm_mday, ttm.tm_mon + 1);

		LogFile.open(szFileName, std::ios::app);

		if (LogFile.is_open())
		{
			char szBuff[256] = { 0 };
			sprintf_s(szBuff, "ID( %s ) Name( %s ) IP( %s ) - PacketFiltered( %d - %d )", Player->getAccount().c_str(), Player->getName().c_str(), Player->lpsmSock->szIP, ((DWORD*)m_Packet)[1], ((DWORD*)m_Packet)[0]);
			LogFile << "\n" << ttm.tm_hour << ":" << ttm.tm_min << ":" << ttm.tm_sec << "\t" << szBuff;
		}

		LogFile.close();
	}
}

void PacketFilter::DumpPacket(rsPLAYINFO* Player) const
{
	if (Player && Player->lpsmSock && m_Packet)
	{
		DWORD PacketCode = ((DWORD*)m_Packet)[1];

		if (PacketCode != OpCode::OPCODE_TRANSPLAYDATA &&
			PacketCode != OpCode::OPCODE_GETPLAYERINFO &&
			PacketCode != OpCode::OPCODE_CHECK_NETSTATE &&
			PacketCode != OpCode::OPCODE_ATTACK_DAMAGE)
		{
			std::ofstream LogFile;

			std::time_t tt = std::time(0);
			std::tm ttm = *std::localtime(&tt);

			char szFileName[256] = { 0 };
			sprintf_s(szFileName, "LogFile\\(Dumps)%d-%d.log", ttm.tm_mday, ttm.tm_mon + 1);

			LogFile.open(szFileName, std::ios::app);

			if (LogFile.is_open())
			{
				char szBuff[256] = { 0 };
				sprintf_s(szBuff, "ID( %s ) Name( %s ) IP( %s ) - DumpPacket( %d - %d )", Player->getAccount().c_str(), Player->getName().c_str(), Player->lpsmSock->szIP, ((DWORD*)m_Packet)[1], ((DWORD*)m_Packet)[0]);
				LogFile << "\n" << ttm.tm_hour << ":" << ttm.tm_min << ":" << ttm.tm_sec << "\t" << szBuff;
			}

			LogFile.close();
		}
	}
}
