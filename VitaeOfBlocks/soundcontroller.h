#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
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
    SoundController(int initVolume=50, bool initMuted=false, QWidget* parent=Q_NULLPTR):QWidget(parent)
    {
        button = new QPushButton;
        button->setIcon(QIcon(":/res/sound.png"));
        button->setCheckable(true);

        slider = new QSlider(Qt::Horizontal);
        slider->setRange(0,100);
        slider->setValue(initVolume);

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
        player->setVolume(initVolume);

        qsrand(QTime::currentTime().msecsSinceStartOfDay());
        playlist->shuffle();

        player->play();

        QHBoxLayout* lay = new QHBoxLayout;
        lay->addWidget(button,0,Qt::AlignCenter);
        lay->addWidget(slider,0,Qt::AlignCenter);
        this->setLayout(lay);

        connect(button,SIGNAL(toggled(bool)),this,SLOT(setMuted(bool)));
        connect(slider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));

        button->setFocusProxy(this);
        slider->setFocusProxy(this);

        this->setMuted(initMuted);
    }

    int getVolume() const
    {
        return player->volume();
    }

    bool isMuted() const
    {
        return player->isMuted();
    }

private slots:
    void setMuted(bool a)
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
