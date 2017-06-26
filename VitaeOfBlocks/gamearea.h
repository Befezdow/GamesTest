#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "shape.h"
#include "primitive.h"
#include <QGLWidget>
#include <QDebug>

class GameArea: public QGLWidget
{
    Q_OBJECT
    QVector<QVector<Primitive>> area;  //само игровое поле
    int squareSide;             //сторона примитивного квадрата

    int areaWidth;              //ширина поля в этих квадратах
    int areaHeight;             //высота поля в этих квадратах

    Shape* currentShape;        //текущая фигура
    int currentX;               //текущее положение по X движущейся фигуры
    int currentY;               //текущее положение по Y движущейся фигуры

    int timerId;                //id таймера для обработки автоспуска

    int currentScore;           //текущий счет игрока

    int nextFigure;             //тип следующей фигуры
    int nextColor;              //цвет следующей фигуры

    QVector<QColor> colors;     //цвета фигур
    QColor currentColor;        //цвет движущейся фигуры

    int shapesCount;            //счетчик упавших фигур
    int currentSpeed;           //кол-во милисекунд между перемещениями вниз
    int shapesForSpeedUp;       //кол-во упавших фигур для начала увеличения скорости
    int difficulty;             //сложность (0,1,2,3,4)

    bool pause;
    bool gameover;

    GLuint textureID[3];

    void initShape();               //инициализирует новую фигуру
    void rotateCurrentShape();      //текущую фигуру, если это возможно
    void showCurrentShape();        //показать текущую фигуру
    void hideCurrentShape();        //скрыть текущую фигуру
    bool moveCurrentShapeDown();    //переместить текущую фигуру на одну клетку вниз
    bool moveCurrentShapeLeft();    //переместить текущую фигуру на одну клетку влево
    bool moveCurrentShapeRight();   //переместить текущую фигуру на одну клетку вправо
    void randomize();               //сгенерировать следующую фигуру
    void upSpeed();                 //увеличить скорость

public:
    GameArea(int side, int width, int height, int numForSpeedUp=10, int diff=1, QWidget* parent=Q_NULLPTR);
    ~GameArea();

    static Shape* generateShape(int typeOfShape);       //генерирует объект фигуры
    void setDifficulty(int d);          //установить сложность
    bool isPaused() const;
    bool isGameOver() const;
    void setGameOver();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void start();                       //запустить игру (запуск таймера)
    void switchPause();

signals:
    void throwNextFigure(int, QColor);
    void scoreChanged(unsigned int);    //сигнал изменения счета
    void gameOver(unsigned int);        //сигнал проигрыша
    void showHighScores();              //сигнал для вызова окна рекордов через key event
    void showDifficulty();              //сигнал для вызова окна сложности через key event
};

#endif // GLWIDGET_H
