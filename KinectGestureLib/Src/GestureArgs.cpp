#define DLL_IMPLEMENT

#include "GestureArgs.h"
#include "HandPoint.h"


GestureArgs::GestureArgs()
{
	reset();
}

GestureArgs::~GestureArgs()
{
}


void GestureArgs::reset()
{
	zoomArgs.reset();
	leftHand.reset();
	rightHand.reset();

	currentTime = 0;

	leftRightAngle = 0;
	leftRightAngleVariation = 0;
	leftRightAngleChangeRate = 0;
	
	leftRightDistance = 0;
	leftRightDisVariation = 0;
	leftRightDisChangeRate = 0;
}

void GestureArgs::refreshData(Hand * leftHand, Hand * rightHand, unsigned long time)
{

	this->setXYZ(
		leftHand->HandCenter.m_depthX,
		leftHand->HandCenter.m_depthY,
		leftHand->HandCenter.m_cameraZ * 1000,
		rightHand->HandCenter.m_depthX,
		rightHand->HandCenter.m_depthY,
		rightHand->HandCenter.m_cameraZ * 1000, time);

	this->setTipXYZ(
		leftHand->HandTip.m_depthX,
		leftHand->HandTip.m_depthY,
		leftHand->HandTip.m_cameraZ * 1000,
		rightHand->HandTip.m_depthX,
		rightHand->HandTip.m_depthY,
		rightHand->HandTip.m_cameraZ * 1000);
	//this->calculateCurvity();
	this->calculateLRHandDistance(time);
}

void GestureArgs::setCurrentTime(unsigned long currentTime)
{
	this->currentTime = currentTime;
}

void GestureArgs::setXYZ(int lx, int ly, float lz, int rx, int ry, float rz, unsigned long currentTime)
{
	this->leftHand.setXYZ(lx, ly, lz, currentTime);
	this->rightHand.setXYZ(rx, ry, rz, currentTime);
}

void GestureArgs::setTipXYZ(int lx, int ly, float lz, int rx, int ry, float rz)
{
	this->leftHand.setTipXYZ(lx, ly, lz);
	this->rightHand.setTipXYZ(rx, ry, rz);
}

void GestureArgs::setVxVyVz(int lvx, int lvy, int lvz, int rvx, int rvy, int rvz)
{
	
	this->leftHand.setVxVyVz(lvx, lvy, lvz);
	this->rightHand.setVxVyVz(rvx, rvy, rvz);
}

void GestureArgs::setDxDyDz(int ldx, int ldy, int ldz, int rdx, int rdy, int rdz, int timeInterval)
{
	this->leftHand.setDxDyDz(ldx, ldy, ldz, timeInterval);
	this->rightHand.setDxDyDz(rdx, rdy, rdz, timeInterval);
}


void GestureArgs::calculateCurvity()
{
	this->leftHand.calculateCurvity();
	this->leftHand.calculateCurvity();
}

//计算双手距离和斜率值
void GestureArgs::calculateLRHandDistance(unsigned long currentTime)
{
	float distanceLRHand = HandPoint::disBtw2Points(leftHand.x, leftHand.y, rightHand.x, rightHand.y);
	//float slopeLRHand = HandPoint::slopeBtw2Points(leftHand.x, leftHand.y, rightHand.x, rightHand.y);
	float angleLRHand = HandPoint::angleBtw2Points(leftHand.x, leftHand.y, rightHand.x, rightHand.y, distanceLRHand);

	if (this->currentTime != 0)
	{
		unsigned long timeInterval = currentTime - this->currentTime;

		int da = (angleLRHand - this->leftRightAngle) * 2;
		this->leftRightAngleVariation = da / 2;
		this->leftRightAngleChangeRate = this->leftRightAngleVariation / (float)timeInterval * 100;
		//this->leftRightSlopeVariation = slopeLRHand - this->leftRightSlope;

		int dis = (distanceLRHand - this->leftRightDistance) * 2;
		this->leftRightDisVariation = dis / 2;
		this->leftRightDisChangeRate = this->leftRightDisVariation / (float)timeInterval * 100;

	}
	else{

		this->leftRightAngleVariation = 0;
		this->leftRightAngleChangeRate = 0;

		this->leftRightDisVariation = 0;
		this->leftRightDisChangeRate = 0;

	}
	this->leftRightAngle = angleLRHand;
	this->leftRightDistance = distanceLRHand;
	this->currentTime = currentTime;
}


