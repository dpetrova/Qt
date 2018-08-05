//declare a QML singleton with theme data used by custom components
//register QML singleton in a plain text file qmldir
pragma Singleton
import QtQuick 2.0

//QtObject is a non-visual component
QtObject {
    property color text: "#000000"

    property color windowBackground: "#eff0f1"
    property color toolbarBackground: "#eff0f1"
    property color pageBackground: "#fcfcfc"
    property color buttonBackground: "#d0d1d2"

    property color itemHighlight: "#3daee9"
}
