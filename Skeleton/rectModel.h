#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "checkPoint.h"
using namespace cv;
using namespace std;
#include "list"
class rectModel
{
public:
	rectModel();
	~rectModel();
	bool	onMouseLeftDown(float x, float y,float width, float height);
	bool    onMouseRightDown(float x, float y, float width, float height);
	bool	onMouseLeftUp(float x, float y, float width, float height);
	bool    onMouseRightUp(float x, float y, float width, float height);
	bool    judgeThreshold(double x, double y);
	bool    judgeRange(float x, float y, float width, float height);

public:
	vector<Point> deleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> moveCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> addCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> pointConvertVector(Point randPoint[1][1024], int m_num);

protected:
	int 		getClickedPoint(Point randPoint[1][1024], int m_num, int x, int y);
protected:
	int m_thresold = 10;  //Êó±êµã»÷×ø±êÔÊÐíÎó²î·¶Î§
};