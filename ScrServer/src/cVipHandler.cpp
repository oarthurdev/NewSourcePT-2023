#include "Server/onserver.h"
#include "cVipHandler.h"
#include "Database/Database.h"
#include "SocketServer/smwsock.h"

extern int SendQuickMessage(rsPLAYINFO* lpPlayInfo, char* szMessage);

void cVipHandler::InsertDB(rsPLAYINFO* lpPlayInfo, int IdVip , int time)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{
		char query[255] = { 0 };

		wsprintf(query, "INSERT INTO Vip  ([PlayerName],[IdVIp],[DateStart],[DateEnd]) values (?,?,GetDate(),DATEADD(DAY, %d, Getdate()))", time);

		if (db->Prepare(query))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->getName().c_str());
			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->BindInputParameter(&IdVip, 2, PARAMTYPE_Integer);
			db->Execute(false);
		}

		db->Close();
	}

	smTRANS_VIP sPacket;
	sPacket.code = OpCode::OPCODE_VIP;
	sPacket.size = sizeof(sPacket);
	sPacket.Vip = IdVip;
	sPacket.Until = time;
	sPacket.Ativo = TRUE;

	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);

	SendQuickMessage(lpPlayInfo, "/comandos para ver suas recompensas do VIP.");
}

void cVipHandler::IsVIp(rsPLAYINFO* lpPlayInfo)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_ServerDB);

	smTRANS_VIP sPacket;
	sPacket.code = OpCode::OPCODE_VIP;
	sPacket.size = sizeof(sPacket);

	if (db->Open())
	{
		if (db->Prepare("DELETE FROM Vip Where PlayerName = ? And GetDate() >= DateEnd"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->getName().c_str());

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);
			db->Execute(false);
		}

		if (db->Prepare("SELECT * FROM Vip Where PlayerName = ?"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->getName().c_str());

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);

			if (db->Execute())
			{

				db->GetData(&IdVip, 4, 2, PARAMTYPE_Integer);

				sPacket.Vip = IdVip;
				sPacket.Ativo = TRUE;
				lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
				SendQuickMessage(lpPlayInfo, "/comandos para ver suas recompensas do VIP.");
			}
		}

		db->Close();
	}

}

bool cVipHandler::returnVip(rsPLAYINFO* lpPlayInfo)
{
	std::shared_ptr<Database> db = Database::GetConnection(DATABASEID_ServerDB);

	if (db->Open())
	{

		if (db->Prepare("SELECT * FROM Vip Where PlayerName = ?"))
		{
			char playerName[32];  lstrcpy(playerName, lpPlayInfo->getName().c_str());

			db->BindInputParameter(playerName, 1, PARAMTYPE_String);

			if (db->Execute()) return true;
		}

		db->Close();
	}

	return false;
}
