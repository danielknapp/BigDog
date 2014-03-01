#include "model.h"

#include <QFileInfoList>
#include <thread>


Model::Model() :
    vc(0)
//    targetFolders(new std::set<QString>())
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

/**
 * @brief Model::addImage
 *      A slot method to add an image to the view in vc.
 * @param file
 *      QFileInfo object that represents the file image file.
 * @param vc
 *      ViewController object to add the image to its view.
 * @param ext
 *      The extension that file needs to have to be added to the ViewController
 *      (note it is probably best to handle this before using this slot, so
 *      ext may be unnecessary).
 */
void Model::addImage(QFileInfo file, ViewController *vc, QString ext)
{
    // Calls another method because this one cannot return a boolean.
    // The code can probably be copied here if that is not needed.
    addValidImage(file, vc, ext);
}

/**
 * @brief Model::addValidImage
 *      Adds an image to the view in vc if the file has the proper extension.
 * @param file
 *      QFileInfo object that represents the file image file.
 * @param vc
 *      ViewController object to add the image to its view.
 * @param ext
 *      The extension that file needs to have to be added to the ViewController
 *      (note it is probably best to handle this before using this slot, so
 *      ext may be unnecessary).
 * @return
 *      A boolean value representing whether the image was actually added or not
 */
bool Model::addValidImage(QFileInfo &file, ViewController *vc, QString &ext)
{
    QString fileName = file.fileName();
    int count = 1;
    if (fileName.contains(ext))
    {
        printf("got %d!\n%s\n", count++, file.absoluteFilePath().toStdString().c_str());

        // prep for addition to the gui through vc
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

//void Model::recurseDir(QDir &dir, ViewController *vc)
//{
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
//                recurseDir(QDir(file.absoluteFilePath()), vc);
//        }
//        else if (!file.isDir())
//        {
//            if (targetFolders.find(file.absoluteFilePath()) == targetFolders.end())
//            {
//                targetFolders.insert(file.absoluteFilePath());
////                printf("emitting now\n");
////                fflush(stdout);
//                emit imageFound(file, vc, ext);
//            }
//        }
//    }
//}

/**
 * @brief Model::fileChecker
 *      Recursively goes through dir and looks for .png files.
 *      When one is found, it emits a signal that an image is found.
 * @param dir
 *      QDir object representing the directory to be recursed.
 * @param vc
 *      ViewController object to pass to the emitted signal
 *      for adding the image to the gui.
 */
void Model::fileChecker(QDir &dir, ViewController *vc)
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
                fileChecker(QDir(file.absoluteFilePath()), vc);
        }
        else if (!file.isDir())
        {
            if (targetFolders.find(file.absoluteFilePath()) == targetFolders.end())
            {
                // Use targetFolders to add only .png files that are new visited
                // absolute paths.
                targetFolders.insert(file.absoluteFilePath());

//                printf("emitting now\n");
//                fflush(stdout);
                emit imageFound(file, vc, ext);
            }
        }
    }
}


