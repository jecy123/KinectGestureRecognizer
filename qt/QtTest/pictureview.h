#ifndef PICTUREVIEW_H
#define PICTUREVIEW_H

#include "basewidget.h"

#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QRect>
#include <QPropertyAnimation>
#include <QHBoxLayout>

class PictureView : public BaseWidget
{
    Q_OBJECT
    Q_PROPERTY(int angle READ angle WRITE setAngle)
    Q_PROPERTY(int distance READ distance WRITE setDistance)

public:
    explicit PictureView(QWidget *parent = 0);
    void initZoomArgs();
    void initViews();
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

    int calculateToAngle(const int fromAngle);

signals:
public slots:
    void cursorPosMove(int dx, int dy);
    void cursorTouched(int x, int y);
    void catchMove(int dx, int dy);
    void cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz);
    void catchRelease(int x, int y, int dx, int dy, float vx, float vy, float vz);
    void clickedAt(int x, int y);
    void zoomIn(float offset);
    void zoomOut(float offset);
    void zoomBegin(int x, int y);
    void zoomEnd();

    void rotateCW(int rotateRate);
    void rotateCCW(int rotateRate);
    void rotateEnd();

    void cursorWavedLeft(int dx);
    void cursorWavedRight(int dx);
    void turnNextPage();
    void turnPrePage();
    void doPageTurningAnimation(int value);

    void onTurnPageFinished();

    //Property
    int angle()const;
    void setAngle(const int angle);
    int distance() const;
    void setDistance(const int distance);

private:

    bool isCursorCatched;
    bool isPicAreaCatched;
    bool isPicPreviewAreaCatched;

    bool isZoomBegin;

    int m_nAngle;
    int m_nDistance;

    int pictureNum;
    int currentPicIndex;

    int picWidth;
    int picHeight;

    int picPreviewWidth;
    int picPreviewHeight;

    int picPreviewZoomedWidth;
    int picPreviewZoomedHeight;

    int picPreviewMinWidth;
    int picPreviewMinHeight;
    int picPreviewMaxWidth;
    int picPreviewMaxHeight;

    QList<QPixmap> picMaps;
    QList<QImage> imageList;
    QList<QLabel *> picLabelList;
    QLabel * picPreviewLabel;

    QLabel * pageIndexLabel;

    QLabel * handCursor;
    QPixmap handMap;
    QPixmap handTouchedMap;
    QPixmap handClickedMap;
    QPixmap fistMap;

    QImage * currentImage;

    QWidget * picPreviewWidget;
    QWidget * picWidget;

    QScrollArea * picArea;
    //QScrollArea * picPreviewArea;

    QHBoxLayout * picLayout;
    QGridLayout * picPreviewLayout;

    QPropertyAnimation * rotateAnimation;
    QPropertyAnimation * turnPageAnimation;

    QRect picPreviewRect;
    QRect picSelectRect;
    QPoint currentCursorPos;
};

#endif // PICTUREVIEW_H
