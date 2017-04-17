#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QtWidgets>

class Primitive
{
    QPoint pos;
    QColor color;
    bool visible;
public:
    Primitive():pos(QPoint(0,0)),color(Qt::white),visible(false) {}
    Primitive(QPoint p,QColor c):pos(p),color(c),visible(false) {}

    QColor getColor() const
    {
        return color;
    }

    bool isVisible() const
    {
        return visible;
    }

    QPoint getPos() const
    {
        return pos;
    }

    void setColor(QColor c)
    {
        color=c;
    }

    void show()
    {
        visible=true;
    }

    void hide()
    {
        visible=false;
    }
};

#endif // PRIMITIVE_H
