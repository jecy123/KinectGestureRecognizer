#pragma once
#include "dllapi.h"
#include "utils.h"
#include "Hand.h"
#include "CVHelper.h"
#include "GestureRecgnition.h"

class DLL_API KinectHelper
{
public:

	KinectHelper();
	virtual ~KinectHelper();

	void setGestureHandler(GestureRecgnition * pRecgnition);

	static void Run();
	HRESULT init();
	void	deInit();
	void	startRefreshData(GestureRecgnition * pRecgnition = nullptr);
	void	stopRefreshData();
	HRESULT UpdateFrame();
	
private:
	HRESULT initDepth();
	HRESULT initBody();
	
	HRESULT UpdateDepthData();
	HRESULT UpdateBodyData();

	IKinectSensor *			m_pKinectSensor;
	ICoordinateMapper *		m_pCoordinateMapper;
	IDepthFrameReader *		m_pDepthFrameReader;
	IBodyFrameReader *		m_pBodyReader;

	UINT16 *				m_pDepthArray;
	Hand *					m_pLeftHand;
	Hand *					m_pRightHand;
	CVHelper *				m_pCVHelper;
	GestureRecgnition *		m_pGestureRecgnition;

	bool					m_bRunning;

protected:
	virtual void onInit(){};
	virtual void onDepthDataArrived(){};
	virtual void onBodyDataArrived(){};
	virtual void onDestroy(){};
};

