#include "partie1.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

Mat Frame::getRawFrame() const
{
    return rawFrame;
}

void Frame::setRawFrame(const Mat &value)
{
    rawFrame = value;
    convert2QImage();
}

QImage Frame::getFrame() const
{
    return frame;
}

void Frame::setFrame(const QImage &value)
{
    frame = value;
    Frame::update();
    emit(frameChanged());
}

/*

 Les filtres implementes sont :

    1. Filtre Moyen
    2. Filtre Mediane
    3. Filtre Laplacien
    4. Filtre Gaussian
    5. Filtre LapGaussian
    6. Erosion
    7. Dilatation
    8. filtre de Canny
    9. H line
    10. V line



*/

bool Frame::filterMoyenNVG(int voisinage){

    Mat src = rawFrame;
    Mat dst = src.clone();
    Mat tempGray;
    //if(src.channels() != 1 || dst.channels() != 1) return false ;
    if(src.rows != dst.rows || src.cols != dst.cols) return false;

    //on vérifie que le voisinage est impaire
    if(voisinage%2 != 1) return false;

    Rect rec_roi = Rect(0,0,voisinage,voisinage);
    int moyenne = 0;
    for (int x = 0; x < src.rows ; x++) {
        for (int y = 0; y < src.cols ; y++) {
            if(x < (voisinage-1)/2 || x > src.rows -1 - (voisinage-1)/2
            || y < (voisinage-1)/2 || y > src.cols -1 - (voisinage-1)/2)
            {
                dst.at<uchar>(x,y) = src.at<uchar>(x,y);
                cvtColor( dst, tempGray, COLOR_RGB2GRAY );

                setRawFrame(tempGray);
                return true;
            }else{
                moyenne = 0;
                rec_roi.y = x - (voisinage-1)/2;
                rec_roi.x = y - (voisinage-1)/2;

                Mat img_roi = src(rec_roi);//init

                for (int i = 0; i < voisinage; i++) {
                    for (int j = 0; j < voisinage; j++) {
                        moyenne += img_roi.at<uchar>(i,j);
                    }
                }

                moyenne /= voisinage*voisinage;
                dst.at<uchar>(x,y) = (uchar) moyenne;
                cvtColor( dst, tempGray, COLOR_RGB2GRAY );
                setRawFrame(tempGray);
                return true;

            }
        }
    }
    return false;

}

bool Frame::filterMedianNVG(int voisinage){

    Mat src = rawFrame;
    Mat dst = src.clone();
    //if(src.channels() != 1 || dst.channels() != 1) return ;
    if(src.rows != dst.rows || src.cols != dst.cols) return false;

    //on vérifie que le voisinage est impaire
    if(voisinage%2 != 1) return false;

    Rect rec_roi = Rect(0,0,voisinage,voisinage);
    int *voisins = new int[voisinage * voisinage];

    for (int x = 0; x < src.rows ; x++) {
        for (int y = 0; y < src.cols ; y++) {
            if(x < (voisinage-1)/2 || x > src.rows -1 - (voisinage-1)/2
               || y < (voisinage-1)/2 || y > src.cols -1 - (voisinage-1)/2)
            {
                dst.at<uchar>(x,y) = src.at<uchar>(x,y);
                setRawFrame(dst);
                return true;
            }else{

                rec_roi.y = x - (voisinage-1)/2;
                rec_roi.x = y - (voisinage-1)/2;

                Mat img_roi = src(rec_roi);//init

                for (int i = 0; i < voisinage; i++) {
                    for (int j = 0; j < voisinage; j++) {
                        voisins[i * voisinage + j] = img_roi.at<uchar>(i, j);
                        setRawFrame(dst);
                        return true;
                    }
                }
                    sort(voisins,voisins+(voisinage*voisinage));
                    dst.at<uchar>(x,y) = (uchar) voisins[(voisinage * voisinage-1)/2];

            }
        }
    }
    return false;
}


