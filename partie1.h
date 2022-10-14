#ifndef PARTIE1_H
#define PARTIE1_H

// Importer les bibliotheques importante //

#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <vector>


using namespace cv;
using namespace std;



class Frame : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(QImage frame READ getFrame WRITE setFrame NOTIFY frameChanged)

    Mat rawFrame;
    QImage frame;

public:
    Frame(QQuickItem *parent = 0);

    void paint(QPainter *painter);
    Mat getRawFrame() const;
    Q_INVOKABLE void setRawFrame(const Mat &value);
    QImage getFrame() const;
    void setFrame(const QImage &value);

    Q_INVOKABLE bool filterMoyenNVG(int voisinage );
    Q_INVOKABLE bool filterMedianNVG(int voisinage);
    Q_INVOKABLE bool gaussianBlur();
    Q_INVOKABLE bool laplacianFilter();
    Q_INVOKABLE bool filtreLapGauss();
    Q_INVOKABLE bool erodeImage();
    Q_INVOKABLE bool dilateImage();
    Q_INVOKABLE bool filtreCanny();
    Q_INVOKABLE bool findHorizontalLines();
    Q_INVOKABLE bool findVerticalLines();
    Q_INVOKABLE bool findImageContours();
    Q_INVOKABLE void openImage(QString url);





 signals:
    void frameChanged(); // pas de definitions

 public slots:
    void convert2QImage();
};

#endif // PARTIE1_H
