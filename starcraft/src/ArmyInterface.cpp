#include "ArmyInterface.h"
#include <algorithm>

void ArmyInterface::onChange(BWAPI::UnitType type, bool add)
{
	m_unitCounts[type] += 1 * (add ? 1 : -1);
	m_unitCounts[type] = std::max(0, m_unitCounts[type]);
}

void ArmyInterface::add(BWAPI::Unit unit)
{
	if (unit->getType().isBuilding())
	{
		addBuilding(unit);
	}
	else
	{
		addUnit(unit);
	}
}

void ArmyInterface::remove(BWAPI::Unit unit)
{
	if (unit->getType().isBuilding())
	{
		removeBuilding(unit);
	}
	else
	{
		removeUnit(unit);
	}
}

void ArmyInterface::addBuilding(BWAPI::Unit building)
{
	UnitProfile profile = { building->getType(), building, building->getPosition(), building->getID() };
	if (m_buildings.find(profile) == m_buildings.end())
	{
		m_buildings.insert(profile);
		onChange(building->getType(), true);
	}
}

void ArmyInterface::addUnit(BWAPI::Unit unit)
{
	UnitProfile profile = { unit->getType(), unit, unit->getPosition(), unit->getID() };
	if (m_units.find(profile) == m_units.end())
	{
		m_units.insert(profile);
		onChange(unit->getType(), true);
	}
}

void ArmyInterface::removeBuilding(BWAPI::Unit building)
{
	UnitProfile profile = { building->getType(), building, building->getPosition(), building->getID() };
	if (m_buildings.erase(profile))
	{
		onChange(profile.type, false);
	}
}

void ArmyInterface::removeUnit(BWAPI::Unit unit)
{
	UnitProfile profile = { unit->getType(), unit, unit->getPosition(), unit->getID() };
	if (m_units.erase(profile))
	{
		onChange(profile.type, false);
	}
}