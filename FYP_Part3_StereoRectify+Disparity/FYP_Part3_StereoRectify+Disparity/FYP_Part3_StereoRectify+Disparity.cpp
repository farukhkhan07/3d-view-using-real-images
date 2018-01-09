
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h> 
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "opencv2/contrib/contrib.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include<iostream>

using namespace cv;
using namespace std;
bool vdo = false;

CvMat part;
IplImage* rightiplimg;
IplImage* leftiplimg;
CvMat coloutl, coloutr;
CvSize size640x480 = cvSize(640, 480);
CvMat* disp2 = cvCreateMat(size640x480.height,
	size640x480.width, CV_16S);
CvMat* vdisp = cvCreateMat(size640x480.height,
	size640x480.width, CV_8U);
CvMat* pir;//=cvCreateMat( size640x480.height, size640x480.width,CV_8UC3 );
CvSize imagesize = { 0, 0 };
CvSize mxsize = { 0, 0 };
CvSize mysize = { 0, 0 };

CvSize customsize = cvSize(320, 240);

CvCapture* p_capwebcam;
CvCapture* p_capwebcam2;
int name = 1;
char lefty[100] = "left";
char righty[100] = "right";
char dispy[100] = "disp";
char nmbr[10] = "0";



Mat disp, dis2, normlizdotpt, g1, g2, img1, img2;
//int alpha_slider,sadsize=9,nofdsprtis=112,prefltsize=63,prefltcap=61,mindisp=61,txtrthresh=507,uniqratio=10,speclsize=100,specklerang=32,pp1=216,pp2=864;
//int alpha_slider,sadsize=7,nofdsprtis=112,prefltsize=5,prefltcap=61,mindisp=61,txtrthresh=507,uniqratio=0,speclsize=0,specklerang=8,pp1=216,pp2=864;
//for sgbm starting
//int alpha_slider,sadsize=5,nofdsprtis=192,prefltsize=5,prefltcap=4,mindisp=-64,txtrthresh=507,uniqratio=1,speclsize=150,specklerang=2,pp1=600,pp2=2400;
//for sbm new wala 3rd
int alpha_slider, sadsize = 41, nofdsprtis = 128, prefltsize = 41, prefltcap = 31, mindisp = -64, txtrthresh = 10, uniqratio = 15, speclsize = 150, specklerang = 2, pp1 = 600, pp2 = 2400;


int mindispx = 61;

StereoBM sbm;
StereoSGBM sgbm;
CvStereoBMState *BMState = cvCreateStereoBMState();


void on_trackbar(int, void*)
{

	if (nofdsprtis<16)
		nofdsprtis = 16;
	nofdsprtis = (nofdsprtis / 16);
	nofdsprtis = (nofdsprtis * 16);
	mindisp = mindispx - 100;


	sgbm.SADWindowSize = sadsize;
	sgbm.numberOfDisparities = nofdsprtis;
	sgbm.preFilterCap = prefltcap;
	sgbm.minDisparity = mindisp;
	sgbm.uniquenessRatio = uniqratio;
	sgbm.speckleWindowSize = speclsize;
	sgbm.speckleRange = specklerang;
	sgbm.disp12MaxDiff = 1;
	sgbm.fullDP = false;
	sgbm.P1 = pp1;
	sgbm.P2 = pp2;

	if (prefltcap>62)
		prefltcap = 62;
	if (prefltcap<5)
		prefltcap = 5;

	if (prefltsize<5)
		prefltsize = 5;
	if (prefltsize>255)
		prefltsize = 255;
	if (prefltsize % 2 == 0)
		prefltsize += 1;

	if (sadsize<5)
		sadsize = 5;
	else if (sadsize>255)
		sadsize = 255;
	if (sadsize % 2 == 0)
		sadsize += 1;



	sbm.state->SADWindowSize = sadsize;//odd and less than hight and width and 5-255
	sbm.state->numberOfDisparities = nofdsprtis;
	sbm.state->preFilterSize = prefltsize;//odd and 5-255
	sbm.state->preFilterCap = prefltcap;//1-63
	sbm.state->minDisparity = mindisp;
	sbm.state->textureThreshold = txtrthresh;
	sbm.state->uniquenessRatio = uniqratio;
	sbm.state->speckleWindowSize = speclsize;
	sbm.state->speckleRange = specklerang;
	sbm.state->disp12MaxDiff = 1;



	assert(BMState != 0);
	BMState->preFilterSize = prefltsize;
	BMState->preFilterCap = prefltcap;
	BMState->SADWindowSize = sadsize;
	BMState->minDisparity = mindisp;
	BMState->numberOfDisparities = nofdsprtis;
	BMState->textureThreshold = txtrthresh;
	BMState->uniquenessRatio = uniqratio;


}


