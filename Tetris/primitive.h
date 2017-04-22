#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QPoint>
#include <QColor>

class Primitive
{
    QPoint pos;         //координаты клетки
    QColor color;       //цвет клетки
    bool visible;       //видимость клетки
public:
    Primitive();
    Primitive(QPoint p,QColor c);

    QColor getColor() const;
    bool isVisible() const;
    QPoint getPos() const;
    void setColor(QColor c);
    void show();
    void hide();
};

#endif // PRIMITIVE_H
