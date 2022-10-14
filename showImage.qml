import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.ProjetComputerVision.frame 1.0

Page {
    //anchors.fill: parent

    Rectangle{
        id: bar
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Partie I"
            font.pointSize: 23
            color: "white"
            anchors.centerIn: parent
        }
    }

    ColumnLayout{
        id: imageContainer
        width: 884
        height: 420

        anchors.top: bar.bottom
        anchors.horizontalCenterOffset: 0
        anchors.topMargin: -2
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: picture
            source: "qrc:/visionLogo"
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height
            fillMode: Image.PreserveAspectFit
        }

        Frame{
            id: selectedImage
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height
            //visible: false
        }
    }


    Dialog{
        id: errorAlert
        title: "Error"
        Text {
            text: "First open an Image"
            anchors.centerIn: parent
        }

        standardButtons: StandardButton.Ok
    }

    FileDialog{
        id: imageDialog
        title: "Choose Image"
        folder: shortcuts.pictures
        onAccepted: {
            selectedImage.openImage(imageDialog.fileUrl);
            picture.visible = false;
            selectedImage.visible = true;
        }
    }


    Button {
        id: button
        x: 48
        y: 499
        text: "Open Image"
        onClicked: imageDialog.open()
    }

    Button {
        id: button1
        x: 48
        y: 556
        text: "Go Back"
        onClicked: loader.pop()
    }

    Button {
        id: button2
        x: 180
        y: 499
        text: "Moyen"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.filterMoyenNVG(25))
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.filterMoyenNVG(25)
            }
        }
    }


    Button {
        id: button3
        x: 180
        y: 556
        text: "Mediane"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.filterMedianNVG(25))
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.filterMedianNVG(25)
            }
        }
    }

    Button {
        id: button4
        x: 315
        y: 499
        text: "Erosion"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.erodeImage())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.erodeImage()
            }
        }
    }

    Button {
        id: button5
        x: 315
        y: 556
        text: "Dilatation"
        height: 40
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.dilateImage())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.dilateImage()
            }
        }
    }

    Button {
        id: button6
        x: 449
        y: 499
        text: "Laplacien"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.laplacianFilter())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.laplacianFilter()
            }
        }
    }

    Button {
        id: button7
        x: 449
        y: 556
        text: "Canny"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.filtreCanny())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.filtreCanny()
            }
        }
    }

    Button {
        id: button8
        x: 586
        y: 499
        text: "GaussianBlur"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.gaussianBlur())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.gaussianBlur()
            }
        }
    }

    Button {
        id: button9
        x: 586
        y: 556
        text: "LapGaussian"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.filtreLapGauss())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.filtreLapGauss()
            }
        }
    }

    Button {
        id: button10
        x: 717
        y: 499
        text: "H lines"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.findHorizontalLines())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.findHorizontalLines()
            }
        }
    }

    Button {
        id: button11
        x: 717
        y: 556
        text: "V Lines"
        onClicked: {
            if(imageDialog.fileUrl!="")

            selectedImage.openImage(imageDialog.fileUrl);
            if(!selectedImage.findVerticalLines())
            {
               errorAlert.open();
            }else
            {
                selectedImage.openImage(imageDialog.fileUrl);
                selectedImage.findVerticalLines()
            }
        }
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:620;width:884}
}
##^##*/
