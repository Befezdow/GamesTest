#ifndef GLSCORES_H
#define GLSCORES_H

#include <QtWidgets>
#include "shape.h"
#include "gamearea.h"

class GLScores : public QGLWidget
{
    int indexOfFigure;
    int side;
    QColor color;

    void paintFigure();

public:
    GLScores(int side, int width=5, int height=5, QWidget* parent=Q_NULLPTR);

    void setIndexOfFigure(int index);
    void setColorOfFigure(QColor color);
    void update();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
};

#endif // GLSCORES_H
