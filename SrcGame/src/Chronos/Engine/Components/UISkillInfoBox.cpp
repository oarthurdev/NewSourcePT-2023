
#include "UISkillInfoBox.h"

int iaUpgradeSkillCost[20];
int iaUpgradeSkillCostPlus[20];

namespace UI
{
	SkillInfoBox::SkillInfoBox()
	{
		iSkillInfoBoxHeight = 0;
	}

	SkillInfoBox::~SkillInfoBox()
	{
	}

	BOOL SkillInfoBox::IsActiveSkill(ESkillID eSkillID)
	{
		switch (eSkillID)
		{
			//Fighter
		case SKILLID_Raving:
		case SKILLID_Impact:
		case SKILLID_TripleImpact:
		case SKILLID_BrutalSwing:
		case SKILLID_RageofZecram:
		case SKILLID_AvengingCrash:
		case SKILLID_BoneCrash:
		case SKILLID_Destroyer:
		case SKILLID_CycloneStrike:
		case SKILLID_SeismicImpact:
		case SKILLID_Whirlwind:

			//Mechanician
		case SKILLID_MechanicBomb:
		case SKILLID_GreatSmash:
		case SKILLID_Spark:
		case SKILLID_GrandSmash:
		case SKILLID_Impulsion:
		case SKILLID_Rupture:
		case SKILLID_MagneticDischarge:

			//Archer
		case SKILLID_WindArrow:
		case SKILLID_PerfectAim:
		case SKILLID_ArrowofRage:
		case SKILLID_Avalanche:
		case SKILLID_ElementalShot:
		case SKILLID_BombShot:
		case SKILLID_Perforation:
		case SKILLID_PhoenixShot:
		case SKILLID_FierceWind:
		case SKILLID_Bombardment:

			//Pikeman 
		case SKILLID_PikeWind:
		case SKILLID_CriticalHit:
		case SKILLID_JumpingCrash:
		case SKILLID_Tornado:
		case SKILLID_Expansion:
		case SKILLID_ChainLance:
		case SKILLID_ChargingStrike:
		case SKILLID_ShadowMaster:

			//Atalanta 
		case SKILLID_BiggerSpear:
		case SKILLID_TwistJavelin:
		case SKILLID_FireJavelin:
		case SKILLID_SplitJavelin:
		case SKILLID_LightningJavelin:
		case SKILLID_StormJavelin:
		case SKILLID_ExtremeRage:
		case SKILLID_Vengeance:
		case SKILLID_ComboJavelin:

			//Knight 
		case SKILLID_SwordBlast:
		case SKILLID_DoubleCrash:
		case SKILLID_Brandish:
		case SKILLID_Piercing:
		case SKILLID_GrandCross:
		case SKILLID_SwordofJustice:
		case SKILLID_DivinePiercing:
		case SKILLID_DivineCross:
		case SKILLID_DivineInquisiton:

			//Magician 
		case SKILLID_Agony:
		case SKILLID_FireBolt:
		case SKILLID_FireBall:
		case SKILLID_Watornado:
		case SKILLID_DeathRay:
		case SKILLID_Diastrophism:
		case SKILLID_FlameWave:
		case SKILLID_Meteorite:
		case SKILLID_StoneSkin:
		case SKILLID_RedRay:
		case SKILLID_Cataclysm:

			//Priestess 
		case SKILLID_Healing:
		case SKILLID_HolyBolt:
		case SKILLID_MultiSpark:
		case SKILLID_DivineLightning:
		case SKILLID_GrandHealing:
		case SKILLID_VigorBall:
		case SKILLID_Ressurection:
		case SKILLID_GlacialSpike:
		case SKILLID_ChainLightning:
		case SKILLID_LightningSurge:
		case SKILLID_HeavenlyLight:

			//Assassin 
		case SKILLID_Stinger:
		case SKILLID_RunningHit:
		case SKILLID_VenomThorn:
		case SKILLID_SoreBlade:
		case SKILLID_GustSlash:
		case SKILLID_FrostWind:
		case SKILLID_NinjaShadow:
		case SKILLID_ShadowBlink:

			//Shaman 
		case SKILLID_DarkBolt:
		case SKILLID_DarkWave:
		case SKILLID_SpiritualFlare:
		case SKILLID_PhantomCall:
		case SKILLID_Scratch:
		case SKILLID_Judgement:
		case SKILLID_MourningPray:
		case SKILLID_PressDeity:
		case SKILLID_PhantomNail:
			return TRUE;
		}

		return FALSE;
	}

	BOOL SkillInfoBox::IsPassiveSkill(ESkillID eSkillID)
	{
		switch (eSkillID)
		{
			//Fighter
		case SKILLID_MeleeMastery:
		case SKILLID_FireAttribute:
		case SKILLID_BoostHealth:
		case SKILLID_SurvivalInstinct:

			//Mechanician
		case SKILLID_PoisonAttribute:
		case SKILLID_MechanicWeaponMastery:

			//Archer
		case SKILLID_ShootingMastery:
		case SKILLID_DionsEye:
		case SKILLID_EvasionMastery:

			//Pikeman 
		case SKILLID_IceAttribute:
		case SKILLID_WeaponDefenseMastery:
		case SKILLID_CriticalMastery:

			//Atalanta 
		case SKILLID_ThrowingMaster:
		case SKILLID_GoldenApple:

			//Knight 
		case SKILLID_PhysicalTraining:
		case SKILLID_SwordMastery:

			//Magician 
		case SKILLID_MetalMastery:

			//Priestess 
		case SKILLID_Meditation:

			//Assassin 
		case SKILLID_DualWieldMastery:
		case SKILLID_AttackMastery:
		case SKILLID_FatalMastery:

			//Shaman 
		case SKILLID_InnerPeace:
		case SKILLID_OccultLife:
			return TRUE;
		}

		return FALSE;
	}

