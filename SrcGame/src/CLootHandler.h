#pragma once

#include "smPacket.h"

class CLootFilter
{
public:
	bool getEnabled() const { return bEnabled; }
	void setEnabled(bool value) { bEnabled = value; }

	bool getHpPot() const { return bHpPot; }
	void setHpPot(bool value) { bHpPot = value; }

	bool getMpPot() const { return bMpPot; }
	void setMpPot(bool value) { bMpPot = value; }

	bool getSpPot() const { return bSpPot; }
	void setSpPot(bool value) { bSpPot = value; }

	bool getGold() const { return bGold; }
	void setGold(bool value) { bGold = value; }

	bool getAmulets() const { return bAmulets; }
	void setAmulets(bool value) { bAmulets = value; }

	bool getRings() const { return bRings; }
	void setRings(bool value) { bRings = value; }

	bool getSheltoms() const { return bSheltoms; }
	void setSheltoms(bool value) { bSheltoms = value; }

	bool getForce() const { return bForce; }
	void setForce(bool value) { bForce = value; }

	bool getPremiums() const { return bPremiums; }
	void setPremiums(bool value) { bPremiums = value; }

	bool getCrystals() const { return bCrystals; }
	void setCrystals(bool value) { bCrystals = value; }

	bool getDefense() const { return bDefense; }
	void setDefense(bool value) { bDefense = value; }

	bool getOffense() const { return bOffense; }
	void setOffense(bool value) { bOffense = value; }

	bool getEverything() const { return bEverything; }
	void setEverything(bool value) { bEverything = value; }

	bool getNonSpec() const { return bNonSpec; }
	void setNonSpec(bool value) { bNonSpec = value; }

	bool getFighter() const { return bFighter; }
	void setFighter(bool value) { bFighter = value; }

	bool getMech() const { return bMech; }
	void setMech(bool value) { bMech = value; }

	bool getArcher() const { return bArcher; }
	void setArcher(bool value) { bArcher = value; }

	bool getPikeman() const { return bPikeman; }
	void setPikeman(bool value) { bPikeman = value; }

	bool getAtalanta() const { return bAtalanta; }
	void setAtalanta(bool value) { bAtalanta = value; }

	bool getKnight() const { return bKnight; }
	void setKnight(bool value) { bKnight = value; }

	bool getMagician() const { return bMagician; }
	void setMagician(bool value) { bMagician = value; }

	bool getPriestess() const { return bPriestess; }
	void setPriestess(bool value) { bPriestess = value; }

	bool Filter(TRANS_ITEM* pItem);

private:
	bool bEnabled;
	bool bHpPot;
	bool bMpPot;
	bool bSpPot;
	bool bGold;
	bool bAmulets;
	bool bRings;
	bool bSheltoms;
	bool bForce;
	bool bPremiums;
	bool bCrystals;
	bool bDefense;
	bool bOffense;
	bool bEverything;
	bool bNonSpec;
	bool bFighter;
	bool bMech;
	bool bArcher;
	bool bPikeman;
	bool bAtalanta;
	bool bKnight;
	bool bMagician;
	bool bPriestess;
};

extern CLootFilter cLootFilter;