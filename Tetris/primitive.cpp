#include "primitive.h"

Primitive::Primitive():pos(QPoint(0,0)),color(Qt::white),visible(false) {}

Primitive::Primitive(QPoint p, QColor c):pos(p),color(c),visible(false) {}

QColor
Primitive::getColor() const
{
    return color;
}

bool
Primitive::isVisible() const
{
    return visible;
}

QPoint
Primitive::getPos() const
{
    return pos;
}

void
Primitive::setColor(QColor c)
{
    color=c;
}

void
Primitive::show()
{
    visible=true;
}

void
Primitive::hide()
{
    visible=false;
}
