import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.ProjetComputerVision.frame 1.0

Page {

    Rectangle{
        id: bar
        width: parent.width
        height: parent.height * 0.1
        color: "orange"

        Label{
            text: "Partie II"
            font.pointSize: 23
            color: "white"
            anchors.centerIn: parent
        }

    }

    TextField {
        id: rec
        x: 334
        y: 186
        width: 98
        height: 40
        placeholderText: qsTr(" max 8")
    }

    Button {
        id: button
        x: 52
        y: 460
        text: qsTr("Generer la video")
        onClicked:
        {
            if(caree.text=="" || circle.text=="" || rec.text=="" || points.text==""||taillePoints.text==""|| dureePoints.text=="" ||path.text=="")
            {
                errorAlert.open();
            }else if(caree.text>8 || circle.text>8 || rec.text>8 || taillePoints.text>5 || points.text>150)
            {
                errorAlert2.open();
            }else

            {
                part2.partieII(caree.text,circle.text,rec.text,points.text,taillePoints.text,dureePoints.text,path.text)
            }
        }
      }

        TextField {
            id: circle
            x: 334
            y: 246
            width: 98
            height: 40
            placeholderText: qsTr("max 8")
        }

        Label {
            id: label
            x: 52
            y: 198
            width: 213
            height: 28
            text: qsTr("Choisissez le nombre de rectangles")
        }

        Label {
            id: label1
            x: 52
            y: 258
            width: 213
            height: 28
            text: qsTr("Choisissez le nombre de circles")
        }

        TextField {
            id: caree
            x: 334
            y: 311
            width: 98
            height: 40
            placeholderText: qsTr("max 8")
        }

        Label {
            id: label2
            x: 52
            y: 317
            width: 189
            height: 28
            text: qsTr("Choisissez le nombre de cares")
        }

        TextField {
            id: points
            x: 743
            y: 186
            width: 98
            height: 40
            placeholderText: qsTr("nombre")
        }

        Label {
            id: label3
            x: 495
            y: 198
            width: 189
            height: 28
            text: qsTr("Choisissez le nombre de points")
        }

        TextField {
            id: taillePoints
            x: 743
            y: 246
            width: 98
            height: 40
            placeholderText: qsTr("taille max 5")
        }

        Label {
            id: label4
            x: 495
            y: 258
            width: 189
            height: 28
            text: qsTr("Taille max des points")
        }

        TextField {
            id: dureePoints
            x: 743
            y: 305
            width: 98
            height: 40
            placeholderText: qsTr("duree(s)")
        }

        Label {
            id: label5
            x: 495
            y: 317
            width: 203
            height: 28
            text: qsTr("La duree d'apparition des points")
        }

        Button {
            id: button1
            x: 52
            y: 524
            width: 115
            height: 40
            text: qsTr("Go back")
            onClicked: loader.pop()

        }

        TextField {
            id: path
            x: 495
            y: 372
            width: 346
            height: 40
            placeholderText: qsTr("path")
        }

        Label {
            id: label6
            x: 52
            y: 384
            width: 262
            height: 28
            text: qsTr("Selectionner le path pour generer la video")
        }

        FileDialog{
            id: imageDialog
            title: "Choose Image"
            folder: shortcuts.home
            selectFolder: true
            onAccepted: {

                //picture.visible = false;
                var finalString
                        var urlString = imageDialog.fileUrl.toString()
                        if (urlString.startsWith("file:///")) {
                            // Check if is a windows string (8) or linux (7)
                            var sliceValue = urlString.charAt(9) === ':' ? 8 : 7
                            finalString = urlString.substring(sliceValue)
                        } else {
                            finalString = urlString
                        }
                         path.text=finalString
            }


        }
        Dialog{
            id: errorAlert
            title: "Error"
            Text {
                text: "Vous devez remplir tous les champs !"
                anchors.centerIn: parent
            }

            standardButtons: StandardButton.Ok
        }

        Dialog{
            id: errorAlert2
            title: "Error"
            Text {
                text: "Veillez respectez les valeurs limites pour chaque objet!"
                anchors.centerIn: parent
            }

            standardButtons: StandardButton.Ok
        }


        Button {
            id: button2
            x: 334
            y: 372
            text: qsTr("Open")
            onClicked: imageDialog.open()
        }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:620;width:884}
}
##^##*/
