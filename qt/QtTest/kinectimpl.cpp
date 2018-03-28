#include "kinectimpl.h"

KinectImpl::KinectImpl(QObject *parent) : QObject(parent)
{
    k = new KinectHelper;

}

KinectImpl::~KinectImpl()
{
	if (k!=nullptr)
	{
		k->stopRefreshData();
		delete k;
	}
}

void KinectImpl::start()
{
	if (k!=nullptr)
	{
        this->setOutput(false);
        k->startRefreshData(this);
        //k->setGestureEventHandler(this);
	}
}

void KinectImpl::stop()
{
	if (k != nullptr)
	{
		k->stopRefreshData();
	}
}


void KinectImpl::onRelease(GestureArgs *args)
{

    cout << "Release" << endl;
    emit fistRelease(args->rightHand.x, args->rightHand.y, args->rightHand.dx, args->rightHand.dy, args->rightHand.vx, args->rightHand.vy, args->rightHand.vz);
}

void KinectImpl::onGrab(GestureArgs *args)
{
    cout << "Grab" << endl;
    emit fistGrab(args->rightHand.x, args->rightHand.y, args->rightHand.dx, args->rightHand.dy, args->rightHand.vx, args->rightHand.vy, args->rightHand.vz);
}

void KinectImpl::onHandMove(GestureArgs *args)
{
    cout << "HandMove!!"<<endl;
    emit handMove(args->rightHand.dx,args->rightHand.dy);
}

void KinectImpl::onFistMove(GestureArgs *args)
{
    cout << "FistMove" << endl;
    emit fistMove(args->rightHand.dx, args->rightHand.dy);
}

void KinectImpl::onClicked(GestureArgs *args)
{
    cout << "Clicked" << endl;
    emit handClicked(args->rightHand.x, args->rightHand.y);
}

void KinectImpl::onTouched(GestureArgs * args)
{
    cout << "Touched"<<endl;
    emit handTouched(args->rightHand.x, args->rightHand.y);
}

void KinectImpl::onTouchMove(GestureArgs * args)
{

    cout << "Touch Move"<<endl;
}


void KinectImpl::onBeginZoom(GestureArgs * args)
{
    cout << "Zoom Begin"<<endl;
    emit zoomBegin(args->rightHand.x, args->rightHand.y);
}

void KinectImpl::onZoomIn(GestureArgs *args)
{
    cout << "Zoom In"<<endl;
    ZoomArgs zoomArgs = args->getZoomArgs();
    cout << "scaleRate = " << zoomArgs.scaleRate << endl;
    emit zoomIn(zoomArgs.scaleRate);

}

void KinectImpl::onZoomOut(GestureArgs *args)
{
    cout << "Zoom Out"<<endl;
    ZoomArgs zoomArgs = args->getZoomArgs();
    cout << "scaleRate = " << zoomArgs.scaleRate << endl;
    emit zoomOut(zoomArgs.scaleRate);
}

void KinectImpl::onEndZoom(GestureArgs *args)
{
    cout << "Zoom End"<<endl;
    emit zoomEnd();
}

void KinectImpl::onPageTurning(GestureArgs *args)
{
    if(args->rightHand.dx > 0)
    {
        emit handWavedRight(args->rightHand.dx);
    }else if(args->rightHand.dx < 0)
    {
        emit handWavedLeft(args->rightHand.dx);
    }
}


void KinectImpl::onRotateCW(GestureArgs *args)
{
    cout << "Rotate ClockWise"<<endl;
    ZoomArgs zoomArgs = args->getZoomArgs();
    cout << "rotateRate = "<< zoomArgs.rotateRate << endl;
    emit rotateCW(zoomArgs.rotateRate);
}

void KinectImpl::onRotateCCW(GestureArgs * args)
{
    cout << "Rotate ClockWise"<<endl;
    ZoomArgs zoomArgs = args->getZoomArgs();
    cout << "rotateRate = "<< zoomArgs.rotateRate << endl;
    emit rotateCCW(zoomArgs.rotateRate);

}

void KinectImpl::onRotateEnd(GestureArgs *args)
{
    cout << "rotate End" << endl;
    emit rotateEnd();
}
