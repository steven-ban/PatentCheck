#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include<QStringList>

namespace Ui {
class Dialog3;
}

class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0);
    ~Dialog3();

private:
    Ui::Dialog3 *ui;
    QStringList subtitles;

private slots:
    void addSubtitle();
    void changeSubtitle();

};

#endif // DIALOG3_H
