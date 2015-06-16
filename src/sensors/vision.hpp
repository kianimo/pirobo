#ifndef SRC_SENSORS_VISION_HPP_
#define SRC_SENSORS_VISION_HPP_

#include <opencv/cv.h>

namespace sensors {

class VisibleExits {
public:
	const bool left, right, front, back;

	VisibleExits(const bool left, const bool front, const bool right):
		left {left}, right {right}, front{ front }, back { true } {}
};

class Camera {
public:
	VisibleExits detectExits();
private:
	cv::Mat img_original, img_processed;
};
}

#endif /* SRC_SENSORS_VISION_HPP_ */
