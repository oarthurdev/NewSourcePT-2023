
#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"
#include "..\\smreg.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"
#include "Language\\language.h"
#include "..\\CAutoCamera.h"
#include "Settings\Settings.h"
#include "Settings\UI.h"
#include "cSettingsWindow.h"
#include "File\File.h"
#include "Login\Login.h"
#include "Log/Logger.h"

extern int			iSettingsBg;
extern int			iSettingsButton[2];
extern int			iSettingsRelog;
extern int			iSettingsSave;
extern int			iSettingsCheckBox[2];



static CAutoCamera		s_AutoCamera;

#ifdef _LANGUAGE_BRAZIL	
char* szJoinWebUrl = "http://www.Priston Tale.com.br";
#endif

extern POINT3D WaveCameraPosi;
extern int	   WaveCameraFactor;
extern int	   WaveCameraTimeCount;
extern int	   WaveCameraDelay;
extern BOOL	   WaveCameraFlag;

char	UserAccount[ACCOUNT_SIZE];
char	UserPassword[PASSWORD_SIZE];

HoOpening::HoOpening()
{


	Stage = NULL;
	PatCamera = NULL;

	LogoBlendValue = 0;
	LoginBlendValue = 0;

	Load();
	StartConnectServerFlag = FALSE;
	WorkState = STATE_OPENING;

	MidY = (600 / 2);
	SetWindowText(hTextWnd, NULL);

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	TarDist = 1600 * fONE;
	CaAngle.x = 220;
	CaAngle.y = 0;
	CaAngle.z = 0;




	MouseDownServerIndex = -1;
	CameraFrame = 0;
}

HoOpening::~HoOpening()
{
	Close();
}

int HoOpening::Init()
{
	GameErrorValue = -1;
	ConnectErrorCount = 0;
	FocusWndFlag = FALSE;
	SetWindowText(hTextWnd, "");
	SendMessage(hTextWnd, EM_SETLIMITTEXT, 31, 0);

	LoginInputState = 0;
	ConnectError = ERROR_NONE;
	ServerWaitTimeCount = 0;
	StartQuitFlag = FALSE;

	WorkState = STATE_OPENING;
	StartConnectServerFlag = FALSE;
	ConnectServerSucessFlag = FALSE;

	FadeCurrentState = FADE_OUT;
	FadeNextState = FADE_OUT;

	LogoBlendValue = 0;
	LoginBlendValue = 0;
	ServerSelectBlendValue = 0;

	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;

	SetWindowText(hTextWnd, NULL);

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	TarDist = 400 * fONE;

	CaAngle.x = 100;
	CaAngle.y = 0;
	CaAngle.z = 0;

	SetFade();

	smInitColorZClip(0, 0, 0);

	smRender.Color_R = 40;
	smRender.Color_G = 0;
	smRender.Color_B = -30;
	smRender.Color_A = 0;
	smRender.ClearLight();

	StopBGM();
	OpenBGM("game\\GUI\\Opening\\Login\\UI\\Intro.wav");
	PlayBGM();

	SetVolumeBGM(OpeningBgmVolume);

	std::string id;

	try
	{
		File file("game.ini");

		id = file.readString("Game", "LastAccount");
	}
	catch (FileException& e)
	{
		char buffer[100] = { 0 };
		strcpy_s(buffer, sizeof(buffer), e.what());
		Logger::getInstance()->output(LogType::Game, buffer);
	}

	if (!id.empty())
	{
		memset(UserAccount, 0, sizeof(UserAccount));
		memcpy(UserAccount, id.c_str(), id.size());
		LoginInputState = 1;
	}

	CurrentWorkState = STATE_OPENING;
	NextWorkState = STATE_OPENING;
	MouseDownServerIndex = -1;
	MouseDownFlag = FALSE;

	CameraFrame = 160;



	g_NewParticleMgr.Init();
	InitAssaEffect();

	InitCinemaFadeEffect();



	smIdentityMatrix(m_CameraRotInvert);

	m_IsDrawOpening = TRUE;
	m_AutoCameraFrameTime = 50;
	m_ParticleSpawnTimeCount = 0;

	s_AutoCamera.m_Frame = 0;


	m_AddWidth = (SETTINGSHANDLER->getWidth() - 800) / 2;
	m_AddHeight = (SETTINGSHANDLER->getHeight() - 600) / 2;


	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
	startLogoAddX = 32;
	startAccountAddX = 230;
	startAccountAddY = 280;

	return TRUE;
}


extern void ReadTexSettings();

void HoOpening::SetCameraCharPos(void)
{
	int x = 0;
	int y = 0;
	int z = (440 << FLOATNS);

	smEMATRIX eCameraRotInvert;
	smEMatrixInvert(eCameraRotInvert, s_AutoCamera.m_eCameraRotMat);

	memcpy((smEMATRIX*)&m_CameraRotInvert, &eCameraRotInvert, sizeof(smEMATRIX));
	smMatrixShift(m_CameraRotInvert, 4);

	int rx = x * m_CameraRotInvert._11 +
		y * m_CameraRotInvert._21 +
		z * m_CameraRotInvert._31;

	int ry = x * m_CameraRotInvert._12 +
		y * m_CameraRotInvert._22 +
		z * m_CameraRotInvert._32;

	int rz = x * m_CameraRotInvert._13 +
		y * m_CameraRotInvert._23 +
		z * m_CameraRotInvert._33;

	rx >>= FLOATS_EM;
	ry >>= FLOATS_EM;
	rz >>= FLOATS_EM;

	lpCurPlayer->pX = int(s_AutoCamera.m_fCameraPos_x) + rx;
	lpCurPlayer->pY = int(s_AutoCamera.m_fCameraPos_y) + ry;
	lpCurPlayer->pZ = int(s_AutoCamera.m_fCameraPos_z) + rz;
}





