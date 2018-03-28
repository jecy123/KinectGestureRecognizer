#pragma once
#include "Hand.h"
#include "dllapi.h"
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;


typedef unsigned char handStatus;
typedef unsigned char zoomStatus;

#define STATUS_LEFT 0x01
#define STATUS_RIGHT 0x02
#define STATUS_ALL 0x03

#define ZOOM_NONE 0x00
#define ZOOM_IN 0x01
#define ZOOM_OUT 0x02
#define ROTATE_CW 0x03
#define ROTATE_CCW 0x04

#define DX_DOWN -1
#define DX_UP	1
#define DY_DOWN -1
#define DY_UP	1
#define DZ_DOWN -1
#define DZ_UP	1


#define VX_DOWN -60
#define VX_UP	60
#define VY_DOWN -60
#define VY_UP	60
#define VZ_DOWN -120
#define VZ_UP	120

#define ZOOM_DOWN -40
#define ZOOM_UP 40

#define ZOOM_DATA_SIZE 21

#define ZOOM_IN_THRESHOLD 100 

#define IS_DATA_BETWEEN(a,d,u)  ((a) >= (d) && (a) <= (u))

typedef struct __ZoomArgs
{
	zoomStatus status;
	float scaleRate;
	int rotateRate;
	inline void reset()
	{
		status = ZOOM_NONE;
		scaleRate = 0;
		rotateRate = 0;
	}

}ZoomArgs;

typedef struct __LeastSquare
{
	double a;
	double b;
	double r;

	inline double getY(double x)
	{
		return a * x + b;
	}
}LeastSquare;



//最小二乘法计算线性拟合函数
inline LeastSquare leastSquareMethod(vector< int > & data, int size)
{
	double sumX = 0.0;
	double sumXSquare = 0.0;
	double sumY = 0.0;
	double sumXY = 0.0;

	for (int i = 0; i < size; i++)
	{
		double x = i + 1;
		sumX += x;
		sumXSquare += x * x;

		double y = data[i];

		sumY += y;
		sumXY += x * y;
	}

	double d = size * sumXSquare - sumX * sumX;
	double na = size * sumXY - sumX * sumY;
	double nb = sumXSquare * sumY - sumX * sumXY;

	double a = na / d;
	double b = nb / d;

	double avgX = sumX / size;
	double avgY = sumY / size;

	double sumDXY = 0.0;
	double sumDXSquare = 0.0;
	double sumDYSquare = 0.0;

	for (int i = 0; i < size; i++)
	{
		double x = i + 1;
		double y = data[i];

		sumDXSquare += (x - avgX) * (x - avgX);
		sumDYSquare += (y - avgY) * (y - avgY);
		sumDXY += (x - avgX) * (y - avgY);
	}

	double dr = sqrt(sumDXSquare * sumDYSquare);
	double r = sumDXY / dr;

	LeastSquare ls;
	ls.a = a;
	ls.b = b;
	ls.r = r;

	return ls;

}

