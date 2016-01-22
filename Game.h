#pragma once

#include <SFML/Graphics.hpp>
#include "engine/EntityManager.h"
#include "engine/SystemManager.h"

#include "system/RenderSystem.h"
#include "system/MovementSystem.h"
#include "engine/System.h"



class Game {
public:
	Game(sf::RenderWindow& renderWindow)
		: _renderWindow(renderWindow)
		/*, view{sf::FloatRect{0, 0, windowWidth, windowHeight}}*/ {
		// _systemManager.addSystem(0, new RenderSystem(*this));
		// _systemManager.addSystem(1, new RenderSystem(*this));
		_systemManager.addSystem(2, new RenderSystem(*this));
		_systemManager.addSystem(1, new MovementSystem(*this));

		_systemManager.printSystems();
	}

	void update(sf::Time deltaTime) {
		// TODO: Iterate through system manager, call system.update(deltaTime)
		for (int i = 0, l = _systemManager.getSystemCount(); i < l; i += 1) {
			System* system = _systemManager.getSystemAt(i);
			if (nullptr == system) {
				std::cout << "System at index " << i << " is nullptr" << std::endl;
				continue;
			}
			std::cout << "System at index " << i << " has type " << systemTypeToString(system->getType()) << std::endl;
			system->update(deltaTime);
		}
	}

private:
	sf::RenderWindow& _renderWindow;
	sf::View view;

	EntityManager _entityManager;
	SystemManager _systemManager;
};