#pragma once
#include "utils.h"
#include "Hand.h"
#include "dllapi.h"

class DLL_API CVHelper
{
public:
	CVHelper();
	~CVHelper();
	void draw(UINT16 * depthData, Hand * leftHand, Hand * rightHand);
	void drawPoint(HandPoint point, Scalar color = cvScalar(0, 255,0),int radius = 5);
	void drawLine(HandPoint p1, HandPoint p2, Scalar color = cvScalar(255, 0, 255));
	void show();
	int getKeyPressed();
private:
	void drawHand(uchar * imgData, Hand * hand);

	Mat m_image;
	int m_nPressedKey;
};

