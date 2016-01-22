#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include "System.h"


typedef std::unique_ptr<System> SystemPtr;
typedef std::pair<int, SystemPtr> SystemPair;
typedef std::vector<SystemPair> OrderedSystemList;


class SystemManager {
public:
	SystemManager();
	~SystemManager();

	void addSystem(int priority, System* system);

	void printSystems() const;

	System* getSystemAt(int index) const;

	int getSystemCount() const {
		return _systems.size();
	}
private:
	OrderedSystemList _systems;
};