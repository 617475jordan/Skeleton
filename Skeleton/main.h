#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;

Mat src;//原始图像 
Mat m_src;
 
bool leftButtonDownFlag ; //左键单击后视频暂停播放的标志位  
bool rightButtonDownFlag; //右键单击后视频暂停播放的标志位
//vector<Point> beginPoint;
//vector<Point> endPoint;
int m_num;	  //坐标点个数
int failNum;  //初始化失败次数
int m_thresold = 20;  //鼠标点击坐标允许误差范围
int raduis = 2;		  //点的半径
int thickness = 2;	  //直线厚度
double totalArea;	  //截图区域总面积
double singleArea;	  //人影面积

Scalar m_color = Scalar(0, 0, 255);	  //点和线的颜色
Scalar textColor = Scalar(0, 0, 255);  //文字的颜色
int textthickness = 1;				  //文字的厚度
int textRaduis = 1;					  //文字半径
int lineType = 10;					  //线的类型
double fontScale = 0.6;				  //字体格式
Point textPoint = Point(10, 10);
Point clearPoint = Point(10, 20);
Point goOutPoint = Point(10, 30);
Point randPoint[1][1024];

//鼠标回调函数    
void OnMouse(int event, int x, int y, int flags, void *ustc);
//初始化
void Initial();
//键盘操作
void keyOperation(); 
//界面提示
Mat  Help(Mat src, int flag);

#define initialName "Initial"
#define coordinateHint "Choose c or C to clear all "
#define personOut 	   "People out"
#define personIn	  "People in"
#define goOut          "Choose o or O to go out"
