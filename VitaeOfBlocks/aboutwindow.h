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
        name->setText("<h1>Vitae Of Blocks</h1><h3>Version 1.3</h3>");
        name->setAlignment(Qt::AlignCenter);

        description = new QLabel;
        description->setTextFormat(Qt::RichText);
        description->setAlignment(Qt::AlignCenter);
        description->setText("This program was written by a couple of<br>"
                             "students in order to test their abilities.<br>"
                             "It uses Qt version 5.8.0.");

        developers = new QLabel;
        developers->setTextFormat(Qt::RichText);
        developers->setText("<b>Developers:</b><br>#Befezdow<br>#YouCanKeepSilence");
        developers->setAlignment(Qt::AlignCenter);

        thanks = new QLabel;
        thanks->setTextFormat(Qt::RichText);
        thanks->setAlignment(Qt::AlignHCenter);
        thanks->setText("<b>Special thanks to:</b><br>#Kampfer<br>#Forze<br>"
                        "#Altum Silentium<br>#Lieee.s<br>#DuMaHbl4");

        music = new QLabel;
        music->setTextFormat(Qt::RichText);
        music->setAlignment(Qt::AlignHCenter);
        music->setText("<b>Music:</b><br>"
                       "KFAlisKA - Живой Сталкер (8 bit)<br>"
                       "KFRock And KFAliska - My Life<br>"
                       "KFAlisKA - IcyNitro (8 bit)<br>"
                       "Roboctopus - Slow Motion Sunset<br>"
                       "Snork25 - Longboard<br>"
                       "Balloonbear - Forever Online<br>");

        developers->setObjectName("l1");                //устанавливаем именя для файла со стилем
        thanks->setObjectName("l1");
        music->setObjectName("l1");
        description->setObjectName("l2");

        ok=new QPushButton("Ok");

        QGridLayout* lay=new QGridLayout;
        lay->addWidget(image,0,0,1,1,Qt::AlignHCenter);
        lay->addWidget(name,0,1,1,1,Qt::AlignHCenter);
        lay->addWidget(description,1,0,1,2,Qt::AlignHCenter);
        lay->addWidget(developers,2,0,1,2,Qt::AlignHCenter);
        lay->addWidget(thanks,3,0,1,1,Qt::AlignHCenter);
        lay->addWidget(music,3,1,1,1,Qt::AlignHCenter);
        lay->addWidget(ok,4,0,2,2,Qt::AlignHCenter);

        this->setLayout(lay);
        this->setFixedSize(this->minimumSize());
        this->setObjectName("About");                   //устанавливаем имя для стиля

        connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
    }
};

#endif // ABOUTWINDOW_H
