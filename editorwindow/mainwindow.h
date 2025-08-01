#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "codelibrary.h"
#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QTextEdit * getTextEdit()const;

private:
    Ui::MainWindow *ui;

    CodeLibrary * code_lib;


    QMenuBar * menu_bar;//main menu bar

    QToolBar * tool_bar;

    QTextEdit * edit_text;
    QLineEdit * font_edt;

    QMenu * file_menu;//file menu
    QMenu * edit_menu;//edit menu
    QMenu * font_menu;
    QMenu * page_menu;
    QMenu * about_menu;//about menu



    //self explanatory actions
    QAction * new_action;
    QAction * save_action;
    QAction * save;
    QAction * save_as_action;
    QAction * cut_action;
    QAction * copy_action;
    QAction * undo_action;
    QAction * redo_action;
    QAction * increase_font;
    QAction * decrease_font;
    QAction * bold_font;
    QAction * italicize_font;
    QAction * underline_font;
    QAction * left_alignment;
    QAction * right_alignment;
    QAction * center_alignment;
    QAction * justify_alignment;
    QAction * paste_action;
    QAction * open_action;
    QAction * open;
    QAction * print_action;
    QAction * page_setup;
    QAction * exit_program;
    QAction * info;

    QLabel * word_counter_lbl;

    QString m_currentFilePath;//this one will store the current path for the current document'

    void action_func(QMenu * menu, QAction *action, const QString &menu_ation_name, const QString &status_tip);

    void new_document();
    void open_document();

    void save_document();
    void save_document_as();

    void undo_text();

    void show_info();

    void onFontDefFinished();
    void word_counter();


};
#endif // MAINWINDOW_H
