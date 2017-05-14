#include "optionswindow.h"


OptionsWindow::OptionsWindow(GameArea *area, int initDifficulty, int screenWidth, QWidget *parent):
    QWidget(parent),
    currentDifficulty(initDifficulty)
{
    scores= new Scoretable(screenWidth/68);
    names = new QLabel("Made by:\n@Befezdow\n@YouCanKeepSilence");
    pause = new QPushButton("Pause");
    restart = new QPushButton("Restart");
    difficulty=new QPushButton("Difficulty");
    highScores = new QPushButton("Highscores");
    vlay = new QVBoxLayout;
    buttonLay = new QVBoxLayout;

    gameArea=area;

    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),scores,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),scores,SLOT(setNextFigure(int,QColor)));
    QObject::connect(pause,SIGNAL(clicked(bool)),gameArea,SLOT(switchPause()));
    QObject::connect(restart,SIGNAL(clicked(bool)),gameArea,SLOT(start()));
    QObject::connect(difficulty,SIGNAL(clicked(bool)),this,SLOT(showDifficultyWindow()));

    buttonLay->addWidget(pause);
    buttonLay->addWidget(restart);
    buttonLay->addWidget(difficulty);
    buttonLay->addWidget(highScores);

    vlay->addWidget(scores,0,Qt::AlignHCenter | Qt::AlignTop);
    vlay->addLayout(buttonLay);
    vlay->addWidget(names,0,Qt::AlignHCenter | Qt::AlignBottom);

    this->setLayout(vlay);

    scores->setFocusProxy(gameArea);
    pause->setFocusProxy(gameArea);
    restart->setFocusProxy(gameArea);
    difficulty->setFocusProxy(gameArea);
    highScores->setFocusProxy(gameArea);
    this->setFocusProxy(gameArea);
}

void OptionsWindow::showDifficultyWindow()
{
    gameArea->switchPause();
    DifficultyWindow diff(currentDifficulty);

    if (diff.exec()==QDialog::Accepted)
    {
        currentDifficulty=diff.getCurrentDifficulty();
        qDebug()<<currentDifficulty;
        gameArea->setDifficulty(currentDifficulty);
        gameArea->start();
    }
    else
    {
        gameArea->switchPause();
    }
}