bool Frame::gaussianBlur()
{
    if(!rawFrame.empty())
    {
        Mat temp;
        GaussianBlur( rawFrame, temp, Size( 31, 31 ), 0, 0 );
        setRawFrame(temp);
        return true;
    }
    return false;
}
bool Frame::filtreLapGauss(){

    if(!rawFrame.empty())
    {
        Mat src,dst, gauss, lap;
        Point anchor;
        double delta;
        int ddepth;
        src = rawFrame;
        if(src.empty()) return false;
        anchor=Point(-1,-1);
        delta = 0;
        ddepth = -1;


        //creation de la matrice laplacien
        lap = Mat(3,3,CV_32FC1);
        lap.at<float>(0,1) = (float)-1.0;
        lap.at<float>(1,0) = (float)-1.0;
        lap.at<float>(1,2) = (float)-1.0;
        lap.at<float>(2,1) = (float)-1.0;
        lap.at<float>(1,1) = (float)4.0;


        //creation de la matrice gaussienne
        gauss = Mat::ones(3,3,CV_32FC1)/(float)1/16;
        gauss.at<float>(0,1) = (float)2.0/16;
        gauss.at<float>(1,0) = (float)2.0/16;
        gauss.at<float>(1,2) = (float)2.0/16;
        gauss.at<float>(2,1) = (float)2.0/16;
        gauss.at<float>(1,1) = (float)4.0/16;

        gauss = gauss+lap;

        filter2D(src,dst,ddepth,gauss,anchor,delta,BORDER_DEFAULT);
        setRawFrame(dst);
        return true;
    }
    return false;
}

bool Frame::erodeImage()
{
    if(!rawFrame.empty()){
        Mat temp;
        Mat kernel = getStructuringElement(MORPH_RECT, Size(16,16));
        erode(rawFrame, temp, kernel);
        setRawFrame(temp);
        return true;
    }
    return false;
}

bool Frame::dilateImage()
{
    if(!rawFrame.empty()){
        Mat temp = rawFrame;
        Mat kernel = getStructuringElement(MORPH_RECT, Size(6,6));
        dilate(temp, temp, kernel);
        setRawFrame(temp);
        return true;
    }
    return false;
}

bool Frame::filtreCanny()
{
    if(!rawFrame.empty())
    {
        Mat tempGray;
        cvtColor( rawFrame, tempGray, COLOR_BGR2GRAY );
        Canny( tempGray, tempGray, 0, 150, 3 );
        setRawFrame(tempGray);
        return true;
    }
    return false;
}

bool Frame::findHorizontalLines()
{
    if(!rawFrame.empty())
    {
        Mat temp;
        Mat binary;
        cvtColor(rawFrame, temp, COLOR_BGR2GRAY);
        adaptiveThreshold(temp, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
        int structureSize = binary.cols / 30;

        Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(structureSize, 1));

        erode(binary, binary, horizontalStructure, Point(-1, -1));
        dilate(binary, binary, horizontalStructure, Point(-1, -1));

        setRawFrame(binary);
        return true;
    }
    return false;
}

bool Frame::findVerticalLines()
{
    if(!rawFrame.empty())
    {
        Mat temp;
        Mat binary;
        cvtColor(rawFrame, temp, COLOR_BGR2GRAY);
        adaptiveThreshold(temp, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
        int structureSize = binary.rows / 30;

        Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, structureSize));

        erode(binary, binary, verticalStructure, Point(-1, -1));
        dilate(binary, binary, verticalStructure, Point(-1, -1));

        setRawFrame(binary);
        return true;
    }
    return false;
}

bool Frame::laplacianFilter()
{
    if(!rawFrame.empty())
    {
        Mat temp, dst;
        cvtColor(rawFrame, temp, COLOR_BGR2GRAY);
        Laplacian( temp, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
        convertScaleAbs(dst, dst);
        setRawFrame(dst);
        return true;
    }
    return false;
}

bool Frame::findImageContours()
{
    if(!rawFrame.empty())
    {
        Mat cannyTemp;

        cvtColor( rawFrame, cannyTemp, COLOR_BGR2GRAY );
        Canny( cannyTemp, cannyTemp, 0, 150, 3 );

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(cannyTemp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

        Mat drawing = Mat::zeros( cannyTemp.size(), CV_8UC3 );

        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( 256, 27, 120 );
            drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
        }
        setRawFrame(drawing);
        return true;
    }
    return false;
}

Frame::Frame(QQuickItem *parent): QQuickPaintedItem(parent)
{

}

void Frame::openImage(QString url)
{
    url.remove("file:/");
    rawFrame = imread(url.toStdString());
    convert2QImage();
}

void Frame::convert2QImage()
{
    Mat tempMat;
    cvtColor(rawFrame, tempMat, COLOR_RGB2BGR);
    QImage tempImage((uchar*) tempMat.data, tempMat.cols,tempMat.rows, tempMat.step, QImage::Format_RGB888);

    frame = tempImage;
    frame.detach();
    Frame::update();
    emit(frameChanged());// send signal
}


void Frame::paint(QPainter *painter)
{
    if (!frame.isNull())
    {
    frame.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    painter->drawImage(0, 0, frame, 0, 0, -1, -1, Qt::AutoColor);
    }

}

//////

