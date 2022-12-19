#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#define SETTINGSHANDLER (Settings::getInstance())

class Settings
{
private:
	// Screen
	bool windowed;
	int ratio;
	int resolution;
	int width;
	int height;
	bool bAutoAdjust;
	bool bStartMaximized;

	//Graphics
	int textureQuality;
	int bpp;

	//Camera
	bool cameraInv;
	bool cameraSight;

	//Audio
	bool sound;
	int soundVolume;
	bool effects;
	int effectsVolume;

	//Game
	bool rememberID;
	bool weather;
	int networkQuality;
	bool motionBlur;
	std::string server1;
	std::string server2;
	std::string server3;
	unsigned short port;

	//Social
	bool bPartyRequest;
	bool bTradeRequest;
	bool bWhisper;

	//Personalization
	bool bDamageDebug;
	bool bHpBar;
	bool bFps;

	//Macro
	std::string macros[10];

	bool bLoaded = false;


public:
	Settings();
	~Settings();

	bool getWindowMode() const { return windowed; }
	void setWindowMode(bool value) { windowed = value; }

	int getTextureQuality() const { return textureQuality; }
	void setTextureQuality(int value) { textureQuality = value; }

	int getBitDepth() const { return bpp; }
	void setBitDepth(int value) { bpp = value; }

	int getNetworkQuality() const { return networkQuality; }
	void setNetworkQuality(int value) { networkQuality = value; }

	bool getCamInv() const { return cameraInv; }
	void setCamInv(bool value) { cameraInv = value; }

	bool isMotionBlur() const { return motionBlur; }
	void setMotionBlur(bool value) { motionBlur = value; }

	bool getSight() const { return cameraSight; }
	void setSight(bool value) { cameraSight = value; }

	int getWidth() const { return width; }
	void setWidth(int value) { width = value; }

	int getHeight() const { return height; }
	void setHeight(int value) { height = value; }

	int getRatio() const { return ratio; }
	void setRatio(int value) { ratio = value; }

	int getResolution() const { return resolution; }
	void setResolution(int iResolution);

	bool isWideScreen() const;

	bool hasSound() const { return sound; }
	void setSound(bool value) { sound = value; }
	int getSoundVolume() const { return (hasSound() ? soundVolume : 0); }
	void setSoundVolume(int value) { soundVolume = value; }

	bool hasEffects() const { return effects; }
	void setEffects(bool value) { effects = value; }
	int getEffectsVolume() const { return effectsVolume; }
	void setEffectsVolume(int value) { effectsVolume = value; }

	bool getWeather() const { return weather; }
	void setWheater(bool value) { weather = value; }

	bool getRememberID() const { return rememberID; }
	void setRememberID(bool value) { rememberID = value; }

	bool getAutoAdjust() const { return bAutoAdjust; }
	void setAutoAdjust(bool adjust) { bAutoAdjust = adjust; }

	bool getStartMaximized() const { return bStartMaximized; }
	void setStartMaximized(bool flag) { bStartMaximized = flag; }

	std::string getServer1() const { return server1; }
	void setServer1(std::string value) { server1 = value; }

	std::string getServer2() const { return server2; }
	void setServer2(std::string value) { server2 = value; }

	std::string getServer3() const { return server3; }
	void setServer3(std::string value) { server3 = value; }

	unsigned short getPort() const { return port; }
	void setPort(unsigned short value) { port = value; }

	bool getPartyRequest() const { return bPartyRequest; }
	void setPartyRequest(bool value) { bPartyRequest = value; }

	bool getTradeRequest() const { return bTradeRequest; }
	void setTradeRequest(bool value) { bTradeRequest = value; }

	bool getWhisper() const { return bWhisper; }
	void setWhisper(bool value) { bWhisper = value; }

	bool getDamageDebug() const { return bDamageDebug; }
	void setDamageDebug(bool value) { bDamageDebug = value; }

	bool getHpBar() const { return bHpBar; }
	void setHpBar(bool value) { bHpBar = value; }

	bool getFps() const { return bFps; }
	void setFps(bool value) { bFps = value; }

	std::string getMacro(unsigned short index) const;
	void setMacro(unsigned short index, std::string macro);

	void readConfig();
	bool save();

	void resizeWindow(int iWidth, int iHeight);

	static Settings* getInstance(bool temp = false);
};


#endif // SETTINGS_H