#include "dialog3.h"
#include "ui_dialog3.h"

#include<QSettings>

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
    QSettings settings("SIPO", "DescriptionCheck");
    this->subtitles = settings.value("Subtitles").toStringList();

    ui->listWidget->addItems(this->subtitles);
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addSubtitle()));
    connect(ui->changeButton, SIGNAL(clicked()), \
            this, SLOT(changeSubtitle()));

}

void Dialog3::changeSubtitle(){

}

void Dialog3::addSubtitle(){
    QString subtitle = ui->lineEdit->text();
    if(!subtitle.isEmpty()){
        this->subtitles.append(subtitle);
        ui->listWidget->addItem(subtitle);
    }
}

Dialog3::~Dialog3()
{
    QSettings settings("SIPO", "DescriptionCheck");
    settings.setValue("Subtitles", this->subtitles);

    delete ui;
}
