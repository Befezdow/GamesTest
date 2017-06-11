#include "optionswindow.h"
#include <QFile>
#include <QHeaderView>


OptionsWindow::OptionsWindow(GameArea *area, int initDifficulty, int screenWidth, QWidget *parent):
    QWidget(parent),
    currentDifficulty(initDifficulty),
    fileName("")
{
    shapeScore= new NextShapeAndScore(screenWidth/68);                      //создаем виджеты
    names = new QLabel("Made by:\n@Befezdow\n@YouCanKeepSilence");
    pause = new QPushButton("Pause");
    restart = new QPushButton("Restart");
    difficulty=new QPushButton("Difficulty");
    highScores = new QPushButton("Highscores");
    vlay = new QVBoxLayout;
    buttonLay = new QVBoxLayout;

    gameArea=area;                                                          //прикрепляем игровую зону

    //соединяем слоты
    QObject::connect(gameArea,SIGNAL(scoreChanged(int)),shapeScore,SLOT(changeScore(int)));
    QObject::connect(gameArea,SIGNAL(throwNextFigure(int,QColor)),shapeScore,SLOT(setNextFigure(int,QColor)));
    QObject::connect(pause,SIGNAL(clicked(bool)),gameArea,SLOT(switchPause()));
    QObject::connect(restart,SIGNAL(clicked(bool)),gameArea,SLOT(start()));
    QObject::connect(difficulty,SIGNAL(clicked(bool)),this,SLOT(showDifficultyWindow()));
    QObject::connect(highScores,SIGNAL(clicked(bool)),this,SLOT(showScoreTable()));

    //собираем виджеты в слои
    buttonLay->addWidget(pause);
    buttonLay->addWidget(restart);
    buttonLay->addWidget(difficulty);
    buttonLay->addWidget(highScores);

    vlay->addWidget(shapeScore,0,Qt::AlignHCenter | Qt::AlignTop);
    vlay->addLayout(buttonLay);
    vlay->addWidget(names,0,Qt::AlignHCenter | Qt::AlignBottom);

    this->setLayout(vlay);                  //устанавливаем слой

    shapeScore->setFocusProxy(gameArea);    //устанавливаем пренаправление фокуса клавиатуры на игровую зону
    pause->setFocusProxy(gameArea);
    restart->setFocusProxy(gameArea);
    difficulty->setFocusProxy(gameArea);
    highScores->setFocusProxy(gameArea);
    this->setFocusProxy(gameArea);

    this->attachFile("scores.svs");
    this->readScores();
}

void OptionsWindow::attachFile(QString fileName)
{
    this->fileName=fileName;
}

void OptionsWindow::showDifficultyWindow()
{
    gameArea->switchPause();                            //ставим игру на паузу
    DifficultyWindow diff(currentDifficulty);           //создаем окно сложности

    if (diff.exec()==QDialog::Accepted)                 //вызываем его
    {                                                   //если юзер нажал принять
        currentDifficulty=diff.getCurrentDifficulty();  //получаем сложность
        gameArea->setDifficulty(currentDifficulty);     //устанавливаем сложность
        gameArea->start();                              //перезапускаем игру
    }
    else                                                //если нажал отмену или закрыл
    {
        gameArea->switchPause();                        //снимаем игру с паузы
    }
}

void OptionsWindow::readScores()
{
    QFile file(fileName);                               //сам файл
    if (!file.open(QIODevice::ReadOnly))                //открываем его
    {
        scores.push_back(ScoreTableElement(QDateTime::currentDateTime(),1000,"The Good"));
        scores.push_back(ScoreTableElement(QDateTime::currentDateTime(),500,"The Bad"));
        scores.push_back(ScoreTableElement(QDateTime::currentDateTime(),100,"The Ugly"));
        return;
    }

    scores.clear();                                     //очищаем текущие рекорды

    QDataStream out(&file);                             //открываем поток для файла
    while (true)                                        //читаем рекорды
    {
        QDateTime t;
        unsigned int s;
        QString p;
        out>>t>>s>>p;                                   //читаем данные

        if (out.atEnd())                                //если поток закончился
        {
            break;                                      //отваливаемся
        }
        else                                            //иначе
        {
            scores.push_back(ScoreTableElement(t,s,p)); //закидываем данные в рекорды
        }
    }

    file.close();                                       //закрываем файл
}

void OptionsWindow::writeScores()
{
    QFile file(fileName);                               //сам файл
    if (!file.open(QIODevice::WriteOnly))               //открываем его
    {
        return;
    }

    QDataStream out(&file);                             //открываем поток для файла

    for (int i=0;i<scores.size();++i)                   //идем по списку рекордов
    {
        ScoreTableElement e=scores.at(i);               //получаем элемент
        out<<e.time<<e.score<<e.playerName;             //пишем его в файл
    }

    file.close();                                       //закрываем файл
}

