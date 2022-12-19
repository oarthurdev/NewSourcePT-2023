#include "sinbaram/sinLinkHeader.h"
#include "cSettingsWindow.h"
#include "Settings/Settings.h"
#include "CLootHandler.h"

cSettingsWindow cSettings;

cSettingsWindow::~cSettingsWindow()
{
	if (pWindow1)
		delete pWindow1;
}

void cSettingsWindow::Init()
{
	ClearLoadedImages();
	if (pWindow1)
	{
		delete pWindow1;
		pWindow1 = 0;
	}

	BuildWindow1();
	if (pWindow1)
	{
		BuildWindowVideo();
		BuildWindowAudio();
		BuildWindowGeneral();
	}
}

void cSettingsWindow::Draw()
{
	if (!pWindow1 || !pWindow1->isVisible())
		return;

	BaseX = (WinSizeX - 560) / 2;
	BaseY = (WinSizeY - 450) / 2;

	pWindow1->Render(BaseX, BaseY, WinSizeX, WinSizeY, 0, 0);
}

bool cSettingsWindow::LButtonDown()
{
	if (!pWindow1 || !pWindow1->isVisible())
		return false;

	bool bRet = false;

	if (pWindow1->OnMouseClick(Down, BaseX, BaseY, WinSizeX, WinSizeY, 0, 0))
		bRet = true;

	return bRet;
}

bool cSettingsWindow::LButtonUp()
{
	if (!pWindow1 || !pWindow1->isVisible())
		return false;

	bool bRet = false;

	if (pWindow1->OnMouseClick(Up, BaseX, BaseY, WinSizeX, WinSizeY, 0, 0))
		bRet = true;

	return bRet;
}

void cSettingsWindow::OnMouseMove()
{
	if (!pWindow1 || !pWindow1->isVisible())
		return;

	pWindow1->OnMouseMove(BaseX, BaseY, WinSizeX, WinSizeY, 0, 0);
}

void cSettingsWindow::OnMouseScroll(int zDelta)
{
	if (!pWindow1 || !pWindow1->isVisible())
		return;

	pWindow1->OnMouseScroll(zDelta, BaseX, BaseY, WinSizeX, WinSizeY, 0, 0);
}

void cSettingsWindow::OnKeyDown(char Code)
{
	if (!pWindow1 || !pWindow1->isVisible())
		return;

	pWindow1->OnKeyDown(Code);
}

void cSettingsWindow::Open()
{
	LoadSettings();
	pWindow1->show();
}

void cSettingsWindow::Close()
{
	pWindow1->hide();
}

void cSettingsWindow::BuildWindow1()
{
	pWindow1 = new UIWindowOld(OBJID_Main, "game\\settings\\window.png", 0, 0);

	pWindow1->AddElement(new UIButtonOld(OBJID_Close, "game\\settings\\cancel.tga", "game\\settings\\cancel_.tga", 28, 341, true, false, std::bind(&cSettingsWindow::Close, this)));
	pWindow1->AddElement(new UIButtonOld(OBJID_Reset, "game\\settings\\reset.tga", "game\\settings\\reset_.tga", 28, 369, true, false, std::bind(&cSettingsWindow::ResetSettings, this)));
	pWindow1->AddElement(new UIButtonOld(OBJID_Save, "game\\settings\\save.tga", "game\\settings\\save_.tga", 28, 397, true, false, std::bind(&cSettingsWindow::SaveSettings, this)));

	auto pListBox = new UIListBoxOld(OBJID_TabList, 14, 47, 121, 29 * 4);
	pWindow1->AddElement(pListBox);

	/*auto pTabUI = new UIListItemOld(OBJID_TabUI, "game\\settings\\ui.png", "game\\settings\\ui_.png", 0, 87);
	pListBox->AddListItem(pTabUI);*/

	pWindow1->hide();
}

