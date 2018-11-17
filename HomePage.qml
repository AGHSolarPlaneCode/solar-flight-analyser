import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8

Item {
    id: root
    property int numberOfPoint : 5
    property real distanceToNextPoint: 2.52545
    property real longitude : 59.91325434
    property real latitude: 10.7534543
    property string porttxt : "COM8"
    property bool connected: false
    property real transmitterDistance : 2.2515
    onConnectedChanged: {
    console.log(connected)
    }

    Item {
        id: weatherWidget
        width: 0.35*parent.width
        height: 0.28*parent.height
        anchors {
            top: parent.top
            topMargin: parent.height*0.35
            right: parent.right
            rightMargin: parent.width*0.05
        }
        Rectangle {
            id: weatherBackground
            anchors.fill:parent
            color: "#2F3243"

        }

    }
    Item {
        id: transmitterWidget
        width: 0.16*parent.width
        height: 0.3*parent.height
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height*0.05
            left: alertsWidget.left
        }
        Rectangle {
            id: transmitterBackground
            anchors.fill:parent
            color: "#2F3243"
            Image {
                anchors.fill:parent
                source: "qrc:/assetsMenu/TRANSMITTER DISTANCE.png"
            }
            Text {
                color: {if(connected ==true )
                        color = "#38865B" //green
                    else {
                        color = "#DB3D40" //red
                    }
                }
                font.pointSize: parent.width*0.12
                anchors {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: parent.width*0.15
                    verticalCenterOffset: parent.height*0.1
                }

                text: {if(connected ==true )
                        text = transmitterDistance.toFixed(1).toString() + "m"
                    else {
                        text = "---"
                    }
                }


            }


        }
    }
    Item {
        id: alertsWidget
        width: 0.35*parent.width
        height: 0.28*parent.height
        anchors {
            top: parent.top
            topMargin: parent.height*0.05
            right: parent.right
            rightMargin: parent.width*0.05
        }
        Rectangle {
            id: alertsBackground
            anchors.fill:parent
            color: "#2F3243"

        }
    }
    Item {
        id: graphWidget
        width: 0.3*parent.width
        height: 0.36*parent.height
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height*0.05
            left: parent.left
            leftMargin: parent.width*0.05
        }
        Rectangle {
            id: graphBackground
            anchors.fill:parent
            color: "#2F3243"

        }
    }

    Item {
        id: portWidget
        width: 0.16*parent.width
        height: 0.3*parent.height
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height*0.05
            right: alertsWidget.right
        }
        Rectangle {
            id: portBackground
            anchors.fill:parent
            color: "#2F3243"
            Image {
                anchors.fill:parent
                source: "qrc:/assetsMenu/PORT STATUS.png"
            }
            Text {
                color: {if(connected ==true )
                        color = "#38865B" //green
                    else {
                        color = "#DB3D40" //red
                    }
                }
                font.pointSize: parent.height*0.05
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 0.01*parent.height
                    horizontalCenter: parent.horizontalCenter
                }

                text: {if(connected ==true )
                        text = "Correctly Connected"
                    else {
                        text = "Not Connected"
                    }
                }

            }
            Text {
                id: port
                color: {if(connected ==true )
                        color = "#38865B" //green
                    else {
                        color = "#DB3D40" //red
                    }
                }
                font.pointSize: parent.height*0.15
                anchors {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: parent.width*0.1
                    verticalCenterOffset: parent.height*0.1
                }

                text: {if(connected == true )
                        text = porttxt.toUpperCase()
                    else {
                        text = "---"
                    }
                }

            }

        }
    }
    Item {
        id: parametersWidget
        width: 0.18*parent.width
        height: 0.36*parent.height
        anchors {
            bottom: parent.bottom
            bottomMargin: parent.height*0.05
            left: parent.left
            leftMargin: parent.width*0.37
        }
        Rectangle {
            id: parametersBackground
            anchors.fill:parent
            color: "#2F3243"

        }
    }
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
                        text: numberOfPoint.toString()
                        color: "#F5F0F0"
                        font.pointSize: parent.parent.width*0.04
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
                        text: distanceToNextPoint.toFixed(2).toString()+" km"
                        color: "#F5F0F0"
                        font.pointSize: parent.parent.width*0.04
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
                Rectangle { //3-nd spacer
                    color: "#1E90F2"
                    height: parent.height*0.6
                    width: parent.width*0.002
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: numberOfPointsTXTstatic.width*3
                    }
                    Text {
                        id: longitudeTXT
                        text: longitude.toFixed(5).toString()
                        color: "#F5F0F0"
                        font.pointSize: parent.parent.width*0.04
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Longitude"
                        font.pointSize: longitudeTXT.font.pointSize*0.4
                        color: "#707070"
                        anchors {
                            left: parent.left
                            leftMargin: parent.width*3
                            bottom: parent.bottom
                }
            }

        }
                Rectangle { //4-nd spacer
                    color: "#E4D013"
                    height: parent.height*0.6
                    width: parent.width*0.002
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: numberOfPointsTXTstatic.width*4.5
                    }
                    Text {
                        id: latitudeTXT
                        text: latitude.toFixed(5).toString()
                        color: "#F5F0F0"
                        font.pointSize: parent.parent.width*0.04
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Longitude"
                        font.pointSize: longitudeTXT.font.pointSize*0.4
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
    }
}
