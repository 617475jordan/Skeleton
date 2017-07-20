#pragma once

#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;
using namespace cv;

class Check
{
public:
	//检查点是否在线段附近
	int CheckPoint(Point a, Point randPoint[1][1024], int m_num);
	//计算两点之间的距离
	int ComputeDistance(Point a, Point randPoint[1][1024], int m_num);
	double Compare(double x0, double y0, double x1, double y1);
	double Distance(double x0, double y0, double x1, double y1);
private:
	double threshold = -0.85;  //cos阈值
};