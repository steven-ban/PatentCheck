#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "dialog2.h"
#include "ui_dialog2.h"

#include<QSettings>
#include<QtDebug>
#include<QTextCharFormat>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Options, SIGNAL(triggered()), this, SLOT(changeSensitiveWordsOptions()));
    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(checkDescription()));
    connect(ui->action_Misspelling_Words, SIGNAL(triggered()), \
            this, SLOT(changeMisspellingOptions()));


    QSettings settings("SIPO", "DescriptionCheck");
    this->despSensWords = settings.value("DespSensWords").toStringList();
    this->misspellingWords = settings.value("MisspellingWords").toMap();

}

void MainWindow::changeMisspellingOptions(){
    Dialog2 dialog2(this);
    dialog2.exec();
}

void MainWindow::changeSensitiveWordsOptions(){
    Dialog dialog(this);
    dialog.exec();

}

void MainWindow::checkDescription(){
    QString rawText = ui->textEdit->toPlainText();
    if(rawText.isEmpty()){
        return;
    }

    ui->listWidget->clear();
    QColor defaultColor = ui->textEdit->textBackgroundColor();
    ui->textEdit->setTextBackgroundColor(defaultColor);

    QTextCharFormat fmt, fmt2;  // sensitive words, misspellings words background
    fmt.setBackground(QBrush(QColor(255, 255, 0)));
    fmt2.setBackground(QBrush(QColor(255, 160, 122)));
    // sensitive words
    for(auto iter = this->despSensWords.constBegin(); \
        iter != this->despSensWords.constEnd();
        ++iter){
        // qDebug()<<"sensitive words: "<<*iter<<"\n";
        // qDebug()<<"text: "<<ui->textEdit->toPlainText();

        QTextCursor newCursor(ui->textEdit->document());
        // parsing sensitive words
        while(!newCursor.isNull() && !newCursor.atEnd()){
            newCursor = ui->textEdit->document()->find(*iter, newCursor);

            if(!newCursor.isNull()){
                // find current paragraph
                QTextCursor paraCursor = newCursor;
                paraCursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                paraCursor.movePosition(QTextCursor::NextCharacter, \
                                        QTextCursor::KeepAnchor, \
                                        6);
                QString curPara = paraCursor.selectedText();

                qDebug()<<"position before move: "<<newCursor.position();
                newCursor.movePosition(QTextCursor::NextCharacter,
                                       QTextCursor::KeepAnchor,
                                       (*iter).length()/2);   // move position by character
                qDebug()<<"sensitive word length: "<<(*iter).length();
                qDebug()<<"selected text: "<<newCursor.selectedText();
                newCursor.setCharFormat(fmt);
                qDebug()<<"position after move: "<<newCursor.position();
                QString log(*iter);
                log.append(tr("appears in paragraph "));
                log.append(curPara);
                ui->listWidget->addItem(log);
            }
        }
    }

    // misspelling words
    for(auto iter2 = this->misspellingWords.constBegin();\
        iter2 != this->misspellingWords.constEnd();\
        ++iter2){
        QTextCursor newCursor(ui->textEdit->document());
        while(!newCursor.isNull() && !newCursor.atEnd()){
            newCursor = ui->textEdit->document()->find(iter2.key(), newCursor);


            if(!newCursor.isNull()){
                QTextCursor paraCursor = newCursor;
                paraCursor.movePosition(QTextCursor::StartOfBlock, \
                                        QTextCursor::MoveAnchor);
                paraCursor.movePosition(QTextCursor::NextCharacter, \
                                        QTextCursor::KeepAnchor, \
                                        6);
                QString curPara = paraCursor.selectedText();

                newCursor.movePosition(QTextCursor::NextCharacter, \
                                       QTextCursor::KeepAnchor, \
                                       iter2.key().length()/2);
                newCursor.setCharFormat(fmt2);

                QString log(iter2.key());
                log.append(tr(" is a misspelling of "));
                log.append(iter2.value().toString());
                log.append(" in paragraph ");
                log.append(curPara);
                log.append(".");
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
