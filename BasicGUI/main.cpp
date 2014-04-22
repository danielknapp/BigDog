//#include "mainwindow.h"
//#include <QApplication>
//#include <QLabel>
//#include <QGraphicsScene>
//#include <QGraphicsView>
//#include <QGraphicsPathItem>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    QPixmap pm("C:/Users/danny_000/Pictures/wall018-1366x768.jpg");
//    QLabel label;
//    label.setPixmap(pm.scaledToWidth(1300));
//    label.show();
////    MainWindow w;
////    w.show();

//    return a.exec();
//}


#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QPoint>
#include <QFile>

int myArgc;
char *myArgv[];
QPixmap *myPix;
QPixmap *origPix;
int origPixHeight;
int origPixWidth;
const char *fileStr = "C:/Users/danny_000/Downloads/targets/targets/YNBGC/1725770091";

class ScribbleArea : public QLabel
{
private:
    QPoint *topLeft;
    QPoint *bottomRight;
    int clickCount;

public:
    ScribbleArea();
    ~ScribbleArea();
    void mousePressEvent(QMouseEvent *event);
};

ScribbleArea::ScribbleArea()
{
    topLeft = new QPoint();
    bottomRight = new QPoint();
    clickCount = 0;
}

ScribbleArea::~ScribbleArea()
{
    delete topLeft;
    delete bottomRight;
    delete myPix;
    delete origPix;
    std::printf("Called the destructor\n");
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
 {
    QLabel::mousePressEvent(event);
     if (event->button() == Qt::LeftButton) {
//         if ( !topLeft )
//             topLeft = &event->pos();
//         else
//         {
//             bottomRight = &event->pos();
//         }
         *topLeft = *bottomRight;
         *bottomRight = event->pos();
         std::printf("tpLeft: %p\nbtmRight: %p\ncurr: %p\n", topLeft, bottomRight, event->pos());
         if ( !topLeft->isNull() && !bottomRight->isNull() && clickCount == 1 ) {

             // ensure topLeft is above and left of bottomRight and actually on pixMap
             if (topLeft->x() > myPix->width() || bottomRight->x() > myPix->width()
                     || topLeft->x() > bottomRight->x() || topLeft->y() > bottomRight->y())
                 return;
             std::printf("tpLeftVal: %p\tbtmRightVal: %p\n", *topLeft, *bottomRight);
             std::printf("tpLeftX: %d\ttpLeftY: %d\nbtmRightX: %d\tbtmRightY: %d\n",
                         topLeft->x(), topLeft->y(), bottomRight->x(), bottomRight->y());
//             *topLeft = *bottomRight;
//             QApplication a(myArgc, myArgv);

//             QPixmap pm("C:/Users/danny_000/Pictures/wall018-1366x768.jpg");


             double xScaled = (double)origPixWidth / (double)myPix->width();
             double yScaled = (double)origPixHeight / (double)myPix->height();

             int topLeftX = (int) (topLeft->x()*xScaled);
             int topLeftY = (int) (topLeft->y()*yScaled);
             int bottomRightX = (int) (bottomRight->x()*xScaled);
             int bottomRightY = (int) (bottomRight->y()*yScaled);

             QRect croprect(QPoint(topLeftX,topLeftY), QPoint(bottomRightX,bottomRightY));

             QPixmap cropped = (origPix)->copy(croprect);

             QLabel cropLabel;
//             label.setMouseTracking(true);
             cropLabel.setPixmap(cropped);
             cropLabel.show();

             QString fileName(fileStr);
//             int lastSlash = fileName.lastIndexOf('/');
//             fileName.remove(0, lastSlash+1);
             QFile file(fileName.append("_c.png"));
             file.open(QIODevice::WriteOnly);
             cropped.save(&file, "PNG");
             file.close();

             clickCount = 0;
//             a.exec();
         }
         else
         {
             clickCount++;
         }
     }
 }

int run(int argc, char*argv[]){
    QApplication a(argc, argv);

//    QPixmap pm("C:/Users/danny_000/Pictures/wall018-1366x768.jpg");
//    myPix = new QPixmap("C:/Users/danny_000/Pictures/wall018-1366x768.jpg");
    QString pxStr(fileStr);
    myPix = new QPixmap(pxStr.append(".jpg"));

    origPix = new QPixmap();
    *origPix = myPix->copy(myPix->rect());
    origPixHeight = myPix->height();
    origPixWidth = myPix->width();

    *myPix = (*myPix).scaledToHeight(675);
    ScribbleArea label;
    label.setPixmap(*myPix);
    label.window()->setFixedWidth(1300);
    label.window()->setFixedHeight(675);
//    label.maximumSize();
    label.show();


//    QRect croprect(QPoint(50,50), QPoint(200,200));

//    QPixmap cropped = pm.copy(croprect);

//    QLabel cropLabel;
//    label.setMouseTracking(true);
//    cropLabel.setPixmap(cropped);
//    cropLabel.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
//    myArgc = argc;
//    myArgv = new char[sizeof(argv)];
//            *argv;
    return run(argc, argv);
}
