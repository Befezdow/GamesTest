#include "gamearea.h"
#include <QTimerEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>
#include <QTime>

void
GameArea::randomize()
{
    nextColor=qrand()%6;
    nextFigure=qrand()%8;
    if (currentShape)           //убираем повторяющиеся подряд фигуры
    {
        if (nextFigure==*currentShape)
            nextFigure=(nextFigure+1)%8;
    }
    qDebug()<<"Срандомил "<<nextColor<<" "<<nextFigure;
    emit throwNextFigure(nextFigure,colors.at(nextColor));
}

void GameArea::setDifficulty(int d)
{
    difficulty=d%5;
}

void GameArea::upSpeed()
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
    currentX=(areaWidth-1)/2;               //задаем X
    currentY=areaHeight-1;                  //задаем Y

    int colorSeed=nextColor;                    //генерируем начальный цвет движ. фигуры
    currentColor=colors.at(colorSeed);          //ставим его

    int shapeSeed=nextFigure;                   //генерируем начальную фигуру
    currentShape=generateShape(shapeSeed);      //ставим её

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
    currentSpeed(500),
    shapesForSpeedUp(numForSpeedUp),
    difficulty(diff%5),
    isPaused(false)

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

    this->setFixedSize(side*width+squareSide/5,side*height+squareSide/7.5);
                                                            //фиксируем размеры окна под игровую область

    connect(this,SIGNAL(gameOver(int)),SLOT(endGame(int))); //соединяем gameover с показом счета
}

GameArea::~GameArea()
{
    delete currentShape;
    QGLWidget::destroy();
    killTimer(timerId);
}

Shape *GameArea::generateShape(int typeOfShape)
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
    qglClearColor(Qt::white);               //задаем цвет фона
}

void
GameArea::resizeGL(int w, int h)
{
    float lineWidth=squareSide/15+1;
    qDebug()<<lineWidth;
    glMatrixMode(GL_PROJECTION);            //начинаем работать с матрицей проекций
    glLoadIdentity();                       //инициализируем её единичной матрицей
    glViewport(0,0,w,h);                    //устанавливаем все окно вьюпортом
    glOrtho(-lineWidth,w-lineWidth,-lineWidth,h-lineWidth,-1,1);                  //устанавливаем начало координат в (0,0)
}

void
GameArea::paintGL()
{
    float lineWidth=squareSide/15;                            //определяем толщину линий

    if (isPaused)                               //если пауза
    {
        QString str="Pause";                    //задаем текст

        qglColor(Qt::black);                    //задаем цвет текста

        QFont font;                             //задаем шрифт
        font.setBold(true);
        font.setPixelSize(squareSide*2);

        QFontMetrics metrics(font);             //определяем положение
        int width=metrics.width(str);
        int height=metrics.height();
        int x=(this->width()-width)/2;
        int y=(this->height()+height)/2;

        renderText(x,y,str,font);               //рисуем текст
                                                //попробовать прикрутить сюда сглаживание!!!
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //очищаем поле

    qglColor(Qt::gray);                                     //ставим серый цвет
    glLineWidth(lineWidth);                                 //ставим ширину линии
    glBegin(GL_LINE_STRIP);                                 //рисуем предельную линию
        glVertex2i(-lineWidth,squareSide*(areaHeight-1));
        glVertex2i(squareSide*(areaWidth)+lineWidth,squareSide*(areaHeight-1));
    glEnd();

    for (int i=0;i<area.size();++i)                         //отрисовываем все поле по клеткам
    {
        for (int j=0;j<area.at(i).size();++j)
        {
            Primitive prim=area.at(i).at(j);                //получаем клетку
            if (prim.isVisible())                           //если её нужно рисовать
            {
                QPoint p=prim.getPos();                     //получаем её координаты
                int x1=p.x();                               //получаем верхний левый угол
                int y1=p.y();
                int x2=x1+squareSide;                       //получаем правый нижний угол
                int y2=y1-squareSide;
                qglColor(prim.getColor());                  //ставим клетке её цвет
                glRecti(x1,y1,x2,y2);                       //рисуем клетку
                qglColor(Qt::black);                        //ставим черный цвет
                glBegin(GL_LINE_LOOP);                      //рисуем обводку
                    glVertex2i(x1,y1);
                    glVertex2i(x1,y2);
                    glVertex2i(x2,y2);
                    glVertex2i(x2,y1);
                glEnd();
            }
        }
    }
    qglColor(Qt::gray);                                     //ставим серый цвет
    glBegin(GL_LINE_STRIP);                                 //рисуем контур
        glVertex2i(-lineWidth,squareSide*areaHeight+lineWidth);
        glVertex2i(-lineWidth,-lineWidth);
        glVertex2i(squareSide*(areaWidth)+lineWidth,-lineWidth);
        glVertex2i(squareSide*(areaWidth)+lineWidth,squareSide*areaHeight+lineWidth);
    glEnd();
}

void GameArea::showCurrentShape()
{
    QVector<QPoint> vec=currentShape->getParts();           //получаем детали фигуры
    for (int i=0;i<vec.size();++i)                          //показываем фигуру
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        area[x][y].show();
    }
}

