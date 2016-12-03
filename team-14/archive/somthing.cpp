/*
 * Main.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: lucky
 */

#include <opencv/cv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int, char**) {
    VideoCapture U("/home/lucky/Videos/CarTraffic00.mp4");
    VideoCapture R("/home/lucky/Videos/CarTraffic01.mp4");
    VideoCapture D("/home/lucky/Videos/CarTraffic02.mp4");
    VideoCapture L("/home/lucky/Videos/CarTraffic03.mp4");
    VideoCapture PU("/home/lucky/Videos/CarTraffic04.mp4");
    VideoCapture PR("/home/lucky/Videos/CarTraffic05.mp4");
    VideoCapture PD("/home/lucky/Videos/CarTraffic06.mp4");
    VideoCapture PL("/home/lucky/Videos/CarTraffic07.mp4");
    if (!U.isOpened())  // check if we succeeded
        return -1;




    while (true) {
        Mat frame[8];
        U >> frame[0];
        R >> frame[1];
        D >> frame[2];
        L >> frame[3];
        PU >> frame[4];
        PR >> frame[5];
        PD >> frame[6];
        PL >> frame[7];
        imshow("U", frame[0]);
        if (waitKey(30) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;

}
