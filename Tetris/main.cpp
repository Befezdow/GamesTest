#include "glwidget.h"
#include <QApplication>
#include "scoretable.h"
//float func(float x)
//{
//    return sin(x);
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w(30,10,15);
    w.start();
    w.show();
    return a.exec();
}
