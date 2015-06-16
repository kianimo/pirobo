#include "vision.hpp"

#include <opencv/highgui.h>
#include <vector>
#include <chrono>

namespace sensors {

VisibleExits Camera::detectExits() {
	using namespace cv;
	using namespace std::chrono;
	VideoCapture captureDevice {0}; // open the default camera
	captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if(!captureDevice.isOpened()) throw string("Kamera nicht gefunden!");
	namedWindow("DebugDisplay", 1);

	while(true) {
		milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		captureDevice >> img_original;
		cvtColor(img_original, img_processed, CV_BGR2GRAY);
		GaussianBlur(img_processed, img_processed, Size(3,3), 2, 2 );
		Mat grey;
		threshold(img_processed, img_processed, 50, 255, CV_THRESH_BINARY_INV);
		img_processed.copyTo(grey);
		Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
		Mat img_eroded, img_tmp;
		Mat img_skel(img_processed.rows, img_processed.cols, 0, Scalar(0, 0));
		Mat img_processed_copy;
		img_processed.copyTo(img_processed_copy);
		while(true) {
			erode(img_processed_copy, img_eroded, element);
			dilate(img_eroded, img_tmp, element);
			subtract(img_processed_copy, img_tmp, img_tmp);
			bitwise_or(img_skel, img_tmp, img_skel);
			img_eroded.copyTo(img_processed_copy);

			if(img_processed_copy.size - countNonZero(img_processed_copy) == img_processed_copy.size) {
				break;
			}
		}

//		vector<Vec4i> lines;
//		HoughLinesP(img_skel, lines, 1, CV_PI/180, 80, 30, 10 );
//		for(size_t i = 0; i < lines.size() && i<10; ++i) {
//			line(img_original,
//					Point(lines[i][0], lines[i][1]),
//					Point(lines[i][2], lines[i][3]),
//					Scalar(0,0,255), 3, 8 );
//		}

		vector<Vec3f> circles;
		HoughCircles(grey, circles, CV_HOUGH_GRADIENT, 1, img_skel.rows/8, 100, 10, 10, 60);
		for(size_t i=0; i < circles.size(); ++i) {
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			circle(img_original, center, cvRound(circles[i][2]), Scalar(0, 255, 0), 3, 8, 0);
		}

		cvtColor(img_skel, img_skel, CV_GRAY2BGR);
		addWeighted(img_original, 0.5, img_skel, 0.5, 0.0, img_processed);
//		subtract(img_processed, img_skel, img_processed);

		std::cout << ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())) - start).count() << std::endl;

//		std::cout << "Ok" << std::endl;
//		waitKey(0);
//		std::cout << "next" << std::endl;
		imshow("DebugDisplay", img_processed);

		if(waitKey(30) >= 0) { break; }
	}
	return VisibleExits {true, false, false};
}

}
