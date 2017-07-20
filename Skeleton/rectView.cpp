#include "rectView.h"

rectView::rectView()
{

}
rectView::~rectView()
{

}
Mat rectView::DrawImage(Mat src, int m_num, vector<Point> coordinate)
{
	m_num = coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		randPoint[0][i] = coordinate[i];
	}
	Mat m_src;
	src.copyTo(m_src);
	m_src.setTo(0);
	Detect detect;
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
	if (totalArea <= 0)
	{
		return src;
	}
	else  if (totalArea>0)
	{
		return m_src;
	}
}