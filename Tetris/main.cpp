#include "glwidget.h"
#include <QApplication>
#include "scoretable.h"
float func(float x)
{
    return sin(x);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w(30,10,15);
    Scoretable table;
    w.start();
    w.show();
    table.show();
    QObject::connect(&w,SIGNAL(scoreChanged(int)),&table,SLOT(changeScore(int)));
    emit w.scoreChanged(200);

    return a.exec();
}
