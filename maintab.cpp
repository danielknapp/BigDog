#include "maintab.h"

#include <QString>
#include <QLabel>

MainTab::MainTab(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    mainLayout ->setSizeConstraint(QLayout::SetNoConstraint);
    setLayout(mainLayout);


    this->addColumn("Char");
    this->addColumn("Color");
    this->addColumn("Shape");
}

void MainTab::addColumn(const char* label) {
    QString labelText = "<b>";
    labelText.append(label);
    labelText.append("</b>");

    QLabel * newLabel = new QLabel(labelText);

    mainLayout -> insertWidget(newLabel);
}