	BOOL SkillInfoBox::IsDebuffSkill(ESkillID eSkillID)
	{
		switch (eSkillID)
		{
			//Fighter
		case SKILLID_Roar:

			//Mechanician
		case SKILLID_ParasitShot:

			//Archer
		case SKILLID_EntalingRoots:

			//Pikeman 
		case SKILLID_GroundPike:
		case SKILLID_VenomSpear:
		case SKILLID_AssassinsEye:
		case SKILLID_RingofSpears:

			//Atalanta 
		case SKILLID_ShieldStrike:
		case SKILLID_SoulSucker:
		case SKILLID_PlagueJavelin:

		case SKILLID_Distortion:

			//Priestess 
		case SKILLID_HolyMind:
		case SKILLID_Extinction:

			//Assassin 
		case SKILLID_Wisp:
		case SKILLID_SoulShock:
		case SKILLID_Polluted:

			//Shaman 
		case SKILLID_Inertia:
		case SKILLID_SpiritualManacle:
		case SKILLID_Haunt:
			return TRUE;
		}

		return FALSE;
	}

	BOOL SkillInfoBox::IsBuffSkill(ESkillID eSkillID)
	{
		switch (eSkillID)
		{
			//Fighter
		case SKILLID_Concentration:
		case SKILLID_SwiftAxe:
		case SKILLID_Berserker:
		case SKILLID_RuthlessofZecram:

			//Mechanician
		case SKILLID_ExtremeShield:
		case SKILLID_PhysicalAbsorb:
		case SKILLID_Maximize:
		case SKILLID_Automation:
		case SKILLID_MetalArmor:
		case SKILLID_SparkShield:
		case SKILLID_Compulsion:
		case SKILLID_MagneticSphere:
		case SKILLID_HardeningShield:

			//Archer
		case SKILLID_ScoutHawk:
		case SKILLID_Falcon:
		case SKILLID_GoldenFalcon:
		case SKILLID_ForceofNature:
		case SKILLID_LethalSight:

			//Pikeman 
		case SKILLID_Vanish:
		case SKILLID_Vague:

			//Atalanta 
		case SKILLID_Farina:
		case SKILLID_Windy:
		case SKILLID_TriumphofJavelin:
		case SKILLID_HallofValhalla:
		case SKILLID_FrostJavelin:

			//Knight 
		case SKILLID_HolyBody:
		case SKILLID_HolyValor:
		case SKILLID_DrasticSpirit:
		case SKILLID_DivineShield:
		case SKILLID_HolyIncantation:
		case SKILLID_GodlyShield:
		case SKILLID_GodsBlessing:
		case SKILLID_GloriousShield:
		case SKILLID_HolyConviction:

			//Magician 
		case SKILLID_Zenith:
		case SKILLID_EnchantWeapon:
		case SKILLID_EnergyShield:
		case SKILLID_SpiritElemental:
		case SKILLID_DancingSword:
		case SKILLID_WizardTrance:

			//Priestess 
		case SKILLID_HolyReflection:
		case SKILLID_VirtualLife:
		case SKILLID_RegenerationField:
		case SKILLID_SummonMuspell:
		case SKILLID_Consecration:

			//Assassin 
		case SKILLID_Alas:
		case SKILLID_Inpes:
		case SKILLID_Blind:

			//Shaman 
		case SKILLID_ChasingHunt:
		case SKILLID_AdventMigal:
		case SKILLID_Rainmaker:
		case SKILLID_AdventMidranda:
		case SKILLID_Creed:
			return TRUE;
		}

		return FALSE;
	}

	BOOL SkillInfoBox::IsSummonSkill(ESkillID eSkillID)
	{
		switch (eSkillID)
		{
			//Mechanician
		case SKILLID_MetalGolem:

			//Archer
		case SKILLID_RecallWolverine:

			//Atalanta
		case SKILLID_SummonTiger:

			//Priestess
		case SKILLID_IceElemental:

			//Magician
		case SKILLID_FireElemental:

			//Shaman
		case SKILLID_RecallHestian:
			return TRUE;
			break;
		}
		return FALSE;
	}

	BOOL SkillInfoBox::CanPrepareShowSkill(Skill* psSkill, Rectangle2D sBox)
	{
		BOOL bRet = TRUE;

		if (cSkillWrapper.sSkillInfo.eSkillID == psSkill->sSkillInfo.eSkillID)
			bRet = FALSE;

		if (!bRet)
		{
			if (cSkillWrapper.iLevel != psSkill->iLevel)
				bRet = TRUE;

			if (!sSkillBox.Equals(&sBox))
				bRet = TRUE;
		}

		return bRet;
	}

	void SkillInfoBox::AddString(int iSide, const std::string& strString, DWORD dwColor, BOOL bBold)
	{
		//Find breakline in String 
		BOOL bMultiLine = FALSE;
		if (strString.find('\n') != std::string::npos)
			bMultiLine = TRUE;

		switch (iSide)
		{
		case 0: //Left Side
		 //Is Multiline?
			if (bMultiLine)
			{
				size_t n = std::count(strString.begin(), strString.end(), '\n');
				iSkillInfoBoxHeight += 14 * n;
			}
			else
			{
				UI::Text_ptr pText = std::make_shared<Text>(strString, Rectangle2D(14, iSkillInfoBoxHeight, 208, 0), bBold, dwColor);
				pText->SetText(trim((std::string)strString));
				pText->SetMultiLine(TRUE);
				pText->SetWordWrap(TRUE);
				iSkillInfoBoxHeight += pText->GetHeightText();
				vLeftText.push_back(pText);
			}
			break;
		case 1: //Right Side
		{
			UI::Text_ptr pText = std::make_shared<Text>(strString, Rectangle2D(14 + vLeftText[vLeftText.size() - 1]->GetTextWidth() + 6, iSkillInfoBoxHeight - vLeftText[vLeftText.size() - 1]->GetHeightText(), 208, 20), bBold, dwColor);
			pText->SetText(trim((std::string)strString));
			pText->SetMultiLine(TRUE);
			pText->SetWordWrap(TRUE);
			vRightText.push_back(pText);
			break;
		}
		case 2:
		{
			UINT uIndex = uSkillStatusPos + vCompareText.size();

			if ((uIndex < vLeftText.size()) && (uIndex < vRightText.size()))
			{
				UI::Text_ptr pText = std::make_shared<Text>(strString, Rectangle2D(vLeftText[uIndex]->GetTextWidth() + vRightText[uIndex]->GetTextWidth() + 24, vLeftText[uIndex]->GetY(), 208, 0), bBold, dwColor);
				pText->SetText(trim((std::string)strString));
				pText->SetMultiLine(TRUE);
				pText->SetWordWrap(TRUE);
				vCompareText.push_back(pText);
			}
			break;
		}
		}
	}

