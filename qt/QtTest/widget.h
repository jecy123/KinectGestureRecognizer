#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QCloseEvent>

#include "kinectimpl.h"
#include "basewidget.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setKinectImpl(KinectImpl * impl);
    void closeEvent(QCloseEvent *event);
signals:

public slots:
    void changeView(int num);
private:
    QVector< BaseWidget * > widgets;
    QStackedLayout * stackLayout;
    QVBoxLayout * mainLayout;
    KinectImpl * kinectimpl;

    int currentViewIndex;
};

#endif // WIDGET_H
