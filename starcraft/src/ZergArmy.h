#pragma once

#include <BWAPI.h>
#include "ArmyInterface.h"

class ZergArmy : public ArmyInterface
{
public:
	const BWAPI::Unitset Bases() override;

	inline const int drone() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Drone]; }
	inline const int overlord() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Overlord]; }
	inline const int zergling() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Zergling]; }
	inline const int hydralisk() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Hydralisk]; }
	inline const int lurker() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Lurker]; }
	inline const int scourge() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Scourge]; }
	inline const int mutalisk() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Mutalisk]; }
	inline const int guardian() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Guardian]; }
	inline const int devourer() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Devourer]; }
	inline const int queen() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Queen]; }
	inline const int ultralisk() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Ultralisk]; }
	inline const int defiler() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Defiler]; }

	inline const int hatchery() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Hatchery]; }
	inline const int extractor() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Extractor]; }
	inline const int lair() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Lair]; }
	inline const int hive() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Hive]; }
	inline const int spawning_pool() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Spawning_Pool]; }
	inline const int hypralisk_den() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Hydralisk_Den]; }
	inline const int queens_nest() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Queens_Nest]; }
	inline const int spire() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Spire]; }
	inline const int defiler_mound() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Defiler_Mound]; }
	inline const int nydus_canal() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Nydus_Canal]; }
	inline const int ultralisk_cavern() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Ultralisk_Cavern]; }
	inline const int greater_spire() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Greater_Spire]; }
	inline const int sunken_colony() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Sunken_Colony]; }
	inline const int spore_colony() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Spore_Colony]; }
	inline const int creep_colony() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Creep_Colony]; }
	inline const int evolution_chamber() override { return m_unitCounts[BWAPI::UnitTypes::Zerg_Evolution_Chamber]; }
};