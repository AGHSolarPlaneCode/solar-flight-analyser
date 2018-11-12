import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8

Item {
    id: root

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
                    color: "red"
                    height: parent.height*0.6
                    width: parent.width*0.002
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: parent.width*0.05
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
