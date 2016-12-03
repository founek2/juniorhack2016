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
    int *TX;
    int *BX;


public:
    ProcessFrame(Mat def, int TX[], int BX[]) // default constructor
    {

        this->TX = TX;
        this->BX = BX;
        def = forDif(def);
        this->def = def.clone();
    };


    void different(Mat dif,int &number1,int &number2,int &number3 ) {
        Mat input = dif;
        dif = forDif(dif);
        Mat diffImage;
        absdiff(dif, def, diffImage);

        threshold(diffImage, diffImage, 60, 255, CV_THRESH_BINARY);

        RNG rng(12345);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(diffImage, contours, hierarchy, CV_RETR_EXTERNAL,
                     CV_CHAIN_APPROX_NONE, Point(0, 0));


        MyLine shitAround[3];
        for (int j = 0; j < 3; ++j) {
            shitAround[j].setPoint(TX[j], 1, BX[j], input.size().height - 1);
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            line(input, CvPoint(TX[j], 1), CvPoint(BX[j], input.size().height - 1), color, 5, CV_AA);
        }


        vector<vector<Point> > contours_poly(contours.size());
        vector<Rect> boundRect(contours.size());
        vector<Point2f> center(contours.size());
        vector<float> radius(contours.size());
        for (int i = 0; i < contours.size(); i++) {
            approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
            boundRect[i] = boundingRect(Mat(contours_poly[i]));
            minEnclosingCircle(contours_poly[i], center[i], radius[i]);
        }



        for (int i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

            if (shitAround[0].left(center[i].x, center[i].y)) {
                number1++;
            } else if (shitAround[1].left(center[i].x, center[i].y)) {
                number2++;
            } else if (shitAround[2].left(center[i].x, center[i].y)) {
                number3++;
            }

            drawContours(input, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());


            rectangle(input, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
        }

    }

    Mat forDif(Mat without) {
        Mat after;
        cv::inRange(without, Scalar(180, 225, 225), Scalar(255, 255, 255), after);
        cv::GaussianBlur(after, after, cv::Size(81, 81), 100, 100);
        return after;
    }


    class MyLine {
        int ax; int ay; int bx; int by;
        int a;
        int b;
        int d;
    public:
        MyLine() {}

        void setPoint(int ax, int ay, int bx, int by) // default constructor
        {
            this->ax=ax;
            this->ay=ay;
            this->bx=bx;
            this->by=by;
            a=ax-bx;
            b=ay-by;
            d=-a*ax-b*ay;

        };

        bool left(int x, int y) {
           int position = (bx - ax) * (y - ay) - (by - ay) * (x - ax);
            if(position<0){
                return false;
            }else{
                return true;
            }

            return true;
        }

    };


};

static void CrosroadOutput(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,int l){
    cout << " "<<a<<" "<<b<<" "<<c<<" "<<endl;
    cout << l<<" "<<" "<<" "<<" "<<" "<<d<<endl;
    cout << k<<" "<<" "<<" "<<" "<<" "<<e<<endl;
    cout << j<<" "<<" "<<" "<<" "<<" "<<f<<endl;
    cout << " "<<i<<" "<<h<<" "<<g<<" "<<endl;
}


int main(int, char **) {


    VideoCapture first("/home/lucky/Videos/Second.mp4");
    Mat firstFrame;
    first >> firstFrame;
    int TX[3]{1000, 1070, 1140};
    int BX[3]{520, 1000, 1450};
    ProcessFrame u(firstFrame, TX, BX);
    ProcessFrame r(firstFrame, TX, BX);
    ProcessFrame d(firstFrame, TX, BX);
    ProcessFrame l(firstFrame, TX, BX);

    VideoCapture U("/home/lucky/Videos/CarTraffic00.mp4");
    VideoCapture R("/home/lucky/Videos/CarTraffic01.mp4");
    VideoCapture D("/home/lucky/Videos/CarTraffic02.mp4");
    VideoCapture L("/home/lucky/Videos/CarTraffic03.mp4");
    if (!U.isOpened())  // check if we succeeded
        return -1;


    while (true) {

        Mat frame[8];
        U >> frame[0];
        R >> frame[1];
        D >> frame[2];
        L >> frame[3];
        int number1=0;
        int number2=0;
        int number3=0;
        u.different(frame[0],number1,number2,number3);
        imshow("U",frame[0]);
        cout << number1 <<" " << number2 << " " <<number3<<" up"<<endl;

        int number4=0;
        int number5=0;
        int number6=0;
        r.different(frame[1],number4,number5,number6);
        imshow("R",frame[1]);

        cout << number4 <<" " << number5 << " " <<number6<<" right"<<endl;

        int number7=0;
        int number8=0;
        int number9=0;
        d.different(frame[2],number7,number8,number9);
        imshow("D",frame[2]);


        cout << number7 <<" " << number8 << " " <<number9<<" down"<<endl;

        int number10=0;
        int number11=0;
        int number12=0;
        l.different(frame[3],number10,number11,number12);
        imshow("L",frame[3]);
        cout << number10 <<" " << number11 << " " <<number12<<" left"<<endl;

        cout << endl;
        cout << endl;
        cout << endl;
        CrosroadOutput(number1,number2,number3,number4,number5,number6,number7,number8,number9,number10,number11,number12);
        cout << endl;
        cout << endl;
        cout << endl;
        if (waitKey(30) >= 0)
            break;
    }
    return 0;

}

