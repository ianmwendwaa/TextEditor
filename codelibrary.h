#ifndef CODELIBRARY_H
#define CODELIBRARY_H

#include <QAction>
#include <QObject>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>

class MainWindow;
class CodeLibrary: public QObject

{
    Q_OBJECT
public:
    explicit CodeLibrary(QObject * parent = nullptr, MainWindow * main_window = nullptr);
    void new_document();
    void save_document();
    void save_document_as();
    void open_document();
    void show_info();
    void page_setup();
    void print_doc();
    QAction* action_handler(QMenu * menu_bar, const QString &menu_item, const QString&status_tip);

private:
    MainWindow * m_main_window;
};


#endif // CODELIBRARY_H
