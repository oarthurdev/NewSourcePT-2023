#pragma warning( disable : 4244 )
#include "sinbaram/sinLinkHeader.h"
#include "cSkinChanger.h"

extern bool isMousePos(int x, int y, int w, int h);

cSKINCHANGER cSkinChanger;

map<DWORD, DWORD> vSkinCodes = {

 { sinSK1 | sin01, sinWA1 | sin05 },
 { sinSK1 | sin02, sinWA1 | sin07 },
 { sinSK1 | sin03, sinWC1 | sin06 },
 { sinSK1 | sin04, sinWH1 | sin08 },
 { sinSK1 | sin05, sinWM1 | sin08 },
 { sinSK1 | sin06, sinWP1 | sin05 },
 { sinSK1 | sin07, sinWS1 | sin06 },
 { sinSK1 | sin08, sinWS2 | sin12 },
 { sinSK1 | sin09, sinWT1 | sin05 },
 { sinSK1 | sin10, sinDS1 | sin07 },
 { sinSK1 | sin11, sinDA1 | sin14 },
 { sinSK1 | sin12, sinDA2 | sin14 },

 //

 { sinSK1 | sin13, sinWA1 | sin05 },
 { sinSK1 | sin14, sinWA1 | sin07 },
 { sinSK1 | sin15, sinWC1 | sin06 },
 { sinSK1 | sin16, sinWH1 | sin08 },
 { sinSK1 | sin17, sinWM1 | sin08 },
 { sinSK1 | sin18, sinWP1 | sin05 },
 { sinSK1 | sin19, sinWS1 | sin06 },
 { sinSK1 | sin20, sinWS2 | sin12 },
 { sinSK1 | sin21, sinWT1 | sin05 },
 { sinSK1 | sin22, sinDS1 | sin07 },
 { sinSK1 | sin23, sinDA1 | sin14 },
 { sinSK1 | sin24, sinDA2 | sin14 },


};

void cSKINCHANGER::Init()
{
	lpBackground = LoadDibSurfaceOffscreen("image\\sinimage\\shopall\\modifyitem\\skinchange.bmp");
	lpButton = LoadDibSurfaceOffscreen("image\\sinimage\\shopall\\modifyitem\\button.bmp");
}

void cSKINCHANGER::Draw()
{
	if (!OpenFlag)
		return;

	BaseX = 50;
	BaseY = 40;

	DrawSprite(BaseX, BaseY, lpBackground, 0, 0, 352, 362);

	if (isMousePos(BaseX + 162, BaseY + 166, 26, 26))
		DrawSprite(BaseX + 162, BaseY + 166, lpButton, 0, 0, 26, 26);

	if (scItem.Flag)
	{
		if (scItem.lpItem)
			DrawSprite(scItem.x, scItem.y, scItem.lpItem, 0, 0, scItem.w, scItem.h);
	}

	if (scStone.Flag)
	{
		if (scStone.lpItem)
			DrawSprite(scStone.x, scStone.y, scStone.lpItem, 0, 0, scStone.w, scStone.h);
	}

	if (isMousePos(BaseX + 62, BaseY + 137, 66, 88))
	{
		if (scItem.Flag)
		{
			cItem.ShowItemInfo(&scItem, 1);
			sinShowItemInfoFlag = 1;
		}

		if (MouseItem.Flag)
		{
			if (!SetSkinChangerItemAreaCheck(&MouseItem, 1))
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(255, 0, 0, 128), BaseX + 62, BaseY + 137, 66, 88);
			else
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(0, 255, 0, 128), BaseX + 62, BaseY + 137, 66, 88);
		}
	}

	if (isMousePos(BaseX + 163, BaseY + 243, 22, 22))
	{
		if (scStone.Flag)
		{
			cItem.ShowItemInfo(&scStone, 1);
			sinShowItemInfoFlag = 1;
		}

		if (MouseItem.Flag)
		{
			if (!SetSkinChangerItemAreaCheck(&MouseItem, 2))
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(255, 0, 0, 128), BaseX + 163, BaseY + 243, 22, 22);
			else
				dsDrawColorBoxFloat(D3DCOLOR_RGBA(0, 255, 0, 128), BaseX + 163, BaseY + 243, 22, 22);
		}
	}

	if (scStone.Flag && scItem.Flag)
	{
		auto it = vSkinCodes.find(scStone.CODE);

		if (it != vSkinCodes.end())
		{
			sITEM* pItem = GetItem(it->second);
			LPDIRECT3DTEXTURE9 lpItem;

			lpItem = GetItemImage(pItem);

			if (lpItem)
			{
				DrawSprite(BaseX + 222 + ((66 - pItem->w) / 2), BaseY + 137 + ((88 - pItem->h) / 2), lpItem, 0, 0, pItem->w, pItem->h);
			}
		}
	}
}

