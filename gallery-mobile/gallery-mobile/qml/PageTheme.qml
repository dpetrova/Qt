import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import "."

//Page is a container control with a header and footer
Page {

    property alias toolbarButtons: buttonsLoader.sourceComponent
    property alias toolbarTitle: titleLabel.text

    //assign header to our ToolBarTheme (which is ToolBar)
    header: ToolBarTheme {
        RowLayout {
            anchors.fill: parent

            //display an image from gallery.qrc
            ToolButton {
                background: Image {
                    source: "qrc:/res/icons/back.svg"
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    }
                }
            }

            //page title
            Label {
                id: titleLabel
                Layout.fillWidth: true
                color: Style.text
                elide: Text.ElideRight
                font.pointSize: 20
            }

            //allow page dinamically add specific items
            Loader {
                Layout.alignment: Qt.AlignRight
                id: buttonsLoader
            }
        }
    }

    Rectangle {
        color: Style.pageBackground
        anchors.fill: parent
    }
}
