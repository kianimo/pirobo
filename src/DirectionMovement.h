/*
 * DirectionMovement.h
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#ifndef SRC_DIRECTIONMOVEMENT_H_
#define SRC_DIRECTIONMOVEMENT_H_

class DirectionMovement {
public:
	DirectionMovement();
	virtual ~DirectionMovement();
	void getCommand(std::string command);
private:
	static int const NORTH = 0;
	static int const EAST = 90;
	static int const SOUTH = 180;
	static int const WEST = 270;


};

#endif /* SRC_DIRECTIONMOVEMENT_H_ */
