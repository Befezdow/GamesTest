#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <QWidget>
#include <QGLWidget>
#include <QLabel>
#include "glscores.h"

class Scoretable : public QWidget
{
    Q_OBJECT
    GLScores *window;
    QLabel *scores;

public:
    explicit Scoretable(int side, QWidget *parent = 0);
    ~Scoretable()
    {
        qDebug()<<"Таблица в минус";
        delete window;
        delete scores;
    }

public slots:
    void changeScore(int score);
    void setNextFigure(int figureNum, QColor color);
};

#endif // SCORETABLE_H
