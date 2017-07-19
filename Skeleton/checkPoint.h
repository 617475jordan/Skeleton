#pragma once

#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;
using namespace cv;

class Check
{
public:
	int CheckPoint(Point a, Point randPoint[1][1024], int m_num);
private:
	double threshold = -0.85;  //cos„–÷µ
};