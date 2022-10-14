import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.ProjetComputerVision.frame 1.0

Page {
    //anchors.fill: parent


    Rectangle{
        id: bar
        x: 0
        y: 0
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Partie III"
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
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
        anchors.topMargin: -12
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: picture
            width: 884
            height: 420
            source: "qrc:/visionLogo"
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height
            fillMode: Image.PreserveAspectFit
        }

        Frame{
            id: selectedImage
            Layout.preferredWidth: imageContainer.width
            Layout.preferredHeight: imageContainer.height

        }
    }

    FileDialog{
        id: videoDialog
        title: "Choose Video"
        folder: shortcuts.movies
        onAccepted: {
            picture.visible = true;
            //selectedImage.visible = true;
            part3.partieIII(videoDialog.fileUrl);
        }
    }

    Button {
        id: button
        x: 30
        y: 515
        text: "Go Back"
        Layout.preferredWidth: parent.width*0.4
        onClicked: loader.pop()
    }

    Button {
        id: button1
        x: 170
        y: 515
        text: "Open Video"
        Layout.preferredWidth: parent.width*0.4
        onClicked:
        {
            videoDialog.open()

        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:620;width:884}
}
##^##*/
