/*
 * sgr_recognizer.h
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#ifndef SGR_RECOGNIZER_H_
#define SGR_RECOGNIZER_H_

#include <string>
#include <vector>

#include "sgr_character.h"

using namespace std;

namespace sgr
{
    class Recognizer
    {
    public:
        Recognizer();

        int ver();
        int type();
        int width();
        int height();
        int pointDist();
        int modelSize();
        string lang();

        bool ready();

        int init(const string & modelFile);

        int feature(const string & word, vector<vector<int> > * featureLists);

        int recognize(Character * cha, vector<string> * words, int maxCount = 10, int dynStroke = 2);
        int recognize(Character * cha, vector<Word> * words, int maxCount = 10, int dynStroke = 2);

    private:
        int mVer;
        int mType;
        int mWidth;
        int mHeight;
        int mPointDist;
        string mLang;
        vector<Feature> mFeatures;
    };
}

#endif /* SGR_RECOGNIZER_H_ */
