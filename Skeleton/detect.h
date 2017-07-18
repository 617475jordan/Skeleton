#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Detect
{
public:
	Mat ShowImage(Mat src, Point originalPoint, int width, int height);
private:
	Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Scalar p_color = Scalar(0, 0, 255);
	Scalar q_color = Scalar(0, 0, 255);
	Mat tmp;
	/***********��ֵ����ֵ************/
	static const int nY20_thresh = 50;

	Rect rect;
	Mat m_roi,n_roi;
};