#include "pictureview.h"
#include "pictureutils.h"
#include "screenutils.h"
#include <QDebug>
#include <QScrollBar>
#include <QPainter>
#include <QMatrix>

PictureView::PictureView(QWidget *parent) : BaseWidget(parent)
{
    qDebug() << "PictureView" << endl;

//    QLabel * nLabel = new QLabel(this);
//    nLabel->setText("asdasdasd");
//    nLabel->setGeometry(20,20,180,40);
    isCursorCatched = false;
    isPicAreaCatched = false;
    isPicPreviewAreaCatched = false;
    isZoomBegin = false;
    //setCursor(30,ScreenUtils::widgetHeight/2);

    currentImage = new QImage;

    rotateAnimation = new QPropertyAnimation;
    rotateAnimation->setTargetObject(this);
    rotateAnimation->setPropertyName("angle");
    rotateAnimation->setDuration(200);
    rotateAnimation->setLoopCount(1);

    turnPageAnimation = new QPropertyAnimation;
    turnPageAnimation->setTargetObject(this);
    turnPageAnimation->setPropertyName("distance");
    turnPageAnimation->setDuration(300);
    turnPageAnimation->setLoopCount(1);

    connect(turnPageAnimation, &QPropertyAnimation::finished, this, &PictureView::onTurnPageFinished);
    initViews();
}


void PictureView::paintEvent(QPaintEvent *event)
{
    //this->handCursor->setText("F");
    this->handCursor->setGeometry(cursorPos.x()-25,cursorPos.y()-25, 50, 50);

    QPainter painter(this);
    painter.drawRect(this->picPreviewRect);


}

void PictureView::closeEvent(QCloseEvent *event)
{
    emit this->display(MENU_VIEW);
}

void PictureView::initZoomArgs()
{
    this->picPreviewZoomedHeight = this->picPreviewHeight;
    this->picPreviewZoomedWidth = this->picPreviewWidth;
    this->m_nAngle = 0;
}

