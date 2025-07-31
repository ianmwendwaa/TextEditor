#include "mainwindow.h"

#include <QApplication>
#include <QMenuBar>
#include <QTextEdit>
#include <QAction>
#include <QObject>
#include <QFileDialog>
#include <QFile>
#include <QToolBar>
#include <QIcon>
#include <QMessageBox>
#include <QToolbar>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("My text editor");
    w.setWindowIconText("Icon");
    w.show();

    return a.exec();
}
