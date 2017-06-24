#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamearea.h"
#include <QWidget>
#include <QCloseEvent>

class MainWindow: public QWidget
{
    GameArea* attachedGameArea;

public:
    MainWindow(GameArea* ga,QWidget* parent=Q_NULLPTR):
        QWidget(parent),
        attachedGameArea(ga)
    {
        this->setObjectName("MAIN");
        this->setStyleSheet("#MAIN {border-image: url(/home/Befezdow/Desktop/eee.jpg) center;}");
    }

protected:
    virtual void closeEvent(QCloseEvent* event)
    {
        if (!attachedGameArea->isGameOver())
        {
            attachedGameArea->setGameOver();
            event->accept();
        }
    }
};

#endif // MAINWINDOW_H
