#include "maintab.h"

#include <QString>
#include <QLabel>
#include <QVBoxLayout>

MainTab::MainTab(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * initialLayout = new QHBoxLayout;
    initialLayout ->setSizeConstraint(QLayout::SetNoConstraint);
//    setLayout(initialLayout);
    mainLayout = initialLayout;
}

MainTab* MainTab::setupAsFirstTab()
{
    this->addColumn("CharType");
    this->addColumn("CharColor");
    this->addColumn("ShapeType");
    this->addColumn("ShapeColor");

    return this;
}

void MainTab::addColumn(const char* label) {
    QString labelText = "<b>";
    labelText.append(label);
    labelText.append("</b>");

    QLabel * newLabel = new QLabel(labelText);

//    mainLayout->
    mainLayout -> addWidget( newLabel);
}
