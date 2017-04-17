#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <QWidget>
#include <QGLWidget>
#include <QLabel>
#include "shape.h"
#include "glwidget.h"
class Scoretable : public QWidget
{
    Q_OBJECT
    GLWidget *figure;
    QLabel *scores;
public:
    explicit Scoretable(QWidget *parent = 0);

signals:

public slots:
    void changeScore(int score)
    {
        scores->setNum(score);
    }
    void setNextFigure(int figureNum, QColor color )
    {

        switch (figureNum)
        {
        case Shape::Square:


            break;
        default:
            break;
        }
    }
};

#endif // SCORETABLE_H
