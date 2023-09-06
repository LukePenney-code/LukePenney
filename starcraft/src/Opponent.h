#pragma once

#include <memory>

#include <BWAPI.h>
#include "ZergArmy.h"

enum class OP_Activity
{
	None,
	Rush,
	Econ,
	Defense,
};

class Opponent
{
	OP_Activity m_state = OP_Activity::None;
	std::unique_ptr<ArmyInterface> m_army;

public:
	Opponent();
	inline const OP_Activity state() { return m_state; }

	void add(BWAPI::Unit unit);
	void remove(BWAPI::Unit unit);

	void onFrame();
	void setState(OP_Activity state);
	inline std::unique_ptr<ArmyInterface>& army() { return m_army; }
};