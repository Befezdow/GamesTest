#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "nextshapeandscore.h"
#include "difficultywindow.h"
#include <QTime>
#include <QTableWidget>

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

    class ScoreTable: public QDialog
    {
        QTableWidget* table;
        QPushButton* ok;

    public:
        ScoreTable(QList<ScoreTableElement> scores)
        {
            table=new QTableWidget(scores.size(),3);
            QStringList lst;
            lst<<"Name"<<"Score"<<"Time";
            table->setHorizontalHeaderLabels(lst);
            lst.clear();
            for (int i=1;i<=scores.size();++i)
            {
                lst<<QString::number(i);
            }

            table->setVerticalHeaderLabels(lst);

            for (int i=0;i<scores.size();++i)
            {
                ScoreTableElement elem=scores.at(i);
                QTableWidgetItem* itemName=new QTableWidgetItem(elem.playerName);
                QTableWidgetItem* itemScore=new QTableWidgetItem(QString::number(elem.score));
                QTableWidgetItem* itemTime=new QTableWidgetItem(elem.time.toString("hh:mm:ss dd.MM.yyyy"));
                table->setItem(i,0,itemName);
                table->setItem(i,1,itemScore);
                table->setItem(i,2,itemTime);
            }
            ok=new QPushButton("Ok");

            QVBoxLayout* lay=new QVBoxLayout;
            lay->addWidget(table);
            lay->addWidget(ok);
            this->setLayout(lay);
        }
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
    void showScoreTable();
};

#endif // OPTIONSWINDOW_H
