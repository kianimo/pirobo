/*
 * DirectionMovement.cpp
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#include "DirectionMovement.h"
#include "MotorMovement.h"
#include <math.h>
#include <stdlib.h>

static MotorMovement *motor = new MotorMovement();
int currentDirection;
static int const NORTH = 0;
static int const EAST = 90;
static int const SOUTH = 180;
static int const WEST = 270;

DirectionMovement::DirectionMovement() {
	// TODO Auto-generated constructor stub
	currentDirection = NORTH;

}

DirectionMovement::~DirectionMovement() {
	// TODO Auto-generated destructor stub
}

void DirectionMovement::move(int cardinalDirection){
	int movementAngle = 0;
	movementAngle = cardinalDirection - currentDirection;
	if (abs(movementAngle) > 180){
		movementAngle = (movementAngle - 180) * (-1);
	}
	motor->turn(movementAngle);
	motor->moveForward(100);
	currentDirection = cardinalDirection;

}

void DirectionMovement::getCommand(const std::string &command){
	if("north" == command){
		DirectionMovement::move(NORTH);
	}else if("east" == command){
		DirectionMovement::move(EAST);
	}else if("south" == command){
		DirectionMovement::move(SOUTH);
	}else if("west" == command){
		DirectionMovement::move(WEST);
	};
};

