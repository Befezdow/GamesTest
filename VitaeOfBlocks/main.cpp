#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include "optionswindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QIcon>

void dummyOutput(QtMsgType, const QMessageLogContext&, const QString&)
{}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("GameTest");
    a.setApplicationName("VitaeOfBlocks");

    QFile file(":/res/style.qss");
    file.open(QFile::ReadOnly);
    QString str=file.readAll();
    a.setStyleSheet(str);

    qInstallMessageHandler(dummyOutput);

    int screenWidth=QApplication::desktop()->width();

    GameArea * gameArea=new GameArea(screenWidth/45,14,20,10,1);
    OptionsWindow* options = new OptionsWindow(gameArea,1,screenWidth);
    MainWindow * wgt = new MainWindow(gameArea);
    QHBoxLayout* hlay = new QHBoxLayout;

    hlay->addWidget(gameArea,0,Qt::AlignRight);
    hlay->addWidget(options,0,Qt::AlignLeft);
    wgt->setLayout(hlay);

    gameArea->setFocus();

    wgt->setWindowTitle("Vitae Of Blocks");
    wgt->setWindowIcon(QIcon(":/res/icon.png"));

    wgt->show();
    gameArea->start();

    return a.exec();
}
