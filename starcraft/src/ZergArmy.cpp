#include "ZergArmy.h"

const BWAPI::Unitset ZergArmy::Bases()
{
	BWAPI::Unitset set;

	for (auto unit : m_buildings)
	{
		BWAPI::UnitType type = unit.type;
		if (type == BWAPI::UnitTypes::Zerg_Hatchery || type == BWAPI::UnitTypes::Zerg_Lair || type == BWAPI::UnitTypes::Zerg_Hive)
		{
			set.insert(unit.unit);
		}
	}

	return set;
}
