import QtQuick 2.0
import QtLocation 5.9
import "MarkerGenerator.js" as MarkerGenerator


MapQuickItem {
id: marker
anchorPoint.x: image.width/2
anchorPoint.y: image.height
visible: true
width: 25
height: 32
property bool isPositionMarker: true
signal markerDeleted()
property int number: 0

sourceItem: Image {
    id:image
    height: 32*0.6
    width: 25*0.6
    FontLoader{
        id:standardFont
        source: "qrc:/assetsMenu/agency_fb.ttf"
    }

    source: "qrc:/assetsMenu/markerIcon.png"
    Text {
        color: "white"
        height: parent.height*0.5
        text: number
        anchors {
            bottom: parent.top
            bottomMargin: parent.height*0.4
            horizontalCenter: parent.horizontalCenter
        }
        font.pixelSize: parent.height*0.8
        font.family: standardFont.name
        font.bold: true
    }
}
MouseArea {
    hoverEnabled: true
    acceptedButtons: Qt.RightButton
    anchors.fill:parent
    onClicked: {
        MarkerGenerator.removeMarker(marker);

    }


}

}