bool cSKINCHANGER::LButtonDown()
{
	if (!OpenFlag)
		return false;

	if (isMousePos(BaseX + 162, BaseY + 166, 26, 26))
	{
		if (scItem.Flag && scStone.Flag)
		{
			SKINCHANGE_INFO sPacket;
			sPacket.size = sizeof(SKINCHANGE_INFO);
			sPacket.code = OpCode::OPCODE_SKINCHANGE;

			memcpy(&sPacket.scItem, &scItem, sizeof(sITEM));
			memcpy(&sPacket.scStone, &scStone, sizeof(sITEM));

			auto it = vSkinCodes.find(scStone.CODE);
			if (it != vSkinCodes.end())
				sPacket.newCode = it->second;

			smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

			scItem.Flag = false;
			scStone.Flag = false;
			Close();
		}
		return true;
	}

	if (isMousePos(BaseX + 62, BaseY + 137, 66, 88))
	{
		if (MouseItem.Flag)
		{
			if (SetSkinChangerItemAreaCheck(&MouseItem, 1))
			{
				if (!scItem.Flag)
				{
					memcpy(&scItem, &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));

					scItem.x = scItem.SetX = (BaseX + 62 + ((66 - scItem.w) / 2));
					scItem.y = scItem.SetY = (BaseY + 137 + ((88 - scItem.h) / 2));
				}
				else
				{
					sITEM backup;

					memcpy(&backup, &scItem, sizeof(sITEM));
					memcpy(&scItem, &MouseItem, sizeof(sITEM));
					memcpy(&MouseItem, &backup, sizeof(sITEM));

					scItem.x = scItem.SetX = (BaseX + 62 + ((66 - scItem.w) / 2));
					scItem.y = scItem.SetY = (BaseY + 137 + ((88 - scItem.h) / 2));
				}
			}
		}
		else
		{
			if (scItem.Flag)
			{
				memcpy(&MouseItem, &scItem, sizeof(sITEM));
				ZeroMemory(&scItem, sizeof(sITEM));
			}
		}
		return true;
	}

	if (isMousePos(BaseX + 163, BaseY + 243, 22, 22))
	{
		if (MouseItem.Flag)
		{
			if (SetSkinChangerItemAreaCheck(&MouseItem, 2))
			{
				if (!scStone.Flag)
				{
					memcpy(&scStone, &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));

					scStone.x = scStone.SetX = (BaseX + 163 + ((22 - scStone.w) / 2));
					scStone.y = scStone.SetY = (BaseY + 243 + ((22 - scStone.h) / 2));
				}
				else
				{
					sITEM backup;

					memcpy(&backup, &scStone, sizeof(sITEM));
					memcpy(&scStone, &MouseItem, sizeof(sITEM));
					memcpy(&MouseItem, &backup, sizeof(sITEM));

					scStone.x = scStone.SetX = (BaseX + 163 + ((22 - scStone.w) / 2));
					scStone.y = scStone.SetY = (BaseY + 243 + ((22 - scStone.h) / 2));
				}
			}
		}
		else
		{
			if (scStone.Flag)
			{
				memcpy(&MouseItem, &scStone, sizeof(sITEM));
				ZeroMemory(&scStone, sizeof(sITEM));
			}
		}
		return true;
	}

	if (isMousePos(BaseX + 329, BaseY + 0, 23, 21))
	{
		Close();
		return true;
	}

	if (isMousePos(BaseX, BaseY, 352, 362))
		return true;

	return false;
}

void cSKINCHANGER::Open()
{
	OpenFlag = true;
}

void cSKINCHANGER::Close()
{
	OpenFlag = false;

	if (scItem.Flag)
	{
		scItem.ItemPosition = 0;
		cInvenTory.LastSetInvenItem(&scItem, 1);
	}
	if (scStone.Flag)
	{
		scStone.ItemPosition = 0;
		cInvenTory.LastSetInvenItem(&scStone, 1);
	}
}

bool cSKINCHANGER::SetSkinChangerItemAreaCheck(sITEM* pItem, int Pos)
{
	if (Pos == 1)
	{
		if ((pItem->CODE & sinITEM_MASK2) == sinSK1)
			return false;

		if ((pItem->CODE & sinITEM_MASK2) != sinWA1 && (pItem->CODE & sinITEM_MASK2) != sinWC1 && (pItem->CODE & sinITEM_MASK2) != sinWH1 && (pItem->CODE & sinITEM_MASK2) != sinWM1 && (pItem->CODE & sinITEM_MASK2) != sinWP1 && (pItem->CODE & sinITEM_MASK2) != sinWD1 && (pItem->CODE & sinITEM_MASK2) != sinWN1 &&
			(pItem->CODE & sinITEM_MASK2) != sinWS1 && (pItem->CODE & sinITEM_MASK2) != sinWS2 && (pItem->CODE & sinITEM_MASK2) != sinWT1 && (pItem->CODE & sinITEM_MASK2) != sinDS1 && (pItem->CODE & sinITEM_MASK2) != sinDA1 && (pItem->CODE & sinITEM_MASK2) != sinDA2)
			return false;

		if (scStone.Flag)
		{
			if (!isCompatible(pItem, &scStone))
				return false;
		}
	}
	else if (Pos == 2)
	{
		if ((pItem->CODE & sinITEM_MASK2) != sinSK1)
			return false;

		if (scItem.Flag)
		{
			if (!isCompatible(&scItem, pItem))
				return false;
		}
	}

	return true;
}

bool cSKINCHANGER::isCompatible(sITEM* pItem, sITEM* pStone)
{
	auto it = vSkinCodes.find(pStone->CODE);

	if (it != vSkinCodes.end())
	{
		for (int i = 0; i < MAX_ITEM; i++)
		{
			if (sItem[i].CODE == it->second)
			{
				if ((pItem->CODE & sinITEM_MASK2) == (sItem[i].CODE & sinITEM_MASK2) && pItem->Class == sItem[i].Class)
					return true;
			}
		}
	}

	return false;
}

LPDIRECT3DTEXTURE9 cSKINCHANGER::GetItemImage(sITEM* pItem)
{
	char szFilePath[255];

	if (pItem)
	{
		if (pItem->lpTempItem)
			return pItem->lpTempItem;
		wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", pItem->ItemFilePath, pItem->LastCategory);

		pItem->lpTempItem = LoadDibSurfaceOffscreen(szFilePath);
		return pItem->lpTempItem;
	}

	return nullptr;
}

sITEM* cSKINCHANGER::GetItem(DWORD CODE)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (sItem[i].CODE == CODE)
		{
			return &sItem[i];
		}
	}
	return nullptr;
}
