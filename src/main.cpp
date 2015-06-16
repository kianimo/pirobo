#include <iostream>
#include "sensors/vision.hpp"

int main(void) {
	sensors::Camera camera;
	camera.detectExits();
	return 0;
}
