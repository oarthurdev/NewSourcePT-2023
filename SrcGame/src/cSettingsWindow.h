#pragma once

#include "UILinkerOld.h"

enum OBJID
{
	OBJID_None,

	OBJID_ONBox,
	OBJID_OFFBox,

	OBJID_Main,
	OBJID_Close,
	OBJID_Save,
	OBJID_Reset,
	OBJID_TabList,
	OBJID_TabAudio,
	OBJID_TabGeneral,
	OBJID_TabUI,

	OBJID_TabVideo,
	OBJID_WindowVideo,
	OBJID_ScreenList,
	OBJID_AutoAdjust,
	OBJID_StartMaximized,
	OBJID_RatioList,
	OBJID_ResolutionList,
	OBJID_TextureList,
	OBJID_BitList,
	OBJID_CameraList,
	OBJID_InvertedList,

	OBJID_WindowAudio,
	OBJID_MusicController,
	OBJID_EffectsController,
	OBJID_Mute,
	OBJID_Volume,

	OBJID_WindowGeneral,
	OBJID_PartyRequest,
	OBJID_TradeRequest,
	OBJID_Whisper,
	OBJID_DamageList,
	OBJID_HPList,
	OBJID_FPSList,
	OBJID_LootFilter,
	OBJID_HPPotion,
	OBJID_MPPotion,
	OBJID_SPPotion,
	OBJID_Gold,
	OBJID_Amulets,
	OBJID_Rings,
	OBJID_Sheltoms,
	OBJID_Force,
	OBJID_Premiums,
	OBJID_NonSpec,
	OBJID_Fighter,
	OBJID_Mechanician,
	OBJID_Archer,
	OBJID_Pikeman,
	OBJID_Atalanta,
	OBJID_Knight,
	OBJID_Magician,
	OBJID_Priestess,
	OBJID_Defense,
	OBJID_Offense,
	OBJID_Everything,
	OBJID_Crystals,
	OBJID_Macro1,
	OBJID_Macro2,
	OBJID_Macro3,
	OBJID_Macro4,
	OBJID_Macro5,
	OBJID_Macro6,
	OBJID_Macro7,
	OBJID_Macro8,
	OBJID_Macro9,
};

class cSettingsWindow
{
public:
	~cSettingsWindow();

	void Init();
	void Draw();
	bool LButtonDown();
	bool LButtonUp();
	void OnMouseMove();
	void OnMouseScroll(int zDelta);
	void OnKeyDown(char Code);

	void Open();
	void Close();

	bool isOpen() { return ((pWindow1 && pWindow1->isVisible()) ? true : false); }

protected:
	void BuildWindow1();
	void BuildWindowVideo();
	void BuildWindowAudio();
	void BuildWindowGeneral();

private:
	UIWindowOld* pWindow1;

	int BaseX, BaseY;

	void LoadSettings();
	void ResetSettings();
	void SaveSettings();
};

extern cSettingsWindow cSettings;