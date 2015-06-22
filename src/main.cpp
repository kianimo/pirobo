#include <iostream>
#include "sensors/vision.hpp"
#include "actors/DirectionMovement.h"

int main(void) {
	sensors::Camera camera;
	camera.detectExits();
	return 0;
}
