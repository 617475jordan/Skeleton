#include "main.h"
int main()
{
	CBodyBasics myKinect;
	Detect detect;

	//传感器初始化
	HRESULT hr = myKinect.InitializeDefaultSensor();
	while (FAILED(hr))
	{
		cout << "连接失败，正在尝试,当前失败次数为:" << m_num << endl;
		hr = myKinect.InitializeDefaultSensor();
		m_num++;
	} 	

	if (SUCCEEDED(hr))
	{
		cout << "输入多边形线条个数:" ;
		cin >> numPoint;

		namedWindow("src");
		setMouseCallback("src", OnMouse);
		while (1)
		{
			src = myKinect.Update();
			if (src.empty())
			{
				src = myKinect.Update();
			}
			else
			{
				/*	if (originalPoint != processPoint)
					{
					//rectangle(src, originalPoint, processPoint, Scalar(255, 0, 0), 2);
					//line(src, originalPoint, processPoint, Scalar(255, 0, 0), 2);
					}
					int width = abs(originalPoint.x - processPoint.x);
					int height = abs(originalPoint.y - processPoint.y);
					if (width > 0 && height > 0)
					{
					Mat out;
					out = detect.ShowImage(src, originalPoint, width, height);
					imshow("screenshot", out);
					waitKey(1);
					}
					*/

				/**************绘制多边形*******/
				src.copyTo(m_src);
				m_src.setTo(255);

				if (m_num > 0)
				{
					const Point* ppt[1] = { randPoint[0] };
					int npt[] = { m_num };
					polylines(m_src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
					for (int i = 0; i < m_num; i++)
					{
						circle(src, randPoint[0][i], raduis, m_color, thickness);
						circle(m_src, randPoint[0][i], raduis, m_color, thickness);

					}
					imshow("m_src", m_src);
					waitKey(1);
				}
				imshow("src", src);
				waitKey(1);
			}

			if (waitKey(10) >= 0)
			{
				string sz = "退出";
				MessageBoxA(NULL, sz.c_str(), "提示", IDOK);
				return 0;
			}
		}
	}
	else
	{
		cout << "kinect initialization failed!" << endl;
		return 0;
	}  
	return 0;
}


void OnMouse(int event, int x, int y, int flags, void *ustc)
{
	/***********左键添加坐标*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag==false)
	{
		if (m_num >= numPoint)
		{
			m_num = 0;
		}
		leftButtonDownFlag = true; //标志位  
	}
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
		if (m_num >= numPoint)
		{
			m_num = 0;		
		}
		leftButtonDownFlag = false;
		int flag = 0;
		for (int i = 0; i < m_num; i++)
		{
			int widthlen = abs(randPoint[0][i].x - x);
			int hightlen = abs(randPoint[0][i].y - y);
			if (widthlen < m_thresold && hightlen < m_thresold)
			{
				flag++;
			}
		}
		if (flag == 0 && CheckPoint(Point(x, y), randPoint, m_num))
		{
			randPoint[0][m_num] = Point(x, y);
			m_num++;
		}	
	}

	/*********右击删除坐标*************/
	if (event == CV_EVENT_RBUTTONDOWN&&rightButtonDownFlag == false)
	{
		rightButtonDownFlag = true;
	}
	if (event == CV_EVENT_RBUTTONUP&&rightButtonDownFlag)
	{
		leftButtonDownFlag = false;
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
					randPoint[0][i] = randPoint[0][i+1];
				}
			}
		}
	}

}

void Initial()
{
	m_num = 0;
	leftButtonDownFlag = false;
	rightButtonDownFlag = false;
}