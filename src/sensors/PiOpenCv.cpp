//============================================================================
// Name        : OpenCVHoughCircle.cpp
// Author      : Ruediger Knoerig
// Version     :
// Copyright   : GPL
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include <vector>

using namespace std;
using namespace cv;
// Test
int mainx() {
	try {
		VideoCapture cap(0); // open the default camera
		cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
		cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
		if (!cap.isOpened()) throw string("Konnte keine Kamera aktivieren!");
		Mat bild,graustufen;
		namedWindow("Anzeige", 1);
		for (;;) {
			cap >> bild; // get a new frame from camera
			cvtColor(bild, graustufen, CV_BGR2GRAY);
			GaussianBlur( graustufen, graustufen,Size(3,3), 2, 2 );
			Canny(graustufen,graustufen, 50, 200, 3 );
			vector<Vec4i> linien;
			HoughLinesP(graustufen, linien, 1, CV_PI/180, 80, 30, 10 );
			for( size_t i = 0; i < linien.size(); i++ )
			  {
			    line(bild, Point(linien[i][0], linien[i][1]),
				  Point(linien[i][2], linien[i][3]), Scalar(0,0,255), 3, 8 );
			  }
			imshow("Anzeige",bild);
			if (waitKey(30) >= 0)
				break;
		}
		vector<int> attribute(2);
		attribute[0] = CV_IMWRITE_JPEG_QUALITY;
		attribute[1] = 90;
		imwrite(string("Bild.jpg"), bild, attribute);
		return 0;
	} catch (string &msg) {
		cerr << "Ein Fehler ist aufgetreten!" << endl << msg << endl;
		return -1;
	}
}


//#include <iostream>
//#include <raspicam/raspicam_still_cv.h>
//#include <opencv/cv.h>
//#include <opencv/highgui.h>
//
//using namespace std;
//
//int main ( int argc,char **argv ) {
//    raspicam::RaspiCam_Still_Cv Camera;
//    cv::Mat image;
////    Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//    cout<<"Opening Camera..."<<endl;
//    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);
//    Camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//    Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
//    Camera.set(CV_CAP_PROP_EXPOSURE, 30);
//    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
//	Camera.grab();
//	Camera.retrieve (image);
//    cout<<"Stop camera..."<<endl;
//    Camera.release();
//    cv::imwrite("raspicam_cv_image.jpg",image);
//    cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
//}



//#include <iostream>
//#include <string>
//#include <vector>
//#include <opencv/cv.h>
//#include <opencv/highgui.h>
//
//using namespace std;
//using namespace cv;
//
//int main( int argc, char** argv ) {
//	try {
//		Mat bild,graustufen;
//
//		  if (argc != 2) {
//			printf("Bilddatei angeben!\n");
//			return -1;
//		  }
//		  bild = imread( argv[1], 1 );
//
//		  if(!bild.data) {
//			printf("No image data \n");
//			return -1;
//		  }
//
//		namedWindow("Anzeige", 1);
////		for (;;) {
//			cvtColor(bild, graustufen, CV_BGR2GRAY);
////			GaussianBlur( graustufen, graustufen,Size(3,3), 2, 2 );
//			Canny(graustufen,graustufen, 50, 200, 3 );
//			vector<Vec4i> linien;
//			HoughLinesP(graustufen, linien, 1, CV_PI/180, 20, 30, 10 );
//			for( size_t i = 0; i < linien.size(); i++ )
//			  {
//			    line(bild, Point(linien[i][0], linien[i][1]),
//				  Point(linien[i][2], linien[i][3]), Scalar(0,0,255), 3, 8 );
//			  }
//			imshow("Anzeige",bild);
//			waitKey(0);
////			if (waitKey(30) >= 0)
////				break;
////		}
//		vector<int> attribute(2);
//		attribute[0] = CV_IMWRITE_JPEG_QUALITY;
//		attribute[1] = 90;
//		imwrite(string("Bild.jpg"), bild, attribute);
//		return 0;
//	} catch (string msg) {
//		cerr << "Ein Fehler ist aufgetreten!" << endl << msg << endl;
//		return -1;
//	}
//
////  Mat image;
////
////  if (argc != 2) {
////	printf("Bilddatei angeben!\n");
////	return -1;
////  }
////  image = imread( argv[1], 1 );
////
////  if(!image.data) {
////	printf("No image data \n");
////	return -1;
////  }
////
////
////  namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
////  imshow( "Display Image", image );
////
////  waitKey(0);
////
////  return 0;
//}
