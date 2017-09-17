#ifndef POSITIVEINTVALIDATOR_H
#define POSITIVEINTVALIDATOR_H

#include <QtWidgets>

class PositiveIntValidator: public QValidator
{
public:
    PositiveIntValidator(QObject* parent = Q_NULLPTR): QValidator(parent)
    {}

protected:
    virtual State validate(QString & str, int &num) const
    {
        if (num == 0 || str.at(num-1).isNumber())
        {
            return Acceptable;
        }
        else
        {
            return Invalid;
        }
    }
};

#endif // POSITIVEINTVALIDATOR_H
