#include "glwidget.h"
#include <QApplication>
#include "scoretable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLWidget w(30,10,15);
    Scoretable scores(30);
    QObject::connect(&w,SIGNAL(scoreChanged(int)),&scores,SLOT(changeScore(int)));
    QObject::connect(&w,SIGNAL(throwNextFigure(int,QColor)),&scores,SLOT(setNextFigure(int,QColor)));
    scores.show();
    w.start();
    w.show();
    return a.exec();
}
