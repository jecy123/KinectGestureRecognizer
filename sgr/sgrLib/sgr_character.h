/*
 * sgr_character.h
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#ifndef SGR_CHARACTER_H_
#define SGR_CHARACTER_H_

#include "sgr_stroke.h"
#include <vector>
using namespace std;

namespace sgr
{
    class Character
    {
    public:
        Character();
        int add(int idx, int x, int y);

        void fullPoints(bool full);
        void fillStrokes();

        void fill();
        void thin();

        void resize(int aw, int bw, int ah, int bh);
        void move(int dx, int dy);

        void rect(int * x, int * y, int * w, int * h);
        int feature(vector<int> * featureList);

        int strokeCount();
        void pointDist(int dist);

        void print();
    private:
        int mLastIdx;
        int mMinDist;
        int mStrokeCount;
        bool mFullPoints;
        vector<Stroke> mStrokes;
    };
}

#endif /* SGR_CHARACTER_H_ */
