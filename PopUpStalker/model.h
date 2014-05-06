#ifndef MODEL_H
#define MODEL_H

#include "viewcontroller.h"
#include "util.h"
#include <set>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <QObject>
#include <QFileInfo>
#include <QDir>
#include <QLabel>

class ViewController;

/**
 * @brief The Model class
 *      This class should contain all the backend stuff for the Big Dog gui.
 *      The idea is that this will function as the Model in the MVC pattern.
 */
class Model : public QObject
{
    Q_OBJECT

public:
    Model();
//    Model(ViewController *vc);

    void setViewController(ViewController *vc);
    ViewController* getViewController();

//    void recurseDir(QDir &dir, ViewController *vc);

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
    void fileChecker(QDir dir, ViewController *vc);

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
    bool addValidImage(QFileInfo &file, ViewController *vc, QString ext = QString(""));

signals:

    // Signal to be sent with those arguments. No implementation needed.
    void imageFound(QFileInfo file, ViewController *vc, QString ext);
    void queueAdd(QString absFP);

public slots:

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
    void addImage(QFileInfo file, ViewController *vc, QString ext);
    void addToNextQ(QString fp);

    void nextClicked();
    void prevClicked();

private:
    ViewController *vc;
    std::set<QString> targetFiles;
    std::unique_lock<std::mutex> *nextQLock;
    std::condition_variable *qFull; // Condition if nextQ is full
    std::condition_variable *qSize; // Condition to sync nextQ's size


    int prev;
    std::vector<StalkerLabels*> *curr;
    std::vector<StalkerLabels*> *nextQ;
    std::vector<StalkerLabels*> *prev1;
    std::vector<StalkerLabels*> *prev2;
    std::vector<StalkerLabels*> *prev3;
    std::vector<StalkerLabels*> *prev4;
    std::vector<StalkerLabels*> *prev5;
};

#endif // MODEL_H