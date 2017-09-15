#include "generator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Generator gen;
    gen.show();

    return a.exec();
}
