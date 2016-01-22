#include "System.h"


std::string systemTypeToString(SystemType systemType) {
	switch (systemType) {
		case RenderSystemType:
			return "RenderSystemType";
		case MovementSystemType:
			return "MovementSystemType";
	}
	return "";
}