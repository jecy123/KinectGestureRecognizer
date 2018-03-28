#include "gesturecanvas.h"

GestureCanvas::GestureCanvas(QWidget * parent): QLabel(parent)
{

    this->mPoints.clear();
    this->mPenSize = 1;
    this->mGestureTracked = false;
    this->mHandler = NULL;
}

GestureCanvas::~GestureCanvas()
{}

void GestureCanvas::updateCanvas()
{
    this->repaint();
}

void GestureCanvas::clear()
{
    this->mPoints.clear();
    this->repaint();
}

void GestureCanvas::setPenSize(int penSize)
{
    this->mPenSize = penSize;
}

void GestureCanvas::setEventHandler(GestureCanvasEventHandler * handler)
{
    this->mHandler = handler;
}

int GestureCanvas::getPoints(vector< vector<QPoint> > * points)
{
    if (points == NULL)
        return 0;

    points->clear();

    int lCnt = mPoints.size();
    for (int i = 0; i < lCnt; i++)
    {
        vector<QPoint> line;
        int pCnt = mPoints.at(i).size();
        for (int j = 0; j < pCnt; j++)
        {
            int x = mPoints.at(i).at(j).x();
            int y = mPoints.at(i).at(j).y();
            line.push_back(QPoint(x, y));
        }
        points->push_back(line);
    }
    return points->size();
}

void GestureCanvas::fillLine(int index)
{
    int lCnt = mPoints.size();
    if (index < 0 || index >= lCnt)
        return;

    int pCnt = mPoints.at(index).size();
    if(pCnt <= 1) return;

    int deltaX, deltaY;
    int numPixels;
    int d, dinc1, dinc2;
    int x, xinc1, xinc2;
    int y, yinc1, yinc2;
    int x1, y1, x2, y2;
    vector<QPoint> line;
    for (int i = 0; i < pCnt - 1; i++)
    {
        x1 = mPoints.at(index).at(i).x();
        y1 = mPoints.at(index).at(i).y();
        x2 = mPoints.at(index).at(i + 1).x();
        y2 = mPoints.at(index).at(i + 1).y();

        deltaX = abs(x2 - x1);
        deltaY = abs(y2 - y1);

        if(deltaX >= deltaY)
        {
            numPixels = deltaX + 1;
            d = (2 * deltaY) - deltaX;

            dinc1 = deltaY << 1;
            xinc1 = 1;
            yinc1 = 0;

            dinc2 = (deltaY - deltaX) << 1;
            xinc2 = 1;
            yinc2 = 1;
        }
        else
        {
            numPixels = deltaY + 1;
            d = (2 * deltaX) - deltaY;

            dinc1 = deltaX << 1;
            xinc1 = 0;
            yinc1 = 1;

            dinc2 = (deltaX - deltaY) << 1;
            xinc2 = 1;
            yinc2 = 1;

        }

        if (x1 > x2)
        {
            xinc1 = 0 - xinc1;
            xinc2 = 0 - xinc2;
        }

        if (y1 > y2)
        {
            yinc1 = 0 - yinc1;
            yinc2 = 0 - yinc2;
        }

        x = x1;
        y = y1;

        for (int j = 1; j < numPixels; j++)
        {
            line.push_back(QPoint(x, y));
            if (d < 0)
            {
                d += dinc1;
                x += xinc1;
                y += yinc1;
            }
            else
            {
                d += dinc2;
                x += xinc2;
                y += yinc2;
            }
        }
    }

    line.push_back( QPoint(mPoints.at(index).at(pCnt - 1).x(), mPoints.at(index).at(pCnt - 1).y()) );
    mPoints.at(index).clear();

    pCnt = line.size();

    for (int i = 0; i < pCnt; i++)
    {
        mPoints.at(index).push_back(line[i]);
    }
}

void GestureCanvas::fillLines()
{
    int lCnt = mPoints.size();

    for (int  i = 0; i < lCnt; i++)
    {
        fillLine(i);
    }
}



void GestureCanvas::onGestureTrakeBegin()
{

}

void GestureCanvas::onGestureTraking()
{

}

void GestureCanvas::onGestureTrakkEnd()
{
}

void GestureCanvas::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    QPen pen;

    painter.fillRect(QRect(0, 0, this->width(), this->height()),QColor(255, 255, 255));

    pen.setColor(QColor(0, 0, 0));
    pen.setWidth(mPenSize);

    painter.setPen(pen);

    int lCnt = mPoints.size();
    for (int i = 0; i < lCnt; i++)
    {
        int pCnt = mPoints.at(i).size();
        for (int j = 0; j < pCnt; j++)
        {
            painter.drawPoint(mPoints.at(i).at(j));
        }
    }


}
