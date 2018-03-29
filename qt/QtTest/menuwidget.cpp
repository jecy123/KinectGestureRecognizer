#include "menuwidget.h"
#include "screenutils.h"
#include <iostream>
#include <QPainter>
#include <QDebug>
using namespace std;

MenuWidget::MenuWidget(QWidget *parent):BaseWidget(parent)
{
    initViews();
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->widgetWidth = ScreenUtils::widgetWidth;
    this->widgetHeight = ScreenUtils::widgetHeight;
    //cursorPos.setX(widgetWidth / 2);
    //cursorPos.setY(widgetHeight / 2);
    //connect(this, SIGNAL(moveCursor(int,int)),this, SLOT(setCursor(int,int)));
    handTouched = false;
}

void MenuWidget::initViews()
{
    buttonCnt = 2;

    int btnPadding = 20;
    int btnWidth = 160;
    int btnHeight = 40;
    int originalX  = (ScreenUtils::widgetWidth - btnWidth) / 2;
    int originalY = (ScreenUtils::widgetHeight - (btnHeight * buttonCnt + btnPadding * (buttonCnt - 1))) / 2;

    buttonPicture = new QPushButton(this);
    buttonPicture->setText("Picture Exploer");
    buttonPicture->setGeometry(originalX, originalY, btnWidth, btnHeight);
    connect(buttonPicture, SIGNAL(clicked()), this, SLOT(onBtnPicturePushed()));

    originalY += (btnHeight + btnPadding);
    buttonGestureRecognizor = new QPushButton(this);
    buttonGestureRecognizor->setText("Gesture Recognizor");
    buttonGestureRecognizor->setGeometry(originalX, originalY, btnWidth, btnHeight);
    connect(buttonGestureRecognizor, SIGNAL(clicked()), this, SLOT(onBtnGesturePushed()));

    handMap.load("./Hand/Hand.jpg");
    handTouchedMap.load("./Hand/Hand_touched.jpg");
    handClickedMap.load("./Hand/Hand_clicked.jpg");
    fistMap.load("./Hand/Fist.jpg");

    handCursor = new QLabel(this);
    handCursor->setScaledContents(true);
    handCursor->setPixmap(handMap);
    handCursor->setGeometry(cursorPos.x()-20,cursorPos.y()-20, 50, 50);

}

void MenuWidget::mouseMoveEvent(QMouseEvent * event)
{
    cout << event->x() << "," << event->y() << endl;
    setCursor(event->x(), event->y());
}


void MenuWidget::paintEvent(QPaintEvent *event)
{

//    QPainter painter(this);
//    if(handTouched)
//    {
//        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
//    }
//    else
//    {
//        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
//    }
//    painter.drawEllipse(cursorPos, 10, 10);
}



void MenuWidget::cursorPosMove(int dx, int dy)
{
    this->handCursor->setPixmap(handMap);
    qDebug()<<"Menu========================HAND MOVE"<<endl;
    int rectW = 200;
    int rectH = 112;
    int x = cursorPos.x();
    int y = cursorPos.y();
    x += dx * widgetWidth / rectW;
    y += dy * widgetHeight / rectH;
    setCursor(x, y);
    handCursor->setGeometry(cursorPos.x()-25,cursorPos.y()-25, 50, 50);
    fingerTouched = false;
    handTouched = false;
}


void MenuWidget::cursorTouched(int x, int y)
{
    handCursor->setPixmap(handTouchedMap);
    //fingerTouched = true;
    handTouched = true;
    this->update();
}

void MenuWidget::clickedAt(int x, int y)
{
    handCursor->setPixmap(handClickedMap);
    if (buttonPicture->geometry().contains(cursorPos.x(), cursorPos.y()))
    {
        onBtnPicturePushed();
    }
    if (buttonGestureRecognizor->geometry().contains(cursorPos.x(), cursorPos.y()))
    {
        onBtnGesturePushed();
    }
}

void MenuWidget::onBtnPicturePushed()
{
    emit display(PICTURE_VIEW);
}

void MenuWidget::onBtnGesturePushed()
{
    emit display(GESTURE_REC);
}
