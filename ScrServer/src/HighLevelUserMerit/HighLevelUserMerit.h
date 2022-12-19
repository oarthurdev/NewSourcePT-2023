#ifndef HIGH_LEVEL_USER_MERIT_H
#define HIGH_LEVEL_USER_MERIT_H

#include <string>
#include "smPacket.h"

namespace Midranda
{
	class HighLevelUserMerit
	{
	public:
		static bool isTopRanking(Player* player);
		static void broadcastTopRanking(Player* player);
		static std::string getJobName(const int jobCode);
		static std::string getTopRankingTitle(const int jobcode);
	};
}

#endif // HIGH_LEVEL_USER_MERIT_H