
#ifndef SCREENUTILS_H
#define SCREENUTILS_H

typedef struct __ScreenSize
{
    int height;
    int width;
}ScreenSize;

class ScreenUtils
{
public:
    ScreenUtils();
    static ScreenSize getScreenSize();

    static int widgetWidth;
    static int widgetHeight;
};
#endif // SCREENUTILS_H
