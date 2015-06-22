/*
 * DirectionMovement.h
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#include <string>
#ifndef SRC_DIRECTIONMOVEMENT_H_
#define SRC_DIRECTIONMOVEMENT_H_

class DirectionMovement {
public:
	DirectionMovement();
	virtual ~DirectionMovement();
	void getCommand(const std::string &command);
private:
	void move(int cardinalDirection);

};

#endif /* SRC_DIRECTIONMOVEMENT_H_ */
