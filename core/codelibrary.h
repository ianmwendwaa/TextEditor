#ifndef CODELIBRARY_H
#define CODELIBRARY_H

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QTextListFormat>
#include <QTextStream>
#include <QToolBar>

class MainWindow;
class CodeLibrary: public QObject
{
    Q_OBJECT

public:
    explicit CodeLibrary(QObject * parent = nullptr, MainWindow * main_window = nullptr);
    void display_msg_dialog(const QString &event_result,const QString &dialog_msg);
    QAction* action_handler(QMenu * menu_bar, const QString &menu_item, const QString&status_tip);
    QString * getStatusTip()const;

public slots:
    void new_document();
    bool save_document();
    bool save_document_as();
    void open_document();
    void show_info();
    void page_setup();
    void print_doc();

    void increase_font();
    void decrease_font();
    void toggle_bullets();
    void toggle_italics();
    void toggle_bold();
    void toggle_underline();

    void toggle_alignments(Qt::Alignment alignment);

    void word_counter();
private:
    MainWindow * m_main_window;
    QTextEdit * txt_edit = nullptr;
    QString curr_file_path;
};

#endif // CODELIBRARY_H
