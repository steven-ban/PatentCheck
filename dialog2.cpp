#include "dialog2.h"
#include "ui_dialog2.h"

#include<QSettings>
#include<QString>
#include<QDebug>
#include<QTableWidgetItem>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), \
            this, SLOT(addMisspellingWord()));
    connect(ui->deleteButton, SIGNAL(clicked()), \
            this, SLOT(deleteMisspellingWord()));

    QSettings settings("SIPO", "DescriptionCheck");
    this->misspellingWords = settings.value("MisspellingWords").toMap();

    // init tablewidget
    ui->tableWidget->setRowCount(this->misspellingWords.size() + 1);
    ui->tableWidget->setColumnCount(2);

    // set header of tablewidget
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Misspelling Word")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Correct Spelling")));
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);


    // load misspelling words read from settings file
    int i = 0;
    for(auto iter = this->misspellingWords.constBegin();
        iter != this->misspellingWords.constEnd();
        ++iter){
        // ui->tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem(i));

        ui->tableWidget->setItem(i , 0, new QTableWidgetItem(iter.key()));
        ui->tableWidget->setItem(i , 1, new QTableWidgetItem(iter.value().toString()));

        ++i;
    }

}

void Dialog2::deleteMisspellingWord(){

}

void Dialog2::addMisspellingWord(){
    QString curMisspellingWord = ui->lineEdit->text();
    QString curCorrectSpellingWord = ui->lineEdit_2->text();
    if(curMisspellingWord.isEmpty() || curCorrectSpellingWord.isEmpty()){
        return;
    } else {
        this->misspellingWords.insert(curMisspellingWord, curCorrectSpellingWord);
        qDebug()<<"tablewidget row count: "<<ui->tableWidget->rowCount();
        qDebug()<<"misspelling word to add: "<<curMisspellingWord<<"\t"<<curCorrectSpellingWord;
        ui->tableWidget->setItem(ui->tableWidget->rowCount(), \
                                 0, \
                                 new QTableWidgetItem(curMisspellingWord));
        ui->tableWidget->setItem(ui->tableWidget->rowCount(), \
                                 1,
                                 new QTableWidgetItem(curCorrectSpellingWord));
        ui->tableWidget->setRowCount((ui->tableWidget->rowCount() + 1));
        ui->tableWidget->update();

    }
}

Dialog2::~Dialog2()
{
    QSettings settings("SIPO", "DescriptionCheck");
    settings.setValue("MisspellingWords", this->misspellingWords);

    delete ui;
}
