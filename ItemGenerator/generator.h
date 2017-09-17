#ifndef GENERTOR_H
#define GENERTOR_H

#include <QtWidgets>
#include "positiveintvalidator.h"

class Generator: public QWidget
{
    Q_OBJECT

    unsigned int nextID;

    QLabel* pathLabel;
    QLineEdit* pathLine;
    QPushButton* browse;

    QLabel* costLabel;
    QLabel* titleLabel;
    QLabel* descriptionLabel;
    QLabel* maxCountLabel;
    QLabel* levelLabel;
    QLabel* rarityLabel;
    QLabel* typeLabel;
    QLabel* attackDamageLabel;
    QLabel* enduranceLabel;
    QLabel* wisdomLabel;
    QLabel* charismaLabel;
    QLabel* intelligenceLabel;
    QLabel* adaptabilityLabel;
    QLabel* nameOfIconLabel;

    QLineEdit* costLine;
    QLineEdit* titleLine;
    QTextEdit* descriptionText;
    QLineEdit* maxCountLine;
    QLineEdit* levelLine;
    QComboBox* rarityBox;
    QComboBox* typeBox;
    QLineEdit* attackDamageLine;
    QLineEdit* enduranceLine;
    QLineEdit* wisdomLine;
    QLineEdit* charismaLine;
    QLineEdit* intelligenceLine;
    QLineEdit* adaptabilityLine;
    QLineEdit* nameOfIconLine;

    PositiveIntValidator* costVal;
    PositiveIntValidator* maxCountVal;
    PositiveIntValidator* levelVal;
    PositiveIntValidator* attackDamageVal;
    QIntValidator* enduranceVal;
    QIntValidator* wisdomVal;
    QIntValidator* charismaVal;
    QIntValidator* intelligenceVal;
    QIntValidator* adaptabilityVal;

    QPushButton* button;

public:
    Generator(QWidget* parent = Q_NULLPTR);

private slots:
    void GetObjectsCount();

    void AppendItem();

    void ChooseFile();
};

#endif // GENERTOR_H
