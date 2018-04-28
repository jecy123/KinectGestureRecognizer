#define DLL_IMPLEMENT

#include "CVHelper.h"
#include "utils.h"
using namespace cv;
using namespace std;

CVHelper::CVHelper()
{
	m_image.create(cDepthHeight, cDepthWidth, CV_8UC3);
	m_image.setTo(0); 

	m_LeftHand = nullptr;
	m_rightHand = nullptr;
	m_showType = SHOW_TYPE_HAND;

	showLeftHandFlag = false;
	showRightHandFlag = true;
	showHandCenter = false;
}

CVHelper::~CVHelper()
{
}

void CVHelper::ROIShot()
{
	if (m_LeftHand!=nullptr && showLeftHandFlag)
	{
		int x = m_LeftHand->m_leftTopHandPoint.m_depthX - 10;
		int y = m_LeftHand->m_leftTopHandPoint.m_depthY;
		int w = m_LeftHand->m_rightBottomHandPoint.m_depthX - m_LeftHand->m_leftTopHandPoint.m_depthX + 21;
		int h = m_LeftHand->m_rightBottomHandPoint.m_depthY - m_LeftHand->m_leftTopHandPoint.m_depthY + 41;
		Rect roiRect = Rect(x, y, w, h);
		Mat roi = m_image(roiRect);
		stringstream ss;
		string str;
		ss << "rightHand" << getTickCount()<<".png";
		str = ss.str();
		imwrite(str, roi);
	}
	if (m_rightHand != nullptr && showRightHandFlag)
	{
		int x = m_rightHand->m_leftTopHandPoint.m_depthX - 10;
		int y = m_rightHand->m_leftTopHandPoint.m_depthY;
		int w = m_rightHand->m_rightBottomHandPoint.m_depthX - m_rightHand->m_leftTopHandPoint.m_depthX + 21;
		int h = m_rightHand->m_rightBottomHandPoint.m_depthY - m_rightHand->m_leftTopHandPoint.m_depthY + 41;
		Rect roiRect = Rect(x, y, w, h);
		Mat roi = m_image(roiRect);
		stringstream ss;
		string str;
		ss << "rightHand" << getTickCount() << ".png";
		str = ss.str();
		imwrite(str, roi);
	}
}

void CVHelper::setShowType(int type)
{
	this->m_showType = type;
}

void CVHelper::drawPoint(HandPoint point, Scalar color, int radius)
{
	circle(m_image, cvPoint(point.m_depthX, point.m_depthY), radius, color, -1);
}


void CVHelper::drawLine(HandPoint p1, HandPoint p2, Scalar color)
{
	line(m_image, cvPoint(p1.m_depthX, p1.m_depthY), cvPoint(p2.m_depthX, p2.m_depthY), color, 5);
}


void CVHelper::drawHand(uchar * imgData, Hand * hand)
{
	if (hand != nullptr)
	{
		int k = 0;
		int l = 0;

		for (int i = 0; i < cDepthHeight; i++)
		{
			for (int j = 0; j < cDepthWidth; j++)
			{
				if (hand->m_pHandAreaArray[i][j])
				{
					imgData[k++] = 255;
					imgData[k++] = 255;
					imgData[k++] = 255;
				}
				else{
					imgData[k++] = 0;
					imgData[k++] = 0;
					imgData[k++] = 0;
				}
			}
		}

		drawPoint(hand->HandTip, cvScalar(0, 0, 255), 10);
	}
}


void CVHelper::addHandThreshold(float val)
{
	if (m_LeftHand != nullptr)
	{
		m_LeftHand->addThreshold(val);
	}
	if (m_rightHand != nullptr)
	{
		m_rightHand->addThreshold(val);
	}
}

