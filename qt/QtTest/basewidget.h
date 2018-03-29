#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#define MENU_VIEW 0
#define PICTURE_VIEW 1
#define GESTURE_REC 2

#include <QWidget>
#include <QPoint>
#include <QPaintEvent>

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    BaseWidget(QWidget *parent = 0);
    virtual ~BaseWidget();

    void paintEvent(QPaintEvent *event);
    void initWindow();
    void setWindowSize(int width, int height);
    void setWindow(int width, int height);
    void setCursor(int x,int y);
protected:
    int widgetWidth;
    int widgetHeight;

    QPoint cursorPos;
signals:
    void display(int index);
public slots:
    virtual void fingerCursorPosMove(int dx, int dy);
    virtual void fingerCursorTouched();
    virtual void cursorPosMove(int dx, int dy);
    virtual void catchMove(int dx, int dy);
    virtual void cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz);
    virtual void catchRelease(int x, int y, int dx, int dy, float vx, float vy, float vz);
    virtual void cursorTouched(int x, int y);
    virtual void clickedAt(int x, int y);
    virtual void zoomIn(float offset);
    virtual void zoomOut(float offset);
    virtual void zoomBegin(int x, int y);
    virtual void zoomEnd();
    virtual void rotateCW(int rotateRate);
    virtual void rotateCCW(int rotateRate);
    virtual void rotateEnd();
    virtual void cursorWavedRight(int dx);
    virtual void cursorWavedLeft(int dx);


};

#endif // BASEWIDGET_H
