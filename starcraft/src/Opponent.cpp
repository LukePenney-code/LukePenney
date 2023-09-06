#include "Opponent.h"
#include "Tools.h"

Opponent::Opponent()
{
	m_army = std::make_unique<ZergArmy>();
}

void Opponent::add(BWAPI::Unit unit)
{
	m_army->add(unit);
}

void Opponent::remove(BWAPI::Unit unit)
{
	m_army->remove(unit);
}

void Opponent::onFrame()
{

}

void Opponent::setState(OP_Activity state)
{
	m_state = state;
}