#pragma once

#include <BWAPI.h>

class Base
{
	BWAPI::Unit m_unit = nullptr;
	BWAPI::Unitset m_workers;

	const int m_workersWanted = 18;

public:
	Base() {}
	Base(BWAPI::Unit unit) : m_unit(unit) {} ;
	Base& operator = (const Base& base);
	void onFrame();

	void setWorkers(const BWAPI::Unitset& workers);
	void addWorker(BWAPI::Unit unit);
	BWAPI::Unit getWorker();
	void removeWorker(BWAPI::Unit unit);

	void sendIdleWorkersToMinerals();
	void sendIdleWorkersToAssimilator();
	void trainAdditionalWorkers();

	inline BWAPI::Unitset& getWorkers() { return m_workers; }
	inline bool alive() { return m_unit && m_unit->exists(); }
	BWAPI::TilePosition getPosition();
	bool buildStructure(BWAPI::UnitType type);
	void Base::buildStructure(BWAPI::TilePosition loc, BWAPI::UnitType type);
};