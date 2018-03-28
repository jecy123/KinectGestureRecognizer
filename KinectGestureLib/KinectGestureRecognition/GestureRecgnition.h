#pragma once
#include "Hand.h"
#include "dllapi.h"
#include "GestureArgs.h"
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

//手势识别的接口类
//class DLL_API GestureEventHandler
//{
//public:
//	GestureEventHandler(){}
//	virtual ~GestureEventHandler(){}
//	virtual void onOneFingerMove(HandArgs * args){}
//	virtual void onOneFingerTouch(HandArgs * args){}
//	virtual void onHandMove(HandArgs * args){}
//	virtual void onHandPush(HandArgs * args){}
//	virtual void onHandPull(HandArgs * args){}
//	virtual void onHandHoldMove(HandArgs * args){}
//	virtual void onHandHoldPush(HandArgs * args){}
//	virtual void onHandHoldPull(HandArgs * args){}
//	virtual void onHandGrab(HandArgs * args){}
//	virtual void onHandRelease(HandArgs * args){}
//};

enum DLL_API GestureType
{
	TYPE_ONE_FINGER,
	TYPE_ONE_FINGER_RETAIN,
	TYPE_OPEN,
	TYPE_OPEN_RETAIN,
	TYPE_OPEN_RETAIN_MOVE,
	TYPE_OPEN_CLICK,
	TYPE_OPEN_MOVE,
	TYPE_OPEN_SWIP,
	TYPE_HOLD,
	TYPE_HOLD_MOVE,
	TYPE_UNKNOWN,
	TYPE_GRAB,
	TYPE_RELEASE,
	TYPE_DRAG,
	TYPE_ZOOM,
	TYPE_ZOOM_IN,
	TYPE_ZOOM_OUT,
	TYPE_ROTATE_CW,
	TYPE_ROTATE_CCW
};

class DLL_API GestureRecgnition
{
public:
	GestureRecgnition();
	~GestureRecgnition();

	void setOutput(bool isInfoOutput);

	void start(Hand * hand);
	void refresh(Hand * leftHand, Hand * rightHand);
	
	//void update(Hand * hand);
	void changeState();

	void tickUp();


	void recgnition();
	GestureType getType();

	//void setGestureEventsHandler(GestureEventHandler * handler);
	void setType(GestureType type);
	virtual void onFingerMove(GestureArgs * args){}
	virtual void onFingerTouch(GestureArgs * args){}

	virtual void onGrab(GestureArgs * args){}
	virtual void onRelease(GestureArgs * args){}
	
	virtual void onBeginZoom(GestureArgs * args){}
	virtual void onZoomIn(GestureArgs * args){}
	virtual void onZoomOut(GestureArgs * args){}
	virtual void onRotateCW(GestureArgs * args){}
	virtual void onRotateCCW(GestureArgs * args){}
	virtual void onRotateEnd(GestureArgs * args){}
	virtual void onEndZoom(GestureArgs * args){}

	virtual void onTouched(GestureArgs * args){}
	virtual void onTouchMove(GestureArgs * args){}
	virtual void onClicked(GestureArgs * args){}

	virtual void onPageTurning(GestureArgs * args){}
	
	virtual void onHandMove(GestureArgs * args){}
	virtual void onHandPush(GestureArgs * args){}
	virtual void onHandPull(GestureArgs * args){}
	virtual void onDrag(GestureArgs * args){}

	
	virtual void onFistMove(GestureArgs * args){}
	virtual void onFistPush(GestureArgs * args){}
	virtual void onFistPull(GestureArgs * args){}
	
private:
	bool isZoomCanceled();
	bool isfirstGetGesture;

	ofstream file;

	GestureType m_type;
	GestureType m_lastType;

	//GestureEventHandler * eventHandler;
	Hand * rightHand;
	Hand * leftHand;
	ULONG currentTime;
	ULONG lastTime;

	GestureArgs * args;

	int startX, startY, startZ;
	int endX, endY, endZ;
	double time;
	bool isTickCountStart;
	bool isInfoOutput;
};

