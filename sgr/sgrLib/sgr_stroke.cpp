/*
 * sgr_stroke.cpp
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#include "sgr_stroke.h"
#include "sgr_common.h"

using namespace sgr;

Stroke::Stroke()
{
}

int Stroke::add(int x, int y)
{
    mPoints.push_back(Point(x, y));
    return mPoints.size();
}

void Stroke::resize(int aw, int bw, int ah, int bh)
{
    int pCnt = mPoints.size();
    for (int i = 0; i < pCnt; ++i)
    {
        mPoints[i].x = mPoints[i].x * aw / bw;
        mPoints[i].y = mPoints[i].y * ah / bh;
    }
}
void Stroke::move(int dx, int dy)
{
    int pCnt = mPoints.size();
    for (int i = 0; i < pCnt; ++i)
    {
        mPoints[i].x = mPoints[i].x + dx;
        mPoints[i].y = mPoints[i].y + dy;
    }
}

void Stroke::fill()
{
    int pCnt = mPoints.size();
    if (pCnt <= 1) return;

    int deltaX, deltaY;
    int numPixels;
    int d, dinc1, dinc2;
    int x, xinc1, xinc2;
    int y, yinc1, yinc2;
    int x1, x2;
    int y1, y2;

    vector<Point> line;

    for (int i = 0; i < pCnt - 1; ++i)
    {
        x1 = mPoints[i].x;
        y1 = mPoints[i].y;
        x2 = mPoints[i + 1].x;
        y2 = mPoints[i + 1].y;

        deltaX = SGR_ABS(x2 - x1);
        deltaY = SGR_ABS(y2 - y1);

        //Initialize all vars based on which is the independent variable
        if (deltaX >= deltaY) //x is independent variable
        {
            numPixels = deltaX + 1;
            d = (2 * deltaY) - deltaX;

            dinc1 = deltaY << 1;
            xinc1 = 1;
            yinc1 = 0;

            dinc2 = (deltaY - deltaX) << 1;
            xinc2 = 1;
            yinc2 = 1;
        } else //y is independent variable
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

        //Make sure x and y move in the right directions
        if (x1 > x2)
        {
            xinc1 = 0 - xinc1;
            xinc2 = 0 - xinc2;
        }
        if(y1 > y2)
        {
            yinc1 = 0 - yinc1;
            yinc2 = 0 - yinc2;
        }

        x = x1;
        y = y1;

        for (int j = 1; j < numPixels; j++)
        {
            line.push_back(Point(x, y));
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

    line.push_back(Point(mPoints[pCnt - 1].x, mPoints[pCnt - 1].y));
    mPoints = line;
}

vector<Point> * Stroke::points()
{
    return &mPoints;
}

void Stroke::thin(int pointDist)
{
    int dist = pointDist * pointDist;

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    int k = 0;

    vector<Point> line;
    int pCnt = mPoints.size();
    for (int i = 0; i < pCnt; i++)
    {
        x2 = mPoints[i].x;
        y2 = mPoints[i].y;

        if(k >  0 && (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= dist) continue;

        line.push_back(Point(x2, y2));

        x1 = x2;
        y1 = y2;

        k++;
    }
    mPoints = line;
}
