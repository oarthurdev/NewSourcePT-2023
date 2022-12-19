#include <map>
#include <string>
#include "HighLevelUserMerit.h"
#include "smPacket.h"

bool g_bTopRanker = false;

std::map<int, std::string> mapTopRankerTitle = {
{ JOBCODE_FIGHTER		, "Senhor da Guerra" },
{ JOBCODE_MECHANICIAN	, "Furia de Metal" },
{ JOBCODE_ARCHER		, "Guerreira Fenix" },
{ JOBCODE_PIKEMAN		, "Ceifador" },
{ JOBCODE_ATALANTA		, "Rainha da Valhalla" },
{ JOBCODE_KNIGHT		, "Cavaleiro Lendario" },
{ JOBCODE_MAGICIAN		, "Mestre Elemental" },
{ JOBCODE_PRIESTESS		, "Arcanjo" },
{ JOBCODE_ASSASSINE		, "Assassina Mestre" },
{ JOBCODE_SHAMAN		, "Grande Xamã" }
//{ JOBCODE_MARTIAL		, "Lutadora Marcial" }
};

std::string Midranda::HighLevelUserMerit::GetTopRankerTitle(const int jobCode)
{
	std::string res = "";

	if (jobCode != -1)
	{
		auto& it = mapTopRankerTitle.find(jobCode);

		if (it != mapTopRankerTitle.end())
		{
			res = it->second;
		}
	}

	return res;
}
