#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("My text editor");
    w.setWindowIconText("Icon");
    w.show();

    return a.exec();
}
