#include "scoretable.h"

Scoretable::Scoretable(int side, QWidget *parent) :
    QWidget(parent),
    window(new GLScores(side,5,5,parent))
{
    QVBoxLayout *vertical=new QVBoxLayout();
    window=new GLScores(side,5,5,parent);
    scores= new QLabel("Your score : "+QString::number(0));
    vertical->addWidget(window);
    vertical->addWidget(scores);
    this->setLayout(vertical);
}

void
Scoretable::changeScore(int score)
{
    scores->setText("Your score : "+QString::number(score));
}

void
Scoretable::setNextFigure(int figureNum, QColor color)
{
    qDebug()<<"Поймал "<<figureNum<<" "<<color;
    window->setIndexOfFigure(figureNum);
    window->setColorOfFigure(color);
    window->update();
}
