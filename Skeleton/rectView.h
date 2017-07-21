#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "detect.h"
using namespace cv;
using namespace std;

class rectView
{
public:
	rectView();
	~rectView();
	Mat  drawImage(Mat src, int m_num, vector<Point> coordinate);
	Mat  help(Mat src, int flag);
	Mat  drawPolygon(Mat src, Point randPoint[1][1024], int m_num,int flag);
private:
	Scalar m_color = Scalar(0, 0, 255);	  //点和线的颜色
	Scalar textColor = Scalar(0, 0, 255);  //文字的颜色
	int fontFace = 1;
	int textthickness = 1;				  //文字的厚度
	int textRaduis = 1;					  //文字半径
	int lineType = 10;					  //线的类型
	int raduis = 2;		  //点的半径
	int thickness = 2;	  //直线厚度
	double totalArea;	  //截图区域总面积
	double singleArea;	  //人影面积
	double fontScale = 0.6;				  //字体格式
	Point textPoint = Point(10, 10);
	Point clearPoint = Point(10, 20);
	Point goOutPoint = Point(10, 30);
	Point randPoint[1][1024];
private:
#define initialName "Initial"
#define coordinateHint "Choose c or C to clear all "
#define personOut 	   "People out"
#define personIn	  "People in"
#define goOut          "Choose o or O to go out"
};