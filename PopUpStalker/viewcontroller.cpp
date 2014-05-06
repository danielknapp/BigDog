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

/**
 * @brief ViewController::setUpStalker
 *      Set up a MainWindow to display everything on and create
 *      the necessary QTabWidget to hold the tabs to be displayed
 *      on PopUpStalker.
 */
void ViewController::setUpStalker()
{
    mainWin = new MainWindow();
    listScrollTabs = new std::list<QScrollArea*>();
    tabWidget = new QTabWidget(mainWin);

    // Sets up the first tab to be scrollable
    QScrollArea *firstScroll = new QScrollArea();
    listScrollTabs->push_back(firstScroll);
    firstScroll->setBackgroundRole(QPalette::Dark);
    firstScroll->setWidgetResizable(true);
    MainTab * firstTab = (new MainTab())->setupAsFirstTab();
    view = firstTab;
    firstScroll->setWidget(firstTab);
    tabWidget->addTab(firstScroll, QWidget::tr("Main"));

    // Sets up the second tab to be scrollable
//    QScrollArea *secondScroll = new QScrollArea();
//    listScrollTabs->push_back(secondScroll);
//    secondScroll->setBackgroundRole(QPalette::Light);
//    secondScroll->setWidgetResizable(true);
//    MainTab * secondTab = new MainTab();
//    secondScroll->setWidget(secondTab);
//    tabWidget->addTab(secondScroll, QWidget::tr("Second Tab"));

    // Display tabWidget on the MainWindow
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

/**
 * @brief ViewController::addRow
 *      Delegate the addition of the row to the view.
 * @param lst
 *      Pass the list of QLabels to the view.
 */
void ViewController::addRow(std::list<QLabel*> *lst)
{
    if (!view)
        return;
    view->addRow(lst);
}

void ViewController::setNames(std::list<QLabel*> *labels)
{
    view->setNames(labels);
}

void ViewController::setLats(std::list<QLabel*> *labels)
{
    view->setLats(labels);
}

void ViewController::setLongs(std::list<QLabel*> *labels)
{
    view->setLongs(labels);
}

void ViewController::setImgs(std::list<QLabel*> *labels)
{
    view->setImgs(labels);
}

