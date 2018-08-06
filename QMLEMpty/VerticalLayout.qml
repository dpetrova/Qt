import QtQuick 2.4
import QtQuick.Controls 2.3

Rectangle {
    //to access  these from other qml files {key:value}, key is what we want, value is id of element
    property alias userPanel: userPanel
    property alias button2: button2
    property alias label: label
    height: 230


    Column {
        id: column
        anchors.bottomMargin: -155
        spacing: 3
        anchors.fill: parent

        Pane {
            id: userPanel
            height: 79
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Rectangle {
                id: rectangle
                x: 76
                y: 56
                color: "#e13131"
                anchors.fill: parent
            }

            Image {
                id: image
                width: 64
                height: 55
                fillMode: Image.PreserveAspectFit
                anchors.left: parent.left
                anchors.leftMargin: 0
                source: "../../../Pictures/fdo-admin-icons/avatar.png"
            }

            Label {
                id: label
                x: 247
                y: 14
                color: "#ffffff"
                text: qsTr("Jan Man 1")
                anchors.left: image.right
                anchors.leftMargin: 5
                font.pointSize: 17
            }

            Button {
                id: button
                x: 387
                y: 8
                icon.source:   "../../../Pictures/fdo-admin-icons/edit.png"
                width: 67
                height: 40
                text: qsTr("Edit")
                font.pointSize: 10
                padding: 5
                checkable: false
                background.opacity: 0
                checked: false
                autoRepeat: false
                flat: false
                highlighted: false
                display: AbstractButton.IconOnly
            }
        }

        Pane {
            id: userPanel1
            height: 79
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            Rectangle {
                id: rectangle1
                x: 76
                y: 56
                color: "#e13131"
                anchors.fill: parent
            }

            Image {
                id: image1
                width: 64
                height: 55
                anchors.leftMargin: 0
                source: "../../../Pictures/fdo-admin-icons/avatar.png"
                fillMode: Image.PreserveAspectFit
                anchors.left: parent.left
            }

            Label {
                id: label1
                x: 247
                y: 14
                color: "#ffffff"
                text: qsTr("Jan Man 1")
                anchors.leftMargin: 5
                font.pointSize: 17
                anchors.left: image1.right
            }

            Button {
                id: button1
                x: 385
                y: 8
                width: 67
                height: 40
                text: qsTr("Edit")
                icon.source: "../../../Pictures/fdo-admin-icons/edit.png"
                display: AbstractButton.IconOnly
                flat: false
                font.pointSize: 10
                autoRepeat: false
                checkable: false
                checked: false
                highlighted: false
                background.opacity: 0
                padding: 5
            }
            anchors.right: parent.right
            anchors.left: parent.left
        }
    }

    Button {
        id: button2
        x: 527
        y: 162
        text: qsTr("Push me")
        anchors.right: parent.right
        anchors.rightMargin: 13
    }
}
