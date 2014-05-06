#include "maintab.h"

#include <QString>
#include <QLabel>

MainTab::MainTab(QWidget *parent)
    : QWidget(parent),
      mainLayout(new QGridLayout(this))
{
    mainLayout->setHorizontalSpacing(30);
    mainLayout->setVerticalSpacing(20);
}

/**
 * @brief MainTab::setupAsFirstTab
 *      Sets up specifically how we would want the first
 *      tab of BigDog to look
 * @return
 *      A pointer to itself
 */
MainTab* MainTab::setupAsFirstTab()
{
    this->addColumn("Name1", 0);
    this->addColumn("Name2");
    this->addColumn("Name3");
    this->addColumn("Name4");
    this->addColumn("Name5");

    std::list<QLabel*> * lst = new std::list<QLabel*>();
    QLabel *r1 = new QLabel("Lat1");
    QLabel *r2 = new QLabel("Lat2");
    QLabel *r3 = new QLabel("Lat3");
    QLabel *r4 = new QLabel("Lat4");
    QLabel *r5 = new QLabel("Lat5");
    lst->push_back(r1);
    lst->push_back(r2);
    lst->push_back(r3);
    lst->push_back(r4);
    lst->push_back(r5);
    this->setRowInfo(lst,1);
    lst->clear();


    r1 = new QLabel("Lon1");
    r2 = new QLabel("Lon2");
    r3 = new QLabel("Lon3");
    r4 = new QLabel("Lon4");
    r5 = new QLabel("Lon5");
    lst->push_back(r1);
    lst->push_back(r2);
    lst->push_back(r3);
    lst->push_back(r4);
    lst->push_back(r5);
    this->setRowInfo(lst,2);
    lst->clear();


    r1 = new QLabel();
    r2 = new QLabel();
    r3 = new QLabel();
    r4 = new QLabel();
    r5 = new QLabel();
    r1->setPixmap(QPixmap("C:\\Users\\danny_000\\Downloads\\targets"
                         "\\targets\\YNBGC\\1725601677_c.png").scaledToWidth(200));
    r2->setPixmap(QPixmap("C:\\Users\\danny_000\\Downloads\\targets"
                         "\\targets\\YNBGC\\1725601677_c.png").scaledToWidth(200));
    r3->setPixmap(QPixmap("C:\\Users\\danny_000\\Downloads\\targets"
                         "\\targets\\YNBGC\\1725601677_c.png").scaledToWidth(200));
    r4->setPixmap(QPixmap("C:\\Users\\danny_000\\Downloads\\targets"
                         "\\targets\\YNBGC\\1725601677_c.png").scaledToWidth(200));
    r5->setPixmap(QPixmap("C:\\Users\\danny_000\\Downloads\\targets"
                         "\\targets\\YNBGC\\1725601677_c.png").scaledToWidth(200));
    lst->push_back(r1);
    lst->push_back(r2);
    lst->push_back(r3);
    lst->push_back(r4);
    lst->push_back(r5);
    this->setRowInfo(lst,3);

    delete lst;


    return this;
}

/**
 * @brief MainTab::addColumn
 *      Adds a column to mainLayout using a QLabel
 * @param label
 *      The string to be displayed in QLabel
 */
void MainTab::addColumn(const char* label)
{
    int cols = mainLayout->columnCount();
    addColumn(label, cols);
}

/**
 * @brief MainTab::addColumn
 *      Adds a column to mainLayout using a QLabel
 *      to a specific column
 * @param label
 *      The string to be displayed in QLabel
 * @param col
 *      The column to add the QLabel to
 */
void MainTab::addColumn(const char* label, int col)
{
    QLabel * newLabel = new QLabel(label);
    QFont f( "Arial", 20, QFont::Bold);
    newLabel->setFont( f);

    mainLayout -> addWidget(newLabel, 0, col);
}

/**
 * @brief MainTab::addRow
 *      Adds a row to mainLayout using the given
 *      list of QLabels
 * @param labels
 *      The list of QLabels to go into the row
 */
void MainTab::addRow(std::list<QLabel*> *labels)
{
    int rows = mainLayout->rowCount();
    if (rows < 0)
        rows = 0;
    int i = 0;
    for (std::list<QLabel*>::iterator start = labels->begin();
         start != labels->end(); start++)
    {
        mainLayout->addWidget( *start , rows, i);
        i++;
    }
}

void MainTab::setRowInfo(std::list<QLabel*> *labels, int row)
{
    if (row < 0)
        row = 0;

    int i = 0;
    for (std::list<QLabel*>::iterator start = labels->begin();
         start != labels->end(); start++)
    {
        mainLayout->addWidget( *start , row, i);
        i++;
    }
}

void MainTab::setNames(std::list<QLabel*> *labels)
{
    setRowInfo(labels, 0);
}

void MainTab::setLats(std::list<QLabel*> *labels)
{
    setRowInfo(labels, 1);
}

void MainTab::setLongs(std::list<QLabel*> *labels)
{
    setRowInfo(labels, 2);
}

void MainTab::setImgs(std::list<QLabel*> *labels)
{
    setRowInfo(labels, 3);
}

void MainTab::setStalkerLabels(std::vector<StalkerLabels*> *labels)
{
    int i = 0;
    for (std::vector<StalkerLabels*>::iterator start = labels->begin();
         start != labels->end(); start++)
    {
        StalkerLabels *tmp = *start;
        mainLayout->addWidget( tmp->getName() , 0 , i);
        mainLayout->addWidget( tmp->getLat() , 1 , i);
        mainLayout->addWidget( tmp->getLon() , 2 , i);
        mainLayout->addWidget( tmp->getPMap() , 3 , i);

        i++;
    }
}


ViewController* MainTab::getViewController()
{
    return vc;
}


void MainTab::setViewController(ViewController* vc)
{
    this->vc = vc;
}




//void MainTab::mousePressEvent(QMouseEvent *event)
//{
//    QWidget::mousePressEvent(event);
//    if (event->button() == Qt::LeftButton)
//    {
//        printf("Clicked!\n");
//    }
//}

