#define DLL_IMPLEMENT

#include "Hand.h"
#include "utils.h"


HandPoint cMaxYhandPoint;


inline bool cmp(HandPoint p1, HandPoint p2)
{

	int ret = HandPoint::crossProduct(cMaxYhandPoint, p1, p2);
	if (ret < 0)
		return true;
	if (ret > 0)
		return false;
	return false;
}

Hand::Hand()
{
	initHandArray();
	initVisited();
	maxDis = 0;
}


void Hand::initHandArray()
{
	for (int i = 0; i < cDepthHeight; i++)
	{
		for (int j = 0; j < cDepthWidth; j++)
		{
			m_pHandAreaArray[i][j] = false;
			m_pHandLineArray[i][j] = false; 
			//m_pHandOutLineArray[i][j] = false;
		}
	}
}

void Hand::initFingerArray()
{
	/*for (int i = 0; i < MAX_FINGERCNT; i++)
	{
		m_pMax5FingerPoint[i].m_depthX = 0;
		m_pMax5FingerPoint[i].m_depthY = 0;
		m_pMax5FingerPoint[i].m_cameraZ = 0;
		m_pMax5FingerPoint[i].m_disFromCenter = 0.0;
	}

	for (int i = 0; i < MAX_IN_FINGER; i++)
	{
		m_pMin4FingerPoint[i].m_depthX = 0;
		m_pMin4FingerPoint[i].m_depthY = 0;
		m_pMin4FingerPoint[i].m_cameraZ = 0;
		m_pMin4FingerPoint[i].m_disFromCenter = FLT_MAX;
	}*/

	HandFingers.clear();
}

void Hand::refreshHandData(ICoordinateMapper * mapper, IBody * pBody, UINT16 * depthArray)
{
	if (pBody != NULL)
	{
		Joint joints[JointType_Count];

		pBody -> GetJoints(JointType_Count, joints);
		//获取手掌的状态
		if (this->m_handType == __handType::typeRightHand){
			pBody->get_HandRightState(&m_handState);
		}
		else if (this->m_handType == __handType::typeLeftHand)
		{
			pBody->get_HandLeftState(&m_handState);
		}

		this -> refreshHandData(mapper, joints, depthArray);
	}
}
void Hand::getHandArea(ICoordinateMapper * mapper, UINT16 * depthArray)
{
	for (int i = m_leftTopHandPoint.m_depthY; i <= m_rightBottomHandPoint.m_depthY; i++)
	{
		for (int j = m_leftTopHandPoint.m_depthX; j <= m_rightBottomHandPoint.m_depthX; j++)
		{
			int k = i * cDepthWidth + j;
			float CameradepthZ = getCameraZFromDepthXY(mapper, j, i, depthArray[k]);
			if (CameradepthZ >= this->HandCenter.m_cameraZ - depthThreshold && CameradepthZ <= this->HandCenter.m_cameraZ + depthThreshold)
			{
				m_pHandAreaArray[i][j] = true;
			}
			else{
				m_pHandAreaArray[i][j] = false;
			}
		}
	}
}

void Hand::getHandOutline(ICoordinateMapper * mapper, UINT16 * depthArray)
{
	int maxI = 0;

	for (int i = m_leftTopHandPoint.m_depthY; i <= m_rightBottomHandPoint.m_depthY; i++)
	{
		for (int j = m_leftTopHandPoint.m_depthX; j <= m_rightBottomHandPoint.m_depthX; j++)
		{
			//m_pHandLineArray[i][j] = checkIsOutline(j, i);

			if (m_pHandAreaArray[i][j])
			{
				bool top = i - 1 >= 0 ? m_pHandAreaArray[i - 1][j] : false;
				bool bottom = i + 1 < cDepthHeight ? m_pHandAreaArray[i + 1][j] : false;
				bool left = j - 1 >= 0 ? m_pHandAreaArray[i][j - 1] : false;
				bool right = j + 1 < cDepthWidth ? m_pHandAreaArray[i][j + 1] : false;
				bool isInContour = !top || !bottom || !left || !right;
				m_pHandLineArray[i][j] = isInContour;
				if (isInContour)
				{
					HandPoint p(j, i, getCameraZFromDepthXY(mapper, j, i, depthArray[i * cDepthWidth + j]));

					if (i > maxI)
					{
						maxI = i;
						HandOutline.insert(HandOutline.begin(), p);
					}
					else{
						HandOutline.push_back(p);
					}
				}
			}
		}
	}
	//轮廓点数组排序
	/*if (HandOutline.size()>2)
	{
		cMaxYhandPoint = HandOutline[0];
		sort(HandOutline.begin() + 1, HandOutline.end(), cmp);
	}*/

	for (int i = 0; i < HandOutline.size(); i++)
	{
		HandOutline[i].m_disFromCenter = HandPoint::disBtw2Points(HandOutline[i], HandCenter);
	}
}

