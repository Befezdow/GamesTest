#include "nextshapewidget.h"

void
NexShapeWidget::paintFigure()
{

    Shape * figure = GameArea::generateShape(indexOfFigure);    //генерируем фигуру

    QVector<QPoint> points = figure->getParts();                //получаем её части
    int left = figure->getLeft();
    int right = figure->getRight();
    int top = figure->getTop();
    int bottom = figure->getBottom();

    delete figure;                                              //удаляем фигуру

    int width=(right-left+1)*side;                              //получаем ширину фигуры
    int height=(top-bottom+1)*side;                             //получаем высоту фигуры

    int absoluteLeft =-width/2;                                 //необходимое положение самой левой части
    int relativeLeft = left*side;                               //текущее положение самой левой части
    int xDelta=relativeLeft-absoluteLeft;                       //разница в положениях по X

    int absoluteBottom=-height/2;                               //необходимое положение самой нижней части
    int relativeBottom=bottom*side;                             //текущее положение самой нижней части
    int yDelta=relativeBottom-absoluteBottom;                   //разница в положениях по Y

    foreach (QPoint point, points)                              //идем по всем элементам
    {
        int x1 = point.x()*side-xDelta;                         //получаем 2 точки элемента
        int y1 = (point.y()+1)*side-yDelta;
        int x2 = x1 + side;
        int y2 = y1 - side;

        qglColor(color);                                        //ставим цвет элемента
        glRecti(x1,y1,x2,y2);                                   //рисуем элемент

        glEnable(GL_ALPHA_TEST);                                //включаем прозрачность
        glEnable(GL_BLEND);                                     //включаем смешивание
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      //настраиваем смешивание

        glBindTexture(GL_TEXTURE_2D, textureID[0]);             //начинаем работу с тексурой
        glBegin(GL_POLYGON);                                    //рисуем тексуру
        glTexCoord2d(0.0,0.0); glVertex2i(x1,y2);               //каждой точке текстуры сопоставляем точку на примитиве
        glTexCoord2d(1.0,0.0); glVertex2i(x2,y2);
        glTexCoord2d(1.0,1.0); glVertex2i(x2,y1);
        glTexCoord2d(0.0,1.0); glVertex2i(x1,y1);
        glEnd();

        qglColor(Qt::black);                                    //ставим черный цвет
        glBegin(GL_LINE_LOOP);                                  //рисуем контур элемента
            glVertex2i(x1,y1);
            glVertex2i(x1,y2);
            glVertex2i(x2,y2);
            glVertex2i(x2,y1);
        glEnd();

        //изощренная тестура элементов
        /*
        int quarter=(x2-x1)/4;

        x1=x1+quarter;
        y1=y1-quarter;
        x2=x2-quarter;
        y2=y2+quarter;

        qglColor(QColor(0,0,0,100));
        glRecti(x1,y1,x2,y2);

        qglColor(QColor(255,255,255,150));
        glBegin(GL_LINE_LOOP);                                  //рисуем обводку
            glVertex2i(x1-1,y1);
            glVertex2i(x1,y2);
            glVertex2i(x2,y2);
            glVertex2i(x2+1,y1);                                //WTF is going on with this 1?
        glEnd();
        */

        glDisable(GL_BLEND);                                    //выключаем смешивание
        glDisable(GL_ALPHA_TEST);                               //выключаем прозрачность
    }

}

NexShapeWidget::NexShapeWidget(int side, int width, int height, QWidget *parent):
    QGLWidget(parent),
    indexOfFigure(0),
    side(side)
{
    this->setFixedSize(side*width,side*height);                 //фиксируем размер
}

void
NexShapeWidget::setIndexOfFigure(int index)
{
    indexOfFigure = index % 8;                                  //На случай если кинут больше 8
}

void
NexShapeWidget::setColorOfFigure(QColor color)
{
    this->color=color;

}

void
NexShapeWidget::update()
{
    updateGL();
}

void
NexShapeWidget::initializeGL()
{
    qglClearColor("#e6dab1");                                           //ставим цвет очистки

    glEnable(GL_TEXTURE_2D);                                            //включаем двумерные текстуры

    glGenTextures(1,textureID);                                         //генерируем текстуру

    QImage img(":/res/mask.png");                                       //открываем картинку
    img=QGLWidget::convertToGLFormat(img);                              //преобразуем её в GL формат

    glBindTexture(GL_TEXTURE_2D, textureID[0]);                         //начинаем работу с текстурой
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
                                                                        //ставим текстуре картинку
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //задана линейная фильтрация вдали
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);           //устанавливаем особенности отрисовки для текстур на смешивание
}

void
NexShapeWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);                                        //начинаем работу с матрицей проекций
    glLoadIdentity();                                                   //инициализируем её единичной матрицей
    glViewport(0,0,w,h);                                                //устанавливаем все окно вьюпортом
    glOrtho(-w/2,w/2,-h/2,h/2,-1,1);                                    //ставим начало координат в центр
}

void
NexShapeWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 //очищаем окно
    qglColor("#72a495");                                                //ставим цвет
    glLineWidth(4);                                                     //ставим ширину линии
    glBegin(GL_LINE_LOOP);                                              //рисуем контур окна
        glVertex2i(-this->width()/2,-this->height()/2);
        glVertex2i(this->width()/2,-this->height()/2);
        glVertex2i(this->width()/2,this->height()/2);
        glVertex2i(-this->width()/2,this->height()/2);
    glEnd();

    glLineWidth(1);                                                     //возвращаем исходную ширину линии

    paintFigure();                                                      //рисуем фигуру

    return;
}
