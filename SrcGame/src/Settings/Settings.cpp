#include "Settings/Settings.h"
#include "File\File.h"
#include "CLootHandler.h"
#include "sinbaram/sinLinkHeader.h"
#include "Log/Logger.h"

Settings settings;
Settings settings_temp;

extern char	szShotCutMessage[10][100];
extern void LeIniStr(char *Section, char *Key, char *szFileIni, char *Var1);
extern void resizeOpening();
extern void resizeLogin();
extern float g_fWinSizeRatio_X;
extern float g_fWinSizeRatio_Y;

int Resolutions43[][2] = {
	{800, 600},
	{1024, 768},
	{1280, 960},
	{1400, 1050},
};

int Resolutions169[][2] = {
	{1280, 720},
	{1366, 768},
	{1600, 900},
	{1920, 1080},
};

Settings::Settings()
{
	windowed = false;
	textureQuality = 0;
	bpp = 0;
	networkQuality = 0;
	cameraInv = false;
	motionBlur = false;
	cameraSight = false;
	width = 0;
	height = 0;
	resolution = 0;
	sound = false;
	weather = false;
	server1 = "127.0.0.1";
	server2 = "127.0.0.1";
	server3 = "127.0.0.1";
	port = 0;

	rememberID = false;
}

Settings::~Settings()
{
}

void Settings::readConfig()
{
	try
	{
		File file("game.ini");
		File fileIP("game.ini");

		setWindowMode(file.readInt("Screen", "Windowed") != 0);

		setRatio(file.readInt("Screen", "Ratio"));
		setResolution(file.readInt("Screen", "Resolution"));

		setAutoAdjust(file.readInt("Screen", "AutoAdjust") != 0);
		setStartMaximized(file.readInt("Screen", "StartMaximized") != 0);


		setTextureQuality(file.readInt("Graphics", "TextureQuality"));
		setBitDepth(file.readInt("Graphics", "BitDepth"));

		setSight(file.readInt("Camera", "Range") != 0);
		setCamInv(file.readInt("Camera", "Inverted") != 0);

		setSound(file.readInt("Audio", "Music") != 0);
		setSoundVolume(file.readInt("Audio", "MusicVolume"));
		setEffects(file.readInt("Audio", "Effects") != 0);
		setEffectsVolume(file.readInt("Audio", "EffectsVolume"));

		setServer1(fileIP.readString("Game", "IP"));
		setServer2(fileIP.readString("Game", "IP"));
		setServer3(fileIP.readString("Game", "IP"));
		setPort(8000);
		setWheater(file.readInt("Game", "Weather") != 0);
		setRememberID(file.readInt("Game", "RememberID") != 0);

		setPartyRequest(file.readInt("Social", "PartyRequest") != 0);
		setTradeRequest(file.readInt("Social", "TradeRequest") != 0);
		setWhisper(file.readInt("Social", "Whisper") != 0);

		setDamageDebug(file.readInt("Personalization", "DamageDebug") != 0);
		setHpBar(file.readInt("Personalization", "HpBar") != 0);
		setFps(file.readInt("Personalization", "FPS") != 0);

		cLootFilter.setEnabled(file.readInt("LootFilter", "Enable") != 0);
		cLootFilter.setHpPot(file.readInt("LootFilter", "HpPot") != 0);
		cLootFilter.setMpPot(file.readInt("LootFilter", "MpPot") != 0);
		cLootFilter.setSpPot(file.readInt("LootFilter", "SpPot") != 0);
		cLootFilter.setGold(file.readInt("LootFilter", "Gold") != 0);
		cLootFilter.setAmulets(file.readInt("LootFilter", "Amulets") != 0);
		cLootFilter.setRings(file.readInt("LootFilter", "Rings") != 0);
		cLootFilter.setSheltoms(file.readInt("LootFilter", "Sheltoms") != 0);
		cLootFilter.setForce(file.readInt("LootFilter", "Force") != 0);
		cLootFilter.setPremiums(file.readInt("LootFilter", "Premiums") != 0);
		cLootFilter.setCrystals(file.readInt("LootFilter", "Crystals") != 0);
		cLootFilter.setDefense(file.readInt("LootFilter", "Defense") != 0);
		cLootFilter.setOffense(file.readInt("LootFilter", "Offense") != 0);
		cLootFilter.setEverything(file.readInt("LootFilter", "Everything") != 0);
		cLootFilter.setNonSpec(file.readInt("LootFilter", "NS") != 0);
		cLootFilter.setFighter(file.readInt("LootFilter", "Fighter") != 0);
		cLootFilter.setMech(file.readInt("LootFilter", "Mech") != 0);
		cLootFilter.setArcher(file.readInt("LootFilter", "Archer") != 0);
		cLootFilter.setPikeman(file.readInt("LootFilter", "Pikeman") != 0);
		cLootFilter.setAtalanta(file.readInt("LootFilter", "Atalanta") != 0);
		cLootFilter.setKnight(file.readInt("LootFilter", "Knight") != 0);
		cLootFilter.setMagician(file.readInt("LootFilter", "Magician") != 0);
		cLootFilter.setPriestess(file.readInt("LootFilter", "Priestess") != 0);

		for (unsigned short i = 1; i < 10; i++)
			setMacro(i, file.readString("Macro", "Macro" + std::to_string(i)));

		bLoaded = true;
	}

	catch(FileException &e)
	{
		Logger::getInstance()->output(LogType::Error, const_cast<char*>(e.what()));
	}
}

