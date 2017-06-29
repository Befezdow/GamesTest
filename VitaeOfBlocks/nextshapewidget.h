#ifndef GLSCORES_H
#define GLSCORES_H

#include "shape.h"
#include "gamearea.h"

class NexShapeWidget : public QGLWidget
{
    int indexOfFigure;          //индекс фигуры
    int side;                   //сторона одного квадрата
    QColor color;               //текущий цвет
    GLuint textureID[1];        //текстура

    void paintFigure();         //нарисовать фигуру

public:
    NexShapeWidget(int side, int width=5, int height=5, QWidget* parent=Q_NULLPTR);

    void setIndexOfFigure(int index);
    void setColorOfFigure(QColor color);
    void update();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
};

#endif // GLSCORES_H
