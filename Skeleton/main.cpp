#include "myKinect.h"
#include <iostream>
using namespace std;

int main()
{
	CBodyBasics myKinect;
	//传感器初始化
	HRESULT hr = myKinect.InitializeDefaultSensor();
	if (SUCCEEDED(hr))
	{
		while (1)
		{
			myKinect.Update();
		}
	}
	else
	{
		cout << "kinect initialization failed!" << endl;
		system("pause");
	}
}