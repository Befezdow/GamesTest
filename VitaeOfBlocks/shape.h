#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
class QPoint;

class Shape                 //базовый класс всех фигур
{
protected:
    int top;                //верхняя точка фигуры (наибольший y)
    int bottom;             //нижняя точка фигуры (наименьший y)
    int left;               //самая левая точка фигуры (наименьший x)
    int right;              //самая правая точка фигуры (наибольший x)
    QVector<QPoint> parts;  //координаты верхних левых углов квадратов, из которых состоит фигура
    bool rotation;          //возможность поворота фигуры

public:
    virtual operator int() const =0;    //это абстрактный класс
    virtual ~Shape();

    enum {Square,LittleSquare,Stick,TShape,ZShape,SShape,JShape,LShape};

    QVector<QPoint> rotatedParts();         //возвращает относительные координаты повернутых частей
    int getTop() const;
    int getBottom() const;
    int getLeft() const;
    int getRight() const;
    void rotateSides();                     //поворачивает стороны l,r,t,b, если это возможно
    void setParts(QVector<QPoint> parts);
    QVector<QPoint> getParts() const;
    bool canRotate() const;
};

class Square : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
    */
public:
    Square();
    virtual operator int() const;
};

class LittleSquare : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 0 1 0 0
        0 0 0 0 0
        0 0 0 0 0
    */
public:
    LittleSquare();
    virtual operator int() const;
};

/*class BigSquare : public Shape
{
//
//        0 0 0 0 0
//        0 1 1 1 0
//        0 1 1 1 0
//        0 1 1 1 0
//        0 0 0 0 0
//
public:
    BigSquare()
    {
        top=1;
        bottom=-1;
        left=-1;
        right=1;
        rotation=false;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(-1,-1));
        parts.push_back(QPoint(0,-1));
        parts.push_back(QPoint(1,-1));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(1,1));
    }
};*/

class Stick : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 1
        0 0 0 0 0
        0 0 0 0 0
    */
public:
    Stick();
    virtual operator int() const;
};

class TShape : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 0 1 0 0
        0 0 0 0 0
    */
public:
    TShape();
    virtual operator int() const;
};

class ZShape : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 0 0
        0 0 1 1 0
        0 0 0 0 0
    */
public:
    ZShape();
    virtual operator int() const;
};

class SShape : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 0 1 1 0
        0 1 1 0 0
        0 0 0 0 0
    */
public:
    SShape();
    virtual operator int() const;
};

class JShape : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 0 0 1 0
        0 0 0 0 0
    */
public:
    JShape();
    virtual operator int() const;
};

class LShape : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 1 0
        0 1 0 0 0
        0 0 0 0 0
    */
public:
    LShape();
    virtual operator int() const;
};

#endif // SHAPE_H