void cSettingsWindow::BuildWindowVideo()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);
	if (pListBox)
	{
		auto pTabVideo = new UIListItemOld(OBJID_TabVideo, "game\\settings\\video.png", "game\\settings\\video_.png", 0, 0);
		if (pTabVideo)
		{
			pListBox->AddListItem(pTabVideo);

			auto pWindowVideo = new UIWindowOld(OBJID_WindowVideo, 137, 41, 410, 394);
			if (pWindowVideo)
			{
				pTabVideo->AddElement(pWindowVideo);

				auto pTitle1 = new UIImageOld(0, "game\\settings\\title.tga", 10, 15);
				pWindowVideo->AddElement(pTitle1);

				auto pScreen = new UIImageOld(0, "game\\settings\\screen.tga", 0, 0);
				pScreen->setX(pTitle1->getX() + (pTitle1->getWidth() - pScreen->getWidth()) / 2);
				pScreen->setY(pTitle1->getY() + (pTitle1->getHeight() - pScreen->getHeight()) / 2);
				pWindowVideo->AddElement(pScreen);

				pWindowVideo->AddElement(new UITextOld(0, "Modo de tela:", 23, pWindowVideo->getMaxY() + 10, true));

				int iY = pWindowVideo->getMaxY() + 2;

				auto pScreenList = new UIListBoxOld(OBJID_ScreenList, 23, iY, 220, 20);
				if (pScreenList)
				{
					pWindowVideo->AddElement(pScreenList);
					pScreenList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Tela cheia", false, false, true));
					pScreenList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 120, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Modo janela", false, false, true));

				}
				pWindowVideo->AddElement(new UICheckboxOld(OBJID_AutoAdjust, 240, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Auto ajuste", true, false, true));
				pWindowVideo->AddElement(new UICheckboxOld(OBJID_StartMaximized, 240, pWindowVideo->getMaxY(), "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Iniciar tela maximizada", true, false, true));
				pWindowVideo->AddElement(new UITextOld(0, "Aspecto de resolução:", 23, pWindowVideo->getMaxY(), true));

				auto pRatioList = new UIListBoxOld(OBJID_RatioList, 23, pWindowVideo->getMaxY() + 2, 240, 20);
				if (pRatioList)
				{
					pWindowVideo->AddElement(pRatioList);



					auto pCheckbox1 = new UICheckboxOld(43, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "4:3", false, false, true);
					auto pCheckbox2 = new UICheckboxOld(169, 120, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "16:9", false, false, true);

					if (pCheckbox1 && pCheckbox2)
					{
						pRatioList->AddListItem(pCheckbox1);
						pRatioList->AddListItem(pCheckbox2);

						pWindowVideo->AddElement(new UITextOld(0, "Resoluções:", 23, pWindowVideo->getMaxY() + 3, true));

						iY = pWindowVideo->getMaxY() + 2;

						auto pResolutionList1 = new UIListBoxOld(OBJID_ResolutionList, 23, iY, 360, 41);
						if (pResolutionList1)
						{
							pCheckbox1->AddElement(pResolutionList1);

							pResolutionList1->AddListItem(new UICheckboxOld(1, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "800x600", false, false, true));
							pResolutionList1->AddListItem(new UICheckboxOld(2, 0, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1024x768", false, false, true));
							pResolutionList1->AddListItem(new UICheckboxOld(3, 120, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1280x960", false, false, true));
							pResolutionList1->AddListItem(new UICheckboxOld(4, 120, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1400x1050", false, false, true));
						}

						auto pResolutionList2 = new UIListBoxOld(OBJID_ResolutionList, 23, iY, 360, 41);
						if (pResolutionList2)
						{
							pCheckbox2->AddElement(pResolutionList2);

							pResolutionList2->AddListItem(new UICheckboxOld(1, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1280x720", false, false, true));
							pResolutionList2->AddListItem(new UICheckboxOld(2, 0, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1366x768", false, false, true));
							pResolutionList2->AddListItem(new UICheckboxOld(3, 120, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1600x900", false, false, true));
							pResolutionList2->AddListItem(new UICheckboxOld(4, 120, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "1920x1080", false, false, true));
						}
					}
				}

				auto pTitle2 = new UIImageOld(0, "game\\settings\\title.tga", 10, pWindowVideo->getMaxY() + 50);
				pWindowVideo->AddElement(pTitle2);

				auto pGraph = new UIImageOld(0, "game\\settings\\graphics.tga", 0, 0);
				pGraph->setX(pTitle2->getX() + (pTitle2->getWidth() - pGraph->getWidth()) / 2);
				pGraph->setY(pTitle2->getY() + (pTitle2->getHeight() - pGraph->getHeight()) / 2);
				pWindowVideo->AddElement(pGraph);

				iY = pWindowVideo->getMaxY() + 10;
				pWindowVideo->AddElement(new UITextOld(0, "Qualidade da textura:", 23, iY, true));
				pWindowVideo->AddElement(new UITextOld(0, "Profundidade de bits:", 203, iY, true));

				iY = pWindowVideo->getMaxY() + 2;

				auto pTextureList = new UIListBoxOld(OBJID_TextureList, 23, iY, 150, 20);
				if (pTextureList)
				{
					pWindowVideo->AddElement(pTextureList);

					pTextureList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Alta", false, false, true));
					pTextureList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Baixa", false, false, true));
				}

				auto pBitList = new UIListBoxOld(OBJID_BitList, 203, iY, 150, 20);
				if (pBitList)
				{
					pWindowVideo->AddElement(pBitList);

					pBitList->AddListItem(new UICheckboxOld(32, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "32 bit", false, false, true));
					pBitList->AddListItem(new UICheckboxOld(16, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "16 bit", false, false, true));
				}

				auto pTitle3 = new UIImageOld(0, "game\\settings\\title.tga", 10, pWindowVideo->getMaxY() + 10);
				pWindowVideo->AddElement(pTitle3);

				auto pCam = new UIImageOld(0, "game\\settings\\camera.png", 0, 0);
				pCam->setX(pTitle3->getX() + (pTitle3->getWidth() - pCam->getWidth()) / 2);
				pCam->setY(pTitle3->getY() + (pTitle3->getHeight() - pCam->getHeight()) / 2);
				pWindowVideo->AddElement(pCam);

				iY = pWindowVideo->getMaxY() + 10;
				pWindowVideo->AddElement(new UITextOld(0, "Alcance da câmera:", 23, iY, true));
				pWindowVideo->AddElement(new UITextOld(0, "Câmera invertida:", 203, iY, true));

				iY = pWindowVideo->getMaxY() + 2;

				auto pCameraList = new UIListBoxOld(OBJID_CameraList, 23, iY, 150, 20);
				if (pCameraList)
				{
					pWindowVideo->AddElement(pCameraList);

					pCameraList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Alto", false, false, true));
					pCameraList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Normal", false, false, true));
				}

				auto pInvertedList = new UIListBoxOld(OBJID_InvertedList, 203, iY, 150, 20);
				if (pInvertedList)
				{
					pWindowVideo->AddElement(pInvertedList);

					pInvertedList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sim", false, false, true));
					pInvertedList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Não", false, false, true));
				}
			}
		}
	}
}

void cSettingsWindow::BuildWindowAudio()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);
	if (pListBox)
	{
		auto pTabAudio = new UIListItemOld(OBJID_TabAudio, "game\\settings\\audio.png", "game\\settings\\audio_.png", 0, 29);
		if (pTabAudio)
		{
			pListBox->AddListItem(pTabAudio);

			auto pWindowAudio = new UIWindowOld(OBJID_WindowAudio, 137, 41, 410, 394);
			if (pWindowAudio)
			{
				pTabAudio->AddElement(pWindowAudio);

				auto pTitle1 = new UIImageOld(0, "game\\settings\\title.tga", 10, 15);
				pWindowAudio->AddElement(pTitle1);

				auto pBgMusic = new UIImageOld(0, "game\\settings\\bgmusic.png", 0, 0);
				pBgMusic->setX(pTitle1->getX() + (pTitle1->getWidth() - pBgMusic->getWidth()) / 2);
				pBgMusic->setY(pTitle1->getY() + (pTitle1->getHeight() - pBgMusic->getHeight()) / 2);
				pWindowAudio->AddElement(pBgMusic);

				pWindowAudio->AddElement(new UITextOld(0, "Música de fundo:", 23, pWindowAudio->getMaxY() + 10, true));

				auto pWindowController = new UIWindowOld(OBJID_MusicController, "game\\settings\\bgcontroller.png", 12, pWindowAudio->getMaxY() + 8);
				if (pWindowController)
				{
					pWindowAudio->AddElement(pWindowController);

					pWindowController->AddElement(new UICheckboxOld(OBJID_Mute, 11, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Desabilitar", true, false, true));
					pWindowController->AddElement(new UIHorizontalScrollOld(OBJID_Volume, 98, 24, 0, 100, 100));
				}

				auto pTitle2 = new UIImageOld(0, "game\\settings\\title.tga", 10, pWindowAudio->getMaxY() + 10);
				pWindowAudio->AddElement(pTitle2);

				auto pBgSound = new UIImageOld(0, "game\\settings\\soundeffects.png", 0, 0);
				pBgSound->setX(pTitle2->getX() + (pTitle2->getWidth() - pBgSound->getWidth()) / 2);
				pBgSound->setY(pTitle2->getY() + (pTitle2->getHeight() - pBgSound->getHeight()) / 2);
				pWindowAudio->AddElement(pBgSound);

				pWindowAudio->AddElement(new UITextOld(0, "Efeitos sonoros:", 23, pWindowAudio->getMaxY() + 10, true));

				auto pWindowController2 = new UIWindowOld(OBJID_EffectsController, "game\\settings\\bgcontroller.png", 12, pWindowAudio->getMaxY() + 8);
				if (pWindowController2)
				{
					pWindowAudio->AddElement(pWindowController2);

					pWindowController2->AddElement(new UICheckboxOld(OBJID_Mute, 11, 20, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Desabilitar", true, false, true));
					pWindowController2->AddElement(new UIHorizontalScrollOld(OBJID_Volume, 98, 24, 0, 100, 100));
				}
			}
		}
	}
}

void cSettingsWindow::BuildWindowGeneral()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);
	if (pListBox)
	{
		auto pTabGeneral = new UIListItemOld(OBJID_TabGeneral, "game\\settings\\general.png", "game\\settings\\general_.png", 0, 58);
		if (pTabGeneral)
		{
			pListBox->AddListItem(pTabGeneral);

			auto pWindowGeneral = new UIWindowOld(OBJID_WindowGeneral, 137, 41, 410, 394);
			if (pWindowGeneral)
			{
				pTabGeneral->AddElement(pWindowGeneral);

				auto pTitle1 = new UIImageOld(0, "game\\settings\\title.tga", 10, 15);
				pWindowGeneral->AddElement(pTitle1);

				auto pSocial = new UIImageOld(0, "game\\settings\\social.png", 0, 0);
				pSocial->setX(pTitle1->getX() + (pTitle1->getWidth() - pSocial->getWidth()) / 2);
				pSocial->setY(pTitle1->getY() + (pTitle1->getHeight() - pSocial->getHeight()) / 2);
				pWindowGeneral->AddElement(pSocial);

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_PartyRequest, 23, pWindowGeneral->getMaxY() + 10, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Desabilitar pedidos de party", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_TradeRequest, 23, pWindowGeneral->getMaxY() + 2, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Desabilitar pedidos de troca", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Whisper, 23, pWindowGeneral->getMaxY() + 2, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Desabilitar mensagens pessoais (PM)", true, false, true));

				auto pTitle2 = new UIImageOld(0, "game\\settings\\title.tga", 10, pWindowGeneral->getMaxY() + 10);
				pWindowGeneral->AddElement(pTitle2);

				auto pPerson = new UIImageOld(0, "game\\settings\\personalization.png", 0, 0);
				pPerson->setX(pTitle2->getX() + (pTitle2->getWidth() - pPerson->getWidth()) / 2);
				pPerson->setY(pTitle2->getY() + (pTitle2->getHeight() - pPerson->getHeight()) / 2);
				pWindowGeneral->AddElement(pPerson);

				int iY = pWindowGeneral->getMaxY() + 10;
				pWindowGeneral->AddElement(new UITextOld(0, "Exibir o dano causado:", 23, iY, true));
				pWindowGeneral->AddElement(new UITextOld(0, "Barra de HP sobre a cabeça:", 203, iY, true));

				iY = pWindowGeneral->getMaxY() + 2;

				auto pDamageList = new UIListBoxOld(OBJID_DamageList, 23, iY, 170, 20);
				if (pDamageList)
				{
					pWindowGeneral->AddElement(pDamageList);

					pDamageList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sim", false, false, true));
					pDamageList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Não", false, false, true));
				}

				auto pHPList = new UIListBoxOld(OBJID_HPList, 203, iY, 170, 20);
				if (pHPList)
				{
					pWindowGeneral->AddElement(pHPList);

					pHPList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sim", false, false, true));
					pHPList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Não", false, false, true));
				}

				iY = pWindowGeneral->getMaxY() + 4;
				pWindowGeneral->AddElement(new UITextOld(0, "Mostrar o FPS:", 23, iY, true));

				iY = pWindowGeneral->getMaxY() + 2;
				auto pFPSList = new UIListBoxOld(OBJID_FPSList, 23, iY, 170, 20);
				if (pFPSList)
				{
					pWindowGeneral->AddElement(pFPSList);

					pFPSList->AddListItem(new UICheckboxOld(OBJID_ONBox, 0, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sim", false, false, true));
					pFPSList->AddListItem(new UICheckboxOld(OBJID_OFFBox, 88, 0, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Não", false, false, true));
				}

				/*iY = pWindowGeneral->getMaxY() + 10;
				pWindowGeneral->AddElement(new UITextOld(0, "Filtro de itens:", 23, iY, true));

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_LootFilter, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Habilitar filtro de itens", true, false, true));

				iY = pWindowGeneral->getMaxY() + 10;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_HPPotion, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Poção de HP", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_NonSpec, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sem Spec", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_MPPotion, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Poção de MP", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Fighter, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Lutador", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_SPPotion, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Poção de RES", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Mechanician, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Mecânico", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Gold, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Gold", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Archer, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Arqueira", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Amulets, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Amuletos", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Pikeman, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Pikeman", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Rings, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Anéis", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Atalanta, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Atalanta", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Sheltoms, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sheltoms", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Knight, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Cavaleiro", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Force, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Forças orb", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Magician, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Mago", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Premiums, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Premiums", true, false, true));
				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Priestess, 203, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Sacerdotiza", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Crystals, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Cristais", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Defense, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Itens defensivos", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Offense, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Itens ofensivos", true, false, true));
				iY = pWindowGeneral->getMaxY() + 2;

				pWindowGeneral->AddElement(new UICheckboxOld(OBJID_Everything, 23, iY, "game\\settings\\checkbox.tga", "game\\settings\\checkbox_.tga", "Todo o resto", true, false, true));*/

				auto pTitle3 = new UIImageOld(0, "game\\settings\\title.tga", 10, pWindowGeneral->getMaxY() + 10);
				pWindowGeneral->AddElement(pTitle3);

				auto pKeyBoard = new UIImageOld(0, "game\\settings\\keyboard.tga", 0, 0);
				pKeyBoard->setX(pTitle3->getX() + (pTitle3->getWidth() - pKeyBoard->getWidth()) / 2);
				pKeyBoard->setY(pTitle3->getY() + (pTitle3->getHeight() - pKeyBoard->getHeight()) / 2);
				pWindowGeneral->AddElement(pKeyBoard);

				iY = pWindowGeneral->getMaxY() + 10;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F1", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro1, 93, iY));
				auto pInput1 = new UIInputOld(OBJID_Macro1, "game\\settings\\textbox.png", 93, iY);
				//pInput1->setY(pWindowGeneral->getHeight() - pInput1->getHeight());
				pInput1->setTextArea(2, 2, pInput1->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput1);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F2", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro2, 93, iY));
				auto pInput2 = new UIInputOld(OBJID_Macro2, "game\\settings\\textbox.png", 93, iY);
				//pInput2->setY(pWindowGeneral->getHeight() - pInput2->getHeight());
				//pInput2->setY(iY);
				pInput2->setTextArea(2, 2, pInput2->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput2);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F3", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro3, 93, iY));
				auto pInput3 = new UIInputOld(OBJID_Macro3, "game\\settings\\textbox.png", 93, iY);
				//pInput3->setY(pWindowGeneral->getHeight() - pInput3->getHeight());
				pInput3->setTextArea(2, 2, pInput3->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput3);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F4", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro4, 93, iY));
				auto pInput4 = new UIInputOld(OBJID_Macro4, "game\\settings\\textbox.png", 93, iY);
				//pInput4->setY(pWindowGeneral->getHeight() - pInput4->getHeight());
				pInput4->setTextArea(2, 2, pInput4->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput4);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F5", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro5, 93, iY));
				auto pInput5 = new UIInputOld(OBJID_Macro5, "game\\settings\\textbox.png", 93, iY);
				//pInput5->setY(pWindowGeneral->getHeight() - pInput5->getHeight());
				pInput5->setTextArea(2, 2, pInput5->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput5);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F6", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro6, 93, iY));
				auto pInput6 = new UIInputOld(OBJID_Macro6, "game\\settings\\textbox.png", 93, iY);
				//pInput6->setY(pWindowGeneral->getHeight() - pInput6->getHeight());
				pInput6->setTextArea(2, 2, pInput6->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput6);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F7", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro7, 93, iY));
				auto pInput7 = new UIInputOld(OBJID_Macro7, "game\\settings\\textbox.png", 93, iY);
				//pInput7->setY(pWindowGeneral->getHeight() - pInput7->getHeight());
				pInput7->setTextArea(2, 2, pInput7->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput7);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F8", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro8, 93, iY));
				auto pInput8 = new UIInputOld(OBJID_Macro8, "game\\settings\\textbox.png", 93, iY);
				//pInput8->setY(pWindowGeneral->getHeight() - pInput8->getHeight());
				pInput8->setTextArea(2, 2, pInput8->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput8);

				iY = pWindowGeneral->getMaxY() + 2;
				pWindowGeneral->AddElement(new UITextOld(0, "CTRL + F9", 23, iY));
				//pWindowGeneral->AddElement(new UIInputOld(OBJID_Macro9, 93, iY));
				auto pInput9 = new UIInputOld(OBJID_Macro9, "game\\settings\\textbox.png", 93, iY);
				//pInput9->setY(pWindowGeneral->getHeight() - pInput9->getHeight());
				pInput9->setTextArea(2, 2, pInput9->getWidth() - 2, 19);
				pWindowGeneral->AddElement(pInput9);
			}
		}
	}
}

void cSettingsWindow::LoadSettings()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);

	if (pListBox)
	{
		pListBox->selectItem(OBJID_TabVideo);

		auto pTabVideo = pListBox->GetListItem<UIListItemOld>(OBJID_TabVideo);
		if (pTabVideo)
		{
			auto pWindowVideo = pTabVideo->GetElement<UIWindowOld>(OBJID_WindowVideo);
			if (pWindowVideo)
			{
				auto pScreenList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_ScreenList);
				if (pScreenList)
					pScreenList->selectItem(SETTINGSHANDLER->getWindowMode() ? OBJID_OFFBox : OBJID_ONBox);

				auto pStartMaximized = pWindowVideo->GetElement<UICheckboxOld>(OBJID_StartMaximized);
				if (pStartMaximized)
					pStartMaximized->setSelected(SETTINGSHANDLER->getStartMaximized());

				auto pAutoAdjust = pWindowVideo->GetElement<UICheckboxOld>(OBJID_AutoAdjust);
				if (pAutoAdjust)
					pAutoAdjust->setSelected(SETTINGSHANDLER->getAutoAdjust());

				auto pRatioList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_RatioList);
				if (pRatioList)
				{
					pRatioList->selectItem(SETTINGSHANDLER->getRatio());

					auto pSelectedRatio = pRatioList->getSelectedItem();
					if (pSelectedRatio)
					{
						auto pResolutionList = pSelectedRatio->GetElement<UIListBoxOld>(OBJID_ResolutionList);
						if (pResolutionList)
							pResolutionList->selectItem(SETTINGSHANDLER->getResolution());
					}
				}

				auto pTextureList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_TextureList);
				if (pTextureList)
					pTextureList->selectItem(SETTINGSHANDLER->getTextureQuality() == 1 ? OBJID_ONBox : OBJID_OFFBox);

				auto pBitList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_BitList);
				if (pBitList)
					pBitList->selectItem(SETTINGSHANDLER->getBitDepth());

				auto pCameraList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_CameraList);
				if (pCameraList)
					pCameraList->selectItem(SETTINGSHANDLER->getSight() ? OBJID_ONBox : OBJID_OFFBox);

				auto pInvertedList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_InvertedList);
				if (pInvertedList)
					pInvertedList->selectItem(SETTINGSHANDLER->getCamInv() ? OBJID_ONBox : OBJID_OFFBox);
			}
		}

		auto pTabAudio = pListBox->GetListItem<UIListItemOld>(OBJID_TabAudio);
		if (pTabAudio)
		{
			auto pWindowAudio = pTabAudio->GetElement<UIWindowOld>(OBJID_WindowAudio);
			if (pWindowAudio)
			{
				auto pMusicController = pWindowAudio->GetElement<UIWindowOld>(OBJID_MusicController);
				if (pMusicController)
				{
					auto pMute = pMusicController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						pMute->setSelected(!SETTINGSHANDLER->hasSound());

					auto pVolume = pMusicController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						pVolume->setValue(SETTINGSHANDLER->getSoundVolume());
				}

				auto pEffectsController = pWindowAudio->GetElement<UIWindowOld>(OBJID_EffectsController);
				if (pEffectsController)
				{
					auto pMute = pEffectsController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						pMute->setSelected(!SETTINGSHANDLER->hasEffects());

					auto pVolume = pEffectsController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						pVolume->setValue(SETTINGSHANDLER->getEffectsVolume());
				}
			}
		}

		auto pTabGeneral = pListBox->GetListItem<UIListItemOld>(OBJID_TabGeneral);
		if (pTabGeneral)
		{
			auto pWindowGeneral = pTabGeneral->GetElement<UIWindowOld>(OBJID_WindowGeneral);
			if (pWindowGeneral)
			{
				auto pPartyRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_PartyRequest);
				if (pPartyRequest)
					pPartyRequest->setSelected(SETTINGSHANDLER->getPartyRequest());

				auto pTradeRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_TradeRequest);
				if (pTradeRequest)
					pTradeRequest->setSelected(SETTINGSHANDLER->getTradeRequest());

				auto pWhisper = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Whisper);
				if (pWhisper)
					pWhisper->setSelected(SETTINGSHANDLER->getWhisper());

				auto pDamageList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_DamageList);
				if (pDamageList)
					pDamageList->selectItem(SETTINGSHANDLER->getDamageDebug() ? OBJID_ONBox : OBJID_OFFBox);

				auto pHpList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_HPList);
				if (pHpList)
					pHpList->selectItem(SETTINGSHANDLER->getHpBar() ? OBJID_ONBox : OBJID_OFFBox);

				auto pFPSList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_FPSList);
				if (pFPSList)
					pFPSList->selectItem(SETTINGSHANDLER->getFps() ? OBJID_ONBox : OBJID_OFFBox);

				auto pLootFilter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_LootFilter);
				if (pLootFilter)
					pLootFilter->setSelected(cLootFilter.getEnabled());

				auto pHpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_HPPotion);
				if (pHpPotion)
					pHpPotion->setSelected(cLootFilter.getHpPot());

				auto pMpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_MPPotion);
				if (pMpPotion)
					pMpPotion->setSelected(cLootFilter.getMpPot());

				auto pSpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_SPPotion);
				if (pSpPotion)
					pSpPotion->setSelected(cLootFilter.getSpPot());

				auto pGold = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Gold);
				if (pGold)
					pGold->setSelected(cLootFilter.getGold());

				auto pAmulets = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Amulets);
				if (pAmulets)
					pAmulets->setSelected(cLootFilter.getAmulets());

				auto pRings = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Rings);
				if (pRings)
					pRings->setSelected(cLootFilter.getRings());

				auto pSheltoms = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Sheltoms);
				if (pSheltoms)
					pSheltoms->setSelected(cLootFilter.getSheltoms());

				auto pForce = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Force);
				if (pForce)
					pForce->setSelected(cLootFilter.getForce());

				auto pPremiums = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Premiums);
				if (pPremiums)
					pPremiums->setSelected(cLootFilter.getPremiums());

				auto pNonSpec = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_NonSpec);
				if (pNonSpec)
					pNonSpec->setSelected(cLootFilter.getNonSpec());

				auto pFighter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Fighter);
				if (pFighter)
					pFighter->setSelected(cLootFilter.getFighter());

				auto pMech = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Mechanician);
				if (pMech)
					pMech->setSelected(cLootFilter.getMech());

				auto pArcher = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Archer);
				if (pArcher)
					pArcher->setSelected(cLootFilter.getArcher());

				auto pPikeman = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Pikeman);
				if (pPikeman)
					pPikeman->setSelected(cLootFilter.getPikeman());

				auto pAtalanta = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Atalanta);
				if (pAtalanta)
					pAtalanta->setSelected(cLootFilter.getAtalanta());

				auto pKnight = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Knight);
				if (pKnight)
					pKnight->setSelected(cLootFilter.getKnight());

				auto pMagician = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Magician);
				if (pMagician)
					pMagician->setSelected(cLootFilter.getMagician());

				auto pPriestess = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Priestess);
				if (pPriestess)
					pPriestess->setSelected(cLootFilter.getPriestess());

				auto pDefense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Defense);
				if (pDefense)
					pDefense->setSelected(cLootFilter.getDefense());

				auto pOffense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Offense);
				if (pOffense)
					pOffense->setSelected(cLootFilter.getOffense());

				auto pCrystals = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Crystals);
				if (pCrystals)
					pCrystals->setSelected(cLootFilter.getCrystals());

				auto pEverything = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Everything);
				if (pEverything)
					pEverything->setSelected(cLootFilter.getEverything());

				for (int i = 0; i < 10; i++)
				{
					auto pMacro = pWindowGeneral->GetElement<UIInputOld>(OBJID_Macro1 + i);
					if (pMacro)
						pMacro->setText(SETTINGSHANDLER->getMacro(i + 1));
				}
			}
		}
	}
}

