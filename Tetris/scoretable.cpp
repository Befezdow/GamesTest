#include "scoretable.h"

Scoretable::Scoretable(int side, int labelwidth, int labelheight, QWidget *parent) :
    window(new GLScores(side,5,5,parent)),
    QWidget(parent)
{
    QVBoxLayout *vertical=new QVBoxLayout();
    window=new GLScores(side,5,5,parent);
    scores= new QLabel("Your score : "+QString::number(0));
    vertical->addWidget(window);
    vertical->addWidget(scores);
    this->setLayout(vertical);
}

void GLScores::paintFigure()
{

    Shape * figure = GLWidget::generateShape(indexOfFigure);
    QVector<QPoint> points = figure->getParts();
    delete figure;
    foreach (QPoint point, points)
    {
        int x = point.x()*side;
        int y = point.y()*side;
        int x1 = x + side;
        int y1 = y - side;
        qglColor(color);
        glRecti(x,y,x1,y1);
        qglColor(Qt::black);
        glBegin(GL_LINE_LOOP);
            glVertex2i(x,y);
            glVertex2i(x,y1);
            glVertex2i(x1,y1);
            glVertex2i(x1,y);
        glEnd();

    }

}
