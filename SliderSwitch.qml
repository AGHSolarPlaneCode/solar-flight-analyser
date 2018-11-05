import QtQuick 2.0

Item {
    property real size
id: root
width: size*1.3
height: size*1.1


    Rectangle{
        id: slider
    color: "#424D5C"
    height: size*0.4
    width: size
    radius: 0.8*size
    anchors {
    verticalCenter: parent.verticalCenter
    horizontalCenter: parent.horizontalCenter
    }
    }
    Rectangle {
        id: ball
        color: "#F1F1F1"
        width: size*0.5
        height: size*0.5
        radius: size*0.5
        border {
            color: "black"
            width: size*0.01
        }

        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: size/2
        }  

    }
    state: "off"
    states: [
        State {
                name: "off"
                PropertyChanges {
                    target: ball;
                    anchors.horizontalCenterOffset: -size/2
                    color: "#F1F1F1"
                }
                PropertyChanges {
                    target: slider
                    color: "#424D5C"

                }
            },
    State {
            name: "on"
            PropertyChanges {
                target: ball
                anchors.horizontalCenterOffset: size/2
                color : "#80CBC4"

            }
            PropertyChanges {
                target: slider
                color: "#80CBC4"

            }
        }


]
    MouseArea {
        anchors.fill: root
        hoverEnabled: true;
        onClicked: {
            root.state =(root.state == "on" ? root.state = "off" : root.state = "on")
        }
    }
}
