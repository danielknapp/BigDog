#include "model.h"

#include <QFileInfoList>
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <thread>

std::mutex *myMutex = new std::mutex();

Model::Model() :
    vc(0),
    prev(0),
//    nextQLock(new std::unique_lock<std::mutex>(*myMutex)),
    qFull(new std::condition_variable()),
    qSize(new std::condition_variable()),
    curr(new std::vector<StalkerLabels*>()),
    nextQ(new std::vector<StalkerLabels*>()),
    prev1(new std::vector<StalkerLabels*>()),
    prev2(new std::vector<StalkerLabels*>()),
    prev3(new std::vector<StalkerLabels*>()),
    prev4(new std::vector<StalkerLabels*>()),
    prev5(new std::vector<StalkerLabels*>())
//    targetFiles(new std::set<QString>())
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
bool Model::addValidImage(QFileInfo &file, ViewController *vc, QString ext)
{
    QString fileName = file.fileName();
    int count = 1;
    if (fileName.contains(ext))
    {
        printf("got %d!\n%s\n", count++, file.absoluteFilePath().toStdString().c_str());

        QString infoFileStr = file.absoluteFilePath();
        infoFileStr = infoFileStr.remove(infoFileStr.size()-3,3).append("info");
        QFile infoFile(infoFileStr);

        QLabel *charT;
        QLabel *charC;
        QLabel *shapeT;
        QLabel *shapeC;
        QLabel *lat;
        QLabel *lon;
        QLabel** properties[] = {&charT, &charC, &shapeT,
                                 &shapeC, &lat, &lon};

        if (!infoFile.open(QIODevice::ReadOnly))
        {
            printf("Problems finding file with name %s\n", infoFileStr.toStdString().c_str());
            charT = new QLabel("CharType");
            charC = new QLabel("CharColor");
            shapeT = new QLabel("ShapeType");
            shapeC = new QLabel("ShapeColor");
            lat = new QLabel("Latitude");
            lon = new QLabel("Longitude");
        }
        else
        {
            QTextStream infoFileStream(&infoFile);

            int i = 0;
            while (!infoFileStream.atEnd())
            {
                QString line = infoFileStream.readLine();
                if (line.isEmpty())
                    continue;
                QLabel *temp = new QLabel(line);
                QFont f( "Arial", 20, QFont::Bold);
                temp->setFont( f);
                *(properties[i++]) = temp;
            }
        }
//        printf("size of properties: %d\n", sizeof(properties));

        infoFile.close();

        // prep for addition to the gui through vc
        std::list<QLabel*> *lst = new std::list<QLabel*>();
        QLabel *picLbl = new QLabel();
        picLbl->setPixmap(QPixmap(file.absoluteFilePath()).scaledToWidth(150));
//        QLabel *charT = new QLabel("CharType");
//        QLabel *charC = new QLabel("CharColor");
//        QLabel *shapeT = new QLabel("ShapeType");
//        QLabel *shapeC = new QLabel("ShapeColor");
        lst->push_back(picLbl);
        lst->push_back(charT);
        lst->push_back(charC);
        lst->push_back(shapeT);
        lst->push_back(shapeC);
        lst->push_back(lat);
        lst->push_back(lon);

        vc->addRow(lst);

        delete lst;
        return true;
    }
    else
        return false;
}

/**
 * Helper function. Deletes all child widgets of the given layout @a item.
 */
void deleteChildWidgets(QLayoutItem *item) {
    if (item->layout()) {
        // Process all child items recursively.
        for (int i = 0; i < item->layout()->count(); i++) {
            deleteChildWidgets(item->layout()->itemAt(i));
        }
    }
    delete item->widget();
}

/**
 * Helper function. Removes all layout items within the given @a layout
 * which either span the given @a row or @a column. If @a deleteWidgets
 * is true, all concerned child widgets become not only removed from the
 * layout, but also deleted.
 *
 * Credit: http://stackoverflow.com/questions/5395266/removing-widgets-from-qgridlayout
 */
