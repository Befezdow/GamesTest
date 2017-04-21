#include "gamearea.h"
#include <QApplication>
#include "scoretable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int screenWidth=QApplication::desktop()->width();
    GameArea gameArea(screenWidth/45,10,15);
    Scoretable scores(screenWidth/68);
    QObject::connect(&gameArea,SIGNAL(scoreChanged(int)),&scores,SLOT(changeScore(int)));
    QObject::connect(&gameArea,SIGNAL(throwNextFigure(int,QColor)),&scores,SLOT(setNextFigure(int,QColor)));
    QWidget wgt;
    QHBoxLayout lay;
    lay.addWidget(&gameArea);
    lay.addWidget(&scores);
    wgt.setLayout(&lay);
    wgt.setFocusProxy(&gameArea);
    scores.setFocusProxy(&gameArea);
    gameArea.setFocus();
    wgt.show();
    gameArea.start();
    return a.exec();
}
