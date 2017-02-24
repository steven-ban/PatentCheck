#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "dialog2.h"
#include "ui_dialog2.h"
#include "dialog3.h"
#include "ui_dialog3.h"

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
    connect(ui->actionSubtitles, SIGNAL(triggered()), \
            this, SLOT(changeSubtitlesOptions()));
    connect(ui->parseFiguresButton, SIGNAL(clicked()), \
            this, SLOT(parseFigures()));



    QSettings settings("SIPO", "DescriptionCheck");
    this->despSensWords = settings.value("DespSensWords").toStringList();
    this->misspellingWords = settings.value("MisspellingWords").toMap();
    this->subtitles = settings.value("Subtitles").toStringList();
}

void MainWindow::parseFigures(){
    QString rawText = ui->textEdit->toPlainText();
    qDebug()<<"text length: "<<rawText.length();
    if(rawText.isEmpty()){
        return;
    }
    QTextCharFormat fmt4;
    fmt4.setBackground(QBrush(QColor(255, 102, 153)));
    QTextCursor cursor4(ui->textEdit->document());
    while(!cursor4.isNull() && !cursor4.atEnd()){
        qDebug()<<"current position: "<<cursor4.position();
        cursor4 = ui->textEdit->document()->find(\
                                /* QRegularExpression("图\\d{1,2}\\({0,1}\\w{0,2}\\){0,1}"), \ */
                                QRegularExpression(QString::fromLatin1("\u56fe\\d{1,2}")),
                                /*QRegularExpression("\\[\\d{4}\\]"), */
                                cursor4);
        if(!cursor4.isNull()){
            cursor4.movePosition(QTextCursor::NextCharacter, \
                                 QTextCursor::KeepAnchor, \
                                 4);
            cursor4.setCharFormat(fmt4);
            qDebug()<<cursor4.selectedText();
            this->figureSet.insert(cursor4.selectedText());
        }
    }

}

void MainWindow::changeSubtitlesOptions(){
    Dialog3 dialog3(this);
    dialog3.exec();

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

    QTextCharFormat fmt, fmt2, fmt3;  // sensitive words, misspellings words background
    fmt.setBackground(QBrush(QColor(255, 255, 0)));
    fmt2.setBackground(QBrush(QColor(255, 160, 122)));
    fmt3.setBackground(QBrush(QColor(0, 153, 51)));
    // sensitive words
    for(auto iter = this->despSensWords.constBegin(); \
        iter != this->despSensWords.constEnd();
        ++iter){
        qDebug()<<"sensitive words: "<<*iter;
        // qDebug()<<"text: "<<ui->textEdit->toPlainText();

        QTextCursor newCursor(ui->textEdit->document());
        // parsing sensitive words
        qDebug()<<"cursor position: "<<newCursor.position();
        while(!newCursor.isNull() && !newCursor.atEnd()){
            newCursor = ui->textEdit->document()->find(*iter, newCursor);

            qDebug()<<"newCursor is null? "<<newCursor.isNull();
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
        QTextCursor newCursor2(ui->textEdit->document());
        while(!newCursor2.isNull() && !newCursor2.atEnd()){
            newCursor2 = ui->textEdit->document()->find(iter2.key(), newCursor2);


            if(!newCursor2.isNull()){
                QTextCursor paraCursor = newCursor2;
                paraCursor.movePosition(QTextCursor::StartOfBlock, \
                                        QTextCursor::MoveAnchor);
                paraCursor.movePosition(QTextCursor::NextCharacter, \
                                        QTextCursor::KeepAnchor, \
                                        6);
                QString curPara = paraCursor.selectedText();

                newCursor2.movePosition(QTextCursor::NextCharacter, \
                                       QTextCursor::KeepAnchor, \
                                       iter2.key().length()/2);
                newCursor2.setCharFormat(fmt2);

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

    // process subtitle check
    for(auto iter3 = this->subtitles.constBegin(); \
        iter3 != this->subtitles.constEnd(); \
        ++iter3){
        QTextCursor cursor3(ui->textEdit->document());
        while(!cursor3.isNull() && !cursor3.atEnd()){
            cursor3 = ui->textEdit->document()->find(*iter3, cursor3);
            if(!cursor3.isNull()){
                cursor3.movePosition(QTextCursor::NextCharacter, \
                                     QTextCursor::KeepAnchor, \
                                     (*iter3).length()/2);
                cursor3.setCharFormat(fmt3);
            }
        }
    }



    ui->textEdit->update();

}

MainWindow::~MainWindow()
{
    delete ui;
}
