#include "glscores.h"

void
GLScores::paintFigure()
{

    Shape * figure = GameArea::generateShape(indexOfFigure);
    QVector<QPoint> points = figure->getParts();
    delete figure;
    foreach (QPoint point, points)
    {
        int x = (point.x()-1)*side;
        int y = (point.y()+1)*side;
        int x1 = x + side;
        int y1 = y - side;
        qglColor(color);
        glRecti(x,y,x1,y1);
        qglColor(Qt::black);
        glBegin(GL_LINE_LOOP);
            glVertex2i(x-1,y);
            glVertex2i(x,y1);
            glVertex2i(x1,y1);
            glVertex2i(x1,y);
        glEnd();

    }

}

GLScores::GLScores(int side, int width, int height, QWidget *parent):
    QGLWidget(parent),
    indexOfFigure(0),
    side(side)
{
    this->setFixedSize(side*width,side*height);
}

void
GLScores::setIndexOfFigure(int index)
{
    indexOfFigure = index % 8;              //На случай если кинут больше 8
}

void
GLScores::setColorOfFigure(QColor color)
{
    this->color=color;

}

void
GLScores::update()
{
    updateGL();
}

void
GLScores::initializeGL()
{
    qglClearColor(Qt::white);
}

void
GLScores::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    glOrtho(-w/2,w/2,-h/2,h/2,-1,1);
}

void
GLScores::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintFigure();
    return;
}
