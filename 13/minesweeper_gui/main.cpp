#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(w.cancelled_at_start)
    {
        return 0;
    }
    w.show();
    return a.exec();
}
