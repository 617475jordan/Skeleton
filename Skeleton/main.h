#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;

Mat src;//ԭʼͼ�� 
Mat m_src;
 
bool leftButtonDownFlag ; //�����������Ƶ��ͣ���ŵı�־λ  
bool rightButtonDownFlag; //�Ҽ���������Ƶ��ͣ���ŵı�־λ
//vector<Point> beginPoint;
//vector<Point> endPoint;
int m_num;	  //��������
int failNum;  //��ʼ��ʧ�ܴ���
int m_thresold = 20;  //���������������Χ
int raduis = 2;		  //��İ뾶
int thickness = 2;	  //ֱ�ߺ��
double totalArea;	  //��ͼ���������
double singleArea;	  //��Ӱ���

Scalar m_color = Scalar(0, 0, 255);	  //����ߵ���ɫ
Scalar textColor = Scalar(0, 0, 255);  //���ֵ���ɫ
int textthickness = 1;				  //���ֵĺ��
int textRaduis = 1;					  //���ְ뾶
int lineType = 10;					  //�ߵ�����
double fontScale = 0.6;				  //�����ʽ
Point textPoint = Point(10, 10);
Point clearPoint = Point(10, 20);
Point goOutPoint = Point(10, 30);
Point randPoint[1][1024];

//���ص�����    
void OnMouse(int event, int x, int y, int flags, void *ustc);
//��ʼ��
void Initial();
//���̲���
void keyOperation(); 
//������ʾ
Mat  Help(Mat src, int flag);

#define initialName "Initial"
#define coordinateHint "Choose c or C to clear all "
#define personOut 	   "People out"
#define personIn	  "People in"
#define goOut          "Choose o or O to go out"
