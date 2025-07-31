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

    edit_text->setStyleSheet("background: transparent");

    //<------------------File menu------------------->
    file_menu = menu_bar->addMenu("&File");

    //initializing the toolbar
    tool_bar = addToolBar("Toolbar");

    //save icon fot the toolbar
    save = new QAction(QIcon::fromTheme("document-save", QIcon(":/icon.png")),"Save",this);

    //open icon
    open = new QAction(QIcon::fromTheme("document-open", QIcon(":/icon.png")),"Open",this);

    //adding the icons to the toolbar
    tool_bar->addAction(save);
    tool_bar->addAction(open);


    //New Document
    new_action = code_lib->action_handler(file_menu, "&New","New");

    //Save Document
    save_action = code_lib->action_handler(file_menu,"&Save","Save");

    save_as_action = code_lib->action_handler(file_menu,"&Save As", "Save As");

    open_action = code_lib->action_handler(file_menu,"&Open","Open");

    exit_program = code_lib->action_handler(file_menu,"&Quit","Exit");

    //<--------------------Edit menu----------------------->
    edit_menu = menu_bar->addMenu("&Edit");
    //cut operation
    cut_action = edit_menu->addAction("&Cut");
    cut_action->setShortcut(QKeySequence::Cut);
    cut_action->setStatusTip("Cut");
    QObject::connect(cut_action, &QAction::triggered, edit_text, &QTextEdit::cut);

    //copy operation
    copy_action = edit_menu->addAction("&Copy");
    copy_action->setShortcut(QKeySequence::Copy);
    copy_action->setStatusTip("Copy");
    QObject::connect(copy_action, &QAction::triggered, edit_text, &QTextEdit::copy);

    //paste operation
    paste_action = edit_menu->addAction("&Paste");
    paste_action->setShortcut(QKeySequence::Paste);
    paste_action->setStatusTip("Paste");
    QObject::connect(paste_action, &QAction::triggered, edit_text, &QTextEdit::paste);

    //undo operation
    undo_action = edit_menu->addAction("&Undo");
    undo_action->setShortcut(QKeySequence::Undo);
    undo_action->setStatusTip("Undo");
    QObject::connect(undo_action, &QAction::triggered, edit_text, &QTextEdit::undo);

    //redo operation
    redo_action = edit_menu->addAction("&Redo");
    redo_action->setShortcut(QKeySequence::Redo);
    redo_action->setStatusTip("Redo");
    QObject::connect(redo_action, &QAction::triggered, edit_text, &QTextEdit::redo);

    //<---------------------Page Menu----------------------->
    page_menu = menu_bar->addMenu("&Page");

    //print operation
    print_action = page_menu->addAction("&Print");
    print_action->setShortcut(QKeySequence::Print);
    print_action->setStatusTip("Print");

    //page setup
    page_setup = page_menu->addAction("&Page Setup");
    page_setup->setStatusTip("Page Setup");

    //<----------------------About menu--------------------->
    about_menu = menu_bar->addMenu("&About");

    //info popup
    info = code_lib->action_handler(about_menu,"&Info","Info");
}

QTextEdit *MainWindow::getTextEdit() const{
    return edit_text;
}


