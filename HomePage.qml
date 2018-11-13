import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8

Item {
    id: root
    property real distanceToNextPoint: 2.52545
    Item {

        id: mapWidget
        height: parent.height*0.5
        width: parent.width*0.5
        anchors {
            top: parent.top
            topMargin: parent.height*0.05
            left: parent.left
            leftMargin: parent.width*0.05

        }

        Rectangle {
            anchors.fill: parent
            color : "#2F3243"
            radius: parent.height*0.02
            Plugin {
                id: mapPlugin
                name: "osm"  //change to mapboxgl
            }

            Map { //map
               height: parent.height*0.8
               width: parent.width
                plugin: mapPlugin
                center: QtPositioning.coordinate(59.91, 10.75)// Oslo example
                zoomLevel: 12
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }

            }
            Rectangle { //topBar
                color: parent.color
                width: parent.width
                height: parent.height*0.2
                radius: parent.height*0.02
                anchors {
                    top: parent.top

                }
                Rectangle { //redspacer
                    id: redspacer
                    color: "#F21E41"
                    height: parent.height*0.6
                    width: parent.width*0.002
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: parent.width*0.03
                    }
                    Text {
                        id: numberOfPointsTXT
                        text: "0"
                        color: "#F5F0F0"
                        font.pointSize: parent.height*0.6
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        id: numberOfPointsTXTstatic
                        text: "Number of Points"
                        font.pointSize: numberOfPointsTXT.font.pointSize*0.4
                        color: "#707070"
                        anchors {
                            left: parent.left
                            leftMargin: parent.width*3
                            bottom: parent.bottom
                        }
                    }
                }
                Rectangle { //2-nd spacer
                    color: "#1E90F2"
                    height: parent.height*0.6
                    width: parent.width*0.002
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: numberOfPointsTXTstatic.width*1.5
                    }
                    Text {
                        id: distanceToNextPointTXT
                        text: distanceToNextPoint.toFixed(3).toString()+" km"
                        color: "#F5F0F0"
                        font.pointSize: parent.height*0.6
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Distance To Next Point"
                        font.pointSize: numberOfPointsTXT.font.pointSize*0.4
                        color: "#707070"
                        anchors {
                            left: parent.left
                            leftMargin: parent.width*3
                            bottom: parent.bottom
                }
            }

        }

    }
    }
    }
    Item {
        id: weatherWidget
    }
    Item {
        id: transmitterWidget
    }
    Item {
        id: alertsWidget
    }
    Item {
        id: graphWidget
    }
    Item {
        id: portWidget
    }
    Item {
        id: parametersWidget
    }
}
