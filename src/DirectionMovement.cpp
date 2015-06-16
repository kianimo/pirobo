/*
 * DirectionMovement.cpp
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#include "DirectionMovement.h"
#include "MotorMovement.h"
#include "math.h"

static MotorMovement *motor = new MotorMovement();
int currentDirection;

DirectionMovement::DirectionMovement() {
	// TODO Auto-generated constructor stub
	currentDirection = NORTH;

}

DirectionMovement::~DirectionMovement() {
	// TODO Auto-generated destructor stub
}

void move(int cardinalDirection){
	int movementAngle = 0;
	movementAngle = cardinalDirection - currentDirection;
	if (abs(movementAngle) > 180){
		movementAngle = (movementAngle - 180) * (-1);
	}
	motor->turn(movementAngle);
	motor->moveForward(100);
	currentDirection = cardinalDirection;

}

void getCommand(std::string command){
	if("north" == command){
		move(NORTH);
	}else if("east" == command){
		move(EAST);
	}else if("south" == command){
		move(SOUTH);
	}else if("west" == command){
		move(WEST);
	};
};

