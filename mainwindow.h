#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTabWidget* getTabBar();


private:
    QTabWidget *tabWidget;
};

#endif // MAINWINDOW_H
