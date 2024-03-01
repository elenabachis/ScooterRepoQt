#include "mainwindow.h"
//#include "tests.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    call_all_tests();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
