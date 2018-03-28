/*
 * sgr_common.h
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#ifndef SGR_COMMON_H_
#define SGR_COMMON_H_

#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

#define SGR_MAX_DIST        99999999
#define SGR_DF_WIDTH        1000
#define SGR_DF_HEIGHT       1000
#define SGR_DF_DIST         50
#define SGR_DF_ST_BY_CNT    5

#define SGR_ABS(a)         ((a) >= 0 ? (a) : 0 - (a))
#define SGR_MAX2(a, b)     ((a) > (b) ? (a) : (b))
#define SGR_MIN2(a, b)     ((a) > (b) ? (b) : (a))
#define SGR_MIN3(a, b, c)  SGR_MIN2(SGR_MIN2(a, b), (c))

namespace sgr
{
    struct ModelHeader
    {
        char sign[3];
        //char lang[6];
        short ver;
        short type;
        short width;
        short height;
        short pointDist;
        int count;
    };

    struct FeatureHeader
    {
        char word[4];
        int strokeCount;
        int count;
    };

    struct Feature
    {
        int strokeCount;
        string word;
        vector<int> feature;
    };

    struct Point
    {
        Point(int xv, int yv): x(xv), y(yv) {}
        int x;
        int y;
    };

    struct Word
    {
        string word;
        int dist;
    };
}

#endif /* SGR_COMMON_H_ */
