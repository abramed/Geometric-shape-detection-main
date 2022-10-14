#include "partie3.h"



int partie3 ::partieIII(const QString &path) {
    // la capture video ici un fichier
    VideoCapture cap(path.toStdString());

    //Verification de la video

    if (!cap.isOpened())
        return 0;

    /*
        Declaration des valeurs du HSV
    */

    int lowHue = 0 ;
    int highHue = 179 ;

    int lowSaturation = 0 ;
    int highSaturation = 255 ;

    int lowValue = 50 ;
    int ihighValue = 254 ;


    while (true)
    {
        Mat imageSource; // declaration du Mat

        bool lectureVerifie = cap.read(imageSource); // lire une nouvelle video

        if (!lectureVerifie)
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat imageHSV;  // declaration du Mat

        cvtColor(imageSource, imageHSV, COLOR_RGB2HSV); // Converstion du frame de RGB a HSV et la stocker dans la matrice imageHSV

        Mat imageThresholded;

        inRange(imageHSV, Scalar(lowHue, lowSaturation, lowValue), Scalar(highHue, highSaturation, ihighValue), imageThresholded); //Threshold the image

        /*

         Appliquer l'erosion pour reduire le bruit

        */

        erode(imageThresholded, imageThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(imageThresholded, imageThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

        vector<int> listeDesPositionsCircle,listeDesPositionsCarre,listeDesPositionsRectangle; // declaration d'un vecteur qui vas contenir les positions de chaque objet

        /*

            En appliquant un filtre HSV sur l'image source et en parcourant notre matrice pixel par pixel en obtiendrons une liste
            contenant les positions de chaque objet et cela en executant la methode "detectPositionObjects"


        */

        detectPositionObjects(imageThresholded,&listeDesPositionsCircle,&listeDesPositionsCarre,&listeDesPositionsRectangle);

        int posx,posy,typeObject;
        string nomObject="";

        for(int i =0;i<listeDesPositionsCircle.size();i+=3)
        {
            posx = listeDesPositionsCircle.at(i);
            posy = listeDesPositionsCircle.at(i+1);
            typeObject = listeDesPositionsCircle.at(i+2);

            string getColor = to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[0]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[1]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[2]);

            if(typeObject==0) nomObject="Cercle";

            string output = "(" + to_string(posx) + "," + to_string(posy) + ", " + getColor + " | " + nomObject+")";
            putText(imageSource, output, Point(posy, posx), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));

        }

        for(int i =0;i<listeDesPositionsCarre.size();i+=3)
        {
            posx = listeDesPositionsCarre.at(i);
            posy = listeDesPositionsCarre.at(i+1);
            typeObject = listeDesPositionsCarre.at(i+2);

            string getColor = to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[0]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[1]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[2]);

            if(typeObject==1) nomObject="Carre";

            string output = "(" + to_string(posx) + "," + to_string(posy) + ", " + getColor + " | " + nomObject+")";
            putText(imageSource, output, Point(posy, posx), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));

        }



        for(int i =0;i<listeDesPositionsRectangle.size();i+=3)
        {
            posx = listeDesPositionsRectangle.at(i);
            posy = listeDesPositionsRectangle.at(i+1);
            typeObject = listeDesPositionsRectangle.at(i+2);

            string getColor = to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[0]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[1]) + " " + to_string(imageSource.at<Vec3b>(posx + 2, posy + 2)[2]);

            if(typeObject==2) nomObject="Rectangle";

            string output = "(" + to_string(posx) + "," + to_string(posy) + ", " + getColor + " | " + nomObject+")";
            putText(imageSource, output, Point(posy, posx), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255));

        }

        imshow("Partie 3", imageSource); //show the original image


        if(waitKey(10) == 27)
        {break;cap.release();}

    }
    destroyWindow("Partie 3");

    return 0;
}

partie3::partie3(QObject *parent) : QObject(parent)
{

}


int partie3 ::DetectionOfRectangle(int posx,int posy,Mat frame) {

    int segment1 = 0,segment2=0,segment3=0,segment4=0,temp1,temp2;
    temp1 = posx;
    temp2 = posy;


    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2) == 255 && (int)frame.at<uchar>(temp1 - 1, temp2) ==0 && (int)frame.at<uchar>(temp1 - 2, temp2) ==0) {
        segment1++;
        temp2++;
    }

    temp2 = posy;temp1 = posx;

    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2) == 255 && (int)frame.at<uchar>(temp1, temp2 - 1) != 255 ) {
        segment2++;
        temp1++;
    }
    temp2 = posy;temp1 = posx;
    while(posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2 + segment1-1) == 255 && (int)frame.at<uchar>(temp1, temp2 + segment1) != 255) {
        segment3++;
        temp1++;
    }
    temp2 = posy;temp1 = posx;

    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1+segment2-1, temp2) == 255 && (int)frame.at<uchar>(temp1+segment2, temp2) !=255) {
        segment4++;
        temp2++;
    }


    if ((segment1==segment4) && (segment1!=segment2) && (segment1!=segment3) && (segment4!=segment2) && (segment4!=segment3) && segment1 > 1) {
        return 1;
    }

    return 0;
}


