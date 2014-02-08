#include "mainwindow.h"
#include "maintab.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new MainTab(), tr("Main"));
    tabWidget->addTab(new MainTab(), tr("Second Tab"));

    setCentralWidget(tabWidget);
}

MainWindow::~MainWindow()
{

}
