#pragma once
#include <iostream>


enum ComponentType {
	PositionComponentType,
	MovementComponentType
};


std::string componentTypeToString(ComponentType);


class Component {
public:
	virtual ~Component() {
		std::cout << "Component base destructor" << std::endl;
	}

	virtual ComponentType getType() const = 0;
};