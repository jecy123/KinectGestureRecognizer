#ifndef GESTUREVIEW_H
#define GESTUREVIEW_H

#include "basewidget.h"
#include "gesturecanvas.h"

#include <QPushButton>
#include <QRect>

class GestureView : public BaseWidget
{
    Q_OBJECT
public:
    explicit GestureView(QWidget * parent = 0);
    ~GestureView();
    void initViews();
signals:
public slots:
private:
    GestureCanvas * canvas;
};

#endif // GESTUREVIEW_H
