import QtQuick 2.0

//signal slot
Circle {
    id: sendBtn

    property int counter: 0
    property Receiver target: null

    signal send(string value)
    onTargetChanged: send.connect(target.receive)

    MouseArea{
        anchors.fill: parent

        onClicked: {
            counter++
            parent.send(counter) //parent is the object in which this is (MouseArea is in Circle, so Circle is parent)
        }

        onPressed: parent.btnColor = "green"

        onReleased: parent.btnColor = "blue"

    }
}
