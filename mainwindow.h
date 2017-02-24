#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringList>
#include<QAction>
#include<QMap>
#include<QVariant>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList despSensWords;
    QMap<QString, QVariant> misspellingWords;


private slots:
    void checkDescription();
    void changeSensitiveWordsOptions();
    void changeMisspellingOptions();
};

#endif // MAINWINDOW_H
