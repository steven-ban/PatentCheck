#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include<QMap>
#include<QString>
#include<QVariant>

namespace Ui {
class Dialog2;
}

class Dialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0);
    ~Dialog2();

private:
    Ui::Dialog2 *ui;
    QMap<QString, QVariant> misspellingWords;

private slots:
    void addMisspellingWord();
    void deleteMisspellingWord();
};

#endif // DIALOG2_H
