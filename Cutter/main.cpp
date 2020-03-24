#include "Cutter.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Cutter w;
    w.show();
    return a.exec();
}