void Hand::refreshHandData(ICoordinateMapper * mapper, Joint joints[JointType_Count],UINT16 * depthArray)
{
	initHandArray();
	initFingerArray();

	clearHandOutLineVector();
	maxDis = 0;


	//手的掌心点：
	CameraSpacePoint pointCenter;
	//手的腕关节点
	CameraSpacePoint pointWrist;
	//手的指尖节点
	CameraSpacePoint pointTip;
	//手拇指节点
	CameraSpacePoint pointThumb;

	if (m_handType == __handType::typeRightHand)
	{
		pointCenter = joints[JointType_HandRight].Position;
		pointWrist = joints[JointType_WristRight].Position;
		pointTip = joints[JointType_HandTipRight].Position;
		pointThumb = joints[JointType_ThumbRight].Position;
	}
	else{
		pointCenter = joints[JointType_HandLeft].Position;
		pointWrist = joints[JointType_WristLeft].Position;
		pointTip = joints[JointType_HandTipLeft].Position;
		pointThumb = joints[JointType_ThumbLeft].Position;

	}

	this->HandCenter = HandPoint::getHandPoint(mapper, pointCenter);
	//this->HandWrist	= HandPoint::getHandPoint(mapper, pointWrist);
	this->HandTip = HandPoint::getHandPoint(mapper, pointTip);
	this->HandThumb = HandPoint::getHandPoint(mapper, pointThumb);

	this->HandWrist.m_cameraZ = this->HandCenter.m_cameraZ;
	this->HandWrist.m_depthX = this->HandCenter.m_depthX;
	this->HandWrist.m_depthY = this->HandCenter.m_depthY + 20;

	//mapper->MapDepthFrameToCameraSpace(cDepthHeight * cDepthWidth, depthArray, cDepthHeight*cDepthWidth, m_points);

	calculateHandRect();
	getHandArea(mapper, depthArray);
	getHandOutline(mapper, depthArray);
	
	//
	float longestDis = 0;
	for (int i = 0; i < HandOutline.size(); i++)
	{
		if (longestDis < HandOutline[i].m_disFromCenter && HandOutline[i].m_depthY < HandCenter.m_depthY)
		{
			longestDis = HandOutline[i].m_disFromCenter;
			this->FingerTip = HandOutline[i];
		}
	}
	//checkFingerPoint();
}


void Hand::clearHandOutLineVector()
{
	HandOutline.clear();
}

Hand::~Hand()
{
	clearHandOutLineVector();
}


UINT16 Hand::conventArray(int x, int y, __checkType type)
{
	bool(*array)[cDepthHeight][cDepthWidth];
	if (type == TYPE_HAND_AREA)
	{
		array = &m_pHandAreaArray;
	}
	else{
		array = &m_pHandLineArray;
	}
	if ((*array)[y][x])
	{
		return 0x1;
	}
	return 0x0;
}


bool Hand::dealWithOutline(int x, int y)
{
	if (m_pHandLineArray[y][x])
	{
		UINT16 handCheck = 0x0000 |
			conventArray(x, y, TYPE_HAND_OUTLINE) << 8 |
			conventArray(x - 1, y - 1, TYPE_HAND_OUTLINE) << 7 |
			conventArray(x - 1, y, TYPE_HAND_OUTLINE) << 6 |
			conventArray(x - 1, y + 1, TYPE_HAND_OUTLINE) << 5 |
			conventArray(x, y + 1, TYPE_HAND_OUTLINE) << 4 |
			conventArray(x + 1, y + 1, TYPE_HAND_OUTLINE) << 3 |
			conventArray(x + 1, y, TYPE_HAND_OUTLINE) << 2 |
			conventArray(x + 1, y - 1, TYPE_HAND_OUTLINE) << 1 |
			conventArray(x, y - 1, TYPE_HAND_OUTLINE);
		//去除直角点
		if (handCheck & 0x0141 == 0x0141 
			|| handCheck & 0x0101 == 0x0101 
			|| handCheck & 0x0150 == 0x0150 
			|| handCheck & 0x0114 == 0x0114)
		{
			return false;
		}

		int cnt = 0;
		for (int i = 0; i <= 8; i++)
		{
			if ((handCheck >> i) & 0x0001 == 0x0001)
			{
				cnt++;
			}
		}
		if (cnt == 3)
		{
			return true;
		}
		return false;
	}
	
	return false;
}