void HoOpening::SetParticleEffectSpawn(void)
{
	m_ParticleSpawnTimeCount++;
	if ((m_ParticleSpawnTimeCount % 70) != 0)
		return;

	m_ParticleSpawnTimeCount = 0;


	POINT3D curPos;
	POINT3D desPos;
	int		rx, ry, rz;
	int		Type = (rand() % 100);
	int		rand_1 = (rand() % 1000) << 8;
	int		rand_2 = (rand() % 1000) << 8;
	int		rand_3 = (rand() % 1000) << 8;
	int		rand_4 = (rand() % 1000) << 8;


	if (Type < 10)
	{
		curPos.x = -rand_1;
		desPos.x = rand_2;
	}
	else
	{
		curPos.x = rand_1;
		desPos.x = -rand_2;
	}


	curPos.y = 200000;
	desPos.y = -200000;

	if (Type < 30)
	{
		curPos.z = rand_1;
		desPos.z = rand_2;
	}
	else
	{
		curPos.z = rand_3;
		desPos.z = rand_4;
	}


	rx = curPos.x * m_CameraRotInvert._11 +
		curPos.y * m_CameraRotInvert._21 +
		curPos.z * m_CameraRotInvert._31;

	ry = curPos.x * m_CameraRotInvert._12 +
		curPos.y * m_CameraRotInvert._22 +
		curPos.z * m_CameraRotInvert._32;

	rz = curPos.x * m_CameraRotInvert._13 +
		curPos.y * m_CameraRotInvert._23 +
		curPos.z * m_CameraRotInvert._33;

	rx >>= FLOATS_EM;
	ry >>= FLOATS_EM;
	rz >>= FLOATS_EM;

	curPos.x = lpCurPlayer->pX + rx;
	curPos.y = lpCurPlayer->pY + ry;
	curPos.z = lpCurPlayer->pZ + rz;


	rx = desPos.x * m_CameraRotInvert._11 +
		desPos.y * m_CameraRotInvert._21 +
		desPos.z * m_CameraRotInvert._31;

	ry = desPos.x * m_CameraRotInvert._12 +
		desPos.y * m_CameraRotInvert._22 +
		desPos.z * m_CameraRotInvert._32;

	rz = desPos.x * m_CameraRotInvert._13 +
		desPos.y * m_CameraRotInvert._23 +
		desPos.z * m_CameraRotInvert._33;

	rx >>= FLOATS_EM;
	ry >>= FLOATS_EM;
	rz >>= FLOATS_EM;

	desPos.x = lpCurPlayer->pX + rx;
	desPos.y = lpCurPlayer->pY + ry;
	desPos.z = lpCurPlayer->pZ + rz;


	AssaParticle_TerrainFire(&curPos, &desPos);
}






int HoOpening::DebugModeLoadFieldInfo(void)
{
	FILE* fp = fopen("game\\GUI\\Opening\\Login\\UI\\OpeningField.txt", "rb");
	if (fp == NULL)
		return FALSE;

	Stage = NULL;


	char* p, line[256], decode[256], strBuff[256];
	while (!feof(fp))
	{
		if (fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			break;
		}

		p = GetWord(decode, line);


		if (lstrcmp(decode, "*ÇÊµå¸í") == 0)
		{
			p = GetWord(strBuff, p);
			Stage = smSTAGE3D_ReadASE(strBuff);
			if (Stage)
				Stage->Head = TRUE;
		}
		else if (lstrcmp(decode, "*Ä«¸Þ¶ó¸í") == 0)
		{
			p = GetWord(strBuff, p);
			s_AutoCamera.ReadASE_AutoCamera(strBuff);
		}
		else if (lstrcmp(decode, "*Ä«¸Þ¶ó¼Óµµ") == 0)
		{
			p = GetWord(strBuff, p);
			m_AutoCameraFrameTime = atoi(strBuff);
		}
		else if (lstrcmp(decode, "*¿öÇÁÇÁ·¹ÀÓ") == 0)
		{
			p = GetWord(strBuff, p);
			int StFrame = atoi(strBuff);

			p = GetWord(strBuff, p);
			int EndFrame = atoi(strBuff);

			s_AutoCamera.SetWarpFrame(StFrame, EndFrame);
		}
		else if (lstrcmp(decode, "*ÁöÇü¹°Ã¼") == 0)
		{
			p = GetWord(strBuff, p);
			Stage->StageObject->AddObjectFile(strBuff);
		}
		else if (lstrcmp(decode, "*ÁöÇü¾Ö´Ï") == 0)
		{
			p = GetWord(strBuff, p);
			Stage->StageObject->AddObjectFile(strBuff, strBuff);
		}
	}

	fclose(fp);

	if (Stage == NULL)
		return FALSE;

	return TRUE;
}

int GetClick(DWORD x, DWORD y, DWORD L, DWORD A)
{
	DWORD XMouse = pCursorPos.x;
	DWORD YMouse = pCursorPos.y;
	int Resultado = 0;

	extern bool clickable;

	if (clickable)
	{

		if (XMouse > x)
		{
			if (XMouse < (x + L - 1))
			{
				if (YMouse > y)
				{
					if (YMouse < (y + A - 1))
					{
						Resultado = 1;
					}
				}
			}
		}
	}
	return Resultado;
}

