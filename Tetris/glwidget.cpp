#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(int side, int width, int height, QWidget *parent):QGLWidget(parent),
    squareSide(side),areaWidth(width),areaHeight(height)
{
                                            //инициализируем пустое поле
    for (int i=0;i<areaWidth;++i)           //идем по столбцам
    {
        QVector<Primitive> vec;    //столбец
        for (int j=1;j<=areaHeight;++j)     //идем по строкам столбца
        {
            vec.push_back(Primitive(QPoint(i*squareSide,j*squareSide),Qt::white));
                                            //заполняем столбец пустыми квадратами
        }
        area.push_back(vec);                //добавили столбец
    }

                                            //добавляем цвета для раскраски фигур
    colors.push_back(Qt::red);
    colors.push_back(Qt::blue);
    colors.push_back(Qt::cyan);
    colors.push_back(Qt::yellow);
    colors.push_back(Qt::green);
    colors.push_back(Qt::magenta);

                                            //задаем начальное положение движ. фигуры
    currentX=(areaWidth-1)/2;               //задаем X
    currentY=areaHeight-1;                  //задаем Y
    int seed=qrand()%6;                     //генерируем начальный цвет движ. фигуры
    currentColor=colors.at(seed);           //ставим его
    area[currentX][currentY].setColor(currentColor);
    area[currentX][currentY].show();        //говорим, что нужно её рисовать по таким координатам

    timerId=0;                              //инициализируем id таймера
    currentScore=0;                         //инициализируем счет

    this->setFixedSize(side*width,side*height);             //фиксируем размеры окна под игровую область

    connect(this,SIGNAL(gameOver(int)),SLOT(endGame(int))); //соединяем gameover с показом счета
}

void GLWidget::initializeGL()
{
    qglClearColor(Qt::white);               //задаем цвет фона
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);            //начинаем работать с матрицей проекций
    glLoadIdentity();                       //инициализируем её единичной матрицей
    glViewport(0,0,w,h);                    //устанавливаем все окно вьюпортом
    glOrtho(0,w,0,h,-1,1);                  //устанавливаем начало координат в (0,0)
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i=0;i<area.size();++i)
    {
        for (int j=0;j<area.at(i).size();++j)
        {
            Primitive prim=area.at(i).at(j);
            if (prim.isVisible())
            {
                QPoint p=prim.getPos();
                int x1=p.x();
                int y1=p.y();
                int x2=x1+squareSide;
                int y2=y1-squareSide;
                qglColor(prim.getColor());
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
    if (event->timerId()==this->timerId)                        //проверяем, тот ли это таймер
    {
        if (currentY==0 || area[currentX][currentY-1].isVisible())   //если фигура уперлась вниз
        {
            if (currentY==areaHeight-1)                         //если это верх области
            {
                emit gameOver(currentScore);                    //завершаем игру
            }

            bool needEraseLine=true;                            //проверяем, нужно ли очистить линию
            for (int i=0;i<areaWidth;++i)
                needEraseLine=needEraseLine && area.at(i).at(currentY).isVisible();

            if (needEraseLine)                                  //если нужно
            {
                for (int i=0;i<areaWidth;++i)                   //сдвигаем все на 1 клетку вниз
                    for (int j=currentY;j<areaHeight-1;++j)
                        if(area[i][j+1].isVisible())
                            area[i][j].show();
                        else
                            area[i][j].hide();

                for (int i=0;i<areaWidth;++i)                   //верхнюю линию очищаем
                    area[i][areaHeight-1].hide();

                currentScore+=this->areaWidth;                  //добавляем счет на кол-во уничтоженных блоков
            }
                                                                //задаем исходное положение фигуре
            currentX=(areaWidth-1)/2;                           //задаем X
            currentY=areaHeight-1;                              //задаем Y
            int seed=qrand()%6;                                 //генерируем цвет новой фигуры
            currentColor=colors.at(seed);                       //устанавливаем его
            area[currentX][currentY].setColor(currentColor);
            area[currentX][currentY].show();                    //говорим, что нужно её рисовать по таким координатам
        }
        else                                                    //если не уперлась
        {
            area[currentX][currentY].hide();                    //то двигаем её вниз
            currentY--;
            area[currentX][currentY].setColor(currentColor);
            area[currentX][currentY].show();
        }
    }
    this->updateGL();                                           //обновляем картинку
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())                                       //смотрим кнопку
    {
    case Qt::Key_Left:                                          //если влево
        if (!(currentX<=0 || area[currentX-1][currentY].isVisible()))    //если можем двигать влево
        {
            area[currentX][currentY].hide();              //двигаем влево
            currentX--;
            area[currentX][currentY].setColor(currentColor);
            area[currentX][currentY].show();
        }
        break;
    case Qt::Key_Right:                                         //если вправо
        if (!(currentX>=areaWidth-1 || area[currentX+1][currentY].isVisible()))  //если можем двигать вправо
        {
            area[currentX][currentY].hide();              //двигаем вправо
            currentX++;
            area[currentX][currentY].setColor(currentColor);
            area[currentX][currentY].show();
        }
        break;
    case Qt::Key_Down:                                          //если вниз
        if (!(currentY==0 || area[currentX][currentY-1].isVisible()))    //если можем двигать вниз
        {
            area[currentX][currentY].hide();              //двигаем вниз
            currentY--;
            area[currentX][currentY].setColor(currentColor);
            area[currentX][currentY].show();
        }
        break;
    default:
        qDebug()<<"Unknown key";                                //иначе не знаем кнопку
    }

    this->updateGL();                                           //обновляем картинку

    QGLWidget::keyPressEvent(event);                            //кидаем кнопку родителю, а то мало ли
}

void GLWidget::start()
{
    if (this->timerId)                                          //если таймер существует
        this->killTimer(timerId);                               //убиваем его
    timerId=this->startTimer(500);                              //запускаем новый
}

void GLWidget::endGame(int score)
{
    QString info="Your score: "+QString::number(score)+"\n Play more?";
    int i=QMessageBox::information(this,"Game Over",info,QMessageBox::Yes,QMessageBox::No);

    if (i==QMessageBox::Yes)                                    //если хочет играть еще
    {
        //TO DO
        //нужно вынести инициализацию в отдельную функцию, и написать её в конструкторе и здесь
        //перезапуск
    }
    else                                                        //если не хочет
        qApp->quit();
}
