/*
 * sgr_stroke.h
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#ifndef SGR_STROKE_H_
#define SGR_STROKE_H_

#include <vector>
#include "sgr_common.h"
using namespace std;

namespace sgr
{
    class Stroke
    {
    public:
        Stroke();
        int add(int x, int y);

        void fill();
        void thin(int pointDist);

        void resize(int aw, int bw, int ah, int bh);
        void move(int dx, int dy);
        vector<Point> * points();
    private:
        vector< Point > mPoints;
    };
}

#endif /* SGR_STROKE_H_ */
