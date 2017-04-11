#include "glwidget.h"

GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(parent) ,
    x(10),
    y(20),
    xstep(2),
    ystep(2),
    rectWidth(10)
{

}

GlWidget::~GlWidget()
{

}
void
GlWidget::initializeGL()
{
    qglClearColor(Qt::black);
}

void
GlWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height);
    glOrtho(-100,100,-100,100,-1,1);
}

void
GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(Qt::white);
    glRectf(x,y,x+rectWidth,y-rectWidth);
}
void
GlWidget::keyPressEvent(QKeyEvent *event)
{
    switch( event->key() )
    {
        case Qt::Key_Left:
            qDebug()<<"left "<<x;
            x -= xstep;
            qDebug()<<"new x "<<x;
            break;
        case Qt::Key_Right:
            x += xstep;
            break;
        case Qt::Key_Up:
            y+= ystep;
            break;
        case Qt::Key_Down:
            y -= ystep;
            break;
    }
//    paintGL();
    updateGL();
}
