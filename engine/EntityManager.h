#pragma once

#include <unordered_map>
#include <set>
#include <memory>
#include "Component.h"


// http://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
// struct EnumClassHash {
// 	template <typename T>
// 	std::size_t operator()(T t) const {
// 		return static_cast<std::size_t>(t);
// 	}
// };

typedef std::unique_ptr<Component> ComponentPtr;
typedef std::unordered_map<int, ComponentPtr> InnerComponentMap;
typedef std::unordered_map<ComponentType, InnerComponentMap, std::hash<int>> ComponentMap;

class EntityManager {
public:
	EntityManager();

	~EntityManager();

	int createEntity();
	
	void addComponent(int entity, Component* component);

	Component* getComponent(int entity, ComponentType componentType);

	// TODO: Should this be const and/or reference?
	// TODO: Constitent parameter order

	// int createEntityWithTag(EntityTagManager& entityTagManager, std::string tag)

	// int removeEntity(int entity);

	// int removeEntityWithTag(int entity, EntityTagManager entityTagManager);


	// TODO: Should remove return a pointer because it could be null
	// Component* removeComponent(int entity, ComponentType componentType);

	// bool entityHasComponent(int entity, ComponentType componentType);

	// std::unordered_map<ComponentType, Component&> getEntityComponents(int entity) const;

	// std::vector<Component&> getAllComponentsOfType(ComponentType componentType) const;

	// std::set<int> getEntitiesWithComponent(ComponentType componentType) const;

	// TODO: Import initializer_list
	// std::set<int> getEntitiesWithComponents(std::initializer_list<ComponentType> componentTypes) const;

	// TODO: Should this be const?
	std::set<int> getEntities() const {
		return _entities;
	}


	int getEntityCount() const {
		return _entities.size();
	}


	bool entityExists(int entity) const {
		return (_entities.find(entity) != _entities.end());
	}

	void clear() {
		_entities.clear();
		_componentsMap.clear();
		_nextEntityId = 0;
	}

private:
	std::set<int> _entities;
	ComponentMap _componentsMap;
	int _nextEntityId;
};