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

MainTab* MainTab::setupAsFirstTab()
{
    this->addColumn("Targets", 0);
    this->addColumn("CharType");
    this->addColumn("CharColor");
    this->addColumn("ShapeType");
    this->addColumn("ShapeColor");

    return this;
}

void MainTab::addColumn(const char* label)
{
//    QString labelText = "<b>";
//    labelText.append(label);
//    labelText.append("</b>");

    QLabel * newLabel = new QLabel(label);

    int cols = mainLayout->columnCount();
    if (cols < 0)
        cols = 1;
    mainLayout -> addWidget(newLabel, 0, cols);
}

void MainTab::addColumn(const char* label, int col)
{
//    QString labelText = "<b>";
//    labelText.append(label);
//    labelText.append("</b>");

    QLabel * newLabel = new QLabel(label);

//    int cols = mainLayout->columnCount();
//    if (cols < 0)
//        cols = 1;
    mainLayout -> addWidget(newLabel, 0, col);
}

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

void MainTab::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        printf("Clicked!\n");
    }
}

