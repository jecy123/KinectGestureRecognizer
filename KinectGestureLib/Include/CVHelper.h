#pragma once
#include "utils.h"
#include "Hand.h"
#include "dllapi.h"

//#define BTN_CNT 3
#define SHOW_TYPE_HAND			0x00000001
#define SHOW_TYPE_HAND_OUTLINE	0x00000002
#define SHOW_TYPE_HAND_CENTER	0x00000003

#define KeyCode_LEFT	0x00250000
#define KeyCode_UP		0x00260000
#define KeyCode_RIGHT	0x00270000
#define KeyCode_DOWN	0x00280000

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
	
	void setShowType(int type);

	void onMouse(int event, int x, int y, int flags, void * param);
	void ROIShot();
	void addHandThreshold(float val);

	bool showLeftHandFlag;
	bool showRightHandFlag;
	bool showHandCenter;

private:
	Rect drawButton(int index, string text, Point coord, int minWidth = 0);
	Rect drawString(string text, Point coord, Scalar color, float fontScale = 1, int thickNess = 1, int fontFace = FONT_HERSHEY_COMPLEX);
	void drawHand(uchar * imgData, Hand * hand);

	Mat m_image;
	//Rect m_buttons[BTN_CNT];
	int m_showType;
	int m_nPressedKey;
	Hand * m_LeftHand;
	Hand * m_rightHand;
};