	void SkillInfoBox::SetLineColor(DWORD dwColor, int iSide, int iLineCount)
	{
		int iSetColor = 0;
		if (iLineCount < 0)
			iSetColor = vLeftText.size() - 1;
		else
			iSetColor = iLineCount;

		switch (iSide)
		{
		case -1:
			vLeftText[iSetColor]->SetColor(dwColor);
			vRightText[iSetColor]->SetColor(dwColor);
			break;
		case 0:
			vLeftText[iSetColor]->SetColor(dwColor);
			break;
		case 1:
			vRightText[iSetColor]->SetColor(dwColor);
			break;
		}
	}

	void SkillInfoBox::Init()
	{
		//Load Images
		pImageMaskLeftTop = ImageLoader::LoadImage("game\\images\\UI\\box\\mask\\topleft.png");
		pImageMaskRightTop = ImageLoader::LoadImage("game\\images\\UI\\box\\mask\\topright.png");
		pImageMaskLeftBottom = ImageLoader::LoadImage("game\\images\\UI\\box\\mask\\bottomleft.png");
		pImageMaskRightBottom = ImageLoader::LoadImage("game\\images\\UI\\box\\mask\\bottomright.png");

		//Load Border Images
		pImageBorderLeftTop = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\topleft.png");
		pImageBorderRightTop = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\topright.png");
		pImageBorderTop = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\top.png");
		pImageBorderRightBottom = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\bottomright.png");
		pImageBorderLeftBottom = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\bottomleft.png");
		pImageBorderBottom = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\bottom.png");
		pImageBorderLeft = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\left.png");
		pImageBorderRight = ImageLoader::LoadImage("game\\images\\UI\\box\\border\\right.png");

		pRenderTargetMask = GetGraphicsDevice()->MakeRenderTarget(5001, 600, 600);
		pEffectMask = GetGraphicsDevice()->GetEffectFactory()->MakeEffect("game\\scripts\\shaders\\UI\\InfoBox.fx");

		for (int i = 0; i < 12; i++)
		{
			pImageIconItems[i] = ImageLoader::LoadImage("image\\Sinimage\\skill\\WeaponIcon\\%d.bmp", i + 1);
		}
	}

	void SkillInfoBox::FormatSkillInfo()
	{
		BOOL bUpdateSkill = FALSE;

		//Tier 5 Skills? So format skill info here
		if ((cSkillWrapper.iID & 0x00FF0000) == 0x00100000)
			bUpdateSkill = TRUE;

		uSkillStatusPos = vLeftText.size();
		UINT uSkillLevel = cSkillWrapper.iLevel - 1;

		if (cSkillWrapper.iLevel == 0)
			uSkillLevel = 0;

		switch (cSkillWrapper.iID)
		{
		case SKILLID_Automation:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT23DamageBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Add Attack Speed:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMechT23AtkSpeed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%.1f", faMechT23MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%.1f", faMechT23SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMechT23DamageBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMechT23AtkSpeed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%.1f)", faMechT23MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%.1f)", faMechT23SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}

