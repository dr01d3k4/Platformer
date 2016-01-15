#include <iostream>
#include "EntityManager.h"


EntityManager::EntityManager() : _nextEntityId{0} {}


EntityManager::~EntityManager() {
	std::cout << "Entity Manager deconstructor" << std::endl;
	// _componentsMap.erase(_componentsMap.begin(), _componentsMap.end());
	_componentsMap.clear();
}


int EntityManager::createEntity() {
	int id = _nextEntityId;
	_nextEntityId += 1;
	_entities.emplace(id);
	return id;
}


void EntityManager::addComponent(int entity, Component* component) {
	std::cout << "Adding component" << std::endl;
	ComponentType componentType = component->getType();
	std::cout << "Component type: " << componentType << "; " << componentTypeToString(componentType) << std::endl;

	// ComponentMap::const_iterator mapIterator = _componentsMap.find(componentType);

	// if (mapIterator == _componentsMap.end()) {
	// 	std::cout << "Map for component type doesn't exist" << std::endl;
	// 	// _componentsMap.insert(ComponentMap::value_type{});
	// } else {
	// 	std::cout << "Map for component type exists" << std::endl;
	// }

	// auto& innerMap = _componentsMap[componentType];
	// InnerComponentMap::const_iterator innerMapIterator = innerMap.find(entity);
	// if (innerMapIterator != innerMap.end()) {
	// 	std::cout << "Entity already exists in inner map" << std::endl;
	// 	innerMap.erase(innerMapIterator);
	// }
	// innerMap.insert(InnerComponentMap::value_type{entity, std::unique_ptr<Component>(component)});

	// std::cout << "Added component" << std::endl;

	_componentsMap[componentType][entity] = std::unique_ptr<Component>(component);
}


Component* EntityManager::getComponent(int entity, ComponentType componentType) {
	ComponentMap::const_iterator mapIterator = _componentsMap.find(componentType);
	if (mapIterator == _componentsMap.end()) {
		std::cout << "No components of type " << componentTypeToString(componentType) << std::endl;
		return nullptr;
	}
	const auto& innerMap = mapIterator->second;

	auto innerMapIterator = innerMap.find(entity);
	if (innerMapIterator == innerMap.end()) {
		std::cout << "No component instance for entity " << entity << std::endl;
		return nullptr;
	}
	const ComponentPtr& componentPtr = innerMapIterator->second;
	return componentPtr.get();

	// uniqueComponentPointer.get()
}	