char ratio[4] = { 0 };
int BackGround;
int HoOpening::Load()
{


	int IsLoad = FALSE;
	PatCamera = NULL;
	ObjCamera = NULL;

	if (smConfig.getSecurity() >= AccountTypes::SEC_MODERATOR)
		IsLoad = DebugModeLoadFieldInfo();

	if (IsLoad == FALSE)
	{
		Stage = smSTAGE3D_ReadASE("StartImage\\Opening\\map\\stage.ASE");

		if (Stage)
		{
			Stage->Head = TRUE;

			s_AutoCamera.ReadASE_AutoCamera("StartImage\\Opening\\opening_camera.ASE");
			m_AutoCameraFrameTime = 50;
			s_AutoCamera.SetWarpFrame(472, 473);

			Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani02.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani03.ASE");

			Stage->StageObject->AddObjectFile("StartImage\\Opening\\babel\\st-ani04.ASE", "StartImage\\Opening\\babel\\st-ani04.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_A.ASE", "StartImage\\Opening\\npc\\opening_NPC_A.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_B.ASE", "StartImage\\Opening\\npc\\opening_NPC_B.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_C.ASE", "StartImage\\Opening\\npc\\opening_NPC_C.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_D.ASE", "StartImage\\Opening\\npc\\opening_NPC_D.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_E.ASE", "StartImage\\Opening\\npc\\opening_NPC_E.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_F.ASE", "StartImage\\Opening\\npc\\opening_NPC_F.ASE");

		}
	}

	if (Stage == NULL)
		return FALSE;

	smGameStage[0] = Stage;
	smGameStage[1] = NULL;


	/*GameLogo[0] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[1] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[2] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[3] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[4] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[5] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\GameLogo6.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);*/

	ButtonLoginImage[0] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\cad.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ButtonLoginImage[1] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\cad_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	ButtonQuitImage[0] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\S_Exit_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ButtonQuitImage[1] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\S_Exit.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	iWindowID = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iInputID = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\input.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iBtnLogin[0] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\btnlogin.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iBtnLogin[1] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\btnlogin_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iBtnExit[0] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\btnexit.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	iBtnExit[1] = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\btnexit_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Logo = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
#ifdef _LANGUAGE_JAPANESE
	PristonLogoImage = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\BlackBox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
#else
	PristonLogoImage = CreateTextureMaterial("game\\GUI\\Opening\\Login\\UI\\priston_txt.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
#endif

	BlackBoxImage = CreateTextureMaterial("game\\GUI\\Opening\\Select\\UI\\BlackBox.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	WhiteBoxImage = CreateTextureMaterial("game\\GUI\\Opening\\Select\\UI\\WhiteBox.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);


	Message.Init();
	MessageBox.Init();

	ReadTexSettings();
	ReadTextures();

	if (Stage)
	{
		Stage->smMaterialGroup->CheckMatreialTextureSwap();
	}

	return TRUE;
}

BOOL bIsWidescreen = FALSE;

void HoOpening::resize()
{

	MidX = SETTINGSHANDLER->getWidth() / 2;
	MidY = SETTINGSHANDLER->getHeight() / 2;

	m_AddWidth = (SETTINGSHANDLER->getWidth() - 800) / 2;
	m_AddHeight = (SETTINGSHANDLER->getHeight() - 600) / 2;

	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
}




int		CaretCount = 0;
DWORD	End = 0;
extern int Client_Version;

#define	DISP_LOGIN_LEN		15


BOOL bDone = FALSE;
int iSave = 0;

extern BOOL bAdjustWindow;

void SaveConfig()
{
	SETTINGSHANDLER->save();
}

extern int QuitGame();

BOOL bs = FALSE;
int iTime = 0;
extern bool bCaptureOpening;
extern DWORD dwTickCap;

void Relog()
{
	if (bs == FALSE)
	{
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcessA(NULL, "Game.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

		bs = TRUE;
	}

	if (iTime >= 3)
		QuitGame();
	else
		iTime++;
}

void DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}
bool clickable = true;

int HoOpening::Draw()
{
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;

	m_AddWidth = (smScreenWidth - 800) / 2;
	m_AddHeight = (smScreenHeight - 600) / 2;

	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
	startLogoAddX = 32;
	startAccountAddX = 150;
	startAccountAddY = 310;

	FastFade();

	
	
	int Largura, Altura;
	Largura = 1600;
	Altura = 850;
	DrawImage(Logo, (smScreenWidth - Largura) / 2, (smScreenHeight - Altura) / 2, Largura, Altura);	

	DrawImage(iWindowID, smScreenWidth / 2 - 250, smScreenHeight / 2 - 270, 500, 500);
	
	char Version[250];
	int v1 = Client_Version / 1000;
	int v2 = (Client_Version / 10) % 100;
	int v3 = Client_Version % 10;
	/*wsprintf(Version, "Versão %d", Client_Version);*/
	wsprintf(Version, "%s%d.%d.%d", "Ver: ", v1, v2, v3);
	SetFontTextColor(RGB(200, 200, 200));
	dsTextLineOut(0, SETTINGSHANDLER->getWidth() - 80, 13, Version, strlen(Version));
	HoDrawTexImage(iInputID, float(startLogoX + startAccountAddX), float(startLogoY + startAccountAddY) - 40, 300.f, 80.f, 0, 0, 300.f, 80.f, LogoBlendValue);

	if (pCursorPos.x > (startLogoX + 150) &&
		pCursorPos.y > (startLogoY + 355) &&
		pCursorPos.x < (startLogoX + 286) &&
		pCursorPos.y < (startLogoY + 385))
	{
		DrawImage(iBtnLogin[1], startLogoX + 150,
			startLogoY + 355,
			136, 30);
	}
	else
	{
		DrawImage(iBtnLogin[0], startLogoX + 150,
			startLogoY + 355,
			136, 30);
	}


	if (pCursorPos.x > (startLogoX + 314) &&
		pCursorPos.y > (startLogoY + 355) &&
		pCursorPos.x < (startLogoX + 450) &&
		pCursorPos.y < (startLogoY + 385))
	{
		DrawImage(iBtnExit[1], startLogoX + 314,
			startLogoY + 355,
			136, 30);
	}
	else
	{
		DrawImage(iBtnExit[0], startLogoX + 314,
			startLogoY + 355,
			136, 30);
	}



	if (NextWorkState == STATE_END) {
		DrawFade();
	}

	if (cSettings.isOpen())
	{
		if (MouseButton[0] /*&& cSettings.LButtonDown()*/)
			MouseButton[0] = 0;
	}


	////setings engrenagem
	if (GetClick((SETTINGSHANDLER->getWidth()>> 1) - 125, 10, 246, 23))
	{
		dsDrawTexImage(iSettingsButton[1], (SETTINGSHANDLER->getWidth() >> 1) -125, 10, 246, 23, 255);

		if (MouseButton[0])
		{
			SettingsUI::getInstance()->open();
			if (cSettings.isOpen())
				cSettings.Close();
			else
				cSettings.Open();

			MouseButton[0] = 0;
		}
	}
	else {
		dsDrawTexImage(iSettingsButton[0], (SETTINGSHANDLER->getWidth() >> 1) -125, 10, 246, 23, 255);
	}

	char buffer[256];
	memset(buffer, 0, sizeof(buffer));

	SetFontTextColor(RGB(255, 255, 255));

	if (bCaptureOpening)
	{
		time_t t = time(0);
		struct tm* now = localtime(&t);

		char localtime[128] = { 0 };
		strftime(localtime, sizeof(localtime), "Hora Local: %d-%m-%Y %X", now);

		dsTextLineOut(0,(SETTINGSHANDLER->getWidth() / 2) - 90, 20, localtime, strlen(localtime));

		if (GetTickCount() - dwTickCap >= 170)
		{
			dwTickCap = 0;
			bCaptureOpening = false;
		}
	}



	if (CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT && ScreenBlendValue <= 100)
	{

		if (LoginBlendValue >= 255)
		{
			if (FocusWndFlag == FALSE)
			{
				FocusWndFlag = TRUE;
				hFocusWnd = hTextWnd;
			}

			if (StartConnectServerFlag == FALSE && ConnectError == ERROR_NONE)
			{
				if (pCursorPos.x > (startLogoX + startAccountAddX + 37) &&
					pCursorPos.x < (startLogoX + startAccountAddX + 297) &&
					pCursorPos.y >(startLogoY + startAccountAddY - 36) &&
					pCursorPos.y < (startLogoY + startAccountAddY - 6) &&
					MouseButton[0])
				{
					if (LoginInputState == 1)
					{

						LoginInputState = 0;
						SetWindowText(hFocusWnd, UserAccount);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount), lstrlen(UserAccount) + 1);
					}
				}

				if (pCursorPos.x > (startLogoX + startAccountAddX + 37) &&
					pCursorPos.x < (startLogoX + startAccountAddX + 297) &&
					pCursorPos.y >(startLogoY + startAccountAddY + 4) &&
					pCursorPos.y < (startLogoY + startAccountAddY + 37) &&
					MouseButton[0])
				{
					if (LoginInputState == 0)
					{
						SetIME_Mode(0);
						LoginInputState = 1;
						SetWindowText(hFocusWnd, UserPassword);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword), lstrlen(UserPassword) + 1);
					}
				}
			}



			if (hFocusWnd && ConnectError == ERROR_NONE && StartConnectServerFlag == FALSE)
			{
				if (LoginInputState == 0)
				{
					GetWindowText(hFocusWnd, UserAccount, sizeof(UserAccount));
					KeyFilter(UserAccount);

				}
				else if (LoginInputState == 1)
				{
					GetWindowText(hFocusWnd, UserPassword, sizeof(UserPassword));
					KeyFilter(UserPassword);
				}
			}

			if (hFocusWnd)
				SendMessage(hFocusWnd, EM_GETSEL, NULL, (LPARAM)&End);

			SetFontTextColor(RGB(255, 255, 255));

			if (hFocusWnd)
			{
				if (CaretCount < 16)
				{
					if (End > DISP_LOGIN_LEN) End = DISP_LOGIN_LEN;

					if (LoginInputState == 0)
						dsTextLineOut(0,startLogoX + startAccountAddX + 37 + End * 6 + 1, startLogoY + startAccountAddY - 26, "|", 1);
					else if (LoginInputState == 1)
						dsTextLineOut(0,startLogoX + startAccountAddX + 37 + End * 6 + 1, startLogoY + startAccountAddY + 13, "|", 1);
				}

				CaretCount++;
				if (CaretCount > 32)
					CaretCount = 0;
			}

			int sp, len;

			sp = 0;
			len = lstrlen(UserAccount);
			if (len > DISP_LOGIN_LEN)
			{
				sp = len - DISP_LOGIN_LEN;
				len -= sp;
			}
			dsTextLineOut(0,startLogoX + startAccountAddX + 37, startLogoY + startAccountAddY - 26, UserAccount + sp, len);
			len = lstrlen(UserPassword);
			if (len > DISP_LOGIN_LEN) len = DISP_LOGIN_LEN;

			for (int count = 0; count < len; count++)
				dsTextLineOut(0,startLogoX + startAccountAddX + 37 + count * 6, startLogoY + startAccountAddY + 16, "*", 1);

		}
	}

	if (StartConnectServerFlag && ConnectError == ERROR_NONE)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[0]);

	if (ConnectError == ERROR_CONNECT)
	{
		StartConnectServerFlag = FALSE;
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[1]);
	}
	else if (ConnectError == ERROR_NO_ACCOUNT)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[2]);
	else if (ConnectError == ERROR_NO_PASSWORD)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[3]);
	else if (ConnectError == ERROR_NO_BETA_TESTER)
		DrawMessage(205 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[4]);
	else if (ConnectError == ERROR_NO_ACCOUNT_IN)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[5]);
	else if (ConnectError == ERROR_NO_VERSION)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[6]);
	else if (ConnectError == ERROR_NO_LIMIT)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[7]);
	else if (ConnectError == ERROR_NO_SERVER_CONNECT)
		DrawMessage(275 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[8]);
	else if (ConnectError == ERROR_NO_USE_DATE_OVER)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[9]);
	else if (ConnectError == ERROR_NO_USE_TIME_OVER)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[10]);
	else if (ConnectError == ERROR_DELETE_ACCOUNT_NOTIFY)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[11]);
	else if (ConnectError == ERROR_SERVER_TRAFFIC_BUSY)
		DrawMessage(275 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[12]);
	else if (ConnectError == ERROR_SERVER_WAIT_MOMNENT)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[13]);
	else if (ConnectError == ERROR_THIRD_CONNECT)
		DrawMessage(285 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[14], 30);
	else if (ConnectError == ERROR_HAN_PASSWORD)
		DrawMessage(285 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[15], 30);
	else if (ConnectError == ERROR_12YEARS)
		DrawMessage(285 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[16], 30);
	else if (ConnectError == ERROR_HOMEAGREE)
		DrawMessage(285 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[17], 30);
	else if (ConnectError == ERROR_UNTIL_LOGINDENIED)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[18], 30);
	else if (ConnectError == ERROR_LOGIN_DENIED)
		DrawMessage(295 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[19], 30);
	
	cSettings.Draw();
	
	return TRUE;
}




