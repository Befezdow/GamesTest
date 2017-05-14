#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "scoretable.h"
#include "difficultywindow.h"

class OptionsWindow: public QWidget
{
    Q_OBJECT
    Scoretable * scores;                    //виджеты очков и следующей фигуры
    QLabel* names;                          //имена разработчиков
    QPushButton* pause;                     //кнопка паузы
    QPushButton* restart;                   //кнопка рестарта
    QPushButton* difficulty;                //кнопка сложности
    QPushButton* highScores;                //кнопка вывода таблицы очков
    QVBoxLayout* vlay;
    QVBoxLayout* buttonLay;

    GameArea* gameArea;                     //указатель на игровую зону, можно без него, но придется переопределять слоты
    int currentDifficulty;                  //текущая сложность игры

public:
    OptionsWindow(GameArea * area,int initDifficulty,int screenWidth,QWidget* parent=Q_NULLPTR);

private slots:
    void showDifficultyWindow();            //показать окно с выбором сложности
};

#endif // OPTIONSWINDOW_H
