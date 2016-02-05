#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>
#include<QTextStream>
#include<QDateTime>
#include<QFile>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<QStringList>
#include<QString>
#include<QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setMinimumSize(800, 600);

    // set text edit area
    textEdit = new QTextEdit(this);
    //centerLayout->addWidget(textEdit);
    setCentralWidget(textEdit);
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(updateText()));

    // initalize matchWidget
    matchWidget = new QListWidget(this);
    matchWidget->setBaseSize(400, 300);
    matchWidget->setVisible(false);
    // set menus and actions
    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));
    runMenu = menuBar()->addMenu(tr("Run"));
    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
    openAct = new QAction(tr("&Open"), this);
    saveAct = new QAction(tr("&Save"), this);
    connect(saveAct, SIGNAL(triggered(bool)), this, SLOT(saveFile()));
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(showAbout()));
    checkAct = new QAction(tr("&Check"), this);
    connect(checkAct, SIGNAL(triggered()), this, SLOT(check()));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    runMenu->addAction(checkAct);
    helpMenu->addAction(aboutAct);

    toolBar = new QToolBar(this);
    toolBar->addAction(openAct);
    toolBar->addAction(tr("&Save"));
    toolBar->addAction(checkAct);
    addToolBar(toolBar);
}

// this function is not coding well, need more check and code
bool MainWindow::saveFile(){

    QFile file;

    this->curFile = QString("Description").append(QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd-hh-mm-ss"));
    file.setFileName(curFile);

    QTextStream out(&file);
    #ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
    #endif
        out << textEdit->toPlainText();
    #ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
    #endif

    return true;

}

void MainWindow::updateText(){
    this->text = textEdit->toPlainText();
}

void MainWindow::check(){
    QRegularExpression re("\\[\\d{4}\\]");
    if(re.isValid()){
    QRegularExpressionMatch matched = re.match(this->text);
    if(matched.hasMatch()){
/*        for(int i = 0; matched.captured(i))
        QStringList::const_iterator matchIter;
        for (matchIter = matched.capturedTexts().constBegin();matchIter != matched.capturedTexts().constEnd();++matchIter){
            QListWidgetItem matchItem(*matchIter, matchWidget);
*/
        QListWidgetItem matchItem(matched.captured(0), matchWidget);



    matchWidget->show();

    }
    else{
        QMessageBox msgBox;
        msgBox.setText(tr("No match found! This text now is") + this->text);
        msgBox.exec();
    }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText(tr("Regular expression invalid!"));
        msgBox.exec();
    }
}

void MainWindow::showAbout()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Patent Check. \n by Steven Ban \n 20160204"));
    msgBox.setDetailedText(tr("You can paste the full descriptiion of your applicatiion, and just click a button, and this application can show the informative messages."));
    msgBox.setInformativeText(tr("This application is coding with Qt5.1.1 and publised with LGPL."));
    msgBox.exec();


}

MainWindow::~MainWindow()
{

}
