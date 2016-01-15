#include "Component.h"


std::string componentTypeToString(ComponentType componentType) {
	switch (componentType) {
		case PositionComponentType:
			return "PositionComponentType";
		case MovementComponentType:
			return "MovementComponentType";
	}
	return "";
}