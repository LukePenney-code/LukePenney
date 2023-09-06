#include "BaseManager.h"
#include "Tools.h"

void BaseManager::addBase(BWAPI::Unit unit)
{
	m_map[unit->getID()] = Base(unit);
	m_baseIds.push_back(unit->getID());
}

void BaseManager::assignWorkers()
{
	auto workers = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Probe);
	auto nexus = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Nexus);
	for (auto w : workers)
	{
		auto n = Tools::GetClosestUnitTo(w->getPosition(), nexus);
		m_map[n->getID()].addWorker(w);
	}
}

void BaseManager::assignWorker(BWAPI::Unit unit)
{
	auto nexus = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Nexus);
	auto n = Tools::GetClosestUnitTo(unit->getPosition(), nexus);
	m_map[n->getID()].addWorker(unit);
}

Base& BaseManager::getMain()
{
	return m_map[m_baseIds[0]];
}

Base& BaseManager::getBase(int index)
{
	return m_map[m_baseIds[index]];
}

void BaseManager::update()
{
	std::vector<int> toRemove;
	for (auto& kv : m_map)
	{
		if (!kv.second.alive())
		{
			toRemove.push_back(kv.first);
		}
	}

	for (int i : toRemove)
	{
		remove(i);
	}
}

void BaseManager::remove(int id)
{
	m_map.erase(id);
	for (auto it = m_baseIds.begin(); it != m_baseIds.end(); )
	{
		if (*it == id)
		{
			it = m_baseIds.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void BaseManager::onFrame()
{
	update();
	for (auto& kv : m_map)
	{
		kv.second.onFrame();
	}
}
