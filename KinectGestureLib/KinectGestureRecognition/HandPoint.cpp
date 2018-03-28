#define DLL_IMPLEMENT

#include "HandPoint.h"
#include "utils.h" 

HandPoint::HandPoint()
{
	m_depthX = m_depthY = 0;

	m_cameraZ = 0;
}


HandPoint::HandPoint(int x, int y, float z, float dis) : m_depthX(x), m_depthY(y), m_cameraZ(z), m_disFromCenter(dis)
{
}


HandPoint::HandPoint(int x, int y, float z) :m_depthX(x), m_depthY(y), m_cameraZ(z)
{
}

HandPoint::~HandPoint()
{
}

void HandPoint::setFingerPoint(bool isFingerPoint)
{
	m_isFingerPoint = isFingerPoint;
}

bool HandPoint::isFingerPoint()
{
	return m_isFingerPoint;
}

//��̬������
//�����㹹�ɵ����������Ĳ��(p0p1 �� p0p2)
int HandPoint::crossProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthY - p0.m_depthY) - (p2.m_depthX - p0.m_depthX) * (p1.m_depthY - p0.m_depthY);
}

//��̬������
//�����㹹�ɵ����������ĵ��(p0p1 �� p0p2 )
int HandPoint::dotProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthX - p0.m_depthX) + (p1.m_depthY - p0.m_depthY) * (p2.m_depthY - p0.m_depthY);
}


//��̬������
//��ά�ռ��������㹹�ɵ����������ĵ��(p0p1 �� p0p2 )
float HandPoint::dotProduct3d(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthX - p0.m_depthX) 
		+ (p1.m_depthY - p0.m_depthY) * (p2.m_depthY - p0.m_depthY) 
		+ (p1.m_cameraZ - p0.m_cameraZ) * (p2.m_cameraZ - p0.m_cameraZ);
}


//��̬������
//������ά�ռ�����������ָ���֮��ľ���ֵ
float HandPoint::disBtw2Points3d(int x1, int y1, float z1, int x2, int y2, float z2)
{
	float dis2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
	float distance = sqrt(dis2);
	return distance;
}

//��̬������
//������ά�ռ�����������ָ���֮��ľ���ֵ
float HandPoint::disBtw2Points3d(HandPoint & p1, HandPoint & p2)
{
	return disBtw2Points3d(p1.m_depthX, p1.m_depthY, p1.m_cameraZ, p2.m_depthX, p2.m_depthY, p2.m_cameraZ);
}

//��̬������
//������������ָ���֮��ľ���ֵ
float HandPoint::disBtw2Points(int x1, int y1, int x2, int y2)
{
	float dis2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	float distance = sqrt(dis2);
	return distance;
}



//��̬������
//������������ָ���֮��ľ���ֵ
float HandPoint::disBtw2Points(HandPoint & p1, HandPoint &  p2)
{
	return disBtw2Points(p1.m_depthX, p1.m_depthY, p2.m_depthX, p2.m_depthY);
}


//��̬������
//������������ָ���֮���б��
float HandPoint::slopeBtw2Points(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		if (y1 > y2)
			return FLT_MAX;
		else if (y1 == y2)
			return 0;
		else
			return FLT_MIN;
	}
	float dx = x1 - x2;
	float dy = y1 - y2;
	return dy / dx;
}
//��̬������
//������������ָ���֮���б��
float HandPoint::slopeBtw2Points(HandPoint & p1, HandPoint & p2)
{
	return slopeBtw2Points(p1.m_depthX, p1.m_depthY, p2.m_depthX, p2.m_depthY);
}

//��̬����
//�����γɵ�ֱ����y�����������ͼ��y������������Ļ�·����γɵļн�
float HandPoint::angleBtw2Points(int x1, int y1, int x2, int y2, float distance)
{
	float dx = x2 - x1;
	float sinValue = dx / distance;
	float angle = asinf(sinValue) * 180.0 / PI;
		
	//�۽�
	if (y2 > y1)
	{
		angle = 180 - angle;
	}

	return angle;
}

//��̬������
//������������ָ���֮��ļнǵ�cosin
float HandPoint::cosin(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	float dot = HandPoint::dotProduct(p0, p1, p2);
	float dis10 = HandPoint::disBtw2Points(p0, p1);
	float dis20 = HandPoint::disBtw2Points(p0, p2);
	return dot / (dis10 * dis20);
}

//��̬������
//�����㹹�ɵ�������ά�����ļн�cosֵ��cos< p0p1 , p0p2>
float HandPoint::cosin3d(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	float dot = HandPoint::dotProduct3d(p0, p1, p2);
	float dis10 = HandPoint::disBtw2Points3d(p0, p1);
	float dis20 = HandPoint::disBtw2Points3d(p0, p2);
	return dot / (dis10 * dis20);
}

//��̬������
//ͨ������ͷ����ӳ�䵽��ȿռ�
HandPoint & HandPoint::getHandPoint(ICoordinateMapper * mapper, CameraSpacePoint point)
{
	int depthX, depthY;
	float cameraZ = point.Z;
	DepthSpacePoint dp;
	mapper->MapCameraPointToDepthSpace(point, &dp);
	depthX = dp.X;
	depthY = dp.Y;

	HandPoint handpoint(depthX, depthY, cameraZ);
	return handpoint;
}


