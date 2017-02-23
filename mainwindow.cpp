#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

#include<QSettings>
#include<QtDebug>
#include<QTextCharFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Options, SIGNAL(triggered()), this, SLOT(changeOptions()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(checkDescription()));

    QSettings settings("SIPO", "DescriptionCheck");
    this->despSensWords = settings.value("DespSensWords").toStringList();

}

void MainWindow::changeOptions(){
    Dialog dialog(this);
    dialog.exec();

}

void MainWindow::checkDescription(){
    QString rawText = ui->textEdit->toPlainText();
    if(rawText.isEmpty()){
        return;
    }

    QTextCharFormat fmt;
    fmt.setBackground(QBrush(QColor(255, 255, 0)));
    for(auto iter = this->despSensWords.constBegin(); \
        iter != this->despSensWords.constEnd();
        ++iter){
        // qDebug()<<"sensitive words: "<<*iter<<"\n";
        // qDebug()<<"text: "<<ui->textEdit->toPlainText();

        QTextCursor newCursor(ui->textEdit->document());
        while(!newCursor.isNull() && !newCursor.atEnd()){
            newCursor = ui->textEdit->document()->find(*iter, newCursor);
            if(!newCursor.isNull()){
                newCursor.movePosition(QTextCursor::WordRight,
                                       QTextCursor::KeepAnchor);
                newCursor.mergeBlockCharFormat(fmt);
                QString log(*iter);
                log.append("appears in paragraph...");
                ui->listWidget->addItem(log);
            }
        }

    }
    ui->textEdit->update();

}

MainWindow::~MainWindow()
{
    delete ui;
}
