import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

//frame with borders
Frame {

    //list view, need 3 things to display data: size, model, delegate
    ListView {
        //natural size of an item , frame will resize according this
        implicitWidth: 250
        implicitHeight: 250
        clip: true //any items outside of the view will not be visible

        //model can be JS array, C++ model, QMl list model, number
        model: ListModel {
            ListElement {
                //each property in ListElement is called row
                done: true
                description: "Study QML!!!!"
            }

            ListElement {
                done: false
                description: "Sleep well"
            }
        }

        //delegate describes how items to look
        delegate: RowLayout {
            width: parent.width
            CheckBox {
                checked: model.done //property from the model
                onClicked: model.done = checked
            }
            TextField {
                text: model.description //property from the model
                onEditingFinished: model.description = text
                Layout.fillWidth: true //text field width to be as much as possible to fill layout width
            }
        }
    }
}
