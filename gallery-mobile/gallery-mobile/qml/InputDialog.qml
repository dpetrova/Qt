import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import "."

//take the generic Quick Dialog and modify it
Dialog {

    //configurable properties
    property string label: "New item"
    property string hint: ""
    property alias editText : editTextItem

    //use standart buttons to validate/cancel the dialog
    standardButtons: StandardButton.Ok | StandardButton.Cancel
    //focus editText when dialog becomes visible
    onVisibleChanged: {
        editTextItem.focus = true
        editTextItem.selectAll()
    }
    onButtonClicked: {
        //when dialog is hidden(OK/Cancel buttons are cklicked) hide the virtual keyboard
        Qt.inputMethod.hide();
    }

    Rectangle {

        implicitWidth: parent.width
        implicitHeight: 100

        ColumnLayout {
            Text {
                id: labelItem
                text: label
                color: Style.text
            }

            TextInput {
                id: editTextItem
                inputMethodHints: Qt.ImhPreferUppercase
                text: hint
                color: Style.text
            }
        }
    }
}