void PictureView::initViews()
{
    this->picWidth = 192;
    this->picHeight = 108;

    this->picPreviewHeight = ScreenUtils::widgetHeight - this->picHeight - 99;
    this->picPreviewWidth = this->picPreviewHeight * 16 / 9;

    this->picPreviewMaxWidth = this->picPreviewWidth * 1.5;
    this->picPreviewMaxHeight = this->picPreviewHeight * 1.5;
    this->picPreviewMinWidth = this->picPreviewWidth / 4;
    this->picPreviewMinHeight = this->picPreviewHeight / 4;


    initZoomArgs();

    this->setWindowTitle("Picture View");
    QString basePath(".\\Images");
    PictureUtils pictureUtils(basePath);
//    this->picMaps = pictureUtils.loadPictures();
    this->imageList = pictureUtils.loadImages();

    //*currentImage = imageList.at(0);

    this->picLayout = new QHBoxLayout;

    //int i = 0;
    pictureNum = this->imageList.size();
    currentPicIndex = 0;
    qDebug()<< pictureNum;

    foreach (QImage image, this->imageList) {
       QLabel * label = new QLabel;
       label->setMargin(10);
       label->setScaledContents(true);
       label->setPixmap(QPixmap::fromImage(image));

       this->picLabelList.append(label);
       this->picLayout->addWidget(label);
       this->picLayout->setStretchFactor(label, 1);

    }

    picSelectRect.setX(0);
    picSelectRect.setY(0);
    picSelectRect.setWidth(picWidth);
    picSelectRect.setHeight(picHeight);

    this->picWidget = new QWidget(this);
    this->picWidget->setLayout(this->picLayout);
    this->picWidget->setGeometry(20, 10, this->picWidth * pictureNum + 10 * (pictureNum + 1), this->picHeight + 20);

    this->picArea = new QScrollArea(this);
    this->picArea->setGeometry(10, 10, ScreenUtils::widgetWidth - 40, this->picHeight + 40);
    this->picArea->setWidget(this->picWidget);


    this->picPreviewLabel = new QLabel;
    //this->picPreviewLabel->setScaledContents(true);
    *currentImage = imageList.at(0).scaled(picPreviewWidth, picPreviewHeight, Qt::KeepAspectRatio);
    this->picPreviewLabel->setPixmap(QPixmap::fromImage(*currentImage));
    //this->picPreviewLabel->setPixmap(this->picMaps.at(0));

    this->picPreviewLayout = new QGridLayout;
    this->picPreviewLayout->setAlignment(Qt::AlignCenter);
    this->picPreviewLayout->addWidget(this->picPreviewLabel);

    int x = (ScreenUtils::widgetWidth - picPreviewWidth) / 2;
    int y = this->picHeight + 60;
    this->picPreviewRect = QRect(x, y, this->picPreviewWidth, this->picPreviewHeight);

    this->picPreviewWidget = new QWidget(this);
    this->picPreviewWidget->setLayout(this->picPreviewLayout);
    this->picPreviewWidget->setGeometry(this->picPreviewRect);


//    this->picPreviewArea = new QScrollArea(this);
//    this->picPreviewArea->setGeometry(x, y, this->picPreviewWidth + 16, this->picPreviewHeight + 9);
//    this->picPreviewArea->setWidget(this->picPreviewWidget);
//    this->picPreviewArea->setAlignment(Qt::AlignCenter);


    handMap.load("./Hand/Hand.jpg");
    handTouchedMap.load("./Hand/Hand_touched.jpg");
    handClickedMap.load("./Hand/Hand_clicked.jpg");
    fistMap.load("./Hand/Fist.jpg");

    this->handCursor = new QLabel(this);
    this->handCursor->setScaledContents(true);
    //this->handCursor->setText("HADN");
    this->handCursor->setPixmap(handMap);
    this->handCursor->setGeometry(cursorPos.x()-20,cursorPos.y()-20, 50, 50);
    //this->handCursor->setFont(QFont("Times New Roman", 20));

    int ox = (ScreenUtils::widgetWidth + picPreviewWidth)/ 2 + 20;
    int oy = ScreenUtils::widgetHeight - 80;
    int w = 80;
    int h = 40;

    pageIndexLabel = new QLabel(this);
    pageIndexLabel->setFont(QFont("Times New Roman", 16));
    pageIndexLabel->setGeometry(ox, oy, w, h);

    QString str;
    str = QString::number((currentPicIndex + 1), 10) + "/" + QString::number(pictureNum, 10);
    pageIndexLabel->setText(str);

}


void PictureView::cursorPosMove(int dx, int dy)
{

    this->handCursor->setPixmap(handMap);
    qDebug()<<"picturePreview========================HAND MOVE"<<endl;
    int rectW = 200;
    int rectH = 112;
    int x = cursorPos.x();
    int y = cursorPos.y();
    x += dx * widgetWidth / rectW;
    y += dy * widgetHeight / rectH;
    setCursor(x, y);
    //fingerTouched = false;
}

void PictureView::cursorTouched(int x, int y)
{
    //this->handCursor->setPixmap(handTouchedMap);
}

void PictureView::zoomBegin(int x, int y)
{
    this->handCursor->setPixmap(handTouchedMap);
}

void PictureView::zoomIn(float offset)
{

    this->handCursor->setPixmap(handClickedMap);
    int  off = (int)offset;
    qDebug()<<"Zoom in: " << off << endl;


    picPreviewZoomedWidth += 16 * off ;
    picPreviewZoomedHeight += 9 * off ;

    if(picPreviewZoomedWidth >= picPreviewMaxWidth)
    {
        picPreviewZoomedWidth = picPreviewMaxWidth;
        picPreviewHeight = picPreviewMaxHeight;
    }

    if(picPreviewZoomedWidth <= picPreviewMinWidth)
    {
        picPreviewZoomedWidth = picPreviewMinWidth;
        picPreviewZoomedHeight = picPreviewMinHeight;
    }

    double rate = (double)picPreviewZoomedWidth / (double)picPreviewWidth;

    QMatrix matrix;
    matrix.rotate(m_nAngle);
    matrix.scale(rate, rate);

    QImage image2 = currentImage->transformed(matrix);
    picPreviewLabel->setPixmap(QPixmap::fromImage(image2));
}

