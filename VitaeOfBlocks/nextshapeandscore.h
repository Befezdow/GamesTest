#ifndef SCORETABLE_H
#define SCORETABLE_H

#include "nextshapewidget.h"
#include <QLabel>
#include <QLCDNumber>

class NextShapeAndScore : public QWidget
{
    Q_OBJECT
    NexShapeWidget* window;         //окно следующей фигуры
    QLabel* scores;                 //надпись
    QLCDNumber* number;             //текущий счет

public:
    explicit NextShapeAndScore(int side, QWidget *parent = 0);

public slots:
    void changeScore(unsigned int score);
    void setNextFigure(int figureNum, QColor color);
};

#endif // SCORETABLE_H
