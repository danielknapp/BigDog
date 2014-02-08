#include "mainwindow.h"
#include "maintab.h"
#include <QApplication>
#include <QTableWidget>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Assumed type casting to be correct will seg fault if wrong
    QTabWidget *mainTabWidget = (QTabWidget*)w.centralWidget();
    QScrollArea *firstScroll = (QScrollArea*)mainTabWidget->widget(0);
    MainTab *firstTab = new MainTab();//(MainTab*)firstScroll->widget();

    QLabel * newLabel = new QLabel();
    newLabel->setPixmap(QPixmap("C:/Users/danny_000/Downloads/sampletarget.jpg").scaledToWidth(100));

    QLabel *targets = new QLabel("Targets");
    QLabel *charT = new QLabel("CharType");
    QLabel *charC = new QLabel("CharColor");
    QLabel *shapeT = new QLabel("ShapeType");
    QLabel *shapeC = new QLabel("ShapeColor");

    QGridLayout *mainGrid = new QGridLayout();
    mainGrid->setHorizontalSpacing(30);
    mainGrid->setVerticalSpacing(20);

    mainGrid->addWidget(targets, 0, 0);
    mainGrid->addWidget(charT, 0, 1);
    mainGrid->addWidget(charC, 0, 2);
    mainGrid->addWidget(shapeT, 0, 3);
    mainGrid->addWidget(shapeC, 0, 4);

//    delete(firstTab->layout());
    firstTab->setLayout(mainGrid);
    firstScroll->setWidget(firstTab);

    // It looks like this is the order of operations to update the ScrollArea
    // when a change has been made to the layout of it's child widget
    mainGrid->addWidget(newLabel, 1, 0);
    QWidget *taken = firstScroll->takeWidget();
    taken->show();
    firstScroll->setWidget(taken);
    firstScroll->show();

    w.showMaximized();

    return a.exec();
}
