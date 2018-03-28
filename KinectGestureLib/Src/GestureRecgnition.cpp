#define DLL_IMPLEMENT

#include "GestureRecgnition.h"
#include "utils.h"


GestureRecgnition::GestureRecgnition()
{
	leftHand = rightHand = nullptr;
	isTickCountStart = false;
	m_lastType = m_type = TYPE_UNKNOWN;
	isfirstGetGesture = false;
	isInfoOutput = true;

	args = new GestureArgs;

	file.open("D:\\data.txt");
}




GestureRecgnition::~GestureRecgnition()
{
	delete args;
	file.close();
}


void GestureRecgnition::start(Hand * hand)
{

}

void GestureRecgnition::setOutput(bool isInfoOutput)
{
	this->isInfoOutput = isInfoOutput;
}

void GestureRecgnition::refresh(Hand * leftHand, Hand * rightHand)
{
	this->rightHand = rightHand;
	this->leftHand = leftHand;
	m_lastType = m_type;
	if (isfirstGetGesture == true)
	{
		if (rightHand->m_handState == HandState_NotTracked || rightHand->m_handState == HandState_Unknown)
		{
			if (m_lastType != TYPE_UNKNOWN)
			{
				isfirstGetGesture = true;
				m_type = m_lastType;
			}
			else
			{
				m_type = TYPE_UNKNOWN;

				isfirstGetGesture = false;
				lastTime = 0;
				currentTime = 0;

				args->reset();
				//lastArgs.reset();
				//currentArgs.reset();
			}
		}
		else{
			changeState();
		}
	}
	else
	{
		if (rightHand->m_handState == HandState_Open)
		{
			isfirstGetGesture = true;
			m_type = TYPE_OPEN;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			//lastArgs.reset();
			//currentArgs.reset();
		}
		else if (rightHand->m_handState == HandState_Closed)
		{
			if (leftHand->m_handState == HandState_Closed)
			{
				m_type = TYPE_ZOOM;
			}
			else{
				m_type = TYPE_GRAB;
			}
			isfirstGetGesture = true;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			//lastArgs.reset();
			//currentArgs.reset();
		}
		else if (rightHand->m_handState == HandState_Lasso)
		{
			isfirstGetGesture = true;
			m_type = TYPE_ONE_FINGER;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			//lastArgs.reset();
			//currentArgs.reset();
		}
		else{

			isfirstGetGesture = false;
		}
	} 
}


bool GestureRecgnition::isZoomCanceled()
{
	//return args->isZoomCancel();
	//return args->isZoomCancel(STATUS_LEFT) || args->isZoomCancel(STATUS_RIGHT);
	return leftHand->m_handState == HandState_Closed || rightHand->m_handState == HandState_Closed || args->isZoomCancel();
}

