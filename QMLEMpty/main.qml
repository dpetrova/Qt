import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    id: window
    visible: true
    width: 640
    height: 820
    title: qsTr("Hello World")

    Background {
        id: background
        target: sender
        y: 0
        height: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: verticalLayout.bottom
        anchors.topMargin: -200

        Sender {
            id: sender
            y: 224
            btnColor: "#0000ff"
            btnText: "Sender"
            anchors.left: parent.left
            anchors.leftMargin: -267
            target: receiver
        }

        Receiver {
            id: receiver
            x: 71
            y: 224
            btnText: "Receiver"
            btnColor: "#ff0000"
            anchors.right: parent.right
            anchors.rightMargin: -271
            width: sender.width
        }
    }


    AnimalData {
        anchors.top: background.bottom
        anchors.topMargin: 230

    }

    VerticalLayout {
        id: verticalLayout
        width: window.width
        height: 300
        color: "#d6e93b"
        //access alias property of MainWindow.qml
        button2.onClicked: {
            label.text = qsTr("Just changed the name");

        }
    }

}