int main()
{

	int i;
	char charCheckForEsckey;
	p_capwebcam = cvCaptureFromCAM(1);

	if (p_capwebcam == NULL)
	{
		//printf("Null was captured \n");
		cout << "Nothing Saved or Captured" << endl;
		cout << "Press Any Key to Exit" << endl;
		getchar();
		return(-1);
	}
	p_capwebcam2 = cvCaptureFromCAM(2);

	if (p_capwebcam2 == NULL)
	{
		//printf("Null was captured \n");
		cout << "Nothing Saved or Captured" << endl;
		cout << "Press Any Key to Exit" << endl;
		getchar();
		return(-1);
	}
	cvNamedWindow("right", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("left", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("trak_window");
	// namedWindow("trak_window", 2);

	createTrackbar("sadsize", "trak_window", &sadsize, 200, on_trackbar);
	createTrackbar("nofdsprtis", "trak_window", &nofdsprtis, 400, on_trackbar);
	createTrackbar("prefltsize", "trak_window", &prefltsize, 100, on_trackbar);
	createTrackbar("prefltcap", "trak_window", &prefltcap, 100, on_trackbar);
	createTrackbar("mindisp", "trak_window", &mindispx, 200, on_trackbar);
	createTrackbar("txtrthresh", "trak_window", &txtrthresh, 1000, on_trackbar);
	createTrackbar("uniqratio", "trak_window", &uniqratio, 200, on_trackbar);
	createTrackbar("speclsize", "trak_window", &speclsize, 100, on_trackbar);
	createTrackbar("pp1", "trak_window", &pp1, 500, on_trackbar);
	createTrackbar("pp2", "trak_window", &pp2, 1000, on_trackbar);
	createTrackbar("specklerang", "trak_window", &specklerang, 100, on_trackbar);


	imagesize = cvSize(640, 480);

	CvMat *mx1 = (CvMat*)cvLoad("mx1.xml", NULL, NULL, NULL);
	CvMat *mx2 = (CvMat*)cvLoad("mx2.xml", NULL, NULL, NULL);
	CvMat *my1 = (CvMat*)cvLoad("my1.xml", NULL, NULL, NULL);
	CvMat *my2 = (CvMat*)cvLoad("my2.xml", NULL, NULL, NULL);

	//*/

	CvMat* imgor = cvCreateMat(imagesize.height, imagesize.width, CV_8U);
	CvMat* imgol = cvCreateMat(imagesize.height, imagesize.width, CV_8U);
	pir = cvCreateMat(size640x480.height, size640x480.width, CV_8UC3);



	sbm.state->SADWindowSize = 7;
	sbm.state->numberOfDisparities = 112;
	sbm.state->preFilterSize = 5;
	sbm.state->preFilterCap = 61;
	sbm.state->minDisparity = -39;
	sbm.state->textureThreshold = 507;
	sbm.state->uniquenessRatio = 0;
	sbm.state->speckleWindowSize = 0;
	sbm.state->speckleRange = 8;
	sbm.state->disp12MaxDiff = 1;


	sgbm.SADWindowSize = 5;
	sgbm.numberOfDisparities = 192;
	sgbm.preFilterCap = 4;
	sgbm.minDisparity = -64;
	sgbm.uniquenessRatio = 1;
	sgbm.speckleWindowSize = 150;
	sgbm.speckleRange = 2;
	sgbm.disp12MaxDiff = 10;
	sgbm.fullDP = false;
	sgbm.P1 = 600;
	sgbm.P2 = 2400;


	//example waly

	assert(BMState != 0);
	BMState->preFilterSize = 41;
	BMState->preFilterCap = 31;
	BMState->SADWindowSize = 41;
	BMState->minDisparity = -64;
	BMState->numberOfDisparities = 112;
	BMState->textureThreshold = 10;
	BMState->uniquenessRatio = 7;

	cvNamedWindow("disparity");

	while (1)
	{

		rightiplimg = cvQueryFrame(p_capwebcam);
		leftiplimg = cvQueryFrame(p_capwebcam2);
		if (rightiplimg == NULL)
		{
			cout << "error: frame is NULL " << endl;
			getchar();
			//break;
		}

		if (leftiplimg == NULL)
		{
			cout << "error: frame is NULL " << endl;
			getchar();
			//	break;
		}
		cvShowImage("right", rightiplimg);
		cvShowImage("left", leftiplimg);


		waitKey(10);
		Mat mat_right(rightiplimg);
		Mat mat_left(leftiplimg);
		imwrite("templ.jpg", mat_left);
		imwrite("tempr.jpg", mat_right);



		IplImage* imginl = cvLoadImage("templ.jpg", 0);
		IplImage* imginr = cvLoadImage("tempr.jpg", 0);

		cvRemap(imginl, imgol, mx1, my1);
		cvRemap(imginr, imgor, mx2, my2);


		cvSaveImage("Lr.jpg", imgol);
		cvSaveImage("Rr.jpg", imgor);

		img1 = cvLoadImage("Lr.jpg");
		img2 = cvLoadImage("Rr.jpg");

		/*cvGetCols(pir, &part, 150, size640x480.width);
		cvCvtColor(imgor, &part, CV_GRAY2BGR);
		cvShowImage("shifted", pir);
		*/

		//cv::resize(img1, img1,customsize); 
		//cv::resize(img2, img2,customsize);
		cvtColor(img1, g1, CV_BGR2GRAY);
		cvtColor(img2, g2, CV_BGR2GRAY);

		cvFindStereoCorrespondenceBM(imgol, imgor, disp2, BMState);
		cvNormalize(disp2, vdisp, 0, 256, CV_MINMAX);

		cvShowImage("disparity", vdisp);

		//sbm(g1, g2, disp);
		//sgbm(g1, g2, disp);


		//	normalize(disp, normlizdotpt, 20, 220, CV_MINMAX, CV_8U);

		cvShowImage("right", rightiplimg);
		cvShowImage("left", leftiplimg);
		//imshow("disp", normlizdotpt);
		if (vdo)
		{
			char lefty[100] = "left";
			char righty[100] = "right";
			char dispy[100] = "disp";
			char nmbr[10] = "0";

			sprintf(nmbr, "%02d", name);
			strcat(lefty, &nmbr[0]);
			strcat(lefty, ".jpg");
			strcat(righty, &nmbr[0]);
			strcat(righty, ".jpg");
			strcat(dispy, &nmbr[0]);
			strcat(dispy, ".jpg");

			cvSaveImage(lefty, leftiplimg);
			cvSaveImage(righty, rightiplimg);
			cvSaveImage(dispy, vdisp);
			name++;
		}
		charCheckForEsckey = cvWaitKey(10);
		if (charCheckForEsckey == 27) break;
		if (charCheckForEsckey == 32)
		{
			vdo = true;
			cvSaveImage("Left.jpg", leftiplimg);
			cvSaveImage("Right.jpg", rightiplimg);
			cvSaveImage("disp2.jpg", vdisp);
			


		}

	}
	cvReleaseCapture(&p_capwebcam);
	cvReleaseCapture(&p_capwebcam2);

	cvDestroyWindow("right");
	cvDestroyWindow("left");
	cvDestroyAllWindows();
	return(0);
}


