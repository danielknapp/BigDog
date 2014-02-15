#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include "maintab.h"
#include "model.h"
#include "mainwindow.h"
#include <QTableWidget>
#include <QScrollArea>
#include <QLabel>

class MainTab;
class Model;

/**
 * @brief The ViewController class
 * The idea is that this will act as the Controller of the MVC pattern in which
 * it will handle communication between the view and the model.
 */
class ViewController
{
public:
    ViewController();
//    ViewController(MainTab *view, Model *model);
    ~ViewController();
    void setUpBigDog();
    void setView(MainTab *view);
    void setModel(Model *model);
    MainTab* getView();
    Model* getModel();
    void addRow(std::list<QLabel*> *lst);

private:
    MainTab *view;
    Model *model;
    MainWindow *mainWin;
    QTabWidget *tabWidget;
    std::list<QScrollArea*> *listScrollTabs;
};

#endif // VIEWCONTROLLER_H