void GestureRecgnition::changeState()
{
	tickUp();
	if (isInfoOutput)
	{
		gotoXY(0, 2);
		args->output();
	}
	//cout << "zoomArgs = " << currentArgs.zoomArgs.a <<"                "<< endl;
	//cout << "curvity = " << currentArgs.curvity << "    " << endl;
	//cout << "disCenterTip = " << currentArgs.disCenterTip << "    " << endl;
	/*if (currentArgs.zoomTime != 0)
	{
	file << setw(6) << currentArgs.zoomTime << setw(10) << currentArgs.curvity << endl;

	}
	else{
	file << endl;
	}*/
	if (m_type == TYPE_OPEN)
	{
		gotoXY(0, 17);
		cout << "OPEN             ";
		if (args->isZoomBegin())
		{
			m_type = TYPE_ZOOM;
		}
		if (args->isSwitched())
		{
			//触发手掌“悬挂触摸”事件
			onTouched(args);
			m_type = TYPE_OPEN_RETAIN;

		}
		else if (args->isSwip())
		{

			//翻页事件
			onPageTurning(args);
			m_type = TYPE_OPEN_SWIP;
		}
		else if (this->rightHand->m_handState == HandState_Closed)
		{
			//触发握拳动作
			onGrab(args);
			m_type = TYPE_GRAB;
		}
		else
		{
			if (args->isMove()){
				m_type = TYPE_OPEN_MOVE;
			}
		}
	}
	if (m_type == TYPE_OPEN_MOVE)
	{
		gotoXY(0, 17);
		cout << "MOVE         ";
		//手掌移动事件
		onHandMove(args);
		if (args->isZoomBegin())
		{
			m_type = TYPE_ZOOM;
		}
		if (args->getRetainTime() >= 100)
		{
			m_type = TYPE_OPEN;
		}
		if (args->isSwip())
		{
			//翻页事件
			onPageTurning(args);
			m_type = TYPE_OPEN_SWIP;
		}
	}
	if (m_type == TYPE_OPEN_RETAIN)
	{
		gotoXY(0, 17);
		cout << "RETAIN        ";

		//触发手掌触摸事件
		onTouched(args);

		/*if (args->isSwitched(STATUS_LEFT))
		{
			m_type = TYPE_ZOOM;
		}*/
		if (args->isSwip())
		{

			//翻页事件
			onPageTurning(args);
			m_type = TYPE_OPEN_SWIP;
		}
		/*else if (args->getRetainTime() >= 1600)
		{
			m_type = TYPE_ZOOM;
		}*/
		else if (args->getRetainTime() <= 2400)
		{
			if (args->isClicked())
			{
				m_type = TYPE_OPEN_CLICK;
			}
			else if (args->isMove())
			{
				m_type = TYPE_OPEN_RETAIN_MOVE;
				args->setRetainTime(0);
			}
		}
		else{
			m_type = TYPE_OPEN;
		}
	}
	if (m_type == TYPE_OPEN_SWIP)
	{
		gotoXY(0, 17);
		cout << "SWIP            "; 
		
		if (!args->isSwip())
		{
			m_type = TYPE_OPEN;
			args->setRetainTime(0);
		}
		
		
	}
	if (m_type == TYPE_GRAB)
	{
		//args->reset();
		gotoXY(0, 17);
		cout << "GRAB              ";
		if (this->leftHand->m_handState == HandState_Closed)
		{
			m_type = TYPE_ZOOM;
		}
		else if (this->rightHand->m_handState == HandState_Open)
		{
			//触发拳头释放事件
			onRelease(args);
			m_type = TYPE_OPEN;
		}
		if (args->isMove())
		{
			m_type = TYPE_HOLD_MOVE;
		}
		else if (args->isSwip())
		{
			m_type = TYPE_DRAG;
		}
	}
	if (m_type == TYPE_HOLD_MOVE)
	{
		gotoXY(0, 17);
		cout << "HOLD MOVE              "; 
		//握拳移动事件
		onFistMove(args);
		/*if (this->leftHand->m_handState == HandState_Closed)
		{
			m_type = TYPE_ZOOM;
		}*/
		if (this->rightHand->m_handState == HandState_Open)
		{
			//触发拳头释放事件
			onRelease(args);
			m_type = TYPE_OPEN;
		}
		if (args->isSwip())
		{
			m_type = TYPE_DRAG;
		}
		if (args->getRetainTime() >= 100)
		{
			m_type = TYPE_GRAB;
		}
	}
	if (m_type == TYPE_DRAG)
	{
		gotoXY(0, 17);
		cout << "DRAG              ";
		//握拳拉拽手势
		onDrag(args);
		if (!args->isSwip())
		{
			m_type = TYPE_GRAB;
		}
		if (args->isMove())
		{
			m_type = TYPE_HOLD_MOVE;
		}
	}
	if (m_type == TYPE_OPEN_CLICK)
	{
		gotoXY(0, 17);
		cout << "         CLICK            ";
		//点击事件
		onClicked(args);
		if (args->getRetainTime() >= 50)
			m_type = TYPE_OPEN; 
	}
	if (m_type == TYPE_OPEN_RETAIN_MOVE)
	{

		gotoXY(0, 17);
		cout << "RETAIN MOVE              ";
		//触摸移动事件
		onTouchMove(args);
		if (args->getRetainTime() >= 500)
		{
			m_type = TYPE_OPEN;
			args->setRetainTime(0);
		}
	}
	if (m_type == TYPE_ZOOM)
	{
		gotoXY(0, 17);
		cout << "ZOOM                    ";
		//开始缩放事件
		onBeginZoom(args);

//	

		if (isZoomCanceled())
		{
			onEndZoom(args);
			this->isfirstGetGesture = false;
		}
		ZoomArgs zoomArgs = args->getZoomArgs();
		switch (zoomArgs.status)
		{
		case ZOOM_IN:
			m_type = TYPE_ZOOM_IN;
			break;
		case ZOOM_OUT:
			m_type = TYPE_ZOOM_OUT;
			break;
		case ROTATE_CCW:
			m_type = TYPE_ROTATE_CCW;
			break;
		case ROTATE_CW:
			m_type = TYPE_ROTATE_CW;
			break;
		}
	}
	if (m_type == TYPE_ZOOM_IN)
	{
		gotoXY(0, 17);
		cout << "ZOOM IN            "; 
		//缩小事件
		onZoomIn(args);

		if (isZoomCanceled())
		{
			onEndZoom(args);
			this->isfirstGetGesture = false;
		}
		ZoomArgs zoomArgs = args->getZoomArgs();
		switch (zoomArgs.status)
		{
		case ZOOM_IN:
			m_type = TYPE_ZOOM_IN;
			break;
		case ZOOM_OUT:
			m_type = TYPE_ZOOM_OUT;
			break;
		case ZOOM_NONE:
			m_type = TYPE_ZOOM;
			break;
		}
	}
	if (m_type == TYPE_ZOOM_OUT)
	{
		gotoXY(0, 17);
		cout << "ZOOM OUT            ";
		//放大事件
		onZoomOut(args);

		if (isZoomCanceled())
		{
			this->isfirstGetGesture = false;
		}
		ZoomArgs zoomArgs = args->getZoomArgs();
		switch (zoomArgs.status)
		{
		case ZOOM_IN:
			m_type = TYPE_ZOOM_IN;
			break;
		case ZOOM_OUT:
			m_type = TYPE_ZOOM_OUT;
			break;
		case ZOOM_NONE:
			m_type = TYPE_ZOOM;
			break;
		}

	}
	if (m_type == TYPE_ROTATE_CW)
	{
		gotoXY(0, 17);
		cout << "ROTATE CW            ";
		//顺时针旋转事件
		onRotateCW(args);
		if (isZoomCanceled())
		{
			this->isfirstGetGesture = false;
		}
		ZoomArgs zoomArgs = args->getZoomArgs();
		switch (zoomArgs.status)
		{
		case ROTATE_CW:
			m_type = TYPE_ROTATE_CW;
			break;
		case ROTATE_CCW:
			m_type = TYPE_ROTATE_CCW;
			break;
		case ZOOM_NONE:
			onRotateEnd(args);
			m_type = TYPE_ZOOM;
			break;
		default:
			if (args->getRetainTime() >= 50)
			{
				onRotateEnd(args);
				m_type = TYPE_ZOOM;
			}
			break;
		}
	}
	if (m_type == TYPE_ROTATE_CCW)
	{
		gotoXY(0, 17);
		cout << "ROTATE CCW            ";
		//逆时针旋转事件
		onRotateCCW(args);

		if (isZoomCanceled())
		{
			this->isfirstGetGesture = false;
		}
		ZoomArgs zoomArgs = args->getZoomArgs();
		switch (zoomArgs.status)
		{
		case ROTATE_CW:
			m_type = TYPE_ROTATE_CW;
			break;
		case ROTATE_CCW:
			m_type = TYPE_ROTATE_CCW;
			break;
		default:
			if (args->getRetainTime() >= 50)
			{
				onRotateEnd(args);
				m_type = TYPE_ZOOM;
			}
			break;
		}
	}
	//if (m_type == TYPE_ZOOM)
	//{

	//	gotoXY(0, 17);
	//	/*if (currentArgs.zoomArgs.a > 0)
	//	{
	//		cout << "ZOOM IN              ";
	//	}
	//	else{
	//		cout << "ZOOM OUT             ";
	//	}*/

	//	if (!currentArgs.isZoom)
	//	{
	//		m_type = TYPE_OPEN;
	//	}
	//}

}

