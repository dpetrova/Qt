import QtQuick 2.6
import QtQuick.Controls 2.0
import "."

//Now that AlbumListPage is a PageTheme element, we do not manipulate header directly
//need to set property toolbarTitle, to display "Albums"
PageTheme {

    toolbarTitle: "Albums"
    toolbarButtons: ToolButton {
        background: Image {
            //reference images stored in the .qrc file
            source: "qrc:/res/icons/album-add.svg"
        }
        onClicked: {
            newAlbumDialog.open() //open InputDialog
        }
    }

    //include Input dialog that we customized
    InputDialog {
        id: newAlbumDialog
        title: "New album"
        label: "Album name:"
        hint: "My Album"

        onAccepted: {
            //call function from C++ AlbumModel file (it is decorated as Q_INVOKABLE)
            albumModel.addAlbumFromName(editText.text)
        }
    }

    //Qt Quick ListView is the Qt Widget QListView equivalent
    //it displays a list of items from a provided model
    ListView {
        id: albumList
        model: albumModel //set model, this refers to C++ model from main.cpp because we used setContextProperty()
        spacing: 5
        anchors.fill: parent

        //must provide a delegate to describe how a row will be displayed
        delegate: Rectangle {
            width: parent.width
            height: 120
            color: Style.buttonBackground

            Text {
                text: name
                font.pointSize: 16
                color: Style.text
                anchors.verticalCenter: parent.verticalCenter
            }

            //to handle mouse click on a album row
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    albumList.currentIndex = index //update the current index of the list view
                    pictureModel.setAlbumId(id) //load the selected album
                    pageStack.push("qrc:/qml/AlbumPage.qml", { albumName: name, albumRowIndex: index }) //push album on the pageStack property, setting properties (key:value)
                }
            }
        }
    }
}
