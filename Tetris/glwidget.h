#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtWidgets>

class GLWidget: public QGLWidget
{
    Q_OBJECT
    QVector<QVector<QPair<QPoint,bool>>> area;
    int squareSide;
    int currentX;
    int currentY;
    int timerId;
    int areaWidth;
    int areaHeight;
    int currentScore;
    QVector<QColor> colors;
    QColor currentColor;
public:
    GLWidget(int side,int width,int height,QWidget* parent=Q_NULLPTR);
protected:
    virtual void initializeGL();

    virtual void resizeGL(int w, int h);

    virtual void paintGL();

    virtual void timerEvent(QTimerEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void start();
    void endGame(int score);
signals:
    void gameOver(int);
};

#endif // GLWIDGET_H
