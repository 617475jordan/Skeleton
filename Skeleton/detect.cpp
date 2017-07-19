#include "detect.h"


Mat Detect::ShowImage(Mat src, Point originalPoint, int width, int height)
{
	m_roi = src(Rect(originalPoint.x, originalPoint.y, width, height));
	Mat out;
	m_roi.copyTo(out);
	cvtColor(m_roi, m_roi, CV_RGB2GRAY);
	/********腐蚀******/
	morphologyEx(m_roi, tmp, MORPH_CLOSE, elemet);
	/*****二值化*******/
	threshold(tmp, m_roi, nY20_thresh, 255, THRESH_BINARY);

	/*********连通区域查找****************/
	vector<vector<Point>> contours;
	vector<vector<Point>> filterContours;
	contours.clear();
	filterContours.clear();
	findContours(m_roi, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	/*********求面积************/
	vector<vector<Point>> maxContour;
	double sum = width*height;
	double m_sum = width*height;
	m_sum = m_sum*0.1;
	double maxArea = 0;
	//int flagMaxArea=0;
	for (size_t a = 0; a < contours.size(); a++)
	{
		double area = cv::contourArea(contours[a]);
		if (area > maxArea)
		{
			maxArea = width*height-area;
		}
	}
	cout << maxArea << endl;
	if (maxArea > m_sum)
	{
		cout << "People in" << endl;
	}
	else
	{
		cout << "Peole out" << endl;
	}
	return out;

}

double Detect::ComputeArea(Mat m_src)
{
	Mat out, tmp;
	m_src.copyTo(out);
	cvtColor(out, out, CV_RGB2GRAY);
	/********腐蚀******/
	morphologyEx(out, tmp, MORPH_CLOSE, elemet);
	/*****二值化*******/
	threshold(tmp, out, nY20_thresh, 255, THRESH_BINARY);

	/*********连通区域查找****************/
	vector<vector<Point>> contours;
	vector<vector<Point>> filterContours;
	contours.clear();
	filterContours.clear();
	findContours(out, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	/*********求面积************/
	vector<vector<Point>> maxContour;
	int width = 424;
	int height = 512;
	double sum = width*height;
	double m_sum = width*height;
	m_sum = m_sum*0.1;
	double maxArea = 0;
	//int flagMaxArea=0;
	for (size_t a = 0; a < contours.size(); a++)
	{
		double area = cv::contourArea(contours[a]);
		if (area > maxArea)
		{
			maxArea = area;
		}
	}
	//cout << maxArea << endl;
	return maxArea;
}