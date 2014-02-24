#include "model.h"

#include <QFileInfoList>
#include <set>
#include <thread>

std::set<QString> targetFolders;

Model::Model() :
    vc(0)
{
}

//Model::Model(ViewController *vc) :
//    vc(vc)
//{
//}

void Model::setViewController(ViewController *vc)
{
    this->vc = vc;
}

ViewController* Model::getViewController()
{
    return vc;
}

void Model::open()
{
    printf("open called!\n");
    fflush(stdout);
}

void Model::addImage(QFileInfo file, ViewController *vc, QString ext)
{
    addValidImage(file, vc, ext);
}

void Model::recurseDir(QDir &dir, ViewController *vc)
{
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
                recurseDir(QDir(file.absoluteFilePath()), vc);
        }
        else if (!file.isDir())
        {
            if (targetFolders.find(file.absoluteFilePath()) == targetFolders.end())
            {
                targetFolders.insert(file.absoluteFilePath());
//                printf("emitting now\n");
//                fflush(stdout);
                emit imageFound(file, vc, ext);
            }
        }
    }
}

void Model::fileChecker(QDir &dir, ViewController *vc)
{
    recurseDir(dir, vc);
////    while (true)
////    {
//        dir.refresh();
//        QFileInfoList dirList = dir.entryInfoList();
//        QString ext(".png");
//        for (int i = 0; i < dirList.size(); i++)
//        {
//            QFileInfo file = dirList.at(i);
//            QString fName = file.fileName();

//            if (file.isDir())
//            {
//                if (fName.compare(".") == 0 || fName.compare("..") == 0)
//                    ; // skip
////                else if (targetFolders.find(fName) == targetFolders.end())
////                {
////                    targetFolders.insert(fName);
////                    recurseDir(QDir(file.absoluteFilePath()), vc);
////                }
//                else
//                    recurseDir(QDir(file.absoluteFilePath()), vc);
//            }
//            else if (!file.isDir())
//            {
//                if (targetFolders.find(fName) == targetFolders.end())
//                    emit imageFound(file, vc, ext);
//            }
//        }
////        std::this_thread::sleep_for(std::chrono::seconds(10));
////    }
}

bool Model::addValidImage(QFileInfo &file, ViewController *vc, QString &ext)
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