void CVHelper::draw(UINT16 * depthData, Hand * leftHand, Hand * rightHand)
{
	m_image.setTo(0);
	uchar * imgData = (uchar *)m_image.data;


	if (leftHand != nullptr || rightHand != nullptr)
	{
		m_LeftHand = leftHand;
		m_rightHand = rightHand;

		if (m_showType == SHOW_TYPE_HAND){
			int k = 0;
			int l = 0;
			for (int i = 0; i < cDepthHeight; i++)
			{
				for (int j = 0; j < cDepthWidth; j++)
				{

					imgData[k] = 0;
					imgData[k + 1] = 0;
					imgData[k + 2] = 0;

					if (leftHand != nullptr && leftHand->m_pHandAreaArray[i][j] && showLeftHandFlag)
					{
						imgData[k] = 255;
						imgData[k + 1] = 255;
						imgData[k + 2] = 255;
					}
					if (rightHand != nullptr && rightHand->m_pHandAreaArray[i][j] && showRightHandFlag)
					{
						imgData[k] = 255;
						imgData[k + 1] = 255;
						imgData[k + 2] = 255;
					}
					k += 3;
				}
			}
		}
		else if (m_showType == SHOW_TYPE_HAND_OUTLINE)
		{
			int k = 0;
			int l = 0;
			for (int i = 0; i < cDepthHeight; i++)
			{
				for (int j = 0; j < cDepthWidth; j++)
				{

					imgData[k] = 0;
					imgData[k + 1] = 0;
					imgData[k + 2] = 0;

					if (leftHand != nullptr && leftHand->m_pHandLineArray[i][j] && showLeftHandFlag)
					{
						imgData[k] = 255;
						imgData[k + 1] = 255;
						imgData[k + 2] = 255;
					}
					if (rightHand != nullptr && rightHand->m_pHandLineArray[i][j] && showRightHandFlag)
					{
						imgData[k] = 255;
						imgData[k + 1] = 255;
						imgData[k + 2] = 255;
					}
					k += 3;
				}
			}
		}
		//drawPoint(leftHand->HandTip, cvScalar(0, 0, 255), 5);
		
		if (rightHand->m_handState == HandState_Closed)
		{
			drawPoint(rightHand->HandCenter, cvScalar(0, 0, 255), 30);
		}
		if (leftHand->m_handState == HandState_Closed)
		{
			drawPoint(leftHand->HandCenter, cvScalar(0, 0, 255), 30);
		}
			
		if (showHandCenter)
		{
			drawPoint(rightHand->HandCenter, cvScalar(255, 0, 255), 5);
		}
		
		if (showLeftHandFlag){
			stringstream ss;
			ss << "k = " << leftHand->m_depthThreshold << "mm";
			string msg1 = ss.str();
			putText(m_image, msg1,
				cvPoint(leftHand->m_leftTopHandPoint.m_depthX, leftHand->m_rightBottomHandPoint.m_depthY),
				1, 1, cvScalar(0, 0, 255));

			ss.clear();
			ss << "Z = " << setprecision(4)<< leftHand->HandCenter.m_cameraZ << "m";
			string msg2 = ss.str();
			putText(m_image, msg2,
				cvPoint(leftHand->m_leftTopHandPoint.m_depthX, leftHand->m_rightBottomHandPoint.m_depthY + 10), 
				1, 1, cvScalar(0, 0, 255));
		}
		if (showRightHandFlag){
			stringstream ss1;
			ss1 << "k = " << rightHand->m_depthThreshold << "mm";
			string msg1 = ss1.str();
			putText(m_image, msg1,
				cvPoint(rightHand->m_leftTopHandPoint.m_depthX, rightHand->m_rightBottomHandPoint.m_depthY), 
				1, 1, cvScalar(0, 0, 255));

			stringstream ss2;
			ss2 << "Z = " << setprecision(4) <<rightHand->HandCenter.m_cameraZ << "m";
			string msg2 = ss2.str();
			putText(m_image, msg2,
				cvPoint(rightHand->m_leftTopHandPoint.m_depthX, rightHand->m_rightBottomHandPoint.m_depthY + 15), 
				1, 1, cvScalar(0, 0, 255));
		}
		//drawPoint(rightHand->HandTip, cvScalar(0, 0, 255), 5);
		//drawPoint(rightHand->FingerTip, cvScalar(255, 255, 0), 15);
		//drawPoint(rightHand->HandThumb, cvScalar(255, 0, 0), 5);
		//drawPoint(rightHand->HandWrist, cvScalar(255, 255, 0), 5);
	}

	//drawHand(imgData, leftHand);
	//drawHand(imgData, rightHand);
	//if (depthData != nullptr)
	//{

	//	uchar * imgData = (uchar *)m_image.data;
	//	int j = 0;
	//	for (int i = 0; i < cDepthHeight * cDepthWidth; i++)
	//	{
	//		imgData[j++] = depthData[i];
	//		imgData[j++] = depthData[i];
	//		imgData[j++] = depthData[i];
	//	}
	//}


	//if (leftHand != nullptr)
	//{
	//	int k = 0;
	//	int l = 0;

	//	for (int i = 0; i < cDepthHeight; i++)
	//	{
	//		for (int j = 0; j < cDepthWidth; j++)
	//		{
	//			if (rightHand->m_pHandAreaArray[i][j])
	//			{
	//				imgData[k++] = 255;
	//				imgData[k++] = 255;
	//				imgData[k++] = 255;
	//			}
	//			else{
	//				imgData[k++] = 0;
	//				imgData[k++] = 0;
	//				imgData[k++] = 0;
	//			}
	//		}
	//	}

	//	drawPoint(rightHand->HandTip, cvScalar(0, 0, 255), 10);
	//}
	//if (rightHand != nullptr)
	//{
	//	int k = 0;
	//	int l = 0;

	//	for (int i = 0; i < cDepthHeight; i++)
	//	{
	//		for (int j = 0; j < cDepthWidth; j++)
	//		{
	//			if (rightHand->m_pHandAreaArray[i][j])
	//			{
	//				imgData[k++] = 255;
	//				imgData[k++] = 255;
	//				imgData[k++] = 255;
	//			}
	//			else{
	//				imgData[k++] = 0;
	//				imgData[k++] = 0;
	//				imgData[k++] = 0;
	//			}
	//		}
	//	}

	//	drawPoint(rightHand->HandTip, cvScalar(0, 0, 255), 10);

		//CvScalar color = cvScalar(0, 255, 0);
		//circle(m_image, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 5, color, -1);
		//drawPoint(rightHand->HandCenter);
		//drawPoint(rightHand->HandWrist);
		//drawPoint(rightHand->HandThumb);
		//drawPoint(rightHand->HandTip);

		//drawLine(rightHand->HandCenter, rightHand->HandWrist);
		//drawLine(rightHand->HandCenter, rightHand->HandThumb);
		//drawLine(rightHand->HandCenter, rightHand->HandTip);

		/*for (int i = 0; i < rightHand->HandFingers.size(); i++)
		{
			drawPoint(rightHand->HandFingers[i], cvScalar(0, 0, 255), 2);

		}*/

		/*for (int i = 0; i < MAX_IN_FINGER; i++)
		{

			if (rightHand->m_pMin4FingerPoint[i] != nullptr)
			{
				drawPoint(*(rightHand->m_pMin4FingerPoint[i]), cvScalar(0, 255, 255));
			}
		}*/
		//setCursor(rightHand->FingePoint.m_depthX, rightHand->FingePoint.m_depthY);

		//gotoXY(0, 2);
		//cout << rightHand->HandOutline.size() << endl;
		//for (int i = 0; i < rightHand->HandOutline.size(); i++)
		//{
		//	HandPoint hand;
		//	hand.m_depthX = i;
		//	hand.m_depthY = cDepthHeight - (int)rightHand->HandOutline[i].m_disFromCenter;

		//	drawPoint(hand, cvScalar(0, 0, 255), 1);
		//}
		/*stringstream ss;
		ss << "(";
		ss << rightHand->HandCenter.m_depthX;
		ss << ",";
		ss << rightHand->HandCenter.m_depthY;
		ss << ",";
		ss << rightHand->HandCenter.m_cameraZ;
		ss << ")";
		string msg = ss.str();
		putText(m_image, msg, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 1,1,color);*/
	//}
}