bool Hand::checkIsOutline(int x, int y)
{
	if (x == 0 || x == cDepthWidth-1||y == 0 || y==cDepthHeight-1)
	{
		return false;
	}
	/*UINT16 handCheck = 0x0000 |
		conventArray(x, y) << 8 |
		conventArray(x - 1, y - 1) << 7 |
		conventArray(x - 1, y) << 6 |
		conventArray(x - 1, y + 1) << 5 |
		conventArray(x, y + 1) << 4 |
		conventArray(x + 1, y + 1) << 3 |
		conventArray(x + 1, y) << 2 |
		conventArray(x + 1, y - 1) << 1 |
		conventArray(x, y - 1);
	*/
	UCHAR handCheck = 0x00 |
		conventArray(x, y) << 4 |
		conventArray(x - 1, y) << 3 |
		conventArray(x + 1, y) << 2 |
		conventArray(x, y - 1) << 1 |
		conventArray(x, y + 1);


	if (handCheck == 0x1f || handCheck == 0x00)
	{
		return false;
	}
	return true;
}

float Hand::getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ)
{
	DepthSpacePoint depthPoint;
	CameraSpacePoint cameraPoint;

	depthPoint.X = (float)x;
	depthPoint.Y = (float)y;

	mapper->MapDepthPointToCameraSpace(depthPoint, DepthZ, &cameraPoint);
	return cameraPoint.Z;

	//return m_points[y * cDepthWidth + x].Z;
}

void Hand::calculateHandRect()
{
	/*float distanceHandTip = HandPoint::disBtw2Points(HandTip, HandCenter);
	float distanceHandThumb = HandPoint::disBtw2Points(HandThumb, HandCenter);

	float distanceMax = max(distanceHandTip, distanceHandThumb);
	int XOffsetFromCenter = 2 * static_cast<int>(distanceMax);
	int YOffsetFromCenter = 2 * static_cast<int>(distanceMax);*/

		
	int XOffsetFromCenter = static_cast<int>(40 * (2 - HandCenter.m_cameraZ));
	int YOffsetFromCenter = static_cast<int>(60 * (2 - HandCenter.m_cameraZ));
	
	m_leftTopHandPoint.m_depthX = max(HandCenter.m_depthX - XOffsetFromCenter, 0);
	m_leftTopHandPoint.m_depthY = max(HandCenter.m_depthY - YOffsetFromCenter, 0);

	m_rightBottomHandPoint.m_depthX = min(HandCenter.m_depthX + XOffsetFromCenter, cDepthWidth - 1);
	m_rightBottomHandPoint.m_depthY = min(HandCenter.m_depthY + YOffsetFromCenter, cDepthHeight - 1);
}


void Hand::initVisited()
{
	for (int i = 0; i < cDepthHeight; i++)
	{
		for (int j = 0; j < cDepthWidth; j++)
		{
			m_visited[i][j] = false;
		}
	}
}


void Hand::setHandType(__handType type)
{
	this->m_handType = type;
}

