#include <opencv2\opencv.hpp>
#include <KinectHelper.h>
#include <Windows.h>

using namespace cv;

class GestureRecgnitionImpl : public GestureRecgnition
{
private:
	int x;
	int y;
public:
	GestureRecgnitionImpl()
	{
		x = y = 0;
	}

	void onHandMove(GestureArgs * args)
	{
		int dx = args->rightHand.dx;
		int dy = args->rightHand.dy;
		int rectW = 200;
		int rectH = 112;
		x += dx * 1366 / rectW;
		y += dy * 768 / rectH;
		//SetCursorPos(x, y);
	}

	void onZoomIn(GestureArgs * args)
	{
	}

	void onZoomOut(GestureArgs * args)
	{
	}

	void onClicked(GestureArgs * args)
	{

	}

	void onGrab(GestureArgs * args)
	{
		cout << "Grabed!!!" << endl;
	}
};


//INPUT input = { 0 };
//input.type = INPUT_KEYBOARD;
//input.ki.wVk = VK_ZOOM;

//Sleep(100);
//if (!SendInput(1,&input,sizeof(input)))
//{
//	cout << "Failed!\n";
//}
//int a;
//cin >> a;
//cout << a << endl;
//return 0;

int main(int argc, char ** argv)
{
	KinectHelper k;
	k.startRefreshData(new GestureRecgnitionImpl);
	k.stopRefreshData();

/*
	k.UpdateFrame();
	k.deInit();*/
	return 0;
}