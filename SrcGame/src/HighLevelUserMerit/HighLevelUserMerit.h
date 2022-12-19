#ifndef HIGH_LEVEL_USER_MERIT_H
#define HIGH_LEVEL_USER_MERIT_H

#include <string>

namespace Midranda
{
	class HighLevelUserMerit
	{
	public:
		static std::string GetTopRankerTitle(const int jobCode);
	};
}
extern bool g_bTopRanker;

#endif // HIGH_LEVEL_USER_MERIT_H