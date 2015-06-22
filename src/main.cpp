#include <iostream>
#include "sensors/vision.hpp"
#include "actors/DirectionMovement.h"

int main(void) {
	sensors::Camera camera;
	sensors::VisibleExits exits = camera.detectExits();
	std::cout << exits << std::endl;
	return 0;
}
