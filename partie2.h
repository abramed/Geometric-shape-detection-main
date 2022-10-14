#ifndef PARTIE2_H
#define PARTIE2_H

#include <QObject>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>


using namespace cv;
using namespace std;

#include <vector>

class Partie2 : public QObject
{
    Q_OBJECT
    QString url;
public:
    explicit Partie2(QObject *parent = nullptr);

    Q_INVOKABLE bool IsIntersectedCircles(int posX, int posX2, int posY, int posY2);
    Q_INVOKABLE bool IsIntersectedRectangle(int x, int x2, int y, int y2, int width, int height);
    Q_INVOKABLE bool IsIntersectedCircleRectangle(int posX, int posY, int rcircle, int x, int y, int width, int height);
    Q_INVOKABLE void creatPoints(vector<Rect> *vecRec,vector<int> *vecRecColorB,vector<int> *vecRecColorG,vector<int> *vecRecColorR,int nbPoint,int tailleMaxPoints);
    Q_INVOKABLE void setUrl(QString &value);
    Q_INVOKABLE bool IsIntersectedCarre(int x, int x2, int y, int y2, int width, int height);
    Q_INVOKABLE bool IsIntersectedCircleCarre(int posX, int posY, int rcircle, int x, int y, int width, int height);
    Q_INVOKABLE int IsIntersectCarreRectangle(int x, int y, int posx, int posy, int type1, int type2);
    Q_INVOKABLE int partieII(int nbcaree,int nbcircle,int nbrec,int nbpoints,int tailleMaxPoints,double dureePoints,const QString &path);


signals:

public slots:
    void cppSlot();

};

#endif // PARTIE2_H
