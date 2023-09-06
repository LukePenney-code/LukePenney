#pragma once

#include <BWAPI.h>
#include "ArmyInterface.h"

class ProtossArmy : public ArmyInterface
{
public:
	const BWAPI::Unitset Bases() override;

	inline const int probe() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Probe]; }
	inline const int zealot() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Zealot]; }
	inline const int dragoon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Dragoon]; }
	inline const int high_templar() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_High_Templar]; }
	inline const int dark_templar() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Dark_Templar]; }
	inline const int shuttle() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Shuttle]; }
	inline const int reaver() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Reaver]; }
	inline const int observer() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Observer]; }
	inline const int scout() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Scout]; }
	inline const int corsair() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Corsair]; }
	inline const int arbiter() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Arbiter]; }
	inline const int carrier() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Carrier]; }
	inline const int archon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Archon]; }
	inline const int dark_archon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Dark_Archon]; }

	inline const int pylon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Pylon]; }
	inline const int nexus() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Nexus]; }
	inline const int assimilator() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Assimilator]; }
	inline const int gateway() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Gateway]; }
	inline const int forge() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Forge]; }
	inline const int shield_battery() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Shield_Battery]; }
	inline const int cybernetics_core() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Cybernetics_Core]; }
	inline const int photon_cannon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Photon_Cannon]; }
	inline const int citadel_of_arun() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Citadel_of_Adun]; }
	inline const int robotics_facility() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Robotics_Facility]; }
	inline const int stargate() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Stargate]; }
	inline const int templar_archives() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Templar_Archives]; }
	inline const int robotics_support_bay() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Robotics_Support_Bay]; }
	inline const int observatory() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Observatory]; }
	inline const int fleet_beacon() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Fleet_Beacon]; }
	inline const int arbiter_tribunal() override { return m_unitCounts[BWAPI::UnitTypes::Protoss_Arbiter_Tribunal]; }
};