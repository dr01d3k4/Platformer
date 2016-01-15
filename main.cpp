#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "TileMap.h"
#include "engine/EntityManager.h"
#include "math.h"


const int windowWidth = 800;
const int windowHeight = 600;
const std::string windowTitle = "Tile Map";


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


int main() {
	sf::RenderWindow window{sf::VideoMode{windowWidth, windowHeight},
		windowTitle};
	sf::View view{sf::FloatRect{0, 0, windowWidth, windowHeight}};

	TileMap tileMap;
	if (!tileMap.load("assets/tiles.png", sf::Vector2u(64, 64), map, mapWidth, mapHeight)) {
		return -1;
	}

	EntityManager entityManager;

	int playerId = entityManager.createEntity();
	std::cout << "Player ID: " << playerId << std::endl;

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
	return 0;
}