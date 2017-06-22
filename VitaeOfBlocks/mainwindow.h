#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamearea.h"
#include <QWidget>
#include <QCloseEvent>

class MainWindow: public QWidget
{
    GameArea* attachedGameArea;
//    QPixmap background;

public:
    MainWindow(GameArea* ga,QWidget* parent=Q_NULLPTR):
        QWidget(parent),
        attachedGameArea(ga)
    {
//        background.load("/home/Befezdow/Desktop/qqq.png");
//        QPalette pal;
//        pal.setBrush(QPalette::Background,QBrush(background));
//        this->setPalette(pal);
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
