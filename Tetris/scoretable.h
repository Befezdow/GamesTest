#ifndef SCORETABLE_H
#define SCORETABLE_H

#include <QWidget>
#include <QGLWidget>
#include <QLabel>
#include "shape.h"
#include "glwidget.h"

class GLScores : public QGLWidget
{
public:
    GLScores(int side, int width=5, int height=5, QWidget* parent=Q_NULLPTR) : QGLWidget(parent)
    {
        this->setFixedSize(side*width,side*height);
        this->side = side;
    }

    void setIndexOfFigure(int index)
    {
        indexOfFigure = index % 8;//На случай если кинут больше 8

    }

    void setColorOfFigure(QColor color)
    {
        this->color=color;

    }
    void update()
    {
        updateGL();
    }

protected:

    void initializeGL()
    {
        qglClearColor(Qt::white);
    }
    void resizeGL(int w, int h)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0,0,w,h);
        glOrtho(-w/2,w/2,-h/2,h/2,-1,1);
    }
    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        paintFigure();
        return;
    }
private:
    int indexOfFigure;
    int side;
    QColor color;
    void paintFigure();
};

class Scoretable : public QWidget
{
    Q_OBJECT
    GLScores *window;
    QLabel *scores;
public:
    explicit Scoretable(int side, QWidget *parent = 0);

signals:

public slots:
    void changeScore(int score)
    {
        scores->setText("Your score : "+QString::number(score));
    }
    void setNextFigure(int figureNum, QColor color )
    {
        qDebug()<<"Поймал "<<figureNum<<" "<<color;
        window->setIndexOfFigure(figureNum);
        window->setColorOfFigure(color);
        window->update();
    }
};

#endif // SCORETABLE_H
