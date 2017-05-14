#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QtWidgets>

class DifficultyWindow: public QDialog
{
    Q_OBJECT
    QRadioButton* difficulties[5];
    QGroupBox* group;
    QPushButton* ok;
    QPushButton* cancel;
    QLabel* label;
    QVBoxLayout* radioLay;
    QVBoxLayout* vLay;
    QHBoxLayout* hLay;
    QSignalMapper* mapper;

    int currentDifficulty;

public:
    DifficultyWindow(int initDiff,QWidget* parent=Q_NULLPTR);
    int getCurrentDifficulty() const;
private slots:
    void changeResult(int i);
};

#endif // DIFFICULTYWINDOW_H
