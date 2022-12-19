#include <memory>
#include "UIMessageBallon.h"
#include "UIElement.h"
#include "UIImageLoader.h"
#include "UIImageRender.h"
#include "UIText.h"
#include "Utils/Geometry.h"
#include "Utils/Macros.h"
#include "def.h"

namespace UI
{
	MessageBalloon::MessageBalloon(Rectangle2D rRectangle) : Element(rRectangle)
	{
	}

	MessageBalloon::~MessageBalloon()
	{
	}

	void MessageBalloon::Init()
	{
		//Normal Skin
		saMessagesBalloon[SKINID_Normal][0].pImageLeftTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageTopLeft.png");
		saMessagesBalloon[SKINID_Normal][0].pImageMiddleTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageTopMiddle.png");
		saMessagesBalloon[SKINID_Normal][0].pImageRightTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageTopRight.png");
		saMessagesBalloon[SKINID_Normal][0].pImageLeft = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageLeft.png");
		saMessagesBalloon[SKINID_Normal][0].pImageCenter = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageCenter.png");
		saMessagesBalloon[SKINID_Normal][0].pImageRight = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageRight.png");
		saMessagesBalloon[SKINID_Normal][0].pImageLeftBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageBottomLeft.png");
		saMessagesBalloon[SKINID_Normal][0].pImageMiddleBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageBottomMiddle.png");
		saMessagesBalloon[SKINID_Normal][0].pImageRightBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageBottomRight.png");
		saMessagesBalloon[SKINID_Normal][0].pImageTailBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\MessageTail.png");

		//Blue Skin
		saMessagesBalloon[SKINID_Blue][0].pImageLeftTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopTopLeft.png");
		saMessagesBalloon[SKINID_Blue][0].pImageMiddleTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopTopMiddle.png");
		saMessagesBalloon[SKINID_Blue][0].pImageRightTop = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopTopRight.png");
		saMessagesBalloon[SKINID_Blue][0].pImageLeft = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopLeft.png");
		saMessagesBalloon[SKINID_Blue][0].pImageCenter = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopCenter.png");
		saMessagesBalloon[SKINID_Blue][0].pImageRight = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopRight.png");
		saMessagesBalloon[SKINID_Blue][0].pImageLeftBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopBottomLeft.png");
		saMessagesBalloon[SKINID_Blue][0].pImageMiddleBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopBottomMiddle.png");
		saMessagesBalloon[SKINID_Blue][0].pImageRightBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopBottomRight.png");
		saMessagesBalloon[SKINID_Blue][0].pImageTailBottom = ImageLoader::LoadImage("game\\images\\UI\\balloon\\PersonalShopTail.png");

		pcaBellatraCrown[0] = ImageLoader::LoadImage("StartImage\\MessageBox\\BellaBox\\Bella_01.tga");
		pcaBellatraCrown[1] = ImageLoader::LoadImage("StartImage\\MessageBox\\BellaBox\\Bella_02.tga");
		pcaBellatraCrown[2] = ImageLoader::LoadImage("StartImage\\MessageBox\\BellaBox\\Bella_03.tga");

		pTextMessage = std::make_shared<Text>(Rectangle2D(rRect), FALSE, -1);
		pTextMessage->SetMaxTextWidth(200);
		pTextMessage->SetNoClip(TRUE);
		pTextMessage->SetMultiLine(TRUE);
		pTextMessage->SetFont("Noto Sans", 16, 0, FALSE, FALSE, -1);

		pTextClanName = std::make_shared<Text>(Rectangle2D(rRect), FALSE, D3DCOLOR_XRGB(150, 255, 250));
		pTextClanName->SetMaxTextWidth(200);
		pTextClanName->SetNoClip(TRUE);
		pTextClanName->SetMultiLine(TRUE);
		pTextClanName->SetFont("Noto Sans", 16, 0, FALSE, FALSE, -1);

		pTextPetName = std::make_shared<Text>(Rectangle2D(rRect), FALSE, -1);
		pTextPetName->SetMaxTextWidth(200);
		pTextPetName->SetNoClip(TRUE);
		pTextPetName->SetMultiLine(TRUE);
		pTextPetName->SetFont("Noto Sans", 16, 0, FALSE, FALSE, -1);

		iBellatraCrown = -1;

		bHover = FALSE;
		bIsMessage = FALSE;
		bIsCharacterMessage = FALSE;
		bShowClanIcon = FALSE;
		bClanName = FALSE;
		bPetName = FALSE;
		psTextureClanIcon = NULL;
	}

