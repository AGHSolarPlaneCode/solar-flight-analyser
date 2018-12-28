import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8
import "MarkerGenerator.js" as MarkerGenerator
import "distanceCalculator.js" as DistanceCalculator

Item {
    id: root
    property int numberOfPoint : 0  //get from JS function
    property real distanceToNextPoint: DistanceCalculator.distanceCalculate(); //get from JS function
    property real longitude : planePosition.longitude //get from backend
    property real latitude: planePosition.latitude  //get from backend
    property string serverAdress : "197.168.0.1" //get from settings (database)
    property bool connected: false //get from backend
    property real transmitterDistance : 2.2515 //get from backend
    property real groundSpeed : 25.46656 //get from backend
    property real altitude : 254.5465 //get from backend
    property real connectionPower : 98.65 //get from backend
    property var planePosition: QtPositioning.coordinate(59.91456456,10.75456456456)
    property bool mapFollow: followSwitch.status
    property real xVelocity: 25
    property real yVelocity: 31


    anchors.fill: parent
    onPlanePositionChanged: {
        if(mapFollow==true){
            map.center = planePosition
        }
    }
    onMapFollowChanged: {
        if(mapFollow==true){
            map.center = planePosition

        }
    }

    onNumberOfPointChanged: {
       distanceToNextPoint = DistanceCalculator.distanceCalculate();
                      }

    onConnectedChanged: {

        if(connected == true )
        {
                controller.doUpdates(true)
                transmitterTXT.color = "#38865B" //green
                portTXT.color = "#38865B"
                portTXT.text = "Correctly Connected"
                port.color = "#38865B"
                port.text = serverAdress.toUpperCase()
                transmitterTXT.text = transmitterDistance.toFixed(1).toString() + "m"
        }
            else
            {
                 controller.doUpdates(false)
                 transmitterTXT.color = "#DB3D40"
                 portTXT.color = "#DB3D40"//red
                 portTXT.text = "Not Connected"
                 port.color = "#DB3D40"
                 port.text =  "---"
                 transmitterTXT.text = "---"
            }

    //console.log(connected)
    }
    Rectangle {
        id: mainPage
        anchors.fill: parent
        color: "#292B38"
        border {
            width: 1
            color: "#333644"
        }

        onHeightChanged: {
            if(mapWidget.state == "windowed") {
                mapWidget.height = parent.height*0.5
            }
            else if(mapWidget.state == "fullPage") {
                mapWidget.height = parent.height
            }
        }
        onWidthChanged: {
            if(mapWidget.state == "windowed") {
                mapWidget.width = parent.width*0.5
            }
            else if(mapWidget.state == "fullPage") {
                mapWidget.width = parent.width
            }
        }


                }//for tests

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
                id: transmitterTXT
                color: "#DB3D40"
                font.pointSize: (parent.width*0.12).toFixed(0)
                anchors {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: parent.width*0.15
                    verticalCenterOffset: parent.height*0.1
                }

                text: "---"

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
            radius: height*0.02
            Rectangle { //tob bar
                id: alertsTopBar
                height: parent.height
                width: parent.width
                radius: parent.height*0.02
                color: "#313646"
                anchors {
                    top:parent.top
                    horizontalCenter: parent.horizontalCenter

                }
                Image { //properties squares
                    height: parent.height*0.15
                    width: parent.width*0.01
                    source: "qrc:/assetsMenu/PROPERTIES SQUARES.png"
                    anchors {
                        top: parent.top
                        topMargin: parent.height*0.12
                        right: parent.right
                        rightMargin: 0.03*parent.width
                    }
                }
                Image { //alert icon
                    height: parent.height*0.2
                    width: parent.width*0.08
                    source: "qrc:/assetsMenu/NotificationIcon.png"
                    anchors {
                        top: parent.top
                        topMargin: parent.height*0.07
                        left: parent.left
                        leftMargin: 0.03*parent.width
                    }
                    Text {
                        font.pointSize: (parent.height*0.8).toFixed(0)
                        text: "Alerts"
                        color: "#999AA3"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                            horizontalCenterOffset: parent.width*2.2
                        }

                    }

                }
                Rectangle { //bottom alert
                    radius: parent.radius
                    color: "#424D5C"
                    height: parent.height*0.6
                    width: parent.width
                    anchors{
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter

                    }
                    Image {
                        height: parent.height*0.25
                        width: parent.height*0.25
                        source: "qrc:/assetsMenu/exampleAlertIcon.png"
                        anchors {
                            left: parent.left
                            leftMargin: 0.03*parent.width
                            bottom: parent.bottom
                            bottomMargin: parent.height*0.1
                        }
                            Text {
                                id: bottomAlertText
                                font.pointSize: (parent.height*0.5).toFixed(0)
                                text: "Test text" //add text
                                color: "#2281D1"
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    horizontalCenter: parent.horizontalCenter
                                    horizontalCenterOffset: parent.width*2.2
                                }

                        }
                    }
                }
                Rectangle{ //spacer
                    id: alertSpacer
                    width: parent.width
                    height: parent.height*0.005
                    color: "#707070"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        verticalCenterOffset: parent.height*0.2
                    }

                }
                Rectangle { //middle bar
                color: "#424D5C"
                height: parent.height*0.35
                width: parent.width
                anchors{
                    bottom: alertSpacer.top
                    horizontalCenter: parent.horizontalCenter

                }
                Image {
                    height: parent.height*0.45
                    width: parent.height*0.45
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: parent.width*0.03
                    }

                    source: "qrc:/assetsMenu/exampleAlertIcon2.png"
                Text {
                    font.pointSize: (parent.height*0.5).toFixed(0)
                    text: "Test text"  //add text
                    color: "#DB3D40"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        horizontalCenter: parent.horizontalCenter
                        horizontalCenterOffset: parent.width*2.2
                    }


                }
                }


            }
            }

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
            Image { //static chart just for now
                anchors.fill:parent
                source: "qrc:/assetsMenu/CHARTS.png"
            }

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
                source: "qrc:/assetsMenu/Server status.png"
            }
            Text {
                id: portTXT
                color: "#DB3D40" //red
                font.pointSize: (parent.height*0.05).toFixed(0)
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 0.01*parent.height
                    horizontalCenter: parent.horizontalCenter
                }
                text:"Not Connected"


            }
            Text {
                id: port
                color: "#DB3D40" //red
                font.pointSize: (parent.height*0.1).toFixed(0)
                anchors {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                    horizontalCenterOffset: parent.width*0.1
                    verticalCenterOffset: parent.height*0.1
                }

                text: "---"

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
        Rectangle
        {
            id: parametersBackground
            anchors.fill:parent
            color: "#292B38"
              Rectangle { //Ground speed
                  width: parent.width*0.5
                  height: parent.height*0.5
                  anchors.top: parent.top
                  anchors.left:parent.left
                  anchors.leftMargin: 0.08*width
                  color: "transparent"
                  Image {
                      width: parent.width*0.98
                      height: parent.height*0.98
                      anchors.centerIn: parent
                      source: "qrc:/assetsMenu/SpeedParametr.png"

                  }
                  Text {
                      color: "#F5F0F0"
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.06
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.052
                      }
                      font.pointSize: (parent.height*0.11).toFixed(0)
                      text: groundSpeed.toFixed(0).toString() + "km/h"
                  }
              }
              Rectangle { //Heigth
                  width: parent.width*0.5
                  height: parent.height*0.5
                  anchors.top: parent.top
                  anchors.right: parent.right
                  anchors.rightMargin: -0.1*width
                  color: "transparent"
                  Image {
                      width: parent.width
                      height: parent.height
                      anchors.centerIn: parent
                      source: "qrc:/assetsMenu/Height.png"

                  }
                  Text {
                      color: "#F5F0F0"
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.06
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.052
                      }
                      font.pointSize: (parent.height*0.12).toFixed(0)
                      text: altitude.toFixed(0).toString() + "m"
                  }
              }
              Rectangle { //connectionPower
                  width: parent.width*0.5
                  height: parent.height*0.5
                  anchors.bottom: parent.bottom
                  anchors.left:parent.left
                  anchors.leftMargin: 0.08*width
                  color: "transparent"
                  Image {
                      width: parent.width*0.98
                      height: parent.height*0.98
                      anchors.centerIn: parent
                      source: "qrc:/assetsMenu/connectionPower.png"

                  }
                  Text {
                      color: "#F5F0F0"
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.06
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.052
                      }
                      font.pointSize: (parent.height*0.11).toFixed(0)
                      text: connectionPower.toFixed(0).toString() + "%"
                  }
              }
              Rectangle { //Distance
                  width: parent.width*0.5
                  height: parent.height*0.5
                  anchors.bottom: parent.bottom
                  anchors.right: parent.right
                  anchors.rightMargin: -0.1*width
                  color: "transparent"
                  Image {
                      width: parent.width
                      height: parent.height
                      anchors.centerIn: parent
                      source: "qrc:/assetsMenu/Distance.png"

                  }
                  Text {
                      color: "#F5F0F0"
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.06
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.052
                      }
                      font.pointSize: (parent.height*0.12).toFixed(0)
                      text: distanceToNextPoint.toFixed(2).toString() + "km"
                  }
              }

        }
    }
    Item {
        id: mapWidget
        height: parent.height*0.5
        width: parent.width*0.5
        state: "started"
        anchors {
            top: parent.top
            topMargin: parent.height*0.05
            left: parent.left
            leftMargin: parent.width*0.05

        }
        Behavior on width { SmoothedAnimation {id:anim1
                velocity: Number.POSITIVE_INFINITY
            } }
        Behavior on height { SmoothedAnimation {id:anim2
                velocity: Number.POSITIVE_INFINITY
            } }
        Behavior on anchors.topMargin  { SmoothedAnimation {id:anim3
                velocity: Number.POSITIVE_INFINITY } }
        Behavior on anchors.leftMargin { SmoothedAnimation {id:anim4
                velocity: Number.POSITIVE_INFINITY } }
        states: [
        State {
                name: "windowed"

            },
        State {
                name: "fullPage"
            }

        ]


    onStateChanged: {
        console.log("Map State Changed")
        if(mapWidget.state === "fullPage") {
            anim1.velocity = 1450
            anim2.velocity = 750
            anim3.velocity = 70
            anim4.velocity = 120
            mapWidget.anchors.topMargin = 0
            mapWidget.anchors.leftMargin = 0
            mapWidget.width = parent.width
            mapWidget.height = parent.height
        }
        else if(mapWidget.state === "windowed") {
            mapWidget.anchors.topMargin = 0.05*parent.height
            mapWidget.anchors.leftMargin = 0.05*parent.width
            mapWidget.width = parent.width*0.5
            mapWidget.height = parent.height*0.5

        }
    }




        Rectangle {
            anchors.fill: parent
            color : "#2F3243"
            //radius: parent.height*0.02

            Map { //map
               id: map
               anchors.fill: parent

                anchors {
                    bottom: parent.bottom
                    left: parent.left
                }
                onCenterChanged: {
                    if(mapFollow==true){
                        center = planePosition
                    }
                }
                plugin: Plugin{
                    name: "mapbox"
                    PluginParameter{
                        name: "mapbox.access_token"
                        value: "pk.eyJ1IjoiYndpZWN6b3JlayIsImEiOiJjanExNmtpbTcwczA3NDNubTc4N3FheGZpIn0.TPJiiIL-8v0UH250L6LKfg"  //add your own acces token
                    }
                    PluginParameter{
                        name: "mapbox.mapping.map_id"
                        value: "mapbox.dark"
                    }
                }
                DropArea {
                    anchors.fill: parent
                    onDropped: {
                        var coord = map.toCoordinate(Qt.point((drop.x-10), (drop.y+9)));
                        MarkerGenerator.createMarkerObjects(coord);
                        anim.running = true;

                    }
                }
                PlaneMarker {
                    id: planePositionMarker
                    coordinate: planePosition
                    planeAzimut: Math.atan2(xVelocity,yVelocity)*180/Math.PI //The azimuth = arctan((x2 –x1)/(y2 –y1))
                }

            }

            Rectangle { //bottomBar
                id: bottomBar
                color: parent.color
                width: parent.width
                height: parent.parent.parent.height*0.1*0.5
                opacity: 0.85
                anchors {
                    bottom: parent.bottom
                    left: parent.left

                }
                Rectangle {
                width: parent.height*0.95
                height: parent.height*0.95
                color: "transparent"
                opacity: 1
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                Image {
                    id : fullPageIcon
                    width: parent.width*0.6
                    height: parent.height*0.6
                    anchors.centerIn: parent
                    source: "qrc:/assetsMenu/mapFullScreen.png"

                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Mouse area here")
                        console.log(mapWidget.state)
                         if(mapWidget.state == "windowed"||mapWidget.state =="started") {mapWidget.state = "fullPage"}
                         else {mapWidget.state = "windowed"}
                         console.log(mapWidget.state)
                    }
                }
                }
                Rectangle {
                width: parent.height*0.95
                height: parent.height*0.95
                color: "transparent"
                opacity: 1
                anchors.left: parent.left
                anchors.leftMargin: parent.height*0.5
                anchors.verticalCenter: parent.verticalCenter
                SliderSwitch {
                    id: followSwitch
                    anchors.fill: parent
                    size: parent.width*0.8
                    onstatecolor: "#009688"
                    offstatecolor: "#424D5C"
                    state: "on"
                }
                Text{
                    text: "Follow"
                    font.pointSize: (parent.height*0.3).toFixed(0)
                    anchors.left: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: parent.width*0.2
                    color: "#707070"



            }
                }

            }



            Rectangle { //topBar
                color: parent.color
                width: parent.width
                height: parent.parent.parent.height*0.2*0.5
                //radius: parent.height*0.02
                opacity: 0.85
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
                        leftMargin: root.width*0.015
                    }
                    Text {
                        id: numberOfPointsTXT
                        text: numberOfPoint.toString()
                        color: "#F5F0F0"
                        font.pointSize: (root.width*0.016).toFixed(0)
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
                        font.pointSize: (numberOfPointsTXT.font.pointSize*0.4).toFixed(0)
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
                        leftMargin: numberOfPointsTXTstatic.width*1.8
                    }
                    Text {
                        id: distanceToNextPointTXT
                        text: distanceToNextPoint.toFixed(2).toString()+" km"
                        color: "#F5F0F0"
                        font.pointSize: (root.width*0.016).toFixed(0)
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Distance To Next Point"
                        font.pointSize: (numberOfPointsTXT.font.pointSize*0.4).toFixed(0)
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
                        leftMargin: numberOfPointsTXTstatic.width*3.5
                    }
                    Text {
                        id: longitudeTXT
                        text: longitude.toFixed(5).toString()
                        color: "#F5F0F0"
                        font.pointSize: (root.width*0.016).toFixed(0)
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Longitude"
                        font.pointSize: (longitudeTXT.font.pointSize*0.4).toFixed(0)
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
                        leftMargin: numberOfPointsTXTstatic.width*5.5
                    }
                    Text {
                        id: latitudeTXT
                        text: latitude.toFixed(5).toString()
                        color: "#F5F0F0"
                        font.pointSize: (root.width*0.016).toFixed(0)
                        anchors {
                            left: parent.right
                            leftMargin: parent.width*2
                            verticalCenter: parent.verticalCenter
                            verticalCenterOffset: -parent.height*0.2
                        }

                        }
                    Text {
                        text: "Latitude"
                        font.pointSize: (longitudeTXT.font.pointSize*0.4).toFixed(0)
                        color: "#707070"
                        anchors {
                            left: parent.left
                            leftMargin: parent.width*3
                            bottom: parent.bottom
                }
            }

        }

    }
            Image {
                id: dragAndDropIcon
                source: "qrc:/assetsMenu/markerIcon.png"
                width: bottomBar.height*0.55
                height: bottomBar.height*0.8
                x: mapWidget.width*0.95
                y: root.height*0.03
                Drag.active: markerDragAndDropMouseArea.drag.active
                Drag.hotSpot.x: 20
                Drag.hotSpot.y: 20
                SequentialAnimation {
                    id: anim
                    running: false
                    NumberAnimation { target: dragAndDropIcon; property: "opacity"; to: 0; duration: 500 }
                    PropertyAction { target: dragAndDropIcon; property: "x"; value: mapWidget.width*0.95 }
                    PropertyAction { target: dragAndDropIcon; property: "y"; value: root.height*0.03 }
                    NumberAnimation { target: dragAndDropIcon; property: "opacity"; to: 1; duration: 500 }
                }
                MouseArea {
                    id: markerDragAndDropMouseArea
                    anchors.fill: parent
                    drag.target: dragAndDropIcon
                    propagateComposedEvents: true
                    onReleased: {
                        dragAndDropIcon.Drag.drop()
                    }
                }

            }
    }

    }
}
