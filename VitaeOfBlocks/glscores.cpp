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
        int x1 = point.x()*side-xDelta;
        int y1 = (point.y()+1)*side-yDelta;
        int x2 = x1 + side;
        int y2 = y1 - side;

        qglColor(color);
        glRecti(x1,y1,x2,y2);

        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, textureID[0]);
        glBegin(GL_POLYGON);
        glTexCoord2d(0.0,0.0); glVertex2i(x1,y2);
        glTexCoord2d(1.0,0.0); glVertex2i(x2,y2);
        glTexCoord2d(1.0,1.0); glVertex2i(x2,y1);
        glTexCoord2d(0.0,1.0); glVertex2i(x1,y1);
        glEnd();

        qglColor(Qt::black);
        glBegin(GL_LINE_LOOP);
            glVertex2i(x1,y1);
            glVertex2i(x1,y2);
            glVertex2i(x2,y2);
            glVertex2i(x2,y1);
        glEnd();

        //изощренная тестура элементов
//        int quarter=(x2-x1)/4;

//        x1=x1+quarter;
//        y1=y1-quarter;
//        x2=x2-quarter;
//        y2=y2+quarter;

//        qglColor(QColor(0,0,0,100));
//        glRecti(x1,y1,x2,y2);

//        qglColor(QColor(255,255,255,150));
//        glBegin(GL_LINE_LOOP);                      //рисуем обводку
//            glVertex2i(x1-1,y1);
//            glVertex2i(x1,y2);
//            glVertex2i(x2,y2);
//            glVertex2i(x2+1,y1);                    //WTF is going on with this 1?
//        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
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

    glEnable(GL_TEXTURE_2D);

    glGenTextures(1,textureID);
    QImage img(":/res/mask.png");
    img=QGLWidget::convertToGLFormat(img);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// задана линейная фильтрация вдали
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
    qglColor("#72a495");                                     //ставим серый цвет
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);                                 //рисуем контур
        glVertex2i(-this->width()/2,-this->height()/2);
        glVertex2i(this->width()/2,-this->height()/2);
        glVertex2i(this->width()/2,this->height()/2);
        glVertex2i(-this->width()/2,this->height()/2);
    glEnd();
    glLineWidth(1);

    paintFigure();
    return;
}
