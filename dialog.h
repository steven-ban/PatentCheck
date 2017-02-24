#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QListWidgetItem>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QStringList despSensWords;
    QString curSensWord;
    int curSensWordIndex;



private slots:
    void addSensWord();
    void selectSensWord(QListWidgetItem*);
    void deleteSensWord();
};

#endif // DIALOG_H