void GameArea::hideCurrentShape()
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
GameArea::moveCurrentShapeDown()
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
    this->updateGL();                                       //обновляем картинку
    return true;
}

bool
GameArea::moveCurrentShapeLeft()
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
    this->updateGL();                                       //обновляем картинку
    return true;
}

bool
GameArea::moveCurrentShapeRight()
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
    this->updateGL();                                       //обновляем картинку
    return true;
}

void
GameArea::rotateCurrentShape()
{
    hideCurrentShape();
    QVector<QPoint> vec(currentShape->rotatedParts());
    bool rotate=true;
    for (int i=0;i<vec.size();++i)                          //двигаем вправо
    {
        int x=currentX+vec.at(i).x();                       //переводим относительные координаты
        int y=currentY+vec.at(i).y();                       //в абсолютные
        if( areaWidth <= x || x < 0 || y > areaHeight - 1 || y < 0 || area.at(x).at(y).isVisible())
        {
            qDebug()<<"Нельзя повернуть";
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
    if (isPaused)                                                   //если пауза, то игнорим
        return;
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
            for (int i=0;i<areaWidth;++i)                   //очищаем deletedLines верхних линий
                for (int j=areaHeight-deletedLines;j<areaHeight;++j)
                    area[i][j].hide();

            switch (deletedLines)                           //добавление очков
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

            this->initShape();              //инициализируем новую фигуру
            this->randomize();                    //Получаем данные следующей фигуры

            this->upSpeed();

            this->updateGL();               //обновляем картинку
        }
    }
}

void
GameArea::keyPressEvent(QKeyEvent *event)
{
    if (isPaused)                                               //если пауза то игнорим
        return;
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

    this->updateGL();                                           //обновляем картинку
}

void
GameArea::start()
{
    for (int i=0;i<areaWidth;++i)           //очищаем игровую область
        for (int j=0;j<areaHeight;++j)
        {
            area[i][j].setColor(Qt::white);
            area[i][j].hide();
        }

    if (this->timerId)                 //если таймер существует
        this->killTimer(timerId);      //убиваем его
    qsrand(QTime::currentTime().msec());
    randomize();                       //Получаем цвет и фигуру следующую
    this->initShape();                 //инициализируем первую фигуру

    shapesCount=0;                              //обнуляем кол-во упавших фигур
    currentSpeed=500;                           //инициализируем скорость падения
    timerId=this->startTimer(currentSpeed);     //запускаем новый

    currentScore=0;
    emit scoreChanged(currentScore);

    randomize();                       //Рандомим следующую

    isPaused=false;

    this->updateGL();
}

void
GameArea::endGame(int score)
{
    QString info="Your score: "+QString::number(score)+"\n Play more?";
    int i=QMessageBox::information(this,"Game Over",info,QMessageBox::Yes,QMessageBox::No);

    if (i==QMessageBox::Yes)                    //если хочет играть еще
    {
        this->start();
    }
    else                                        //если не хочет
        qApp->quit();
}

void GameArea::switchPause()
{
    isPaused=!isPaused;
    this->updateGL();
}
