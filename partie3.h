#ifndef PARTIE3_H
#define PARTIE3_H

#include <QObject>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <string>


using namespace cv;
using namespace std;

#include <vector>

class partie3 : public QObject
{
    Q_OBJECT
    QString url;
public:

    explicit partie3(QObject *parent = nullptr);

    Q_INVOKABLE int DetectionOfCarre(int posx,int posy,Mat frame);
    Q_INVOKABLE int DetectionOfRectangle(int posx,int posy,Mat frame) ;
    Q_INVOKABLE int DetectionOfCircle(int posx, int posy, Mat frame);
    Q_INVOKABLE void detectPositionObjects(Mat frame,vector<int> *listeCircle,vector<int> *listeCarre,vector<int> *listeRectangle);

    Q_INVOKABLE int partieIII(const QString &path);
    Q_INVOKABLE void setUrl(QString &value);

signals:

};

#endif // PARTIE3_H