typedef struct _HandArgs
{
	int x;
	int y;
	float z;

	int tipX;
	int tipY;
	float tipZ;

	int vx;
	int vy;
	int vz;

	int dx;
	int dy;
	int dz;

	int curvity;
	float disCenterTip;
	float cosine;
	//float centerAndTipDis;


	unsigned long currentTime;
	unsigned long swipeTime;
	int retainTime;
	int zoomTime;
	bool isRetain;
	bool isSwip;
	bool isMove;
	bool isGrab;
	bool isZoom;

	int zoomInCnt;
	LeastSquare zoomLeastSquare;
	vector<int> zoomData;

	_HandArgs()
	{
		zoomData.resize(ZOOM_DATA_SIZE);
		zoomTime = 0;
		reset();
	}

	~_HandArgs()
	{
	}
	void reset()
	{
		x = y = 0;
		z = 0.0;
		tipX = tipY = 0;
		tipZ = 0.0;
		vx = vy = vz = 0.0;
		dx = dy = dz = 0;
		retainTime = 0;
		isRetain = false;
		isSwip = false;
		isMove = false;
		isGrab = false;
		isZoom = false;

		zoomInCnt = 0;
		currentTime = 0; 
		swipeTime = 0;
		disCenterTip = 0;
	}

	inline void refreshTime(unsigned long time)
	{
		if (isSwip)
		{
			unsigned long dt = time - swipeTime;
			if (dt >= 500)
			{
				isSwip = false;
			}
		}
		this->currentTime = time;

	}

	inline void setXYZ(int x, int y, float z, unsigned long currentTime)
	{
		
		if (this->currentTime != 0)
		{
			unsigned long timeInterval = currentTime - this->currentTime;
			int dx = x - this->x;
			int dy = y - this->y;
			int dz = z - this->z;

			setDxDyDz(dx, dy, dz, timeInterval);

			double interval = (double)timeInterval;
			double vx = dx / interval * 100;
			double vy = dy / interval * 100;
			double vz = dz / interval * 100;
			setVxVyVz(vx, vy, vz);
		}
		else
		{
			setDxDyDz(0, 0, 0, 0);
			setVxVyVz(0, 0, 0);
		}

		this->x = x;
		this->y = y;
		this->z = z;
		refreshTime(currentTime);
	}

	inline void setTipXYZ(int x, int y, float z)
	{
		this->tipX = x;
		this->tipY = y;
		this->tipZ = z;
	}

	inline void calculateCurvity(/*unsigned long currentTime*/)
	{
		//this->currentTime = currentTime;

		float k = 10 * (z - tipZ) / (y - tipY);
		curvity = int(k);

		//if (this->currentTime != 0)
		//{
		//	
		//	zoomData[zoomTime] = curvity; 
		//	zoomTime++;
		//	if (zoomTime >= 8)
		//	{
		//		zoomTime = 0;

		//		zoomArgs = leastSquareMethod(zoomData, 8);
		//		if (!IS_DATA_BETWEEN(this->zoomArgs.a, ZOOM_DOWN, ZOOM_UP))
		//		{
		//			isZoom = true;
		//		}
		//		else{
		//			isZoom = false; 
		//		}
		//	}
		//}
		//else
		//{
		//	//zoomTime = 0;
		//	//file << endl;
		//}

	}

	inline void setDxDyDz(int dx, int dy, int dz, int timeInterval)
	{
		this->dx = dx;
		this->dy = dy;
		this->dz = dz;

		if (IS_DATA_BETWEEN(dx, DX_DOWN, DX_UP)
			&& IS_DATA_BETWEEN(dy, DY_DOWN, DY_UP)
			&& IS_DATA_BETWEEN(dz, DZ_DOWN, DZ_UP))
		{
			retainTime += timeInterval;
			if (retainTime >= 800)
			{
				isRetain = true;
				isMove = false;
			}
		}
		else{
			retainTime = 0;
			isRetain = false;
			isMove = true;
		}
	}

	inline void setVxVyVz(int vx, int vy, int vz)
	{
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;

		if (!isSwip)
		{
			if (!IS_DATA_BETWEEN(vx, VX_DOWN, VX_UP)
				|| !IS_DATA_BETWEEN(vy, VY_DOWN, VY_UP)
				|| !IS_DATA_BETWEEN(vz, VZ_DOWN, VZ_UP))
			{
				swipeTime = this->currentTime;
				isSwip = true;
			}
		}
	}

	inline void setCos(float cosine)
	{
		this->cosine = cosine;
	}
}HandArgs;

class DLL_API GestureArgs
{
public:
	GestureArgs();
	~GestureArgs();

	void reset();

	void refreshData(Hand * leftHand, Hand * rightHand, unsigned long time);
	void setCurrentTime(unsigned long currentTime);
	void setXYZ(int lx, int ly, float lz, int rx, int ry, float rz, unsigned long currentTime);
	void setTipXYZ(int lx, int ly, float lz, int rx, int ry, float rz);
	void setVxVyVz(int lvx, int lvy, int lvz, int rvx, int rvy, int rvz);
	void setDxDyDz(int ldx, int ldy, int ldz, int rdx, int rdy, int rdz, int timeInterval);
	void calculateCurvity();
	void calculateLRHandDistance(unsigned long currentTime);

	void output();

		//currentArgs.calculateCurvity(currentTime);
		//currentArgs.setCos(HandPoint::cosin3d(hand->HandCenter, hand->HandWrist, hand->HandTip));

	ZoomArgs& getZoomArgs();
	bool isSwip(handStatus status = STATUS_RIGHT);
	bool isMove(handStatus status = STATUS_RIGHT);
	bool isSwitched(handStatus status = STATUS_RIGHT);
	bool isGrab(handStatus status = STATUS_RIGHT);
	bool isClicked(handStatus status = STATUS_RIGHT);
	bool isBothHandStill();
	bool isZoomCancel(handStatus status = STATUS_RIGHT);
	bool isZoomBegin();
	int getRetainTime(handStatus status = STATUS_RIGHT);
	void setRetainTime(int time, handStatus status = STATUS_RIGHT);
	HandArgs leftHand;
	HandArgs rightHand;
	ZoomArgs zoomArgs;

public:
	unsigned long currentTime;

	/*float leftRightSlope;
	float leftRightSlopeVariation;
	double leftRightSlopeChangeRate;*/

	float leftRightAngle;
	float leftRightAngleVariation;
	double leftRightAngleChangeRate;


	float leftRightDistance;
	float leftRightDisVariation;
	double leftRightDisChangeRate;

};

