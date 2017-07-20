#include "rectModel.h"
#include "math.h"
rectModel::rectModel()
{
	m_bMouseDown = false;
	m_pCurrentChoosed = NULL;
}

rectModel::~rectModel()
{
	m_bMouseDown = false;
	m_pCurrentChoosed = NULL;
}

bool	rectModel::onMouseDown(float x, float y)
{
	Point* p = getClickedPoint(x, y);
	if (p)
	{
		m_pCurrentChoosed = p;
	}
	else
	{
		addPointAtLast(x, y);
	}
	m_bMouseDown = true;
	return false;
}

bool	rectModel::onMouseMove(float x, float y)
{
	if (!m_bMouseDown)
	{
		return false;
	}

	if (m_pCurrentChoosed)
	{
		m_pCurrentChoosed->x = x;
		m_pCurrentChoosed->y = y;
		return true;
	}

}

bool	rectModel::onMouseUp()
{
	m_bMouseDown = false;
	return false;
}

bool	rectModel::onMouseRightBtnDown(float x, float y)
{

}

Point*		rectModel::getClickedPoint(float x, float y)
{
	list<Point*>::iterator itr = m_pointList.begin();
	for (; itr != m_pointList.end();itr++)
	{
		Point* p = *itr;
		double d = sqrt((x - p->x)*(x - p->x) + (y - p->y)*(y - p->y));
		if (d <20)
		{
			return *itr;
		}
	}
	return 0;
}

void		rectModel::addPointAtLast(float x, float y)
{
	Point* pPoint = new Point;
	pPoint->x = x;
	pPoint->y = y;
	m_pointList.push_back(pPoint);
}


void	drawToImage(Mat dst)
{

}


/***********移动坐标*********************/
vector<Point> rectModel::MoveCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	for (int i = 0; i < m_num; i++)
	{
		int widthlen = abs(randPoint[0][i].x - x);
		int hightlen = abs(randPoint[0][i].y - y);
		if (widthlen < m_thresold && hightlen < m_thresold)
		{
			randPoint[0][i] = Point(x, y);
		}
	}
	vector<Point> coordinate;
	for (int i = 0; i < m_num; i++)
	{
		coordinate.push_back(randPoint[0][i]);
	}
	return coordinate;
}
/**********删除坐标**********************/
vector<Point> rectModel::DeleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	for (int i = 0; i < m_num; i++)
	{
		int widthlen = abs(randPoint[0][i].x - x);
		int hightlen = abs(randPoint[0][i].y - y);
		if (widthlen < m_thresold && hightlen < m_thresold)
		{
			if (i == m_num - 1)
			{
				m_num--;
			}
			else
			{
				randPoint[0][i] = randPoint[0][i + 1];
			}
		}
	}
	vector<Point> coordinate;
	for (int i = 0; i < m_num; i++)
	{
		coordinate.push_back(randPoint[0][i]);
	}
	return coordinate;
}
/**********添加坐标**********************/
vector<Point> rectModel::AddCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	Check CheckPoint;
	int flag = 0;	   //点是否在直线附近标志位
	for (int i = 0; i < m_num; i++)
	{
		int widthlen = abs(randPoint[0][i].x - x);
		int hightlen = abs(randPoint[0][i].y - y);
		if (widthlen < m_thresold && hightlen < m_thresold)
		{
			flag++;
		}
	}
	if (flag == 0)
	{
		int m_position = CheckPoint.CheckPoint(Point(x, y), randPoint, m_num);

		if (m_position < 0)
		{
			randPoint[0][m_num] = Point(x, y);
			m_num++;
		}
		else
		{
			m_num++;
			for (int k = m_num - 1; k > m_position; k--)
			{
				randPoint[0][k] = randPoint[0][k - 1];
			}
			randPoint[0][m_position + 1] = Point(x, y);
		}
	}
	vector<Point> coordinate;
	for (int i = 0; i < m_num; i++)
	{
		coordinate.push_back(randPoint[0][i]);
	}
	return coordinate;
}