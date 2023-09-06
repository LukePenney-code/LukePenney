#include "ArmyManager.h"
#include "Tools.h"

ArmyManager::ArmyManager()
{
	m_army = std::make_unique<ProtossArmy>();
	m_next = std::vector<BWAPI::UnitType>{ BWAPI::UnitTypes::Protoss_Gateway,
		BWAPI::UnitTypes::Protoss_Cybernetics_Core, 
	    BWAPI::UnitTypes::Protoss_Stargate, BWAPI::UnitTypes::Protoss_Gateway};
}

void ArmyManager::setup(BaseManager* bases)
{
	m_bases = bases;
}

void ArmyManager::add(BWAPI::Unit unit)
{
	m_army->add(unit);
}

void ArmyManager::remove(BWAPI::Unit unit)
{
	m_army->remove(unit);
}

void ArmyManager::onFrame()
{
	m_opponent.onFrame();

	auto probes = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Probe);
	int gasToUse = 0;
	int mineralsToUse = 0;

	for (auto probe : probes)
	{
		if (probe->isConstructing())
		{
			auto type = probe->getLastCommand().getUnitType();
			gasToUse += type.gasPrice();
			mineralsToUse += type.mineralPrice();
		}
	}

	m_building--;

	BWAPI::UnitType next = getNextBuilding();
	if (m_building < 0 && next != BWAPI::UnitTypes::None
		&& BWAPI::Broodwar->self()->minerals() - mineralsToUse >= next.mineralPrice()
		&& BWAPI::Broodwar->self()->gas() - gasToUse >= next.gasPrice())
	{
		
		auto did = m_bases->getMain().buildStructure(next);
		if (did) m_building = 2000;
	}

	auto zealot_gateways = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Gateway);
	for (auto gate : zealot_gateways)
	{
		if (!gate->isTraining())
		{
			gate->train(BWAPI::UnitTypes::Protoss_Zealot);
		}

	}

	auto gateways = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Gateway);
	for (auto gate : gateways)
	{
		if (!gate->isTraining())
		{
			gate->train(BWAPI::UnitTypes::Protoss_High_Templar);
		}
	}

	auto star_gates = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Stargate);
	for (auto gate : star_gates)
	{
		if (!gate->isTraining())
		{
			gate->train(BWAPI::UnitTypes::Protoss_Corsair);
		}
	}
	if (m_army->zealot() > 3)
	{
		m_attack = true;
	}
	if (m_army->corsair() > 2 )
	{
		m_patrol = true;
	}

	if (m_attack){
	
		Zealot_ATTACK();
	    Templar_ATTACK();
	}

	if (m_patrol)
	{
		Corsair_PATROL();
	}
}

BWAPI::UnitType ArmyManager::getNextBuilding()
{
	return m_next.size() > 0 ? m_next[0] : BWAPI::UnitTypes::None;
}

void ArmyManager::built(BWAPI::UnitType type)
{
	if (type == getNextBuilding())
	{
		m_next.erase(m_next.begin());
		m_building = 0;
	}
}

void ArmyManager::Zealot_ATTACK()
{
	auto zealots = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Zealot);
	auto enemyBase = *m_opponent.army()->buildings().begin();

	for (auto z : zealots)
	{
		if (z->getOrder() != BWAPI::Orders::AttackMove)
		{
			z->attack(enemyBase.position);
		}
	}
}

void ArmyManager::Templar_ATTACK()
{
	auto templar = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_High_Templar);
	auto enemyBase = *m_opponent.army()->buildings().begin();

	for (auto t : templar)
	{
		if (t->getOrder() != BWAPI::Orders::CastPsionicStorm)
		{
			t->useTech(BWAPI::TechTypes::Psionic_Storm, enemyBase.position);
		}
	}
}

void ArmyManager::Corsair_PATROL()
{
	auto corsairs = Tools::GetAllUnitsOfType(BWAPI::UnitTypes::Protoss_Corsair);
	auto enemyBase = *m_opponent.army()->buildings().begin();

	for (auto c : corsairs)
	{
		if (c->getOrder() != BWAPI::Orders::Patrol)
		{
			c->patrol(enemyBase.position);
		}
	}
}

