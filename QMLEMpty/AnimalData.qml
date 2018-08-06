import QtQuick 2.4
import QtQuick.Dialogs 1.2

AnimalDataForm {

    comboBox.model: ['Dog', 'Cat', 'Fish', 'Bird']

    button.onClicked: {
        var order = "Ordering: " + textField.text + "\r\n"
        order = order + "Your " + Math.round(dial.value) + "years old " + comboBox.currentText

        messageDialog.text = order
        messageDialog.open()
    }

    dial.onValueChanged: {
        progressBar.value = dial.value
        label1.text = Math.round(dial.value) + "years old"
    }

    MessageDialog {
        id: messageDialog
        title: "Hello World"
        text: ""
        onAccepted: Qt.quit()
    }

}
