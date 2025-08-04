#include "codelibrary.h"
#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QLabel>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QRegularExpression>
#include <QString>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>

//menu actions
enum ActionTypes{
    NEW, SAVE, SAVE_AS, OPEN,
    EXIT, UNDO, REDO, PASTE,
    CUT, COPY, PRINT, PAGE_SETUP,
    ABOUT, INFO, INCREASE_FNT_SZ,DECREASE_FNT_SZ,
    ITALICS, BOLD, UNDERLINE,
    CENTER_ALIGNMENT, LEFT_ALIGNMENT, RIGHT_ALIGNMENT,
    JUSTIFIED_ALIGNMENT, UNKNOWN_CMD
};

//results from process execution
enum ProcessResult{
    SUCCESS, FAILURE, PERMISSION_DENIED, INFORMATION, UNKNOWN_ERROR
};

CodeLibrary::CodeLibrary(QObject * parent, MainWindow * main_window): QObject(parent), m_main_window(main_window) {
    if(m_main_window){
        txt_edit = m_main_window->getTextEdit();
        if(!txt_edit){
            qWarning()<<"Text Edit is null";
        }
    }else{
        qWarning()<<"Null Window!";
    }

}

QAction* CodeLibrary::action_handler(QMenu * menu_bar, const QString &menu_item, const QString &status_tip){
    QAction * action = menu_bar->addAction(menu_item);
    QTextEdit * txt_edit = m_main_window->getTextEdit();

    static QMap<QString, ActionTypes> action_maps = {
                                                     {"New", NEW},{"Save", SAVE},{"Save As", SAVE_AS},
                                                     {"Open", OPEN},{"Exit", EXIT},{"Undo", UNDO},{"Redo",REDO},
                                                     {"Paste", PASTE},{"Cut", CUT},{"Copy", COPY},{"Print",PRINT},
                                                     {"Page Setup", PAGE_SETUP},{"About", ABOUT},{"Info", INFO},
                                                     {"Increase Font", INCREASE_FNT_SZ},{"Decrease Font", DECREASE_FNT_SZ},
                                                     {"Italics", ITALICS},{"Bold", BOLD},{"Underline", UNDERLINE},
                                                     {"Center", CENTER_ALIGNMENT},{"Left", LEFT_ALIGNMENT},{"Right", RIGHT_ALIGNMENT},
                                                     {"Justify", JUSTIFIED_ALIGNMENT}};

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
        break;
    case CUT:
        action->setShortcut(QKeySequence::Cut);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::cut);
        break;
    case COPY:
        action->setShortcut(QKeySequence::Copy);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::copy);
        break;
    case PASTE:
        action->setShortcut(QKeySequence::Paste);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::paste);
        break;
    case UNDO:
        action->setShortcut(QKeySequence::Undo);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::undo);
        break;
    case REDO:
        action->setShortcut(QKeySequence::Redo);
        QObject::connect(action, &QAction::triggered, txt_edit, &QTextEdit::redo);
        break;
    case INCREASE_FNT_SZ:
        action->setShortcut(QKeySequence("CTRL++"));
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::increase_font);
        break;
    case DECREASE_FNT_SZ:
        action->setShortcut(QKeySequence("CTRL+-"));
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::decrease_font);
        break;
    case ITALICS:
        action->setShortcut(QKeySequence("CTRL+I"));
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::toggle_italics);
        break;
    case BOLD:
        action->setShortcut(QKeySequence("CTRL+B"));
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::toggle_bold);
        break;
    case UNDERLINE:
        action->setShortcut(QKeySequence("CTRL+U"));
        QObject::connect(action, &QAction::triggered, this, &CodeLibrary::toggle_underline);
        break;
    case CENTER_ALIGNMENT:
        action->setShortcut(QKeySequence("CTRL+E"));
        QObject::connect(action, &QAction::triggered, this, [this](){CodeLibrary::toggle_alignments(Qt::AlignCenter);});
        break;
    case LEFT_ALIGNMENT:
        action->setShortcut(QKeySequence("CTRL+L"));
        QObject::connect(action, &QAction::triggered, this, [this](){CodeLibrary::toggle_alignments(Qt::AlignLeft);});
        break;
    case RIGHT_ALIGNMENT:
        action->setShortcut(QKeySequence("CTRL+R"));
        QObject::connect(action, &QAction::triggered, this, [this](){CodeLibrary::toggle_alignments(Qt::AlignRight);});
        break;
    case JUSTIFIED_ALIGNMENT:
        action->setShortcut(QKeySequence("CTRL+J"));
        QObject::connect(action, &QAction::triggered, this, [this](){CodeLibrary::toggle_alignments(Qt::AlignJustify);});
    default:
        break;
    }
    return action;
}

