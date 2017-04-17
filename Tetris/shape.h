#ifndef SHAPE_H
#define SHAPE_H

#include <QtWidgets>

class Shape                 //базовый класс всех фигур
{
protected:
    int height;             //высота фигуры
    int width;              //ширина фигуры
    QVector<QPoint> parts;  //координаты верхних левых углов квадратов, из которых состоит фигура
    bool rotation;          //возможность поворота фигуры

    Shape() {}              //хотел абстрактный класс
public:
    QVector<QPoint> rotateShape()
    {
        if(!this->canRotate())
            return this->parts;
        else
        {
            QVector<QPoint> rotatedPoints;
            foreach (QPoint point, this->parts)
            {
                QPoint rPoint; //Повернутая точка
                rPoint.setX(-point.y());
                rPoint.setY(point.x());
                rotatedPoints.push_back(rPoint);
            }
            return rotatedPoints;
        }
    }

    enum {Square,LittleSquare,Stick,TShape,ZShape,SShape,JShape,LShape};

    int getHeight() const
    {
        return height;
    }
    int getWidth() const
    {
        return width;
    }
    void setParts(QVector<QPoint> parts)
    {
        this->parts=parts;
    }

    QVector<QPoint> getParts() const
    {
        return parts;
    }
    bool canRotate() const
    {
        return rotation;
    }
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
    Square()
    {
        height=2;
        width=2;
        rotation=false;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(-1,-1));
        parts.push_back(QPoint(0,-1));
    }
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
    LittleSquare()
    {
        height=1;
        width=1;
        rotation=false;
        parts.push_back(QPoint(0,0));
    }
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
       height=3;
       width=3;
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
    Stick()
    {
        height=1;
        width=4;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(2,0));
        parts.push_back(QPoint(-1,0));
    }
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
    TShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(0,-1));
        parts.push_back(QPoint(1,0));
    }
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
    ZShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(0,-1));
        parts.push_back(QPoint(1,-1));
    }
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
    SShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(0,-1));
        parts.push_back(QPoint(-1,-1));
    }
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
    JShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(1,-1));
    }
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
    LShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(-1,-1));
    }
};

#endif // SHAPE_H
