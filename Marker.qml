import QtQuick 2.4
import QtLocation 5.9

// plane marker

MapQuickItem {

    id: marker
    property int rotate: -9;  // variable to change rotation
    property string city;
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    antialiasing: true

    sourceItem: Grid{

        horizontalItemAlignment: Grid.AlignHCenter // to rotate whole own axis
        Image {  // add plane marker
            id: image
            width:45
            height: 45
            rotation: rotate
            opacity: 60
            source: "qrc:/assetsMenu/planeMarker.png"
        }
    }
}
