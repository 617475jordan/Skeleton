#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;

class Detect
{
public:
	Mat ShowImage(Mat src, Point originalPoint, int width, int height);
	double ComputeArea(Mat m_src);

private:
	Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	//Scalar p_color = Scalar(0, 0, 255);
	//Scalar q_color = Scalar(0, 0, 255);
	Mat tmp;
	/***********二值化阈值************/
	static const int nY20_thresh = 50;
	int width = 424;
	int height = 512;
	Rect rect;
	Mat m_roi,n_roi;
};
