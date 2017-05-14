#include "difficultywindow.h"

DifficultyWindow::DifficultyWindow(int initDiff, QWidget *parent):
    QDialog(parent)
{
    mapper=new QSignalMapper(this);

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(changeResult(int)));

    difficulties[0]=new QRadioButton("Free");
    difficulties[1]=new QRadioButton("Easy");
    difficulties[2]=new QRadioButton("Normal");
    difficulties[3]=new QRadioButton("Hard");
    difficulties[4]=new QRadioButton("Master");

    mapper->setMapping(difficulties[0],0);
    mapper->setMapping(difficulties[1],1);
    mapper->setMapping(difficulties[2],2);
    mapper->setMapping(difficulties[3],3);
    mapper->setMapping(difficulties[4],4);

    connect(difficulties[0],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[1],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[2],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[3],SIGNAL(clicked(bool)),mapper,SLOT(map()));
    connect(difficulties[4],SIGNAL(clicked(bool)),mapper,SLOT(map()));

    group=new QGroupBox("Game difficulty:");
    radioLay=new QVBoxLayout;

    radioLay->addWidget(difficulties[0]);
    radioLay->addWidget(difficulties[1]);
    radioLay->addWidget(difficulties[2]);
    radioLay->addWidget(difficulties[3]);
    radioLay->addWidget(difficulties[4]);

    group->setLayout(radioLay);

    difficulties[initDiff % 5]->setChecked(true);

    label=new QLabel("*The game will start again\nafter changing the difficulty.");
    ok=new QPushButton("Accept");
    cancel=new QPushButton("Cancel");

    hLay=new QHBoxLayout;
    hLay->addWidget(cancel);
    hLay->addWidget(ok);

    vLay=new QVBoxLayout;
    vLay->addWidget(group);
    vLay->addWidget(label);
    vLay->addLayout(hLay);
    this->setLayout(vLay);

    connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

    this->setWindowTitle("Changing of difficulty");
    this->setModal(true);
}

int DifficultyWindow::getCurrentDifficulty() const
{
    return currentDifficulty;
}

void DifficultyWindow::changeResult(int i)
{
    currentDifficulty=i;
}
