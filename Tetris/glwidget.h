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
    //в этот вектор нужно засунуть еще цвет каждого блока, ибо хочется красок

    int squareSide;             //сторона примитивного квадрата

    int areaWidth;              //ширина поля в этих квадратах
    int areaHeight;             //высота поля в этих квадратах

    int currentX;               //текущее положение по X движущейся фигуры
    int currentY;               //текущее положение по Y движущейся фигуры

    int timerId;                //id таймера для обработки автоспуска

    int currentScore;           //текущий счет игрока

    QVector<QColor> colors;     //цвета фигур
    QColor currentColor;        //цвет движущейся фигуры
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
    void gameOver(int);         //сигнал проигрыша
};

#endif // GLWIDGET_H
