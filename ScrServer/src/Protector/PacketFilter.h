#pragma once
#include "..\\SinBaram\\sinLinkHeader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

class PacketFilter
{
public:
	PacketFilter(const char* Packet, const size_t Length);
	~PacketFilter();

	bool IsSafeToProcess() const;
	void LogPacket(rsPLAYINFO* Player) const;
	void DumpPacket(rsPLAYINFO* Player) const;

private:
	const char* m_Packet;
	const size_t m_Length;
};
