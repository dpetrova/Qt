import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import "."

PageTheme {

    property string pictureName
    property int pictureIndex

    toolbarTitle: pictureName
    toolbarButtons: RowLayout {
        ToolButton {
            background: Image {
                source: "qrc:/res/icons/photo-delete.svg"
            }
            onClicked: {
                pictureModel.removeRows(pictureIndex, 1)
                stackView.pop()
            }
        }
    }

    ListView {
        id: pictureListView
        model: pictureModel
        anchors.fill: parent
        spacing: 5
        orientation: Qt.Horizontal
        snapMode: ListView.SnapOneItem //To swipe through each picture
        currentIndex: pictureIndex

        //when component is loaded view has to be updated to be positioned at correct index
        Component.onCompleted: {
            positionViewAtIndex(currentIndex, ListView.SnapPosition)
        }

        //get current index
        onMovementEnded: {
            currentIndex = itemAt(contentX, contentY).itemIndex
        }

        //change name of current showing image
        onCurrentItemChanged: {
            toolbarTitle = currentItem.itemName
        }


        delegate: Rectangle {
            property int itemIndex: index
            property string itemName: name

            // delegate is instanciated first so listview has no dimension,
            // causing positionViewAtIndex to fail...
            width: ListView.view.width == 0 ? parent.width : ListView.view.width
            height: pictureListView.height
            color: "transparent"

            Image {
                fillMode: Image.PreserveAspectFit
                cache: false
                width: parent.width
                height: parent.height
                source: "image://pictures/" + index + "/full"

            }
        }
    }
}
