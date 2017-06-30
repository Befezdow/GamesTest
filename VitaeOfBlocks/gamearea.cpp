#include "gamearea.h"
#include <QTimerEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QTime>
#include <QImage>

void
GameArea::randomize()
{
    nextColor=qrand()%6;
    nextShape=qrand()%8;
    if (currentShape)                                   //убираем повторяющиеся подряд фигуры
    {
        if (nextShape==*currentShape)
            nextShape=(nextShape+1)%8;
    }
    qDebug()<<"Generated: Shape: "<<nextShape<<"; Color: "<<nextColor;
    emit throwNextFigure(nextShape,colors.at(nextColor));
}

void
GameArea::setDifficulty(int d)
{
    difficulty=d%5;                                     //на всякий случай берем остаток от 5
}

bool
GameArea::isPaused() const
{
    return pause;
}

bool
GameArea::isGameOver() const
{
    return gameover;
}

void
GameArea::setGameOver()
{
    gameover=true;                                      //включаем конец игры
    emit gameOver(this->currentScore);                  //отправляем текущий счет
}

void
GameArea::upSpeed()
{
    if (difficulty!=0 && shapesCount>shapesForSpeedUp)  //увеличиваем скорость падения, если уже можно
    {
        if (currentSpeed>difficulty)                    //если скорость не предельная
        {
            this->killTimer(timerId);                   //убиваем текущий таймер
            currentSpeed-=difficulty;                   //увеличиваем скорость падения
            timerId=this->startTimer(currentSpeed);     //запускаем новый
        }
    }
}

void
GameArea::initShape()
{
    if (currentShape)
        delete currentShape;

    //задаем начальное положение центра движ. фигуры
    currentX=(areaWidth-1)/2;                               //задаем X
    currentY=areaHeight-1;                                  //задаем Y

    int colorSeed=nextColor;                                //генерируем начальный цвет движ. фигуры
    currentColor=colors.at(colorSeed);                      //ставим его

    int shapeSeed=nextShape;                                //генерируем начальную фигуру
    currentShape=generateShape(shapeSeed);                  //ставим её

    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if (x<areaWidth && x>=0 && y<areaHeight && y>=0)    //если деталь в области
        {
            if (area.at(x).at(y).isVisible())
            {
                gameover=true;
                emit gameOver(currentScore);
                return;
            }
            area[x][y].setColor(currentColor);              //ставим её цвет
            area[x][y].show();                              //говорим, что нужно её рисовать
        }
    }
}


GameArea::GameArea(int side, int width, int height, int numForSpeedUp,int diff, QWidget *parent):
    QGLWidget(parent),
    squareSide(side),
    areaWidth(width),
    areaHeight(height),
    currentShape(Q_NULLPTR),
    timerId(0),
    currentScore(0),
    shapesCount(0),
    currentSpeed(400),
    shapesForSpeedUp(numForSpeedUp),
    difficulty(diff%5),
    pause(false),
    gameover(false)

{
    //инициализируем пустое поле
    for (int i=0;i<areaWidth;++i)                           //идем по столбцам
    {
        QVector<Primitive> vec;                             //создаем столбец
        for (int j=1;j<=areaHeight;++j)                     //идем по строкам столбца
        {
            vec.push_back(Primitive(QPoint(i*squareSide,j*squareSide),Qt::white));
                                                            //заполняем столбец пустыми квадратами
        }
        area.push_back(vec);                                //добавили столбец
    }

    //добавляем цвета для раскраски фигур
    colors.push_back(Qt::red);
    colors.push_back(Qt::blue);
    colors.push_back(Qt::cyan);
    colors.push_back(Qt::yellow);
    colors.push_back(Qt::green);
    colors.push_back(Qt::magenta);

    this->setFixedSize(side*width+squareSide/5,side*height+squareSide/7.5);
                                                            //фиксируем размеры окна под игровую область
}

GameArea::~GameArea()
{
    delete currentShape;
    QGLWidget::destroy();
    killTimer(timerId);
}

Shape*
GameArea::generateShape(int typeOfShape)
{
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
GameArea::initializeGL()
{
    qglClearColor("#e6dab1");                                           //задаем цвет фона
    glEnable(GL_TEXTURE_2D);                                            //включаем двумерные текстуры
    glGenTextures(3,textureID);                                         //создаем текстуры

    QImage img(":/res/mask.png");                                       //открываем картинку
    img=QGLWidget::convertToGLFormat(img);                              //преобразуем её в GL формат
    glBindTexture(GL_TEXTURE_2D, textureID[0]);                         //начинаем работу с 1 текстурой
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
                                                                        //устанавливаем картинку в текстуру
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //задана линейная фильтрация вдали

    img.load(":/res/pause.png");                                        //открываем картинку
    img=QGLWidget::convertToGLFormat(img);                              //преобразуем её в GL формат
    glBindTexture(GL_TEXTURE_2D,textureID[1]);                          //начинаем работу со 2 текстурой
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
                                                                        //устанавливаем картинку в текстуру
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //задана линейная фильтрация вдали

    img.load(":/res/gameover.png");                                     //открываем картинку
    img=QGLWidget::convertToGLFormat(img);                              //преобразуем её в GL формат
    glBindTexture(GL_TEXTURE_2D,textureID[2]);                          //начинаем работу с 3 текстурой
    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)img.width(), (GLsizei)img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
                                                                        //устанавливаем картинку в текстуру
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   //задана линейная фильтрация вблизи
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);   //задана линейная фильтрация вдали
}

