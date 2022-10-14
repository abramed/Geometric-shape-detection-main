import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 884
    height: 620
    title: qsTr("Vision App")

    // permet de recuperer une autre page
    StackView{
        id: loader
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: -38
        anchors.leftMargin: 0
        anchors.topMargin: 0
        initialItem: "qrc:/home"

    }
}

/*##^##
Designer {
    D{i:0;height:650;width:884}
}
##^##*/
