#pragma once

#include <BWAPI.h>
#include "Base.h"

#define WorkerType BWAPI::UnitTypes::Protoss_Probe
#define DepotType BWAPI::UnitTypes::Protoss_Nexus

namespace Tools
{
    BWAPI::Unit GetClosestUnitTo(BWAPI::Position p, const BWAPI::Unitset& units);
    BWAPI::Unit GetClosestUnitTo(BWAPI::Unit unit, const BWAPI::Unitset& units);

    int CountUnitsOfType(BWAPI::UnitType type, const BWAPI::Unitset& units);

    BWAPI::Unitset GetAllUnitsOfType(BWAPI::UnitType type);
    BWAPI::Unit GetUnitOfType(BWAPI::UnitType type);
    BWAPI::Unit GetIdleWorker();
    BWAPI::Unit GetDepot();

    // Only used for starting location. Only used for main base
    bool BuildBuilding(BWAPI::UnitType type);
    // Specify which base the structure is built
    bool BuildBuilding(BWAPI::UnitType type, Base& builder);
    // Specify the tile position
    bool BuildBuilding(BWAPI::UnitType type, BWAPI::TilePosition loc);

    void DrawUnitBoundingBoxes();
    void DrawUnitCommands();

    void SmartRightClick(BWAPI::Unit unit, BWAPI::Unit target);

    int GetTotalSupply(bool inProgress = false);

    void DrawUnitHealthBars();
    void DrawHealthBar(BWAPI::Unit unit, double ratio, BWAPI::Color color, int yOffset);
}