void remove2(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if ((r <= row && r + rs - 1 >= row) || (c <= column && c + cs - 1 >= column)) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
//            if (deleteWidgets) {
//                deleteChildWidgets(item);
//            }
            delete item;
        }
    }
}

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
        tmp = new std::vector<StalkerLabels*>();
        int i = 0;
        // **Note: There may be a data race here which
        // may need to be synchronized
        while (i < 5)
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

        prev5->clear();
        prev5 = prev4;
        prev4 = prev3;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = curr;
        curr = tmp;

        qFull->notify_all();
    }


    // Look into QStacked Widget for this problem
    ViewController *vc = getViewController();
//    MainTab * mainView = getViewController()->getView();
    QScrollArea *scroll = vc->listScrollTabs->front();
    remove2(vc->getView()->getGridLayout(), 3, 4, false);
    scroll->takeWidget();
    MainTab *myTab = new MainTab();
    vc->setView(myTab);
    vc->prev->setParent(myTab);
    vc->next->setParent(myTab);
    vc->setGridInfo(vc->prev, 4, 0);
    vc->setGridInfo(vc->next, 4, 4);
    scroll->setWidget(myTab);
    scroll->show();

//    getViewController()->tabWidget->clear();
//    getViewController()->tabWidget->addTab(getViewController()->view, QWidget::tr("Main1"));
//    mainView->setGridLayout(new QGridLayout(mainView));
//    QGridLayout* gLayout = getViewController()->getView()->getGridLayout();

//    gLayout->invalidate();
    getViewController()->getView()->setStalkerLabels(tmp); // Update the view

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
        MainTab * mainView = getViewController()->getView();
        getViewController()->tabWidget->clear();
        getViewController()->tabWidget->addTab(getViewController()->view, QWidget::tr("Main1"));
//        mainView->setGridLayout(new QGridLayout(mainView));
//        QGridLayout* gLayout = getViewController()->getView()->getGridLayout();
//        remove2(gLayout, 3, 4, false);
//        gLayout->invalidate();
        getViewController()->getView()->setStalkerLabels(tmp); // Update the view
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

void Model::addToNextQ(QString fp)
{
    QString infoFileStr = fp;
    infoFileStr = infoFileStr.remove(infoFileStr.size()-3,3).append("txt");
    QFile infoFile(infoFileStr);
    QString attribs[3] = {0,0,0};

    if (!infoFile.open(QIODevice::ReadOnly))
    {
        printf("Problems finding file with name %s\n", infoFileStr.toStdString().c_str());

        return;
    }
    else
    {
        QTextStream infoFileStream(&infoFile);

        int i = 0;
        while (!infoFileStream.atEnd() && i < 3)
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
                attribs[0], attribs[1], attribs[2], fp);

//    nextQLock->lock();
    std::unique_lock<std::mutex> localLock(*myMutex);

    nextQ->push_back(lbls);

    qSize->notify_all();

//    nextQLock->unlock();
//    myMutex->unlock();

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
//    recurseDir(dir, vc);
    dir.refresh();
    QFileInfoList dirList = dir.entryInfoList();
    QString ext(".png");
    for (int i = 0; i < dirList.size(); i++)
    {
        QFileInfo file = dirList.at(i);
        QString fName = file.fileName();
        QString absFP = file.absoluteFilePath();

        if (file.isDir())
        {
            if (fName.compare(".") == 0 || fName.compare("..") == 0)
                ; // skip
            else
                fileChecker(QDir(absFP), vc);
        }
        else if (!file.isDir())
        {
            if (fName.contains(ext) &&
                    targetFiles.find(absFP) == targetFiles.end())
            {
                // Use targetFiles to add only .png files that are new visited
                // absolute paths.
                targetFiles.insert(absFP);

//                printf("owns lock?: %d\n", nextQLock->owns_lock());
//                fflush(stdout);
//                if (nextQLock->owns_lock())
//                    nextQLock->unlock();
//                nextQLock->lock();
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
                    infoFile.close();

                    int size = nextQ->size();
                    int sizeThresh = 5;
                    if ( size == sizeThresh )
                    {
                        printf("Size is now %d!\n", sizeThresh);
                        fflush(stdout);
//                        qFull->wait(*nextQLock);
                        qFull->wait(localLock);
                    }

                    emit queueAdd(absFP);
//                    qSize->wait(*nextQLock);

                    // synchronize nextQ's size
                    qSize->wait(localLock);

//                    nextQLock->unlock();
//                    myMutex->unlock();
                }

            }
        }
    }
}


