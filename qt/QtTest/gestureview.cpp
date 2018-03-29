#include "gestureview.h"
#include "screenutils.h"
#include <QDebug>


GestureView::GestureView(QWidget * parent): BaseWidget(parent)
{
    qDebug() << "GestureView" << endl;
    //handMap.load("./Hand/Hand.jpg");

    mCanvasWidth = 1000;
    mCanvasHeight = 800;

    initViews();

}

GestureView::~GestureView()
{

}

void GestureView::initViews()
{
    int canvasY = (ScreenUtils::widgetHeight - mCanvasHeight) / 2;

    canvas = new GestureCanvas(this);
    canvas->setGeometry(0, canvasY, mCanvasWidth, mCanvasHeight);

//    this->handCursor = new QLabel(this);
//    this->handCursor->setScaledContents(true);
//    this->handCursor->setPixmap(handMap);
//    this->handCursor->setGeometry(cursorPos.x() - 10,cursorPos.y() - 10, 20, 20);

}

//void GestureView::fingerCursorPosMove(int dx, int dy)
//{
//    //this->handCursor->setPixmap(handMap);
//    qDebug()<<"gesureView========================HAND MOVE"<<endl;
//    setCursor(dx, dy);
//    if(!canvas->isGesureTracked())
//    {
//        canvas->onGestureTrackBegin();
//    }else
//    {
//        canvas->onGestureTracking();
//    }
//    //this->handCursor->setGeometry(cursorPos.x()-25,cursorPos.y()-25, 50, 50);

//}


void GestureView::cursorPosMove(int dx, int dy)
{
    qDebug()<<"gesureView========================CURSOR MOVE"<<endl;
    setCursor(dx, dy);

    if(!canvas->isGesureTracked())
    {
        canvas->onGestureTrackBegin();
    }
    else
    {
        canvas->onGestureTracking();
    }
//    if(canvas->isGesureTracked())
//    {
//        canvas->onGestureTrackEnd();
//    }
}


void GestureView::catchMove(int dx, int dy)
{

    qDebug()<<"gesureView========================FIST MOVE"<<endl;
    setCursor(dx, dy);
}


void GestureView::cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz)
{
    if (canvas->isGesureTracked())
    {
        canvas->onGestureTrackEnd();
    }
}

void GestureView::paintEvent(QPaintEvent *event)
{
    //this->handCursor->setGeometry(cursorPos.x()-10,cursorPos.y()-10, 20, 20);
}


void GestureView::setCursor(int dx, int dy)
{
    int rectW = 200;
    int rectH = 112;
    int x = canvas->getCurrentPoint().x();
    int y = canvas->getCurrentPoint().y();
    x += dx * mCanvasWidth / rectW;
    y += dy * mCanvasHeight / rectH;

    if(x < 0)
    {
        x = 0;
    }else if(x > mCanvasWidth)
    {
        x = mCanvasWidth;
    }

    if(y < 0)
    {
        y = 0;
    }else if(y > mCanvasHeight)
    {
        y = mCanvasHeight;
    }

    this->canvas->setCursorPos(x, y);
}

