#include "ProtossArmy.h"

const BWAPI::Unitset ProtossArmy::Bases()
{
	BWAPI::Unitset set;

	for (auto& unit : m_buildings)
	{
		BWAPI::UnitType type = unit.type;
		if (type == BWAPI::UnitTypes::Protoss_Nexus)
		{
			set.insert(unit.unit);
		}
	}

	return set;
}