#pragma once

#include "../engine/System.h"
#include <SFML/Graphics.hpp>


class Game;

class RenderSystem : public System {
public:
	RenderSystem(const Game& game) : System(game) {}

	void update(sf::Time deltaTime);

	SystemType getType() const {
		return RenderSystemType;
	}
};