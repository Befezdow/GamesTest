#include "gamearea.h"
#include <QApplication>
#include "scoretable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int screenWidth=QApplication::desktop()->width();
    GameArea * gameArea=new GameArea(screenWidth/45,10,15);
    Scoretable * scores= new Scoretable(screenWidth/68);
    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),scores,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),scores,SLOT(setNextFigure(int,QColor)));
    QWidget * wgt = new QWidget();
    QHBoxLayout * lay = new QHBoxLayout();
    lay->addWidget(gameArea);
    lay->addWidget(scores);
    wgt->setLayout(lay);
    wgt->setFocusProxy(gameArea);
    scores->setFocusProxy(gameArea);
    gameArea->setFocus();
    wgt->show();
    gameArea->start();
    return a.exec();
}
