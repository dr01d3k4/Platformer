#pragma once

#include <SFML/Graphics.hpp>

class Game;

class System {
public:
	System(Game& game) : _game{game};

	virtual void update(sf::Time deltaTime) = 0;

protected:
	Game& _game;
};