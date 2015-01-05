#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

// The Parameters here will vary according to the need
int v_d = 0;		// For Dark
int v_g = 127;      // For Gray
int v_b = 255;      // For Bright

int break1 = 10;	// The Ramp break of the fuzzy membership functions	
int break2 = 98;
int break3 = 250;

float mu_dark;
float mu_gray;
float mu_bright;

void fuzzy_transform(int inten){

	if(inten < break1 ) {mu_dark = 1; mu_gray = 0; mu_bright = 0;}
	if(inten > break3) {mu_dark = 0; mu_gray = 0; mu_bright = 1;}
	if(inten>break1 && inten <break2){
		mu_bright = 0;
		float k1 = 1/float(break1 - break2);
		mu_dark = float((k1)*inten)  - float((break2*k1));
		k1 = 1/float(break2 - break1);
		mu_gray = float(k1*inten) - float(break1*k1);
	}
	if(inten>break2 && inten <break3){
		mu_dark = 0;
		float k1 = 1/float(break2 - break3);
		mu_gray = float((k1)*inten)  - float(break3*k1);
		k1 = 1/float(break3 - break2);
		mu_bright = float(k1*inten) - float(break2*k1);
	}

}


int main(){

	// Load the image 
	Mat input_img;
	input_img = imread("Test.bmp",1);
	imshow("Input Image",input_img);

	// The Image is already resized

	// We try three different enhancement techniques

	// 1) Histogram equalization
	cvtColor(input_img,input_img,CV_BGR2GRAY);
	Mat out1;
	equalizeHist(input_img,out1);
	imshow("After 1st enhancement(hist equalize)",out1);

	//2) Linear contrast streaching
	Mat out2 = input_img;
	// find the min and maximum pixel intensities
	double minval=0;
	double maxval=0;
	minMaxLoc(input_img,&minval,&maxval);

	cout << minval << "  "<<maxval <<endl;

	for( int y = 0; y < input_img.rows; y++ )
    { 
        for( int x = 0; x < input_img.cols; x++ )
        { 

        	double temp = double(input_img.at<uchar>(y,x));
        	temp = temp - minval; 
        	temp = temp/(maxval-minval);

        	temp = temp*255;
        	
        	out2.at<uchar>(y,x) = int(temp);
        }
    }

	imshow("After 2nd enancement technique(LCS)",out2);
	minMaxLoc(out2,&minval,&maxval);

	cout << minval << "  "<<maxval <<endl;

	//3) Fuzzy based enhancement on Out1
	Mat out3;
	out3 = input_img;
	equalizeHist(out1,out1);
    equalizeHist(out1,out1);
    equalizeHist(out1,out1);
    equalizeHist(out1,out1);
	for( int y = 0; y < input_img.rows; y++ )
    { 
        for( int x = 0; x < input_img.cols; x++ )
        { 	
        	int temp = out1.at<uchar>(y,x); 
        	fuzzy_transform(temp);
        	//cout << mu_dark<<endl;
        	float tempnew = (v_d*mu_dark + v_b*mu_bright + v_g*mu_gray);
        	tempnew = tempnew/(mu_gray+mu_bright+mu_dark);
        	
        	out3.at<uchar>(y,x) = tempnew;
        }
    }

    imshow("fuzzy_transform image the 3rd enhancement type",out3);

    // For Now out3 was the best, when dealing with the actual thing we will need some kind of adaptive bound setting
    // Lets try on the thresholding
    Mat dst;

    //threshold( out3, dst, 105, 255,1);
    adaptiveThreshold(out3,dst,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,11,2);
    medianBlur(dst,dst,5);
    imshow("threshold Image",dst);
	waitKey(0);
	return 0;
}