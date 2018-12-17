import QtQuick 2.0
import QtLocation 5.9

MapQuickItem {
id: marker
anchorPoint.x: image.width/2
anchorPoint.y: image.height
visible: true

sourceItem: Image {
    id:image
    height: 32
    width: 25
    source: "qrc:/assetsMenu/markerIcon.png"
}
}
