#include "Scout.h"

void ScoutGroup::set(const BWAPI::Unitset& unitset, const std::deque<BWAPI::TilePosition>& locations)
{
	m_units = unitset;
	m_targets = locations;
}

void ScoutGroup::setTargets(const std::deque<BWAPI::TilePosition>& locations)
{
	m_targets = locations;
}

void ScoutGroup::addTargets(BWAPI::TilePosition location)
{
	m_targets.push_back(location);
}

void ScoutGroup::addTargetTypes(BWAPI::UnitType type)
{
	m_types.push_back(type);
}

bool ScoutGroup::hasHatchery()
{
	bool hatchery = false;

	for (int i = 0; i < m_types.size(); i++)
	{
		if (m_types[i] == BWAPI::UnitTypes::Zerg_Hatchery)
		{
			hatchery = true;
			return hatchery;
		}
	}
}

void ScoutGroup::enemyFound()
{
	m_targets.clear();
	m_enemyBaseFound = true;
}

bool ScoutGroup::isSet()
{
	return m_units.size() && m_targets.size();
}

const BWAPI::Unitset& ScoutGroup::units() const
{
	return m_units;
}

void ScoutGroup::onFrame()
{
	if (m_units.empty() || !m_alive)
	{
		kill();
		return;
	}

	auto sight = (*m_units.begin())->getType().sightRange();

	int i = 0;
	for (auto& loc : m_targets)
	{
		const BWAPI::Position pos(loc);
		if (m_units.getPosition().getApproxDistance(pos) < (sight / 2))
		{
			i++;
			continue;
		}

		m_units.move(pos);
		break;
	}

	for (int j = 0; j < i; j++)
	{
		m_targets.erase(m_targets.begin());
	}
}

void ScoutGroup::kill()
{
	m_alive = false;
	m_targets.clear();
	m_units.clear();
}

bool ScoutGroup::isAlive()
{
	return m_alive;
}

void ScoutGroup::start()
{
	m_alive = true;
}