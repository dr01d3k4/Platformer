#include "Game.h"

#include "system/RenderSystem.h"
#include "system/MovementSystem.h"


#include "component/PositionComponent.h"



int createBasicEntity(EntityManager& entityManager) {
	int id = entityManager.createEntity();
	entityManager.addComponent(id, new PositionComponent{sf::Vector2f{0, 0}});
	return id;
}


Game::Game(sf::RenderWindow& renderWindow) : _renderWindow(renderWindow) {
	_systemManager.addSystem(2, new RenderSystem(*this));
	_systemManager.addSystem(1, new MovementSystem(*this));

	_systemManager.printSystems();
}


void Game::initEntities() {
	createBasicEntity(_entityManager);
}


void Game::update(sf::Time deltaTime) {
	// TODO: Iterate through system manager, call system.update(deltaTime)
	for (int i = 0, l = _systemManager.getSystemCount(); i < l; i += 1) {
		System* system = _systemManager.getSystemAt(i);
		if (nullptr == system) {
			std::cout << "System at index " << i << " is nullptr" << std::endl;
			continue;
		}
		// std::cout << "System at index " << i << " has type " << systemTypeToString(system->getType()) << std::endl;
		system->update(deltaTime);
	}
}