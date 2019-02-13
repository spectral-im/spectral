import QtQuick 2.12
import QtGraphicalEffects 1.0

Image {
    id: image

    source: "qrc:/assets/img/icon.png"

    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: Rectangle {
            width: image.width
            height: image.width

            radius: width / 2
        }
    }
}