bool Settings::save()
{
	try
	{
		File file("game.ini");

		//Screen
		file.write("Screen", "Windowed", getWindowMode() ? 1 : 0);
		file.write("Screen", "Ratio", getRatio());
		file.write("Screen", "Resolution", getResolution());
		file.write("Screen", "AutoAdjust", getAutoAdjust() ? 1 : 0);
		file.write("Screen", "StartMaximized", getStartMaximized() ? 1 : 0);

		//Graphics
		file.write("Graphics", "TextureQuality", getTextureQuality());
		file.write("Graphics", "BitDepth", getBitDepth());

		//Camera
		file.write("Camera", "Range", getSight() ? 1  : 0);
		file.write("Camera", "Inverted", getCamInv() ? 1  : 0);

		//Audio
		file.write("Audio", "Music", hasSound() ? 1  : 0);
		file.write("Audio", "MusicVolume", getSoundVolume());
		file.write("Audio", "Effects", hasEffects() ? 1 : 0);
		file.write("Audio", "EffectsVolume", getEffectsVolume());

		//Game
		file.write("Game", "RememberID", getRememberID() ? 1 : 0);
		file.write("Game", "Weather", getWeather() ? 1 : 0);

		//Social
		file.write("Social", "PartyRequest", getPartyRequest() ? 1 : 0);
		file.write("Social", "TradeRequest", getTradeRequest() ? 1 : 0);
		file.write("Social", "Whisper", getWhisper() ? 1 : 0);

		//Personalization
		file.write("Personalization", "DamageDebug", getDamageDebug() ? 1 : 0);
		file.write("Personalization", "HpBar", getHpBar() ? 1 : 0);
		file.write("Personalization", "FPS", getFps() ? 1 : 0);

		//Loot Filter
		file.write("LootFilter", "Enable", cLootFilter.getEnabled() ? 1 : 0);
		file.write("LootFilter", "HPPot", cLootFilter.getHpPot() ? 1 : 0);
		file.write("LootFilter", "MPPot", cLootFilter.getMpPot() ? 1 : 0);
		file.write("LootFilter", "SPPot", cLootFilter.getSpPot() ? 1 : 0);
		file.write("LootFilter", "Gold", cLootFilter.getGold() ? 1 : 0);
		file.write("LootFilter", "Amulets", cLootFilter.getAmulets() ? 1 : 0);
		file.write("LootFilter", "Rings", cLootFilter.getRings() ? 1 : 0);
		file.write("LootFilter", "Sheltoms", cLootFilter.getSheltoms() ? 1 : 0);
		file.write("LootFilter", "Force", cLootFilter.getForce() ? 1 : 0);
		file.write("LootFilter", "Premiums", cLootFilter.getPremiums() ? 1 : 0);
		file.write("LootFilter", "Crystals", cLootFilter.getCrystals() ? 1 : 0);
		file.write("LootFilter", "Defense", cLootFilter.getDefense() ? 1 : 0);
		file.write("LootFilter", "Offense", cLootFilter.getOffense() ? 1 : 0);
		file.write("LootFilter", "Everything", cLootFilter.getEverything() ? 1 : 0);
		file.write("LootFilter", "NS", cLootFilter.getNonSpec() ? 1 : 0);
		file.write("LootFilter", "Fighter", cLootFilter.getFighter() ? 1 : 0);
		file.write("LootFilter", "Mech", cLootFilter.getMech() ? 1 : 0);
		file.write("LootFilter", "Archer", cLootFilter.getArcher() ? 1 : 0);
		file.write("LootFilter", "Pikeman", cLootFilter.getPikeman() ? 1 : 0);
		file.write("LootFilter", "Atalanta", cLootFilter.getAtalanta() ? 1 : 0);
		file.write("LootFilter", "Knight", cLootFilter.getKnight() ? 1 : 0);
		file.write("LootFilter", "Magician", cLootFilter.getMagician() ? 1 : 0);
		file.write("LootFilter", "Priestess", cLootFilter.getPriestess() ? 1 : 0);

		//Macro
		for (int i = 0; i < 9; i++)
		{
			file.write("Macro", "Macro" + std::to_string(i + 1), getMacro(i));
		}
		return true;
	}
	catch(FileException &e)
	{
		MessageBox(NULL, e.what(), "Error saving configs", MB_ICONERROR);
	}

	return false;
}

