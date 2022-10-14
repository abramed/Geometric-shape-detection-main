import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

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
            width: 265
            height: 22
            text: "Welcome to our vision application "
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 1
            font.pointSize: 17
            color: "white"
            anchors.centerIn: parent
        }
    }


    Image {
        id: image
        width: 884
        height: 480
        visible: true
        anchors.fill: parent
        source: "qrc:/visionLogo"
        layer.format: ShaderEffectSource.RGBA
        anchors.rightMargin: 0
        anchors.bottomMargin: 159
        anchors.leftMargin: 0
        anchors.topMargin: 36
        smooth: false
        fillMode: Image.PreserveAspectFit
    }

    Button {
        id: imageButton
        x: 81
        y: 536
        text: "Partie I"
        layer.format: ShaderEffectSource.RGBA
        onClicked: loader.push("qrc:/showImage")
    }

    Button {
        id: videoButton
        x: 392
        y: 536
        text: "Partie II"
        onClicked: loader.push("qrc:/selectParams")
    }

    Button {
        id: button
        x: 708
        y: 536
        text: qsTr("Partie III")
        onClicked: loader.push("qrc:/showVideo")
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:620;width:884}
}
##^##*/
