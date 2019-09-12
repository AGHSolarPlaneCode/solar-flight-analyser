import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    Rectangle {
        id: root1
         anchors.fill: parent
         color: "#292B38"
         border {
             width: 1
             color: "#333644"
                }
        Slider{
            id: slider
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height*0.1
            width: parent.width*0.3
            from: 10
            value:  300
            to: 5000
        }
        Text{
            anchors.bottom: slider.bottom
            anchors.bottomMargin: slider.height*1
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: "Data flow deadTime: " + (slider.value).toFixed(0) + " ms"

        }
        }
}
