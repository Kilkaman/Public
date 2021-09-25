#include "MyPlot.h"

#include <qdebug.h>

//
MyPlot::MyPlot(QObject *parent) :
    QObject(parent)
{


}

MyPlot::~MyPlot()
{
    qDebug("By in Thread!");
}
