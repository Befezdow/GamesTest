#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtWidgets>
#include <QGLWidget>

class GlWidget : public QGLWidget
{
    Q_OBJECT
public :
    GlWidget(QWidget *parent = 0);
    ~GlWidget();
protected:

    virtual void resizeGL(int width, int height);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent * event);
private:
    int rectWidth;
    int x;
    int y;
    int ystep;
    int xstep;

};

#endif // GLWIDGET_H
