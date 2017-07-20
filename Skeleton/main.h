#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;

Mat src;//原始图像 
Mat m_src;
//Point originalPoint; //矩形框起点  
//Point processPoint; //矩形框终点  
bool leftButtonDownFlag ; //左键单击后视频暂停播放的标志位  
bool rightButtonDownFlag;
bool flagLBUTTON;
//vector<Point> beginPoint;
//vector<Point> endPoint;
int  numPoint;
int m_num;
int failNum;
int m_thresold = 20;
int raduis = 2;
int thickness = 2;
double totalArea;
double singleArea;

Scalar m_color = Scalar(0, 0, 255);	
Scalar textColor = Scalar(0, 0, 255);
int textthickness = 1;
int textRaduis = 1;
int lineType = 10;
double fontScale = 0.6;
Point textPoint = Point(10, 10);
Point clearPoint = Point(10, 20);
Point goOutPoint = Point(10, 30);
Point randPoint[1][1024];

Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
static const int nY20_thresh = 50;

//鼠标回调函数    
void OnMouse(int event, int x, int y, int flags, void *ustc);
void Initial();
void keyOperation();
Mat  Help(Mat src, int flag);

#define initialName "Initial"
#define coordinateHint "Choose c or C to clear all "
#define personOut 	   "People out"
#define personIn	  "People in"
#define goOut          "Choose o or O to go out"
