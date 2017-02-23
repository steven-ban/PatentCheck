#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->checkButton, SIGNAL(clicked()), this, SLOT(checkDescription()));

}

void MainWindow::checkDescription(){
    QString rawText = ui->textEdit->toPlainText();
    if(rawText.isEmpty()){
        return;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