void OptionsWindow::addRecord(unsigned int score,QString player)
{
    scores.push_back(ScoreTableElement(QDateTime::currentDateTime(),score,player));
                                                                //добавляем новый рекорд
    std::sort(scores.begin(),scores.end());                     //сортируем список рекордов
    if (scores.size()>20)                                       //если в нем больше 20 элементов
    {
        scores.pop_back();                                      //последний выкидываем
    }
}

void OptionsWindow::showScoreTable()
{
    gameArea->switchPause();                                    //ставим игру на паузу

    ScoreTable table(scores);                                   //создаем виджет таблицы рекордов
    table.exec();                                               //вызываем его

    gameArea->switchPause();                                    //снимаем паузу
}

OptionsWindow::ScoreTableElement::ScoreTableElement():
    score(0)
{}

OptionsWindow::ScoreTableElement::ScoreTableElement(QDateTime t, unsigned int s, QString p):
    time(t),
    score(s),
    playerName(p)
{}

bool OptionsWindow::ScoreTableElement::operator<(const OptionsWindow::ScoreTableElement &ob) const
{
    if (score<ob.score)                         //сравниваем счет
    {
        return false;                           //инверсия, так как хочу сортировку по убыванию
    }
    else
    {
        if (score==ob.score && time>ob.time)    //если счет совпадает, сраниваем время
        {
            return false;                       //инверсия, так как хочу сортировку по убыванию
        }
        return true;                            //инверсия, так как хочу сортировку по убыванию
    }
}

OptionsWindow::ScoreTable::ScoreTable(QList<OptionsWindow::ScoreTableElement> scores)
{
    table=new QTableWidget(scores.size(),4);            //создаем виджет таблицы

    QStringList lst;                                    //временный список
    lst<<"Name"<<"Score"<<"Time"<<"Date";
    table->setHorizontalHeaderLabels(lst);              //задаем горизонтальный заголовок

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
                                                        //фиксируем высоту строки
    for (int i=0;i<scores.size();++i)                   //закидываем в таблицу элементы
    {
        ScoreTableElement elem=scores.at(i);            //получаем элемент из списка
        QTableWidgetItem* itemName=new QTableWidgetItem(elem.playerName);                           //создаем ячейку имени
        QTableWidgetItem* itemScore=new QTableWidgetItem(QString::number(elem.score));              //создаем ячейку счета
        QTableWidgetItem* itemTime=new QTableWidgetItem(elem.time.time().toString("hh:mm:ss"));     //создаем ячейку времени
        QTableWidgetItem* itemDate=new QTableWidgetItem(elem.time.date().toString("dd.MM.yyyy"));   //создаем ячейку даты

        itemName->setFlags(Qt::ItemIsEnabled);          //говорим, что ячейки не редактируемые и не выбираемые
        itemScore->setFlags(Qt::ItemIsEnabled);
        itemTime->setFlags(Qt::ItemIsEnabled);
        itemDate->setFlags(Qt::ItemIsEnabled);

        itemName->setTextAlignment(Qt::AlignCenter);    //устанавливаем выравнивание текста в ячейках
        itemScore->setTextAlignment(Qt::AlignCenter);
        itemTime->setTextAlignment(Qt::AlignCenter);
        itemDate->setTextAlignment(Qt::AlignCenter);

        table->setItem(i,0,itemName);                   //вставляем ячейки в таблицу в одну строчку
        table->setItem(i,1,itemScore);
        table->setItem(i,2,itemTime);
        table->setItem(i,3,itemDate);
    }

    table->resizeColumnsToContents();                   //изменяем размер колонок в соответствии с содержимым

    int width=table->verticalHeader()->width()+table->columnWidth(0);           //считаем ширину поля
    width+=table->columnWidth(1)+table->columnWidth(2)+table->columnWidth(3);

    int height=table->horizontalHeader()->height();                             //считаем высоту поля
    for (int i=0;i<table->rowCount();++i)
    {
        height+=table->rowHeight(i);
    }

    table->setShowGrid(false);                                                  //убираем сетку
    table->setMinimumSize(width+2,height);                                      //устанавливаем минимальный размер таблицы
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);                  //убираем вертикальный слайдер

    ok=new QPushButton("Ok");                           //создаем кнопку и соединяем со слотом
    QObject::connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

    QVBoxLayout* lay=new QVBoxLayout;                   //создаем слой

    lay->addWidget(table);                              //закидываем в него виджеты
    lay->addWidget(ok,0,Qt::AlignHCenter | Qt::AlignBottom);

    this->setLayout(lay);                               //устанавливаем этот слой
}
