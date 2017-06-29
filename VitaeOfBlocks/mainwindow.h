#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamearea.h"
#include <QCloseEvent>

class MainWindow: public QWidget
{
    GameArea* attachedGameArea;

public:
    MainWindow(GameArea* ga,QWidget* parent=Q_NULLPTR):
        QWidget(parent),
        attachedGameArea(ga)
    {
        this->setWindowTitle("Vitae Of Blocks");        //устанавливаем название главного окна
        this->setWindowIcon(QIcon(":/res/icon.png"));   //устанавливаем иконку

        this->setAttribute(Qt::WA_DeleteOnClose);       //говорим окну выключаться по закрытии
        this->setObjectName("MAIN");                    //устанавливаем имя для стиля
    }

protected:
    virtual void closeEvent(QCloseEvent* event)
    {
        if (!attachedGameArea->isGameOver())            //если не конец игры
        {
            attachedGameArea->setGameOver();            //делаем конец игры
            event->accept();                            //говорим, что можно закрываться
        }
    }
};

#endif // MAINWINDOW_H
