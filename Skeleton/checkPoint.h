#pragma once

#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;
using namespace cv;

class Check
{
public:
	Check();
	~Check();
	//�����Ƿ����߶θ���
	int checkPoint(Point a, Point randPoint[1][1024], int m_num);
	//��������֮��ľ���
	int computeDistance(Point a, Point randPoint[1][1024], int m_num);
	double compare(double x0, double y0, double x1, double y1);
	double distance(double x0, double x1, double y0, double y1);
	double coordinateDistance[1][2];
	double coordinateFlag[1][2];
private:
	double threshold = -0.85;  //cos��ֵ
};