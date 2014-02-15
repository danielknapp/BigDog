#include "viewcontroller.h"
#include <QScrollArea>
#include <QWidget>



ViewController::ViewController() :
    view(0),
    model(0)
{
}

//ViewController::ViewController(MainTab *view, Model *model) :
//    view(view),
//    model(model)
//{
//}

ViewController::~ViewController()
{
    delete mainWin;
    delete listScrollTabs;
}

void ViewController::setUpBigDog()
{
    mainWin = new MainWindow();
    listScrollTabs = new std::list<QScrollArea*>();
    tabWidget = new QTabWidget(mainWin);

    QScrollArea *firstScroll = new QScrollArea();
    listScrollTabs->push_back(firstScroll);
    firstScroll->setBackgroundRole(QPalette::Dark);
    firstScroll->setWidgetResizable(true);
    MainTab * firstTab = (new MainTab())->setupAsFirstTab();
    view = firstTab;
    firstScroll->setWidget(firstTab);
    tabWidget->addTab(firstScroll, QWidget::tr("Main"));

    QScrollArea *secondScroll = new QScrollArea();
    listScrollTabs->push_back(secondScroll);
    secondScroll->setBackgroundRole(QPalette::Light);
    secondScroll->setWidgetResizable(true);
    MainTab * secondTab = new MainTab();
    secondScroll->setWidget(secondTab);
    tabWidget->addTab(secondScroll, QWidget::tr("Second Tab"));

    mainWin->setCentralWidget(tabWidget);

    mainWin->showMaximized();
}

void ViewController::setView(MainTab *view)
{
    this->view = view;
}

void ViewController::setModel(Model *model)
{
    this->model = model;
}

MainTab* ViewController::getView()
{
    return view;
}

Model* ViewController::getModel()
{
    return model;
}

void ViewController::addRow(std::list<QLabel*> *lst)
{
    if (!view)
        return;
    view->addRow(lst);
}

