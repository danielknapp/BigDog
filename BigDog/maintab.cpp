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
    this->addColumn("Targets", 0);
    this->addColumn("CharType");
    this->addColumn("CharColor");
    this->addColumn("ShapeType");
    this->addColumn("ShapeColor");
    this->addColumn("Latitude");
    this->addColumn("Longitude");

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

