#include "gamearea.h"
#include <QApplication>
#include "scoretable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameArea gameArea(30,10,15);
    Scoretable scores(20);
    QObject::connect(&gameArea,SIGNAL(scoreChanged(int)),&scores,SLOT(changeScore(int)));
    QObject::connect(&gameArea,SIGNAL(throwNextFigure(int,QColor)),&scores,SLOT(setNextFigure(int,QColor)));
    gameArea.show();
    scores.show();
    gameArea.start();
    return a.exec();
}
