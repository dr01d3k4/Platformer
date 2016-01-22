#pragma once

#include <SFML/Graphics.hpp>

class Game;

enum SystemType {
	RenderSystemType,
	MovementSystemType
};


std::string systemTypeToString(SystemType);


class System {
public:
	System(const Game& game) : _game(game) {}

	virtual void update(sf::Time deltaTime) = 0;

	virtual SystemType getType() const = 0;

	// EntityManager& getEntityManager() {
	// 	return _game.getEntityManager();
	// }

protected:
	const Game& _game;
};