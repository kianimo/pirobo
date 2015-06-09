/*
 * MotorMovement.h
 */

#ifndef SRC_MOTORMOVEMENT_H_
#define SRC_MOTORMOVEMENT_H_

class MotorMovement {
public:
	MotorMovement();
	virtual ~MotorMovement();
	void moveForward(int discance);
	void moveBackward(int discance);
	void turn(int angle);
};

#endif /* SRC_MOTORMOVEMENT_H_ */
