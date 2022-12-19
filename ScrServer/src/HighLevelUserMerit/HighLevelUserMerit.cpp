#include <string>
#include <map>
#include "smPacket.h"
#include "SocketServer/smwsock.h"
#include "HighLevelUserMerit.h"
#include "Server/onserver.h"
#include "Database/Database.h"

namespace Midranda
{
	std::map<int, std::string> mapJobClassName = {
	{ JOBCODE_FIGHTER		, "Luchador" },
	{ JOBCODE_MECHANICIAN	, "Mecanico" },
	{ JOBCODE_ARCHER		, "Arquera" },
	{ JOBCODE_PIKEMAN		, "Pikeman" },
	{ JOBCODE_ATALANTA		, "Atalanta" },
	{ JOBCODE_KNIGHT		, "Caballero" },
	{ JOBCODE_MAGICIAN		, "Mago" },
	{ JOBCODE_PRIESTESS		, "Sacerdotisa" },
	{ JOBCODE_ASSASSINE		, "Assassina" },
	{ JOBCODE_SHAMAN		, "Xamã" }
//	{ JOBCODE_MARTIAL		, "Lutadora" }
	};

	std::map<int, std::string> mapTopRankerTitle = {
	{ JOBCODE_FIGHTER		, "Top Level" },
	{ JOBCODE_MECHANICIAN	, "Top Level" },
	{ JOBCODE_ARCHER		, "Top Level" },
	{ JOBCODE_PIKEMAN		, "Top Level" },
	{ JOBCODE_ATALANTA		, "Top Level" },
	{ JOBCODE_KNIGHT		, "Top Level" },
	{ JOBCODE_MAGICIAN		, "Top Level" },
	{ JOBCODE_PRIESTESS		, "Top Level" },
	{ JOBCODE_ASSASSINE		, "Top Level" },
	{ JOBCODE_SHAMAN		, "Top Level" }
	//{ JOBCODE_MARTIAL		, "Lutadora Marcial" }
	};

	std::string HighLevelUserMerit::getTopRankingTitle(const int jobcode)
	{
		std::string res = "";

		if (jobcode != -1)
		{
			auto& it = mapTopRankerTitle.find(jobcode);

			if (it != mapTopRankerTitle.end())
			{
				res = it->second;
			}
		}
		return res;
	}

	std::string HighLevelUserMerit::getJobName(const int jobCode)
	{
		std::string res = "";

		if (jobCode != -1)
		{
			auto& it = mapJobClassName.find(jobCode);

			if (it != mapJobClassName.end())
			{
				res = it->second;
			}
		}
		return res;
	}

	bool HighLevelUserMerit::isTopRanking(Player* player)
	{
		bool result = false;

		if (player)
		{
			char szCharClass[32] = { 0 };
			char szNick[32] = { 0 };

			auto db = Database::GetConnection(DATABASEID_rPTDB);

			if (db && db->Open())
			{
				if (db->Prepare("SELECT TOP 1 CharName FROM LevelList WHERE CharClass =? ORDER BY CharLevel DESC, DateUp ASC"))
				{
					std::string CharClass = HighLevelUserMerit::getJobName(player->smCharInfo.JOB_CODE);
					strcpy_s(szCharClass, sizeof(szCharClass), CharClass.c_str());

					db->BindInputParameter(szCharClass, 1, PARAMTYPE_String);

					if (db->Execute())
					{
						db->GetData(szNick, 32, 1, PARAMTYPE_String);

						std::string nickname = player->getName();

						result = nickname.compare(szNick) == 0;
					}
				}

				db->Close();
			}
		}

		return result;
	}

	void HighLevelUserMerit::broadcastTopRanking(Player* player)
	{
		if (player && HighLevelUserMerit::isTopRanking(player))
		{
			smTRANS_COMMAND smTransCommand = {};
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = OpCode::HIGH_LEVEL_USER;
			smTransCommand.LParam = player->dwObjectSerial;
			smTransCommand.WParam = player->smCharInfo.JOB_CODE;

			for (int cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
				}
			}
		}
	}

}