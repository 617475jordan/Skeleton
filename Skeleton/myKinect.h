#pragma once
#include <Kinect.h>
#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

class CBodyBasics
{
	//kinect 2.0 ����ȿռ�ĸ�*���� 424 * 512���ڹ�������˵��
	static const int        cDepthWidth = 512;
	static const int        cDepthHeight = 424;

public:
	CBodyBasics();
	~CBodyBasics();
	Mat                    Update();//��ùǼܡ�������ֵͼ�������Ϣ
	HRESULT                 InitializeDefaultSensor();//���ڳ�ʼ��kinect

private:
	IKinectSensor*          m_pKinectSensor=NULL;//kinectԴ
	ICoordinateMapper*      m_pCoordinateMapper=NULL;//��������任
	IBodyFrameReader*       m_pBodyFrameReader = NULL;//���ڹǼ����ݶ�ȡ
	IDepthFrameReader*      m_pDepthFrameReader = NULL;//����������ݶ�ȡ
	IBodyIndexFrameReader*  m_pBodyIndexFrameReader = NULL;//���ڱ�����ֵͼ��ȡ

	//ͨ����õ�����Ϣ���ѹǼܺͱ�����ֵͼ������
	void                    ProcessBody(int nBodyCount, IBody** ppBodies);
	//���Ǽܺ���
	void DrawBone(const Joint* pJoints, const DepthSpacePoint* depthSpacePosition, JointType joint0, JointType joint1);
	//���ֵ�״̬����
	void DrawHandState(const DepthSpacePoint depthSpacePosition, HandState handState);

	//��ʾͼ���Mat
	cv::Mat skeletonImg;
	cv::Mat depthImg;
};

