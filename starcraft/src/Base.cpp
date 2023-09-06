#include "Base.h"
#include "Tools.h"

void Base::setWorkers(const BWAPI::Unitset& workers)
{
	m_workers = workers;
}

void Base::addWorker(BWAPI::Unit unit)
{
	m_workers.insert(unit);
}

BWAPI::Unit Base::getWorker()
{
	for (auto unit : m_workers)
	{
		if (unit->isIdle() || unit->isGatheringMinerals() || unit->isGatheringGas())
		{
			return unit;
		}
	}

	return nullptr;
}

void Base::removeWorker(BWAPI::Unit unit)
{
    m_workers.erase(unit);
}

Base& Base::operator=(const Base& base)
{
    m_unit = base.m_unit;
    m_workers = base.m_workers;
    return *this;
}

void Base::onFrame()
{
    sendIdleWorkersToAssimilator();
    sendIdleWorkersToMinerals();
    if (Tools::CountUnitsOfType(BWAPI::UnitTypes::Protoss_Assimilator, BWAPI::Broodwar->self()->getUnits()) < 1 && BWAPI::Broodwar->self()->minerals() > 110)
    {
        buildStructure(BWAPI::UnitTypes::Protoss_Assimilator);
    }
    trainAdditionalWorkers();
}

// Send our idle workers to mine minerals so they don't just stand there
void Base::sendIdleWorkersToMinerals()
{
    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
 
    for (auto& unit : m_workers)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(m_unit, BWAPI::Broodwar->getMinerals());
            

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestMineral) { unit->rightClick(closestMineral); }
        }
    }
}

void Base::sendIdleWorkersToAssimilator()
{
    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
    int num_gathering = 0;
    for (auto& unit : m_workers)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle() && !unit->isGatheringMinerals())
        {
            // Get the closest mineral to this worker unit
            const BWAPI::Unit  assmilator = Tools::GetUnitOfType(BWAPI::UnitTypes::Protoss_Assimilator);

            // If a valid assimilator was found, right click it with the unit in order to start harvesting
            if (assmilator)
            {
                unit->rightClick(assmilator);
                unit->isGatheringGas();
            }
        }
        num_gathering++;
        if (num_gathering > 6)
        {
            break;
        }
    }
}

// Train more workers so we can gather more income
void Base::trainAdditionalWorkers()
{
    const int workersOwned = m_workers.size();
    if (workersOwned < m_workersWanted)
    {
        // if we have a valid depot unit and it's currently not training something, train a worker
        // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
        if (m_unit && !m_unit->isTraining()) { m_unit->train(WorkerType); }
    }
}

bool Base::buildStructure(BWAPI::UnitType type)
{

    const bool startedBuilding = Tools::BuildBuilding(type, *this);
    if (startedBuilding)
    {
        BWAPI::Broodwar->printf("Started Building %s", type.getName().c_str());
    }

    return startedBuilding;
}

void Base::buildStructure(BWAPI::TilePosition loc, BWAPI::UnitType type)
{
    const bool startedBuilding = Tools::BuildBuilding(type, loc);
    if (startedBuilding)
    {
        BWAPI::Broodwar->printf("Started Building %s", type.getName().c_str());
    }
}



BWAPI::TilePosition Base::getPosition()
{
    return m_unit->getTilePosition();
}
