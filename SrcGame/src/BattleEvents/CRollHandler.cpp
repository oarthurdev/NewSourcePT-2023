#include "CRollHandler.h"

CRollHandler cRollHandler;

CRollHandler * CRollHandler::getInstance()
{
	return &cRollHandler;
}

void CRollHandler::Render()
{
	for (auto pRoll : vRolls)
	{
		auto pRollWindow = pRoll.second;
		if (pRollWindow && pRollWindow->GetWindow() && pRollWindow->GetWindow()->isVisible())
		{
			pRollWindow->GetWindow()->Render(0, 0, WinSizeX, WinSizeY, 0, 0);
			return;
		}
	}
}

bool CRollHandler::OnMouseClick(bool flag)
{
	for (auto pRoll : vRolls)
	{
		auto pRollWindow = pRoll.second;
		if (pRollWindow && pRollWindow->GetWindow() && pRollWindow->GetWindow()->isVisible())
			if (pRollWindow->GetWindow()->OnMouseClick(flag ? Down : Up, 0, 0, WinSizeX, WinSizeY, 0, 0))
				return true;
	}

	return false;
}

void CRollHandler::OnMouseMove()
{
	for (auto pRoll : vRolls)
	{
		auto pRollWindow = pRoll.second;
		if (pRollWindow && pRollWindow->GetWindow() && pRollWindow->GetWindow()->isVisible())
		{
			pRollWindow->GetWindow()->OnMouseMove(0, 0, WinSizeX, WinSizeY, 0, 0);
			return;
		}
	}
}

bool CRollHandler::isInsideRoll()
{
	for (auto pRoll : vRolls)
	{
		auto pRollWindow = pRoll.second;
		if (pRollWindow && pRollWindow->isInside() && pRollWindow->GetWindow() && pRollWindow->GetWindow()->isVisible())
			return true;
	}
	return false;
}

void CRollHandler::HandlePacket(PacketRollInfo * psPacket)
{
	vRolls.insert(pair<DWORD, CRollWindow*>(psPacket->iRollID, new CRollWindow(psPacket->iRollID, 302, 256, &psPacket->sItemInfo)));
}

void CRollHandler::HandlePacket(smTRANS_COMMAND * psPacket)
{
	for (auto it = vRolls.begin(); it != vRolls.end(); it++)
	{
		auto Roll = (*it);
		if (Roll.first == psPacket->WParam)
		{
			delete Roll.second;
			vRolls.erase(it);
			break;
		}
	}
}

void CRollHandler::Resize()
{	
	for (auto pRoll : vRolls)
	{
		auto pRollWindow = pRoll.second;
		if (pRollWindow && pRollWindow->GetWindow() && pRollWindow->GetWindow()->isVisible())
		{
			pRollWindow->GetWindow()->setX((WinSizeX - pRollWindow->GetWindow()->getWidth()) / 2);
			pRollWindow->GetWindow()->setY((WinSizeY - pRollWindow->GetWindow()->getHeight()) / 2);
			return;
		}
	}
}
