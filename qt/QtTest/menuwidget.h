#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "basewidget.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>

class MenuWidget : public BaseWidget
{
    Q_OBJECT
public:
    MenuWidget(QWidget * parent = 0);
    void initViews();
    void mouseMoveEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
signals:
public slots:
    void cursorPosMove(int dx, int dy);
    void cursorTouched(int x, int y);
    void clickedAt(int x, int y);

    void onBtnPicturePushed();
    void onBtnGesturePushed();
private:

    QLabel * handCursor;


    QPixmap handMap;
    QPixmap handTouchedMap;
    QPixmap handClickedMap;
    QPixmap fistMap;

    int buttonCnt;
    QPushButton * buttonPicture;
    QPushButton * buttonGestureRecognizor;

    bool fingerTouched = false;
    bool handTouched;

};

#endif // MENUWIDGET_H
