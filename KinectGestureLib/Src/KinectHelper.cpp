#define DLL_IMPLEMENT

#include "KinectHelper.h"
#include "utils.h"

void KinectHelper::Run()
{
	KinectHelper k;
	k.init();
	k.UpdateFrame();
	k.deInit();
}

void KinectHelper::startRefreshData(GestureRecgnition * pRecgnition)
{
	m_bRunning = true;
	this->init();
	this->setGestureHandler(pRecgnition);
	this->UpdateFrame();
	
}

void KinectHelper::stopRefreshData()
{
	m_bRunning = false;
	this->deInit();
}


HRESULT KinectHelper::UpdateFrame()
{
	HRESULT hr = S_OK;
	while (m_bRunning)
	{
		
		hr = UpdateDepthData();
		hr = UpdateBodyData();	

		if (m_pCVHelper != nullptr && m_pDepthArray != nullptr /*&& m_pRightHand != nullptr*/)
		{
			m_pCVHelper->draw(m_pDepthArray, m_pLeftHand, m_pRightHand);
			m_pCVHelper->show();
			int key = m_pCVHelper->getKeyPressed();
			if (key == VK_ESCAPE)
			{
				cout << "exit" << endl;
				m_bRunning = false;
			}
			else if (key == 'z')
			{
				m_pCVHelper->setShowType(SHOW_TYPE_HAND);
			}
			else if (key == 'x')
			{
				m_pCVHelper->setShowType(SHOW_TYPE_HAND_OUTLINE);
			}
			else if (key == 'c')
			{
				if (m_pCVHelper->showHandCenter)
				{
					m_pCVHelper->showHandCenter = false;
				}
				else
				{
					m_pCVHelper->showHandCenter = true;
				}
			}
			else if (key == 'l')
			{
				if (m_pCVHelper->showLeftHandFlag)
				{
					m_pCVHelper->showLeftHandFlag = false;
				}
				else
				{
					m_pCVHelper->showLeftHandFlag = true;
				}
			}
			else if (key == 'r')
			{
				if (m_pCVHelper->showRightHandFlag)
				{
					m_pCVHelper->showRightHandFlag = false;
				}
				else
				{
					m_pCVHelper->showRightHandFlag = true;
				}
			}
			else if (key == 'q')
			{
				m_pCVHelper->ROIShot();
			}
			else if (key == KeyCode_UP)
			{
				m_pCVHelper->addHandThreshold(1);
			}
			else if (key == KeyCode_DOWN)
			{
				m_pCVHelper->addHandThreshold(-1);
			}
			else
			{
				if (key != -1)
				{
					cout << key << endl;
				}
			}
		}

		if (m_pGestureRecgnition != nullptr)
		{
			m_pGestureRecgnition->refresh(m_pLeftHand, m_pRightHand);
			//m_pGestureRecgnition->update(m_pRightHand);
		}
	}
	return hr;
}

HRESULT KinectHelper::UpdateDepthData()
{
	if (!m_pKinectSensor || !m_pDepthFrameReader)
	{
		return E_POINTER;
	}

	HRESULT hr = -1;
	IDepthFrame * pDepthFrame = nullptr;
	hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame);
	
	if (SUCCEEDED(hr))
	{
		//cout << "�ɹ���ȡ��������ݣ�" << endl;
		hr = pDepthFrame->CopyFrameDataToArray(cDepthHeight * cDepthWidth, m_pDepthArray);
		
	}
	SafeRealease(pDepthFrame);
	return hr;
}


