#include "sinbaram/sinLinkHeader.h"
#include "CRollWindow.h"

CRollWindow::CRollWindow(DWORD iRollID, int x, int y, sITEMINFO * lpItemInfo)
{
	char szText[256];

	pWindow1 = new UIWindowOld(iRollID, "game\\roll\\background.png", x, y);
	pWindow1->setX((WinSizeX - pWindow1->getWidth()) / 2);
	pWindow1->setY((WinSizeY - pWindow1->getHeight()) / 2);
	pWindow1->show();

	if(lpItemInfo)
	{
		for (int cnt = 0; cnt < MAX_ITEM; cnt++)
		{
			if (sItem[cnt].CODE == lpItemInfo->CODE)
			{
				memcpy(&Item, &sItem[cnt], sizeof(sITEM));
				memcpy(&Item.sItemInfo, lpItemInfo, sizeof(sITEMINFO));
				sprintf_s(szText, "image\\Sinimage\\Items\\%s\\it%s.bmp", Item.ItemFilePath, Item.DorpItem);
				auto pImage = new UIImageOld(0, szText, 10, 57);
				pImage->setX(pImage->getX() + (66 - pImage->getWidth()) / 2);
				pImage->setY(pImage->getY() + (88 - pImage->getHeight()) / 2);
				pImage->setHoverFunc(bind(&CRollWindow::OnHoverItemImage, this));
				pWindow1->AddElement(pImage);

				auto pText = new UITextOld(0, lpItemInfo->ItemName, 0, 34, true);
				pText->setX((pWindow1->getWidth() - pText->getWidth()) / 2);
				pWindow1->AddElement(pText);
				break;
			}
		}
	}

	pWindow1->AddElement(new UIButtonOld(-1, "game\\roll\\roll.png", "game\\roll\\roll_.png", 90, 102, true, false, bind(&CRollWindow::OnClickRollButton, this)));
	pWindow1->AddElement(new UIButtonOld(-2, "game\\roll\\skip.png", "game\\roll\\skip_.png", 165, 102, true, false, bind(&CRollWindow::OnClickSkipButton, this)));
}

CRollWindow::~CRollWindow()
{
	if (pWindow1)
		delete pWindow1;
}

bool CRollWindow::isInside()
{
	
	if (!pWindow1)
		return false;

	if (isMousePos(pWindow1->getX(), pWindow1->getY(), pWindow1->getWidth(), pWindow1->getHeight()))
		return true;
	return false;
}

void CRollWindow::OnClickRollButton()
{
	smTRANS_COMMAND sPacket;
	sPacket.size = sizeof(smTRANS_COMMAND);
	sPacket.code = OpCode::OPCODE_ROLL;
	sPacket.WParam = pWindow1->getID();
	sPacket.LParam = 1;
	smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

	pWindow1->hide();
}

void CRollWindow::OnClickSkipButton()
{
	smTRANS_COMMAND sPacket;
	sPacket.size = sizeof(smTRANS_COMMAND);
	sPacket.code = OpCode::OPCODE_ROLL;
	sPacket.WParam = pWindow1->getID();
	sPacket.LParam = 0;
	smWsockServer->Send((char*)&sPacket, sPacket.size, TRUE);

	pWindow1->hide();
}


void CRollWindow::OnHoverItemImage()
{
	Item.x = pCursorPos.x;
	Item.y = pCursorPos.y;
	cItem.ShowItemInfo(&Item, 1);
	sinShowItemInfoFlag = 1;
}
