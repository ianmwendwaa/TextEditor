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

enum ActionTypes{
    NEW, SAVE, SAVE_AS, OPEN,
    EXIT, UNDO, REDO, PASTE,
    CUT, COPY, PRINT, PAGE_SETUP, ABOUT, INFO, UNKNOWN_CMD
};
CodeLibrary::CodeLibrary(QObject * parent, MainWindow * main_window): QObject(parent), m_main_window(main_window) {
    // edit_ = new QTextEdit();
}

void CodeLibrary::action_func(QAction * action, QMenu * menu_bar, QString &menu_item,QString&status_tip){
    action = menu_bar->addAction(menu_item);/*adding the action to the menu specified-> I realised that if you
    dont, it throws an error*/
    QMap<QString, ActionTypes> action_maps;

    action_maps["New"] = NEW;
    action_maps["Save"] = SAVE;
    action_maps["Open"] = OPEN;
    action_maps["Exit"] = EXIT;

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
    default:
        break;
    }


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

void CodeLibrary::open_document(){

}