HANDLE	hHoLoginThread = 0;

DWORD WINAPI HoLoginThreadProc(void* pInfo)
{
	HoOpening* lpHoOpening = (HoOpening*)pInfo;

	if (!smWsockDataServer)
	{
		ConnectServer_InfoMain();

		if (smWsockDataServer)
		{
			ServerUserCharacterInfo = NULL;
			DownServerListInfo = NULL;
			ServerLoginError = NULL;
			lpHoOpening->ServerWaitTimeCount = 0;

			if (HoCommandLineFlag)
			{
				memset(UserAccount, 0, sizeof(UserAccount));
				memset(UserPassword, 0, sizeof(UserPassword));

				memcpy(UserAccount, HoCommandInfo.Id, strlen(HoCommandInfo.Id));
				memcpy(UserPassword, HoCommandInfo.Pass, strlen(HoCommandInfo.Pass));
			}

			LoginResult result = requestLogin(UserAccount, UserPassword);

			if (result != LoginResult::OK)
			{
				DisconnectServerFull();
				lpHoOpening->ConnectError = ERROR_NO_VERSION;
				lpHoOpening->StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}
		}
		else
		{
			lpHoOpening->ConnectError = ERROR_CONNECT;
			lpHoOpening->StartConnectServerFlag = FALSE;
		}
	}

	hHoLoginThread = 0;

	ExitThread(TRUE);
	return TRUE;
}

