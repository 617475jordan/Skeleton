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
	//void	drawToImage(Mat dst);
	vector<Point> deleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> moveCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> addCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> pointConvertVector(Point randPoint[1][1024], int m_num);
	//Point randPoint[1][1024];
//	list<Point*>			m_pointList;


protected:
	int 		getClickedPoint(Point randPoint[1][1024], int m_num, int x, int y);
protected:
//	bool leftButtonDownFlag; //�����������Ƶ��ͣ���ŵı�־λ  
//	bool rightButtonDownFlag; //�Ҽ���������Ƶ��ͣ���ŵı�־λ
	//bool		m_bMouseDown;
	//Point*		m_pCurrentChoosed;
	int m_thresold = 20;  //���������������Χ
};