void PictureView::zoomOut(float offset)
{
    this->handCursor->setPixmap(handClickedMap);
    int  off = (int)offset;
    qDebug()<<"Zoom out: " << off << endl;

    m_nAngle += 0;//rotateRate;
    if(m_nAngle>=360)
    {
        m_nAngle = 0;
    }
    if(m_nAngle < 0)
    {
        m_nAngle = 360;
    }

    picPreviewZoomedWidth += 16 * off ;
    picPreviewZoomedHeight += 9 * off ;

    if(picPreviewZoomedWidth >= picPreviewMaxWidth)
    {
        picPreviewZoomedWidth = picPreviewMaxWidth;
        picPreviewHeight = picPreviewMaxHeight;
    }

    if(picPreviewZoomedWidth <= picPreviewMinWidth)
    {
        picPreviewZoomedWidth = picPreviewMinWidth;
        picPreviewZoomedHeight = picPreviewMinHeight;
    }


    double rate = (double)picPreviewZoomedWidth / (double)picPreviewWidth;

    QMatrix matrix;
    matrix.rotate(m_nAngle);
    matrix.scale(rate, rate);

    QImage image2 = currentImage->transformed(matrix);
    picPreviewLabel->setPixmap(QPixmap::fromImage(image2));
}

void PictureView::zoomEnd()
{
    this->handCursor->setPixmap(handTouchedMap);
    qDebug() << "PictureView=======>Zoom End" << endl;

    if(m_nAngle > 360)
    {
        m_nAngle = 0;
    }
    if(m_nAngle < 0)
    {
        m_nAngle = 360;
    }

    int toAngle = calculateToAngle(m_nAngle);

    qDebug() << "angle = " << m_nAngle << "  toAngle = " << toAngle ;

    rotateAnimation->setKeyValueAt(0, m_nAngle);
    rotateAnimation->setKeyValueAt(1, toAngle);
    rotateAnimation->start();

}


void PictureView::rotateCW(int rotateRate)
{

    this->handCursor->setPixmap(handClickedMap);
    m_nAngle += rotateRate;
    if(m_nAngle>360)
    {
        m_nAngle = 0;
    }
    if(m_nAngle < 0)
    {
        m_nAngle = 360;
    }

    double rate = (double)picPreviewZoomedWidth / (double)picPreviewWidth;

    QMatrix matrix;
    matrix.rotate(m_nAngle);
    matrix.scale(rate, rate);

    QImage image2 = currentImage->transformed(matrix);
    picPreviewLabel->setPixmap(QPixmap::fromImage(image2));
}

void PictureView::rotateCCW(int rotateRate)
{
    this->handCursor->setPixmap(handClickedMap);

    m_nAngle += rotateRate;
    if(m_nAngle>360)
    {
        m_nAngle = 0;
    }
    if(m_nAngle < 0)
    {
        m_nAngle = 360;
    }

    double rate = (double)picPreviewZoomedWidth / (double)picPreviewWidth;

    QMatrix matrix;
    matrix.rotate(m_nAngle);
    matrix.scale(rate, rate);

    QImage image2 = currentImage->transformed(matrix);
    picPreviewLabel->setPixmap(QPixmap::fromImage(image2));
}

void PictureView::rotateEnd()
{
    qDebug() << "PictureView=======>Rotate End" << endl;

    if(m_nAngle > 360)
    {
        m_nAngle = 0;
    }
    if(m_nAngle < 0)
    {
        m_nAngle = 360;
    }

    int toAngle = calculateToAngle(m_nAngle);

    qDebug() << "angle = " << m_nAngle << "  toAngle = " << toAngle ;

    rotateAnimation->setKeyValueAt(0, m_nAngle);
    rotateAnimation->setKeyValueAt(1, toAngle);
    rotateAnimation->start();
}


