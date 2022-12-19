
#include "UIUnitMesh.h"

namespace UI
{
	UnitMesh::UnitMesh()
	{
	}

	UnitMesh::UnitMesh(Rectangle2D sBox) : Element(sBox)
	{
		uAngle = 2048;
		bRenderHead = TRUE;
		bRenderWeapons = TRUE;
		bRenderBody = TRUE;
		sCameraPosition = Point3D();
		pcImageMask = NULL;
		pcUnitDataMesh = new UnitData;
		ZeroMemory(pcUnitDataMesh, sizeof(UnitData));
		pcUnitDataMesh->iID = 0;
	}

	UnitMesh::~UnitMesh()
	{
		if (pcUnitDataMesh)
			pcUnitDataMesh->Free();

		DELET(pcUnitDataMesh);
	}

	void UnitMesh::SetHeadModel(char* pszHeadModel)
	{
		LoadUnitData(pcUnitDataMesh, pcUnitDataMesh->sCharacterData.Player.szBodyModel, pszHeadModel);

		pcUnitDataMesh->Animate(ANIMATIONTYPE_Idle);

		if (pcUnitDataMesh->pcHeadMeshContainer)
			pcUnitDataMesh->ChangeAnimationID(10);
	}

	void UnitMesh::SetBodyModel(char* pszBodyModel)
	{
		LoadUnitData(pcUnitDataMesh, pszBodyModel, pcUnitDataMesh->sCharacterData.Player.szHeadModel);

		pcUnitDataMesh->Animate(ANIMATIONTYPE_Idle);

		if (pcUnitDataMesh->pcBodyMeshContainer)
			pcUnitDataMesh->ChangeAnimationID(10);
	}

	NAKED void UnitMesh::LoadUnitData(UnitData* pcUnitData, char* pszBodyModel, char* pszHeadModel)
	{
		JMP(pfnLoadUnitDataModels);
	}

	void UnitMesh::Clear()
	{
		if (pcUnitDataMesh)
			pcUnitDataMesh->Free();

		DELET(pcUnitDataMesh);
	}

	void UnitMesh::Animate()
	{
	}

	void UnitMesh::PrepareUnitData(UnitData* pcUnitData)
	{
		if ((pcUnitDataMesh->iID - 0x7F000000) == pcUnitData->iID)
			return;

		if (pcUnitDataMesh->iID != 0)
			pcUnitDataMesh->Free();

		pcUnitDataMesh->Init();
		pcUnitDataMesh->pcStage = pcUnitData->pcStage;

		LoadUnitData(pcUnitDataMesh, pcUnitData->sCharacterData.Player.szBodyModel, pcUnitData->sCharacterData.Player.szHeadModel);

		pcUnitDataMesh->sCharacterData.iClass = pcUnitData->sCharacterData.iClass;
		pcUnitDataMesh->sCharacterData.sWarpHomeTown = 0;

		pcUnitDataMesh->SetPosition(0, 0, 0, 0, uAngle, 0);

		pcUnitDataMesh->iID = pcUnitData->iID + 0x7F000000;

		pcUnitDataMesh->bActive = TRUE;
		pcUnitDataMesh->bVisible = TRUE;

		pcUnitDataMesh->Animate(ANIMATIONTYPE_Idle);

		if (pcUnitData->sCharacterData.iType == CHARACTERTYPE_Player || pcUnitData->iCharacterType == CHARACTERTYPE_Player)
			pcUnitDataMesh->ChangeAnimationID(10);

		EXEMesh* pcMesh = pcUnitDataMesh->pcBoneContainer->GetMesh("Bip01 Head");
		if (pcMesh)
		{
			EXEMatrixI* sWorld;
			sWorld = &pcMesh->sWorld;

			sCameraPosition = Point3D(0, sWorld->i[3][2] + (2 << 8), 150 << 8);
		}
		else
			sCameraPosition = Point3D(0, pcUnitDataMesh->iModelHeight + (6 << 8), 200 << 8);
	}


	void UnitMesh::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (pcUnitDataMesh->bVisible == FALSE)
			return;