int HoOpening::LoginDataServer()
{
	DWORD dwHoLoginThreadId;

	if (!hHoLoginThread)
	{
		hHoLoginThread = CreateThread(NULL, 0, HoLoginThreadProc, this, 0, &dwHoLoginThreadId);

		//PlayWav2(13 - 1);
		StartConnectServerFlag = TRUE;
		return TRUE;
	}
	return FALSE;
}

int HoOpening::LoginGameServer(int serverIndex)
{

	PlayWav2(13 - 1);
	DisconnectServer_GameMain();


	if (ConnectServer_GameMain(UserServerListInfo[serverIndex].szServerIp1,
		UserServerListInfo[serverIndex].dwServerPort1,
		UserServerListInfo[serverIndex].szServerIp2,
		UserServerListInfo[serverIndex].dwServerPort2,
		UserServerListInfo[serverIndex].szServerIp3,
		UserServerListInfo[serverIndex].dwServerPort3))
	{
		StartConnectServerFlag = TRUE;
	}
	else
		ConnectError = ERROR_CONNECT;

	return TRUE;
}


int HoOpening::KeyFilter(char* message)
{
	if (message == NULL || hFocusWnd == NULL)
		return FALSE;

	if (strlen(message) >= (ACCOUNT_SIZE - 1) && message[ACCOUNT_SIZE - 2] != '\t')
	{
		message[ACCOUNT_SIZE - 2] = 0;
		SetWindowText(hFocusWnd, 0);
		SetWindowText(hFocusWnd, message);
		SendMessage(hFocusWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
	}

	for (int index = 0; index < (int)strlen(message); index++)
	{
		if (message[index] == '\t')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, 0);

			if (LoginInputState == 0)
			{
				SetIME_Mode(0);
				LoginInputState = 1;
				SetWindowText(hFocusWnd, UserPassword);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword) + 1, lstrlen(UserPassword) + 1);
			}
			else if (LoginInputState == 1)
			{
				LoginInputState = 0;
				SetWindowText(hFocusWnd, UserAccount);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount) + 1, lstrlen(UserAccount) + 1);
			}
		}
		else if (message[index] >= 'a' && message[index] <= 'z'
			|| message[index] >= 'A' && message[index] <= 'Z'
			|| message[index] >= '0' && message[index] <= '9')
		{
			continue;
		}
		else
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, message);
			SendMessage(hTextWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
			break;
		}


	}
	return TRUE;
};


