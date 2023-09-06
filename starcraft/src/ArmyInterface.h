#pragma once

#include <BWAPI.h>
#include <map>
#include <unordered_set>

struct UnitProfile
{
	BWAPI::UnitType type;
	BWAPI::Unit unit;
	BWAPI::Position position;
	int id;

	inline bool operator==(const UnitProfile& lhs) const { return id == lhs.id; }

	struct HashFunction
	{
		inline size_t operator()(const UnitProfile& profile) const
		{
			return (size_t)profile.id;
		}
	};
};

typedef std::unordered_set<UnitProfile, UnitProfile::HashFunction> profile_set;

class ArmyInterface
{
protected:
	std::map<BWAPI::UnitType, int> m_unitCounts;
	profile_set m_buildings;
	profile_set m_units;

	void onChange(BWAPI::UnitType type, bool add);

public:
	virtual ~ArmyInterface() {}
	inline const profile_set& units() { return m_units; }
	inline const profile_set& buildings() { return m_buildings; }

	void add(BWAPI::Unit unit);
	void remove(BWAPI::Unit unit);

	void addUnit(BWAPI::Unit unit);
	void addBuilding(BWAPI::Unit building);

	void removeUnit(BWAPI::Unit unit);
	void removeBuilding(BWAPI::Unit building);

	virtual const BWAPI::Unitset Bases() = 0;

	inline virtual const int drone() { return 0; }
	inline virtual const int overlord() { return 0; }
	inline virtual const int zergling() { return 0; }
	inline virtual const int hydralisk() { return 0; }
	inline virtual const int lurker() { return 0; }
	inline virtual const int scourge() { return 0; }
	inline virtual const int mutalisk() { return 0; }
	inline virtual const int guardian() { return 0; }
	inline virtual const int devourer() { return 0; }
	inline virtual const int queen() { return 0; }
	inline virtual const int ultralisk() { return 0; }
	inline virtual const int defiler() { return 0; }

	inline virtual const int extractor() { return 0; }
	inline virtual const int hatchery() { return 0; }
	inline virtual const int lair() { return 0; }
	inline virtual const int hive() { return 0; }
	inline virtual const int spawning_pool() { return 0; }
	inline virtual const int hypralisk_den() { return 0; }
	inline virtual const int queens_nest() { return 0; }
	inline virtual const int spire() { return 0; }
	inline virtual const int defiler_mound() { return 0; }
	inline virtual const int nydus_canal() { return 0; }
	inline virtual const int ultralisk_cavern() { return 0; }
	inline virtual const int greater_spire() { return 0; }
	inline virtual const int sunken_colony() { return 0; }
	inline virtual const int spore_colony() { return 0; }
	inline virtual const int creep_colony() { return 0; }
	inline virtual const int evolution_chamber() { return 0; }

	inline virtual const int probe() { return 0; }
	inline virtual const int zealot() { return 0; }
	inline virtual const int dragoon() { return 0; }
	inline virtual const int high_templar() { return 0; }
	inline virtual const int dark_templar() { return 0; }
	inline virtual const int shuttle() { return 0; }
	inline virtual const int reaver() { return 0; }
	inline virtual const int observer() { return 0; }
	inline virtual const int scout() { return 0; }
	inline virtual const int corsair() { return 0; }
	inline virtual const int arbiter() { return 0; }
	inline virtual const int carrier() { return 0; }
	inline virtual const int archon() { return 0; }
	inline virtual const int dark_archon() { return 0; }

	inline virtual const int pylon() { return 0; }
	inline virtual const int nexus() { return 0; }
	inline virtual const int assimilator() { return 0; }
	inline virtual const int gateway() { return 0; }
	inline virtual const int forge() { return 0; }
	inline virtual const int shield_battery() { return 0; }
	inline virtual const int cybernetics_core() { return 0; }
	inline virtual const int photon_cannon() { return 0; }
	inline virtual const int citadel_of_arun() { return 0; }
	inline virtual const int robotics_facility() { return 0; }
	inline virtual const int stargate() { return 0; }
	inline virtual const int templar_archives() { return 0; }
	inline virtual const int robotics_support_bay() { return 0; }
	inline virtual const int observatory() { return 0; }
	inline virtual const int fleet_beacon() { return 0; }
	inline virtual const int arbiter_tribunal() { return 0; }
};
