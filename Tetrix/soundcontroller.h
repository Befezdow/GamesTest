#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>

class SoundController: public QWidget
{
    Q_OBJECT
    QPushButton* button;
    QSlider* slider;
//    QMediaPlayer* player;

public:
    SoundController(QWidget* parent=Q_NULLPTR):QWidget(parent)
    {
        button=new QPushButton;
        button->setIcon(QIcon(":/res/sound.png"));
        button->setCheckable(true);
        slider=new QSlider(Qt::Horizontal);
        slider->setRange(0,100);
        slider->setValue(50);

        QHBoxLayout* lay=new QHBoxLayout;
        lay->addWidget(button,0,Qt::AlignCenter);
        lay->addWidget(slider,0,Qt::AlignCenter);
        this->setLayout(lay);

        connect(button,SIGNAL(toggled(bool)),this,SLOT(changeIcon(bool)));
//        connect(slider,SIGNAL(valueChanged(int)),player,SIGNAL(changeVolume()));

        button->setFocusProxy(this);
        slider->setFocusProxy(this);
    }

private slots:
    void changeIcon(bool a)
    {
        if (a)
        {
            button->setIcon(QIcon(":/res/soundoff.png"));
            //выключить звук в плееер;
        }
        else
        {
            button->setIcon(QIcon(":/res/sound.png"));
            //включить звук в плееере
        }
    }
};

#endif // SOUNDCONTROLLER_H
