#pragma once


enum ComponentType {
	PositionComponent,
	MovementComponent
};


class Component {
public:
	virtual ComponentType getType() const = 0;
};