HRESULT KinectHelper::UpdateBodyData()
{
	if (!m_pKinectSensor || !m_pDepthFrameReader)
	{
		return E_POINTER;
	}

	HRESULT hr = -1;
	IBodyFrame * pBodyFrame = nullptr;
	hr = m_pBodyReader->AcquireLatestFrame(&pBodyFrame);
	if (SUCCEEDED(hr))
	{
		IBody * pBody[BODY_COUNT] = { 0 };
		hr = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, pBody);

		if (SUCCEEDED(hr))
		{
			BOOLEAN bTracked = FALSE;
			for (int i = 0; i < BODY_COUNT; i++)
			{
				hr = pBody[i]->get_IsTracked(&bTracked);
				if (SUCCEEDED(hr) && bTracked)
				{
					if (NULL != pBody[i])
					{
						//cout << i << endl;
						//Joint joints[JointType_Count];
						//pBody[i]->GetJoints(JointType_Count, joints);
						m_pLeftHand->refreshHandData(m_pCoordinateMapper, pBody[i], m_pDepthArray);
						m_pRightHand->refreshHandData(m_pCoordinateMapper, pBody[i], m_pDepthArray);
						//m_pRightHand->refreshHandData(m_pCoordinateMapper, joints,  m_pDepthArray);
					}
				}
			}
		}
	}
	SafeRealease(pBodyFrame);
	return hr;
}

HRESULT KinectHelper::init()
{
	HRESULT hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->Open();
		
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}
		if (SUCCEEDED(hr))
		{
			hr = initBody();
		}
		if (SUCCEEDED(hr))
		{
			hr = initDepth();
		}

		if (!m_pKinectSensor || FAILED(hr))
		{
			cout << "��ʼ��Kinectʧ�ܣ�" << endl;
			return E_FAIL;
		}
		cout << "��ʼ��Kinect�ɹ���" << endl;
	}

	m_pDepthArray = new UINT16[cDepthHeight * cDepthWidth];
	m_pCVHelper = new CVHelper;
	m_pGestureRecgnition = new GestureRecgnition;
	m_pRightHand = new Hand;
	m_pLeftHand = new Hand;

	m_pRightHand->setHandType(__handType::typeRightHand);
	m_pLeftHand->setHandType(__handType::typeLeftHand);
	return hr;
}


void KinectHelper::setGestureHandler(GestureRecgnition * pRecgnition)
{
	this->m_pGestureRecgnition = pRecgnition;
}

//void KinectHelper::setGestureEventHandler(GestureEventHandler * pEventHandler)
//{
//	this->m_pEventHandler = pEventHandler;
//	if (this->m_pGestureRecgnition == nullptr)
//	{
//		this->m_pGestureRecgnition = new GestureRecgnition;
//	}
//	this->m_pGestureRecgnition->setGestureEventsHandler(pEventHandler);
//}

HRESULT KinectHelper::initBody()
{
	IBodyFrameSource *pBodyFrameSource = nullptr;
	HRESULT hr = -1;
	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyReader);
		}
	}
	SafeRealease(pBodyFrameSource);
	return hr;
}

HRESULT KinectHelper::initDepth()
{
	IDepthFrameSource * pDepthFrameSource = nullptr;
	HRESULT hr = -1;
	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
		if (SUCCEEDED(hr))
		{
			hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
		}
	}
	SafeRealease(pDepthFrameSource);
	return hr;
}


void KinectHelper::deInit()
{
	BOOLEAN isOpened;
	m_pKinectSensor->get_IsOpen(&isOpened);
	if (isOpened)
	{
		m_pKinectSensor->Close();
	}

	SafeRealease(m_pKinectSensor);
	SafeRealease(m_pCoordinateMapper);
	SafeRealease(m_pDepthFrameReader);
	SafeRealease(m_pBodyReader);
	
	if (m_pDepthArray != nullptr)
	{
		delete[] m_pDepthArray;
	}

	if (m_pLeftHand != nullptr)
	{
		delete m_pLeftHand;
	}

	if (m_pRightHand != nullptr)
	{
		delete m_pRightHand;
	}

	if (m_pCVHelper != nullptr)
	{
		delete m_pCVHelper;
	}

	if (m_pGestureRecgnition != nullptr)
	{
		delete m_pGestureRecgnition;
	}

	//if (m_pEventHandler != nullptr)
	//{
	//	delete m_pEventHandler;
	//}
}

KinectHelper::KinectHelper()
{
	m_pKinectSensor = nullptr;
	m_pCoordinateMapper = nullptr;
	m_pDepthFrameReader = nullptr; 
	m_pBodyReader = nullptr;
	m_pRightHand = nullptr;
	m_pDepthArray = nullptr;
	m_pCVHelper = nullptr;
	//m_pEventHandler = nullptr;

	m_bRunning = false;
}


KinectHelper::~KinectHelper()
{
}
