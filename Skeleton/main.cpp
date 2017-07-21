#include "main.h"
int main()
{
	CBodyBasics myKinect;
	rectModel rectModel;
	rectView rectView;

	//传感器初始化
	HRESULT hr = myKinect.InitializeDefaultSensor();
	initial();
	while (FAILED(hr))
	{
		cout << "连接失败，正在尝试,当前失败次数为:" << failNum << endl;
		hr = myKinect.InitializeDefaultSensor();
		failNum++;
	} 	

	if (SUCCEEDED(hr))
	{
		namedWindow(windowName);
		setMouseCallback(windowName, onMouse);
		while (1)
		{
			src = myKinect.Update();
			if (src.empty())
			{
				src = myKinect.Update();
			}
			else
			{
				width = src.cols;
				height = src.rows;
				src=rectView.drawImage(src, m_num, coordinate);
				imshow(windowName, src);
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


void onMouse(int event, int x, int y, int flags, void *ustc)
{
	rectModel rectModel;
	/***********左键添加坐标，按下左键*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag == false)
	{
		leftButtonDownFlag=rectModel.onMouseLeftDown(x, y,width,height);
	}
	/***********左键添加坐标，移动左键*****************/
	if (event == CV_EVENT_MOUSEMOVE &&leftButtonDownFlag)
	{
		coordinate=rectModel.moveCoordinate(randPoint, m_num, x, y);
	}
	/***********左键添加坐标，抬起左键*****************/
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
		leftButtonDownFlag = rectModel.onMouseLeftUp(x, y, width, height);
		coordinate=rectModel.addCoordinate(randPoint, m_num, x, y);
	}
	/*********右击删除坐标,按下右键**************/
	if (event == CV_EVENT_RBUTTONDOWN&&rightButtonDownFlag == false)
	{
		rightButtonDownFlag = rectModel.onMouseRightDown(x, y, width, height);
	}
	/*********右击删除坐标,抬起右键**************/
	if (event == CV_EVENT_RBUTTONUP&&rightButtonDownFlag)
	{
		rightButtonDownFlag = rectModel.onMouseRightUp(x, y, width, height);
		coordinate=rectModel.deleteCoordinate(randPoint, m_num, x, y);
	}
	m_num=coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		randPoint[0][i] = coordinate[i];
	}
}


void initial()
{
	failNum = 0;
	m_num = 0;
	coordinate.clear();
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
		string sz = "退出";
		MessageBoxA(NULL, sz.c_str(), "初始化数据", IDOK);
		initial();
	}
}
