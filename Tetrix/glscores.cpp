#include "glscores.h"

void
GLScores::paintFigure()
{

    Shape * figure = GameArea::generateShape(indexOfFigure);
    QVector<QPoint> points = figure->getParts();
    int left = figure->getLeft();
    int right = figure->getRight();
    int top = figure->getTop();
    int bottom = figure->getBottom();
    delete figure;
    int width=(right-left+1)*side;
    int height=(top-bottom+1)*side;

    int absoluteLeft =-width/2;                 //необходимое положение самой левой части
    int relativeLeft = left*side;               //текущее положение самой левой части
    int xDelta=relativeLeft-absoluteLeft;       //разница в положениях по X

    int absoluteBottom=-height/2;               //необходимое положение самой нижней части
    int relativeBottom=bottom*side;             //текущее положение самой нижней части
    int yDelta=relativeBottom-absoluteBottom;   //разница в положениях по Y

    foreach (QPoint point, points)
    {
        int x = point.x()*side-xDelta;
        int y = (point.y()+1)*side-yDelta;
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
