/*
 * MotorMovement.cpp
 */

#include "MotorMovement.h"
#include "stdio.h"
#include "stdlib.h"
#include <wiringPi.h>
#include <exception>

const int left_motor_channel_map[4] = {2, 3, 4, 17};
const int right_motor_channel_map[4] = {18, 23, 24, 25};
const int step_map[8][4] = {
	{0, 0, 0, 1},
	{0, 0, 1, 1},
	{0, 0, 1, 0},
	{0, 1, 1, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 1},
};
int left_current_step = 0;
int right_current_step = 0;
const int steps = 8;

MotorMovement::MotorMovement() {
	try {
		if(wiringPiSetupGpio() == -1) { throw 1; }
	} catch (int e) {
	}
	pinMode(left_motor_channel_map[0], OUTPUT);
	pinMode(left_motor_channel_map[1], OUTPUT);
	pinMode(left_motor_channel_map[2], OUTPUT);
	pinMode(left_motor_channel_map[3], OUTPUT);
	pinMode(right_motor_channel_map[0], OUTPUT);
	pinMode(right_motor_channel_map[1], OUTPUT);
	pinMode(right_motor_channel_map[2], OUTPUT);
	pinMode(right_motor_channel_map[3], OUTPUT);
	digitalWrite(left_motor_channel_map[0], 0);
	digitalWrite(left_motor_channel_map[1], 0);
	digitalWrite(left_motor_channel_map[2], 0);
	digitalWrite(left_motor_channel_map[3], 0);
	digitalWrite(right_motor_channel_map[0], 0);
	digitalWrite(right_motor_channel_map[1], 0);
	digitalWrite(right_motor_channel_map[2], 0);
	digitalWrite(right_motor_channel_map[3], 0);
}

MotorMovement::~MotorMovement() {
	// TODO Auto-generated destructor stub
}

void move_left_stepper(int pos) {
	for(int i=0; i<4; i++) {
		digitalWrite(left_motor_channel_map[i], step_map[pos][i]);
	}
}

void move_right_stepper(int pos) {
	for(int i=0; i<4; i++) {
		digitalWrite(right_motor_channel_map[i], step_map[pos][i]);
	}
}

// step the left motor.  1 for clockwise,  -1 for counter-clockwise
void left_step(int dir) {
	left_current_step = (left_current_step+dir+steps) % steps;
	move_left_stepper(left_current_step);
}

// step the left motor.  1 for clockwise,  -1 for counter-clockwise
void right_step(int dir) {
	right_current_step = (right_current_step+dir+steps) % steps;
	move_right_stepper(right_current_step);
}

void resetGPIO(void){
	digitalWrite(left_motor_channel_map[0], 0);
	digitalWrite(left_motor_channel_map[1], 0);
	digitalWrite(left_motor_channel_map[2], 0);
	digitalWrite(left_motor_channel_map[3], 0);
	digitalWrite(right_motor_channel_map[0], 0);
	digitalWrite(right_motor_channel_map[1], 0);
	digitalWrite(right_motor_channel_map[2], 0);
	digitalWrite(right_motor_channel_map[3], 0);
}

void MotorMovement::moveForward(int discance){
	int steps = discance *20;
	for(int i=0; i<steps; ++i) {
		left_step(1);
		right_step(-1);
		delayMicroseconds(2000);
	}
	resetGPIO();
}

void MotorMovement::moveBackward(int discance){
	int steps = discance *20;
	for(int i=0; i<steps; ++i) {
		left_step(-1);
		right_step(1);
		delayMicroseconds(2000);
	}
	resetGPIO();
}

void MotorMovement::turn(int angle){
	int ldir = 0;
	int rdir = 0;
	if(0 > angle){
		ldir = -1;
		rdir = -1;
	}
	else{
		ldir = 1;
		rdir = 1;
	}
	int count = abs(angle)*25.3;
	for(int i=0; i<count; ++i) {
			left_step(ldir);
			right_step(rdir);
			delayMicroseconds(2000);
		}
	resetGPIO();
}





