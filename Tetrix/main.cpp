#include "gamearea.h"
#include "scoretable.h"
#include <QApplication>
#include <QMessageLogContext>
#include <QString>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QIcon>

void dummyOutput(QtMsgType, const QMessageLogContext&, const QString&)
{}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(dummyOutput);

    int screenWidth=QApplication::desktop()->width();

    GameArea * gameArea=new GameArea(screenWidth/45,14,20);
    Scoretable * scores= new Scoretable(screenWidth/68);
    QWidget * wgt = new QWidget;
    QLabel* names = new QLabel("Made by:\n@Befezdow\n@YouCanKeepSilence");
    QHBoxLayout* hlay = new QHBoxLayout;
    QVBoxLayout* vlay = new QVBoxLayout;

    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),scores,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),scores,SLOT(setNextFigure(int,QColor)));

    hlay->addWidget(gameArea,0,Qt::AlignCenter);
    vlay->addWidget(scores,0,Qt::AlignHCenter | Qt::AlignTop);
    vlay->addWidget(names,0,Qt::AlignHCenter | Qt::AlignBottom);
    hlay->addLayout(vlay);
    wgt->setLayout(hlay);

    wgt->setFocusProxy(gameArea);
    scores->setFocusProxy(gameArea);
    gameArea->setFocus();

    wgt->setWindowTitle("Tetrix");
    wgt->setWindowIcon(QIcon(":/res/icon.png"));
    wgt->show();
    gameArea->start();
    return a.exec();
}
