#include "dialog.h"
#include "ui_dialog.h"

#include<QSettings>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QSettings settings("SIPO", "DescriptionCheck");
    this->despSensWords = settings.value("DespSensWords").toStringList();

    this->ui->listWidget->addItems(this->despSensWords);
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addSensWord()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteSensWord()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), \
            this, SLOT(selectSensWord(QListWidgetItem*)));
}

void Dialog::addSensWord(){
    QString sensWord = ui->lineEdit->text();
    if(!sensWord.isEmpty()){
        this->despSensWords.append(sensWord);
    }
    this->ui->listWidget->addItem(sensWord);

}

void Dialog::selectSensWord(QListWidgetItem* item){
    this->curSensWord = item->text();
    this->curSensWordIndex = ui->listWidget->currentRow();
    ui->deleteButton->setEnabled(true);

}

void Dialog::deleteSensWord(){
    this->despSensWords.removeAll(curSensWord);
    ui->listWidget->takeItem(this->curSensWordIndex);

}

Dialog::~Dialog()
{
    QSettings settings("SIPO", "DescriptionCheck");
    settings.setValue("DespSensWords", this->despSensWords);

    delete ui;
}
