#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include <QTime>

class OptionsWindow: public QWidget
{
    Q_OBJECT
    NextShapeAndScore * shapeScore;         //виджеты очков и следующей фигуры
    QLabel* names;                          //имена разработчиков
    QPushButton* pause;                     //кнопка паузы
    QPushButton* restart;                   //кнопка рестарта
    QPushButton* difficulty;                //кнопка сложности
    QPushButton* highScores;                //кнопка вывода таблицы очков
    QVBoxLayout* vlay;
    QVBoxLayout* buttonLay;

    GameArea* gameArea;                     //указатель на игровую зону, можно без него, но придется переопределять слоты
    int currentDifficulty;                  //текущая сложность игры
    QString fileName;                       //имя файла с рекордами

    class ScoreTableElement                //класс рекорда
    {
    public:
        QDateTime time;                     //время
        unsigned int score;                 //счет
        QString playerName;                 //имя игрока

        ScoreTableElement();
        ScoreTableElement(QDateTime t, unsigned int s, QString p);

        bool operator< (const ScoreTableElement& ob) const;
    };

    QList<ScoreTableElement> scores;      //сами рекорды

public:
    OptionsWindow(GameArea * area,int initDifficulty,int screenWidth,QWidget* parent=Q_NULLPTR);
    void attachFile(QString fileName);      //прикрепить файл с рекордами

private slots:
    void showDifficultyWindow();            //показать окно с выбором сложности
    void readScores();      //прочитать рекорды из файла
    void writeScores();     //выписать рекорды в файл
    void addRecord(unsigned int score, QString player);
};

#endif // OPTIONSWINDOW_H