void
GameArea::resizeGL(int w, int h)
{
    float lineWidth=squareSide/15+1;
    glMatrixMode(GL_PROJECTION);                                        //начинаем работать с матрицей проекций
    glLoadIdentity();                                                   //инициализируем её единичной матрицей
    glViewport(0,0,w,h);                                                //устанавливаем все окно вьюпортом
    glOrtho(-lineWidth,areaWidth*squareSide+lineWidth,-lineWidth,areaHeight*squareSide+lineWidth,-1,1); //устанавливаем орты
}

void
GameArea::paintGL()
{
    float lineWidth=squareSide/15;                              //определяем толщину линий

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);   //устанавливаем особенности отрисовки для текстур на смешивание

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         //очищаем поле
    qglColor("#72a495");                                        //ставим цвет
    glLineWidth(lineWidth);                                     //ставим ширину линии
    glBegin(GL_LINE_STRIP);                                     //рисуем предельную линию
        glVertex2i(-lineWidth,squareSide*(areaHeight-1));
        glVertex2i(squareSide*(areaWidth)+lineWidth,squareSide*(areaHeight-1));
    glEnd();

    for (int i=0;i<area.size();++i)                             //отрисовываем все поле по клеткам
    {
        for (int j=0;j<area.at(i).size();++j)
        {
            Primitive prim=area.at(i).at(j);                    //получаем клетку
            if (prim.isVisible())                               //если её нужно рисовать
            {
                QPoint p=prim.getPos();                         //получаем её координаты
                int x1=p.x();                                   //получаем верхний левый угол
                int y1=p.y();
                int x2=x1+squareSide;                           //получаем правый нижний угол
                int y2=y1-squareSide;
                qglColor(prim.getColor());                      //ставим клетке её цвет
                glRecti(x1,y1,x2,y2);                           //рисуем клетку

                glEnable(GL_ALPHA_TEST);                        //включаем прозрачность
                glEnable(GL_BLEND);                             //включаем смешивание
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//настраемаем смешивание

                glBindTexture(GL_TEXTURE_2D, textureID[0]);     //начинаем работу с 1 текстурой
                glBegin(GL_POLYGON);                            //рисуем её
                glTexCoord2d(0.0,0.0); glVertex2i(x1,y2);       //каждой точке текстуры сопоставляем точку на примитиве
                glTexCoord2d(1.0,0.0); glVertex2i(x2,y2);
                glTexCoord2d(1.0,1.0); glVertex2i(x2,y1);
                glTexCoord2d(0.0,1.0); glVertex2i(x1,y1);
                glEnd();

                qglColor(Qt::black);                            //ставим черный цвет
                glBegin(GL_LINE_LOOP);                          //рисуем обводку
                    glVertex2i(x1,y1);
                    glVertex2i(x1,y2);
                    glVertex2i(x2,y2);
                    glVertex2i(x2,y1);
                glEnd();

                //изощренная тестура элементов
//                int quarter=(x2-x1)/4;                        //четверть стороны квадрата

//                x1=x1+quarter;                                //точки нового квадрата
//                y1=y1-quarter;
//                x2=x2-quarter;
//                y2=y2+quarter;

//                qglColor(QColor(0,0,0,100));                  //ставим черный полупрозрачный цвет
//                glRecti(x1,y1,x2,y2);                         //рисуем квадрат

//                qglColor(QColor(255,255,255,150));            //ставим белый полупрозрачный цвет
//                glBegin(GL_LINE_LOOP);                        //рисуем обводку
//                    glVertex2i(x1,y1);
//                    glVertex2i(x1,y2);
//                    glVertex2i(x2,y2);
//                    glVertex2i(x2,y1);
//                glEnd();

                glDisable(GL_BLEND);                            //выключаем смешивание
                glDisable(GL_ALPHA_TEST);                       //выключаем прозрачность

            }
        }
    }
    qglColor("#72a495");                                        //ставим цвет
    glBegin(GL_LINE_STRIP);                                     //рисуем контур
        glVertex2i(-lineWidth,squareSide*areaHeight+lineWidth);
        glVertex2i(-lineWidth,-lineWidth);
        glVertex2i(squareSide*(areaWidth)+lineWidth,-lineWidth);
        glVertex2i(squareSide*(areaWidth)+lineWidth,squareSide*areaHeight+lineWidth);
    glEnd();

    if (gameover)                                               //если конец игры
    {
        int x1=0;                                               //определяем положение текстуры gameover
        int x2=this->width()-lineWidth;
        int y1=this->height()*0.75;
        int y2=this->height()*0.25;

        glEnable(GL_ALPHA_TEST);                                //включаем прозрачность
        glEnable(GL_BLEND);                                     //включаем смешивание
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      //настраемаем смешивание

        glBindTexture(GL_TEXTURE_2D, textureID[2]);             //начинаем работу с 3 текстурой
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//устанавливаем особенности отрисовки для текстур на замену
        glBegin(GL_POLYGON);                                    //рисуем её
        glTexCoord2d(0.0,0.0); glVertex2i(x1,y2);               //каждой точке текстуры сопоставляем точку на примитиве
        glTexCoord2d(1.0,0.0); glVertex2i(x2,y2);
        glTexCoord2d(1.0,1.0); glVertex2i(x2,y1);
        glTexCoord2d(0.0,1.0); glVertex2i(x1,y1);
        glEnd();

        glDisable(GL_BLEND);                                    //выключаем смешивание
        glDisable(GL_ALPHA_TEST);                               //выключаем прозрачность
    }
    else if (pause)                                             //если пауза
    {
        int x1=0;                                               //определяем положение текстуры pause
        int x2=this->width()-lineWidth;
        int y1=this->height()*0.75;
        int y2=this->height()*0.25;

        glEnable(GL_ALPHA_TEST);                                //включаем прозрачность
        glEnable(GL_BLEND);                                     //включаем смешивание
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      //настраемаем смешивание

        glBindTexture(GL_TEXTURE_2D, textureID[1]);             //начинаем работу со 2 текстурой
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//устанавливаем особенности отрисовки для текстур на замену
        glBegin(GL_POLYGON);                                    //рисуем её
        glTexCoord2d(0.0,0.0); glVertex2i(x1,y2);               //каждой точке текстуры сопоставляем точку на примитиве
        glTexCoord2d(1.0,0.0); glVertex2i(x2,y2);
        glTexCoord2d(1.0,1.0); glVertex2i(x2,y1);
        glTexCoord2d(0.0,1.0); glVertex2i(x1,y1);
        glEnd();

        glDisable(GL_BLEND);                                    //выключаем смешивание
        glDisable(GL_ALPHA_TEST);                               //выключаем прозрачность
    }
}

