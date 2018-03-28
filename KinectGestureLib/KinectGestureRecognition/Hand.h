#pragma once
#include "utils.h"
#include "HandPoint.h"
#include "dllapi.h"

#define MAX_FINGERCNT 50
#define MAX_IN_FINGER 4

enum DLL_API __handType
{
	typeLeftHand,
	typeRightHand
};

enum DLL_API __checkType
{
	TYPE_HAND_AREA,
	TYPE_HAND_OUTLINE
};



class DLL_API Hand
{
public:
	Hand();
	~Hand();
	void initHandArray();
	void initFingerArray();
	void clearHandOutLineVector();
	void refreshHandData(ICoordinateMapper * mapper, Joint joints[JointType_Count], UINT16 * depthArray);
	void refreshHandData(ICoordinateMapper * mapper, IBody * pBody, UINT16 * depthArray);
//	void checkFingerPoint(ICoordinateMapper * mapper, UINT16 * depthArray);
	void checkFingerPoint();
	void setHandType(__handType type);

	//void refreshHandAreaArray();
	HandPoint	HandCenter;
	HandPoint	HandWrist;
	HandPoint	FingerTip;
	HandPoint	HandTip;
	HandPoint	HandThumb;

	//HandPoint	m_pMax5FingerPoint[MAX_FINGERCNT];
	//HandPoint	m_pMin4FingerPoint[MAX_IN_FINGER];

	double		maxDis;
	HandPoint	m_leftTopHandPoint;
	HandPoint	m_rightBottomHandPoint;

	HandState	m_handState;
	__handType	m_handType;

	bool		m_pHandAreaArray[cDepthHeight][cDepthWidth];
	bool		m_pHandLineArray[cDepthHeight][cDepthWidth];
	//bool		m_pHandOutLineArray[cDepthHeight][cDepthWidth];
	vector < HandPoint > HandOutline;
	vector < HandPoint > HandFingers;
private:

	bool				m_visited[cDepthHeight][cDepthWidth];
	CameraSpacePoint	m_points[cDepthHeight * cDepthWidth];
	void	initVisited();
	void	calculateHandRect();
	float	getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ);
	bool	checkIsOutline(int x, int y);
	bool	dealWithOutline(int x, int y);
	UINT16	conventArray(int x, int y, __checkType type = TYPE_HAND_AREA);
	void	findNextXY(const int & oldX, const int & oldY, int & newX, int & newY);

	void	getHandArea(ICoordinateMapper * mapper, UINT16 * depthArray);
	void	getHandOutline(ICoordinateMapper * mapper, UINT16 * depthArray);
};

