#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QDialog>
#include <QWidget>

class DifficultyWindow: public QDialog
{
    Q_OBJECT
    QRadioButton* difficulties[5];              //кнопки сложности
    QGroupBox* group;
    QPushButton* ok;
    QPushButton* cancel;
    QLabel* label;
    QVBoxLayout* radioLay;
    QVBoxLayout* vLay;
    QHBoxLayout* hLay;
    QSignalMapper* mapper;

    int currentDifficulty;                      //выбранная сложность

public:
    DifficultyWindow(int initDiff,QWidget* parent=Q_NULLPTR);

    int getCurrentDifficulty() const;           //возвращает выбранную сложность

private slots:
    void changeResult(int i);                   //изменяем выбранную сложность
};

#endif // DIFFICULTYWINDOW_H
