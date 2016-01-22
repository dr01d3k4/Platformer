#pragma once

#include "../engine/System.h"
#include <SFML/Graphics.hpp>


class Game;

class MovementSystem : public System {
public:
	MovementSystem(const Game& game) : System(game) {}

	void update(sf::Time deltaTime);

	SystemType getType() const {
		return MovementSystemType;
	}
};