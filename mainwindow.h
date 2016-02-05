#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QToolBar>
#include<QAction>
#include<QString>
#include<QListWidget>
#include<QHBoxLayout>

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
    QTextEdit* textEdit;
    QString curFile;
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* toolsMenu;
    QMenu* helpMenu;
    QMenu* runMenu;
    QAction* openAct;
    QToolBar* toolBar;
    QAction* aboutAct;
    QAction* checkAct;
    QAction* saveAct;
    QListWidget* matchWidget;
    QString text;
    QHBoxLayout* centerLayout;

private slots:
    void showAbout();
    void check();
    bool saveFile();
    void updateText();

};

#endif // MAINWINDOW_H
