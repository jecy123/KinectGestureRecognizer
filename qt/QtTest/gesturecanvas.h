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
    virtual void onFinishGesture(vector< vector<QPoint> > * points) = 0;
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
    QPoint & getCurrentPoint();
    void fillLine(int index);
    void fillLines();
    void setCursorPos(int x, int y);
    bool isGesureTracked();
private:
    vector< vector<QPoint> > mPoints;
    int mPenSize;
    bool mGestureTracked;
    GestureCanvasEventHandler * mHandler;

    QPoint mCurrentPoint;
    QPixmap handMap;
    QLabel * handCursor;

public slots:

    void onGestureTrackBegin();
    void onGestureTracking();
    void onGestureTrackEnd();

    void paintEvent(QPaintEvent * e);
};

#endif // GESTURECANVAS_H
