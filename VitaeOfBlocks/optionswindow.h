#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include "soundcontroller.h"
#include <QTime>
#include <QTableWidget>

class OptionsWindow: public QWidget
{
    Q_OBJECT

    class ScoreTableElement                                 //класс рекорда
    {
    public:
        QDateTime time;                                     //время
        unsigned int score;                                 //счет
        QString playerName;                                 //имя игрока

        ScoreTableElement();
        ScoreTableElement(QDateTime t, unsigned int s, QString p);

        bool operator< (const ScoreTableElement& ob) const; //оператор сравнения, нужен для сортировки
    };

    class ScoreWidget: public QDialog                       //класс таблицы рекордов
    {
        QTableWidget* table[5];                             //виджет таблицы
        QPushButton* ok;                                    //кнопка ок
        QTabWidget* tabs;

    public:
        ScoreWidget();

        void updateInfo(unsigned int dif, QList<ScoreTableElement> scoreList);
    };

    NextShapeAndScore * shapeScore;                         //виджеты очков и следующей фигуры
    ScoreWidget* scoresView;
    QLabel* names;                                          //имена разработчиков
    SoundController* soundWidget;
    QPushButton* pause;                                     //кнопка паузы
    QPushButton* restart;                                   //кнопка рестарта
    QPushButton* difficulty;                                //кнопка сложности
    QPushButton* highScores;                                //кнопка вывода таблицы очков
    QPushButton* about;
    QVBoxLayout* vlay;                                      //общий слой
    QVBoxLayout* buttonLay;                                 //слой с кнопками

    GameArea* gameArea;                                     //указатель на игровую зону, можно без него, но придется переопределять слоты
    unsigned int currentDifficulty;                         //текущая сложность игры
    QString fileName[5];                                    //имя файла с рекордами

    QList<ScoreTableElement> scores[5];                     //сами рекорды

    void addRecord(unsigned int score, QString player);     //добавить рекорд
    bool checkForAdding(unsigned int score);                //проверить на вхождение в таблицу рекордов

public:
    OptionsWindow(GameArea * area, unsigned int initDifficulty, int screenWidth, QWidget* parent=Q_NULLPTR);
    ~OptionsWindow();
    void attachFile(unsigned int dif, QString fileName);    //прикрепить файл с рекордами

private slots:
    void showDifficultyWindow();                            //показать окно с выбором сложности
    void readScores();                                      //прочитать рекорды из файла
    void writeScores();                                     //выписать рекорды в файл
    void showScoreTable();                                  //показать таблицу рекордов
    void insertRecord(unsigned int score);                  //проверить и добавить рекорд в таблицу
    void aboutProgram();
};

#endif // OPTIONSWINDOW_H