void CodeLibrary::increase_font(){
    QTextEdit * txt_edit = m_main_window->getTextEdit();

    QFont font = txt_edit->font();
    int curr_size = font.pointSize();
    font.setPointSize(curr_size+1);
    txt_edit->setFont(font);

}

void CodeLibrary::decrease_font(){
    QTextEdit * txt_edit = m_main_window->getTextEdit();
    QFont font = txt_edit->font();

    int curr_size = font.pointSize();
    font.setPointSize(curr_size-1);
    txt_edit->setFont(font);
}

void CodeLibrary::toggle_italics(){
    QTextEdit * txt_edit = m_main_window->getTextEdit();

    QTextCharFormat char_fmt;
    char_fmt.setFontItalic(!txt_edit->fontItalic());

    QTextCursor cursor = txt_edit->textCursor();
    cursor.mergeCharFormat(char_fmt);

    txt_edit->mergeCurrentCharFormat(char_fmt);
}

void CodeLibrary::toggle_bold(){
    QTextEdit * txt_edit = m_main_window->getTextEdit();

    int currWeight = txt_edit->fontWeight();

    QTextCharFormat fmt;

    //if the current font weight is greater than normal, pass the weight to be normal
    if(currWeight > QFont::Normal){
        fmt.setFontWeight(QFont::Normal);
    }else{
        //otherwise bold the text
        fmt.setFontWeight(QFont::Bold);
    }

    QTextCursor cursor = txt_edit->textCursor();
    cursor.mergeCharFormat(fmt);
    txt_edit->mergeCurrentCharFormat(fmt);
}

void CodeLibrary::toggle_alignments(Qt::Alignment alignment){
    QTextEdit * txt_edit = m_main_window->getTextEdit();
    txt_edit->setAlignment(alignment);
}

void CodeLibrary::word_counter(){
    QTextEdit * txt_edit = m_main_window->getTextEdit();
    static QRegularExpression separator("\\s+");
    QString text = txt_edit->toPlainText();
    QStringList words = text.split(separator, Qt::SkipEmptyParts);
    int wordCount = words.size();
    QLabel * wordCounter = m_main_window->getWordCounter();
    wordCounter->setText(QString("Words: %1").arg(wordCount));
}

void CodeLibrary::toggle_underline(){
    bool isUnderlined = txt_edit->fontUnderline();
    QTextEdit * txt_edit = m_main_window->getTextEdit();

    QTextCharFormat fmt;
    fmt.setFontUnderline(!isUnderlined);

    QTextCursor cursor = txt_edit->textCursor();
    cursor.mergeCharFormat(fmt);
    txt_edit->mergeCurrentCharFormat(fmt);
}

void CodeLibrary::new_document(){
    if(m_main_window){
        QTextEdit * txt_edit = m_main_window->getTextEdit();
        if(txt_edit){
            txt_edit->clear();
            MainWindow * new_window = new MainWindow();

            new_window->setAttribute(Qt::WA_DeleteOnClose);
            new_window->show();
        }
    }
}

void CodeLibrary::save_document_as(){
    QString file_path = QFileDialog::getSaveFileName(m_main_window,"Save Document","C:/Documents","*.txt");

    if(file_path.isEmpty()){
        CodeLibrary::display_msg_dialog("Error","Something went wrong.");
    }
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Truncate|QIODevice::Text)){
        CodeLibrary::display_msg_dialog("Error","Something went wrong.");
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


bool CodeLibrary::save_document(){
    QString file_path = QFileDialog::getSaveFileName(m_main_window, "Save Document","C:/Documents","*.txt");

    if(file_path.isEmpty()){
        CodeLibrary::display_msg_dialog("Error","Provide a title");
        return false;
    }

    QFile file(file_path);

    if(!file.open(QIODevice::Text|QIODevice::WriteOnly|QIODevice::Truncate)){
        CodeLibrary::display_msg_dialog("Error","Something wrong occurred. Try again later!");
        return false;
    }

    QTextStream file_data(&file);

    QTextEdit * txt_edit = m_main_window->getTextEdit();
    if(txt_edit){
        file_data<<txt_edit->toPlainText();
        file.close();
    }
    m_main_window->setWindowTitle(QFileInfo(file_path).fileName());
    return true;
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
