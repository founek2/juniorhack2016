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

/*

class Crossroad {

public:
    Crossroad(){

    };
    int switchLights(int &pU1,int &pU2,int &pU3,int &pR1,int &pR2,int &pR3,int &pD1,int &pD2,int &pD3,int &pL1,int &pL2,int &pL3){
        if((((pD2>pU2)||(pU2>pD2))>(pR2)&&(((pD2>pU2)||(pU2>pD2))>(pL2)))&&(pD2>=pD3)&&(pD2>=pD1)&&(pU2>=pU1)&&(pU2>=pU3)){
          cout<<"penis"<< endl;
           pU2 = jedeRovneDolu();
            pD2 =jedeRovneNahodu();
            pD3 = jedeDopravaZeZdola();
            pU3 = jedeDolevaZeZdola();
            pL1,pL2,pL3,pU1,pD1,pR1,pR2,pR3 = 0;
        }else{

        }


    }





    int jedeRovneDolu(){
        return 1;
    }
    int jedeRovneNahodu(){
        return 1;
    }
    int jedeDopravaZeZdola(){
        return 1;
    }
    int jedeDopravaZeZhora(){
        return  1;
    }
    int jedeDolevaZeZdola(){
        return 1;
    }
    int jedeDolevaZeZhora(){
        return 1;
    }
    int jedeRovneZLeva(){
        return 1;
    }
    int jedeRovneZPrava(){
        return 1;
    }
    int jedeDoluZLeva(){
        return 1;
    }
    int jedeDoluZprava(){
        return 1;
    }
    int jedeNahoruZleva(){
        return 1;
    }
    int jedeNahoruZPrava(){
        return 1;
    }



};*/







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


    void different(Mat dif, int &number1, int &number2, int &number3) {
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
        int ax;
        int ay;
        int bx;
        int by;
        int a;
        int b;
        int d;
    public:
        MyLine() {}

        void setPoint(int ax, int ay, int bx, int by) // default constructor
        {
            this->ax = ax;
            this->ay = ay;
            this->bx = bx;
            this->by = by;
            a = ax - bx;
            b = ay - by;
            d = -a * ax - b * ay;

        };

        bool left(int x, int y) {
            int position = (bx - ax) * (y - ay) - (by - ay) * (x - ax);
            if (position < 0) {
                return false;
            } else {
                return true;
            }
        }

    };


};

static void
Crosroad(int &ul, int &ud, int &ur, int &ru, int &rl, int &rd, int &dr, int &du, int &dl, int &ld, int &lr, int &lu) {
    int cancerArray[12]{ul, ud, ur, ru, rl, rd, dr, du, dl, ld, lr, lu};
    int maxIdes = 0;
    for (int i = 1; i < 12; ++i) {
        if (cancerArray[i] > cancerArray[maxIdes]) {
            maxIdes = i;
        }
    }
    if (maxIdes == 0) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 1;
        cancerArray[3] = 1;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 0;
        cancerArray[7] = 0;
        cancerArray[8] = 1;
        cancerArray[9] = 1;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 1) {
        cancerArray[0] = 0;
        cancerArray[1] = 1;
        cancerArray[2] = 1;
        cancerArray[3] = 1;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 2) {
        cancerArray[0] = 0;
        cancerArray[1] = 0;
        cancerArray[2] = 1;
        cancerArray[3] = 1;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 1;
        cancerArray[9] = 1;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 3) {
        cancerArray[0] = 0;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 1;
        cancerArray[4] = 1;
        cancerArray[5] = 1;
        cancerArray[6] = 0;
        cancerArray[7] = 0;
        cancerArray[8] = 1;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 4) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 1;
        cancerArray[5] = 1;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 5) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 0;
        cancerArray[5] = 1;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 1;
        cancerArray[10] = 0;
        cancerArray[11] = 1;
    } else if (maxIdes == 6) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 1;
        cancerArray[5] = 0;
        cancerArray[6] = 1;
        cancerArray[7] = 1;
        cancerArray[8] = 1;
        cancerArray[9] = 1;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 7) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 0;
        cancerArray[7] = 1;
        cancerArray[8] = 1;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 8) {
        cancerArray[0] = 0;
        cancerArray[1] = 0;
        cancerArray[2] = 1;
        cancerArray[3] = 1;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 0;
        cancerArray[7] = 0;
        cancerArray[8] = 1;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 0;
    } else if (maxIdes == 9) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 0;
        cancerArray[5] = 1;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 1;
        cancerArray[10] = 1;
        cancerArray[11] = 1;
    } else if (maxIdes == 10) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 0;
        cancerArray[4] = 0;
        cancerArray[5] = 1;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 0;
        cancerArray[10] = 1;
        cancerArray[11] = 1;
    } else if (maxIdes == 11) {
        cancerArray[0] = 1;
        cancerArray[1] = 0;
        cancerArray[2] = 0;
        cancerArray[3] = 1;
        cancerArray[4] = 0;
        cancerArray[5] = 0;
        cancerArray[6] = 1;
        cancerArray[7] = 0;
        cancerArray[8] = 0;
        cancerArray[9] = 0;
        cancerArray[10] = 0;
        cancerArray[11] = 1;
    }
    ul = cancerArray[0];
    ud = cancerArray[1];
    ur = cancerArray[2];
    ru = cancerArray[3];
    rl = cancerArray[4];
    rd = cancerArray[5];
    dr = cancerArray[6];
    du = cancerArray[7];
    dl = cancerArray[8];
    ld = cancerArray[9];
    lr = cancerArray[10];
    lu = cancerArray[11];
    cout << maxIdes << endl;
}