void CVHelper::show()
{
	imshow("Hand", m_image); 
	m_nPressedKey = waitKey(10);
}


int CVHelper::getKeyPressed()
{
	return m_nPressedKey;
}


void CVHelper::onMouse(int event, int x, int y, int flags, void * param)
{
}

Rect CVHelper::drawButton(int index, string text, Point coord, int minWidth)
{
	int padding = 10;
	Point textCoord = Point(coord.x + padding, coord.y + padding);
	Rect rcText = drawString(text, textCoord, CV_RGB(255, 255, 255));

	Rect rcButton = Rect(rcText.x - padding, rcText.y - padding,
		rcText.width + padding + padding, rcText.height + padding + padding);

	if (rcButton.width < minWidth)
	{
		rcButton.width = minWidth;
	}

	//Mat matButton = m_image(rcButton);
	//matButton += CV_RGB(90, 90, 90);
	rectangle(m_image, rcButton, CV_RGB(200, 200, 200), 1, CV_AA);
	drawString(text, textCoord, CV_RGB(10, 55, 20));
	return rcButton;
}

Rect CVHelper::drawString(string text, Point coord, Scalar color, float fontScale, int thickNess, int fontFace)
{
	int baseLine = 0;
	Size textSize = getTextSize(text, fontFace, fontScale, thickNess, &baseLine);
	baseLine += thickNess;

	if (coord.y >= 0)
	{
		coord.y += textSize.height;
	}
	else
	{
		coord.y += m_image.rows - baseLine + 1;
	}

	if (coord.x < 0)
	{
		coord.x += m_image.cols - textSize.width + 1;
	}

	Rect boundingRect = Rect(coord.x, coord.y - textSize.height, textSize.width, baseLine + textSize.height);
	putText(m_image, text, coord, fontFace, fontScale, color, thickNess, CV_AA);
	
	return boundingRect;

}

