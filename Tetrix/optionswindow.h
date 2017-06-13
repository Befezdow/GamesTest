#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include <QTime>
#include <QTableWidget>

class OptionsWindow: public QWidget
{
    Q_OBJECT

    class ScoreTableElement                 //класс рекорда
    {
    public:
        QDateTime time;                     //время
        unsigned int score;                 //счет
        QString playerName;                 //имя игрока

        ScoreTableElement();
        ScoreTableElement(QDateTime t, unsigned int s, QString p);

        bool operator< (const ScoreTableElement& ob) const;
                                            //оператор сравнения, нужен для сортировки
    };

    class ScoreTable: public QDialog        //класс таблицы рекордов
    {
        QTableWidget* table[5];             //виджет таблицы
        QPushButton* ok;                    //кнопка ок

    public:
        ScoreTable();
        void updateInfo(unsigned int dif, QList<ScoreTableElement> scoreList);
    };

    NextShapeAndScore * shapeScore;         //виджеты очков и следующей фигуры
    ScoreTable* scoresView;
    QLabel* names;                          //имена разработчиков
    QPushButton* pause;                     //кнопка паузы
    QPushButton* restart;                   //кнопка рестарта
    QPushButton* difficulty;                //кнопка сложности
    QPushButton* highScores;                //кнопка вывода таблицы очков
    QVBoxLayout* vlay;
    QVBoxLayout* buttonLay;

    GameArea* gameArea;                     //указатель на игровую зону, можно без него, но придется переопределять слоты
    unsigned int currentDifficulty;         //текущая сложность игры
    QString fileName[5];                    //имя файла с рекордами

    QList<ScoreTableElement> scores[5];     //сами рекорды

public:
    OptionsWindow(GameArea * area,int initDifficulty,int screenWidth,QWidget* parent=Q_NULLPTR);
    void attachFile(unsigned int dif, QString fileName);
                                            //прикрепить файл с рекордами
private slots:
    void showDifficultyWindow();            //показать окно с выбором сложности
    void readScores();                      //прочитать рекорды из файла
    void writeScores();                     //выписать рекорды в файл
    void addRecord(unsigned int score, QString player); //добавить рекорд
    void showScoreTable();                  //показать таблицу рекордов
};

#endif // OPTIONSWINDOW_H