void
GameArea::showCurrentShape()
{
    QVector<QPoint> vec=currentShape->getParts();               //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                              //показываем фигуру
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        area[x][y].show();
    }
}

void
GameArea::hideCurrentShape()
{
    QVector<QPoint> vec=currentShape->getParts();               //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                              //скрываем фигуру
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        area[x][y].hide();
    }
}

bool
GameArea::moveCurrentShapeDown()
{
    this->hideCurrentShape();                                   //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();               //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                              //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        if (y-1<0 || area.at(x).at(y-1).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentY--;
    for (int i=0;i<vec.size();++i)                              //двигаем вниз
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();                                           //обновляем картинку
    return true;
}

bool
GameArea::moveCurrentShapeLeft()
{
    this->hideCurrentShape();                                   //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();               //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                              //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        if (x-1<0 || area.at(x-1).at(y).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentX--;
    for (int i=0;i<vec.size();++i)                              //двигаем влево
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();                                           //обновляем картинку
    return true;
}

bool
GameArea::moveCurrentShapeRight()
{
    this->hideCurrentShape();                                   //скрываем текущую фигуру

    QVector<QPoint> vec=currentShape->getParts();               //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                              //проверяем, можем ли двигать
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        if (x+1>=areaWidth || area.at(x+1).at(y).isVisible())
        {
            this->showCurrentShape();
            return false;
        }
    }
    currentX++;
    for (int i=0;i<vec.size();++i)                              //двигаем вправо
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        area[x][y].setColor(currentColor);
        area[x][y].show();
    }
    this->updateGL();                                           //обновляем картинку
    return true;
}

