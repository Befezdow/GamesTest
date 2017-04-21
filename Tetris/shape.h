#ifndef SHAPE_H
#define SHAPE_H

#include <QtWidgets>



class Shape                 //базовый класс всех фигур
{
protected:
    int top;                //верхняя точка фигуры (наибольший y)
    int bottom;             //нижняя точка фигуры (наименьший y)
    int left;               //самая левая точка фигуры (наименьший x)
    int right;              //самая правая точка фигуры (наибольший x)
    QVector<QPoint> parts;  //координаты верхних левых углов квадратов, из которых состоит фигура
    bool rotation;          //возможность поворота фигуры

    Shape() {}              //хотел абстрактный класс
public:

    QVector<QPoint> rotatedParts()          //возвращает относительные координаты повернутых частей
    {
        if(!this->canRotate())              //если нельзя поворачивать
            return this->parts;
        else                                //если можно
        {
            QVector<QPoint> rotatedPoints;  //новые координаты повернутых частей
            foreach (QPoint point, this->parts)
            {
                QPoint rPoint;              //Повернутая точка
                rPoint.setX(-point.y());    //поставили новый x
                rPoint.setY(point.x());     //поставили новый y
                rotatedPoints.push_back(rPoint);
            }
            return rotatedPoints;
        }
    }

    enum {Square,LittleSquare,Stick,TShape,ZShape,SShape,JShape,LShape};

    int getTop() const
    {
        return top;
    }

    int getBottom() const
    {
        return bottom;
    }

    void rotateSides()                      //поворачивает стороны l,r,t,b, если это возможно
    {
        if (!rotation)                      //если нельзя поворачивать
            return;
        int tempT=top;                      //запоминаем исходные
        int tempB=bottom;
        int tempL=left;
        int tempR=right;
        ////////////
        qDebug()<<"   "<<top;
        qDebug()<<left<<"     "<<right;
        qDebug()<<"   "<<bottom;
        ////////////
        top=tempR;                      //поворачиваем
        right=-tempB;
        bottom=tempL;
        left=-tempT;
        ////////////
        qDebug()<<"Стало:";
        qDebug()<<"   "<<top;
        qDebug()<<left<<"     "<<right;
        qDebug()<<"   "<<bottom;
        ////////////
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
        top=0;
        bottom=-1;
        left=-1;
        right=0;
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
        top=0;
        bottom=0;
        left=0;
        right=0;
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
    Stick()
    {
        top=0;
        bottom=0;
        left=-1;
        right=2;
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
        top=0;
        bottom=-1;
        left=-1;
        right=1;
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
        top=0;
        bottom=-1;
        left=-1;
        right=1;
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
        top=0;
        bottom=-1;
        left=-1;
        right=1;
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
        top=0;
        bottom=-1;
        left=-1;
        right=1;
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
        top=0;
        bottom=-1;
        left=-1;
        right=1;
        rotation=true;
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(1,0));
        parts.push_back(QPoint(-1,-1));
    }
};

#endif // SHAPE_H
