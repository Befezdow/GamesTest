#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class AboutWindow: public QDialog
{
    QLabel* image;
    QLabel* name;
    QLabel* description;
    QLabel* developers;
    QLabel* thanks;
    QLabel* music;
    QPushButton* ok;

public:
    AboutWindow(QWidget* parent=Q_NULLPTR):QDialog(parent)
    {
        image = new QLabel;
        image->setPixmap(QPixmap(":/res/icon.png"));

        name = new QLabel;
        name->setTextFormat(Qt::RichText);
        name->setText("<h2>Vitae Of Blocks</h2><h4>Version 1.3</h4>");
        name->setAlignment(Qt::AlignCenter);

        description = new QLabel;
        description->setTextFormat(Qt::RichText);
        description->setText("This program was written by a couple of<br>"
                             "students in order to test their abilities.<br>"
                             "It uses Qt version 5.8.0.");
        description->setAlignment(Qt::AlignCenter);

        developers = new QLabel;
        developers->setTextFormat(Qt::RichText);
        developers->setText("<b>Developers:</b><br>#Befezdow<br>#YouCanKeepSilence");
        developers->setAlignment(Qt::AlignCenter);

        thanks = new QLabel;
        thanks->setTextFormat(Qt::RichText);
        thanks->setText("<b>Special thanks to:</b><br>#Kampfer<br>#Forze<br>"
                        "#Altum Silentium<br>#Lieee.s<br>#DuMaHbl4");
        thanks->setAlignment(Qt::AlignCenter);

        music = new QLabel;
        music->setTextFormat(Qt::RichText);
        music->setText("<b>Music:</b><br>");
        music->setAlignment(Qt::AlignCenter);

        ok=new QPushButton("Ok");

        QGridLayout* lay=new QGridLayout;
        lay->addWidget(image,0,0,1,1,Qt::AlignHCenter);
        lay->addWidget(name,0,1,1,1,Qt::AlignHCenter);
        lay->addWidget(description,1,0,1,2,Qt::AlignHCenter);
        lay->addWidget(developers,2,0,1,2,Qt::AlignHCenter);
        lay->addWidget(thanks,3,0,1,1,Qt::AlignHCenter);
        lay->addWidget(music,3,1,1,1,Qt::AlignHCenter);
        lay->addWidget(ok,4,0,2,2);

        this->setLayout(lay);

        connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

        this->setFixedSize(this->minimumSize());
    }
};

#endif // ABOUTWINDOW_H
