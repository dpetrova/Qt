#include <QApplication>
#include "studentdb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StudentDB w;
    w.show();
    return a.exec();
}
