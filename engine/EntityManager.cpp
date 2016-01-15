#include "EntityManager.h"


EntityManager::EntityManager() : nextEntityId{0} {}


int EntityManager::createEntity() {
	int id = nextEntityId;
	nextEntityId += 1;
	entities.insert(id);
	return id;
}


