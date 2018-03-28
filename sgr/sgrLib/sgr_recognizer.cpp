/*
 * sgr_recognizer.cpp
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#include "sgr_recognizer.h"
#include "sgr.h"

using namespace sgr;

Recognizer::Recognizer()
{
    mVer = 1;
    mType = 1;
    mWidth = SGR_DF_WIDTH;
    mHeight = SGR_DF_HEIGHT;
    mPointDist = SGR_DF_DIST;
    mLang = "zh-CN";
}

int Recognizer::ver()
{
    return mVer;
}

int Recognizer::type()
{
    return mType;
}

int Recognizer::width()
{
    return mWidth;
}

int Recognizer::height()
{
    return mHeight;
}

int Recognizer::pointDist()
{
    return mPointDist;
}

string Recognizer::lang()
{
    return mLang;
}

int Recognizer::modelSize()
{
    return mFeatures.size();
}

bool Recognizer::ready()
{
    return mFeatures.size() > 0;
}

int Recognizer::init(const string & modelFile)
{
    int headerSize = sizeof(ModelHeader);
    int subSize = sizeof(FeatureHeader);
    int shortSize = sizeof(short);

    ifstream inputFile;
    inputFile.open(modelFile.c_str(), ios::binary);
    if (!inputFile.is_open())
    {
        printf("Fail to open model file: %s\n", modelFile.c_str());
        return -1;
    }
    inputFile.seekg(0, ios::end);
    int fileSize = inputFile.tellg();

    if (fileSize < headerSize)
    {
        inputFile.close();
        printf("Invalid model file: %s\n", modelFile.c_str());
        return -1;
    }

    inputFile.seekg(0, ios::beg);
    try
    {
        ModelHeader header;
        inputFile.read((char *) &header, headerSize);

        bool ok = true;
        if (header.sign[0] != 'S' || header.sign[1] != 'G'
                || header.sign[2] != 'R')
        {
            ok = false;
        }

        if (ok)
        {
            if (header.width < 10 || header.height < 10 || header.pointDist < 1
                    || header.count < 0)
            {
                ok = false;
            }
        }

        if (ok)
        {
            if (fileSize - (header.count) * subSize < 0)
                ok = false;
        }
        if (ok)
        {
            //char lang[8];
            //memset(lang, 0, 8);
            //memcpy(lang, &(header.lang[0]), 6);

            //mLang = lang;
            mVer = header.ver;
            mType = header.type;
            mPointDist = header.pointDist;
            mWidth = header.width;
            mHeight = header.height;

            int cnt = header.count;
            mFeatures.clear();

            for (int i = 0; i < cnt; ++i)
            {
                if (fileSize - subSize < 0)
                {
                    printf("Invalid model file: Sub header is not valid.\n");
                    ok = false;
                    break;
                }

                bool subOk = true;
                FeatureHeader subHeader;
                inputFile.read((char *) &subHeader, subSize);

                if (subHeader.count <= 0 || subHeader.strokeCount <= 0
                        || subHeader.word[0] == '0')
                {
                    printf("Invalid model file: Sub header is not valid.\n");
                    subOk = false;
                    ok = false;
                    break;
                }

                if (subOk)
                {
                    fileSize = fileSize - subSize;
                    if (fileSize - (subHeader.count) * shortSize < 0)
                    {
                        printf(
                                "Invalid model file: Feature data is not valid.\n");
                        subOk = false;
                        ok = false;
                        break;
                    }

                    char newWord[8];
                    memset(newWord, 0, 8);
                    memcpy(newWord, &(subHeader.word[0]), 4);

                    Feature feature;
                    feature.strokeCount = subHeader.strokeCount;
                    feature.word = newWord;

                    for (int j = 0; j < subHeader.count; ++j)
                    {
                        short sv;
                        inputFile.read((char *) &sv, shortSize);
                        int fv = sv;
                        feature.feature.push_back(fv);
                    }
                    mFeatures.push_back(feature);
                    fileSize = fileSize - (subHeader.count) * shortSize;
                }

                if (fileSize <= 0)
                {
                    if (fileSize < 0)
                        ok = false;
                    break;
                }
            }
            if (!ok)
                mFeatures.clear();
        }

    } catch (...)
    {
        printf("Found error when parse model file: %s\n", modelFile.c_str());
    }
    inputFile.close();

    if (mFeatures.size() > 0)
    {
        sort(mFeatures.begin(), mFeatures.end(), cmp_feature);
    }
    return mFeatures.size();
}

int Recognizer::feature(const string & word,
        vector<vector<int> > * featureLists)
{
    if (!featureLists)
        return -1;
    if (word.length() <= 0 || !ready())
        return 0;

    featureLists->clear();

    int cnt = mFeatures.size();
    for (int i = 0; i < cnt; ++i)
    {
        if (mFeatures[i].word == word)
        {
            featureLists->push_back(mFeatures[i].feature);
        }
    }
    return featureLists->size();
}

int Recognizer::recognize(Character * cha, vector<string> * words, int maxCount,
        int dynStroke)
{
    if (!cha || !words)
        return -1;
    if (!ready())
        return 0;

    int strokeCount = cha->strokeCount();
    if (strokeCount <= 0)
        return 0;

    cha->pointDist(mPointDist);
    int x, y, width, height;
    vector<int> featurelist;
    cha->rect(&x, &y, &width, &height);

    int aw = 7 * mWidth;
    int bw = 10 * width;
    int ah = 7 * mHeight;
    int bh = 10 * height;

    if (mWidth / width > 10)
    {
        aw = 1;
        bw = 1;
    }
    if (mHeight / height > 10)
    {
        ah = 1;
        bh = 1;
    }

    cha->resize(aw, bw, ah, bh);
    cha->rect(&x, &y, &width, &height);

    int dx = (mWidth - width) / 2 - x;
    int dy = (mHeight - height) / 2 - y;

    cha->move(dx, dy);
    cha->thin();
    cha->feature(&featurelist);

    std::vector<Word> wordlist;

    int count = mFeatures.size();
    int dist = 0;
    int countDiff = 0;
    int lastDist = 0;
    string lastWord = "";

    if (dynStroke < 0)
    {
        dynStroke = 0 - dynStroke;
        for (int i = 0; i < count; i++)
        {
            countDiff = mFeatures[i].strokeCount - strokeCount;

            if (countDiff > dynStroke)
                break;
            else if (countDiff < 0)
                countDiff = 0 - countDiff;

            if (countDiff > dynStroke)
                continue;

            dist = dtw(featurelist, mFeatures[i].feature);

            Word record;
            record.word = mFeatures[i].word;
            record.dist = dist;
            if (record.word == lastWord)
            {
                if (record.dist < lastDist)
                {
                    wordlist.back().dist = record.dist;
                }
            }
            else
            {
                wordlist.push_back(record);
            }
            lastWord = record.word;
            lastDist = record.dist;
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            countDiff = mFeatures[i].strokeCount - strokeCount;

            if (countDiff < 0)
                continue;
            if (countDiff > dynStroke)
                break;

            dist = dtw(featurelist, mFeatures[i].feature);

            Word record;
            record.word = mFeatures[i].word;
            record.dist = dist;
            if (record.word == lastWord)
            {
                if (record.dist < lastDist)
                {
                    wordlist.back().dist = record.dist;
                }
            }
            else
            {
                wordlist.push_back(record);
            }
            lastWord = record.word;
            lastDist = record.dist;
        }
    }

    std::sort(wordlist.begin(), wordlist.end(), cmp_word);

    int wordcount = wordlist.size();
    wordcount = SGR_MIN2(wordcount, maxCount);

    words->clear();
    for (int i = 0; i < wordcount; i++)
    {
        words->push_back(wordlist[i].word);
    }
    return words->size();
}

int Recognizer::recognize(Character* cha, std::vector<Word> * words, int maxCount, int dynStroke)
{
    if(!cha || !words) return -1;
    if(!ready()) return 0;

    int strokeCount = cha->strokeCount();
    if(strokeCount <= 0) return 0;

    cha->pointDist(mPointDist);

    int x, y, width, height;
    std::vector<int> featureList;

    cha->rect(&x, &y, &width, &height);

    int aw = 7 * mWidth;
    int bw = 10 * width;
    int ah = 7 * mHeight;
    int bh = 10 * height;

    if(mWidth / width > 10)
    {
        aw = 1;
        bw = 1;
    }
    if(mHeight / height > 10)
    {
        ah = 1;
        bh = 1;
    }

    cha->resize(aw, bw, ah, bh);
    cha->rect(&x, &y, &width, &height);

    int dx = (mWidth - width) / 2 - x;
    int dy = (mHeight - height) / 2 - y;

    cha->move(dx, dy);
    cha->thin();
    cha->feature(&featureList);
    words->clear();

    int count = mFeatures.size();
    int dist = 0;
    int countDiff = 0;
    int lastDist = 0;
    std::string lastWord = "";

    if(dynStroke < 0)
    {
        dynStroke = 0 - dynStroke;
        for(int i=0; i<count; i++)
        {
            countDiff = mFeatures[i].strokeCount - strokeCount;

            if(countDiff > dynStroke) break;
            else if(countDiff < 0) countDiff = 0 - countDiff;

            if(countDiff > dynStroke) continue;

            dist = dtw(featureList, mFeatures[i].feature);

            Word record;
            record.word = mFeatures[i].word;
            record.dist = dist;
            if(record.word == lastWord)
            {
                if(record.dist < lastDist)
                {
                    words->back().dist = record.dist;
                }
            }
            else
            {
                words->push_back(record);
            }
            lastWord = record.word;
            lastDist = record.dist;
        }
    }
    else
    {
        for(int i=0; i<count; i++)
        {
            countDiff = mFeatures[i].strokeCount - strokeCount;

            if(countDiff < 0) continue;
            if(countDiff > dynStroke) break;

            dist = dtw(featureList, mFeatures[i].feature);

            Word record;
            record.word = mFeatures[i].word;
            record.dist = dist;
            if(record.word == lastWord)
            {
                if(record.dist < lastDist)
                {
                    words->back().dist = record.dist;
                }
            }
            else
            {
                words->push_back(record);
            }
            lastWord = record.word;
            lastDist = record.dist;
        }
    }
    std::sort(words->begin(), words->end(), cmp_word);
    int wordCount = words->size();
    if(wordCount != maxCount)
    {
        wordCount = SGR_MIN2(wordCount, maxCount);
        words->resize(wordCount);
    }
    return words->size();
}
