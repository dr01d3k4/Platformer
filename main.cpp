#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "math.h"
#include "TileMap.h"
#include "engine/EntityManager.h"
#include "engine/Component.h"
#include "component/PositionComponent.h"

// https://github.com/SFML/SFML/wiki/Tutorial%3A-Build-your-SFML-project-with-CMake
// TODO: Use namespaces


const int windowWidth = 800;
const int windowHeight = 600;
const std::string windowTitle = "Platformer";


const int map[] = {
	12, 1, 1, 1, 1, 1, 1, 13,
	3, 48, 48, 48, 48, 48, 48, 3,
	3, 48, 48, 48, 48, 48, 48, 3,
	3, 48, 48, 48, 48, 48, 48, 3,
	3, 48, 48, 48, 48, 48, 48, 3,
	3, 48, 48, 48, 48, 48, 48, 3,
	3, 48, 48, 48, 48, 48, 48, 3,
	14, 1, 1, 1, 1, 1, 1, 15
};


const int mapWidth = 8;
const int mapHeight = 8;


bool handleEvents(sf::Window& window, sf::View& view) {
	sf::Event event;
	bool continueRunning = true;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			continueRunning = false;
		}
		if (event.type == sf::Event::Resized) {
			view.setSize(event.size.width, event.size.height);
		}
	}

	return continueRunning;
}


void updateView(sf::View& view, sf::Time& deltaTime) {
	float dx = 0;
	float dy = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		dx -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dx += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dy -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dy += 1;
	}

	float moveSpeed = 1000;
	float timeSeconds = deltaTime.asSeconds();

	float dd = dx * dx + dy * dy;
	if (dd != 0) {
		dd = sqrt(dd);
		dx /= dd;
		dy /= dd;
	}

	dx *= moveSpeed;
	dy *= moveSpeed;

	view.move(dx * timeSeconds, dy * timeSeconds);
}


int createEntity(EntityManager& entityManager) {
	int id = entityManager.createEntity();
	std::cout << "Entity ID: " << id << std::endl;
	// std::unique_ptr<PositionComponent> position{new PositionComponent{sf::Vector2f{0, 0}}};
	// entityManager.addComponent(id, std::move(position));
	entityManager.addComponent(id, new PositionComponent{sf::Vector2f{(float) id, 4432}});
	return id;
}


int main() {
	sf::RenderWindow window{sf::VideoMode{windowWidth, windowHeight},
		windowTitle};
	sf::View view{sf::FloatRect{0, 0, windowWidth, windowHeight}};

	TileMap tileMap;
	if (!tileMap.load("assets/tiles.png", sf::Vector2u(64, 64), map, mapWidth, mapHeight)) {
		return -1;
	}

	EntityManager entityManager;

	int playerId = createEntity(entityManager);
	std::cout << "Player ID: " << playerId << std::endl;

	std::cout << std::endl;

	int enemyId = createEntity(entityManager);
	std::cout << "Enemy ID: " << enemyId << std::endl;

	std::cout << std::endl;

	std::cout << "Adding new position for player" << std::endl;
	entityManager.addComponent(playerId, new PositionComponent{sf::Vector2f{10, 10}});

	std::cout << std::endl;
	std::cout << "Getting player position" << std::endl;
	PositionComponent* playerPositionComponent = static_cast<PositionComponent*>(entityManager.getComponent(playerId, PositionComponentType));
	if (playerPositionComponent != nullptr) {
		std::cout << "Position: (" << playerPositionComponent->_position.x << ", " << playerPositionComponent->_position.y << ")" << std::endl;
	} else {
		std::cout << "Player has no position component" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Getting Enemy position" << std::endl;
	PositionComponent* enemyPositionComponent = static_cast<PositionComponent*>(entityManager.getComponent(enemyId, PositionComponentType));
	if (enemyPositionComponent != nullptr) {
		std::cout << "Position: (" << enemyPositionComponent->_position.x << ", " << enemyPositionComponent->_position.y << ")" << std::endl;
	} else {
		std::cout << "Enemy has no position" << std::endl;
	}

	// int enemyId = entityManager.createEntity();

	// std::cout << "" << std::endl;
	// PositionComponent playerPosition{sf::Vector2f{0, 0}};
	// PositionComponent enemyPosition{sf::Vector2f{10, 10}};

	// std::cout << "" << std::endl;
	// entityManager.addComponent(playerId, playerPosition);
	// std::cout << "" << std::endl;
	// entityManager.addComponent(enemyId, enemyPosition);

	// Component&& playerPosition = entityManager.addComponent(playerId, PositionComponent{sf::Vector2f{0, 0}});
	// std::cout << "" << std::endl;
	// Component&& enemyPosition = entityManager.addComponent(enemyId, PositionComponent{sf::Vector2f{0, 0}});

	sf::Clock clock;

	bool running = true;
	while (running) {
		running = handleEvents(window, view);

		sf::Time elapsed = clock.restart();

		updateView(view, elapsed);

		window.setView(view);
		window.clear(sf::Color::Black);
		window.draw(tileMap);
		window.display();
	}

	window.close();

	std::cout << std::endl;
	return 0;
}