		int iZOld = READDWORD(0x82BF0C);
		WRITEDWORD(0x82BF0C, 1400);

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth - GetX());
		int iRenderHeight = low(GetHeight(), iHeight - GetY());

		//Setting Render Position
		WRITEDWORD(0x82BF04, iRenderX + (iRenderWidth >> 1));
		WRITEDWORD(0x82BF08, iRenderY + (iRenderHeight >> 1));

		GetGraphicsDevice()->Clear(FALSE, TRUE, FALSE);

		//Render Mask if exist
		if (pcImageMask)
			UI::ImageRender::Render(pcImageMask, iRenderX, iRenderY, iRenderWidth, iRenderHeight, D3DCOLOR_RGBA(255, 255, 255, TRUE));

		//Scissor Test
		GetGraphicsDevice()->PushScissorRect(RECT{ iRenderX, iRenderY, iRenderX + iRenderWidth, iRenderY + iRenderHeight });

		//Setting Camera and Render UnitData
		SetCharacterCamera(sCameraPosition.iX, sCameraPosition.iY, sCameraPosition.iZ, 0, 2048, 0);

		RENDERER->ClearLight();

		//Update Frame of Animation
		pcUnitDataMesh->iFrame += 40;

		//Reset Animation
		if (pcUnitDataMesh->iFrame > pcUnitDataMesh->iEndFrame)
			pcUnitDataMesh->iFrame = pcUnitDataMesh->iStartFrame;

		//Render Head of Unit
		if (pcUnitDataMesh->pcHeadMeshContainer && bRenderHead)
		{
			pcUnitDataMesh->sPosi = Point3D(0, 0, 0);
			pcUnitDataMesh->pcHeadMeshContainer->SetPosition(&pcUnitDataMesh->sPosi, &Point3D(0, uAngle, 0));

			if ((pcUnitDataMesh->pcHeadMeshContainer->pcBoneContainer) && (int)pcUnitDataMesh->pcHeadMeshContainer->pcBoneContainer->uMaxFrame > pcUnitDataMesh->iFrame)
				pcUnitDataMesh->pcHeadMeshContainer->uFrame = (UINT)pcUnitDataMesh->iFrame;

			if (pcUnitDataMesh->pcHeadMeshContainer->pcBoneContainer)
				pcUnitDataMesh->pcHeadMeshContainer->pcBoneContainer->iLastFrame = -1;
			else
				pcUnitDataMesh->pcHeadMeshContainer->iLastFrame = -1;

			pcUnitDataMesh->pcHeadMeshContainer->Render(&sCameraPosition, &Point3D(0, 2048, 0), (EXEFrame*)&pcUnitDataMesh->iStartFrame);
		}

		//Render Body of Unit
		if (pcUnitDataMesh->pcBodyMeshContainer && bRenderBody)
		{
			pcUnitDataMesh->sPosi = Point3D(0, 0, 0);
			pcUnitDataMesh->pcBodyMeshContainer->SetPosition(&pcUnitDataMesh->sPosi, &Point3D(0, uAngle, 0));

			if ((pcUnitDataMesh->pcBodyMeshContainer->pcBoneContainer) && (int)pcUnitDataMesh->pcBodyMeshContainer->pcBoneContainer->uMaxFrame > pcUnitDataMesh->iFrame)
				pcUnitDataMesh->pcBodyMeshContainer->uFrame = (UINT)pcUnitDataMesh->iFrame;

			if (pcUnitDataMesh->pcBodyMeshContainer->pcBoneContainer)
				pcUnitDataMesh->pcBodyMeshContainer->pcBoneContainer->iLastFrame = -1;
			else
				pcUnitDataMesh->pcBodyMeshContainer->iLastFrame = -1;

			pcUnitDataMesh->pcBodyMeshContainer->Render(&sCameraPosition, &Point3D(0, 2048, 0), (EXEFrame*)&pcUnitDataMesh->iStartFrame);
		}

		GetGraphicsDevice()->PopScissorRect();

		//Reset default Render Settings
		WRITEDWORD(0x82BF04, RESOLUTION_WIDTH >> 1);
		WRITEDWORD(0x82BF08, RESOLUTION_HEIGHT >> 1);

		WRITEDWORD(0x82BF0C, iZOld);

		Element::Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
	}
}