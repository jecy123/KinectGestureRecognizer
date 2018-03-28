#ifndef GESTURECANVAS_H
#define GESTURECANVAS_H

#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

#include <vector>

using namespace std;

class GestureCanvasEventHandler
{
public:
    virtual void onFinishGesture() = 0;
};

class GestureCanvas : public QLabel
{
    Q_OBJECT
public:
    explicit GestureCanvas(QWidget * parent = 0);
    ~GestureCanvas();
    void updateCanvas();
    void clear();
    void setPenSize(int penSize);
    void setEventHandler(GestureCanvasEventHandler * handler);
    int getPoints(vector< vector<QPoint> > * points);
    void fillLine(int index);
    void fillLines();
private:
    vector< vector<QPoint> > mPoints;
    int mPenSize;
    int mGestureTracked;
    GestureCanvasEventHandler * mHandler;

    QPoint mCurrentPoint;

public slots:

    void onGestureTrakeBegin();
    void onGestureTraking();
    void onGestureTrakkEnd();

    void paintEvent(QPaintEvent * e);
};

#endif // GESTURECANVAS_H
