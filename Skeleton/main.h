#pragma once

#include "checkPoint.h"
#include "myKinect.h"
#include "detect.h"
#include "rectModel.h"
#include "rectView.h"
#include <iostream>

using namespace std;

Mat src;//ԭʼͼ�� 
int failNum;  //��ʼ��ʧ�ܴ���
int m_num;    //�������
int width;
int height;
Point randPoint[1][1024];
vector<Point> coordinate;
bool leftButtonDownFlag; //�����������Ƶ��ͣ���ŵı�־λ  
bool rightButtonDownFlag; //�Ҽ���������Ƶ��ͣ���ŵı�־λ


//���ص�����    
void onMouse(int event, int x, int y, int flags, void *ustc);
//��ʼ��
void initial();
//���̲���
void keyOperation(); 
#define  windowName "show"




