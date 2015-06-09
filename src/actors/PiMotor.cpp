#include "stdio.h"
#include "stdlib.h"
#include <wiringPi.h>


unsigned int delay_us = 1000;
const int motor_channel_map[4] = {2, 3, 4, 17};
//const int motor_channel_map[4] = {18, 23, 24, 25};
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
int current_step = 0;
int steps = 8;

void move_stepper(int pos) {
	for(int i=0; i<4; i++) {
		digitalWrite(motor_channel_map[i], step_map[pos][i]);
	}
}

// step the motor.  1 for clockwise,  -1 for counter-clockwise
void step(int dir) {
	current_step = (current_step+dir+steps) % steps;
	printf("step: %i \n", current_step);
	move_stepper(current_step);
}

//void turn(int deg) {
//	for(int i=0; i<(512.0/360.0)*deg; i++) {
//		cycle();
//	}
//}

int test_motor() {
	if(wiringPiSetupGpio() == -1) { return 1; }
//	for(int i=0;i<3;i++) {
//		pinMode(motor_channel_map[i], OUTPUT);
//		digitalWrite(motor_channel_map[i], 0);
//	}

	pinMode(motor_channel_map[0], OUTPUT);
	pinMode(motor_channel_map[1], OUTPUT);
	pinMode(motor_channel_map[2], OUTPUT);
	pinMode(motor_channel_map[3], OUTPUT);
	digitalWrite(motor_channel_map[0], 0);
	digitalWrite(motor_channel_map[1], 0);
	digitalWrite(motor_channel_map[2], 0);
	digitalWrite(motor_channel_map[3], 0);

	for(int i=0; i<4096; ++i) {
		printf("i: %i \n", i);
		step(1);
		delayMicroseconds(2000);
	}
//	for(int i=0; i<4096; ++i) {
//		printf("i: %i \n", i);
//		step(-1);
//		delayMicroseconds(500);
//	}

	digitalWrite(motor_channel_map[0], 0);
	digitalWrite(motor_channel_map[1], 0);
	digitalWrite(motor_channel_map[2], 0);
	digitalWrite(motor_channel_map[3], 0);

	return 0;
}
