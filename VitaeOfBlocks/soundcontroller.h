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
#include <QMessageBox>

class SoundController: public QWidget
{
    Q_OBJECT
    QPushButton* button;                                    //кнопка выключения звука
    QSlider* slider;                                        //слайдер громкости
    QMediaPlaylist* playlist;                               //плейлист
    QMediaPlayer* player;                                   //сам плеер

public:
    SoundController(int initVolume=50, bool initMuted=false, QWidget* parent=Q_NULLPTR):QWidget(parent)
    {
        button = new QPushButton;                           //создаем кнопку
        button->setIcon(QIcon(":/res/sound.png"));
        button->setCheckable(true);

        button->setObjectName("Switcher");                  //даем её имя для стиля

        slider = new QSlider(Qt::Horizontal);               //создаем слайдер
        slider->setRange(0,100);
        slider->setValue(initVolume);

        slider->setObjectName("Slider");                    //даем ему имя для стиля

        playlist=new QMediaPlaylist(this);                  //создаем плейлист
        playlist->setPlaybackMode(QMediaPlaylist::Loop);    //говорим ему идти по кругу

        QDir dir=QDir::current();                           //текущая папка
        if (!dir.cd("Sound"))                               //если не можем перейти в Sound
        {
            dir.mkdir("Sound");                             //создаем Sound и выкидываем оповещение
            qApp->beep();
            QMessageBox::warning(this,"Can't find music",
                                 "There is no music found in the Sound folder, so it will not be in the game until you add it there"
                                 "In the original assembly there is a specially selected music.");
        }

        QStringList formats;                                //список форматов
        formats<<"*.mp3"<<"*.wav";
        QStringList list=dir.entryList(formats,QDir::Files);//получаем список всех названий из Sound

        for (int i=0;i<list.size() && i<20;++i)             //идем по списку названий
        {                                                   //добавляем саундтреки в плейлист
            playlist->addMedia(QUrl::fromLocalFile(dir.path()+dir.separator()+list.at(i)));
        }

        player = new QMediaPlayer(this);                    //создаем плеер
        player->setAudioRole(QAudio::GameRole);             //говорим, что это игра
        player->setPlaylist(playlist);                      //устанавливаем плейлист
        player->setVolume(initVolume);                      //устанавливаем громкость

        qsrand(QTime::currentTime().msecsSinceStartOfDay());//инициализируем рандом
        playlist->shuffle();                                //перемешиваем плейлист

        player->play();                                     //запускаем плеер

        QHBoxLayout* lay = new QHBoxLayout;
        lay->addWidget(button,0,Qt::AlignCenter);
        lay->addWidget(slider,0,Qt::AlignCenter);
        this->setLayout(lay);

        connect(button,SIGNAL(toggled(bool)),this,SLOT(setMuted(bool)));
        connect(slider,SIGNAL(valueChanged(int)),player,SLOT(setVolume(int)));

        button->setFocusProxy(this);                        //устанавливаем перенаправление
        slider->setFocusProxy(this);                        //фокуса для кнопок

        this->setMuted(initMuted);                          //инициализируем выключение звука
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
            button->setIcon(QIcon(":/res/soundoff.png"));   //меняем иконку
        }
        else
        {
            button->setIcon(QIcon(":/res/sound.png"));      //меняем иконку
        }
        player->setMuted(a);                                //переключаем звук
    }
};

#endif // SOUNDCONTROLLER_H
