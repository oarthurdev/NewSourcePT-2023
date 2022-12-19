#include "sinbaram/sinLinkHeader.h"
#include "Server/onserver.h"
#include "cSorteio.h"

extern int srSetItemFromCode(psITEM* lpsItem, char* szCoed);
extern int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);
extern int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
extern int	rsDeleteInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

void cSorteio::SendSorteio(rsPLAYINFO * lpPlayInfo)
{

	if (SQL::GetInstance()->IsConnected())
	{
		int QtnItens = 0;
		char szItem[50][16];
		char MsgPlayer[255] = { 0 };
		SQL::GetInstance()->EnterSqlSection();

		if (SQL::GetInstance()->Execute("SELECT * FROM [PristonDB].[dbo].[RoletaItens]"))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, szItem[QtnItens]);
				QtnItens++;
			}

			if (QtnItens <= 0) return;

			int cnt = rand() % QtnItens;

			psITEM* lpsItem = new psITEM;
			TRANS_ITEMINFO	TransItemInfo;


			if (srSetItemFromCode(lpsItem, szItem[cnt]))
			{
				TransItemInfo.code = OpCode::OPCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));

				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

				lpPlayInfo->lpsmSock->Send((char *)&TransItemInfo, TransItemInfo.size, TRUE);

				wsprintf(MsgPlayer, "Roleta de Itens>  Parabéns %s acaba de ganhar um %s!", lpPlayInfo->getName().c_str(), lpsItem->ItemInfo.ItemName);
				rsSendServerChatMessageToUser(lpPlayInfo, 5, MsgPlayer);
			}

		}

	}
}

void cSorteio::RecvGetItemKeys(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand = {};
	int QtnsChaves = 0;

	for (int cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode == (sinSP1 | sin64))
			QtnsChaves++;
	}

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = OpCode::OPCODE_RECVKEYS_SORTEIO_ITENS;
	smTransCommand.WParam = QtnsChaves;
	lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

}


void cSorteio::OpenNpcSorteio(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND sPacket;
	sPacket.code = OpCode::OPCODE_OPEN_SORTEIO_ITENS;
	sPacket.size = sizeof(smTRANS_COMMAND);
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);
}

