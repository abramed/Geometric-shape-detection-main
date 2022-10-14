//  ProjetVision
//
//  Created by Walid on 12/02/2021.
//

// Importer les bibliotheques importante //

#include "partie2.h"
#include <iostream>
#include <unistd.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>


#include <list>
using namespace cv;
using namespace std;

bool IsIntersectedCircles(int posX, int posX2, int posY, int posY2);
bool IsIntersectedCarre(int x, int x2, int y, int y2, int width, int height);
bool IsIntersectedRectangle(int x, int x2, int y, int y2, int width, int height);
bool IsIntersectedCircleCarre(int posX, int posY, int rcircle, int x, int y, int width, int height);
int  IsIntersectCarreRectangle(int x, int y, int posx, int posy, int type1, int type2);
bool IsIntersectedCircleRectangle(int posX, int posY, int rcircle, int x, int y, int width, int height);
void creatPoints(vector<Rect> *vecRec,vector<int> *vecRecColorB,vector<int> *vecRecColorG,vector<int> *vecRecColorR,int nbPoint,int tailleMaxPoints);
void setUrl(QString &value);


int Partie2 ::partieII(int nbcaree,int nbcircle,int nbrec,int nbpoints,int tailleMaxPoints,double dureePoints,const QString &path){

    /*
        Declaration de frame width et frame height
        Declaration d'un vecteur de (Points,Circle,Carre,Rectangle)
        Declaration d'un vecteur de couleurs pour (Points,Circle,Carre,Rectangle)

     */

    int frame_width = 1024;
    int frame_height = 1024;
    int durationChangeCircle=100;
    int durationChangeCarre=100;
    int durationChangeRectangle=100;

    int widthCarre=30, heightCarre=30;
    int widthRectangle=60,heightRectangle=30;
    int radius = 20;

    vector<Rect> vecPoints;
    vector<int> vecPointsColorB;
    vector<int> vecPointsColorG;
    vector<int> vecPointsColorR;

    vector<vector<int>> vecCircle,vecCarre,vecRectangle;
    vector<int> v1Circle,v2Carre,v3Rectangle;

    vector<vector<int>> vecColor,vecColor2,vecColor3;
    vector<int> v1Circlecolor,v2Carrecolor,v3Rectanglecolor;

    int nbCircle =nbcircle;
    int nbCarre =nbcaree;
    int nbRectangle =nbrec;

    /*
        Compresser et enregistrer un flux vidéo de format R G B A
    */


    VideoWriter video(path.toStdString()+"/demonstration.avi",VideoWriter::fourcc('R','G','B','A') , 50,Size(frame_width, frame_height),1);


    /*
        Creation d'un vecteur des points
    */


    creatPoints(&vecPoints,&vecPointsColorB,&vecPointsColorG,&vecPointsColorR,nbpoints,tailleMaxPoints);

    /*

        Lancer le start_time

    */

    clock_t start_time = clock();

    /*

        Preciser des positions de depart pour chaque objet

    */

    int positionDepart=rand()%3;
    int x1=0,x2=0,x3=0;

    int val =10;
    int position =3;

    if (positionDepart==0){
        x1 = 120;
        x2 = 500;
        x3 = 800;
    }

    if (positionDepart==1){
        x2 = 900;
        x3 = 400;
        x1 = 50;
    }

    if (positionDepart==2){
        x3 = 800;
        x2 = 550;
        x1 = 200;
    }

    /*

        Remplir les vecteurs(Circle,Carre,Rectangle) par des postions de depart et des couleurs Random

    */

    for(int i=0;i<nbCircle;i++)
    {
        v1Circle={x1,50+val*position,1,1};

        vecCircle.push_back(v1Circle);

        v1Circlecolor = {rand()%200+rand()%50,rand()%100+rand()%150,rand()%180+rand()%70};

        vecColor.push_back(v1Circlecolor);

        position = position + 10;

    }

    position = 3;
    for(int i=0;i<nbCarre;i++)
    {
        v2Carre={x2,60+val*position,1,1};

        vecCarre.push_back(v2Carre);

        v2Carrecolor = {rand()%200+rand()%50,rand()%150+rand()%90,rand()%120+rand()%130};

        vecColor2.push_back(v2Carrecolor);

        position = position + 10;

    }
    position = 3;
    for(int i=0;i<nbRectangle;i++)
    {
        v3Rectangle={x3,70+val*position,1,1};

        vecRectangle.push_back(v3Rectangle);

        v3Rectanglecolor = {rand()%150+rand()%100,rand()%90+rand()%150,rand()%90+rand()%160};

        vecColor3.push_back(v3Rectanglecolor);

        position = position + 10;
    }
    position = 3;


    /*
        Recuperer la duree d'apparition des points
     */

    dureePoints=dureePoints*1000000; // la durre est en micros seconde


    /*

        lancer une boucle true pour chaque frame

    */

    for (;;)
    {
        Mat frame;

        //Pour récupérer la frame et la convertir en Mat (et la décompresser)
        frame = Mat(1024,1024,CV_8UC3,Scalar(0,0,0));


        if (frame.empty()) break; // end of video stream


        clock_t end_time = clock();


        double duration = end_time - start_time ; // calculer le temps

        /*

         definir une duree pour le changement des points

        */


        if (duration>dureePoints) // la duree de changement des points par micro seconde
        {
            creatPoints(&vecPoints,&vecPointsColorB,&vecPointsColorG,&vecPointsColorR,nbpoints,tailleMaxPoints);
            start_time = clock();

        }

        /*

            Creation des objets (Points,Circle,Carre,Rectangle)

        */

        for(int i =0;i<vecPoints.size();i++)
        {
            rectangle(frame,vecPoints.at(i),Scalar(vecPointsColorB.at(i),vecPointsColorG.at(i),vecPointsColorR.at(i)),cv::FILLED,9);
        }

        for(int i=0;i<nbCircle;i++)
        {

            circle(frame, Point(vecCircle[i][0],vecCircle[i][1]),radius,Scalar(vecColor[i][0],vecColor[i][1],vecColor[i][2]),-1);
        }
        for(int i=0;i<nbCarre;i++)
        {
            rectangle(frame,Rect (vecCarre[i][0],vecCarre[i][1],widthCarre,heightCarre),Scalar(vecColor2[i][0],vecColor2[i][1],vecColor2[i][2]),cv::FILLED,9);
        }
        for(int i=0;i<nbRectangle;i++)
        {
            rectangle(frame,Rect (vecRectangle[i][0],vecRectangle[i][1],widthRectangle,heightRectangle), Scalar(vecColor3[i][0],vecColor3[i][1],vecColor3[i][2]),cv::FILLED,9);
        }



        /*

            Delimiter les objets a l'interieur de notre fenetre en testant
            le width et height du frame

        */

        /*

            Delimiter les objets par rapport au width du frame

        */

        for(int i=0;i<nbCircle;i++)
        {
            if (vecCircle[i][0]+radius > frame_width || vecCircle[i][0]-radius <=0)
            {

                vecCircle[i][2] = vecCircle[i][2]*-1;
                vecCircle[i][3] = vecCircle[i][3]*-1;

            }
        }

        for(int i=0;i<nbCarre;i++)
        {
            if (vecCarre[i][0]+widthCarre > frame_width || vecCarre[i][0] <=0)
            {

            vecCarre[i][2] = vecCarre[i][2]*-1;
            vecCarre[i][3] = vecCarre[i][3]*-1;

            }
        }
        for(int i=0;i<nbRectangle;i++)
        {
            if (vecRectangle[i][0]+widthRectangle > frame_width || vecRectangle[i][0] <=0)
            {

            vecRectangle[i][2] = vecRectangle[i][2]*-1;
            vecRectangle[i][3] = vecRectangle[i][3]*-1;

            }
        }


        /*

            Delimiter les objets par rapport au height du frame

        */

        for(int i=0;i<nbCircle;i++)
        {
            if (vecCircle[i][1]+radius > frame_height || vecCircle[i][1]-20 <0) vecCircle[i][3] = vecCircle[i][3]*-1;
        }

        for(int i=0;i<nbCarre;i++)
        {
            if (vecCarre[i][1]+heightCarre > frame_height || vecCarre[i][1] <0) vecCarre[i][3] = vecCarre[i][3]*-1;
        }
        for(int i=0;i<nbRectangle;i++)
        {
            if (vecRectangle[i][1]+heightRectangle > frame_height || vecRectangle[i][1] <0) vecRectangle[i][3] = vecRectangle[i][3]*-1;
        }

        /*

            Incrementer le pas pour chaque objet (Circle,Carre,Rectangle)

        */



        for(int i=0;i<nbCircle;i++)
        {

            vecCircle[i][0] += vecCircle[i][2];
            vecCircle[i][1] += vecCircle[i][3];

        }

        for(int i=0;i<nbCarre;i++)
        {

            vecCarre[i][0] += vecCarre[i][2];
            vecCarre[i][1] += vecCarre[i][3];

        }

        for(int i=0;i<nbRectangle;i++)
        {

            vecRectangle[i][0] += vecRectangle[i][2];
            vecRectangle[i][1] += vecRectangle[i][3];

        }


        /*

            Changement des positions de chaque objet en changent le pas aleatoirement en utilisant un random compris entre [0,2]

        */

        /*

            Changement des positions du circle en changent le pas aleatoirement en utilisant un random compris entre [0,2]

        */

        for(int i=0;i<nbCircle;i++)
        {
            if(durationChangeCircle==0)
            {
                vecCircle[i][2]=rand()%3-1;
                vecCircle[i][3]=rand()%3-1;
                durationChangeCircle=100;
            }else
            {
                durationChangeCircle--;
            }
        }

        /*

            Changement des positions du carre en changent le pas aleatoirement en utilisant un random compris entre [0,2]

        */

        for(int i=0;i<nbCarre;i++)
        {

            if(durationChangeCarre==0)
            {
                vecCarre[i][2]=rand()%3-1;
                vecCarre[i][3]=rand()%3-1;
                durationChangeCarre=100;
            }else
            {
                durationChangeCarre--;
            }
        }

        /*

            Changement des positions du rectangle en changent le pas aleatoirement en utilisant un random compris entre [0,2]

        */

        for(int i=0;i<nbRectangle;i++)
        {
            if(durationChangeRectangle==0)
            {
                vecRectangle[i][2]=rand()%3-1;
                vecRectangle[i][3]=rand()%3-1;
                durationChangeRectangle=100;
            }else
            {
                durationChangeRectangle--;
            }

        }

        /*

            Detection et ignorance de collisions entre objets

        */

        /*

            Detection et ignorance de collisions entre le circle et le circle

        */
        for(int i=0;i<nbCircle;i++)
        {
            for(int j=i+1;j<nbCircle;j++)
            {
                if(IsIntersectedCircles(vecCircle[i][0], vecCircle[j][0], vecCircle[i][1], vecCircle[j][1]))
                    {

                        vecCircle[i][2] = vecCircle[i][2]*-1;
                        vecCircle[i][3] = vecCircle[i][3]*-1;

                        vecCircle[j][2] = vecCircle[j][2]*-1;
                        vecCircle[j][3] = vecCircle[j][3]*-1;



                    }

            }
        }

        /*

            Detection et ignorance de collisions entre le carre et le carre

        */

        for(int i=0;i<nbCarre;i++)
        {
            for(int j=i+1;j<nbCarre;j++)
            {
                if(IsIntersectedCarre(vecCarre[i][0], vecCarre[j][0], vecCarre[i][1], vecCarre[j][1],widthCarre, heightCarre))
                    {

                        vecCarre[i][2] = vecCarre[i][2]*-1;
                        vecCarre[i][3] = vecCarre[i][3]*-1;

                        vecCarre[j][2] = vecCarre[j][2]*-1;
                        vecCarre[j][3] = vecCarre[j][3]*-1;


                    }

            }
        }

        /*

            Detection et ignorance de collisions entre le rectangle et le rectangle

        */

        for(int i=0;i<nbRectangle;i++)
        {
            for(int j=i+1;j<nbRectangle;j++)
            {
                if(IsIntersectedRectangle(vecRectangle[i][0], vecRectangle[j][0], vecRectangle[i][1], vecRectangle[j][1],widthRectangle, heightRectangle))
                    {

                        vecRectangle[i][2] = vecRectangle[i][2]*-1;
                        vecRectangle[i][3] = vecRectangle[i][3]*-1;

                        vecRectangle[j][2] = vecRectangle[j][2]*-1;
                        vecRectangle[j][3] = vecRectangle[j][3]*-1;


                    }

            }
        }

        /*

            Detection et ignorance de collisions entre le circle et le carre

        */


        for(int i=0;i<nbCircle;i++)
        {
            for(int j=0;j<nbCarre;j++)
            {


                if(IsIntersectedCircleCarre(vecCircle[i][0], vecCircle[i][1],15, vecCarre[j][0], vecCarre[j][1],widthCarre, heightCarre))
                    {

                        vecCircle[i][2] = vecCircle[i][2]*-1;
                        vecCircle[i][3] = vecCircle[i][3]*-1;

                        vecCarre[j][2] = vecCarre[j][2]*-1;
                        vecCarre[j][3] = vecCarre[j][3]*-1;


                    }

            }
        }

        /*

            Detection et ignorance de collisions entre le circle et le rectangle

        */

        for(int i=0;i<nbCircle;i++)
        {
            for(int j=0;j<nbRectangle;j++)
            {


                if(IsIntersectedCircleRectangle(vecCircle[i][0], vecCircle[i][1],15, vecRectangle[j][0], vecRectangle[j][1],widthRectangle, heightRectangle))
                    {

                        vecCircle[i][2] = vecCircle[i][2]*-1;
                        vecCircle[i][3] = vecCircle[i][3]*-1;

                        vecRectangle[j][2] = vecRectangle[j][2]*-1;
                        vecRectangle[j][3] = vecRectangle[j][3]*-1;


                    }

            }
        }

        /*

            Detection et ignorance de collisions entre le carre et le rectangle

        */

        for(int i=0;i<nbCarre;i++)
        {
            for(int j=0;j<nbRectangle;j++)
            {


                if(IsIntersectCarreRectangle(vecCarre[i][0], vecCarre[i][1],vecRectangle[j][0], vecRectangle[j][1],1, 2))
                    {

                        vecCarre[i][2] = vecCarre[i][2]*-1;
                        vecCarre[i][3] = vecCarre[i][3]*-1;

                        vecRectangle[j][2] = vecRectangle[j][2]*-1;
                        vecRectangle[j][3] = vecRectangle[j][3]*-1;


                    }

            }
        }


        video.write(frame); //
        if (waitKey(10) == 27) break; // stop capturing by pressing ESC
        imshow("Partie 2", frame);
    }

    //Pour relcher la capture on utilize :

    //Pour relcher le writer on utilize :
    video.release();
    destroyWindow("Partie 2");
    return 0;
}


