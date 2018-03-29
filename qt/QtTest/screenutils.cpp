#include "screenutils.h"
#include <QApplication>
#include <QDesktopWidget>

int ScreenUtils::widgetWidth = 1400;
int ScreenUtils::widgetHeight = 900;

ScreenUtils::ScreenUtils()
{
}

ScreenSize ScreenUtils::getScreenSize()
{
    int screenWidth = 0;
    int screenHeight = 0;

    QDesktopWidget * deskWgt = QApplication::desktop();
    if(deskWgt)
    {
        QRect screenRect = deskWgt->screenGeometry();
        screenWidth = screenRect.width();
        screenHeight = screenRect.height();
    }
    ScreenSize size;
    size.height = screenHeight;
    size.width = screenWidth;
    return size;

}
