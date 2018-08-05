import QtQuick 2.0
import QtQuick.Controls 2.0
import "." //QML Singletons require an explicit import to load the qmldir file. The import "." is a workaround for this Qt bug

ToolBar {
     background: Rectangle {
         color: Style.toolbarBackground //access our singleton class Style
     }
}
