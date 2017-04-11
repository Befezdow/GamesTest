#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtWidgets>
#include <QGLWidget>
#define X_TILE_COUNT 10
#define Y_TILE_COUNT 10
namespace myFigure
{
    struct Rectnagle
    {
        float x;
        float y;
        float size;
    };
}


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
    void addRectangle(float x, float y);//, float size);
    void eraseRectangle(float x, float y);
    QList<myFigure::Rectnagle*> rectangles;
    bool tiles[X_TILE_COUNT][Y_TILE_COUNT];
    float xleft;
    float xright;
    float ytop;
    float ybot;
    float sizeOfSide;
    float x;
    float y;
    float ystep;
    float xstep;

};

#endif // GLWIDGET_H
