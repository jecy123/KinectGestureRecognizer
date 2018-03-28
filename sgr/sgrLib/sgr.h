/*
 * sgr.h
 *
 *  Created on: 2018-3-22
 *      Author: jecy
 */

#ifndef SGR_H_
#define SGR_H_

#include "sgr_common.h"
#include "sgr_stroke.h"
#include "sgr_character.h"
#include "sgr_recognizer.h"

using namespace sgr;

bool cmp_word(const Word & a, const Word & b);
bool cmp_feature(const Feature & a, const Feature & b);
int dtw(const vector<int> & s, const vector<int> & t);

#endif /* SGR_H_ */
