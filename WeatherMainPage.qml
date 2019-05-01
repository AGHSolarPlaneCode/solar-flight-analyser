import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent
    property string mainTemerature: (54.2).toFixed(0).toString();
    antialiasing: true
    FontLoader{
        id: standardFont
        source: "qrc:/assetsMenu/agency_fb.ttf"
    }


    Image {
        id: weatherMainIcon
        height: parent.height*0.35
        width: parent.width*0.2
        anchors {
            top: parent.top
            topMargin: parent.height*0.08
            right: parent.right
            rightMargin: parent.height*0.16
        }

        Rectangle {
            anchors.fill: parent
            color: "red"
        }

    }
    Text {
        id: weatherMainTemerature
        font.pixelSize: parent.height*0.12
        color: "white"
        font.family: standardFont.name
        anchors{
            right: weatherMainIcon.left
            top: weatherMainIcon.top
            rightMargin: parent.width*0.01
        }
        text: mainTemerature + "\u00B0" + "C"
    }
    Text{
        id: weatherCityName
        color: "white"
        text: "Cracow"
        font.family: standardFont.name
        font.pixelSize: parent.height*0.12
        anchors{
            top: weatherMainIcon.top
            left: root.left
            leftMargin:  root.height*0.15
        }
    }
    Rectangle {
        id: forcastRectangle
        width: parent.width*0.8
        color: "transparent"
        height: parent.height*0.35
        anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
            verticalCenterOffset: parent.height*0.15
        }
        Rectangle {
            id: weatherinfo1
            color: "blue"
            height: parent.height
            width: parent.width*0.184
            anchors.left: parent.left
        }
        Rectangle {
            id: weatherinfo2
            color: "blue"
            height: parent.height
            width: parent.width*0.184
            anchors.left: weatherinfo1.right
            anchors.leftMargin: parent.width*0.02
        }
        Rectangle {
            id: weatherinfo3
            color: "blue"
            height: parent.height
            width: parent.width*0.184
            anchors.left: weatherinfo2.right
            anchors.leftMargin: parent.width*0.02
        }
        Rectangle {
            id: weatherinfo4
            color: "blue"
            height: parent.height
            width: parent.width*0.184
            anchors.left: weatherinfo3.right
            anchors.leftMargin: parent.width*0.02
        }
        Rectangle {
            id: weatherinfo5
            color: "blue"
            height: parent.height
            width: parent.width*0.184
            anchors.left: weatherinfo4.right
            anchors.leftMargin: parent.width*0.02
        }
    }
    Rectangle {
        id: bottomRectangle
        color: "transparent"
        width: parent.width*0.6
        height: parent.height*0.1
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        Image {
            id: windIcon
            height: parent.height*0.7
            width: parent.height*0.8
            anchors.left: parent.left
            anchors.leftMargin: parent.height*0.1
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/assetsMenu/windIcon.png"
        }
        Rectangle {
            id: windDot1
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: windIcon.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot2
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: windDot1.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot3
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: windDot2.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot4
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: windDot3.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot5
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: windDot4.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }

        //-----------------------------
        Image {
            id: rainIcon
            height: parent.height*0.7
            width: parent.height*0.6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -parent.width*0.08
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/assetsMenu/rainIcon.png"
        }
        Rectangle {
            id: rainDot1
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: rainIcon.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot2
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: rainDot1.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot3
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: rainDot2.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot4
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: rainDot3.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot5
            height: parent.height*0.4
            width: parent.height*0.4
            radius: parent.height*0.4
            color: "yellow"
            anchors {
                left: rainDot4.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Text{
            id: sunText
            font.pixelSize: parent.height*0.8
            text: "5"
            color: "white"
            font.family: standardFont.name
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: parent.height*0.2
        }
        Image {
            id: sunIcon
            height: parent.height*0.7
            width: parent.height*0.7
            source: "qrc:/assetsMenu/sunLevel.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: sunText.left
            anchors.rightMargin: parent.height*0.2
        }


    }
}
