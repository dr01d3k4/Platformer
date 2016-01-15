#pragma once

#include <unordered_map>
#include <set>
#include "Component.h"


// http://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
struct EnumClassHash {
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};


class EntityManager {
public:
	EntityManager();

	int createEntity();

	// int createEntityWithTag(EntityTagManager& entityTagManager, std::string tag)

private:
	std::set<int> entities;
	std::unordered_map<ComponentType, std::unordered_map<int, Component*>, EnumClassHash> componentsMap;
	int nextEntityId;
};