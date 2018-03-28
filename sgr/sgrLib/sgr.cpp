/*
 * sgr.cpp
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#include "sgr.h"

using namespace sgr;

bool cmp_word(const Word & a, const Word & b)
{
    return a.dist < b.dist;
}

bool cmp_feature(const Feature & a, const Feature & b)
{
    if (a.strokeCount == b.strokeCount)
        return a.word < b.word;
    else return a.strokeCount < b.strokeCount;
}

int dtw(const vector<int> & s, const vector<int> & t)
{
    int n = s.size() >> 1;
    int m = t.size() >> 1;

//#ifdef WIN32
	vector< vector <int> > DTW(n + 1, vector<int>(m + 1));
//#else
    //int DTW[n+1][m+1];
//#endif
    int i, j, cost;

    if(n > m)
    {
        for (i = 1; i <= m; i++)
        {
            DTW[0][i] = SGR_MAX_DIST;
            DTW[i][0] = SGR_MAX_DIST;
        }
        for(i=m+1; i <= n; i++) DTW[i][0] = SGR_MAX_DIST;
    }
    else if(n < m)
    {
        for (i = 1; i <= n; i++)
        {
            DTW[0][i] = SGR_MAX_DIST;
            DTW[i][0] = SGR_MAX_DIST;
        }
        for(i=n+1; i <= m; i++) DTW[0][i] = SGR_MAX_DIST;
    }
    else
    {
        for (i = 1; i <= m; i++)
        {
            DTW[0][i] = SGR_MAX_DIST;
            DTW[i][0] = SGR_MAX_DIST;
        }
    }

    DTW[0][0] = 0;
    int x, y;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            x = (i-1) << 1;
            y = (j-1) << 1;
            cost = SGR_ABS(s[x] - t[y]) + SGR_ABS(s[x+1] - t[y+1]);
            DTW[i][j] = cost + SGR_MIN3(DTW[i-1][j], DTW[i][j-1], DTW[i-1][j-1]);
        }

    return DTW[n][m];
}




