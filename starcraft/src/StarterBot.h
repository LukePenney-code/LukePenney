#pragma once

#include "MapTools.h"
#include "Scout.h"
#include "BaseManager.h"
#include "Opponent.h"
#include "ArmyManager.h"

#include <BWAPI.h>
#include <map>
#include <iostream>

class StarterBot
{
    MapTools m_mapTools;
	ScoutGroup m_scout;
	BaseManager m_bases;
	ArmyManager m_army;

public:

    StarterBot();

    // helper functions to get you started with bot programming and learn the API
    void buildAdditionalSupply();
    void drawDebugInformation();
	void manageScout();

    // functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
};
