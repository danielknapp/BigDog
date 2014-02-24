#ifndef MODEL_H
#define MODEL_H

#include "viewcontroller.h"
#include <QObject>
#include <QFileInfo>
#include <QDir>

class ViewController;

/**
 * This class should contain all the backend stuff for the Big Dog gui.
 * The idea is that this will function as the Model in the MVC pattern
 */
class Model : public QObject
{
    Q_OBJECT

public:
    Model();
//    Model(ViewController *vc);
    void setViewController(ViewController *vc);
    ViewController* getViewController();
    void recurseDir(QDir &dir, ViewController *vc);
    void fileChecker(QDir &dir, ViewController *vc);
    bool addValidImage(QFileInfo &file, ViewController *vc, QString &ext = QString(""));

signals:
    void imageFound(QFileInfo file, ViewController *vc, QString ext);

public slots:
    void open();
    void addImage(QFileInfo file, ViewController *vc, QString ext);

private:
    ViewController *vc;
};

#endif // MODEL_H
