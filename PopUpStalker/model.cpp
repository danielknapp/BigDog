#include "model.h"

#include <QFileInfoList>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <thread>

//std::mutex *myMutex = new std::mutex();
//std::unordered_set<std::string> * targetFiles = new std::unordered_set<std::string>();

Model::Model() :
    vc(0),
    prev(0),
//    nextQLock(new std::unique_lock<std::mutex>(*myMutex)),
    qFull(new std::condition_variable()),
    qSize(new std::condition_variable()),
    myMutex(new std::mutex()),
    setMutex(new std::mutex()),
    curr(new std::vector<StalkerLabels*>()),
    nextQ(new std::vector<StalkerLabels*>()),
    prev1(new std::vector<StalkerLabels*>()),
    prev2(new std::vector<StalkerLabels*>()),
    prev3(new std::vector<StalkerLabels*>()),
    prev4(new std::vector<StalkerLabels*>()),
    prev5(new std::vector<StalkerLabels*>()),
    targetFiles(new std::unordered_set<std::string>())
{
}

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
//void Model::addImage(QFileInfo file, ViewController *vc, QString ext)
//{
//    // Calls another method because this one cannot return a boolean.
//    // The code can probably be copied here if that is not needed.
//    addValidImage(file, vc, ext);
//}

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
//bool Model::addValidImage(QFileInfo &file, ViewController *vc, QString ext)
//{
//    QString fileName = file.fileName();
//    int count = 1;
//    if (fileName.contains(ext))
//    {
//        printf("got %d!\n%s\n", count++, file.absoluteFilePath().toStdString().c_str());

//        QString infoFileStr = file.absoluteFilePath();
//        infoFileStr = infoFileStr.remove(infoFileStr.size()-3,3).append("info");
//        QFile infoFile(infoFileStr);

//        QLabel *charT;
//        QLabel *charC;
//        QLabel *shapeT;
//        QLabel *shapeC;
//        QLabel *lat;
//        QLabel *lon;
//        QLabel** properties[] = {&charT, &charC, &shapeT,
//                                 &shapeC, &lat, &lon};

//        if (!infoFile.open(QIODevice::ReadOnly))
//        {
//            printf("Problems finding file with name %s\n", infoFileStr.toStdString().c_str());
//            charT = new QLabel("CharType");
//            charC = new QLabel("CharColor");
//            shapeT = new QLabel("ShapeType");
//            shapeC = new QLabel("ShapeColor");
//            lat = new QLabel("Latitude");
//            lon = new QLabel("Longitude");
//        }
//        else
//        {
//            QTextStream infoFileStream(&infoFile);

//            int i = 0;
//            while (!infoFileStream.atEnd())
//            {
//                QString line = infoFileStream.readLine();
//                if (line.isEmpty())
//                    continue;
//                QLabel *temp = new QLabel(line);
//                QFont f( "Arial", 20, QFont::Bold);
//                temp->setFont( f);
//                *(properties[i++]) = temp;
//            }
//        }
////        printf("size of properties: %d\n", sizeof(properties));

//        infoFile.close();

//        // prep for addition to the gui through vc
//        std::list<QLabel*> *lst = new std::list<QLabel*>();
//        QLabel *picLbl = new QLabel();
//        picLbl->setPixmap(QPixmap(file.absoluteFilePath()).scaledToWidth(150));
////        QLabel *charT = new QLabel("CharType");
////        QLabel *charC = new QLabel("CharColor");
////        QLabel *shapeT = new QLabel("ShapeType");
////        QLabel *shapeC = new QLabel("ShapeColor");
//        lst->push_back(picLbl);
//        lst->push_back(charT);
//        lst->push_back(charC);
//        lst->push_back(shapeT);
//        lst->push_back(shapeC);
//        lst->push_back(lat);
//        lst->push_back(lon);

//        vc->addRow(lst);

//        delete lst;
//        return true;
//    }
//    else
//        return false;
//}

void Model::nextClicked()
{
    if (!vc)
        return;

    std::vector<StalkerLabels*> *tmp = 0;
    switch(prev) {
        case 1:
            tmp = curr;
            break;
        case 2:
            tmp = prev1;
            break;
        case 3:
            tmp = prev2;
            break;
        case 4:
            tmp = prev3;
            break;
        case 5:
            tmp = prev4;
            break;
    }

    if (tmp != 0)
    {
        prev--;
    }
    else
    {
        if (nextQ->empty())
            return;

        tmp = new std::vector<StalkerLabels*>();
        int i = 0;
        // **Note: There may be a data race here which
        // may need to be synchronized
        while (i < 10)
        {
            if (!nextQ->empty())
            {
                StalkerLabels *lbls = nextQ->front();
                tmp->push_back(lbls);
                nextQ->erase(nextQ->begin());
            }
            else
            {
                tmp->push_back(new StalkerLabels());
            }
            i++;
        }

        // TODO: synchronize setMutex and targetFiles set
        MainTab *anotherTab = new MainTab();
        anotherTab->setStalkerLabels(tmp);

        QWidget *remove = vc->mainDisp->widget(5);
        if (remove)
            vc->mainDisp->removeWidget(remove);

        vc->mainDisp->insertWidget(0, anotherTab);

        // Before clear of prev5, delete input files
        for (std::vector<StalkerLabels*>::iterator start = prev5->begin();
             start != prev5->end(); start++)
        {
//            StalkerLabels * curr = start*;
//            QString currStr = curr->getAbsPath();
            QString picPath = (*start)->getAbsPath();

            // Don't delete an empty path
            if (picPath.isEmpty())
                continue;

            QString infoPath = picPath;
            infoPath = infoPath.remove(infoPath.size()-3,3).append("txt");
            if ( !QFile::remove(picPath) )
            {
                printf("Model.cpp: Something went wrong deleting a picture\n");
            }
            if ( !QFile::remove(infoPath) )
            {
                printf("Model.cpp: Something went wrong deleting a text file\n");
            }
            fflush(stdout);
        }

        prev5->clear();
        prev5 = prev4;
        prev4 = prev3;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = curr;
        curr = tmp;

        qFull->notify_all();
    }

    vc->mainDisp->setCurrentIndex(prev);


}



