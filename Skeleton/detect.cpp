#include "detect.h"


Mat Detect::ShowImage(Mat src, Point originalPoint, int width, int height)
{
	m_roi = src(Rect(originalPoint.x, originalPoint.x, width, height));
	Mat out;
	m_roi.copyTo(out);
	cvtColor(m_roi, m_roi, CV_RGB2GRAY);
	/********��ʴ******/
	morphologyEx(m_roi, tmp, MORPH_CLOSE, elemet);
	/*****��ֵ��*******/
	threshold(tmp, m_roi, nY20_thresh, 255, THRESH_BINARY);

	/*********��ͨ�������****************/
	vector<vector<Point>> contours;
	vector<vector<Point>> filterContours;
	contours.clear();
	filterContours.clear();
	findContours(m_roi, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	/*********�����************/
	vector<vector<Point>> maxContour;
	double sum = 200 * 200;
	for (size_t a = 0; a < contours.size(); a++)
	{
		double area = cv::contourArea(contours[a]);
		if (area > 0)
		{
			sum = sum - area;
		}
	}
	return out;

}
