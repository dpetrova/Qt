import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: item1
    property alias textField: textField
    property alias comboBox: comboBox
    property alias button: button
    property alias label1: label1
    property alias progressBar: progressBar
    property alias dial: dial

    Pane {
        id: pane
        width: 640
        height: 250

        Row {
            id: row
            anchors.fill: parent
            layoutDirection: Qt.LeftToRight
            spacing: 20

            Column {
                id: column
                width: row.width/2 - 10
                height: row.height
                spacing: 10

                Label {
                    id: label
                    text: qsTr("Enter a name")
                }

                TextField {
                    id: textField
                }

                ComboBox {
                    id: comboBox
                }

                Button {
                    id: button
                    text: qsTr("Order")
                }
            }

            Column {
                id: column1
                width: row.width/2 -10
                height: row.height
                spacing: 10

                Dial {
                    id: dial
                    width: 160
                    height: 160
                    to: 20
                    from: 1
                    value: 1
                }

                ProgressBar {
                    id: progressBar
                    to: 20
                    from: 1
                    value: 1
                }

                Label {
                    id: label1
                    text: qsTr("1 Year Old")
                }
            }
        }
    }

}
