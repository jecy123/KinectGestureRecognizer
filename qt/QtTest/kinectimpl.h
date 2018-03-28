#ifndef KINECTIMPL_H
#define KINECTIMPL_H

#include <QObject>
#include <GestureRecgnition.h>
#include <KinectHelper.h>

class KinectImpl : public QObject, public GestureRecgnition
{
    Q_OBJECT
public:
    explicit KinectImpl(QObject *parent = 0);
    ~KinectImpl();
    void onRelease(GestureArgs *args);
    void onGrab(GestureArgs *args);
    void onClicked(GestureArgs *args);
    void onTouched(GestureArgs * args);
    void onTouchMove(GestureArgs * args);
    void onHandMove(GestureArgs * args);
    void onFistMove(GestureArgs *args);
    void onBeginZoom(GestureArgs * args);
    void onZoomIn(GestureArgs * args);
    void onZoomOut(GestureArgs * args);
    void onEndZoom(GestureArgs * args);

    void onRotateCW(GestureArgs *args);
    void onRotateCCW(GestureArgs * args);
    void onRotateEnd(GestureArgs *args);
    void onPageTurning(GestureArgs *args);
signals:
    void fingerMove(int dx, int dy);
    void fingerTouch();
    void handPushed();
    void handMove(int dx, int dy);
    void fistMove(int dx, int dy);
    void fistGrab(int x, int y, int dx, int dy, float vx, float vy, float vz);
    void fistRelease(int x, int y, int dx, int dy, float vx, float vy, float vz);
    void handClicked(int x, int y);
    void handTouched(int x, int y);
    void handTouchMoved(int x, int y, int dx, int dy);
    void handWavedLeft(int dx);
    void handWavedRight(int dx);

    void zoomBegin(int x, int y);
    void zoomIn(float offset);
    void zoomOut(float offset);
    void zoomEnd();

    void rotateCW(int rotateRate);
    void rotateCCW(int rotateRate);
    void rotateEnd();
public slots:
    void start();
    void stop();
private:
    KinectHelper * k;
};

#endif // KINECTIMPL_H
