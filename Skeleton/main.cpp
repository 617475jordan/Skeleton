#include "main.h"
int main()
{
	CBodyBasics myKinect;
	rectModel rectModel;
	rectView rectView;
	//��������ʼ��
	HRESULT hr = myKinect.InitializeDefaultSensor();
	while (FAILED(hr))
	{
		cout << "����ʧ�ܣ����ڳ���,��ǰʧ�ܴ���Ϊ:" << failNum << endl;
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
				src=rectView.DrawImage(src, m_num, coordinate);
				imshow("src", src);
				waitKey(1);
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
	rectModel rectModel;
	/***********���������꣬�������*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag == false)
	{
		rectModel.onMouseDown(x, y);
		//leftButtonDownFlag = true; //��־λ 
	}
	/***********���������꣬�ƶ����*****************/
	if (event == CV_EVENT_MOUSEMOVE &&leftButtonDownFlag)
	{
		rectModel.onMouseMove(x, y);
		coordinate=rectModel.MoveCoordinate(randPoint, m_num, x, y);
	}
	/***********���������̧꣬�����*****************/
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
		rectModel.onMouseUp();
		leftButtonDownFlag = false;
		coordinate=rectModel.AddCoordinate(randPoint, m_num, x, y);
	}
	/*********�һ�ɾ������*************/
	if (event == CV_EVENT_RBUTTONDOWN&&rightButtonDownFlag == false)
	{
		rightButtonDownFlag = true;
	}
	if (event == CV_EVENT_RBUTTONUP&&rightButtonDownFlag)
	{
		leftButtonDownFlag = false;
		coordinate=rectModel.DeleteCoordinate(randPoint, m_num, x, y);
	}
	m_num=coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		randPoint[0][i] = coordinate[i];
	}
}


void Initial()
{
	failNum = 0;
	m_num = 0;
}

void keyOperation()
{
	char charkey;
	charkey = waitKey(10);
	if (charkey=='o'||charkey=='O')
	{
		string sz = "�˳�";
		MessageBoxA(NULL, sz.c_str(), "��ʾ", IDOK);
	}
	if (charkey == 'C' || charkey == 'c')
	{
		Initial();
	}
}