void GestureArgs::output()
{
	cout << "Left Hand ";
	cout << "x = " << leftHand.x << " y = "<< leftHand.y <<" z = "<< leftHand.z << endl;
	cout <<"dx = " << leftHand.dx << " dy = " << leftHand.dy << " dz = " << leftHand.dz << endl;
	cout << "vx = " << leftHand.vx << " vy = " << leftHand.vy << " vz = " << leftHand.vz << endl;
	cout << "retain time = " << leftHand.retainTime << "    " << endl;
	//cout << "zoom time = " << leftHand.zoomTime << "    " << endl;
	cout << "isRetain = " << leftHand.isRetain << endl;
	cout << "isSwip = " << leftHand.isSwip << endl;

	cout << "LR Y Dis = " << leftHand.y - rightHand.y << "     " << endl;
	cout << "Right Hand ";
	cout << "x = " << rightHand.x << " y = " << rightHand.y << " z = " << rightHand.z << endl;
	cout << "dx = " << rightHand.dx << " dy = " << rightHand.dy << " dz = " << rightHand.dz << endl;
	cout << "vx = " << rightHand.vx << " vy = " << rightHand.vy << " vz = " << rightHand.vz << endl;
	cout << "retain time = " << rightHand.retainTime << "    " << endl;
	//cout << "zoom time = " << rightHand.zoomTime << "    " << endl;
	cout << "isRetain = " << rightHand.isRetain << endl;
	cout << "isSwip = " << rightHand.isSwip << " currentTime" << this->currentTime << "      " << endl;
	cout << "angle = " << this->leftRightAngle << " var = " << this->leftRightAngleVariation << " rate = " << (int)this->leftRightAngleChangeRate << "  " << endl;
	cout << "dis=" << this->leftRightDistance << " var = " << this->leftRightDisVariation<< " rate = " << this->leftRightDisChangeRate<<"    " << endl;
}

ZoomArgs& GestureArgs::getZoomArgs()
{
	//int zoom_upper_limit = 0;
	//int zoom_lower_limit = 0;


	//if (leftHand.vx < zoom_lower_limit && leftHand.vy > zoom_upper_limit
	//	&& rightHand.vx > zoom_upper_limit && rightHand.vy < zoom_lower_limit)
	//{
	//	zoomArgs.status = ZOOM_OUT;
	//	zoomArgs.scaleRate = (
	//		leftHand.dx * leftHand.dx
	//		+ leftHand.dy * leftHand.dy
	//		+ rightHand.dx * rightHand.dx
	//		+ rightHand.dy * rightHand.dy) / 2;
	//}
	//
	//if (rightHand.vx < zoom_lower_limit && rightHand.vy > zoom_upper_limit 
	//	&& leftHand.vx > zoom_upper_limit && leftHand.vy < zoom_lower_limit)
	//{
	//	zoomArgs.status = ZOOM_IN;
	//	zoomArgs.scaleRate = (
	//		leftHand.dx * leftHand.dx
	//		+ leftHand.dy * leftHand.dy
	//		+ rightHand.dx * rightHand.dx
	//		+ rightHand.dy * rightHand.dy) / 2;
	//}
	

	int slopeChange = this->leftRightAngleVariation;

	if (isBothHandStill())
	{

		zoomArgs.status = ZOOM_NONE;
		zoomArgs.scaleRate = 0;
		zoomArgs.rotateRate = 0;
	}
	else{
		if (this->leftRightAngleVariation <= -10 || this->leftRightAngleVariation >= 10)
		{
			if (this->leftRightAngleVariation >= 10)
			{
				zoomArgs.status = ROTATE_CW;
				zoomArgs.rotateRate = slopeChange * 2;
			}
			else if (this->leftRightAngleVariation <= -10)
			{
				zoomArgs.status = ROTATE_CCW;
				zoomArgs.rotateRate = slopeChange * 2;
			}
		}
		else{
			if (this->leftRightDisVariation >= 8)
			{
				zoomArgs.status = ZOOM_OUT;
				zoomArgs.scaleRate = this->leftRightDisVariation / 10.0 + 1.0;
				//cout << "scaleRate = " << zoomArgs.scaleRate;
			}
			else if (this->leftRightDisVariation <= -8)
			{
				zoomArgs.status = ZOOM_IN;
				zoomArgs.scaleRate = this->leftRightDisVariation / 10.0 - 1.0;
				//cout << "scaleRate = " << zoomArgs.scaleRate;
			}
		}
	}
	
	return this->zoomArgs;
}

