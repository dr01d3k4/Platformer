#include "SystemManager.h"
#include <iostream>


SystemManager::SystemManager() {
}


SystemManager::~SystemManager() {
	_systems.erase(_systems.begin(), _systems.end());
}


void SystemManager::addSystem(int priority, System* system) {
	SystemType systemType = system->getType();
	// std::cout << "Adding with priority " << priority << "; type " << systemTypeToString(systemType) << std::endl;

	int index = 0;
	int addIndex = -1;
	int removeIndex = -1;

	for (auto& e : _systems) {
		// std::cout << "Looking at element index " << index << "; priority " << e.first << std::endl;
		if ((addIndex < 0) && (priority < e.first)) {
			// std::cout << "Adding here" << std::endl;
			addIndex = index;
		}

		if (e.second->getType() == systemType) {
			removeIndex = index;
		}
	
		index += 1;
	}

	// std::cout << "Add index: " << addIndex << "; ";
	// std::cout << "Remove index: " << removeIndex << std::endl;

	if (addIndex < 0) {
		addIndex = index;
	}


	if (removeIndex >= 0) {
		// std::cout << "Going to remove at index " << removeIndex << std::endl;
		// std::cout << "Systems list is currently: " << std::endl;
		// printSystems();
		// std::cout << "Removing" << std::endl;
		_systems.erase(_systems.begin() + removeIndex + 1);
		// std::cout << "Finished removing" << std::endl;
		
		addIndex -= 1;

	}
	// std::cout << "Adding at index " << addIndex << std::endl;
	_systems.insert(_systems.begin() + addIndex, std::make_pair(priority, std::unique_ptr<System>(system)));
	
	// std::cout << "Added at index " << addIndex << std::endl;
	// std::cout << "Systems list is currently: " << std::endl;
	// printSystems();
	// std::cout << std::endl << std::endl;
}


void SystemManager::printSystems() const {
	std::cout << "Printing systems" << std::endl;
	if (_systems.size() == 0) {
		std::cout << "\t" << "Systems list is empty" << std::endl;
		return;
	}
	for (auto& e : _systems) {
		int priority = e.first;
		const SystemPtr& s = e.second;
		std::cout << "\t" << priority << ": " << systemTypeToString(s->getType()) << std::endl;
	}
}


System* SystemManager::getSystemAt(int index) const {
	if ((index < 0) || (index >= _systems.size())) {
		return nullptr;
	}
	return _systems[index].second.get();
}