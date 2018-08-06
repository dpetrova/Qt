import QtQuick 2.0

Item {
    width: 200
    height: 200
    property alias btnText: textBtn.text
    property alias btnColor: circleBtn.color


    Rectangle {
        id: circleBtn
        color: "#12837e"
        radius: width * 0.5
        anchors.fill: parent

        Text {
            id: textBtn
            x: 89
            y: 77
            color: "#ffffff"
            text: qsTr("Text")
            font.family: "Arial"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
        }
    }

}