			bUpdateSkill = TRUE;
			break;
		case SKILLID_GreatSmash:
			AddString(0, "Damage:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT21Damage[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMechT21Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMechT21Damage[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMechT21Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}

			bUpdateSkill = TRUE;
			break;
		case SKILLID_Rupture:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaMechT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_ParasitShot:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Poison Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMechT52PoisonTimeDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMechT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMechT52PoisonTimeDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_HardeningShield:
			AddString(0, "Damage Reduction:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT53DMGReduction[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "WP ATK Rate Reduction:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT53WPAtkRateRed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMechT53DMGReduction[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaMechT53WPAtkRateRed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_MagneticDischarge:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMechT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaMechT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_RageofZecram:
			AddString(0, "DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT24DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT24Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaFighterT24DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT24Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_SurvivalInstinct:
			AddString(0, "Add HP Regen:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%.1f", faFighterT51AddHPRegen[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Add HP Potion Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT51AddHPPotionBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Add HP Boost Health:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT51BoostHealthBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%.1f)", faFighterT51AddHPRegen[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaFighterT51AddHPPotionBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaFighterT51BoostHealthBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_SeismicImpact:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT52Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaFighterT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT52Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_RuthlessofZecram:
			AddString(0, "HP Decrease:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%.1f%%", faFighterT53HPDec[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Hits for boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT53HitsBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Final DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%.1f%%)", faFighterT53HPDec[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT53HitsBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaFighterT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_Whirlwind:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaFighterT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT54Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT54MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaFighterT54SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaFighterT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT54Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT54MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaFighterT54SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_RingofSpears:
			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", iaPikeT51Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%dsec)", iaPikeT51Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_Focus:
			AddString(0, "Min ATK Reduced:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPikeT52MinATKRed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Max ATK Increased:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPikeT52MaxATKInc[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d)", iaPikeT52MinATKRed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPikeT52MaxATKInc[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_DeathMaster:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPikeT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "WP ATK Rate Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPikeT53ATKRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaPikeT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaPikeT53ATKRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_Twister:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPikeT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaPikeT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_LethalSight:
			AddString(0, "Range Add:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaArcherT51RangeAdd[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Critical Rate:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaArcherT51CritRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "After Damage:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaArcherT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d)", iaArcherT51RangeAdd[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaArcherT51CritRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaArcherT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_FierceWind:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaArcherT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Critical DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaArcherT52CDMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaArcherT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaArcherT52CDMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_EntalingRoots:
			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaArcherT53Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d)", iaArcherT53Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_Bombardment:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaArcherT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaArcherT54Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaArcherT54MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaArcherT54SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaArcherT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaArcherT54Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaArcherT54MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaArcherT54SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_HolyConviction:
			AddString(0, "Undead DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaKnightT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaKnightT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_DivineInquisiton:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaKnightT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaKnightT52Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Undead Damage:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaKnightT52UndeadDMG[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaKnightT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaKnightT52Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaKnightT52UndeadDMG[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_GloriousShield:
			AddString(0, "Shield Def Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaKnightT53DefBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaKnightT53DefBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_DivineCross:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaKnightT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
				AddString(2, FormatString("(%d%%)", iaKnightT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			break;
		case SKILLID_SummonTiger:
			AddString(0, "Pet Settings:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%s", SKILLMANAGERHANDLER->IsAgressive(SKILLID_SummonTiger) ? "Automatic" : "Manual"), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d-%d", iaSummonTigerAttackPower[uSkillLevel], iaSummonTigerAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaSummonTigerAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "HP:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaSummonTigerHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", 300), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString(""), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d-%d)", iaSummonTigerAttackPower[uSkillLevel + 1], iaSummonTigerAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaSummonTigerAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaSummonTigerHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%dsec)", 300), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_PlagueJavelin:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaAtaT51DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Targets:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaAtaT51Targets[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Poison Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaAtaT51PoisonDuration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaAtaT51DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaAtaT51Targets[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaAtaT51PoisonDuration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_GoldenApple:
			AddString(0, "Speed:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaAtaT52Speed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Evade:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaAtaT52Evade[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaAtaT52Speed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaAtaT52Evade[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_IceElemental:
			AddString(0, "Pet Settings:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%s", SKILLMANAGERHANDLER->IsAgressive(SKILLID_IceElemental) ? "Automatic" : "Manual"), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Attack Power:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d-%d", iaIceElementalAttackPower[uSkillLevel], iaIceElementalAttackPower[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Attack Rating:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaIceElementalAttackRating[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "HP:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaIceElementalHP[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", 300), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString(""), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d-%d)", iaIceElementalAttackPower[uSkillLevel + 1], iaIceElementalAttackPower[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaIceElementalAttackRating[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaIceElementalHP[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%dsec)", 300), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_LightningSurge:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPrsT52DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPrsT52Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Charged Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPrsT52ChargedArea[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaPrsT52DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPrsT52Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPrsT52ChargedArea[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_HeavenlyLight:
			AddString(0, "ATK Rate Reduction:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPrsT53ATKRate[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPrsT53Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Charged Area:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPrsT53Area[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaPrsT53ATKRate[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPrsT53Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPrsT53Area[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_Consecration:
			AddString(0, "Defense:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaPrsT54Defense[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Absorption:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaPrsT54Absorption[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaPrsT54Defense[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaPrsT54Absorption[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_WizardTrance:
			AddString(0, "Orb Block Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMageT51BlockBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "ATK Rate Reduced:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMageT51ATKRateRed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMageT51BlockBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaMageT51ATKRateRed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_StoneSkin:
			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", iaMageT52Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Run Speed Reduction:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMageT52RunSpeedRed[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%dsec)", iaMageT52Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaMageT52RunSpeedRed[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_RedRay:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMageT53DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Add Range:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMageT53AddRange[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMageT53DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMageT53AddRange[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_Cataclysm:
			AddString(0, "Damage Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaMageT54DMGBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", iaMageT54Duration[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "MP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMageT54MPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "SP Drain:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaMageT54SPDrain[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaMageT54DMGBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%dsec)", iaMageT54Duration[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMageT54MPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaMageT54SPDrain[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_ShadowBlink:
			AddString(0, "Critical DMG Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaASNT51CritBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Range:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d", iaASNT51Range[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaASNT51CritBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d)", iaASNT51Range[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		case SKILLID_Creed:
			AddString(0, "MP Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaShaT51MPBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "STM Boost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%d%%", iaShaT51STMBoost[uSkillLevel]), D3DCOLOR_XRGB(238, 210, 151));

			AddString(0, "Duration:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%dsec", 300), D3DCOLOR_XRGB(238, 210, 151));

			if (cSkillWrapper.iLevel < 10)
			{
				AddString(2, FormatString("(%d%%)", iaShaT51MPBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%d%%)", iaShaT51STMBoost[uSkillLevel + 1]), D3DCOLOR_XRGB(92, 163, 99));
				AddString(2, FormatString("(%dsec)", 300), D3DCOLOR_XRGB(92, 163, 99));
			}
			break;
		}

		//Upgrade Cost
		if (cSkillWrapper.iLevel < 10 && READDWORD(0x367DE9C) > 0)
		{
			CopyMemory(iaUpgradeSkillCost, (char*)0x9BBE58, sizeof(int) * 20);
			CopyMemory(iaUpgradeSkillCostPlus, (char*)0x9BBEA8, sizeof(int) * 20);

			strSkillNextLevelCost = FormatString("%s gp", FormatNumber(iaUpgradeSkillCost[cSkillWrapper.sSkillInfo.iSkillIndex] + (iaUpgradeSkillCostPlus[cSkillWrapper.sSkillInfo.iSkillIndex] * (cSkillWrapper.iLevel))));
		}

		if (bUpdateSkill == FALSE)
		{
			std::string strBufferLeft = (char*)0x036762A0;
			std::string strBufferRight = (char*)0x03677628;

			std::vector<std::string> vStringLeft;
			vStringLeft = split(strBufferLeft, '\r');

			std::vector<std::string> vStringRight;
			vStringRight = split(strBufferRight, '\r');

			for (size_t i = 0; i < vStringLeft.size(); i++)
			{
				if (vStringLeft[i].empty())
				{
					vStringLeft[i].erase();
					vStringRight[i].erase();
				}
			}

			bool bNextLevel = false;
			for (size_t i = 0; i < vStringLeft.size(); i++)
			{
				if (i == 0)
					uSkillStatusPos = vLeftText.size() + 1;

				if (vStringLeft[i].compare("Next Level") == 0)
					bNextLevel = true;

				if (!bNextLevel)
				{
					AddString(0, vStringLeft[i], D3DCOLOR_XRGB(243, 237, 216));
					AddString(1, vStringRight[i], D3DCOLOR_XRGB(238, 210, 151));
				}
				else
				{
					if (!vStringRight[i].empty())
					{
						if (vStringRight[i].find("gp") != std::string::npos)
							strSkillNextLevelCost = vStringRight[i];
						else
							AddString(2, FormatString("(%s)", vStringRight[i].c_str()), D3DCOLOR_XRGB(92, 163, 99));
					}
				}
			}
		}
	}

	BOOL SkillInfoBox::PrepareShowSkill(Skill* pcSkill, BOOL bSkillTimer, Rectangle2D sBox)
	{
		bInfoBoxSkillTimer = bSkillTimer;

		//Save Box Position
		sSkillBox = sBox;

		//Clear D3DVECTORs
		vLeftText.clear();
		vRightText.clear();
		vCompareText.clear();
		strSkillNextLevelCost.clear();

		uSkillStatusPos = 0;
		iSkillInfoBoxHeight = 20;

		//Copy pcSkill to cSkillWrapper
		CopyMemory(&cSkillWrapper, pcSkill, sizeof(Skill));

		//Name Skill
		if (cSkillWrapper.iID == SKILLID_DefaultAttack)
		{
			AddString(0, "Default Attack", D3DCOLOR_XRGB(243, 237, 216), TRUE);
			AddString(1, "");
		}
		else
		{
			AddString(0, cSkillWrapper.sSkillInfo.szName, D3DCOLOR_XRGB(243, 237, 216), TRUE);
			AddString(1, "");
		}

		//Level Skill
		if (cSkillWrapper.iLevel > 0 && cSkillWrapper.iID != SKILLID_Force && cSkillWrapper.iID != SKILLID_QUEST1 && cSkillWrapper.iID != SKILLID_QUEST2 &&
			cSkillWrapper.iID != SKILLID_QUEST3 && cSkillWrapper.iID != SKILLID_QUEST4 && cSkillWrapper.iID != SKILLID_QUESTNew && cSkillWrapper.iID != SKILLID_QUESTNewTime &&
			(cSkillWrapper.iID < ITEMID_HopyCrystal || cSkillWrapper.iID > ITEMID_ArcticCrystal) && cSkillWrapper.iID != SKILLID_BellatraGold && cSkillWrapper.iID != SKILLID_BellatraSilver &&
			cSkillWrapper.iID != SKILLID_BellatraBronze && cSkillWrapper.iID != SKILLID_DefaultAttack)
		{
			AddString(0, "Level");
			AddString(1, FormatString("%d", cSkillWrapper.iLevel));
			SetLineColor(D3DCOLOR_XRGB(243, 237, 216));
		}

		//Required Level
		if (cSkillWrapper.iLevel >= 0 && cSkillWrapper.iLevel < 10 && !bInfoBoxSkillTimer && cSkillWrapper.iID != SKILLID_DefaultAttack)
		{
			int iRequiredLevel = (cSkillWrapper.sSkillInfo.iSkillLevelRequired + (cSkillWrapper.iLevel * 2));

			AddString(0, "Required Level:");
			AddString(1, FormatString("%d", iRequiredLevel));
			SetLineColor(D3DCOLOR_XRGB(255, 185, 89));
		}

		//Type Skill
		if (cSkillWrapper.iID != SKILLID_Force && cSkillWrapper.iID != SKILLID_QUEST1 && cSkillWrapper.iID != SKILLID_QUEST2 && cSkillWrapper.iID != SKILLID_QUEST3 && cSkillWrapper.iID != SKILLID_QUEST4)
		{
			int iSkillID = cSkillWrapper.iID;

			if (!iSkillID)
				iSkillID = cSkillWrapper.sSkillInfo.eSkillID;

			if (IsActiveSkill((ESkillID)iSkillID))
				AddString(0, "Active Skill");
			else if (IsPassiveSkill((ESkillID)iSkillID))
				AddString(0, "Passive Skill");
			else if (IsDebuffSkill((ESkillID)iSkillID))
				AddString(0, "Debuff Skill");
			else if (IsBuffSkill((ESkillID)iSkillID))
				AddString(0, "Buff Skill");
			else if (IsSummonSkill((ESkillID)iSkillID))
				AddString(0, "Summon Skill");
			else
				AddString(0, "");

			AddString(1, "");
			SetLineColor(D3DCOLOR_XRGB(255, 185, 89));
		}

		if (cSkillWrapper.iID == TIMERSKILLID_QuestNew || cSkillWrapper.iID == TIMERSKILLID_QuestNewT)
		{
			int iQuestType = CQUESTGAME->GetQuestType(&cSkillWrapper);

			if (iQuestType == 1)
				AddString(0, "Solo Quest");
			else if (iQuestType == 2)
				AddString(0, "Party Quest");
			else if (iQuestType == 3)
				AddString(0, "Solo/Party Quest");
			else if (iQuestType == 4)
				AddString(0, "Party/Raid Quest");
			else if (iQuestType == 5)
				AddString(0, "Solo/Party/Raid Quest");
			else
				AddString(0, "Normal Quest");

			AddString(1, "");
		}

		AddString(0, "\n");


		//Description Skill
		AddString(0, cSkillWrapper.sSkillInfo.szDescription);
		AddString(1, "");
		SetLineColor(D3DCOLOR_XRGB(169, 169, 169));

		AddString(0, "\n");

		//Skill Locked
		if (SKILLDATAHANDLER->IsSkillLocked(cSkillWrapper.iID))
		{
			AddString(0, "Skill is locked. Coming soon!");
			AddString(1, "");
			SetLineColor(D3DCOLOR_XRGB(200, 90, 90));

			AddString(0, "\n");
		}

		//Correct Item Group
		if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[0] != ITEMTYPE_None)
		{
			uImageIconsItemsY = iSkillInfoBoxHeight - 4;
			AddString(0, "\n");
			AddString(0, "\n");
		}

		if (cSkillWrapper.iID == SKILLID_Automation)
		{
			AddString(0, "(+150% Damage VS Monsters)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_MetalArmor)
		{
			AddString(0, "(Physical Absorption Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Rupture)
		{
			AddString(0, "(Grand Smash 70% ATK Rtg Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_ShadowBlink)
		{
			AddString(0, "(Needs Blind Active)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_GrandSmash)
		{
			AddString(0, "(+50% Damage VS Machines)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "(Attack Rating Boost only works with Hammers)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_MagneticSphere)
		{
			AddString(0, "(+30% Damage VS Machines)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_BrutalSwing)
		{
			AddString(0, "(+40% Damage VS Demons)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_AvengingCrash)
		{
			AddString(0, "(Brutal Swing 50% Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Destroyer)
		{
			AddString(0, "(+100% Damage VS Demons)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_SurvivalInstinct)
		{
		}
		else if (cSkillWrapper.iID == SKILLID_SeismicImpact)
		{
			AddString(0, "(Avening Crash 50% Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_JumpingCrash)
		{
			AddString(0, "(+30% Damage VS Demons)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Twister)
		{
			AddString(0, "(Tornado Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_WindArrow)
		{
			AddString(0, "(+30% Damage VS Normal Monsters)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_PerfectAim)
		{
			AddString(0, "(+30% Damage VS Demons)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_FierceWind)
		{
			AddString(0, "(Perforation Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Bombardment)
		{
			AddString(0, "(Phoenix Shot Range Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Stinger)
		{
			AddString(0, "(+30% Damage VS Normal and Mutant)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Alas)
		{
			AddString(0, "(Party Buff)", D3DCOLOR_XRGB(105, 235, 105));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_HolyValor)
		{
			AddString(0, "(Party Buff)", D3DCOLOR_XRGB(105, 235, 105));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_HolyIncantation)
		{
			AddString(0, "(Undead Only)", D3DCOLOR_XRGB(255, 0, 16));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_GodlyShield)
		{
			AddString(0, "(Divine Shield Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_HolyConviction)
		{
			AddString(0, "(Holy Valor Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "(Holy Body Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "(Party Buff Holy Body 50% Chain)", D3DCOLOR_XRGB(105, 235, 105));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Extinction)
		{
			AddString(0, "(Undead Only)", D3DCOLOR_XRGB(255, 0, 16));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_HolyReflection)
		{
			AddString(0, "(Undead Only)", D3DCOLOR_XRGB(255, 0, 16));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_DivineLightning)
		{
			AddString(0, "(+50% Damage VS Undead)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_VigorBall)
		{
			AddString(0, "(+100% Damage VS Undead)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_ChainLightning)
		{
			AddString(0, "(+50% Damage VS Undead)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_Farina)
		{
			AddString(0, "(+20% Damage VS Normal Monsters)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_BiggerSpear)
		{
			AddString(0, "(+30% Damage VS Machines)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_TwistJavelin)
		{
			AddString(0, "(+30% Damage VS Demons)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_FireJavelin)
		{
			AddString(0, "(+30% Damage VS Mutants)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_LightningJavelin)
		{
			AddString(0, "(+30% Damage VS Undead)", D3DCOLOR_XRGB(212, 39, 232));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_HallofValhalla)
		{
			AddString(0, "(Triumph of Valhalla Chain)", D3DCOLOR_XRGB(105, 144, 176));
			AddString(1, "");
			AddString(0, "\n");
		}
		else if (cSkillWrapper.iID == SKILLID_AdventMigal)
		{
			AddString(0, "(Party Buff)", D3DCOLOR_XRGB(105, 235, 105));
			AddString(1, "");
			AddString(0, "\n");
		}

		//Next Level
		if (cSkillWrapper.iLevel < 10 && cSkillWrapper.iLevel > 0 && !bInfoBoxSkillTimer && cSkillWrapper.iID != SKILLID_DefaultAttack)
		{
			AddString(0, "Next Level", D3DCOLOR_XRGB(92, 163, 99), TRUE);
			AddString(1, "");
		}

		//Format Skill Info
		FormatSkillInfo();

		if (!bInfoBoxSkillTimer && cSkillWrapper.sSkillInfo.eSkillType != SKILLTYPE_Passive)
			AddString(0, "\n");

		if (cSkillWrapper.iLevel > 0 && !bInfoBoxSkillTimer)
		{
			//MP
			if (cSkillWrapper.sSkillInfo.dwUseManaPointer)
			{
				int* piaUseMana = (int*)cSkillWrapper.sSkillInfo.dwUseManaPointer;

				if (piaUseMana[cSkillWrapper.iLevel - 1] != 0)
				{
					AddString(0, "MP Cost:", D3DCOLOR_XRGB(243, 237, 216));

					//Decrease MP Item?
					if ((READDWORD(0x035D0C48) > 0) && (READDWORD(0x035D0C4C) > 0))
					{
						int iDecreaseMP = (piaUseMana[cSkillWrapper.iLevel - 1] * READDWORD(0x035D0C4C)) / 100;

						AddString(1, FormatString("%d(-%d)", piaUseMana[cSkillWrapper.iLevel - 1], iDecreaseMP));
					}
					else
						AddString(1, FormatString("%d", piaUseMana[cSkillWrapper.iLevel - 1]));

					SetLineColor(D3DCOLOR_XRGB(234, 186, 81), 1);
				}
			}

			//STM
			if (cSkillWrapper.sSkillInfo.iaSkillUseStamina[0] != 0)
			{
				AddString(0, "SP Cost:", D3DCOLOR_XRGB(243, 237, 216));

				//Decrease STM Item?
				if ((READDWORD(0x035D0C60) > 0) && (READDWORD(0x035D0C64) > 0))
				{
					int iSP = cSkillWrapper.sSkillInfo.iaSkillUseStamina[0] + (cSkillWrapper.sSkillInfo.iaSkillUseStamina[1] * (cSkillWrapper.iLevel - 1));

					int iDecreaseSP = (iSP * READDWORD(0x035D0C64)) / 100;

					AddString(1, FormatString("%d(-%d)", iSP, iDecreaseSP));
				}
				else
					AddString(1, FormatString("%d", cSkillWrapper.sSkillInfo.iaSkillUseStamina[0] + (cSkillWrapper.sSkillInfo.iaSkillUseStamina[1] * (cSkillWrapper.iLevel - 1))));

				SetLineColor(D3DCOLOR_XRGB(234, 186, 81), 1);
			}
		}

		//Cooldown Skill
		if (!bInfoBoxSkillTimer && (cSkillWrapper.iLevel > 0) && (cSkillWrapper.sSkillInfo.eSkillType != SKILLTYPE_Passive) && cSkillWrapper.iID != SKILLID_DefaultAttack)
		{
			int iMastery = cSkillWrapper.Mastery;

			if (iMastery > MAX_MASTERY)
				iMastery = MAX_MASTERY;
			else if (iMastery < 2)
				iMastery = 2;

			float fSkillCooldown = ((MAX_MASTERY / (MAX_MASTERY / ((float)iMastery / 2.0f))) * 35) * (1000.0f / 60.0f);
			fSkillCooldown /= 1000.0f;

			AddString(0, "Cooldown:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%.2fsec", fSkillCooldown), D3DCOLOR_XRGB(234, 186, 81));
		}

		//Next Level Cost
		if (cSkillWrapper.iLevel < 10 && !strSkillNextLevelCost.empty())
		{
			AddString(0, "Upgrade Cost:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, strSkillNextLevelCost, D3DCOLOR_XRGB(234, 186, 81));
		}

		//Time Left
		if (bInfoBoxSkillTimer && (cSkillWrapper.iID & 0xFFFF0000) != 0x096A0000 && cSkillWrapper.iID != SKILLID_AbsorptionOfGlory && cSkillWrapper.iID != SKILLID_PowerSiege && cSkillWrapper.iID != SKILLID_EvasionAdaption)
		{
			int iTimeLeft = 0;

			if ((cSkillWrapper.iCheckTime / 70) > 0)
				iTimeLeft = cSkillWrapper.iUseTime - (cSkillWrapper.iCheckTime / 70);
			else
				iTimeLeft = (cSkillWrapper.iCheckTime / 70) - cSkillWrapper.iUseTime;

			int iHour = abs(iTimeLeft / 3600);
			int iMinutes = abs((iTimeLeft) / 60) % 60;
			int iSeconds = abs((iTimeLeft) % 60);

			AddString(0, "\n");
			AddString(0, "Time Left:", D3DCOLOR_XRGB(243, 237, 216));
			AddString(1, FormatString("%02d:%02d:%02d", iHour, iMinutes, iSeconds), D3DCOLOR_XRGB(234, 186, 81));
		}

		return TRUE;
	}

	void SkillInfoBox::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!READDWORD(0x367DF48) && !bInfoBoxSkillTimer)
			return;

		if (bInfoBoxSkillTimer && !READDWORD(0x0367DE8C))
			return;

		//Set iWidth and iHeight of Box
		int iSkillInfoBoxWidth = 224;

		//Adjust Box Position
		if (!bInfoBoxSkillTimer)
		{
			iX = sSkillBox.iX - (iSkillInfoBoxWidth >> 1) + 20;
			iY = sSkillBox.iY - iSkillInfoBoxHeight;
		}
		else
		{
			iX = sSkillBox.iX;
			iY = sSkillBox.iY;
		}

		//iItemSlot of box is out the window?
		if (iX < 0)
			iX = 0;

		if (iY < 0)
			iY = 16;

		if (iX + iSkillInfoBoxWidth > (int)RESOLUTION_WIDTH)
			iX -= ((iX + iSkillInfoBoxWidth) - RESOLUTION_WIDTH) + 16;

		//Fix position
		if (!bInfoBoxSkillTimer)
			iY += RESOLUTION_HEIGHT - 600;

		//Draw Skill Info Box Background
		DrawSkillInfoBox(iX, iY + 20, iSkillInfoBoxWidth, iSkillInfoBoxHeight);

		//Drawing Border
		UI::ImageRender::Render(pImageBorderLeftTop, iX, iY + 10, pImageBorderLeftTop->GetWidth(), pImageBorderLeftTop->GetHeight(), -1);
		UI::ImageRender::Render(pImageBorderTop, iX + pImageBorderLeftTop->GetWidth(), iY + 10, iSkillInfoBoxWidth - pImageBorderLeftTop->GetWidth() - pImageBorderRightTop->GetWidth(), pImageBorderTop->GetHeight(), -1);
		UI::ImageRender::Render(pImageBorderRightTop, iX + pImageBorderLeftTop->GetWidth() + iSkillInfoBoxWidth - pImageBorderLeftTop->GetWidth() - pImageBorderRightTop->GetWidth(), iY + 10, pImageBorderRightTop->GetWidth(), pImageBorderRightTop->GetHeight(), -1);
		UI::ImageRender::Render(pImageBorderLeft, iX, iY + 10 + pImageBorderLeftTop->GetHeight(), pImageBorderLeft->GetWidth(), iSkillInfoBoxHeight - pImageBorderLeftTop->GetWidth() - pImageBorderLeftBottom->GetWidth(), -1);
		UI::ImageRender::Render(pImageBorderRight, iX + iSkillInfoBoxWidth - pImageBorderRight->GetWidth(), iY + 10 + pImageBorderLeftTop->GetHeight(), pImageBorderRight->GetWidth(), iSkillInfoBoxHeight - pImageBorderLeftTop->GetWidth() - pImageBorderLeftBottom->GetWidth(), -1);
		UI::ImageRender::Render(pImageBorderLeftBottom, iX, iY + 10 + iSkillInfoBoxHeight - pImageBorderLeftBottom->GetHeight(), pImageBorderLeftBottom->GetWidth(), pImageBorderLeftBottom->GetHeight(), -1);
		UI::ImageRender::Render(pImageBorderRightBottom, iX + iSkillInfoBoxWidth - pImageBorderRightBottom->GetWidth(), iY + 10 + iSkillInfoBoxHeight - pImageBorderRightBottom->GetHeight(), pImageBorderRightBottom->GetWidth(), pImageBorderRightBottom->GetHeight(), -1);
		UI::ImageRender::Render(pImageBorderBottom, iX + pImageBorderLeftBottom->GetWidth(), iY + 10 + iSkillInfoBoxHeight - pImageBorderBottom->GetHeight(), iSkillInfoBoxWidth - pImageBorderLeftTop->GetWidth() - pImageBorderRightTop->GetWidth(), pImageBorderBottom->GetHeight(), -1);

		//Render Text
		int iAddTextHeight = 0;
		if (vLeftText.size() == vRightText.size())
		{
			for (size_t i = 0; i < vLeftText.size(); i++)
			{
				Text_ptr pLeftText = vLeftText[i];
				Text_ptr pRightText = vRightText[i];

				//Load Texts
				pLeftText->SetNoClip(TRUE);
				pRightText->SetNoClip(TRUE);

				pLeftText->SetHorizontalAlign(ALIGN_Left);
				pRightText->SetHorizontalAlign(ALIGN_Left);

				//Render Texts
				pLeftText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
				pRightText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
			}

			if (!bInfoBoxSkillTimer)
			{
				for (size_t i = 0; i < vCompareText.size(); i++)
				{
					Text_ptr pCompareText = vCompareText[i];
					if (pCompareText)
					{
						pCompareText->SetNoClip(TRUE);
						pCompareText->SetHorizontalAlign(ALIGN_Left);
						pCompareText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
					}
				}
			}
		}

		//Render Correct Item Group
		if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[0] != ITEMTYPE_None && uImageIconsItemsY > 0)
		{
			for (size_t i = 0; i < 8; i++)
			{
				if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Axe)
					UI::ImageRender::Render(pImageIconItems[1], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Wand)
					UI::ImageRender::Render(pImageIconItems[2], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Hammer)
					UI::ImageRender::Render(pImageIconItems[3], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Shield)
					UI::ImageRender::Render(pImageIconItems[4], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Scythe)
					UI::ImageRender::Render(pImageIconItems[5], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Sword)
					UI::ImageRender::Render(pImageIconItems[6], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Claw)
					UI::ImageRender::Render(pImageIconItems[7], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Bow)
					UI::ImageRender::Render(pImageIconItems[8], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Javelin)
					UI::ImageRender::Render(pImageIconItems[9], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Dagger)
					UI::ImageRender::Render(pImageIconItems[10], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
				else if (cSkillWrapper.sSkillInfo.eSkillItemAllowed[i] == ITEMTYPE_Phantom)
					UI::ImageRender::Render(pImageIconItems[11], iX + 13 + (i * 20), iY + uImageIconsItemsY, 18, 24, -1);
			}
		}
	}

	void SkillInfoBox::DrawSkillInfoBox(int iX, int iY, int iWidth, int iHeight)
	{
		//Draw Item Info Box Background
		if (pRenderTargetMask)
		{
			if (GetGraphicsDevice()->SetRenderTarget(pRenderTargetMask))
			{
				//Clear Render Target
				GetGraphicsDevice()->Clear(TRUE, TRUE, FALSE);

				//Draw Background
				GRAPHICENGINE->DrawRectangle2D(Rectangle2D(0, 0, iWidth, iHeight), D3DCOLOR_ARGB(235, 45, 39, 27), D3DCOLOR_ARGB(245, 9, 23, 22));

				//Drawing Mask Border
				UI::ImageRender::Render(pImageMaskLeftTop, 0, 0, pImageMaskLeftTop->GetWidth(), pImageMaskLeftTop->GetHeight(), -1);
				UI::ImageRender::Render(pImageMaskRightTop, iWidth - pImageMaskRightTop->GetWidth(), 0, pImageMaskRightTop->GetWidth(), pImageMaskRightTop->GetHeight(), -1);
				UI::ImageRender::Render(pImageMaskLeftBottom, 0, iHeight - pImageMaskLeftBottom->GetHeight(), pImageMaskLeftBottom->GetWidth(), pImageMaskLeftBottom->GetHeight(), -1);
				UI::ImageRender::Render(pImageMaskRightBottom, iWidth - pImageMaskRightTop->GetWidth(), iHeight - pImageMaskLeftBottom->GetHeight(), pImageMaskRightBottom->GetWidth(), pImageMaskRightBottom->GetHeight(), -1);

				//Back Old Render Target
				GetGraphicsDevice()->UnsetRenderTarget();
			}

			//Set Sprite Effect...
			UI::ImageRender::SetEffect(pEffectMask);
			pEffectMask->SetTechnique("Mask");

			if (pEffectMask->Begin() >= 0)
			{
				//Render the Render Target and mask it on effect
				UI::ImageRender::Render(pRenderTargetMask->GetTexture(), iX, iY - 10, pRenderTargetMask->GetWidth(), pRenderTargetMask->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), FALSE);

				pEffectMask->End();
			}


			UI::ImageRender::SetEffect(NULL);
		}
	}

}