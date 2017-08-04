#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include "rectModel.h"
#include "rectView.h"
#include <iostream>

using namespace std;

Mat src;//原始图像 
int failNum;  //初始化失败次数
int m_num;    //坐标个数
int width;
int height;
Point randPoint[1][1024];
vector<Point> coordinate;
bool leftButtonDownFlag; //左键单击后视频暂停播放的标志位  
bool rightButtonDownFlag; //右键单击后视频暂停播放的标志位


//鼠标回调函数    
void onMouse(int event, int x, int y, int flags, void *ustc);
//初始化
void initial();
//键盘操作
void keyOperation(); 
#define  windowName "show"




