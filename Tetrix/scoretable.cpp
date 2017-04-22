#include "scoretable.h"
#include <QVBoxLayout>

Scoretable::Scoretable(int side, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* vertical=new QVBoxLayout();
    window=new GLScores(side,5,5,parent);
    scores=new QLabel("Your score:");

    QFont f=scores->font();
    f.setPointSize(side/1.5);
    scores->setFont(f);

    number=new QLCDNumber(6);
    number->setSegmentStyle(QLCDNumber::Flat);
    number->setFixedSize(5*side,2*side);

    QPalette pal;
    pal.setColor(QPalette::Background,Qt::black);
    number->setPalette(pal);

    vertical->addWidget(window);
    vertical->addWidget(scores,0,Qt::AlignHCenter);
    vertical->addWidget(number,0,Qt::AlignHCenter);
    this->setLayout(vertical);
}

void
Scoretable::changeScore(int score)
{
    if (!number->checkOverflow(score))
        number->display(score);
}

void
Scoretable::setNextFigure(int figureNum, QColor color)
{
    qDebug()<<"Поймал "<<figureNum<<" "<<color;
    window->setIndexOfFigure(figureNum);
    window->setColorOfFigure(color);
    window->update();
}
