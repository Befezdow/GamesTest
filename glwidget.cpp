#include "glwidget.h"

GlWidget::GlWidget(QWidget *parent)
    : QGLWidget(parent) ,
    xleft(0),
    xright(40),
    ytop(40),
    ybot(0)

{
    xstep = (xright - xleft)/X_TILE_COUNT;
    ystep = (ytop - ybot)/Y_TILE_COUNT;
    sizeOfSide = xstep;
    x=xleft;
    y=ybot+ystep;
    for(int i = 0 ; i < X_TILE_COUNT ; i++)
    {
        for(int j = 0; j < Y_TILE_COUNT ; j++)
        {
            tiles[i][j]=0;
        }
    }
}

GlWidget::~GlWidget()
{

}
void
GlWidget::eraseRectangle(float x, float y)
{
    if(!rectangles.isEmpty())
    {
        foreach (myFigure::Rectnagle* rec, rectangles)
        {
            if(rec->x == x && rec->y == y)
            {
                rectangles.removeAt(rectangles.indexOf(rec));
                delete rec;
                return;
            }
        }
    }
}

void
GlWidget::addRectangle(float x, float y)//, float size)
{
    if(!rectangles.isEmpty())
    {
        foreach (myFigure::Rectnagle* rec, rectangles)
        {
            if(rec->x == x && rec->y == y)
            {
                qDebug()<<"already exist!";
                return;
            }
        }
    }
    myFigure::Rectnagle* rec = new myFigure::Rectnagle;
    rec->x = x;
    rec->y = y;
    rec->size = xstep; // квадрату плевать
    rectangles.append(rec);
    int tilex = floor(x / xstep);
    int tiley = floor((y - rec->size) / ystep);
    tiles[tilex][tiley] = 1;
//    qDebug()<<"added x "<<x<<" tilex "<<tilex<<" y "<<y<< " tiley "<<tiley;
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

    foreach (myFigure::Rectnagle* rec, rectangles)
    {
        glRectf(rec->x,rec->y,rec->x+sizeOfSide,rec->y-sizeOfSide);
    }
    qglColor(Qt::darkMagenta);
    glRectf(x,y,x+sizeOfSide,y-sizeOfSide);


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
        if(x+sizeOfSide < xright)
            x += xstep;
        break;
    case Qt::Key_Up:
        if(y < ytop)
            y+= ystep;
        break;
    case Qt::Key_Down:
        if( y - sizeOfSide > ybot)
            y -= ystep;
        break;
    case Qt::Key_D:
//        qDebug()<<"pressed";
        addRectangle(x,y);
        break;
    case Qt::Key_E:
        eraseRectangle(x,y);
        break;

    }
//    paintGL();
    updateGL();
}
