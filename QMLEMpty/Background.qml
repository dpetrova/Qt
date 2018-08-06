import QtQuick 2.0

//property binding
BackgroundForm {
    property Circle target: null
    focus: true

    Keys.onPressed: {
        if(event.key == Qt.Key_Plus) target.width = target.width + 10
        if(event.key == Qt.Key_Minus) target.width = target.width - 10
    }
}
