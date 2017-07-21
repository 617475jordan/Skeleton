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
	Scalar m_color = Scalar(0, 0, 255);	  //����ߵ���ɫ
	Scalar textColor = Scalar(0, 0, 255);  //���ֵ���ɫ
	int fontFace = 1;
	int textthickness = 1;				  //���ֵĺ��
	int textRaduis = 1;					  //���ְ뾶
	int lineType = 10;					  //�ߵ�����
	int raduis = 2;		  //��İ뾶
	int thickness = 2;	  //ֱ�ߺ��
	double totalArea;	  //��ͼ���������
	double singleArea;	  //��Ӱ���
	double fontScale = 0.6;				  //�����ʽ
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