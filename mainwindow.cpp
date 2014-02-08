#include "mainwindow.h"
#include "maintab.h"

#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QTabBar>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tabWidget = new QTabWidget;

    QScrollArea *firstScroll = new QScrollArea();
    firstScroll->setBackgroundRole(QPalette::Dark);
    MainTab * firstTab = (new MainTab())->setupAsFirstTab();
    firstScroll->setWidget(firstTab);

    tabWidget->addTab(firstScroll, tr("Main"));
    tabWidget->addTab(new MainTab(), tr("Second Tab"));

    QAction *newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    QAction *openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();

    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);

    setCentralWidget(tabWidget);
}

MainWindow::~MainWindow()
{

}

QTabWidget* MainWindow::getTabBar()
{
    return tabWidget;
}
