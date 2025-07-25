#include "codelibrary.h"

CodeLibrary::CodeLibrary(QWidget *parent): QMainWindow(parent){
    save_action = new QAction(QIcon::fromTheme("document-save",QIcon(":/icons/open.png")), tr("&Open"), this);
    save_action->setShortcut(QKeySequence::Save);
    save_action->setStatusTip("Save current document");

    toolbar = addToolBar(tr("ToolBar"));

    toolbar->addAction(save_action);

}