void cSettingsWindow::ResetSettings()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);

	if (pListBox)
	{
		auto pTabVideo = pListBox->GetListItem<UIListItemOld>(OBJID_TabVideo);
		if (pTabVideo)
		{
			auto pWindowVideo = pTabVideo->GetElement<UIWindowOld>(OBJID_WindowVideo);
			if (pWindowVideo)
			{
				auto pScreenList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_ScreenList);
				if (pScreenList)
					pScreenList->selectItem(SETTINGSHANDLER->getWindowMode() ? OBJID_OFFBox : OBJID_ONBox);

				auto pStartMaximized = pWindowVideo->GetElement<UICheckboxOld>(OBJID_StartMaximized);
				if (pStartMaximized)
					pStartMaximized->setSelected(true);

				auto pAutoAdjust = pWindowVideo->GetElement<UICheckboxOld>(OBJID_AutoAdjust);
				if (pAutoAdjust)
					pAutoAdjust->setSelected(true);

				auto pRatioList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_RatioList);
				if (pRatioList)
				{
					pRatioList->selectItem(SETTINGSHANDLER->getRatio());

					auto pSelectedRatio = pRatioList->getSelectedItem();
					if (pSelectedRatio)
					{
						auto pResolutionList = pSelectedRatio->GetElement<UIListBoxOld>(OBJID_ResolutionList);
						if (pResolutionList)
							pResolutionList->selectItem(1);
					}
				}

				auto pTextureList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_TextureList);
				if (pTextureList)
					pTextureList->selectItem(OBJID_ONBox);

				auto pBitList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_BitList);
				if (pBitList)
					pBitList->selectItem(32);

				auto pCameraList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_CameraList);
				if (pCameraList)
					pCameraList->selectItem(OBJID_ONBox);

				auto pInvertedList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_InvertedList);
				if (pInvertedList)
					pInvertedList->selectItem(OBJID_OFFBox);
			}
		}

		auto pTabAudio = pListBox->GetListItem<UIListItemOld>(OBJID_TabAudio);
		if (pTabAudio)
		{
			auto pWindowAudio = pTabAudio->GetElement<UIWindowOld>(OBJID_WindowAudio);
			if (pWindowAudio)
			{
				auto pMusicController = pWindowAudio->GetElement<UIWindowOld>(OBJID_MusicController);
				if (pMusicController)
				{
					auto pMute = pMusicController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						pMute->setSelected(false);

					auto pVolume = pMusicController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						pVolume->setValue(50);
				}

				auto pEffectsController = pWindowAudio->GetElement<UIWindowOld>(OBJID_EffectsController);
				if (pEffectsController)
				{
					auto pMute = pEffectsController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						pMute->setSelected(false);

					auto pVolume = pEffectsController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						pVolume->setValue(50);
				}
			}
		}

		auto pTabGeneral = pListBox->GetListItem<UIListItemOld>(OBJID_TabGeneral);
		if (pTabGeneral)
		{
			auto pWindowGeneral = pTabGeneral->GetElement<UIWindowOld>(OBJID_WindowGeneral);
			if (pWindowGeneral)
			{
				auto pPartyRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_PartyRequest);
				if (pPartyRequest)
					pPartyRequest->setSelected(true);

				auto pTradeRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_TradeRequest);
				if (pTradeRequest)
					pTradeRequest->setSelected(true);

				auto pWhisper = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Whisper);
				if (pWhisper)
					pWhisper->setSelected(true);

				auto pDamageList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_DamageList);
				if (pDamageList)
					pDamageList->selectItem(OBJID_ONBox);

				auto pHpList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_HPList);
				if (pHpList)
					pHpList->selectItem(OBJID_ONBox);

				auto pFPSList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_FPSList);
				if (pFPSList)
					pFPSList->selectItem(OBJID_ONBox);

				auto pLootFilter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_LootFilter);
				if (pLootFilter)
					pLootFilter->setSelected(true);

				auto pHpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_HPPotion);
				if (pHpPotion)
					pHpPotion->setSelected(true);

				auto pMpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_MPPotion);
				if (pMpPotion)
					pMpPotion->setSelected(true);

				auto pSpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_SPPotion);
				if (pSpPotion)
					pSpPotion->setSelected(true);

				auto pGold = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Gold);
				if (pGold)
					pGold->setSelected(true);

				auto pAmulets = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Amulets);
				if (pAmulets)
					pAmulets->setSelected(true);

				auto pRings = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Rings);
				if (pRings)
					pRings->setSelected(true);

				auto pSheltoms = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Sheltoms);
				if (pSheltoms)
					pSheltoms->setSelected(true);

				auto pForce = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Force);
				if (pForce)
					pForce->setSelected(true);

				auto pPremiums = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Premiums);
				if (pPremiums)
					pPremiums->setSelected(true);

				auto pNonSpec = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_NonSpec);
				if (pNonSpec)
					pNonSpec->setSelected(true);

				auto pFighter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Fighter);
				if (pFighter)
					pFighter->setSelected(true);

				auto pMech = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Mechanician);
				if (pMech)
					pMech->setSelected(true);

				auto pArcher = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Archer);
				if (pArcher)
					pArcher->setSelected(true);

				auto pPikeman = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Pikeman);
				if (pPikeman)
					pPikeman->setSelected(true);

				auto pAtalanta = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Atalanta);
				if (pAtalanta)
					pAtalanta->setSelected(true);

				auto pKnight = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Knight);
				if (pKnight)
					pKnight->setSelected(true);

				auto pMagician = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Magician);
				if (pMagician)
					pMagician->setSelected(true);

				auto pPriestess = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Priestess);
				if (pPriestess)
					pPriestess->setSelected(true);

				auto pDefense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Defense);
				if (pDefense)
					pDefense->setSelected(true);

				auto pOffense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Offense);
				if (pOffense)
					pOffense->setSelected(true);

				auto pCrystals = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Crystals);
				if (pCrystals)
					pCrystals->setSelected(true);

				auto pEverything = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Everything);
				if (pEverything)
					pEverything->setSelected(true);

				for (int i = 0; i < 10; i++)
				{
					auto pMacro = pWindowGeneral->GetElement<UIInputOld>(OBJID_Macro1 + i);
					if (pMacro)
						pMacro->setText(SETTINGSHANDLER->getMacro(i + 1));
				}
			}
		}
	}
}