static void CrosroadOutput(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l) {
    cout << " " << a << " " << b << " " << c << " " << endl;
    cout << l << " " << " " << " " << " " << " " << d << endl;
    cout << k << " " << " " << " " << " " << " " << e << endl;
    cout << j << " " << " " << " " << " " << " " << f << endl;
    cout << " " << i << " " << h << " " << g << " " << endl;
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

    VideoCapture U("/home/lucky/Videos/CarTraffic01.mp4");
    VideoCapture R("/home/lucky/Videos/CarTraffic02.mp4");
    VideoCapture D("/home/lucky/Videos/CarTraffic03.mp4");
    VideoCapture L("/home/lucky/Videos/CarTraffic04.mp4");
    if (!U.isOpened())  // check if we succeeded
        return -1;


    while (true) {

        Mat frame[8];
        U >> frame[0];
        R >> frame[1];
        D >> frame[2];
        L >> frame[3];
        int number1 = 0;
        int number2 = 0;
        int number3 = 0;
        u.different(frame[0], number1, number2, number3);
        imshow("U", frame[0]);
        cout << number1 << " " << number2 << " " << number3 << " up" << endl;

        int number4 = 0;
        int number5 = 0;
        int number6 = 0;
        r.different(frame[1], number4, number5, number6);
        imshow("R", frame[1]);

        cout << number4 << " " << number5 << " " << number6 << " right" << endl;

        int number7 = 0;
        int number8 = 0;
        int number9 = 0;
        d.different(frame[2], number7, number8, number9);
        imshow("D", frame[2]);


        cout << number7 << " " << number8 << " " << number9 << " down" << endl;

        int number10 = 0;
        int number11 = 0;
        int number12 = 0;
        l.different(frame[3], number10, number11, number12);
        imshow("L", frame[3]);
        cout << number10 << " " << number11 << " " << number12 << " left" << endl;

        cout << endl;
        cout << endl;
        cout << endl;


        /* Crossroad crossroad;
         crossroad.switchLights(number1,number2,number3,number4,number5,number6,number7,number8,number9,number10,number11,number12);*/

        Crosroad(number1, number2, number3, number4, number5, number6, number7, number8, number9, number10, number11,
                 number12);


        CrosroadOutput(number1, number2, number3, number4, number5, number6, number7, number8, number9, number10,
                       number11, number12);
        cout << endl;
        cout << endl;
        cout << endl;
        if (waitKey(30) >= 0)
            break;
    }
    return 0;

};


