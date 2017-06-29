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
        this->setAttribute(Qt::WA_DeleteOnClose);
        this->setObjectName("MAIN");
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
