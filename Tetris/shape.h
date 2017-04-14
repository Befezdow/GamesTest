#ifndef SHAPE_H
#define SHAPE_H

#include <QtWidgets>

class Shape
{
<<<<<<< HEAD
protected:
=======
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066
    int height;
    int width;
    QVector<QPoint> parts;
    bool rotation;
public:
    virtual ~Shape()=0;
    int getHeight() const
    {
        return height;
    }
    int getWidth() const
    {
        return width;
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

<<<<<<< HEAD
class Square : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 1 1 0 0
        0 1 1 0 0
        0 0 0 0 0
    */
=======
class Square:public Shape
{
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066
public:
    Square()
    {
        height=2;
        width=2;
        rotation=false;
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(-1,0));
        parts.push_back(QPoint(0,0));
    }
};

<<<<<<< HEAD
class LittleSquare : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        0 0 1 0 0
        0 0 0 0 0
        0 0 0 0 0
    */
=======
class LittleSquare:public Shape
{
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066
public:
    LittleSquare()
    {
        height=1;
        width=1;
        rotation=false;
        parts.push_back(QPoint(0,1));
    }
};

<<<<<<< HEAD
/*class BigSquare : public Shape
{
//
//        0 0 0 0 0
//        0 1 1 1 0
//        0 1 1 1 0
//        0 1 1 1 0
//        0 0 0 0 0
//
=======
class BigSquare:public Shape
{
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066
public:
    BigSquare()
    {
       height=3;
       width=3;
       rotation=false;
       parts.push_back(QPoint(0,1));
       parts.push_back(QPoint(0,2));
       parts.push_back(QPoint(-1,2));
       parts.push_back(QPoint(-1,1));
       parts.push_back(QPoint(-1,0));
       parts.push_back(QPoint(0,0));
       parts.push_back(QPoint(1,0));
       parts.push_back(QPoint(1,1));
       parts.push_back(QPoint(1,2));
    }
<<<<<<< HEAD
};*/

class Stick : public Shape
{
    /*
        0 0 0 0 0
        0 0 0 0 0
        1 1 1 1 0
        0 0 0 0 0
        0 0 0 0 0
    */
=======
};

class Stick:public Shape
{
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066
public:
    Stick()
    {
        height=1;
        width=4;
        rotation=true;
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(1,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(-2,1));
    }
};

<<<<<<< HEAD
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
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(0,0));
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
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(1,0));
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
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(1,1));
        parts.push_back(QPoint(0,0));
        parts.push_back(QPoint(-1,0));
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
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(1,1));
        parts.push_back(QPoint(1,0));
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
    LShape()
    {
        height=2;
        width=3;
        rotation=true;
        parts.push_back(QPoint(0,1));
        parts.push_back(QPoint(-1,1));
        parts.push_back(QPoint(1,1));
        parts.push_back(QPoint(-1,0));
    }
};
=======
class
>>>>>>> 0439562b79dfdfe7f819caf99607f75e8b77a066

#endif // SHAPE_H
