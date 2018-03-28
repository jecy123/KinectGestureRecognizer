#include "widget.h"
#include "menuwidget.h"
#include "pictureview.h"
#include "screenutils.h"
#include "gestureview.h"
#include <QDebug>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(ScreenUtils::widgetWidth, ScreenUtils::widgetHeight);
    BaseWidget * menuWidget = new MenuWidget;
    BaseWidget * pictureView = new PictureView;
    BaseWidget * gestureView = new GestureView;

    this->widgets.push_back(menuWidget);
    this->widgets.push_back(pictureView);
    this->widgets.push_back(gestureView);

    this->stackLayout = new QStackedLayout;
    this->stackLayout->addWidget(menuWidget);
    this->stackLayout->addWidget(pictureView);
    this->stackLayout->addWidget(gestureView);

    this->currentViewIndex = MENU_VIEW;

    foreach (BaseWidget * widget, this->widgets) {
        connect(widget,SIGNAL(display(int)), this->stackLayout, SLOT(setCurrentIndex(int)));
        connect(widget,SIGNAL(display(int)),this,SLOT(changeView(int)));
    }
    this->mainLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->stackLayout);
    setLayout(this->mainLayout);
}

Widget::~Widget()
{
    if (this->kinectimpl != nullptr)
    {
        delete this->kinectimpl;
        this->kinectimpl = nullptr;
    }
}


void Widget::setKinectImpl(KinectImpl * impl)
{
    this->kinectimpl = impl;
    if(this->kinectimpl!=nullptr)
    {
        foreach (BaseWidget* widget, this->widgets)
        {
            connect(this->kinectimpl, &KinectImpl::fingerMove, widget , &BaseWidget::cursorPosMove);
            connect(this->kinectimpl, &KinectImpl::handMove, widget, &BaseWidget::cursorPosMove);
            connect(this->kinectimpl, &KinectImpl::fistMove, widget, &BaseWidget::catchMove);
            connect(this->kinectimpl, &KinectImpl::fistGrab, widget, &BaseWidget::cursorCatched);
            connect(this->kinectimpl, &KinectImpl::fistRelease, widget, &BaseWidget::catchRelease);
            connect(this->kinectimpl, &KinectImpl::handTouched, widget, &BaseWidget::cursorTouched);
            connect(this->kinectimpl, &KinectImpl::handClicked, widget, &BaseWidget::clickedAt);
            connect(this->kinectimpl, &KinectImpl::zoomBegin, widget, &BaseWidget::zoomBegin);
            connect(this->kinectimpl, &KinectImpl::zoomIn, widget, &BaseWidget::zoomIn);
            connect(this->kinectimpl, &KinectImpl::zoomOut, widget, &BaseWidget::zoomOut);
            connect(this->kinectimpl, &KinectImpl::zoomEnd, widget, &BaseWidget::zoomEnd);
            connect(this->kinectimpl, &KinectImpl::rotateCW, widget, &BaseWidget::rotateCW);
            connect(this->kinectimpl, &KinectImpl::rotateCCW, widget, &BaseWidget::rotateCCW);
            connect(this->kinectimpl, &KinectImpl::rotateEnd, widget, &BaseWidget::rotateEnd);
            connect(this->kinectimpl, &KinectImpl::handWavedLeft, widget, &BaseWidget::cursorWavedLeft);
            connect(this->kinectimpl, &KinectImpl::handWavedRight, widget, &BaseWidget::cursorWavedRight);
        }
    }
}

void Widget::changeView(int num)
{
    qDebug()<<num;
    this->currentViewIndex = num;
}


void Widget::closeEvent(QCloseEvent *event)
{

    if(this->currentViewIndex != MENU_VIEW)
    {
        qDebug() << "close";
        emit this->widgets.at(this->currentViewIndex)->display(MENU_VIEW);
        this->currentViewIndex = MENU_VIEW;
    }
}
