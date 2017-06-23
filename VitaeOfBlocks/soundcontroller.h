#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QApplication>
#include <QDir>
#include <QTime>

class SoundController: public QWidget
{
    Q_OBJECT
    QPushButton* button;
    QSlider* slider;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;

public:
    SoundController(QWidget* parent=Q_NULLPTR):QWidget(parent)
    {
        button = new QPushButton;
        button->setIcon(QIcon(":/res/sound.png"));
        button->setCheckable(true);

        slider = new QSlider(Qt::Horizontal);
        slider->setRange(0,100);
        slider->setValue(50);

        playlist=new QMediaPlaylist(this);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        QDir dir=QDir::current();
        dir.cd("Sound");
        QStringList list=dir.entryList(QDir::Files);

        for (int i=0;i<list.size() && i<20;++i)
        {
            playlist->addMedia(QUrl::fromLocalFile(dir.path()+dir.separator()+list.at(i)));
        }

        player = new QMediaPlayer(this);
        player->setAudioRole(QAudio::GameRole);
        player->setPlaylist(playlist);
        player->setVolume(50);

        qsrand(QTime::currentTime().msecsSinceStartOfDay());
        playlist->shuffle();

        player->play();

        QHBoxLayout* lay = new QHBoxLayout;
        lay->addWidget(button,0,Qt::AlignCenter);
        lay->addWidget(slider,0,Qt::AlignCenter);
        this->setLayout(lay);

        connect(button,SIGNAL(toggled(bool)),this,SLOT(changeIcon(bool)));
        connect(slider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));

        button->setFocusProxy(this);
        slider->setFocusProxy(this);
    }

private slots:
    void changeIcon(bool a)
    {
        if (a)
        {
            button->setIcon(QIcon(":/res/soundoff.png"));
            player->setMuted(a);
        }
        else
        {
            button->setIcon(QIcon(":/res/sound.png"));
            player->setMuted(a);
        }
    }
};

#endif // SOUNDCONTROLLER_H
