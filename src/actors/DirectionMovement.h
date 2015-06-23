/*
 * DirectionMovement.h
 *
 *  Created on: 16.06.2015
 *      Author: christian
 */

#include <string>
#ifndef SRC_DIRECTIONMOVEMENT_H_
#define SRC_DIRECTIONMOVEMENT_H_

namespace sensors {
	class VisibleExits;
}

class DirectionMovement {
public:
	DirectionMovement();
	virtual ~DirectionMovement();
	std::string getCommand(const std::string &command);
private:
	std::string move(int cardinalDirection);
	std::string getCardinalExits(const sensors::VisibleExits &exits);

};

#endif /* SRC_DIRECTIONMOVEMENT_H_ */
