#include "glwidget.h"

GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(parent) ,
    xleft(-20),
    xright(20),
    ytop(20),
    ybot(0),
    x(-2.5),
    y(2),
    xstep(0.5),
    ystep(1),
    rectWidth(5)
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
//    glOrtho(-100,100,-100,100,-1,1);
    glOrtho(xleft,xright, ybot , ytop, -1 , 1);
}

void
GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(Qt::darkCyan);
    glRectf(x,y,x+rectWidth,y-rectWidth);
}
void
GlWidget::keyPressEvent(QKeyEvent *event)
{
    switch( event->key() )
    {
    case Qt::Key_Left:
        if(x > xleft)
            x -= xstep;
        break;
    case Qt::Key_Right:
        if(x+rectWidth < xright)
            x += xstep;
        break;
    case Qt::Key_Up:
        if(y < ytop)
            y+= ystep;
        break;
    case Qt::Key_Down:
        if( y - rectWidth > ybot)
            y -= ystep;
        break;
    case Qt::Key_R:
        break;

    }
//    paintGL();
    updateGL();
}
