#include "shape.h"

QVector<QPoint>
Shape::rotatedParts()
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

int
Shape::getTop() const
{
    return top;
}

int
Shape::getBottom() const
{
    return bottom;
}

void
Shape::rotateSides()
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

void
Shape::setParts(QVector<QPoint> parts)
{
    this->parts=parts;
}

QVector<QPoint>
Shape::getParts() const
{
    return parts;
}

bool
Shape::canRotate() const
{
    return rotation;
}
