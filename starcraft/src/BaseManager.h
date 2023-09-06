#pragma once

#include "Base.h"

#include <map>

class BaseManager
{
	std::map<int, Base> m_map;
	std::vector<int> m_baseIds;

	void remove(int id);
	void update();

public:
	BaseManager() {}

	void addBase(BWAPI::Unit unit);
	void assignWorkers();
	void assignWorker(BWAPI::Unit unit);
	Base& getBase(int index);

	Base& getMain();
	void onFrame();
};