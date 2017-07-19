#include "main.h"
int main()
{
	CBodyBasics myKinect;
	Detect detect;

	//��������ʼ��
	HRESULT hr = myKinect.InitializeDefaultSensor();
	while (FAILED(hr))
	{
		cout << "����ʧ�ܣ����ڳ���,��ǰʧ�ܴ���Ϊ:" << m_num << endl;
		hr = myKinect.InitializeDefaultSensor();
		m_num++;
	} 	

	if (SUCCEEDED(hr))
	{
		cout << "����������������:" ;
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
				/**************���ƶ����*******/
				src.copyTo(m_src);
				m_src.setTo(0);

				if (m_num > -1)
				{
					const Point* ppt[1] = { randPoint[0] };
					int npt[] = { m_num };
					polylines(m_src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
					fillPoly(m_src, ppt, npt, 1, Scalar(255,255,255));
					totalArea = detect.ComputeArea(m_src);
					for (int i = 0; i < m_num; i++)
					{
//						circle(src, randPoint[0][i], raduis, m_color, thickness);
						circle(m_src, randPoint[0][i], raduis, m_color, thickness);

					}

				}
				Mat bitM;
				bitwise_not(src, bitM);
				src = bitM;
				//imshow("src", src);
				//waitKey(1);
				bitwise_and(m_src, src, bitM);
			    singleArea = detect.ComputeArea(bitM);

				if (singleArea > 0.1*totalArea)
				{
					cout << "People in" << endl;
				}
				else
				{
					cout << "People out" << endl;
				}
				if (totalArea > 0)
				{
					const Point* ppt[1] = { randPoint[0] };
					int npt[] = { m_num };
					polylines(bitM, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()
					totalArea = detect.ComputeArea(m_src);
					for (int i = 0; i < m_num; i++)
					{
						circle(bitM, randPoint[0][i], raduis, m_color, thickness);
					}
					src = bitM;
					imshow("src", src);		
					waitKey(1);
				}
				else
				{
					imshow("src", src);
					waitKey(1);
				}
			
			}

			if (waitKey(10) >= 0)
			{
				string sz = "�˳�";
				MessageBoxA(NULL, sz.c_str(), "��ʾ", IDOK);
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
	/***********����������*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag==false)
	{
		if (m_num >= numPoint)
		{
			m_num = 0;
		}
		leftButtonDownFlag = true; //��־λ  
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

	/*********�һ�ɾ������*************/
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
	totalArea = 0;
	singleArea = 0;
	leftButtonDownFlag = false;
	rightButtonDownFlag = false;
}