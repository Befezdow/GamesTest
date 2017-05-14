#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "scoretable.h"
#include "difficultywindow.h"
#include <QtWidgets>

class OptionsWindow: public QWidget
{
    Q_OBJECT
    Scoretable * scores;
    QLabel* names;
    QPushButton* pause;
    QPushButton* restart;
    QPushButton* difficulty;
    QPushButton* highScores;
    QVBoxLayout* vlay;
    QVBoxLayout* buttonLay;

    GameArea* gameArea;
    int currentDifficulty;

public:
    OptionsWindow(GameArea * area,int initDifficulty,int screenWidth,QWidget* parent=Q_NULLPTR);

private slots:
    void showDifficultyWindow();
};

#endif // OPTIONSWINDOW_H
