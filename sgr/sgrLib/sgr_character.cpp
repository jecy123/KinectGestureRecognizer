/*
 * sgr_character.cpp
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#include "sgr_character.h"
#include "sgr_stroke.h"
#include "sgr_common.h"
using namespace sgr;

Character::Character()
{
    mLastIdx = -1;
    mMinDist = SGR_DF_DIST;
    mStrokeCount = 0;
    mFullPoints = false;
}

int Character::strokeCount()
{
    return mStrokeCount;
}

void Character::pointDist(int dist)
{
    mMinDist = dist;
}

int Character::add(int idx, int x, int y)
{
    if (idx < 0)
        return 0;
    if (idx != mLastIdx)
    {
        Stroke newOne;
        newOne.add(x, y);
        mStrokes.push_back(newOne);
        mStrokeCount++;
        mLastIdx = idx;
    }
    else
    {
        if (mStrokes.size() > 0)
            mStrokes.back().add(x, y);
    }
    return mStrokeCount;
}

void Character::fullPoints(bool full)
{
    mFullPoints = full;
}
//模型中离散的点填充起来，便于更进一步识别
void Character::fillStrokes()
{
    if (mFullPoints)
        return;
    int cnt = mStrokes.size();

    for (int i = 0; i < cnt; ++i)
    {
        mStrokes[i].fill();
    }
    mFullPoints = true;
}

//把每个字之间的笔画连起来，用以识别连字
void Character::fill()
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    int cnt, i, j;
    int dist = mMinDist * mMinDist * 2;

    j = 0;
    vector<Stroke>::iterator it = mStrokes.begin();
    cnt = mStrokes.size();

    for (i = 0; i < cnt - 1; ++i)
    {
        it++;

        x1 = mStrokes[j].points()->back().x;
        y1 = mStrokes[j].points()->back().y;

        x2 = mStrokes[j + 1].points()->front().x;
        y2 = mStrokes[j + 1].points()->front().y;

        //前一笔的起点和后一笔的终点距离大于mMinDist(默认值是50)时，加入两笔之间的连线
        if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) > dist)
        {
            Stroke newOne;
            newOne.add(x1, y1);
            newOne.add(x2, y2);

            if (mFullPoints)
                newOne.fill();
            it = mStrokes.insert(it, newOne);
            it++;
            j++;
        }
        j++;
    }
}

void Character::thin()
{
    int cnt = mStrokes.size();
    for (int i = 0; i < cnt; ++i)
    {
        mStrokes[i].thin(mMinDist);
    }
}

void Character::resize(int aw, int bw, int ah, int bh)
{
    int cnt = mStrokes.size();
    for (int i = 0; i < cnt; ++i)
    {
        mStrokes[i].resize(aw, bw, ah, bh);
    }
}

void Character::move(int dx, int dy)
{
    int cnt = mStrokes.size();
    for (int i = 0; i < cnt; ++i)
    {
        mStrokes[i].move(dx, dy);
    }
}

void Character::rect(int * x, int * y, int * w, int * h)
{
    int xMin = SGR_MAX_DIST;
    int yMin = SGR_MAX_DIST;

    int xMax = 0;
    int yMax = 0;

    int ptx = 0;
    int pty = 0;

    int cnt = mStrokes.size();

    for (int i = 0; i < cnt; ++i)
    {
        int pCnt = mStrokes[i].points()->size();
        for (int j = 0; j < pCnt; ++j)
        {
            ptx = mStrokes[i].points()->at(j).x;
            pty = mStrokes[i].points()->at(j).y;

            xMin = SGR_MIN2(xMin, ptx);
            yMin = SGR_MIN2(yMin, pty);

            xMax = SGR_MAX2(xMax, ptx);
            yMax = SGR_MAX2(yMax, pty);
        }
    }

    *x = xMin;
    *y = yMin;
    *w = xMax - xMin + 1;
    *h = yMax - yMin + 1;
}

void Character::print()
{
    int ptx = 0;
    int pty = 0;
    int cnt = mStrokes.size();
    for (int i = 0; i < cnt; ++i)
    {
        int pCnt = mStrokes[i].points()->size();
        for (int j = 0; j < pCnt; ++j) {
            ptx = mStrokes[i].points()->at(j).x;
            pty = mStrokes[i].points()->at(j).y;
            printf("[%d, %d] = (%d, %d)\n", i, j, ptx, pty);
        }
    }
}

int Character::feature(vector<int> * featureList)
{
    if (!featureList) return -1;
    featureList->clear();
    int ptx = 0;
    int pty = 0;
    int cnt = mStrokes.size();

    for (int i = 0; i < cnt; ++i) {
        int pCnt = mStrokes[i].points()->size();
        //if(pCnt <= 0) continue;
        for (int j = 0; j < pCnt; ++j) {
            ptx = mStrokes[i].points()->at(j).x;
            pty = mStrokes[i].points()->at(j).y;
            featureList->push_back(ptx);
            featureList->push_back(pty);
        }
    }
    return featureList->size();
}




