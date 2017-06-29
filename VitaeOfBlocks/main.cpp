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
    QApplication a(argc, argv);                                             //объект приложения
    a.setOrganizationName("GameTest");                                      //устанавливаем имя
    a.setApplicationName("VitaeOfBlocks");                                  //устанавливаем название

    QFile file(":/res/style.qss");                                          //файл со стилем
    if (!file.open(QFile::ReadOnly))                                        //открываем его
    {
        QMessageBox::warning(Q_NULLPTR,"Error","The built-in file with styles can not be opened.");
        a.exit(1);
    }
    QString str=file.readAll();                                             //читаем все из него
    a.setStyleSheet(str);                                                   //устанавливаем стиль

    qInstallMessageHandler(dummyOutput);                                    //устанавливаем вывод в никуда, чтоб не было грязи

    int screenWidth=QApplication::desktop()->width();                       //получаем ширину экрана

    GameArea * gameArea=new GameArea(screenWidth/45,14,20,10,1);            //создаем объект игровой зоны
    OptionsWindow* options = new OptionsWindow(gameArea,1,screenWidth);     //создаем объект виджета с опциями
    MainWindow * wgt = new MainWindow(gameArea);                            //создвем глваное окно

    QHBoxLayout* hlay = new QHBoxLayout;
    hlay->addWidget(gameArea,0,Qt::AlignRight);
    hlay->addWidget(options,0,Qt::AlignLeft);
    wgt->setLayout(hlay);

    gameArea->setFocus();                                                   //устанавливаем фокус клавиатуры на игровую зону

    wgt->show();                                                            //показываем главный виджет
    gameArea->start();                                                      //запускаем игру

    return a.exec();
}
