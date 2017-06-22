#ifndef SCORETABLE_H
#define SCORETABLE_H

#include "glscores.h"
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>

class NextShapeAndScore : public QWidget
{
    Q_OBJECT
    GLScores* window;
    QLabel* scores;
    QLCDNumber* number;

public:
    explicit NextShapeAndScore(int side, QWidget *parent = 0);

public slots:
    void changeScore(unsigned int score);
    void setNextFigure(int figureNum, QColor color);
};

#endif // SCORETABLE_H