void Model::prevClicked()
{
    if (!vc)
        return;

    std::vector<StalkerLabels*> *tmp = 0;
    switch(prev) {
        case 0:
            if (prev1->size() != 0)
                tmp = prev1;
            break;
        case 1:
            if (prev2->size() != 0)
                tmp = prev2;
            break;
        case 2:
            if (prev3->size() != 0)
                tmp = prev3;
            break;
        case 3:
            if (prev4->size() != 0)
                tmp = prev4;
            break;
        case 4:
            if (prev5->size() != 0)
                tmp = prev5;
            break;
        default:
            break;
    }

    if (tmp != 0)
    {
        prev++;

//        MainTab * mainView = getViewController()->getView();
//        getViewController()->tabWidget->clear();
//        getViewController()->tabWidget->addTab(getViewController()->view, QWidget::tr("Main1"));
////        mainView->setGridLayout(new QGridLayout(mainView));
////        QGridLayout* gLayout = getViewController()->getView()->getGridLayout();
////        remove2(gLayout, 3, 4, false);
////        gLayout->invalidate();
//        getViewController()->getView()->setStalkerLabels(tmp); // Update the view


        vc->mainDisp->setCurrentIndex(prev);
    }
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
//            if (targetFiles.find(file.absoluteFilePath()) == targetFiles.end())
//            {
//                targetFiles.insert(file.absoluteFilePath());
////                printf("emitting now\n");
////                fflush(stdout);
//                emit imageFound(file, vc, ext);
//            }
//        }
//    }
//}

void Model::addToNextQ(QString fp, QString fName)
{
    QString infoFileStr = fp;
    infoFileStr = infoFileStr.remove(infoFileStr.size()-3,3).append("txt");
    QFile infoFile(infoFileStr);

    printf("File Name: %s\n", fName.toStdString().c_str());
    fflush(stdout);

    QString attribs[2] = {0,0};

    if (!infoFile.open(QIODevice::ReadOnly))
    {
        printf("Problems finding file with name %s\n", infoFileStr.toStdString().c_str());

        return;
    }
    else
    {
        QTextStream infoFileStream(&infoFile);

        int i = 0;
        while (!infoFileStream.atEnd() && i < 4)
        {
            infoFileStream.readLine();
            i++;
        }

        i = 0;
        while (!infoFileStream.atEnd() && i < 2)
        {
            QString line = infoFileStream.readLine();
            if (line.isEmpty())
                continue;
            attribs[i] = line;
            i++;
        }
    }

    infoFile.close();

    StalkerLabels *lbls = new StalkerLabels(
                fName, attribs[0], attribs[1], fp);

    std::unique_lock<std::mutex> localLock(*myMutex);

    nextQ->push_back(lbls);

    qSize->notify_all();


}


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
void Model::fileChecker(QDir dir, ViewController *vc)
{

    // TODO: Do the file removing in here so it is handled by the side
    //       thread and does not hang the gui.
//    recurseDir(dir, vc);
    dir.refresh();
    QFileInfoList dirList = dir.entryInfoList();
    QString ext(".png");
    for (int i = 0; i < dirList.size(); i++)
    {
        QFileInfo file = dirList.at(i);
        QString fName = file.fileName();
        QString absFP = file.absoluteFilePath();
        std::string stdAbsFP = std::string(absFP.toStdString());

        // Don't need the recursive check so file is dir path is
        // just commented out since we just wanted to skip that case
//        if (file.isDir())
//        {
//            if (fName.compare(".") == 0 || fName.compare("..") == 0)
//                ; // skip
//            else
//                fileChecker(QDir(absFP), vc);
//        }
        if (!file.isDir())
        {
            // ensure either branch of the if unlocks the mutex afterwards
            setMutex->lock();

            if (fName.contains(ext) &&
                    targetFiles->find(stdAbsFP) == targetFiles->end())
            {

                setMutex->unlock();

                // Need a lock for condition variables
                std::unique_lock<std::mutex> localLock(*myMutex);

                QString infoFileStr = file.absoluteFilePath();
                infoFileStr = infoFileStr.remove(infoFileStr.size()-3,3).append("txt");
                QFile infoFile(infoFileStr);

                if (!infoFile.open(QIODevice::ReadOnly))
                {
                    infoFile.close();
                    printf("Problems finding file with name %s\n",
                           infoFileStr.toStdString().c_str());

                }
                else
                {
                    // Use targetFiles to add only .png files that are new visited
                    // absolute paths.
                    setMutex->lock();
                    targetFiles->insert(stdAbsFP);
                    setMutex->unlock();

                    infoFile.close();

                    int size = nextQ->size();
                    int sizeThresh = 20;
                    if ( size == sizeThresh )
                    {
                        printf("Size is now %d!\n", sizeThresh);
                        fflush(stdout);
                        qFull->wait(localLock);
                    }

                    emit queueAdd(absFP, fName);

                    // synchronize nextQ's size
                    qSize->wait(localLock);

                }

            } // end if ext check
            else
            {
                setMutex->unlock();
            }
        }
    }
}


