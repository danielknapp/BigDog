#include "mainwindow.h"
#include "maintab.h"
#include "viewcontroller.h"
#include "model.h"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <Windows.h>
#include "dirent.h"
//#include <unistd.h>
//#include <sys/stat.h>
//#include <sys/types.h>
#include <thread>
#include <signal.h>

#include <sstream>
#include <QApplication>
#include <QTableWidget>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>


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

//class ViewController;

bool addValidImage(QFileInfo &file, ViewController *vc, QString &ext = QString(""));

void recurseDir(QDir &dir, ViewController *vc)
{
    QFileInfoList dirList = dir.entryInfoList();
    QString ext(".png");
    for (int i = 0; i < dirList.size(); i++)
    {
        QFileInfo file = dirList.at(i);
        QString fName = file.fileName();

        if (file.isDir())
        {
            if (fName.compare(".") == 0 || fName.compare("..") == 0)
                ; // skip
            else
                recurseDir(QDir(file.absoluteFilePath()), vc);
        }
        else if (!file.isDir())
        {
            addValidImage(file, vc, ext);
        }
    }
}

bool addValidImage(QFileInfo &file, ViewController *vc, QString &ext)
{
    QString fileName = file.fileName();
    int count = 1;
    if (fileName.contains(ext))
    {
        printf("got %d!\n%s\n", count++, file.absoluteFilePath().toStdString().c_str());
        std::list<QLabel*> *lst = new std::list<QLabel*>();
        QLabel *picLbl = new QLabel();
        picLbl->setPixmap(QPixmap(file.absoluteFilePath()).scaledToWidth(200));
        QLabel *charT = new QLabel("CharType");
        QLabel *charC = new QLabel("CharColor");
        QLabel *shapeT = new QLabel("ShapeType");
        QLabel *shapeC = new QLabel("ShapeColor");
        lst->push_back(picLbl);
        lst->push_back(charT);
        lst->push_back(charC);
        lst->push_back(shapeT);
        lst->push_back(shapeC);

        vc->addRow(lst);

        delete lst;
        return true;
    }
    else
        return false;
}

void callFromThread(int i)
{
    while (i < 5)
    {
        printf("Call number %d\n", i);
        fflush(stdout);
        i++;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
    //std::terminate();
}

void sigabrt(int i)
{
    printf("Abort signaled with %d\n", i);
    exit(0);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewController *vc = new ViewController();

    void (*sigabrtPtr)(int);
    sigabrtPtr = signal(SIGABRT, SIG_IGN);
    std::thread myt(callFromThread, 0);
    myt.detach();

    vc->setUpBigDog();

    std::list<QLabel*> *lst = new std::list<QLabel*>();
    QLabel * newLabel = new QLabel();
    newLabel->setPixmap(QPixmap("C:/Users/danny_000/Downloads/sampletarget.jpg").scaledToWidth(200));
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

    QDir currDir("C:\\Users\\danny_000\\Downloads\\targets\\targets");
//    QFileInfoList dirList = currDir.entryInfoList();
//    QString ext(".png");
    recurseDir(currDir, vc);

//    int i = 0;

//    DIR *dir;
//    struct dirent *ent;
////    std::list<QString*> *lst = new std::list<QString*>();
//    QStringList strLst;
//    QString ext(".png");
//    if ((dir = opendir("c:\\Users\\danny_000\\Downloads\\targets\\targets")) != NULL)
//    {
//        while ((ent = readdir(dir)) != NULL)
//        {
//            printf("%s\n", ent->d_name);

//            // Check if file is a directory
//            struct stat st;
//            errno = 0;
//            unsigned short errCode = stat(ent->d_name, &st);
//            int erStuff = errno;
//            if (errno)
//                perror("errno set");

//            if(S_ISDIR(st.st_mode))
//            {
//               continue;
//            }
//            else
//            {
//                // if it has a .png ending, include it
//                QString dName(ent->d_name);
//                if (dName.contains(ext))
//                    strLst.append(dName);
//            }

//        }
//        closedir(dir);
//    }
//    else
//    {
//        perror("");
//        return EXIT_FAILURE;
//    }

//    printf("%d\n", strLst.size());

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

//    myt.join();
    return a.exec();
}


