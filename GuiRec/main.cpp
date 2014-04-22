#include "mainwindow.h"
#include "util.h"

#include <QApplication>

#include <set>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QPoint>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QString>
#include <QObject>

#include <thread>
#include <signal.h>


QPixmap *myPix;


void doRec(QDir dir, QLabel *lbl, TargetRec *tRec)
{
    tRec->recurseTargets(dir, lbl);
}


/**
 * @brief fileChecker
 *      Recursively goes through dir and looks for .png files.
 *      When one is found, it emits a signal that an image is found.
 * @param dir
 *      QDir object representing the directory to be recursed.
 * @param targetFolders
 *      std::set ptr that keeps track of the files that have
 *      been viewed
 */
//void fileChecker(QDir &dir, QLabel &lbl, std::set<QString> *targetFolders)
//{
////    recurseDir(dir, vc);
//    dir.refresh();
//    QFileInfoList dirList = dir.entryInfoList();
//    QString ext(".png");
//    for (int i = 0; i < dirList.size(); i++)
//    {
//        QFileInfo file = dirList.at(i);
//        QString fName = file.fileName();

//        if (file.isDir())
//        {
//            if (fName.compare(".") == 0 || fName.compare("..") == 0)
//                ; // skip
//            else
//                fileChecker(QDir(file.absoluteFilePath()), vc);
//        }
//        else if (!file.isDir())
//        {
//            if (targetFolders->find(file.absoluteFilePath()) == targetFolders->end())
//            {
//                // Use targetFolders to add only .png files that are new visited
//                // absolute paths.
//                targetFolders->insert(file.absoluteFilePath());

////                printf("emitting now\n");
////                fflush(stdout);
////                emit imageFound(file, vc, ext);
//            }
//        }
//    }
//}

int run(int argc, char*argv[]){
    // Need this for the application
    QApplication a(argc, argv);

    // The main window to be displayed
    QWidget Main_Window;

//    qRegisterMetaType<TargetRec>("TargetRec");

    // Create a widget to hold the pictures and character/shape inputs
    //QWidget picAndInputs(&Main_Window);
    QHBoxLayout *hbl = new QHBoxLayout();

    // The target image displayed
    QLabel i_label("Start", &Main_Window);
    i_label.setPixmap(QPixmap("C:/Users/danny_000/Downloads/sampletarget.jpg").scaledToHeight(675));
    hbl->addWidget(&i_label);

    // Holds the labels and lineEdit widgets vertically
    QVBoxLayout *vblInputs = new QVBoxLayout();

    // Displays charType label and lineEdit
    QHBoxLayout *hblCharType = new QHBoxLayout();
    QLabel charTypeLabel("charType:");
    hblCharType->addWidget(&charTypeLabel);
    QLineEdit charType("");
    hblCharType->addWidget(&charType);
    vblInputs->addLayout(hblCharType);

    // Displays charColor label and lineEdit
    QHBoxLayout *hblCharColor = new QHBoxLayout();
    QLabel charColorLabel("charColor:");
    hblCharColor->addWidget(&charColorLabel);
    QLineEdit charColor("");
    hblCharColor->addWidget(&charColor);
    vblInputs->addLayout(hblCharColor);

    // Displays shapeType label and lineEdit
    QHBoxLayout *hblShapeType = new QHBoxLayout();
    QLabel shapeTypeLabel("shapeType:");
    hblShapeType->addWidget(&shapeTypeLabel);
    QLineEdit shapeType("");
    hblShapeType->addWidget(&shapeType);
    vblInputs->addLayout(hblShapeType);

    // Displays shapeColor label and lineEdit
    QHBoxLayout *hblShapeColor = new QHBoxLayout();
    QLabel shapeColorLabel("shapeColor:");
    hblShapeColor->addWidget(&shapeColorLabel);
    QLineEdit shapeColor("");
    hblShapeColor->addWidget(&shapeColor);
    vblInputs->addLayout(hblShapeColor);

    // Add the vertical inputs box to the larger horizontal box
    hbl->addLayout(vblInputs);

    // Vertical box to have pic and inputs above buttons
    QVBoxLayout *vbl = new QVBoxLayout(&Main_Window);

    // Add the pic and Inputs to the larger vertical box
    vbl->addLayout(hbl);

    // GuiButton defined in util.h
    //QWidget confirmAndNegative(&Main_Window);
    QHBoxLayout *hblConfNeg = new QHBoxLayout();
    GuiButton confirm("Confirm");

    // Add the fields GuiButton will have to write to a file when clicked
    confirm.addQLineEdit(&charType);
    confirm.addQLineEdit(&charColor);
    confirm.addQLineEdit(&shapeType);
    confirm.addQLineEdit(&shapeColor);

    hblConfNeg->addWidget(&confirm);
    GuiButton negative("Negative");
    QObject::connect(&negative , SIGNAL(clicked()), qApp , SLOT(quit()));
    hblConfNeg->addWidget(&negative);

    // Add the buttons to the overall vertical box
    vbl->addLayout(hblConfNeg);

    // Maximize the main window
    Main_Window.showMaximized();

    TargetRec *myTarRec = new TargetRec();
    QObject::connect(myTarRec, SIGNAL(infoConfirmed(QLabel *, QString)), myTarRec, SLOT(nextImage(QLabel *, QString)));
    std::thread myt(doRec, QDir("C:/Users/danny_000/Downloads/targets/targets"), &i_label, myTarRec);
    myt.detach();

    return a.exec();
}

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    return run(argc, argv);
}