void cSettingsWindow::SaveSettings()
{
	auto pListBox = pWindow1->GetElement<UIListBoxOld>(OBJID_TabList);

	if (pListBox)
	{
		pListBox->selectItem(OBJID_TabVideo);

		auto pTabVideo = pListBox->GetListItem<UIListItemOld>(OBJID_TabVideo);
		if (pTabVideo)
		{
			auto pWindowVideo = pTabVideo->GetElement<UIWindowOld>(OBJID_WindowVideo);
			if (pWindowVideo)
			{
				auto pScreenList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_ScreenList);
				if (pScreenList)
					SETTINGSHANDLER->setWindowMode(pScreenList->getSelectedItem()->getID() == OBJID_OFFBox ? 1 : 0);

				auto pStartMaximized = pWindowVideo->GetElement<UICheckboxOld>(OBJID_StartMaximized);
				if (pStartMaximized)
					SETTINGSHANDLER->setStartMaximized(pStartMaximized->getSelected());

				auto pAutoAdjust = pWindowVideo->GetElement<UICheckboxOld>(OBJID_AutoAdjust);
				if (pAutoAdjust)
					SETTINGSHANDLER->setAutoAdjust(pAutoAdjust->getSelected());

				auto pRatioList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_RatioList);
				if (pRatioList)
				{
					auto pSelectedRatio = pRatioList->getSelectedItem();
					if (pSelectedRatio)
					{
						auto pResolutionList = pSelectedRatio->GetElement<UIListBoxOld>(OBJID_ResolutionList);
						if (pResolutionList)
						{
							if (pResolutionList->getSelectedItem() != nullptr) {
								if (SETTINGSHANDLER->getRatio() != pSelectedRatio->getID() || SETTINGSHANDLER->getResolution() != pResolutionList->getSelectedItem()->getID())
								{
									SETTINGSHANDLER->setRatio(pSelectedRatio->getID());
									SETTINGSHANDLER->setResolution(pResolutionList->getSelectedItem()->getID());
								}
							}
						}
					}
				}

				auto pTextureList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_TextureList);
				if (pTextureList)
					SETTINGSHANDLER->setTextureQuality(pTextureList->getSelectedItem()->getID() == OBJID_ONBox ? 1 : 2);

				auto pBitList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_BitList);
				if (pBitList)
					SETTINGSHANDLER->setBitDepth(pBitList->getSelectedItem()->getID());

				auto pCameraList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_CameraList);
				if (pCameraList)
					SETTINGSHANDLER->setSight(pCameraList->getSelectedItem()->getID() == OBJID_ONBox);

				auto pInvertedList = pWindowVideo->GetElement<UIListBoxOld>(OBJID_InvertedList);
				if (pInvertedList)
					SETTINGSHANDLER->setCamInv(pInvertedList->getSelectedItem()->getID() == OBJID_ONBox);
			}
		}

		auto pTabAudio = pListBox->GetListItem<UIListItemOld>(OBJID_TabAudio);
		if (pTabAudio)
		{
			auto pWindowAudio = pTabAudio->GetElement<UIWindowOld>(OBJID_WindowAudio);
			if (pWindowAudio)
			{
				auto pMusicController = pWindowAudio->GetElement<UIWindowOld>(OBJID_MusicController);
				if (pMusicController)
				{
					auto pMute = pMusicController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						SETTINGSHANDLER->setSound(!pMute->getSelected());

					auto pVolume = pMusicController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						SETTINGSHANDLER->setSoundVolume(pVolume->getValue());
				}

				auto pEffectsController = pWindowAudio->GetElement<UIWindowOld>(OBJID_EffectsController);
				if (pEffectsController)
				{
					auto pMute = pEffectsController->GetElement<UICheckboxOld>(OBJID_Mute);
					if (pMute)
						SETTINGSHANDLER->setEffects(!pMute->getSelected());

					auto pVolume = pEffectsController->GetElement<UIHorizontalScrollOld>(OBJID_Volume);
					if (pVolume)
						SETTINGSHANDLER->setEffectsVolume(pVolume->getValue());
				}
			}
		}

		auto pTabGeneral = pListBox->GetListItem<UIListItemOld>(OBJID_TabGeneral);
		if (pTabGeneral)
		{
			auto pWindowGeneral = pTabGeneral->GetElement<UIWindowOld>(OBJID_WindowGeneral);
			if (pWindowGeneral)
			{
				auto pPartyRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_PartyRequest);
				if (pPartyRequest)
					SETTINGSHANDLER->setPartyRequest(pPartyRequest->getSelected());

				auto pTradeRequest = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_TradeRequest);
				if (pTradeRequest)
					SETTINGSHANDLER->setTradeRequest(pTradeRequest->getSelected());

				auto pWhisper = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Whisper);
				if (pWhisper)
					SETTINGSHANDLER->setWhisper(pWhisper->getSelected());

				auto pDamageList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_DamageList);
				if (pDamageList)
					SETTINGSHANDLER->setDamageDebug(pDamageList->getSelectedItem()->getID() == OBJID_ONBox);

				auto pHpList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_HPList);
				if (pHpList)
					SETTINGSHANDLER->setHpBar(pHpList->getSelectedItem()->getID() == OBJID_ONBox);

				auto pFPSList = pWindowGeneral->GetElement<UIListBoxOld>(OBJID_FPSList);
				if (pFPSList)
					SETTINGSHANDLER->setFps(pFPSList->getSelectedItem()->getID() == OBJID_ONBox);

				auto pLootFilter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_LootFilter);
				if (pLootFilter)
					cLootFilter.setEnabled(pLootFilter->getSelected());

				auto pHpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_HPPotion);
				if (pHpPotion)
					cLootFilter.setHpPot(pHpPotion->getSelected());

				auto pMpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_MPPotion);
				if (pMpPotion)
					cLootFilter.setMpPot(pMpPotion->getSelected());

				auto pSpPotion = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_SPPotion);
				if (pSpPotion)
					cLootFilter.setSpPot(pSpPotion->getSelected());

				auto pGold = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Gold);
				if (pGold)
					cLootFilter.setGold(pGold->getSelected());

				auto pAmulets = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Amulets);
				if (pAmulets)
					cLootFilter.setAmulets(pAmulets->getSelected());

				auto pRings = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Rings);
				if (pRings)
					cLootFilter.setRings(pRings->getSelected());

				auto pSheltoms = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Sheltoms);
				if (pSheltoms)
					cLootFilter.setSheltoms(pSheltoms->getSelected());

				auto pForce = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Force);
				if (pForce)
					cLootFilter.setForce(pForce->getSelected());

				auto pPremiums = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Premiums);
				if (pPremiums)
					cLootFilter.setPremiums(pPremiums->getSelected());

				auto pNonSpec = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_NonSpec);
				if (pNonSpec)
					cLootFilter.setNonSpec(pNonSpec->getSelected());

				auto pFighter = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Fighter);
				if (pFighter)
					cLootFilter.setFighter(pFighter->getSelected());

				auto pMech = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Mechanician);
				if (pMech)
					cLootFilter.setMech(pMech->getSelected());

				auto pArcher = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Archer);
				if (pArcher)
					cLootFilter.setArcher(pArcher->getSelected());

				auto pPikeman = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Pikeman);
				if (pPikeman)
					cLootFilter.setPikeman(pPikeman->getSelected());

				auto pAtalanta = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Atalanta);
				if (pAtalanta)
					cLootFilter.setAtalanta(pAtalanta->getSelected());

				auto pKnight = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Knight);
				if (pKnight)
					cLootFilter.setKnight(pKnight->getSelected());

				auto pMagician = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Magician);
				if (pMagician)
					cLootFilter.setMagician(pMagician->getSelected());

				auto pPriestess = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Priestess);
				if (pPriestess)
					cLootFilter.setPriestess(pPriestess->getSelected());

				auto pDefense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Defense);
				if (pDefense)
					cLootFilter.setDefense(pDefense->getSelected());

				auto pOffense = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Offense);
				if (pOffense)
					cLootFilter.setOffense(pOffense->getSelected());

				auto pCrystals = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Crystals);
				if (pCrystals)
					cLootFilter.setCrystals(pCrystals->getSelected());

				auto pEverything = pWindowGeneral->GetElement<UICheckboxOld>(OBJID_Everything);
				if (pEverything)
					cLootFilter.setEverything(pEverything->getSelected());

				for (int i = 0; i < 10; i++)
				{
					auto pMacro = pWindowGeneral->GetElement<UIInputOld>(OBJID_Macro1 + i);
					if (pMacro)
						SETTINGSHANDLER->setMacro(i, pMacro->getText());
				}
			}
		}
	}

	SETTINGSHANDLER->save();
	SetVolumeBGM(0);
	PlayWav_UpdateVolume();
}
