#include "kinectimpl.h"
#include "widget.h"
#include <QApplication>
#include <KinectHelper.h>
#include <QDebug>
#include <QThread>
#include <QTimer>

//class KThread: public QThread
//{
////    Q_OBJECT
//public:
//    KThread();
//    void stop();

//private:
//    KinectHelper * helper;
//protected:
//    void run();
//};

//KThread::KThread()
//{
//    helper=new KinectHelper;
//}

//void KThread::run()
//{
//    helper->start();
//}
//void KThread::stop()
//{
//    helper->stop();
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread * thr = new QThread;
    KinectImpl * impl = new KinectImpl;
    impl->moveToThread(thr);
    thr->start();
    QTimer::singleShot(0,impl,SLOT(start()));


    Widget * w = new Widget;
    w->setKinectImpl(impl);
    w->show();

    return a.exec();
}
