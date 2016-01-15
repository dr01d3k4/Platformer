#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../engine/Component.h"


class MovementComponent : public Component {
public:
	sf::Vector2f _velocity;


	MovementComponent(sf::Vector2f velocity) : _velocity{velocity} {
		std::cout << "Movement component constructor" << std::endl;
	}

	MovementComponent(const MovementComponent&) = default;

	MovementComponent(MovementComponent&&) = default;

	~MovementComponent() {
		std::cout << "Movement component destructor" << std::endl;
	}

	ComponentType getType() const {
		return MovementComponentType;
	}
};