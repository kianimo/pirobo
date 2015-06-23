/*
 * DirectionMovement.cpp
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#include "DirectionMovement.h"
#include "MotorMovement.h"
#include "../sensors/vision.hpp"
#include <math.h>
#include <stdlib.h>

static MotorMovement *motor = new MotorMovement();
int currentDirection;
static int const NORTH = 0;
static int const EAST = 90;
static int const SOUTH = 180;
static int const WEST = 270;
static sensors::Camera camera;
const static std::string exit_strings[] = { "north", "east", "south", "west" };

DirectionMovement::DirectionMovement() {
	// TODO Auto-generated constructor stub
	currentDirection = NORTH;

}

DirectionMovement::~DirectionMovement() {
	// TODO Auto-generated destructor stub
}

std::string DirectionMovement::move(int cardinalDirection){
	int movementAngle = 0;
	movementAngle = cardinalDirection - currentDirection;
	if (abs(movementAngle) > 180){
		movementAngle = (movementAngle - 180) * (-1);
	}
	motor->turn(movementAngle);
	motor->moveForward(70);

	sensors::VisibleExits exits = camera.detectExits();
	std::cout << exits << std::endl;

	motor->moveForward(30);

	currentDirection = cardinalDirection;

	return getCardinalExits(exits);
}

std::string DirectionMovement::getCardinalExits(const sensors::VisibleExits &exits) {
	int offset;
	switch(currentDirection) {
	case EAST: offset=1; break;
	case SOUTH: offset=2; break;
	case WEST: offset=3; break;
	case NORTH:
	default: offset=0;
	}

	std::string result;
	result += (exits.left ? exit_strings[((3+offset)%4)]+":" : "");
	result += (exits.front ? exit_strings[offset]+":" : "");
	result += (exits.right ? exit_strings[((1+offset)%4)]+":" : "");
	result += (exits.back ? exit_strings[((2+offset)%4)] : ""); //Back gibt es immer!
	return result;
}

std::string DirectionMovement::getCommand(const std::string &command){
	std::string exit_string;
	if("north" == command){
		exit_string = DirectionMovement::move(NORTH);
	}else if("east" == command){
		exit_string = DirectionMovement::move(EAST);
	}else if("south" == command){
		exit_string = DirectionMovement::move(SOUTH);
	}else if("west" == command){
		exit_string = DirectionMovement::move(WEST);
	};
	return exit_string;
};