bool GestureArgs::isSwip(handStatus status)
{
	bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.isSwip;
		break;
	case STATUS_RIGHT:
		res = rightHand.isSwip;
		break;
	case STATUS_ALL:
		res = leftHand.isSwip && rightHand.isSwip;
		break;
	}
	return res;
}

bool GestureArgs::isMove(handStatus status)
{
	bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.isMove;
		break;
	case STATUS_RIGHT:
		res = rightHand.isMove;
		break;
	case STATUS_ALL:
		res = leftHand.isMove && rightHand.isMove;
		break;
	}
	return res;
}

bool GestureArgs::isSwitched(handStatus status)
{
	bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.isRetain;
		break;
	case STATUS_RIGHT:
		res = rightHand.isRetain;
		break;
	case STATUS_ALL:
		res = leftHand.isRetain && rightHand.isRetain;
		break;
	}
	return res;
}

bool GestureArgs::isGrab(handStatus status)
{
	bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.isGrab;
		break;
	case STATUS_RIGHT:
		res = rightHand.isGrab;
		break;
	case STATUS_ALL:
		res = leftHand.isGrab && rightHand.isGrab;
		break;
	}
	return res;
}


int GestureArgs::getRetainTime(handStatus status)
{
	int time = 0;
	switch (status)
	{
	case STATUS_LEFT:
		time = leftHand.retainTime;
		break;
	case STATUS_RIGHT:
		time = rightHand.retainTime;
		break;
	default:
		time = 0;
		break;
	}
	return time;
}


void GestureArgs::setRetainTime(int time, handStatus status)
{
	switch (status)
	{
	case STATUS_LEFT:
		leftHand.retainTime = time;
		break;
	case STATUS_RIGHT:
		rightHand.retainTime = time;
		break;
	case STATUS_ALL:
		leftHand.retainTime = time;
		rightHand.retainTime = time;
		break;
	}
}

bool GestureArgs::isClicked(handStatus status)
{
	bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.vz < -5;
		break;
	case STATUS_RIGHT:
		res = rightHand.vz < -5;
		break;
	case STATUS_ALL:
		res = (leftHand.vz < -5) && (rightHand.vz < -5);
	}
	return res;
}


bool GestureArgs::isZoomCancel(handStatus status)
{
	/*bool res = false;
	switch (status)
	{
	case STATUS_LEFT:
		res = leftHand.vz > 15;
		break;
	case STATUS_RIGHT:
		res = rightHand.vz > 15;
		break;
	case STATUS_ALL:
		res = (leftHand.vz > 15) && (rightHand.vz > 15);
	}
	return res;*/

	int dy = leftHand.y - rightHand.y;
	return dy > 185 || dy < -185;

}


bool GestureArgs::isZoomBegin()
{
	int dy = leftHand.y - rightHand.y;
	return dy >= -40 && dy <= 40;
}


bool GestureArgs::isBothHandStill()
{
	return IS_DATA_BETWEEN(this->leftHand.dx, -2, 2)
		&& IS_DATA_BETWEEN(this->leftHand.dy, -2, 2)
		&& IS_DATA_BETWEEN(this->rightHand.dx, -2, 2)
		&& IS_DATA_BETWEEN(this->rightHand.dy, -2, 2);
}
