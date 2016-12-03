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









class ProcessFrame {

    Mat def;
public:
    ProcessFrame(Mat def) // default constructor
    {
        def =forDif(def);
        this->def=def.clone();
    };


    int different(Mat dif){

        dif = forDif(dif);
        imshow("def", def);
        imshow("dif",dif);
        Mat diffImage;
        absdiff(dif, def, diffImage);

         imshow("diferent",diffImage);
        return 0;
    }

    Mat forDif(Mat without){
        Mat after;
        cv::inRange(without, Scalar(180, 225, 225), Scalar(255, 255, 255),after);
        cv::GaussianBlur(after, without, cv::Size(9, 9), 5, 5);
        return after;
    }

};










int main(int, char**) {


   /* if (i > 1) {
        Mat dif;
        absdiff(rgb_out_frame, prev_frame, dif);
        threshold(dif, dif, 60, 255, CV_THRESH_BINARY);
    }*/


    VideoCapture first("/home/lucky/Videos/Second.mp4");
    Mat firstFrame;
    first>>firstFrame;
    imshow("sdfds",firstFrame);
    ProcessFrame a(firstFrame);

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
        a.different(frame[0]);
        if (waitKey(30) >= 0)
            break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;

}

