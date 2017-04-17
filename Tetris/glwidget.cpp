#include "glwidget.h"
#include <iostream>

Shape* generateShape(int typeOfShape)       //генерирует объект фигуры
{                                           //нужно куда-то это засунуть! сее в зад
    switch(typeOfShape)
    {
    case Shape::Square:
        return new Square;
    case Shape::LittleSquare:
        return new LittleSquare;
    case Shape::Stick:
        return new Stick;
    case Shape::TShape:
        return new TShape;
    case Shape::ZShape:
        return new ZShape;
    case Shape::SShape:
        return new SShape;
    case Shape::JShape:
        return new JShape;
    case Shape::LShape:
        return new LShape;
    default:
        return Q_NULLPTR;
    }
}

void
GLWidget::initShape()
{
    if (currentShape)
        delete currentShape;
    //задаем начальное положение центра движ. фигуры
    currentX=(areaWidth-1)/2;               //задаем X
    currentY=areaHeight-1;                  //задаем Y

    qsrand(time(0));

    int colorSeed=qrand()%6;                //генерируем начальный цвет движ. фигуры
    currentColor=colors.at(colorSeed);      //ставим его

    int shapeSeed=qrand()%8;                //генерируем начальную фигуру
    currentShape=generateShape(shapeSeed);  //ставим её

    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if (x<areaWidth && x>=0 && y<areaHeight && y>=0)    //если деталь в области
        {
            if (area.at(x).at(y).isVisible())
            {
                emit gameOver(currentScore);
                return;
            }
            area[x][y].setColor(currentColor);              //ставим её цвет
            area[x][y].show();              //говорим, что нужно её рисовать
        }
    }
}

GLWidget::GLWidget(int side, int width, int height, QWidget *parent):QGLWidget(parent),
    squareSide(side),areaWidth(width),areaHeight(height),currentShape(Q_NULLPTR)
{
    //инициализируем пустое поле
    for (int i=0;i<areaWidth;++i)           //идем по столбцам
    {
        QVector<Primitive> vec;             //создаем столбец
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

    timerId=0;                              //инициализируем id таймера
    currentScore=0;                         //инициализируем счет

    this->setFixedSize(side*width,side*height);             //фиксируем размеры окна под игровую область

    connect(this,SIGNAL(gameOver(int)),SLOT(endGame(int))); //соединяем gameover с показом счета
}

void
GLWidget::initializeGL()
{
    qglClearColor(Qt::white);               //задаем цвет фона
}

void
GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);            //начинаем работать с матрицей проекций
    glLoadIdentity();                       //инициализируем её единичной матрицей
    glViewport(0,0,w,h);                    //устанавливаем все окно вьюпортом
    glOrtho(0,w,0,h,-1,1);                  //устанавливаем начало координат в (0,0)
}

void
GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglColor(Qt::gray);
    glBegin(GL_LINE_STRIP);
        glVertex2i(0,squareSide*(areaHeight-1));
        glVertex2i(squareSide*(areaWidth),squareSide*(areaHeight-1));
    glEnd();
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

void GLWidget::showCurrentShape()
{
    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //показываем фигуру
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].show();
    }
}

void GLWidget::hideCurrentShape()
{
    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //скрываем фигуру
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].hide();
    }
}

bool
GLWidget::moveCurrentShapeDown()
{
    this->hideCurrentShape();                               //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if (y-1<0 || area.at(x).at(y-1).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentY--;
    for (int i=0;i<vec.size();++i)                          //двигаем вниз
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();               //обновляем картинку
    return true;
}

bool
GLWidget::moveCurrentShapeLeft()
{
    this->hideCurrentShape();                               //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if (x-1<0 || area.at(x-1).at(y).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentX--;
    for (int i=0;i<vec.size();++i)                          //двигаем влево
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();               //обновляем картинку
    return true;
}

bool
GLWidget::moveCurrentShapeRight()
{
    this->hideCurrentShape();                               //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if (x+1>=areaWidth || area.at(x+1).at(y).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentX++;
    for (int i=0;i<vec.size();++i)                          //двигаем вправо
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();               //обновляем картинку
    return true;
}

void
GLWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId()==this->timerId)                    //проверяем, тот ли это таймер
    {
        if (!this->moveCurrentShapeDown())
        {
            //проверить на удаление линий + проверить счет
            this->initShape();         //инициализируем новую фигуру
            this->updateGL();               //обновляем картинку
        }
    }
        /*if (currentY==0 || area[currentX][currentY-1].isVisible())   //если фигура уперлась вниз
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
    */
}

void
GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())                                       //смотрим кнопку
    {
    case Qt::Key_Left:                                          //если влево
        this->moveCurrentShapeLeft();
        break;
    case Qt::Key_Right:                                         //если вправо
        this->moveCurrentShapeRight();
        break;
    case Qt::Key_Down:                                          //если вниз
        this->moveCurrentShapeDown();
        break;
    default:
        qDebug()<<"Unknown key";                                //иначе не знаем кнопку
    }

    this->updateGL();                                           //обновляем картинку

    QGLWidget::keyPressEvent(event);                            //кидаем кнопку родителю, а то мало ли
}

void
GLWidget::start()
{
    if (this->timerId)                 //если таймер существует
        this->killTimer(timerId);      //убиваем его
    this->initShape();                 //инициализируем первую фигуру
    timerId=this->startTimer(500);     //запускаем новый
}

void
GLWidget::endGame(int score)
{
    QString info="Your score: "+QString::number(score)+"\n Play more?";
    int i=QMessageBox::information(this,"Game Over",info,QMessageBox::Yes,QMessageBox::No);

    if (i==QMessageBox::Yes)                    //если хочет играть еще
    {
        for (int i=0;i<areaWidth;++i)           //очищаем игровую область
            for (int j=0;j<areaHeight;++j)
            {
                area[i][j].setColor(Qt::white);
                area[i][j].hide();
            }

        this->start();
    }
    else                                        //если не хочет
        qApp->quit();
}
