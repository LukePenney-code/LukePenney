#include "ProtossArmy.h"
#include "Opponent.h"
#include "BaseManager.h"
#include "MapTools.h"
#include <memory>
#include <vector>


class ArmyManager
{
	std::unique_ptr<ArmyInterface> m_army;
	std::vector<BWAPI::UnitType> m_next;
	BaseManager* m_bases = nullptr;
	Opponent m_opponent;
	MapTools m_mapTools;

	int m_building = 0;
	bool m_attack = false;
	bool m_patrol = false;

public:
	ArmyManager();
	void setup(BaseManager* bases);

	void add(BWAPI::Unit unit);
	void remove(BWAPI::Unit unit);
	inline void addEnemy(BWAPI::Unit unit) { m_opponent.add(unit); }
	inline void removeEnemy(BWAPI::Unit unit) { m_opponent.remove(unit); }

	void onFrame();
	BWAPI::UnitType getNextBuilding();
	void built(BWAPI::UnitType type);
	void Zealot_ATTACK();
	void Templar_ATTACK();
	void Corsair_PATROL();
};