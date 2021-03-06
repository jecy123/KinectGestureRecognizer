#ifndef GESTUREVIEW_H
#define GESTUREVIEW_H

#include "basewidget.h"
#include "gesturecanvas.h"

#include <QPushButton>
#include <QRect>
#include <QPixmap>
#include <QPaintEvent>
#include <QListWidget>

class GestureView : public BaseWidget, public GestureCanvasEventHandler
{
    Q_OBJECT
public:
    explicit GestureView(QWidget * parent = 0);
    ~GestureView();
    void initViews();

    void onFinishGesture(vector<vector<QPoint> > *points);

signals:
public slots:
    //void fingerCursorPosMove(int dx, int dy);
    //void fingerCursorTouched();
    void cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz);
    void cursorPosMove(int dx, int dy);
    void catchMove(int dx, int dy);

    void paintEvent(QPaintEvent *event);

    void setCursor(int dx, int dy);
private:
    GestureCanvas * canvas;
    int mCanvasWidth;
    int mCanvasHeight;
    QPixmap handMap;
    QLabel * handCursor;
    QListWidget * mList;
    QLabel * mDelayTest;
    QLabel * mListTitle;

};

#endif // GESTUREVIEW_H
