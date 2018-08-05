import QtQuick 2.6
import QtQuick.Controls 2.0
import "." // QTBUG-34418, singletons require explicit import to load qmldir file

//main window
ApplicationWindow {

    //define a  property alias for the stackView
    //property alias is a simple reference to another existing property
    //this alias will be useful to access stackView from other QML components
    readonly property alias pageStack: stackView

    id: app
    visible: true
    width: 768
    height: 1280
    color: Style.windowBackground

    //application is constructed around the StackView component
    StackView {
        id: stackView //set the id property to allow our StackView to be identified and referred to by other QML objects
        anchors.fill: parent //anchors property will set stackView to fill its parent
        initialItem: AlbumListPage {} //initially loaded page
    }

    //on Android, onClosing will be executed each time the user presses the back button
    //to mimic a native Android application, we will first pop the last stacked page before really closing the application.
    onClosing: {
        if (Qt.platform.os == "android") {
            if (stackView.depth > 1) {
                close.accepted = false
                stackView.pop()
            }
        }
    }
}
