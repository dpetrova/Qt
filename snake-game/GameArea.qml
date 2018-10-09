import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import QtQuick 2.9 as QQ2 //to avoid name collisions
import "engine.js" as Engine

Entity {
    id: root
    property alias gameRoot: root
    property alias timerInterval: timer.interval
    property int initialTimeInterval: 80
    property int initialSnakeSize: 5
    property string state: ""

    //create a camera
    Camera {
        id: camera
        property real x: 24.5
        property real y: 14.0
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( x, y, 33.0 ) //camera position
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 ) //specifies the up vector of the camera (y)
        viewCenter: Qt.vector3d( x, y, 0.0 ) //point at center of the screen
    }

    Entity {
        id: sun
        components: [
            DirectionalLight {
                color: Qt.rgba(0.8, 0.8, 0.8, 0.5)
                worldDirection: Qt.vector3d(-0.6, -0.5, -1)
            }
        ]
    }

    //configure RenderSettings
    RenderSettings {
        id: frameFraph
        activeFrameGraph: ForwardRenderer {
            clearColor: Qt.rgba(0, 0, 0, 1) //means that the background will be pitch-black
            camera: camera //determine the viewport to be rendered
        }
    }

    //capture keyboard events; it is in charge of dispatching key events to the active KeyboardHandler
    KeyboardDevice {
        id: keyboardController
    }

    InputSettings {
        id: inputSettings
    }

    KeyboardHandler {
        id: input
        sourceDevice: keyboardController //attached to the controller
        focus: true
        onPressed: Engine.handleKeyEvent(event)
    }

    QQ2.Component.onCompleted: {
        console.log("Start game...");
        Engine.start();
        timer.start()
    }

    QQ2.Timer {
        id: timer
        interval: initialTimeInterval //repeat every 80 milliseconds
        repeat: true
        onTriggered: Engine.update()
    }

    Background {
        position: Qt.vector3d(camera.x, camera.y, 0)
        scale3D: Qt.vector3d(camera.x * 2, camera.y * 2, 0)
    }

    components: [frameFraph, input]
}
