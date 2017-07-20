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
				Mat a;
				src.copyTo(m_src);
				src.copyTo(a);
				m_src.setTo(0);
				a.setTo(0);
				if (m_num > -1)
				{
					const Point* ppt[1] = { randPoint[0] };
					int npt[] = { m_num };
					/*智能绘制多边形**/
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

				const Point* ppt[1] = { randPoint[0] };
				int npt[] = { m_num };
		        /*智能绘制多边形**/	
		     	polylines(bitM, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
				polylines(src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()

				totalArea = detect.ComputeArea(m_src);
				for (int i = 0; i < m_num; i++)
				{
					circle(bitM, randPoint[0][i], raduis, m_color, thickness);
				}
	
				if (totalArea<=0)
				{
					src = Help(src, 1);
					imshow("src", src);
					waitKey(1);
				}
				else  if (totalArea>0)
				{
					if (singleArea > 0.1*totalArea)
					{
						bitM = Help(bitM, 2);
					}
					else
					{
						bitM = Help(bitM, 3);
					}
					imshow("src", bitM);
					waitKey(1);
				}
				keyOperation();
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
	int moveflag = -1; //点拖拽标记位
	/***********左键添加坐标*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag == false  )
	{
		leftButtonDownFlag = true; //标志位 
		for (int i = 0; i < m_num; i++)
		{
			int widthlen = abs(randPoint[0][i].x - x);
			int hightlen = abs(randPoint[0][i].y - y);
			if (widthlen < m_thresold && hightlen < m_thresold)
			{
				moveflag = i;
				randPoint[0][i] = Point(x, y);
			}
		}
	}
	if (event == CV_EVENT_MOUSEMOVE &&leftButtonDownFlag)
	{
		randPoint[0][moveflag] = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
		leftButtonDownFlag = false;
		if (moveflag > 0)
		{
			randPoint[0][moveflag] = Point(x, y);
		}
		else
		{
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
			 
				/**************判断添加点是否在最近************/
				/**
				int n_position = CheckPoint.ComputeDistance(Point(x, y), randPoint, m_num);
				if (m_position < 0)
				{
					if (n_position < 0)
					{
						randPoint[0][m_num] = Point(x, y);
						m_num++;
					}
					else
					{
						for (int k = m_num; k>n_position; k--)
						{
							randPoint[0][k] = randPoint[0][k - 1];
						}
						randPoint[0][n_position + 1] = Point(x, y);
						m_num++;
					}
				}  */
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
		}
	}

	/*********右击删除坐标*************/
	if (event == CV_EVENT_RBUTTONDOWN&&rightButtonDownFlag == false && flagLBUTTON == false)
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
	failNum = 0;
	m_num = 0;
	totalArea = 0;
	singleArea = 0;
	leftButtonDownFlag = false;
	rightButtonDownFlag = false;
	flagLBUTTON = false;
}

void keyOperation()
{
	char charkey;
	charkey = waitKey(10);
	if (charkey=='o'||charkey=='O')
	{
		string sz = "退出";
		MessageBoxA(NULL, sz.c_str(), "提示", IDOK);
	}
	if (charkey == 'C' || charkey == 'c')
	{
		Initial();
	}
}
Mat  Help(Mat src,int flag)
{
	switch (flag)
	{
	case 1:
		putText(src, initialName, textPoint, textRaduis, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, textRaduis, fontScale, textColor, textthickness, lineType);
	//	putText(src, goOut, goOutPoint, textRaduis, fontScale, textColor, textthickness, lineType);

		break;
	case 2:
		putText(src, personIn, textPoint, textRaduis, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, textRaduis, fontScale, textColor, textthickness, lineType);
	//	putText(src, goOut, goOutPoint, textRaduis, fontScale, textColor, textthickness, lineType);

		break;
	case 3:
		putText(src, personOut, textPoint, textRaduis, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, textRaduis, fontScale, textColor, textthickness, lineType);
	//	putText(src, goOut, goOutPoint, textRaduis, fontScale, textColor, textthickness, lineType);

		break;
	default:
		break;
	}
	return src;
}