int partie3 ::DetectionOfCircle(int posx, int posy, Mat frame) {
    int radius1 = 0,radius2=0,radius3=0,radius4=0,temp1,temp2;
    temp1 = posx;
    temp2 = posy;

    while (temp1 < frame.rows && (int)frame.at<uchar>(temp1, temp2) == 255) {
        radius1++;
        temp1++;
    }
    temp2 = posy;temp1 = posx;
    while (temp2 <= frame.cols && (int)temp1 + (radius1 / 2) < frame.rows && (int)frame.at<uchar>(temp1 + radius1/2, temp2) == 255) {
        radius2++;
        temp2++;
    }
    temp2 = posy;temp1 = posx;
    while (temp2 >= 0 && temp1 + radius1 / 2 < frame.rows &&(int)frame.at<uchar>(temp1 + radius1 / 2, temp2) == 255) {
        radius3++;
        temp2--;
    }
    temp2 = posy;temp1 = posx;
    while (temp2 >= 0  && (int)frame.at<uchar>(temp1, temp2) == 0 && temp2 > temp2-radius1/4) {
        radius4++;
        temp2--;
    }
    if (radius4 > 0) {
        return 0;
    }

    temp2 = posy;temp1 = posx;
    if ( radius2==radius3  || (radius3-radius2 <=1 && radius3-radius2>0) || (radius2-radius3 <=1 && radius2-radius3>0)) {
        if (temp2 + radius1 / 4 <= frame.cols && temp2-radius1/4 >= 0 && temp1-1 >= 0 && (int)frame.at<uchar>(temp1, temp2 + radius1 / 4) == 0 && (int)frame.at<uchar>(temp1, temp2 - radius1 / 4) == 0  && (int)frame.at<uchar>(temp1-1, temp2) == 0) return 1;
    }

    return 0;
}

int  partie3 ::DetectionOfCarre(int posx,int posy,Mat frame) {

    int segment1 = 0,segment2=0,segment3=0,segment4=0,temp1,temp2;
    temp1 = posx;
    temp2 = posy;

    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2) == 255 && (int)frame.at<uchar>(temp1 - 1, temp2) ==0 && (int)frame.at<uchar>(temp1 - 2, temp2) ==0) {
        segment1++;
        temp2++;
    }
        temp2 = posy;temp1 = posx;

    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2) == 255 && (int)frame.at<uchar>(temp1, temp2 - 1) != 255 ) {
        segment2++;
        temp1++;
    }
    temp2 = posy;temp1 = posx;

    while(posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1, temp2 + segment1-1) == 255 && (int)frame.at<uchar>(temp1, temp2 + segment1) != 255) {
        segment3++;
        temp1++;
    }
    temp2 = posy;temp1 = posx;

    while (posx>0 && posy>0 && posx<=frame.rows && posy<=frame.cols && (int)frame.at<uchar>(temp1+segment2-1, temp2) == 255 && (int)frame.at<uchar>(temp1+segment2, temp2) !=255) {
        segment4++;
        temp2++;
    }

    if ( segment1==segment2 && segment1==segment3 && segment1==segment4 ) {
        return 1;
    }

    return 0;
}



void partie3 :: detectPositionObjects(Mat frame,vector<int> *listeCircle,vector<int> *listeCarre,vector<int> *listeRectangle) {

    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++)
        {

            if ((int)frame.at<uchar>(i, j) > 200 && (int)frame.at<uchar>(i, j-1) == 0)
            {

                if (DetectionOfCircle(i, j, frame))
                {
                    (*listeCircle).push_back(i);
                    (*listeCircle).push_back(j);
                    (*listeCircle).push_back(0);

                }

                if (DetectionOfCarre(i,j,frame))
                {
                    (*listeCarre).push_back(i);
                    (*listeCarre).push_back(j);
                    (*listeCarre).push_back(1);
                }


                if (DetectionOfRectangle(i, j, frame))
                {
                    (*listeRectangle).push_back(i);
                    (*listeRectangle).push_back(j);
                    (*listeRectangle).push_back(2);
                }

            }
        }
    }


}
void partie3::setUrl(QString &value)
{
    value.remove("file://");
    url = value;
}


