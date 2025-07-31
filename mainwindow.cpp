#include "mainwindow.h"
#include "codelibrary.h"
#include <map>

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
    save_action = new QAction();
    MainWindow::action_func(file_menu, save_action, "&Save", "Save");

    save_as_action = new QAction();
    MainWindow::action_func(file_menu, save_as_action, "&Save As", "Save As");

    open_action = new QAction();
    MainWindow::action_func(file_menu, open_action, "&Open", "Open");

    exit_program = new QAction();
    MainWindow::action_func(file_menu, exit_program, "&Exit", "Exit");


    save_action = file_menu->addAction("&Save");
    save_action->setShortcut(QKeySequence::Save);
    save_action->setStatusTip("Save Document");
    QObject::connect(save_action, &QAction::triggered, this, &MainWindow::save_document);

    //Save As
    save_as_action = file_menu->addAction("&Save As");
    save_as_action->setShortcut(QKeySequence::SaveAs);
    save_as_action->setStatusTip("Save As");

    //Open Document
    open_action = file_menu->addAction("&Open");
    open_action->setShortcut(QKeySequence::Open);
    open_action->setStatusTip("Open Document");

    QObject::connect(open_action, &QAction::triggered, this, &MainWindow::open_document);

    //Exit
    exit_program = file_menu->addAction("&Exit");
    exit_program->setShortcut(QKeySequence::Quit);
    exit_program->setStatusTip("Exit");
    QObject::connect(exit_program, &QAction::triggered, this, &QApplication::quit);


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
    info = about_menu->addAction("&Info");
    info->setStatusTip("Info");
    QObject::connect(info, &QAction::triggered, this, &MainWindow::show_info);
}

QTextEdit *MainWindow::getTextEdit() const{
    return edit_text;
}

enum ActionTypes{
    NEW, SAVE, SAVE_AS, OPEN,
    EXIT, UNDO, REDO, PASTE,
    CUT, COPY, PRINT, PAGE_SETUP, ABOUT, INFO, UNKNOWN_CMD

};
void MainWindow::action_func(QMenu *menu, QAction * action,
                             const QString &menu_ation_name, const QString &status_tip){
    action = menu->addAction(menu_ation_name);

    std::map<QString, ActionTypes> action_map;

    action_map["New"] = NEW;
    action_map["Save"] = SAVE;
    action_map["save_as"] = SAVE_AS;

    QString action_input = status_tip;
    ActionTypes cmd = UNKNOWN_CMD;
    if(action_map.count(action_input)){
        cmd = action_map[action_input];
    }

    switch (cmd) {
    case NEW:
        action->setShortcut(QKeySequence::New);
        QObject::connect(action, &QAction::triggered, code_lib, &CodeLibrary::new_document);
        break;
    case SAVE:
        action->setShortcut(QKeySequence::Save);
        QObject::connect(action, &QAction::triggered, this, &MainWindow::save_document);
    case SAVE_AS:
        action->setShortcut(QKeySequence::SaveAs);
        QObject::connect(action, &QAction::triggered, code_lib, &CodeLibrary::save_document_as);
    default:
        break;
    }

    action->setStatusTip(status_tip);


}

void MainWindow::new_document(){
    edit_text->clear();//clearing the text edit to simulate new doc created

    /*  TODO: I need to implement a more elaborative approach on this
     a system where a new window with a new text edit appears*/
}

void MainWindow::open_document(){
    QString file_path = QFileDialog::getOpenFileName(this, "Open Document","","*.doc *.txt *.docx");//storing file path as a QString

    //checking if the file is empty or not, if it is not, perform the file opening
    if(!file_path.isEmpty()){
        QFile file(file_path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QMessageBox::critical(this,"Error: ",""+ file.errorString());//throws an error as it returns false
            return;
        }
        //getting the data from file
        QTextStream data_in(&file);
        QString content = data_in.readAll();//reading the files content

        //closing the file as the contents have already been obtained
        file.close();

        //checking if the widget has been initialized to prevent runtime error
        if(edit_text){
            edit_text->setPlainText(content);
            setWindowTitle(QFileInfo(file_path).fileName());//set window title as name of the document
        }else{
            QMessageBox::critical(this, "Widget accessed is a null pointer","");
        }
    }
}

void MainWindow::save_document(){
    QString file_path = QFileDialog::getSaveFileName(this, "Save Document","C:/Documents", "*.txt");

    if(file_path.isEmpty()){
        QMessageBox::critical(this, "Error","Enter text file's title!");
        return;
    }

    QFile file(file_path);

    if(!file.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate)){
        QMessageBox::critical(this, "Error saving document!","");
        return;
    }
    //packaging the contents of the file
    QTextStream data_out(&file);

    //passing the content to be saved
    data_out<<edit_text->toPlainText();

    file.close();//closing the file to save on resources and stuff

    setWindowTitle(QFileInfo(file_path).fileName());//get and set the window title as the title of the document
}


void MainWindow::show_info(){
    QMessageBox::information(this, "About me","This is the very first complete C++ GUI application in Project 91E. I am exhilarated!");
}



