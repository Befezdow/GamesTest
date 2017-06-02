#include "gamearea.h"
#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include "optionswindow.h"
#include <QApplication>
#include <QMessageLogContext>
#include <QString>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>

void dummyOutput(QtMsgType, const QMessageLogContext&, const QString&)
{}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qInstallMessageHandler(dummyOutput);

    int screenWidth=QApplication::desktop()->width();

    GameArea * gameArea=new GameArea(screenWidth/45,14,20,10,1);
    OptionsWindow* options=new OptionsWindow(gameArea,1,screenWidth);
    QWidget * wgt = new QWidget;
    QHBoxLayout* hlay = new QHBoxLayout;

    hlay->addWidget(gameArea,0,Qt::AlignCenter);
    hlay->addWidget(options);
    wgt->setLayout(hlay);

    gameArea->setFocus();

    wgt->setWindowTitle("Tetrix");
    wgt->setWindowIcon(QIcon(":/res/icon.png"));
    wgt->show();
    gameArea->start();

    return a.exec();
}
