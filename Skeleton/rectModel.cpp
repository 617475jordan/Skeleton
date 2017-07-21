#include "rectModel.h"
#include "math.h"
rectModel::rectModel()
{
	//leftButtonDownFlag = false;
	//rightButtonDownFlag = false;
}

rectModel::~rectModel()
{

}

bool rectModel::judgeThreshold(double x, double y)
{
	if (x < m_thresold&&y < m_thresold)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool    rectModel::judgeRange(float x, float y, float width, float height)
{
	if (x <= width&&y <= height&&x > 0 && y > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool	rectModel::onMouseLeftDown(float x, float y, float width, float height)
{
	if (judgeRange(x, y, width, height))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
bool	rectModel::onMouseLeftUp(float x, float y, float width, float height)
{
	if (judgeRange(x, y, width, height))
	{
		return false;
	}
	else
	{
		return true;
	}

}
bool rectModel::onMouseRightDown(float x, float y, float width, float height)
{
	if (judgeRange(x, y, width, height))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool rectModel::onMouseRightUp(float x, float y, float width, float height)
{
	if (judgeRange(x, y, width, height))
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**********添加坐标**********************/
vector<Point> rectModel::addCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	Check CheckPoint;
	int flag = getClickedPoint(randPoint,  m_num, x, y);	   //点是否在直线附近标志位

	if (flag == 0)
	{
		int m_position = CheckPoint.checkPoint(Point(x, y), randPoint, m_num);
		if (m_position < 0)
		{	

			int n_position = CheckPoint.computeDistance(Point(x, y), randPoint, m_num);
			if (n_position<-1)
			{
				randPoint[0][m_num] = Point(x, y);
				m_num++;
			}
			else
			{
				m_num++;
				for (int k = m_num - 1; k > n_position; k--)
				{
					randPoint[0][k] = randPoint[0][k - 1];
				}
				randPoint[0][n_position+1] = Point(x, y);
			}
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
	coordinate.clear();
	coordinate = pointConvertVector(randPoint, m_num);
	return coordinate;
}

/***********判断点是否在直线附近************************/
int		rectModel::getClickedPoint(Point randPoint[1][1024], int m_num, int x, int y)
{
	int flag = 0;
	for (int i = 0; i < m_num; i++)
	{
		if (judgeThreshold(abs(randPoint[0][i].x - x), abs(randPoint[0][i].y - y)))
		{
			flag++;
		}
	}
	return flag;
}
/***********移动坐标*********************/
vector<Point> rectModel::moveCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	for (int i = 0; i < m_num; i++)
	{
		if (judgeThreshold(abs(randPoint[0][i].x - x), abs(randPoint[0][i].y - y)))
		{
			randPoint[0][i] = Point(x, y);
		}
	}
	vector<Point> coordinate;
	coordinate.clear();
	coordinate = pointConvertVector(randPoint, m_num);
	return coordinate;
}
/**********删除坐标**********************/
vector<Point> rectModel::deleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y)
{
	int n_num = m_num;
	int flag=-1;
	for (int i = 0; i < m_num; i++)
	{
		if (judgeThreshold(abs(randPoint[0][i].x - x), abs(randPoint[0][i].y - y)))
		{
			flag = i;
			break;
		}
	}
	for (int i = flag; i < m_num-1; i++)
	{
		randPoint[0][i] = randPoint[0][i + 1];
	}
	m_num--;
	vector<Point> coordinate;
	coordinate.clear();
	coordinate = pointConvertVector(randPoint, m_num);
	return coordinate;
}

/************Point转为Vector类型**********************/
vector<Point> rectModel::pointConvertVector(Point randPoint[1][1024], int m_num)
{
	vector<Point> coordinate;
	coordinate.clear();
	for (int i = 0; i < m_num; i++)
	{
		coordinate.push_back(randPoint[0][i]);
	}
	return coordinate;
}