void Hand::checkFingerPoint()
{
	int k = 2;
	int j = 0;
	for (int i = k; i + k < HandOutline.size(); i++)
	{
		/*float dis1 = HandPoint::disBtw2Points(HandOutline[i - k], HandCenter);
		float dis2 = HandPoint::disBtw2Points(HandOutline[i], HandCenter);
		float dis3 = HandPoint::disBtw2Points(HandOutline[i + k], HandCenter);

		bool isSharpPoint = dis2 > dis1 && dis2 > dis3;*/

		bool isAboveCenter = HandOutline[i].m_depthY < HandWrist.m_depthY;
		bool isAcuteAngle = HandPoint::cosin(HandOutline[i], HandOutline[i - k], HandOutline[i + k]) >= 0.5;
		bool isFinger = HandPoint::crossProduct(HandOutline[i], HandOutline[i - k], HandOutline[i + k]) > 20;

		if (isAboveCenter && isAcuteAngle && isFinger)
		{
			HandFingers.push_back(HandOutline[i]);
			/*m_pMax5FingerPoint[j++] = HandOutline[i];
			if (j == 10)
			{

				break;
			}*/
		}
		/*
		float dis1 = HandPoint::disBtw2Points(HandOutline[i - k], HandCenter);
		float dis2 = HandPoint::disBtw2Points(HandOutline[i], HandCenter);
		float dis3 = HandPoint::disBtw2Points(HandOutline[i + k], HandCenter);
		if (dis2 > dis1 && dis2 > dis3)
		{
			m_pMax5FingerPoint[j++] = HandOutline[i];
			if (j == 5)
			{

				break;
			}
		}*/
	}
}

//void Hand::checkFingerPoint(ICoordinateMapper * mapper, UINT16 * depthArray)
//{
//	initVisited();
//	clearHandOutLineVector();
//	//找到第一个轮廓点：
//	int x = HandCenter.m_depthX;
//	int y = HandCenter.m_depthY;
//	while (!m_pHandLineArray[y][x]){
//		x--; 
//		if (x == 0)
//		{
//			break;
//		}
//	}
//
//	if (!m_pHandLineArray[y][x])
//	{
//		return;
//	}
//	int nx, ny;
//
//	while (true){
//
//		float z = getCameraZFromDepthXY(mapper, x, y, depthArray[y * cDepthWidth + x]);
//		HandPoint *point = new HandPoint(x, y, z);
//
//		HandOutline.push_back(point);
//
//		findNextXY(x, y, nx, ny);
//		if (nx == -1 && ny == -1)
//		{
//			break;
//		}
//		x = nx;
//		y = ny;
//	}
//
//}


void Hand::findNextXY(const int & oldX, const int & oldY, int & newX, int & newY)
{
	if (m_pHandLineArray == nullptr)
	{
		return;
	}
	int startX = oldX - 1;
	int startY = oldY - 1;
	
	int endX = oldX - 1;
	int endY = oldY;


	if (oldY == 0)
	{
		//左上边界：
		if (oldX == 0)
		{
			startX = oldX + 1;
			startY = oldY;
			endX = oldX;
			endY = oldY + 1;
		}
		//右上边界：
		else if(oldX == cDepthWidth - 1){
			startX = oldX;
			startY = oldY + 1;
			endX = oldX - 1;
			endY = oldY;
		}
		//上边界：
		else{
			startX = oldX + 1;
			startY = oldY;
			endX = oldX - 1;
			endY = oldY;
		}
	}

	if (oldY == cDepthHeight - 1)
	{
		//左下边界：
		if (oldX == 0)
		{
			startX = oldX;
			startY = oldY - 1;
			endX = oldX + 1;
			endY = oldY;
		}
		//右下边界：
		else if (oldX == cDepthWidth - 1){
			startX = oldX - 1;
			startY = oldY;
			endX = oldX;
			endY = oldY - 1;
		}
		//下边界：
		else{
			startX = oldX - 1;
			startY = oldY;
			endX = oldX + 1;
			endY = oldY;
		}
	}
	
	while (true)
	{
		if (!m_visited[startY][startX] && m_pHandLineArray[startY][startX])
		{
			m_visited[startY][startX] = true;
			break;
		}

		m_visited[startY][startX] = true;

		if (startX == endX && startY == endY)
		{
			break;
		}

		if (startY == oldY - 1 && startX < oldX + 1)
		{
			startX++;
		}
		
		if (startX == oldX + 1 && startY < oldY + 1)
		{
			startY++;
		}
		if (startY == oldY + 1 && startX > oldX - 1)
		{
			startX--;
		}
		if (startX == oldX - 1 && startY > oldY - 1)
		{
			startY--;
		}
	}

	if (m_pHandLineArray[startY][startX])
	{
		newX = startX;
		newY = startY;
	}
	else
	{
		newX = -1;
		newY = -1;
	}
}