#ifndef SRC_SENSORS_VISION_HPP_
#define SRC_SENSORS_VISION_HPP_

#include <opencv/cv.h>
#include <iostream>

namespace sensors {

class VisibleExits {
public:
	bool left, front, right, back;

	VisibleExits(const bool left, const bool front, const bool right):
		left {left}, front{ front }, right {right}, back { true } {}

	VisibleExits operator|(const VisibleExits &rhs);

	friend std::ostream &operator<<(std::ostream &os, const VisibleExits &exits);
};

class Camera {
public:
	VisibleExits detectExits();
private:
	cv::Mat img_original, img_processed;

	VisibleExits detectExitsFromVision(std::vector<cv::Vec3f> &circles, std::vector<cv::Vec4i> &lines);
	bool isPointInsideSquare(cv::Point &point, cv::Point &square_center, double square_side_length);
};
}

#endif /* SRC_SENSORS_VISION_HPP_ */
