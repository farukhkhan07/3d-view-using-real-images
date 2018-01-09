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

IplImage* p_imgorignal;
IplImage* p_imgorignal2;
CvSize imagesize = { 0, 0 };
CvSize mxsize = { 0, 0 };
CvSize mysize = { 0, 0 };

int name = 1;


void picSaverfunc()
{

	char lefty[110] = "C:/Users/hp/Documents/Visual Studio 2013/Projects/FYP_Part1_PairSaving/FYP_Part1_PairSaving/Calib/left";
	char righty[110] = "C:/Users/hp/Documents/Visual Studio 2013/Projects/FYP_Part1_PairSaving/FYP_Part1_PairSaving/Calib/right";

	char nmbr[10] = "0";

	sprintf(nmbr, "%02d", name);
	
	
	strcat(lefty, &nmbr[0]);
	strcat(lefty, ".jpg");
	strcat(righty, &nmbr[0]);
	strcat(righty, ".jpg");
	printf("%s \n %s \n", lefty, righty);

	Mat mat_right(p_imgorignal);
	Mat mat_left(p_imgorignal2);
	Mat *left_rect = NULL, *right_rect = NULL;



	imwrite(lefty, mat_left);
	imwrite(righty, mat_right);
	printf("\n %d image pair saved", name);
	name++;


}
int main()
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "Note: Pair Saving is used to detect the postions and results of 2 cameras" << endl;
	cout << "********************************************************************************" << endl;
	cout << "Press SpaceBar to Capture the Pictures of Stereo Cameras Left and Right" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	CvSize size640x480 = cvSize(640, 480);
	CvCapture* p_capwebcam;
	CvCapture* p_capwebcam2;

	//int i;
	char charCheckForEsckey;
	p_capwebcam = cvCaptureFromCAM(1);

	if (p_capwebcam == NULL)
	{
		printf("Null was captured \n");
		getchar();
		return(-1);
	}
	p_capwebcam2 = cvCaptureFromCAM(2);

	if (p_capwebcam2 == NULL)
	{
		printf("Null was captured \n");
		getchar();
		return(-1);
	}
	cvNamedWindow("right", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("left", CV_WINDOW_AUTOSIZE);


	while (1)
	{
		p_imgorignal = cvQueryFrame(p_capwebcam);
		p_imgorignal2 = cvQueryFrame(p_capwebcam2);
		if (p_imgorignal == NULL)
		{
			printf("error: frame is NULL \n");
			getchar();
		
		}

		if (p_imgorignal2 == NULL)
		{
			printf("error: frame is NULL \n");
			getchar();
			
		}
		Mat src1(p_imgorignal);
		Mat src2(p_imgorignal2);
		Mat dst;
		addWeighted(src1, 0.5, src2, 0.5, 0.0, dst);

		cvShowImage("right", p_imgorignal);
		cvShowImage("left", p_imgorignal2);
		imshow("mix", dst);
		
		charCheckForEsckey = cvWaitKey(10);
		if (charCheckForEsckey == 27) break;
		if (charCheckForEsckey == 32)
		{
			picSaverfunc();
		}
	}
	cvReleaseCapture(&p_capwebcam);
	cvReleaseCapture(&p_capwebcam2);

	cvDestroyWindow("right");
	cvDestroyWindow("left");
	return(0);

}


