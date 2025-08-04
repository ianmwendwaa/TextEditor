#include "mainwindow.h"
#include "codelibrary.h"

#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    menu_bar = menuBar();
    resize(600,400);

    code_lib = new CodeLibrary(this,this);

    edit_text = new QTextEdit();
    // edit_text->setFixedWidth(700);

    //the font was too small by default so i had to manually increase it
    QFont sth = edit_text->font();
    int fontSize = sth.pointSize();
    sth.setPointSize(fontSize+2);
    edit_text->setFont(sth);

    setCentralWidget(edit_text);
    showMaximized();
    // setStyleSheet("background: #f4f4f4;"
    //               "color:black");

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

    //<------------------Font menu---------------------------->
    font_menu = menu_bar->addMenu("&Font");

    //increase font operation
    increase_font = code_lib->action_handler(font_menu,"&Increase Font Size","Increase Font");

    //decrease font operation
    decrease_font = code_lib->action_handler(font_menu,"&Decrease Font Size","Decrease Font");

    //italicize font
    italicize_font = code_lib->action_handler(font_menu,"&Italics","Italics");

    //bold font
    bold_font = code_lib->action_handler(font_menu,"&Bold", "Bold");

    //underline font
    underline_font = code_lib->action_handler(font_menu,"&Underline","Underline");

    //left alignment
    left_alignment = code_lib->action_handler(font_menu, "&Left Alignment","Left");

    //left alignment
    right_alignment = code_lib->action_handler(font_menu, "&Right Alignment","Right");

    //left alignment
    center_alignment = code_lib->action_handler(font_menu, "&Center Alignment","Center");

    //left alignment
    justify_alignment = code_lib->action_handler(font_menu, "&Justified Alignment","Justify");

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

    QToolBar * bottomToolBar = addToolBar("Status bar");
    bottomToolBar->setMovable(false);
    bottomToolBar->setFloatable(false);
    addToolBar(Qt::BottomToolBarArea, bottomToolBar);

    word_counter_lbl = new QLabel("Words: 0", this);
    bottomToolBar->addWidget(word_counter_lbl);
    QObject::connect(edit_text, &QTextEdit::textChanged, code_lib, &CodeLibrary::word_counter);
}

QTextEdit *MainWindow::getTextEdit() const{
    return edit_text;
}

QLabel *MainWindow::getWordCounter() const{
    return word_counter_lbl;
}

bool MainWindow::isSaved()
{
    if(this->getTextEdit()->document()->isModified()){
        QMessageBox::StandardButton action = QMessageBox::warning(this,
                                                                  "Text Editor:Save Watcher","There have been modifications to your document. "
                                                                  "Do you want to save your document?",QMessageBox::Save|QMessageBox::Cancel|QMessageBox::Discard);

        switch (action) {
        case QMessageBox::Save:
            return code_lib->save_document();
            break;
        case QMessageBox::Cancel:
            return false;
        default:
            break;
        }
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *closeEvent){
    if(isSaved()){
        closeEvent->accept();
    }else{
        closeEvent->ignore();
    }
}

