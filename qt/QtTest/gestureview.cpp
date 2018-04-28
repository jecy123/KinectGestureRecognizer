#include "gestureview.h"
#include "screenutils.h"
#include <QDebug>
#include <sgr.h>
#include <QTime>

using namespace sgr;

static Recognizer g_sgr;


GestureView::GestureView(QWidget * parent): BaseWidget(parent)
{
    qDebug() << "GestureView" << endl;
    //handMap.load("./Hand/Hand.jpg");

    g_sgr.init("simple-gesture.model");

    mCanvasWidth = 800;
    mCanvasHeight = 600;

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
    canvas->setEventHandler(this);

    int listW = 200;
    int listX = mCanvasWidth + (ScreenUtils::widgetWidth - mCanvasWidth - listW) / 2;

    mList = new QListWidget(this);
    mList->setGeometry(listX, canvasY, listW, mCanvasHeight);
    mList->setFont(QFont("Times New Roman", 18));

    mDelayTest = new QLabel(this);
    mDelayTest->setGeometry(listX, canvasY - 80, listW, 60);

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


void GestureView::onFinishGesture(vector<vector<QPoint> > *points)
{
    qDebug() << "Finish......................................." << endl;
    QTime now = QTime::currentTime();
    now.start();

    if (points && canvas && g_sgr.ready())
    {
        vector<string> wordlist;

        Character cha;

        int lCnt = points->size();
        for (int i = 0; i < lCnt; i++)
        {
            int pCnt = points->at(i).size();
            for (int j = 0; j < pCnt; j++)
            {
                cha.add(i, points->at(i).at(j).x(), points->at(i).at(j).y());
            }
        }

        g_sgr.recognize(&cha, &wordlist, 2, 1);

        int cnt = wordlist.size();

        if (cnt > 10)
            cnt = 10;

        mList->clear();
        for (int i = 0; i < cnt; i++)
        {
            qDebug() << QString::fromStdString(wordlist[i]) << endl;
            mList->addItem(QString::number(i) + ": " +  QString::fromStdString(wordlist[i]));
        }
    }
}

