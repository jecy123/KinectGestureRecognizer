#include "gestureview.h"
#include <QDebug>


GestureView::GestureView(QWidget * parent): BaseWidget(parent)
{
    qDebug() << "GestureView" << endl;
    initViews();
}

GestureView::~GestureView()
{

}

void GestureView::initViews()
{
    canvas = new GestureCanvas(this);
    canvas->setGeometry(0, 0, 600, 600);
}
