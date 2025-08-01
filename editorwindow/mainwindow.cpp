#include "mainwindow.h"
#include "codelibrary.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextEdit>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    menu_bar = menuBar();
    resize(600,400);

    code_lib = new CodeLibrary(this,this);

    edit_text = new QTextEdit();

    setCentralWidget(edit_text);
    showMaximized();
    // setStyleSheet("background: white;"
    //               " color:black");

    edit_text->setStyleSheet("background: transparent;"
                             "border-color: black");

    //<------------------File menu------------------->
    file_menu = menu_bar->addMenu("&File");


    //New Document
    new_action = code_lib->action_handler(file_menu, "&New","New");

    //Save Document
    save_action = code_lib->action_handler(file_menu,"&Save","Save");

    //Save As
    save_as_action = code_lib->action_handler(file_menu,"&Save As", "Save As");

    //Open Document
    open_action = code_lib->action_handler(file_menu,"&Open","Open");

    //Exit Application
    exit_program = code_lib->action_handler(file_menu,"&Quit","Exit");

    //<--------------------Edit menu----------------------->
    edit_menu = menu_bar->addMenu("&Edit");
    //cut operation
    cut_action = code_lib->action_handler(edit_menu,"&Cut","Cut");

    //copy operation
    copy_action = code_lib->action_handler(edit_menu,"&Copy","Copy");

    //paste operation
    paste_action = code_lib->action_handler(edit_menu,"&Paste","Paste");

    //undo operation
    undo_action = code_lib->action_handler(edit_menu,"&Undo","Undo");

    //redo operation
    redo_action = code_lib->action_handler(edit_menu,"&Redo","Redo");

    //<---------------------Page Menu----------------------->
    page_menu = menu_bar->addMenu("&Page");

    //print operation
    print_action = code_lib->action_handler(edit_menu,"&Print","Print");

    //page setup
    page_setup = code_lib->action_handler(edit_menu,"&Page Setup","Page Setup");

    //<----------------------About menu--------------------->
    about_menu = menu_bar->addMenu("&About");

    //info popup
    info = code_lib->action_handler(about_menu,"&Info","Info");
}

QTextEdit *MainWindow::getTextEdit() const{
    return edit_text;
}


