#include "nextshapeandscore.h"
#include <QVBoxLayout>

NextShapeAndScore::NextShapeAndScore(int side, QWidget *parent) :
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

//    QPalette pal;
//    pal.setColor(QPalette::Background,Qt::black);
//    number->setPalette(pal);
    QWidget* wgt=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout;
    lay->addWidget(scores,0,Qt::AlignHCenter);
    lay->addWidget(number,0,Qt::AlignHCenter);
    wgt->setLayout(lay);
    wgt->setObjectName("ScoreFigure");
    scores->setObjectName("ScoreLable");
    number->setObjectName("LCD");

    vertical->addWidget(window,0,Qt::AlignHCenter);
    vertical->addWidget(wgt,0,Qt::AlignHCenter);
//    vertical->addWidget(number,0,Qt::AlignHCenter);
    this->setLayout(vertical);
}

void
NextShapeAndScore::changeScore(unsigned int score)
{
    if (!number->checkOverflow((int(score))))
        number->display(QString::number(score));
}

void
NextShapeAndScore::setNextFigure(int figureNum, QColor color)
{
    qDebug()<<"Поймал "<<figureNum<<" "<<color;
    window->setIndexOfFigure(figureNum);
    window->setColorOfFigure(color);
    window->update();
}
