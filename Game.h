#pragma once

#include <SFML/Graphics.hpp>
#include "engine/EntityManager.h"
#include "engine/SystemManager.h"


int createBasicEntity(EntityManager&);

class Game {
public:
	Game(sf::RenderWindow& renderWindow);

	void initEntities();
	void update(sf::Time deltaTime);

	EntityManager& getEntityManager() {
		return _entityManager;
	}

private:
	sf::RenderWindow& _renderWindow;
	sf::View view;

	EntityManager _entityManager;
	SystemManager _systemManager;
};