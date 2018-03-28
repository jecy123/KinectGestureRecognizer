#include "basewidget.h"
#include "screenutils.h"
#include <QPainter>

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent)
{
    this->widgetWidth = ScreenUtils::widgetWidth;
    this->widgetHeight = ScreenUtils::widgetHeight;
    setCursor(widgetWidth/2 , widgetHeight/2);
}

BaseWidget::~BaseWidget()
{

}


void BaseWidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(cursorPos, 20, 20);
}

void BaseWidget::initWindow()
{
    ScreenSize size = ScreenUtils::getScreenSize();
    int startX = (size.width - widgetWidth) / 2;
    int startY = (size.height - widgetHeight) / 2;
    this->move(startX, startY);
    this->resize(widgetWidth, widgetHeight);
}

void BaseWidget::setWindowSize(int width, int height)
{
    this->widgetHeight = height;
    this->widgetWidth = width;
}

void BaseWidget::setWindow(int width, int height)
{
    this->setWindowSize(width, height);
    this->initWindow();
}


void BaseWidget::setCursor(int x,int y)
{
    if(x < 0)
    {
        x = 0;
    }else if(x > widgetWidth)
    {
        x = widgetWidth;
    }

    if(y < 0)
    {
        y = 0;
    }else if(y > widgetHeight)
    {
        y = widgetHeight;
    }

    cursorPos.setX(x);
    cursorPos.setY(y);
    this->update();
}

void BaseWidget::cursorPosMove(int dx, int dy)
{
}

void BaseWidget::cursorTouched(int x, int y)
{
}

void BaseWidget::clickedAt(int x, int y)
{
}

void BaseWidget::catchMove(int dx, int dy)
{
}

void BaseWidget::cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz)
{
}

void BaseWidget::catchRelease(int x, int y, int dx, int dy, float vx, float vy, float vz)
{
}

void BaseWidget::zoomIn(float offset)
{
}

void BaseWidget::zoomOut(float offset)
{
}

void BaseWidget::zoomBegin(int x, int y)
{

}

void BaseWidget::zoomEnd()
{

}

void BaseWidget::rotateCW(int rotateRate)
{
}

void BaseWidget::rotateCCW(int rotateRate)
{
}

void BaseWidget::rotateEnd()
{

}

void BaseWidget::cursorWavedLeft(int dx)
{

}

void BaseWidget::cursorWavedRight(int dx)
{

}
