#include "util.h"
#include <thread>

GuiButton::GuiButton(QWidget *parent) :
    QPushButton(parent),
    funptr(0)
{
    textBoxes = new std::list<QLineEdit*>();
}

GuiButton::GuiButton(const QString &text, QWidget *parent) :
    QPushButton(text,parent),
    funptr(0)
{
    textBoxes = new std::list<QLineEdit*>();
}

GuiButton::~GuiButton()
{
    delete textBoxes;
}

void GuiButton::addQLineEdit(QLineEdit *ledit)
{
    textBoxes->push_back(ledit);
}

void GuiButton::setFunptr(void (*func)())
{
    funptr = func;
}

void GuiButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        if (funptr != 0)
            (*funptr)();
    }
    else
    {
        printf("Incorrect mouse button clicked.\nExpected: %d\nReceived: %d\n", Qt::LeftButton, event->button());
    }
}

void GuiButton::keyPressEvent(QKeyEvent *event)
{
    QPushButton::keyPressEvent(event);
    if (event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter)
    {
        if (funptr != 0)
            (*funptr)();
    }
    else
    {
        printf("Incorrect key was pressed.\nExpected: %d\nReceived: %d\n", Qt::Key_Space, event->key());
    }
}

/////////////////////////////// Target Rec //////////////////////////////////////////////


TargetRec::TargetRec() :
    imageConfirmed(false)
{
}

void TargetRec::recurseDir(QDir &dir, std::set<QString> *targetFolders)
{
//    recurseDir(dir, vc);
    dir.refresh();
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
                recurseDir(QDir(file.absoluteFilePath()), targetFolders);
        }
        else if (!file.isDir())
        {
            if (targetFolders->find(file.absoluteFilePath()) == targetFolders->end())
            {
                // Use targetFolders to add only .png files that are new visited
                // absolute paths.
                targetFolders->insert(file.absoluteFilePath());

//                printf("emitting now\n");
//                fflush(stdout);
//                emit imageFound(file, vc, ext);
            }
        }
    }
}

void TargetRec::recurseTargets(QDir &dir, QLabel *lbl)
{
    std::set<QString> *targetFolders = new std::set<QString>();
    recurseDir(dir, targetFolders);
    start = targetFolders->begin();
    end = targetFolders->end();

    lbl->setPixmap(QPixmap(*start++).scaledToHeight(600));
//    while (start != end)
//    {
//        while (!imageConfirmed)
//        {
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        }

//        lbl->setPixmap(QPixmap(*start++).scaledToHeight(600));
//        imageConfirmed = false;
//    }

}




void TargetRec::nextImage(QLabel *lbl, QString fileStr)
{
//    imageConfirmed = true;
    printf("nextImage called!\n");
    fflush(stdout);

    if (start == end)
    {
        recurseTargets(QDir(fileStr), lbl);
    }
    else
    {
        lbl->setPixmap(QPixmap(*start++).scaledToHeight(600));
    }


}

//    QLabel *picLabel;

