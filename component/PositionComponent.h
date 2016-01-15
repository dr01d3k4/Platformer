#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../engine/Component.h"


class PositionComponent : public Component {
public:
	sf::Vector2f _position;


	PositionComponent(sf::Vector2f position) : _position{position} {
		std::cout << "Position component constructor" << std::endl;
	}

	PositionComponent(const PositionComponent&) = default;

	PositionComponent(PositionComponent&&) = default;

	~PositionComponent() {
		std::cout << "Position component destructor" << std::endl;
	}

	ComponentType getType() const {
		return PositionComponentType;
	}
};