int HoOpening::MainFadeIn()
{
	if (FadeNextState == FADE_IN)
	{
		ScreenBlendValue -= 2;
		if (ScreenBlendValue < 0)
			ScreenBlendValue = 0;

		if (ScreenBlendValue <= 0)
		{
			ScreenBlendValue = 0;
			FadeCurrentState = FADE_IN;
			FadeNextState = FADE_IN;
		}
	}
	return TRUE;
}


int HoOpening::MainFadeOut()
{
	if (FadeNextState == FADE_OUT)
	{
		if (ScreenBlendValue < 255)
		{
			OpeningBgmVolume -= 2;
			if (OpeningBgmVolume < 0)
				OpeningBgmVolume = 0;
			ScreenBlendValue += 3;
		}

		if (ScreenBlendValue >= 255)
		{
			ScreenBlendValue = 255;
			LogoBlendValue = 255;
			LoginBlendValue = 255;
			FadeCurrentState = FADE_OUT;
			FadeNextState = FADE_OUT;
		}
	}
	return TRUE;
}


void HoOpening::InitCinemaFadeEffect()
{
	CinemaFadeOutFlag = FALSE;
	CinemaBlendValue = 0;
	CinemaFadeState = STATE_FADE_NONE;
}


void HoOpening::MainCinemaFadeEffect()
{
	if (CinemaFadeState == STATE_FADE_IN)
	{
		CinemaBlendValue += 5;
		if (CinemaBlendValue >= 255)
			CinemaBlendValue = 255;
	}

	if (CinemaFadeState == STATE_FADE_IN && CinemaBlendValue >= 255)
		CinemaFadeState = STATE_FADE_OUT;

	if (CinemaFadeState == STATE_FADE_OUT)
	{
		CinemaBlendValue -= 5;
		if (CinemaBlendValue <= 0)
			CinemaBlendValue = 0;
	}
}



void HoOpening::DrawCinemaFadeEffect()
{
	if (CinemaFadeState != STATE_FADE_NONE)
	{
		if (CinemaBlendValue >= 0 && CinemaBlendValue <= 255)
		{

			dsDrawTexImage(WhiteBoxImage, 0, 0, SETTINGSHANDLER->getWidth(), SETTINGSHANDLER->getHeight(), CinemaBlendValue);

		}
	}
}


int HoOpening::FastFade()
{

	if ((FadeNextState == FADE_IN && LoginBlendValue < 255) ||
		(FadeNextState == FADE_OUT && LoginBlendValue > 0))
	{

		static bool fastBlendFlag = false;
		for (int index = 0; index < 256; index++)
		{
			if (VRKeyBuff[index] == TRUE)
			{
				fastBlendFlag = true;
				break;
			}
		}

		if (MouseDownFlag == FALSE)
		{
			if (MouseButton[0] && fastBlendFlag == false)
			{
				fastBlendFlag = true;
				MouseDownFlag = TRUE;
			}
		}

		if (fastBlendFlag)
		{
			if (FadeNextState == FADE_IN)
			{
				if ((CurrentWorkState == STATE_OPENING &&
					NextWorkState == STATE_OPENING) ||
					(CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT))
				{
					LogoBlendValue = 255;
					ScreenBlendValue = 0;
					FadeCurrentState = FADE_IN;

					if (HoCommandLineFlag == FALSE)
					{
						LoginBlendValue = 255;
						CurrentWorkState = STATE_LOGIN_INPUT;
						NextWorkState = STATE_LOGIN_INPUT;
					}

					if (HoCommandLineFlag)
						NextWorkState = STATE_LOGIN_INPUT;

				}
			}
			else if (FadeNextState == FADE_OUT)
			{

				LogoBlendValue = 0;
				LoginBlendValue = 0;
				ScreenBlendValue = 255;
				OpeningBgmVolume = 0;
				FadeCurrentState = FADE_OUT;

			}
			fastBlendFlag = false;
		}
	}
	return TRUE;
}

int HoOpening::DrawFade()
{
	if (ScreenBlendValue >= 0 && ScreenBlendValue <= 255)
		dsDrawTexImage(BlackBoxImage, 0, 0, SETTINGSHANDLER->getWidth(), SETTINGSHANDLER->getHeight(), ScreenBlendValue);

	return TRUE;
}

int HoOpening::MainFade()
{
	if ((FadeNextState == FADE_IN) ||
		(FadeNextState == FADE_OUT))
	{
		if (FadeCurrentState != FadeNextState)
		{
			if (FadeNextState == FADE_IN)
				MainFadeIn();
			else
			{
				SetVolumeBGM(OpeningBgmVolume);
				MainFadeOut();
			}
		}
	}
	return TRUE;
}

