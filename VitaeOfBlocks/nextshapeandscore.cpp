#include "nextshapeandscore.h"
#include <QVBoxLayout>

NextShapeAndScore::NextShapeAndScore(int side, QWidget *parent) :
    QWidget(parent)
{
    window=new NexShapeWidget(side,5,5,parent);                 //объект виджета следующей фигуры

    scores=new QLabel("Your score:");                           //обьект надписи
    QFont f=scores->font();
    f.setPointSize(side/1.5);
    scores->setFont(f);

    number=new QLCDNumber(6);                                   //объект LCD экрана
    number->setSegmentStyle(QLCDNumber::Flat);                  //ставим ему плоские сегменты
    number->setFixedSize(5*side,2*side);                        //фиксируем ему размер

    scores->setObjectName("ScoreLable");                        //задаем имена для стиля
    number->setObjectName("LCD");

    QWidget* wgt=new QWidget;
    QVBoxLayout* lay=new QVBoxLayout;
    lay->addWidget(scores,0,Qt::AlignHCenter);
    lay->addWidget(number,0,Qt::AlignHCenter);
    wgt->setLayout(lay);

    wgt->setObjectName("ScoreFigure");                          //задаем имя для стиля

    QVBoxLayout* vertical=new QVBoxLayout;
    vertical->addWidget(window,0,Qt::AlignHCenter);
    vertical->addWidget(wgt,0,Qt::AlignHCenter);
    this->setLayout(vertical);
}

void
NextShapeAndScore::changeScore(unsigned int score)
{
    if (!number->checkOverflow((int(score))))                   //если число влазит
        number->display(QString::number(score));                //ставим его
}

void
NextShapeAndScore::setNextFigure(int figureNum, QColor color)
{
    qDebug()<<"Catched: Shape: "<<figureNum<<"; Color: "<<color;

    window->setIndexOfFigure(figureNum);                        //ставим фигуру
    window->setColorOfFigure(color);                            //ставим цвет
    window->update();                                           //перерисоваваем
}
