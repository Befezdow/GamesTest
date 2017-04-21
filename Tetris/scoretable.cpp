#include "scoretable.h"

Scoretable::Scoretable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vertical=new QVBoxLayout();
    figure=new GLWidget(10,4,4,parent);
    scores= new QLabel("Hello "+QString::number(0));
    vertical->addWidget(figure);
    vertical->addWidget(scores);
    this->setFixedWidth(100);
    this->setFixedHeight(100);
    this->setLayout(vertical);
}