void HoOpening::SetFade()
{


	if (FadeCurrentState == FADE_OUT)
	{
		FadeNextState = FADE_IN;
		ScreenBlendValue = 254;
		OpeningBgmVolume = 350;
	}
	else
	{
		FadeNextState = FADE_OUT;
		ScreenBlendValue = 1;
	}
}


void HoOpening::Close()
{
	if (Stage)
	{
		delete Stage;
		Stage = NULL;



		lpCurPlayer->pX = lpCurPlayer->pY = lpCurPlayer->pZ = 0;
		smGameStage[0] = NULL;
		smGameStage[1] = NULL;

	}

	if (PatCamera)
	{
		delete PatCamera;
		PatCamera = NULL;
	}

	BackColor_R = 0;
	BackColor_G = 0;
	BackColor_B = 0;

	BackColor_mR = 0;
	BackColor_mG = 0;
	BackColor_mB = 0;

	InitSky();








}






int HoOpening::Main()
{
	if (MouseButton[0] == FALSE)
	{
		MouseDownFlag = FALSE;
	}



	float timeDelta = 1.f / 70.f;
	g_NewParticleMgr.Main(0.0f, timeDelta);

	MainSky();
	m_IsDrawOpening = s_AutoCamera.FrameMain(m_AutoCameraFrameTime);
	if (m_IsDrawOpening > 1 && CinemaFadeOutFlag == FALSE)
	{
		CinemaFadeState = STATE_FADE_IN;
		CinemaFadeOutFlag = TRUE;
	}


	//SetCameraCharPos();
	if (m_IsDrawOpening == 1)
		SetParticleEffectSpawn();

	//MainAssaEffect();
	//MainCinemaFadeEffect();

	if (WaveCameraFlag)
	{
		WaveCameraTimeCount++;

		if ((WaveCameraTimeCount > WaveCameraDelay))
		{
			WaveCameraTimeCount = 0;
			if (WaveCameraDelay > 1 && WaveCameraFactor < 40)
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 9.f);
			else
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 8.f);
		}

		if (abs(WaveCameraFactor) < 1)
		{
			WaveCameraFlag = FALSE;
			WaveCameraTimeCount = 0;
		}
	}




	if (ConnectError != ERROR_NONE)
	{
		if (ConnectErrorCount >= 160)
		{
			MouseDownServerIndex = -1;
			bool errorEndFlag = false;

			if (MouseButton[0] || MouseDblClick)
				errorEndFlag = true;


			for (int index = 0; index < 256; index++)
			{
				if (VRKeyBuff[index] == TRUE)
				{
					errorEndFlag = true;
					break;
				}
			}

			if (ConnectErrorCount >= 250)
				errorEndFlag = true;

			if (errorEndFlag)
			{
				ConnectError = ERROR_NONE;
				FocusWndFlag = FALSE;
				ConnectErrorCount = 0;
			}


			if (errorEndFlag && HoCommandLineFlag
				&& CurrentWorkState == STATE_LOGIN_INPUT
				&& NextWorkState == STATE_LOGIN_INPUT)
			{

				HoCommandLineFlag = FALSE;
				NextWorkState = STATE_LOGIN_INPUT;
				CurrentWorkState = STATE_OPENING;
				ConnectServerSucessFlag = FALSE;
				DisconnectServerFull();
			}
		}
		ConnectErrorCount++;
	}



	MainFade();


	if (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_OPENING)
	{
		if (CinemaFadeState == STATE_FADE_OUT)
			NextWorkState = STATE_LOGIN_INPUT;


	}


	if (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT)
	{
		if (FadeNextState == FADE_IN)
		{
			LogoBlendValue += 1;
			if (LogoBlendValue >= 255)
				LogoBlendValue = 255;

			if (LogoBlendValue >= 255)
			{

				if (HoCommandLineFlag)
				{
					CurrentWorkState = STATE_LOGIN_INPUT;
					LoginDataServer();
				}
				else
				{
					LoginBlendValue += 1;
					if (LoginBlendValue >= 255)
					{
						LoginBlendValue = 255;
						CurrentWorkState = STATE_LOGIN_INPUT;
					}
				}
			}
		}
	}









	if (CurrentWorkState == STATE_LOGIN_INPUT
		&& NextWorkState == STATE_LOGIN_INPUT
		&& (LoginBlendValue >= 255)
		&& (ScreenBlendValue <= 0)
		&& StartConnectServerFlag == FALSE
		&& ConnectError == ERROR_NONE)
	{

		if (FocusWndFlag && hFocusWnd == NULL
			&& ConnectServerSucessFlag == FALSE
			&& ConnectError == ERROR_NONE)
		{
			LoginDataServer();
		}

		int downFlag = -1;



		if (MouseDownFlag == FALSE)
		{
			if (MouseButton[0])
			{
				if (pCursorPos.x > (startLogoX + 150) &&
					pCursorPos.y > (startLogoY + 355) &&
					pCursorPos.x < (startLogoX + 286) &&
					pCursorPos.y < (startLogoY + 385))
				{
					MouseDownFlag = TRUE;
					hFocusWnd = NULL;
				}
				else if (pCursorPos.x > (startLogoX + 314) &&
					pCursorPos.y > (startLogoY + 355) &&
					pCursorPos.x < (startLogoX + 450) &&
					pCursorPos.y < (startLogoY + 385))
				{
					MouseDownFlag = TRUE;
					PlayWav2(4 - 1);
					quit = 1;
				}
				
			}
		}
	}


	if (CurrentWorkState == STATE_SERVER_SELECT
		&& NextWorkState == STATE_SERVER_SELECT)
	{
		for (int index = 0; index < UserServerListInfoCount; index++)
		{
			if (ConnectError == ERROR_NONE && !StartConnectServerFlag)
			{

				MouseDownFlag = TRUE;
				MouseDownServerIndex = index;
				LoginGameServer(index);

			}
		}
	}



	if (StartConnectServerFlag)
	{
		if (ConnectError != ERROR_NONE)
		{
			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
		}

		if (ServerLoginError)
		{
			if (CurrentWorkState == STATE_LOGIN_INPUT
				&& NextWorkState == STATE_LOGIN_INPUT)
				DisconnectServerFull();

			if (CurrentWorkState == STATE_SERVER_SELECT
				&& NextWorkState == STATE_SERVER_SELECT)
				DisconnectServer_GameMain();

			if (ServerLoginError->WParam == 0)
				ConnectError = ERROR_CONNECT;
			else if (ServerLoginError->WParam == -1)
				ConnectError = ERROR_NO_ACCOUNT;
			else if (ServerLoginError->WParam == -2)
				ConnectError = ERROR_NO_PASSWORD;
			else if (ServerLoginError->WParam == -3)
				ConnectError = ERROR_NO_BETA_TESTER;
			else if (ServerLoginError->WParam == -4)
				ConnectError = ERROR_NO_ACCOUNT_IN;
			else if (ServerLoginError->WParam == -5)
				ConnectError = ERROR_NO_USE_DATE_OVER;
			else if (ServerLoginError->WParam == -6)
				ConnectError = ERROR_NO_USE_TIME_OVER;
			else if (ServerLoginError->WParam == -8)
				ConnectError = ERROR_DELETE_ACCOUNT_NOTIFY;
			else if (ServerLoginError->WParam == -16)
				ConnectError = ERROR_SERVER_TRAFFIC_BUSY;
			else if (ServerLoginError->WParam == -17)
				ConnectError = ERROR_SERVER_WAIT_MOMNENT;
			else if (ServerLoginError->WParam == -18)
				ConnectError = ERROR_THIRD_CONNECT;
			else if (ServerLoginError->WParam == -19)
				ConnectError = ERROR_HAN_PASSWORD;
			else if (ServerLoginError->WParam == -12)
				ConnectError = ERROR_12YEARS;
			else if (ServerLoginError->WParam == -13)
				ConnectError = ERROR_HOMEAGREE;
			else if (ServerLoginError->WParam == -23)
				ConnectError = ERROR_UNTIL_LOGINDENIED;
			else if (ServerLoginError->WParam == -24)
				ConnectError = ERROR_LOGIN_DENIED;



			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
			ServerLoginError = NULL;
		}

		ServerWaitTimeCount++;
		if (ServerWaitTimeCount >= 3000)
		{
			ServerWaitTimeCount = 0;
			ConnectError = ERROR_CONNECT;
			StartConnectServerFlag = FALSE;
			ConnectServerSucessFlag = FALSE;
		}


		if (CurrentWorkState == STATE_LOGIN_INPUT &&
			NextWorkState == STATE_LOGIN_INPUT)
		{
			if (ServerUserCharacterInfo
				&& DownServerListInfo
				&& ConnectError == ERROR_NONE
				&& GameErrorValue == 0)
			{

				StartConnectServerFlag = FALSE;
				ConnectServerSucessFlag = TRUE;
				CurrentWorkState = STATE_SERVER_SELECT;
				NextWorkState = STATE_SERVER_SELECT;
				GameErrorValue = -1;
			}
		}


		if (CurrentWorkState == STATE_SERVER_SELECT
			&& NextWorkState == STATE_SERVER_SELECT)
		{

			if (ConnectError == ERROR_NONE && GameErrorValue == 0)
			{
				StartConnectServerFlag = FALSE;
				SetFade();
				NextWorkState = STATE_END;
				GameErrorValue = -1;
			}
		}

		if (GameErrorValue != 0)
		{

			if (GameErrorValue == 1)
			{
				DisconnectServerFull();
				ConnectError = ERROR_NO_VERSION;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}


			if (GameErrorValue == 2)
			{
				if (CurrentWorkState == STATE_LOGIN_INPUT
					&& NextWorkState == STATE_LOGIN_INPUT)
					DisconnectServerFull();

				if (CurrentWorkState == STATE_SERVER_SELECT
					&& NextWorkState == STATE_SERVER_SELECT)
					DisconnectServer_GameMain();

				ConnectError = ERROR_NO_LIMIT;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}
		}
	}

	if (ConnectServerSucessFlag)
	{
		if (FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
		{
			try
			{
				File file("game.ini");

				if (file.readInt("Game", "RememberID"))
				{
					file.write("Game", "LastAccount", UserAccount);
				}
			}
			catch (FileException& e)
			{
				char buffer[100] = { 0 };
				strcpy_s(buffer, sizeof(buffer), e.what());
				Logger::getInstance()->output(LogType::Game, buffer);
			}

			SetWindowText(hTextWnd, NULL);
			SendMessage(hTextWnd, EM_SETLIMITTEXT, 80, 0);

			StopBGM();
			return 2;
		}
	}

	if (StartQuitFlag)
	{
		if (FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
			quit = 1;
	}

	return 1;
}