	void MessageBalloon::SetMessage(std::string strMessage)
	{
		if (strMessage.find(":") != std::string::npos)
		{
			if (bShowClanIcon)
				strMessage.insert(0, " ");

			bIsMessage = TRUE;
			pTextMessage->SetHighlightText(TRUE);
			pTextMessage->SetHighlightTextColor(D3DCOLOR_XRGB(240, 180, 100));
		}

		pTextMessage->SetText(strMessage);
	}

	void MessageBalloon::SetClanName(std::string strText)
	{
		strText.insert(0, " ");
		pTextClanName->SetText(strText);
		pTextMessage->GetText() = trim(pTextMessage->GetText());
		bClanName = TRUE;
	}

	void MessageBalloon::SetPetName(std::string strText, DWORD dwColor)
	{
		pTextPetName->SetText(strText);
		pTextPetName->SetColor(dwColor);
		bPetName = TRUE;
	}

	void MessageBalloon::AddExtraText(int iID, EPositionText ePosition, std::string strText, DWORD dwColor)
	{
		ExtraText* psExtraText = new ExtraText;

		Text_ptr pText = std::make_shared<UI::Text>(strText, Rectangle2D(0, 0, 0, 0), FALSE, dwColor);
		pText->SetID(iID);
		pText->SetFont("Noto Sans", 16, 0, FALSE, FALSE, dwColor);
		psExtraText->ePosition = ePosition;
		psExtraText->pText = pText;
		vExtraText.push_back(psExtraText);
	}

	void MessageBalloon::ResetMessage()
	{
		pTextMessage->SetHighlightText(FALSE);
		bHover = FALSE;
		bIsMessage = FALSE;
		bIsCharacterMessage = FALSE;
		bShowClanIcon = FALSE;
		bClanName = FALSE;
		bPetName = FALSE;
		psTextureClanIcon = NULL;
		iBellatraCrown = -1;
		pTextClanName->SetText("");
		pTextMessage->SetText("");
		pTextPetName->SetText("");

		for (std::vector<ExtraText*>::iterator it = vExtraText.begin(); it != vExtraText.end(); it++)
		{
			ExtraText* ps = (*it);

			CLEARPTR(ps->pText);
			RESETPTR(ps->pText);
			DELET(ps);
		}

		vExtraText.clear();
	}

