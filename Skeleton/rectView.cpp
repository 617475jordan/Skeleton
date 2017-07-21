#include "rectView.h"

rectView::rectView()
{
	totalArea = -1;
	singleArea = -1;
}
rectView::~rectView()
{

}

/*************��������*************/
/*
src::ͼƬ
randPoint����
m_num �������
flag �Ƿ���Ҫ������� 1��ʾ��Ҫ

*/
Mat  rectView::drawPolygon(Mat src, Point randPoint[1][1024], int m_num, int flag)
{
	Detect detect;
	for (int i = 0; i < m_num; i++)
	{
		if (i < m_num - 1)
		{
			line(src, randPoint[0][i], randPoint[0][i + 1], m_color, thickness);
		}
		else
		{
			line(src, randPoint[0][i], randPoint[0][0], m_color, thickness);
		}
	}
	if (flag == 1)
	{
		const Point* ppt[1] = { randPoint[0] };
		int npt[] = { m_num };
		/*���ܻ��ƶ����**/
		//polylines(src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()

		fillPoly(src, ppt, npt, 1, Scalar(255, 255, 255));
		totalArea = detect.ComputeArea(src);
	}

	for (int i = 0; i < m_num; i++)
	{
		circle(src, randPoint[0][i], raduis, m_color, thickness);
	}

	return src;
}

Mat rectView::drawImage(Mat src, int m_num, vector<Point> coordinate)
{
	m_num = coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		randPoint[0][i] = coordinate[i];
	}
	Mat m_src, n_src;
	src.copyTo(m_src);
	src.copyTo(n_src);
	m_src.setTo(0);
	
	if (m_num > -1)
	{
		m_src = drawPolygon(m_src, randPoint, m_num, 1);
	}
	Mat bitM;
	bitwise_not(src, bitM);
	bitM.copyTo(src);
	bitwise_and(m_src, bitM, bitM);
	Detect detect;
	singleArea = detect.ComputeArea(bitM);


	bitM = drawPolygon(bitM, randPoint, m_num,0);//�����߶�
	src = drawPolygon(src, randPoint, m_num, 0);//�����߶�
	if (totalArea <= 0&&m_num<3)
	{
		n_src=help(src, 1);
	}
	else if (totalArea <= 0 && m_num >= 3)
	{
		n_src = help(bitM, 3);
	}
	else  if (totalArea)
	{
		if (singleArea > 0.1*totalArea)
		{
			n_src=help(bitM, 2);
		}
		else
		{
			n_src=help(bitM, 3);
		}
	}

	return n_src;
}

Mat rectView::help(Mat src, int flag)
{
	switch (flag)
	{
	case 1:
		putText(src, initialName, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	case 2:
		putText(src, personIn, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	case 3:
		putText(src, personOut, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	default:
		break;
	}
	return src;
}