#include "codelibrary.h"
#include "mainwindow.h"

#include <QMap>
#include <QString>
#include <QTextEdit>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QApplication>

enum ActionTypes{
    NEW, SAVE, SAVE_AS, OPEN,
    EXIT, UNDO, REDO, PASTE,
    CUT, COPY, PRINT, PAGE_SETUP,
    ABOUT, INFO, UNKNOWN_CMD
};
CodeLibrary::CodeLibrary(QObject * parent, MainWindow * main_window): QObject(parent), m_main_window(main_window) {
    // edit_ = new QTextEdit();
}

QAction* CodeLibrary::action_handler(QMenu * menu_bar, const QString &menu_item, const QString &status_tip){
    QAction * action = menu_bar->addAction(menu_item);/*adding the action to the menu specified-> I realised that if you
    dont, it throws an error*/
    static QMap<QString, ActionTypes> action_maps = {
        {"New", NEW},{"Save", SAVE},{"Save As", SAVE_AS},
        {"Open", OPEN},{"Exit",EXIT},{"Undo", UNDO},{"Redo",REDO},
        {"Paste",PASTE},{"Cut", CUT},{"Copy", COPY},{"Print",PRINT},
        {"Page Setup", PAGE_SETUP},{"About", ABOUT},{"Info",INFO}};

    QString menu_input = status_tip;
    ActionTypes cmd = UNKNOWN_CMD;

    auto it = action_maps.find(menu_input);

    //check if the element specified in args exists in the map
    if(it != action_maps.end()){
        cmd = it.value();
    }

    switch (cmd) {
    case NEW:
        action->setShortcut(QKeySequence::New);
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::new_document);
        break;
    case OPEN:
        action->setShortcut(QKeySequence::Open);
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::open_document);
        break;
    case SAVE:
        action->setShortcut(QKeySequence::Save);
        break;
    case SAVE_AS:
        action->setShortcut(QKeySequence::SaveAs);
        break;
    case EXIT:
        action->setShortcut(QKeySequence::Quit);
        QObject::connect(action, &QAction::triggered, this, &QApplication::quit);
        break;
    default:
        break;
    }
    return action;
}

void CodeLibrary::new_document(){
    if(m_main_window){
        QTextEdit * txt_edit = m_main_window->getTextEdit();
        if(txt_edit){
            txt_edit->clear();
        }
    }
}

void CodeLibrary::save_document_as(){

}

void CodeLibrary::save_document(){

}

void CodeLibrary::open_document(){

}

void CodeLibrary::show_info(){

}

void CodeLibrary::page_setup(){

}
void CodeLibrary::print_doc(){

}
