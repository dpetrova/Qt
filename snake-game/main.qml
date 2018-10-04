import QtQuick 2.10
import QtQuick.Controls 1.4
import QtQuick.Scene3D 2.0

Item {
    id: mainView
    width: 1280;
    height: 768
    visible: true

    property int score: 0
    readonly property alias window: mainView

    //bound the Escape key to the Qt.quit() signal
    Keys.onEscapePressed: {
        Qt.quit()
    }

    //define the HUD (heads up display) at the top of the screen, where the score will be displayed
    Rectangle {
        id: hud
        color: "#31363b"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top : parent.top
        height: 60

        Label {
            id: snakeSizeText
            anchors.centerIn: parent
            font.pointSize: 25
            color: "white"
            text: "Score: " + score
        }
    }

    //Qt3D content
    Scene3D {
        id: scene
        anchors.top: hud.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        focus: true //takes the focus of the window to be able to intercept keyboard events
        aspects: "input" //enables the input aspect to let the Qt3D engine process keyboard events

        GameArea {
           id: gameArea
           initialSnakeSize: 5
        }
    }

    OverlayItem {
        id: overlayItem
        anchors.fill: mainView
        visible: false

        //qml signal/slot connection
        Connections {
            target: gameArea
            onStateChanged: { //This item contains the state variable, so we can be notified when the state variable is updated using onStateChanged
                overlayItem.state = gameArea.state;
            }
        }
    }
}