bool Partie2 ::IsIntersectedCircles(int posX, int posX2, int posY, int posY2)
{
    int d2 = (posX-posX2)*(posX-posX2) + (posY-posY2)*(posY-posY2);
    if (d2 > (20 + 20)*(20+20)) return false;
    else return true;
}

bool Partie2 ::IsIntersectedRectangle(int x, int x2, int y, int y2, int width, int height)
{
    if (x < x2 + width && x + width > x2 && y < y2 + height && y + height > y2) return true;
    else return false;
}

bool Partie2 ::IsIntersectedCarre(int x, int x2, int y, int y2, int width, int height)
{
    if (x < x2 + width && x + width > x2 && y < y2 + height && y + height > y2) return true;
    else return false;
}

bool Partie2 ::IsIntersectedCircleRectangle(int posX, int posY, int rcircle, int x, int y, int width, int height)
{
    float rectangleCenterX = x + width / 2;
    float rectangleCenterY = y + height / 2;


    float w = width  / 2;
    float h = height / 2;

    // les valeurs absolues de la différence de x et de y entre le centre du cercle et le centre du rectangle.


    float dx = abs(posX - rectangleCenterX);
    float dy = abs(posY - rectangleCenterY);

    //le cas ou le cercle est assez éloigné du rectangle

    if (dx > (20 + w) || dy > (20 + h)) return false;

    float circleDistanceX = abs(posX - x - w);
    float circleDistanceY = abs(posY - y - h);


     //  le cercle est assez proche du rectangle
    if (circleDistanceX <= (w)) return true;

    if (circleDistanceY <= (h)) return true;


    //le cercle peut croiser le coin du rectangle

    float cornerDistanceSq = pow(circleDistanceX - w, 2) + pow(circleDistanceY - h, 2);

    return (cornerDistanceSq <= (pow(rcircle, 2)));

}

