#ifndef MAINTAB_H
#define MAINTAB_H

#include <QWidget>
#include <QHBoxLayout>

class MainTab : public QWidget {
    Q_OBJECT

public:
    MainTab(QWidget *parent = 0);
    void addColumn(const char* label);
    MainTab* setupAsFirstTab();
//    void setLayout(QLayout *layout);

private:
    QHBoxLayout * mainLayout;
};

#endif // MAINTAB_H
