#include "difficultywindow.h"

DifficultyWindow::DifficultyWindow(int initDiff, QWidget *parent):
    QDialog(parent)
{
    mapper=new QSignalMapper(this);

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(changeResult(int)));   //соединяем маппер со слотом изменения выбранной сложности

    difficulties[0]=new QRadioButton("Free");
    difficulties[1]=new QRadioButton("Easy");
    difficulties[2]=new QRadioButton("Normal");
    difficulties[3]=new QRadioButton("Hard");
    difficulties[4]=new QRadioButton("Master");

    difficulties[0]->setObjectName("r1");
    difficulties[1]->setObjectName("r1");
    difficulties[2]->setObjectName("r1");
    difficulties[3]->setObjectName("r1");
    difficulties[4]->setObjectName("r1");

    mapper->setMapping(difficulties[0],0);                              //ассоциируем кнопки с уровнями сложности
    mapper->setMapping(difficulties[1],1);
    mapper->setMapping(difficulties[2],2);
    mapper->setMapping(difficulties[3],3);
    mapper->setMapping(difficulties[4],4);

    connect(difficulties[0],SIGNAL(clicked(bool)),mapper,SLOT(map()));  //соедиянем кнопки с маппером
    connect(difficulties[1],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[2],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[3],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[4],SIGNAL(clicked(bool)),mapper,SLOT(map()));

    group=new QGroupBox("Game difficulty:");
    group->setObjectName("g1");
    radioLay=new QVBoxLayout;

    radioLay->addWidget(difficulties[0],0,Qt::AlignHCenter);
    radioLay->addWidget(difficulties[1],0,Qt::AlignHCenter);
    radioLay->addWidget(difficulties[2],0,Qt::AlignHCenter);
    radioLay->addWidget(difficulties[3],0,Qt::AlignHCenter);
    radioLay->addWidget(difficulties[4],0,Qt::AlignHCenter);

    group->setLayout(radioLay);

    difficulties[initDiff % 5]->setChecked(true);

    label=new QLabel("*The game will restart\nafter changing the difficulty.");
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName("l2");

    ok=new QPushButton("Accept");
    cancel=new QPushButton("Cancel");

    hLay=new QHBoxLayout;
    hLay->addWidget(cancel,0,Qt::AlignRight);
    hLay->addWidget(ok,0,Qt::AlignLeft);

    vLay=new QVBoxLayout;
    vLay->addWidget(group,0,Qt::AlignHCenter);
    vLay->addWidget(label,0,Qt::AlignHCenter);
    vLay->addLayout(hLay);
    this->setLayout(vLay);

    connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setWindowTitle("Changing of difficulty");
    this->setModal(true);
    this->setObjectName("DiffWindow");
}

int DifficultyWindow::getCurrentDifficulty() const
{
    return currentDifficulty;
}

void DifficultyWindow::changeResult(int i)
{
    currentDifficulty=i;
}
