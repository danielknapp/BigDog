#ifndef MAINTAB_H
#define MAINTAB_H

#include "viewcontroller.h"
#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QLabel>

class ViewController;

class MainTab : public QWidget {
    Q_OBJECT

public:
    MainTab(QWidget *parent = 0);
    void addColumn(const char* label);
    void addColumn(const char* label, int col);
    void addRow(std::list<QLabel*> *labels);
    MainTab* setupAsFirstTab();
    void mousePressEvent(QMouseEvent *event);
    void setViewController(ViewController* vc);
//    void setLayout(QLayout *layout);

private:
    QGridLayout *mainLayout;
    ViewController *vc;
};

#endif // MAINTAB_H