	void MessageBalloon::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth - GetX());
		int iRenderHeight = low(GetHeight(), iHeight - GetY());

		int iYBase = 0;
		int iXBase = 0;

		if (iRenderX < 0 || iRenderX > RESOLUTION_WIDTH)
			return;

		if (iRenderY < 0 || iRenderY > RESOLUTION_HEIGHT)
			return;

		int iMessageBalloonBoxWidth = pTextMessage->GetTextWidth();
		int iMessageBalloonBoxHeight = pTextMessage->GetHeightText();

		if (bShowClanIcon && !bIsMessage)
			iMessageBalloonBoxWidth += 34;

		for (std::vector<ExtraText*>::iterator it = vExtraText.begin(); it != vExtraText.end(); it++)
		{
			ExtraText* ps = (*it);

			if (iMessageBalloonBoxWidth < ps->pText->GetTextWidth())
				iMessageBalloonBoxWidth = ps->pText->GetTextWidth();

			iMessageBalloonBoxHeight += ps->pText->GetHeightFont() + 2;
		}

		//New Width and Height
		if (bClanName)
		{
			if (iMessageBalloonBoxWidth < pTextClanName->GetTextWidth())
				iMessageBalloonBoxWidth = pTextClanName->GetTextWidth();

			iMessageBalloonBoxHeight += pTextClanName->GetHeightFont() + 2;
		}
		if (bPetName)
		{
			if (iMessageBalloonBoxWidth < pTextPetName->GetTextWidth())
				iMessageBalloonBoxWidth = pTextPetName->GetTextWidth();

			iMessageBalloonBoxHeight += pTextPetName->GetHeightFont() + 2;
		}

		if (iMessageBalloonBoxWidth < 20)
		{
			iMessageBalloonBoxWidth = 20;
			iXBase += 10 - (pTextMessage->GetTextWidth() >> 1);
		}

		//Render Box
		DrawMessageBalloonBox(iRenderX - 6 - (iMessageBalloonBoxWidth >> 1), iRenderY - 4 - iMessageBalloonBoxHeight - 18, iMessageBalloonBoxWidth - 4, iMessageBalloonBoxHeight);

		if (bClanName)
		{
			pTextClanName->Render(iX - (iMessageBalloonBoxWidth >> 1) + 2, iY - iMessageBalloonBoxHeight - 18, iWidth, iHeight, iSourceX, iSourceY);

			if (iMessageBalloonBoxWidth > pTextMessage->GetTextWidth())
				iXBase = (iMessageBalloonBoxWidth >> 1) - (pTextMessage->GetTextWidth() >> 1);

			iYBase += pTextClanName->GetHeightFont();
		}

		//Top Render
		for (std::vector<ExtraText*>::iterator it = vExtraText.begin(); it != vExtraText.end(); it++)
		{
			ExtraText* ps = (*it);
			if (ps->ePosition == POSITIONTEXT_Top)
			{
				ps->pText->Render(iX - (iMessageBalloonBoxWidth >> 1) + ((iMessageBalloonBoxWidth >> 1) - (ps->pText->GetTextWidth() >> 1)), iY - iMessageBalloonBoxHeight - 18 + iYBase, iWidth, iHeight, iSourceX, iSourceY);
				iYBase += ps->pText->GetHeightFont();
			}
		}


		if (bPetName)
		{
			if (iMessageBalloonBoxWidth > pTextPetName->GetTextWidth())
				pTextPetName->Render(iX - (iMessageBalloonBoxWidth >> 1) + ((iMessageBalloonBoxWidth >> 1) - (pTextPetName->GetTextWidth() >> 1)), iY - iMessageBalloonBoxHeight - 2, iWidth, iHeight, iSourceX, iSourceY);
			else
				pTextPetName->Render(iX - (iMessageBalloonBoxWidth >> 1), iY - iMessageBalloonBoxHeight - 2, iWidth, iHeight, iSourceX, iSourceY);

			if (iMessageBalloonBoxWidth > pTextMessage->GetTextWidth())
				iXBase = (iMessageBalloonBoxWidth >> 1) - (pTextMessage->GetTextWidth() >> 1);
		}

		//Clan Icon
		if (bShowClanIcon)
		{
			int iClanWidth = psTextureClanIcon->sTexture.iWidth;
			int iClanHeight = psTextureClanIcon->sTexture.iHeight;

			UI::ImageRender::Render(psTextureClanIcon->sTexture.pcD3DTexture, iX - (iMessageBalloonBoxWidth >> 1), iY - iMessageBalloonBoxHeight - 17, iClanWidth, iClanHeight, 0, 0, -1, bIsMessage ? 0.5f : 1.0f);
			iXBase += bIsMessage ? 0 : (iClanWidth >> 1);
		}

		//Middle Render
		for (std::vector<ExtraText*>::iterator it = vExtraText.begin(); it != vExtraText.end(); it++)
		{
			ExtraText* ps = (*it);
			if (ps->ePosition == POSITIONTEXT_Middle)
			{
				ps->pText->Render(iX - (iMessageBalloonBoxWidth >> 1) + ((iMessageBalloonBoxWidth >> 1) - (ps->pText->GetTextWidth() >> 1)), iY - iMessageBalloonBoxHeight - 18 + iYBase, iWidth, iHeight, iSourceX, iSourceY);
				iYBase += ps->pText->GetHeightFont();
			}
		}

		if (bShowClanIcon)
			pTextMessage->Render(iX - (iMessageBalloonBoxWidth >> 1) + iXBase, iY - iMessageBalloonBoxHeight - 18 + iYBase, iWidth, iHeight, iSourceX, iSourceY);
		else
			pTextMessage->Render(iX - (iMessageBalloonBoxWidth >> 1) + ((iMessageBalloonBoxWidth >> 1) - (pTextMessage->GetTextWidth() >> 1)), iY - iMessageBalloonBoxHeight - 18 + iYBase, iWidth, iHeight, iSourceX, iSourceY);


		iYBase += pTextMessage->GetHeightFont();

		//Bottom Render
		for (std::vector<ExtraText*>::iterator it = vExtraText.begin(); it != vExtraText.end(); it++)
		{
			ExtraText* ps = (*it);
			if (ps->ePosition == POSITIONTEXT_Bottom)
			{
				ps->pText->Render(iX - (iMessageBalloonBoxWidth >> 1) + ((iMessageBalloonBoxWidth >> 1) - (ps->pText->GetTextWidth() >> 1)), iY - iMessageBalloonBoxHeight - 18 + iYBase, iWidth, iHeight, iSourceX, iSourceY);
				iYBase += ps->pText->GetHeightFont();
			}
		}

		//Bellatra Icon
		if (iBellatraCrown > 0)
		{
			UI::Image* pcImage = pcaBellatraCrown[iBellatraCrown - 1];

			int iIconX = iRenderX - (iMessageBalloonBoxWidth >> 1);
			int iIconY = iRenderY - iMessageBalloonBoxHeight - 18;

			UI::ImageRender::Render(pcImage, iIconX + (iMessageBalloonBoxWidth >> 1) - (pcImage->GetWidth() >> 1), iIconY - pcImage->GetHeight() - 2, pcImage->GetWidth(), pcImage->GetHeight(), -1);
		}

		Element::Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
	}

	void MessageBalloon::SetColor(DWORD dwColor)
	{
		pTextMessage->SetColor(dwColor);
	}

	void MessageBalloon::IsCharacterMessage(BOOL b)
	{
		bIsCharacterMessage = b;
	}

	void MessageBalloon::SetClanIconTexture(EXESurfaceOld* ps)
	{
		psTextureClanIcon = ps;

		bShowClanIcon = TRUE;
	}

	void MessageBalloon::DrawMessageBalloonBox(int iX, int iY, int iWidth, int iHeight)
	{
		//Check if have Hover Images
		if (!saMessagesBalloon[eSkinID][1].pImageLeftTop)
			bHover = 0;

		//Drawing Top
		if (saMessagesBalloon[eSkinID][bHover].pImageLeftTop)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageLeftTop, iX, iY, 16, 8, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageMiddleTop)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageMiddleTop, iX + 16, iY, iWidth - 16, 8, 0, 0, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageRightTop)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageRightTop, iX + iWidth, iY, 16, 8, 0, 0, -1);

		//Drawing Middle
		if (saMessagesBalloon[eSkinID][bHover].pImageLeft)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageLeft, iX, iY + 8, 16, iHeight - 8, 0, 0, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageCenter)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageCenter, iX + 16, iY + 8, iWidth - 16, iHeight - 8, 0, 0, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageRight)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageRight, iX + iWidth, iY + 8, 16, iHeight - 8, 0, 0, -1);

		//Drawing Bottom
		if (saMessagesBalloon[eSkinID][bHover].pImageLeftBottom)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageLeftBottom, iX, iY + iHeight, 16, 8, 0, 0, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageMiddleBottom)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageMiddleBottom, iX + 16, iY + iHeight, iWidth - 16, 8, 0, 0, -1);

		if (saMessagesBalloon[eSkinID][bHover].pImageRightBottom)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageRightBottom, iX + iWidth, iY + iHeight, 16, 8, 0, 0, -1);

		//Drawing Tail Bottom
		if (saMessagesBalloon[eSkinID][bHover].pImageTailBottom && bIsMessage)
			UI::ImageRender::Render(saMessagesBalloon[eSkinID][bHover].pImageTailBottom, iX + (iWidth >> 1), iY + iHeight + 5, 16, 16, 0, 5, -1);
	}
};
