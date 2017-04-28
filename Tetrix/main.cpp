#include "gamearea.h"
#include "scoretable.h"
#include <QApplication>
#include <QMessageLogContext>
#include <QString>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>

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
    QPushButton* pause = new QPushButton("Pause");
    QPushButton* restart = new QPushButton("Restart");
    QPushButton* highScores = new QPushButton("Highscores");
    QHBoxLayout* hlay = new QHBoxLayout;
    QVBoxLayout* vlay = new QVBoxLayout;
    QVBoxLayout* buttonLay = new QVBoxLayout;

    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),scores,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),scores,SLOT(setNextFigure(int,QColor)));
    QObject::connect(pause,SIGNAL(clicked(bool)),gameArea,SLOT(switchPause()));
    QObject::connect(restart,SIGNAL(clicked(bool)),gameArea,SLOT(start()));

    buttonLay->addWidget(pause);
    buttonLay->addWidget(restart);
    buttonLay->addWidget(highScores);

    vlay->addWidget(scores,0,Qt::AlignHCenter | Qt::AlignTop);
    vlay->addLayout(buttonLay);
    vlay->addWidget(names,0,Qt::AlignHCenter | Qt::AlignBottom);

    hlay->addWidget(gameArea,0,Qt::AlignCenter);
    hlay->addLayout(vlay);
    wgt->setLayout(hlay);

    wgt->setFocusProxy(gameArea);
    scores->setFocusProxy(gameArea);
    pause->setFocusProxy(gameArea);
    restart->setFocusProxy(gameArea);
    highScores->setFocusProxy(gameArea);
    gameArea->setFocus();

    wgt->setWindowTitle("Tetrix");
    wgt->setWindowIcon(QIcon(":/res/icon.png"));
    wgt->show();
    pause->show();
    gameArea->start();
    return a.exec();
}
