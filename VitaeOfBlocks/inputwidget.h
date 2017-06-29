#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QIcon>
#include <QGridLayout>
#include <QString>

class InputWidget:public QDialog
{
    Q_OBJECT
    QLabel* lbl;
    QLineEdit* edit;
    QPushButton* ok;
    QPushButton* cancel;

public:
    InputWidget(QWidget* parent=Q_NULLPTR):QDialog(parent)
    {
        this->setWindowTitle("Excellent!");
        this->setWindowIcon(QIcon(":/res/icon.png"));

        lbl=new QLabel("You have entered the highscore table.\nPlease enter your nickname:");
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setObjectName("l1");

        edit=new QLineEdit("Player");
        edit->setMaxLength(30);
        edit->setObjectName("InputEdit");

        ok=new QPushButton("Ok");
        cancel=new QPushButton("Cancel");

        QGridLayout* lay=new QGridLayout;
        lay->addWidget(lbl,0,0,1,2,Qt::AlignHCenter);
        lay->addWidget(edit,1,0,1,2,Qt::AlignHCenter);
        lay->addWidget(cancel,2,0,1,1,Qt::AlignHCenter);
        lay->addWidget(ok,2,1,1,1,Qt::AlignHCenter);
        this->setLayout(lay);

        this->setFixedSize(this->minimumSize());
        this->setObjectName("Input");

        connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
        connect(cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
        connect(edit,SIGNAL(returnPressed()),this,SLOT(accept()));
    }

    QString getText()
    {
        return edit->text();
    }
};

#endif // INPUTWIDGET_H
