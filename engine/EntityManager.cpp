#include <iostream>
#include <algorithm>
#include "EntityManager.h"


EntityManager::EntityManager() : _nextEntityId{0} {}


EntityManager::~EntityManager() {
	std::cout << "Entity Manager deconstructor" << std::endl;
	_componentsMap.clear();
}


int EntityManager::createEntity() {
	int id = _nextEntityId;
	_nextEntityId += 1;
	_entities.emplace(id);
	return id;
}


void EntityManager::addComponent(int entity, Component* component) {
	// std::cout << "Adding component" << std::endl;
	ComponentType componentType = component->getType();
	// std::cout << "Component type: " << componentType << "; " << componentTypeToString(componentType) << std::endl;

	_componentsMap[componentType][entity] = std::unique_ptr<Component>(component);
}


bool EntityManager::entityHasComponent(int entity, ComponentType componentType) const {
	ComponentMap::const_iterator mapIterator = _componentsMap.find(componentType);
	if (mapIterator == _componentsMap.end()) {
		return false;
	}

	const auto& innerMap = mapIterator->second;
	auto innerMapIterator = innerMap.find(entity);
	if (innerMapIterator == innerMap.end()) {
		return false;
	}

	return true;
}


Component* EntityManager::getComponent(int entity, ComponentType componentType) const {
	ComponentMap::const_iterator mapIterator = _componentsMap.find(componentType);
	if (mapIterator == _componentsMap.end()) {
		return nullptr;
	}

	const auto& innerMap = mapIterator->second;
	auto innerMapIterator = innerMap.find(entity);
	if (innerMapIterator == innerMap.end()) {
		return nullptr;
	}

	const ComponentPtr& componentPtr = innerMapIterator->second;
	return componentPtr.get();
}


std::set<int> EntityManager::getEntitiesWithComponent(ComponentType componentType) const {
	ComponentMap::const_iterator mapIterator = _componentsMap.find(componentType);
	if (mapIterator == _componentsMap.end()) {
		return std::set<int>{};
	}

	const auto& innerMap = mapIterator->second;
	std::set<int> entities;

	for (const auto& kv : innerMap) {
		entities.insert(kv.first);
	}

	return entities;
}


std::set<int> EntityManager::getEntitiesWithComponents(std::initializer_list<ComponentType> componentTypes) const {
	std::set<int> entities = getEntities();

	for (auto& type : componentTypes) {
		std::set<int> newEntities = getEntitiesWithComponent(type);
		std::set<int> intersect;
		std::set_intersection(entities.begin(), entities.end(), newEntities.begin(), newEntities.end(), std::inserter(intersect, intersect.begin()));
		entities = intersect;
	}

	return entities;
}