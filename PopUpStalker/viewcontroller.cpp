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
    setView(firstTab);
    firstTab->setViewController(this);
    firstScroll->setWidget(firstTab);
    tabWidget->addTab(firstScroll, QWidget::tr("Main"));
    setModel(new Model());
    getModel()->setViewController(this);

    prev = new GuiButton("Prev");
    next = new GuiButton("Next");

    setGridInfo(prev, 4, 0);
    setGridInfo(next, 4, 4);



    QObject::connect(prev, SIGNAL(clicked()),
                     getModel(), SLOT(prevClicked()));

    QObject::connect(next, SIGNAL(clicked()),
                     getModel(), SLOT(nextClicked()));


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
    if (this->view)
        delete this->view;
    this->view = view;
}

void ViewController::setModel(Model *model)
{
    if (this->model)
        delete this->model;
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

void ViewController::setGridInfo(QWidget *label, int row, int col)
{
    if (!view)
        return;
    view->setGridInfo(label, row, col);
}

void ViewController::setNames(std::list<QLabel*> *labels)
{
    if (!view)
        return;
    view->setNames(labels);
}

void ViewController::setLats(std::list<QLabel*> *labels)
{
    if (!view)
        return;
    view->setLats(labels);
}

void ViewController::setLongs(std::list<QLabel*> *labels)
{
    if (!view)
        return;
    view->setLongs(labels);
}

void ViewController::setImgs(std::list<QLabel*> *labels)
{
    if (!view)
        return;
    view->setImgs(labels);
}

