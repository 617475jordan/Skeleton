#include "main.h"
int main()
{
	CBodyBasics myKinect;
	Detect detect;

	//传感器初始化
	HRESULT hr = myKinect.InitializeDefaultSensor();
	while (FAILED(hr))
	{
		cout << "连接失败，正在尝试,当前失败次数为:" << failNum << endl;
		hr = myKinect.InitializeDefaultSensor();
		failNum++;
	} 	

	if (SUCCEEDED(hr))
	{
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
				/**************绘制多边形*******/
				src.copyTo(m_src);
				m_src.setTo(0);
				waitKey(1);
				if (m_num > -1)
				{
					const Point* ppt[1] = { randPoint[0] };
					int npt[] = { m_num };
					polylines(m_src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
					fillPoly(m_src, ppt, npt, 1, Scalar(255, 255, 255));
					totalArea = detect.ComputeArea(m_src);
					for (int i = 0; i < m_num; i++)
					{
						//						circle(src, randPoint[0][i], raduis, m_color, thickness);
						circle(m_src, randPoint[0][i], raduis, m_color, thickness);

					}

				}
				Mat bitM;
				bitwise_not(src, bitM);
				bitM.copyTo(src);
				bitwise_and(m_src, bitM, bitM);
				singleArea = detect.ComputeArea(bitM);

				if (singleArea > 0.1*totalArea)
				{
					cout << "People in" << endl;
				}
				else
				{
					cout << "People out" << endl;
				}
				const Point* ppt[1] = { randPoint[0] };
				int npt[] = { m_num };
				polylines(bitM, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
				polylines(src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()

				totalArea = detect.ComputeArea(m_src);
				for (int i = 0; i < m_num; i++)
				{
					circle(bitM, randPoint[0][i], raduis, m_color, thickness);
				}
	
				if (totalArea<=0)
				{
					imshow("src", src);
					waitKey(1);
				}
				else  if (totalArea>0)
				{
					imshow("src", bitM);
					waitKey(1);
				}
					
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
	Check CheckPoint;
	/***********左键添加坐标*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag==false)
	{
	
		leftButtonDownFlag = true; //标志位  
	}
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
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
		if (flag == 0)
		{
			int position = CheckPoint.CheckPoint(Point(x, y), randPoint, m_num);
			if (position < 0)
			{
				randPoint[0][m_num] = Point(x, y);
				m_num++;
			}
			else
			{
				m_num++;
				for (int k = m_num-1; k>position; k--)
				{
					randPoint[0][k] = randPoint[0][k - 1];
				}
				randPoint[0][position + 1] = Point(x, y);
			}

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
	/***************鼠标拖拽*************/
	if (event == CV_EVENT_FLAG_LBUTTON)
	{
		int flag = -1;
		for (int i = 0; i < m_num; i++)
		{
			int w = abs(randPoint[0][i].x - x);
			int h = abs(randPoint[0][i].y - y);
			if (w<m_thresold&&h<m_thresold)
			{
				flag = i;
			}
		}
		if (flag>-1)
		{
			randPoint[0][flag] = Point(x, y);
		}
	}
}

void Initial()
{
	failNum = 0;
	m_num = 0;
	totalArea = 0;
	singleArea = 0;
	leftButtonDownFlag = false;
	rightButtonDownFlag = false;
}