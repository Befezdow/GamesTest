#include "optionswindow.h"
#include <QFileInfo>


OptionsWindow::OptionsWindow(GameArea *area, int initDifficulty, int screenWidth, QWidget *parent):
    QWidget(parent),
    currentDifficulty(initDifficulty),
    fileName("")
{
    shapeScore= new NextShapeAndScore(screenWidth/68);
    names = new QLabel("Made by:\n@Befezdow\n@YouCanKeepSilence");
    pause = new QPushButton("Pause");
    restart = new QPushButton("Restart");
    difficulty=new QPushButton("Difficulty");
    highScores = new QPushButton("Highscores");
    vlay = new QVBoxLayout;
    buttonLay = new QVBoxLayout;

    gameArea=area;

    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),shapeScore,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),shapeScore,SLOT(setNextFigure(int,QColor)));
    QObject::connect(pause,SIGNAL(clicked(bool)),gameArea,SLOT(switchPause()));
    QObject::connect(restart,SIGNAL(clicked(bool)),gameArea,SLOT(start()));
    QObject::connect(difficulty,SIGNAL(clicked(bool)),this,SLOT(showDifficultyWindow()));
    QObject::connect(highScores,SIGNAL(clicked(bool)),this,SLOT(showScoreTable()));

    buttonLay->addWidget(pause);
    buttonLay->addWidget(restart);
    buttonLay->addWidget(difficulty);
    buttonLay->addWidget(highScores);

    vlay->addWidget(shapeScore,0,Qt::AlignHCenter | Qt::AlignTop);
    vlay->addLayout(buttonLay);
    vlay->addWidget(names,0,Qt::AlignHCenter | Qt::AlignBottom);

    this->setLayout(vlay);

    shapeScore->setFocusProxy(gameArea);
    pause->setFocusProxy(gameArea);
    restart->setFocusProxy(gameArea);
    difficulty->setFocusProxy(gameArea);
    highScores->setFocusProxy(gameArea);
    this->setFocusProxy(gameArea);
}

void OptionsWindow::attachFile(QString fileName)
{
    this->fileName=fileName;
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

void OptionsWindow::readScores()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    scores.clear();

    QDataStream out(&file);
    while (true)
    {
        QDateTime t;
        unsigned int s;
        QString p;
        out>>t>>s>>p;

        if (out.atEnd())
        {
            break;
        }
        else
        {
            scores.push_back(ScoreTableElement(t,s,p));
        }
    }

    file.close();
}

void OptionsWindow::writeScores()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QDataStream out(&file);

    for (int i=0;i<scores.size();++i)
    {
        ScoreTableElement e=scores.at(i);
        out<<e.time<<e.score<<e.playerName;
    }

    file.close();
}

void OptionsWindow::addRecord(unsigned int score,QString player)
{
    scores.push_back(ScoreTableElement(QDateTime::currentDateTime(),score,player));
    std::sort(scores.begin(),scores.end());
    if (scores.size()>20)
    {
        scores.pop_back();
    }
}

void OptionsWindow::showScoreTable()
{
    gameArea->switchPause();

    this->addRecord(12,"Pupkin");
    this->addRecord(13,"Pupkin");

    ScoreTable table(scores);
    table.exec();

    gameArea->switchPause();
}

OptionsWindow::ScoreTableElement::ScoreTableElement():
    score(0)
{}

OptionsWindow::ScoreTableElement::ScoreTableElement(QDateTime t, unsigned int s, QString p):
    time(t),
    score(s),
    playerName(p)
{}

bool OptionsWindow::ScoreTableElement::operator<(const OptionsWindow::ScoreTableElement &ob) const
{
    if (score<ob.score)
    {
        return true;
    }
    else
    {
        if (score==ob.score && time>ob.time)
        {
            return true;
        }
        return false;
    }
}