void PictureView::turnNextPage()
{

    if(currentPicIndex == pictureNum - 1)
        return;
    currentPicIndex ++;
    doPageTurningAnimation(-200);

}

void PictureView::turnPrePage()
{
    if(currentPicIndex == 0)
        return;
    currentPicIndex --;
    doPageTurningAnimation(200);
}

void PictureView::doPageTurningAnimation(int value)
{
    turnPageAnimation->setKeyValueAt(0, 0);
    turnPageAnimation->setKeyValueAt(1, value);
    turnPageAnimation->start();
}

void PictureView::onTurnPageFinished()
{
    initZoomArgs();
    *currentImage = imageList.at(currentPicIndex);
    QImage imageScaled = currentImage->scaled(picPreviewWidth, picPreviewHeight, Qt::KeepAspectRatio);
    picPreviewLabel->setPixmap(QPixmap::fromImage(imageScaled));
    QString str;
    str = QString::number((currentPicIndex + 1), 10) + "/" + QString::number(pictureNum, 10);
    pageIndexLabel->setText(str);
}

void PictureView::cursorWavedLeft(int dx)
{
    qDebug()<<"PictureView=======>cursorWavedLeft" << endl;
    turnNextPage();
}

void PictureView::cursorWavedRight(int dx)
{

    qDebug()<<"PictureView=======>cursorWavedRight" << endl;
    turnPrePage();
}

void PictureView::clickedAt(int x, int y)
{
    this->handCursor->setPixmap(handClickedMap);
}

void PictureView::catchMove(int dx, int dy)
{
    if(isPicAreaCatched)
    {
        int x = this->picArea->horizontalScrollBar()->value();
        x += dx*10;
        if(x < 0)
            x = 0;
        picArea->horizontalScrollBar()->setValue(x);
    }
}

void PictureView::cursorCatched(int x, int y, int dx, int dy, float vx, float vy, float vz)
{
   qDebug() << "CATCHED";
    isCursorCatched = true;
    this->handCursor->setPixmap(fistMap);
    if(this->picWidget->geometry().contains( cursorPos.x(),cursorPos.y() ))
    {
        isPicAreaCatched = true;
        //this->handCursor->setVisible(false);
    }
    if(this->picPreviewWidget->geometry().contains( cursorPos.x(),cursorPos.y() ))
    {
        isPicPreviewAreaCatched = true;
    }
}

void PictureView::catchRelease(int x, int y, int dx, int dy, float vx, float vy, float vz)
{
    qDebug() << "RELEASE..." << endl;
    this->handCursor->setPixmap(handMap);
    isCursorCatched = false;
    isPicAreaCatched = false;
    isPicPreviewAreaCatched = false;

    if(!this->handCursor->isVisible())
    {
        this->handCursor->setVisible(true);
    }
}


int PictureView::angle() const
{
    return this->m_nAngle;
}

void PictureView::setAngle(const int angle)
{
    this->m_nAngle = angle;

    double rate = (double)picPreviewZoomedWidth / (double)picPreviewWidth;
    QMatrix matrix;
    matrix.rotate(m_nAngle);
    matrix.scale(rate, rate);

    QImage image2 = currentImage->transformed(matrix);
    picPreviewLabel->setPixmap(QPixmap::fromImage(image2));
}


int PictureView::distance() const
{
    return m_nDistance;
}

void PictureView::setDistance(const int distance)
{
    m_nDistance = distance;

    QRect rect = picPreviewLabel->geometry();
    int x = rect.x();
    int y = rect.y();
    int w = rect.width();
    int h = rect.height();


    QRect rect2;
    x+=distance;
    rect2.setX(x);
    rect2.setY(y);
    rect2.setWidth(w);
    rect2.setHeight(h);

    picPreviewLabel->setGeometry(rect2);
}

int PictureView::calculateToAngle(const int fromAngle)
{
    int table[9] = {0, 90, 90, 180, 180, 270, 270, 360, 360};
    int k = fromAngle / 45;

    return table[k];
}


