import QtQuick 2.0

Circle {
    id: receiveBtn
    function receive(value){
        btnText = value
        clicknotify.running = true;
    }

    SequentialAnimation on btnColor {
        id: clicknotify
        running: false

        ColorAnimation {
            from: "red"
            to: "blue"
            duration: 250
        }
        ColorAnimation {
            from: "blue"
            to: "red"
            duration: 250
        }
    }
}