GestureType GestureRecgnition::getType()
{
	return m_type;
}

void GestureRecgnition::setType(GestureType type)
{
	this->m_type = type;
}

void GestureRecgnition::tickUp()
{
	lastTime = currentTime;
	currentTime = getTickCounts();

	//lastArgs = currentArgs;

	if (rightHand != nullptr && leftHand != nullptr)
	{
		args->refreshData(leftHand, rightHand, currentTime);
		/*if (m_type == TYPE_ONE_FINGER || m_type == TYPE_ONE_FINGER_RETAIN)
		{
			args->setXYZ(
				leftHand->HandTip.m_depthX,
				leftHand->HandTip.m_depthY,
				leftHand->HandTip.m_cameraZ * 1000,
				rightHand->HandTip.m_depthX,
				rightHand->HandTip.m_depthY,
				rightHand->HandTip.m_cameraZ * 1000, currentTime);
		}
		else{

			args->setXYZ(
				leftHand->HandCenter.m_depthX,
				leftHand->HandCenter.m_depthY,
				leftHand->HandCenter.m_cameraZ * 1000,
				rightHand->HandCenter.m_depthX,
				rightHand->HandCenter.m_depthY,
				rightHand->HandCenter.m_cameraZ * 1000, currentTime);

			args->setTipXYZ(
				leftHand->HandTip.m_depthX,
				leftHand->HandTip.m_depthY,
				leftHand->HandTip.m_cameraZ * 1000,
				rightHand->HandTip.m_depthX,
				rightHand->HandTip.m_depthY,
				rightHand->HandTip.m_cameraZ * 1000);
			args->calculateCurvity();
			args->calculateLRHandDistance(currentTime);
		}*/
	}
}