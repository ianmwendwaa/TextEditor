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

//results from process execution
enum ProcessResult{
    SUCCESS, FAILURE, PERMISSION_DENIED, INFORMATION, UNKNOWN_ERROR
};

CodeLibrary::CodeLibrary(QObject * parent, MainWindow * main_window): QObject(parent), m_main_window(main_window) {
    txt_edit = m_main_window->getTextEdit();
}

QAction* CodeLibrary::action_handler(QMenu * menu_bar, const QString &menu_item, const QString &status_tip){
    QAction * action = menu_bar->addAction(menu_item);
    QTextEdit * txt_edit = m_main_window->getTextEdit();

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
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::save_document);
        break;
    case SAVE_AS:
        action->setShortcut(QKeySequence::SaveAs);
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::save_document_as);
        break;
    case EXIT:
        action->setShortcut(QKeySequence::Quit);
        QObject::connect(action, &QAction::triggered, this, &QApplication::quit);
        break;
    case INFO:
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::show_info);
    case CUT:
        action->setShortcut(QKeySequence::Cut);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::cut);
    case COPY:
        action->setShortcut(QKeySequence::Copy);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::copy);
    case PASTE:
        action->setShortcut(QKeySequence::Paste);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::paste);
    case UNDO:
        action->setShortcut(QKeySequence::Undo);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::undo);
    case REDO:
        action->setShortcut(QKeySequence::Redo);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::redo);
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
            /*  TODO: I need to implement a more elaborative approach on this
     a system where a new window with a new text edit appears*/
        }
    }
}

void CodeLibrary::save_document_as(){
    QString file_path = QFileDialog::getSaveFileName(m_main_window,"Save Document","C:/Documents","*.txt");

    if(file_path.isEmpty()){
        CodeLibrary::display_msg_dialog("Error","Something went wrong.");
        return;
    }
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Truncate|QIODevice::Text)){
        CodeLibrary::display_msg_dialog("Error","Something went wrong.");
        return;
    }

    QTextStream file_data_out(&file);

    QTextEdit * txt_edit = m_main_window->getTextEdit();

    if(txt_edit){
        file_data_out<<txt_edit->toPlainText();
        file.close();
    }
    curr_file_path = file_path;//updating the new file path
    m_main_window->setWindowTitle(QFileInfo(file_path).fileName());
}

void CodeLibrary::open_document(){
    QString file_path = QFileDialog::getOpenFileName(m_main_window,"Open Document","C:/Documents", "*.txt");
    if(file_path.isEmpty()){
        CodeLibrary::display_msg_dialog("Error","Something went wrong!");
        return;
    }

    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        CodeLibrary::display_msg_dialog("Error","Error opening file!");
        return;
    }

    QTextStream file_data(&file);
    QString file_contents = file_data.readAll();
    file.close();

    QTextEdit * txt_edit = m_main_window->getTextEdit();

    if(txt_edit){
        txt_edit->setPlainText(file_contents);
        m_main_window->setWindowTitle(QFileInfo(file_path).fileName());
    }else {
        CodeLibrary::display_msg_dialog("Error","Editor is uninitialized!");
    }
}


void CodeLibrary::save_document(){
    QString file_path = QFileDialog::getSaveFileName(m_main_window, "Save Document","C:/Documents","*.txt");

    if(file_path.isEmpty()){
        CodeLibrary::display_msg_dialog("Error","Provide a title");
    }

    QFile file(file_path);

    if(!file.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate)){
        CodeLibrary::display_msg_dialog("Error","Something wrong occurred. Try again later!");
    }

    QTextStream file_data(&file);

    QTextEdit * txt_edit = m_main_window->getTextEdit();
    if(txt_edit){
        file_data<<txt_edit->toPlainText();
        file.close();
    }
    m_main_window->setWindowTitle(QFileInfo(file_path).fileName());

}

void CodeLibrary::show_info(){
    CodeLibrary::display_msg_dialog("Info","This is my very first GUI application in C++ and Qt. More are on the way!");
}

void CodeLibrary::page_setup(){

}
void CodeLibrary::print_doc(){

}

void CodeLibrary::display_msg_dialog(const QString &event_result,const QString &dialog_msg){
    static QMap<QString, ProcessResult> results_map = {
        {"Success", SUCCESS},{"Error",FAILURE},{"Permdenied",PERMISSION_DENIED},{"Info",INFORMATION}
    };

    QString result_input = event_result;
    ProcessResult res = UNKNOWN_ERROR;
    auto it = results_map.find(event_result);
    if(it != results_map.end()){
        res = results_map[result_input];
    }
    switch (res) {
    case SUCCESS:
        QMessageBox::information(m_main_window,event_result,dialog_msg);
        break;
    case FAILURE:
        QMessageBox::critical(m_main_window,event_result,dialog_msg);
        break;
    case PERMISSION_DENIED:
        QMessageBox::warning(m_main_window, event_result, dialog_msg);
        break;
    case INFORMATION:
        QMessageBox::information(m_main_window,event_result,dialog_msg);
        break;
    default:
        break;
    }
}
