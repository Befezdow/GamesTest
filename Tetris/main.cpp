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
//    Scoretable table(30,22,22);

    w.start();
    w.show();
//    table.setNextFigure(Shape::Square, 1);
//    table.show();


//    emit w.scoreChanged(200);

    return a.exec();
}
