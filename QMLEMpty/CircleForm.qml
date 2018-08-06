import QtQuick 2.0

Item {
    width: 200
    height: 200
    property alias circleBtnColor: textBtn.color
    property alias circleBtnText: textBtn.text

    Rectangle {
        id: circleBtn
        radius: width * 0.5
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#65f0e9"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }
        }
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
