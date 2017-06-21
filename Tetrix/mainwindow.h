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
    {}

protected:
    virtual void closeEvent(QCloseEvent* event)
    {
        attachedGameArea->setGameOver();
        event->accept();
    }
};

#endif // MAINWINDOW_H
