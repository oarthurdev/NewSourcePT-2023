#include "sinbaram/sinLinkHeader.h"
#include "cSkinChanger.h"
#include "field.h"
#include "Server/onserver.h"

extern int SendQuickMessage2(rsPLAYINFO *lpPlayInfo, char *szMessage);
extern int	rsDeleteInvenItem(rsPLAYINFO *lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
extern int srSetItemFromCode(psITEM *lpsItem, char *szCoed);
extern int	rsRegist_ItemSecCode(rsPLAYINFO *lpPlayInfo, TRANS_ITEMINFO *lpTransItemInfo, int NewItem);

extern sDEF_ITEMINFO* DefaultItems;
extern int DefaultItemCount;

cSKINCHANGER cSkinChanger;

void cSKINCHANGER::RecvSkinChange(SKINCHANGE_INFO* psPacket, rsPLAYINFO* lpPlayInfo)
{
	TRANS_ITEMINFO	TransItemInfo;

	if (rsDeleteInvenItem(lpPlayInfo, psPacket->scItem.CODE, psPacket->scItem.sItemInfo.ItemHeader.Head, psPacket->scItem.sItemInfo.ItemHeader.dwChkSum) < 0 || !CheckItemForm(&psPacket->scItem.sItemInfo))
	{
		SendQuickMessage2(lpPlayInfo, "> O item não foi encontrado.");
		return;
	}

	if (rsDeleteInvenItem(lpPlayInfo, psPacket->scStone.CODE, psPacket->scStone.sItemInfo.ItemHeader.Head, psPacket->scStone.sItemInfo.ItemHeader.dwChkSum) < 0 || !CheckItemForm(&psPacket->scStone.sItemInfo))
	{
		SendQuickMessage2(lpPlayInfo, "> A pedra não foi encontrada.");
		return;
	}

	TransItemInfo.code = OpCode::OPCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);

	memcpy(&TransItemInfo.Item, &psPacket->scItem.sItemInfo, sizeof(sITEMINFO));
	TransItemInfo.Item.CODE = psPacket->newCode;

	/*for (int cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if (DefaultItems[cnt].Item.CODE == psPacket->scStone.CODE)
		{
			if (DefaultItems[cnt].sDamage[1] || DefaultItems[cnt].sDamage[3])
			{
				TransItemInfo.Item.Damage[0] += DefaultItems[cnt].sDamage[1];
				TransItemInfo.Item.Damage[1] += DefaultItems[cnt].sDamage[3];
			}

			if (DefaultItems[cnt].sAttack_Rating[0])
				TransItemInfo.Item.Attack_Rating += DefaultItems[cnt].sAttack_Rating[0];

			if (DefaultItems[cnt].fAbsorb[0] != 0)
				TransItemInfo.Item.fAbsorb += DefaultItems[cnt].fAbsorb[0];

			if (DefaultItems[cnt].sDefence[0])
				TransItemInfo.Item.Defence += DefaultItems[cnt].sDefence[0];

			if (DefaultItems[cnt].fBlock_Rating[0] != 0)
				TransItemInfo.Item.fBlock_Rating += DefaultItems[cnt].fBlock_Rating[0];

			if (DefaultItems[cnt].fSpeed[0] != 0)
				TransItemInfo.Item.fSpeed += DefaultItems[cnt].fSpeed[0];

			if (DefaultItems[cnt].fMana_Regen[0] != 0)
				TransItemInfo.Item.fMana_Regen += DefaultItems[cnt].fMana_Regen[0];

			if (DefaultItems[cnt].fLife_Regen[0] != 0)
				TransItemInfo.Item.fLife_Regen += DefaultItems[cnt].fLife_Regen[0];

			if (DefaultItems[cnt].fStamina_Regen[0] != 0)
				TransItemInfo.Item.fStamina_Regen += DefaultItems[cnt].fStamina_Regen[0];

			if (DefaultItems[cnt].Increase_Life[0])
				TransItemInfo.Item.fIncrease_Life += (float)DefaultItems[cnt].Increase_Life[0];

			if (DefaultItems[cnt].Increase_Mana[0])
				TransItemInfo.Item.fIncrease_Mana += (float)DefaultItems[cnt].Increase_Mana[0];

			if (DefaultItems[cnt].Increase_Stamina[0])
				TransItemInfo.Item.fIncrease_Stamina += (float)DefaultItems[cnt].Increase_Stamina[0];
		}
	}*/

	ReformItem(&TransItemInfo.Item);

	rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

	lpPlayInfo->lpsmSock->Send((char*)&TransItemInfo, TransItemInfo.size, TRUE);
}


bool cSKINCHANGER::OpenSkinChange(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND sPacket;
	sPacket.code = OpCode::OPCODE_OPEN_SKINCHANGE;
	sPacket.size = sizeof(smTRANS_COMMAND);
	lpPlayInfo->lpsmSock->Send((char*)&sPacket, sPacket.size, TRUE);

	return true;
}
