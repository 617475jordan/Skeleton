#include"checkPoint.h"

//检查点是否在线段附近
int Check::CheckPoint(Point a, Point randPoint[1][1024], int m_num)
{
	int flag = 0;
	int position =-1;
	if (m_num < 2)
	{
		return position;
	}
	for (int i = 0; i < m_num - 1; i++)
	{
		for (int j = i + 1; j < m_num; j++)
		{
			double x0 = a.x - randPoint[0][i].x;
			double y0 = a.y - randPoint[0][i].y;
			double x1 = a.x - randPoint[0][j].x;
			double y1 = a.y - randPoint[0][j].y;
			double _sum = x0*x1 + y0*y1;
			double p_sum = abs(x0*x0 + y0*y0);
			double q_sum = abs(x1*x1 + y1*y1);
			p_sum = sqrt(p_sum);
			q_sum = sqrt(q_sum);
			if (_sum / (p_sum*q_sum) < threshold)
			{
				flag++;
				position = i;
			}
		}
	}
	if (flag ==0)
	{
		cout << "点在直线附近请重新选择" << endl;
	}
	return position;
}