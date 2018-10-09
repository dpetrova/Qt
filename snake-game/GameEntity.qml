import Qt3D.Core 2.0

//The game area will be a grid where each cell contains an instance of one of our entities
Entity {
    property int type: 0
    property vector2d gridPosition: Qt.vector2d(0, 0)
}
