#pragma once

#include <BWAPI.h>
#include <vector>
#include <deque>

class ScoutGroup
{
private:
	BWAPI::Unitset m_units;
	std::deque<BWAPI::TilePosition> m_targets;
	std::deque<BWAPI::UnitType> m_types;
	bool m_alive = false;
	bool m_enemyBaseFound = false;

public:
	void set(const BWAPI::Unitset& units, const std::deque<BWAPI::TilePosition>& locations);
	void setTargets(const std::deque<BWAPI::TilePosition>& locations);
	void addTargets(BWAPI::TilePosition location);
	void addTargetTypes(BWAPI::UnitType type);

	const BWAPI::Unitset& units() const;
	void onFrame();
	void kill();
	void start();
	void enemyFound();
	bool hasHatchery();

	bool isAlive();
	bool isSet();
	inline bool isEnemyFound() { return m_enemyBaseFound; }
};