#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(int side, int width, int height, QWidget *parent):QGLWidget(parent)
{
    areaWidth=width;
    areaHeight=height;
    squareSide=side;
    for (int i=0;i<areaWidth;++i)
    {
        QVector<QPair<QPoint,bool>> vec;
        for (int j=1;j<=areaHeight;++j)
        {
            vec.push_back(QPair<QPoint,bool>(QPoint(i*squareSide,j*squareSide),false));
        }
        area.push_back(vec);
    }
    ////////////////////
    for (int i=0;i<area.size();++i)
    {
        for (int j=0;j<area.at(i).size();++j)
            std::cout<<area[i][j].second<<" ";
        std::cout<<std::endl;
    }
    ////////////////////
    currentX=(areaWidth-1)/2;
    currentY=areaHeight-1;
    area[currentX][currentY].second=true;
    timerId=0;
    currentScore=0;
    colors.push_back(Qt::red);
    colors.push_back(Qt::blue);
    colors.push_back(Qt::cyan);
    colors.push_back(Qt::yellow);
    colors.push_back(Qt::green);
    colors.push_back(Qt::magenta);
    int seed=qrand()%6;
    currentColor=colors.at(seed);
    this->setFixedSize(side*width,side*height);
    connect(this,SIGNAL(gameOver(int)),SLOT(endGame(int)));
}

void GLWidget::initializeGL()
{
    qglClearColor(Qt::white);
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    glOrtho(0,w,0,h,-1,1);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i=0;i<area.size();++i)
    {
        for (int j=0;j<area.at(i).size();++j)
        {
            QPair<QPoint,bool> pair=area.at(i).at(j);
            if (pair.second)
            {
                QPoint p=pair.first;
                int x1=p.x();
                int y1=p.y();
                int x2=x1+squareSide;
                int y2=y1-squareSide;
                qglColor(currentColor);
                glRecti(x1,y1,x2,y2);
                qglColor(Qt::black);
                glLineWidth(2);
                glBegin(GL_LINE_LOOP);
                    glVertex2i(x1,y1);
                    glVertex2i(x1,y2);
                    glVertex2i(x2,y2);
                    glVertex2i(x2,y1);
                glEnd();
            }
        }
    }
}

void GLWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId()==this->timerId)
    {
        if (currentY==0 || area[currentX][currentY-1].second)
        {
            if (currentY==areaHeight-1)
            {
                emit gameOver(currentScore);
            }
            bool needEraseLine=true;        //проверяем, нужно очистить линию
            for (int i=0;i<areaWidth;++i)
                needEraseLine=needEraseLine && area.at(i).at(currentY).second;
            if (needEraseLine)              //если нужно
            {
                for (int i=0;i<areaWidth;++i)      //сдвигаем все на 1 клетку вниз
                    for (int j=currentY;j<areaHeight-1;++j)
                        area[i][j].second=area[i][j+1].second;
                for (int i=0;i<areaWidth;++i)
                    area[i][areaHeight-1].second=false; //верхнюю линию очищаем
                currentScore+=this->areaWidth;
            }
            currentX=(areaWidth-1)/2;
            currentY=areaHeight-1;
            area[currentX][currentY].second=true;
            int seed=qrand()%6;
            currentColor=colors.at(seed);
        }
        else
        {
            area[currentX][currentY].second=false;
            currentY--;
            area[currentX][currentY].second=true;
        }
    }
    this->updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (!(currentX<=0 || area[currentX-1][currentY].second))
        {
            area[currentX][currentY].second=false;
            currentX--;
            area[currentX][currentY].second=true;
        }
        break;
    case Qt::Key_Right:
        if (!(currentX>=areaWidth-1 || area[currentX+1][currentY].second))
        {
            area[currentX][currentY].second=false;
            currentX++;
            area[currentX][currentY].second=true;
        }
        break;
    case Qt::Key_Down:
        if (!(currentY==0 || area[currentX][currentY-1].second))
        {
            area[currentX][currentY].second=false;
            currentY--;
            area[currentX][currentY].second=true;
        }
        break;
    default:
        qDebug()<<"Unknown key";
    }
    this->updateGL();
    QGLWidget::keyPressEvent(event);
}

void GLWidget::start()
{
    if (this->timerId)
        this->killTimer(timerId);
    timerId=this->startTimer(500);
}

void GLWidget::endGame(int score)
{
    QString info="Your score: "+QString::number(score)+"\n Play more?";
    int i=QMessageBox::information(this,"Game Over",info,QMessageBox::Yes,QMessageBox::No);
    if (i==QMessageBox::Yes)
    {
        //перезапуск
    }
    else
        qApp->quit();
}
