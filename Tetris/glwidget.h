#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtWidgets>
#include "shape.h"
#include "primitive.h"

class GLWidget: public QGLWidget
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

    int nextFigure;
    int nextColor;

    QVector<QColor> colors;     //цвета фигур
    QColor currentColor;        //цвет движущейся фигуры

    void initShape();
    void rotateCurrentShape();
    void showCurrentShape();
    void hideCurrentShape();
    bool moveCurrentShapeDown();
    bool moveCurrentShapeLeft();
    bool moveCurrentShapeRight();
    void randomize();
public:
    GLWidget(int side,int width,int height,QWidget* parent=Q_NULLPTR);
protected:
    virtual void initializeGL();

    virtual void resizeGL(int w, int h);

    virtual void paintGL();

    virtual void timerEvent(QTimerEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void start();               //запустить игру (запуск таймера)

    void endGame(int score);    //завершить игру и вывести счет
signals:
    void scoreChanged(int);
    void gameOver(int);         //сигнал проигрыша
};

#endif // GLWIDGET_H
