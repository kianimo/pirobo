#include "vision.hpp"

#include <opencv/highgui.h>
#include <vector>
#include <chrono>
//#include <unistd.h>

namespace sensors {
std::ostream &operator<<(std::ostream &os, const VisibleExits &exits) {
  return (os << "Exits: "
		  	 << (exits.left ? "L" : "") << " "
			 << (exits.front ? "F" : "") << " "
			 << (exits.right ? "R" : "")
		  );
}

VisibleExits VisibleExits::operator|(const VisibleExits &rhs) {
	VisibleExits result { left||rhs.left, front||rhs.front, right||rhs.right };
	return result;
}


VisibleExits Camera::detectExits() {
	using namespace cv;
	using namespace std::chrono;
	VideoCapture captureDevice {0}; // open the default camera
	captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if(!captureDevice.isOpened()) throw string("Kamera nicht gefunden!");
	namedWindow("DebugDisplay", 1);
	int bin_threshold=50;
	int hough_circ_p1=245;
	int hough_circ_p2=27;
	int hough_line_threshold = 80;
	int hough_line_min_length = 30;
	int hough_line_max_gap = 20;
	cvCreateTrackbar("bin_threshold", "DebugDisplay", &bin_threshold, 255,  NULL);//OK tested
	cvCreateTrackbar("hough_circ_p1", "DebugDisplay", &hough_circ_p1, 1000,  NULL);//OK tested
	cvCreateTrackbar("hough_circ_p2", "DebugDisplay", &hough_circ_p2, 200,  NULL);//OK tested
	cvCreateTrackbar("hough_line_threshold", "DebugDisplay", &hough_line_threshold, 500,  NULL);//OK tested
	cvCreateTrackbar("hough_line_min_length", "DebugDisplay", &hough_line_min_length, 100,  NULL);//OK tested
	cvCreateTrackbar("hough_line_max_gap", "DebugDisplay", &hough_line_max_gap, 100,  NULL);//OK tested
	VisibleExits result {false, false, false};

	while(true) {
		Mat grey, canny;
		milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		captureDevice >> img_original;
		GaussianBlur(img_original, img_original, Size(3,3), 2, 2 );
		cvtColor(img_original, img_processed, CV_BGR2GRAY);
//		threshold(img_processed, img_processed, bin_threshold, 255, CV_THRESH_BINARY_INV);
//		img_processed.copyTo(grey);
		img_original.copyTo(canny);
		Canny(img_original, canny, (double)hough_circ_p1/3+1, (double)hough_circ_p1+1, 3);

//		Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
//		Mat img_eroded, img_tmp;
//		Mat img_skel(img_processed.rows, img_processed.cols, 0, Scalar(0, 0));
//		Mat img_processed_copy;
//		img_processed.copyTo(img_processed_copy);
//		while(true) {
//			erode(img_processed_copy, img_eroded, element);
//			dilate(img_eroded, img_tmp, element);
//			subtract(img_processed_copy, img_tmp, img_tmp);
//			bitwise_or(img_skel, img_tmp, img_skel);
//			img_eroded.copyTo(img_processed_copy);
//
//			if(img_processed_copy.size - countNonZero(img_processed_copy) == img_processed_copy.size) {
//				break;
//			}
//		}

		vector<Vec4i> lines;
		HoughLinesP(canny, lines, 1, CV_PI/180, hough_line_threshold, hough_line_min_length, hough_line_max_gap);
		for(size_t i = 0; i < lines.size() && i<10; ++i) {
			line(img_original,
					Point(lines[i][0], lines[i][1]),
					Point(lines[i][2], lines[i][3]),
					Scalar(0,0,255), 3, 8 );
		}

		vector<Vec3f> circles;
		HoughCircles(img_processed, circles, CV_HOUGH_GRADIENT, 1, 24, (double)hough_circ_p1+1, (double)hough_circ_p2+1, 10, 60);
		for(size_t i=0; i < circles.size(); ++i) {
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			circle(img_original, center, cvRound(circles[i][2]), Scalar(0, 255, 0), 3, 8, 0);
		}
		cvtColor(img_processed, img_processed, CV_GRAY2BGR);
		cvtColor(canny, canny, CV_GRAY2BGR);
		addWeighted(img_original, 0.5, img_processed, 0.5, 0.0, img_processed);
		addWeighted(img_processed, 0.5, canny, 0.5, 0.0, img_processed);
//		subtract(img_processed, img_skel, img_processed);

		std::cout << ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())) - start).count() << std::endl;

//		std::cout << "Ok" << std::endl;
//		waitKey(0);
//		std::cout << "next" << std::endl;
		imshow("DebugDisplay", img_processed);
		result = result | detectExitsFromVision(circles, lines);
		std::cout << result << std::endl;

		if(waitKey(30) >= 0) { break; }
	}
	return VisibleExits {true, false, false};
}

VisibleExits Camera::detectExitsFromVision(std::vector<cv::Vec3f> &circles, std::vector<cv::Vec4i> &lines) {
	if (circles.size() <= 0) { return VisibleExits { false, false, false }; }

	using namespace cv;
	using namespace std;

	Vec3f circle = circles[0]; //TODO Eigentlich besten Kreis suchen --> mittigster? Radius?

	bool left = false, front = false, right = false;

	double square_side_length = circle[2] * 3.5;
	Point center(circle[0], circle[1]);

	Point line_start, line_end;
	for (unsigned int i = 0; i < lines.size(); ++i)
	{
		line_start = Point(lines[i][0], lines[i][1]);
		line_end = Point(lines[i][2], lines[i][3]);

		Point &point_in_square = line_start;
		Point &point_out_of_square = line_end;

		if (isPointInsideSquare(line_end, center, square_side_length))
		{
			Point temp = line_start;
			point_in_square = line_end;
			point_out_of_square = temp;
		}
		else if (!isPointInsideSquare(line_start, center, square_side_length))
			continue;

		if ((point_out_of_square.x) < (center.x - square_side_length / 2))
		{
			left = true;
		}
		else if (point_out_of_square.x > (center.x + square_side_length / 2))
		{
			right = true;
		}
		else if (point_out_of_square.y < (center.y - square_side_length / 2))
		{
			front = true;
		}

	}

	std::cout << "left: " << left << "\tfront: "<< front << "\tright: " << right << std::endl;
	return VisibleExits(left, front, right);
}

bool Camera::isPointInsideSquare(cv::Point &point, cv::Point &square_center, double square_side_length) {
	if (point.x > (square_center.x - square_side_length / 2)
			&& point.x<(square_center.x + square_side_length / 2)
			&& point.y>(square_center.y - square_side_length / 2)
			&& point.y < (square_center.y + square_side_length / 2))
		{ return true; }
	return false;
}

}
