#include "mainwindow.h"
#include "maintab.h"
#include "viewcontroller.h"
#include "model.h"

#include <Windows.h>
#include "dirent.h"
//#include <unistd.h>
//#include <sys/stat.h>
//#include <sys/types.h>

#include <sstream>
#include <QApplication>
#include <QTableWidget>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>


//void addLabel(QGridLayout *grid, QLabel *label, QScrollArea *scroll)
//{
//    int rows = grid->rowCount();
//    grid->addWidget(label, rows, 0);
////    QWidget *taken = scroll->takeWidget();
////    taken->show();
////    taken->setParent(scroll);
////    scroll->setWidget(taken);
////    scroll->show();
//}

class ViewController;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewController *vc = new ViewController();

    vc->setUpBigDog();

    std::list<QLabel*> *lst = new std::list<QLabel*>();
    QLabel * newLabel = new QLabel();
    newLabel->setPixmap(QPixmap("C:/Users/danny_000/Downloads/sampletarget.jpg").scaledToWidth(100));
    QLabel *charT = new QLabel("CharType");
    QLabel *charC = new QLabel("CharColor");
    QLabel *shapeT = new QLabel("ShapeType");
    QLabel *shapeC = new QLabel("ShapeColor");

    lst->push_back(newLabel);
    lst->push_back(charT);
    lst->push_back(charC);
    lst->push_back(shapeT);
    lst->push_back(shapeC);

    vc->addRow(lst);

//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir("c:\\src\\")) != NULL)
//    {
//        while ((ent = readdir(dir)) != NULL)
//        {
//            printf("%s\n", ent->d_name);
//        }
//        closedir(dir);
//    }
//    else
//    {
//        perror("");
//        return EXIT_FAILURE;
//    }

//    MainWindow w;

//    // Assumed type casting to be correct will seg fault if wrong
//    QTabWidget *mainTabWidget = (QTabWidget*)w.centralWidget();
//    QScrollArea *firstScroll = (QScrollArea*)mainTabWidget->widget(0);
//    MainTab *firstTab = new MainTab();//(MainTab*)firstScroll->widget();

//    QLabel * newLabel = new QLabel();
//    newLabel->setPixmap(QPixmap("C:/Users/danny_000/Downloads/sampletarget.jpg").scaledToWidth(100));

//    QLabel *targets = new QLabel("Targets");
//    QLabel *charT = new QLabel("CharType");
//    QLabel *charC = new QLabel("CharColor");
//    QLabel *shapeT = new QLabel("ShapeType");
//    QLabel *shapeC = new QLabel("ShapeColor");

//    QGridLayout *mainGrid = new QGridLayout();
//    mainGrid->setHorizontalSpacing(30);
//    mainGrid->setVerticalSpacing(20);

//    mainGrid->addWidget(targets, 0, 0);
//    mainGrid->addWidget(charT, 0, 1);
//    mainGrid->addWidget(charC, 0, 2);
//    mainGrid->addWidget(shapeT, 0, 3);
//    mainGrid->addWidget(shapeC, 0, 4);

////    delete(firstTab->layout());
//    firstTab->setLayout(mainGrid);
//    firstScroll->setWidget(firstTab);

//    // It looks like this is the order of operations to update the ScrollArea
//    // when a change has been made to the layout of it's child widget
////    mainGrid->addWidget(newLabel, 1, 0);
////    QWidget *taken = firstScroll->takeWidget();
////    taken->show();
////    firstScroll->setWidget(taken);
////    firstScroll->show();
//    firstScroll->setWidgetResizable(true);
//    addLabel(mainGrid, newLabel, firstScroll);
//    for (int i = 0; i < 20; i++)
//    {
//        std::stringstream ss;//create a stringstream
//        ss << i;//add number to the stream
//        char buff[20];
//        sprintf_s(buff, 20, "Test%d", i);
//        //return a string with the contents of the stream
//        addLabel(mainGrid, new QLabel(buff), firstScroll);
//    }
////    addLabel(mainGrid, new QLabel("Test1"), firstScroll);
////    addLabel(mainGrid, new QLabel("Test2"), firstScroll);
////    addLabel(mainGrid, new QLabel("Test3"), firstScroll);
////    addLabel(mainGrid, new QLabel("Test4"), firstScroll);


//    w.showMaximized();

    return a.exec();
}