void
GameArea::rotateCurrentShape()
{
    hideCurrentShape();
    QVector<QPoint> vec(currentShape->rotatedParts());
    bool rotate=true;
    for (int i=0;i<vec.size();++i)                              //двигаем вправо
    {
        int x=currentX+vec.at(i).x();                           //переводим относительные координаты
        int y=currentY+vec.at(i).y();                           //в абсолютные
        if( areaWidth <= x || x < 0 || y > areaHeight - 1 || y < 0 || area.at(x).at(y).isVisible())
        {
            qDebug()<<"Can't rotate";
            rotate = false;
            showCurrentShape();
            return;
        }
    }
    if(rotate)
    {
        currentShape->setParts(vec);
        currentShape->rotateSides();
        int i=0;
        foreach (QPoint points, currentShape->getParts())
        {

            int x=currentX+points.x();
            int y=currentY+points.y();
            area[x][y].setColor(currentColor);
            i++;
        }
        showCurrentShape();
        updateGL();
    }
}

void
GameArea::timerEvent(QTimerEvent *event)
{
    if (pause || gameover)                                          //если пауза или конец игры, то игнорим
    {
        return;
    }
    if (event->timerId()==this->timerId)                            //проверяем, тот ли это таймер
    {
        if (!this->moveCurrentShapeDown())                          //если фигура уперлась
        {
            shapesCount++;
            int topLine=currentY+currentShape->getTop();
            int bottomLine=currentY+currentShape->getBottom();
            int deletedLines=0;
            while (topLine>=bottomLine)
            {
                bool needEraseLine=true;                            //проверяем, нужно ли очистить линию
                for (int i=0;i<areaWidth;++i)
                    needEraseLine=needEraseLine && area.at(i).at(bottomLine).isVisible();

                if (needEraseLine)                                  //если строку нужно очистить
                {
                    qDebug()<<"Очищаем линию";
                    for (int i=0;i<areaWidth;++i)                   //сдвигаем все на 1 клетку вниз
                        for (int j=bottomLine;j<areaHeight-1;++j)
                        {
                            if(area[i][j+1].isVisible())
                            {
                                area[i][j].setColor(area[i][j+1].getColor());
                                area[i][j].show();
                            }
                            else
                                area[i][j].hide();
                        }
                    topLine--;
                    deletedLines++;
                }
                else
                {
                    bottomLine++;
                }
            }
            for (int i=0;i<areaWidth;++i)                           //очищаем deletedLines верхних линий
                for (int j=areaHeight-deletedLines;j<areaHeight;++j)
                    area[i][j].hide();

            switch (deletedLines)                                   //добавление очков
            {
            case 1:
                currentScore+=100;
                break;
            case 2:
                currentScore+=500;
                break;
            case 3:
                currentScore+=1000;
                break;
            case 4:
                currentScore+=1500;
                break;
            }
            emit scoreChanged(currentScore);

            this->initShape();                                      //инициализируем новую фигуру
            this->randomize();                                      //Получаем данные следующей фигуры

            this->upSpeed();                                        //увеличиваем скорость

            this->updateGL();                                       //обновляем картинку
        }
    }
}

void
GameArea::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())                                           //определяем кнопку
    {
    case Qt::Key_R:
        if (event->modifiers() & Qt::ControlModifier)               //если Ctrl+R
            {
                this->start();                                      //перезапускаем игру
                return;
            }
        break;
    case Qt::Key_P:                                                 //если P
        this->switchPause();                                        //переключаем паузу
        return;
    case Qt::Key_D:                                                 //если D
        emit showDifficulty();                                      //открываем окно сложности
        return;
    case Qt::Key_H:                                                 //если H
        emit showHighScores();                                      //открываем окно рекордов
        return;
    }

    if (!pause)                                                     //если не пауза
    {
        switch (event->key())                                       //смотрим кнопку
        {
        case Qt::Key_Up:
            this->rotateCurrentShape();
            break;
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
    }

    this->updateGL();                                               //обновляем картинку
}

void
GameArea::start()
{
    for (int i=0;i<areaWidth;++i)                                   //очищаем игровую область
        for (int j=0;j<areaHeight;++j)
        {
            area[i][j].setColor(Qt::white);
            area[i][j].hide();
        }

    if (this->timerId)                                              //если таймер существует
        this->killTimer(timerId);                                   //убиваем его
    qsrand(QTime::currentTime().msec());
    randomize();                                                    //Получаем цвет и фигуру следующую
    this->initShape();                                              //инициализируем первую фигуру

    shapesCount=0;                                                  //обнуляем кол-во упавших фигур
    currentSpeed=500;                                               //инициализируем скорость падения
    timerId=this->startTimer(currentSpeed);                         //запускаем новый

    currentScore=0;
    emit scoreChanged(currentScore);

    randomize();                                                    //рандомим следующую

    pause=false;                                                    //выключаем паузу
    gameover=false;                                                 //выключаем конец игры

    this->updateGL();                                               //обновляем картинку
}

void
GameArea::switchPause()
{
    if (gameover)                                                   //если конец игры, то игнорируем
    {
        return;
    }

    pause=!pause;                                                   //меняем состояние паузы
    this->updateGL();                                               //обновляем картинку
}
