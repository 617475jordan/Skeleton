#include "myKinect.h"
#include "detect.h"
#include <iostream>
using namespace std;


bool draw;
Mat src;//ԭʼͼ��  
Mat roi;//ROIͼ��
Point cursor;//��ʼ����   
Rect rect;//���ROI�ľ��ο�

Point originalPoint; //���ο����  
Point processPoint; //���ο��յ�  
bool leftButtonDownFlag = false; //�����������Ƶ��ͣ���ŵı�־λ  
//���ص�����    
void onMouse(int event, int x, int y, int flags, void *ustc);
int main()
{
	CBodyBasics myKinect;
	Detect detect;

	//��������ʼ��
	HRESULT hr = myKinect.InitializeDefaultSensor();
	int m_num = 1;
	while (FAILED(hr))
	{
		cout << "����ʧ�ܣ����ڳ���,��ǰʧ�ܴ���Ϊ:" << m_num << endl;
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

void onMouse(int event, int x, int y, int flags, void *ustc)
{

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		leftButtonDownFlag = true; //��־λ  
		originalPoint = Point(x, y);  //����������µ�ľ������  
		processPoint = originalPoint;
	}
	if (event == CV_EVENT_MOUSEMOVE&&leftButtonDownFlag)
	{
		processPoint = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		leftButtonDownFlag = false;
		Mat rectImage = src(Rect(originalPoint, processPoint)); //��ͼ����ʾ  
		imshow("src", rectImage);
	}
}