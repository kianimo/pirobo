#include <iostream>
#include "sensors/vision.hpp"
#include "actors/DirectionMovement.h"

int main(void) {
	static DirectionMovement mov;
	std::cout << mov.getCommand("north") << std::endl;
	std::cout << mov.getCommand("west") << std::endl;

	return 0;
}
