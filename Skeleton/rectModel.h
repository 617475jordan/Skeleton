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
	bool	onMouseDown(float x, float y);
	bool	onMouseMove(float x, float y);
	bool	onMouseUp();

	bool	onMouseRightBtnDown(float x, float y);

public:
	void	drawToImage(Mat dst);
	vector<Point> DeleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> MoveCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> AddCoordinate(Point randPoint[1][1024], int m_num, int x, int y);

	Point randPoint[1][1024];
	list<Point*>			m_pointList;


protected:
	Point*		getClickedPoint(float x, float y);
	void		addPointAtLast(float x, float y);
protected:
	bool		m_bMouseDown;
	Point*		m_pCurrentChoosed;
	int m_thresold = 20;  //Êó±êµã»÷×ø±êÔÊÐíÎó²î·¶Î§
};