#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;

Mat src;//ԭʼͼ�� 
Mat m_src;
//Point originalPoint; //���ο����  
//Point processPoint; //���ο��յ�  
bool leftButtonDownFlag ; //�����������Ƶ��ͣ���ŵı�־λ  
bool rightButtonDownFlag;
//vector<Point> beginPoint;
//vector<Point> endPoint;
int  numPoint;
int m_num;
int failNum;
int m_thresold = 10;
int raduis = 2;
int thickness = 2;
double totalArea;
double singleArea;

Scalar m_color = Scalar(0, 0, 255);
Point randPoint[1][1024];

Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
static const int nY20_thresh = 50;

//���ص�����    
void OnMouse(int event, int x, int y, int flags, void *ustc);
void Initial();