void Settings::resizeWindow(int iWidth, int iHeight)
{
	WinSizeX = iWidth;
	WinSizeY = iHeight;

	RECT wrect;
	wrect.left = 0;
	wrect.top = 0;
	wrect.right = SETTINGSHANDLER->getWidth();
	wrect.bottom = SETTINGSHANDLER->getHeight();

	AdjustWindowRectEx(&wrect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE, 0);

	int wx = wrect.right - wrect.left;
	int wy = wrect.bottom - wrect.top;

	SetWindowPos(hwnd, 0, (GetSystemMetrics(SM_CXSCREEN) - wx) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - wy) / 2, wx, wy, SWP_SHOWWINDOW);
}

Settings* Settings::getInstance(bool temp)
{
	if(temp)
		return &settings_temp;
	else
		return &settings;
}

void Settings::setResolution(int iResolution)
{
	resolution = iResolution;

	if (getRatio() == 43)
	{
		setWidth(Resolutions43[iResolution - 1][0]);
		setHeight(Resolutions43[iResolution - 1][1]);
	}
	else
	{
		setWidth(Resolutions169[iResolution - 1][0]);
		setHeight(Resolutions169[iResolution - 1][1]);
	}

	if ((getWidth() != WinSizeX || getHeight() != WinSizeY) && bLoaded)
		resizeWindow(getWidth(), getHeight());
}
bool Settings::isWideScreen() const
{
	//return ((width * 3) != (height * 4));
	return ((width / 4) != (height / 3));
}

std::string Settings::getMacro(unsigned short index) const
{
	if(index >= 0 || index < 10)
		return szShotCutMessage[index];
	else
		return std::string();
}

void Settings::setMacro(unsigned short index, std::string macro)
{
	lstrcpy(szShotCutMessage[index%10], macro.c_str());
}
