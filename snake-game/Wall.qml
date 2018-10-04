import Qt3D.Core 2.0
import "factory.js" as Factory

//wall does not have any visual representation, it is invisible
GameEntity {
    id: root
    type: Factory.WALL_TYPE
    property alias position: transform.translation

    Transform {
        id: transform
    }

    components: [transform]
}
