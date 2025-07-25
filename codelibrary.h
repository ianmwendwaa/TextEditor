#ifndef CODELIBRARY_H
#define CODELIBRARY_H

#include <QToolBar>
#include <QAction>
#include <QWidget>
#include <QMainWindow>

class CodeLibrary:public QMainWindow
{
    Q_OBJECT;
public:
    CodeLibrary(QWidget * parent = nullptr);

private:
    QAction * save_action;
    QAction * undo_action;
    QAction * redo_action;

    QToolBar * toolbar;
};



#endif // CODELIBRARY_H
