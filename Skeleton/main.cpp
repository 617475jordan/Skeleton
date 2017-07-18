#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;


bool draw;
Mat src;//原始图像  
Mat roi;//ROI图像
Point cursor;//初始坐标   
Rect rect;//标记ROI的矩形框

Point originalPoint; //矩形框起点  
Point processPoint; //矩形框终点  
bool leftButtonDownFlag = false; //左键单击后视频暂停播放的标志位  
//鼠标回调函数    
void onMouse(int event, int x, int y, int flags, void *ustc);
int main()
{
	CBodyBasics myKinect;
	Detect detect;

	//传感器初始化
	HRESULT hr = myKinect.InitializeDefaultSensor();
	int m_num = 1;
	while (FAILED(hr))
	{
		cout << "连接失败，正在尝试,当前失败次数为:" << m_num << endl;
		hr = myKinect.InitializeDefaultSensor();
		m_num++;
	} 	

	namedWindow("src");
	setMouseCallback("src", onMouse);
	if (SUCCEEDED(hr))
	{
		//setMouseCallback("src", onMouse, NULL);
		while (1)
		{
			src = myKinect.Update();
			if (src.empty())
			{
				src = myKinect.Update();
			}
			else
			{	
				if (originalPoint != processPoint)
				{
					rectangle(src, originalPoint, processPoint, Scalar(255, 0, 0), 2);
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

void onMouse(int event, int x, int y, int flags, void *ustc)
{

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		leftButtonDownFlag = true; //标志位  
		originalPoint = Point(x, y);  //设置左键按下点的矩形起点  
		processPoint = originalPoint;
	}
	if (event == CV_EVENT_MOUSEMOVE&&leftButtonDownFlag)
	{
		processPoint = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		leftButtonDownFlag = false;
		Mat rectImage = src(Rect(originalPoint, processPoint)); //子图像显示  
		imshow("src", rectImage);
	}
}