bool Partie2 ::IsIntersectedCircleCarre(int posX, int posY, int rcircle, int x, int y, int width, int height)
{
    float rectangleCenterX = x + width / 2;
    float rectangleCenterY = y + height / 2;


    float w = width  / 2;
    float h = height / 2;

    // les valeurs absolues de la différence de x et de y entre le centre du cercle et le centre du rectangle.

    float dx = abs(posX - rectangleCenterX);
    float dy = abs(posY - rectangleCenterY);

    if (dx > (20 + w) || dy > (20 + h)) return false; //le cas ou le cercle est assez éloigné du rectangle

    float circleDistanceX = abs(posX - x - w);
    float circleDistanceY = abs(posY - y - h);


    //  le cercle est assez proche du rectangle

    if (circleDistanceX <= (w)) return true;

    if (circleDistanceY <= (h)) return true;

    //le cercle peut croiser le coin du rectangle


    float cornerDistanceSq = pow(circleDistanceX - w, 2) + pow(circleDistanceY - h, 2);

    return (cornerDistanceSq <= (pow(rcircle, 2)));

}


void Partie2 ::creatPoints(vector<Rect> *vecRec,vector<int> *vecRecColorB,vector<int> *vecRecColorG,vector<int> *vecRecColorR,int nbPoint,int tailleMaxPoints)
{

    Rect r;
    int rColor;

    (*vecRec).clear();
    (*vecRecColorB).clear();
    (*vecRecColorG).clear();
    (*vecRecColorR).clear();

    for (int i=1;i<nbPoint;i+=1)
    {

        r =Rect(rand()%1024,rand()%1024,tailleMaxPoints,tailleMaxPoints);

        (*vecRec).push_back(r);
        rColor = rand()%255;
        (*vecRecColorB).push_back(rColor);
        rColor = rand()%255;
        (*vecRecColorG).push_back(rColor);
        rColor = rand()%255;
        (*vecRecColorR).push_back(rColor);
    }


}

int Partie2 ::IsIntersectCarreRectangle(int x, int y, int posx, int posy, int type1, int type2)
{
    if (posx + 30 * type2 < x || x + 30 * type1 < posx || y > posy + 30 || y + 30 < posy) {
        return 0;
    }
    else {

        return 1;
    }
}

Partie2::Partie2(QObject *parent) : QObject(parent)
{

}


void Partie2::setUrl(QString &value)
{
    value.remove("file://");
    url = value;
}

void Partie2::cppSlot()
{

}




