#pragma once

#include <SFML/Graphics.hpp>
#include "engine/EntityManager.h"
#include "engine/SystemManager.h"


class Game {
public:
	Game(sf::RenderWindow& renderWindow)
		: _renderWindow(renderWindow)
		/*, view{sf::FloatRect{0, 0, windowWidth, windowHeight}}*/ {
	}

	void update(sf::Time deltaTime) {
		// TODO: Iterate through system manager, call system.update(deltaTime)
	}

private:
	sf::RenderWindow& _renderWindow;
	sf::View view;

	EntityManager _entityManager;
	SystemManager _systeManager;
};