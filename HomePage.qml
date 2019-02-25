import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8
import "MarkerGenerator.js" as MarkerGenerator
import "distanceCalculator.js" as DistanceCalculator
import "ShowErrors.js" as ShowErrors

Item {
    id: root
    property int numberOfPoint : 0  //get from JS function
    property real distanceToNextPoint: DistanceCalculator.distanceCalculate();
    property real longitude : planePosition.longitude //get from backend
    property real latitude: planePosition.latitude  //get from backend
    property string serverAdress : "LOCALHOST" //get from settings (database) or RequestDialog
    property bool connected: false
    property real transmitterDistance : 2.2515 //get from backend
    property real groundSpeed : Math.sqrt((adapter.Vx)^2+(adapter.Vy)^2) //get from backend
    property real altitude : adapter.Alt
    property var planePosition: QtPositioning.coordinate(adapter.Lat,adapter.Lon)
    property bool mapFollow: followSwitch.status
    property real xVelocity: adapter.Vx
    property real yVelocity: adapter.Vy
    property string fontFamily: standardFont.name
    property bool notify: false
    property string realPortS: "8080"
    property int numberOfError: 2 //get from backend
    property int numberOfWarning: 3 //get from backend
    property int numberOfInformation: 6 //get from backend
    property var jsonWarning: []
    property int errorIterator: 1
    property int informationIterator: 1
    property var errors: []
    property var informations: []



    onNumberOfErrorChanged: {
        if(!(numberOfError||numberOfWarning)){
            errorIcon.source="qrc:/assetsMenu/okIcon.png"
            errorTXT.text = "Everything works correctly"
            errorTXT.color = "#38865B"
        }
        else {
            ShowErrors.showErrors();
        }

    }
    Connections {
        target: request
        onSetAdress:{
            serverAdress = adressS
            realPortS = portS
        }

    }

    Component.onCompleted: {
        if(!(numberOfError||numberOfWarning)){
            errorIcon.source="qrc:/assetsMenu/okIcon.png"
            errorTXT.text = "Everything works correctly"
            errorTXT.color = "#38865B"
        }
        else {
            ShowErrors.showErrors();
        }
        if(!numberOfInformation){
            informationTXT.text = "Nothing to say"
        }
        else {
            ShowErrors.showInformation();
        }
    }
    onNumberOfInformationChanged: {
        if(!numberOfInformation){
            informationTXT.text = "Nothing to say"
        }
        else {
            ShowErrors.showInformation();
        }
    }

    onNumberOfWarningChanged: {
        if(!(numberOfError||numberOfWarning)){
            errorIcon.source="qrc:/assetsMenu/okIcon.png"
            errorTXT.text = "Everything works correctly"
            errorTXT.color = "#38865B"
        }
        else {
            ShowErrors.showErrors();
        }
    }
    RequestDialog{
        id:request
    }

    Timer {
        interval: 3000; running: true; repeat: true
        onTriggered: {
                if(errorIterator<(numberOfError+numberOfWarning)){
                errorIterator++;
                }
                else {errorIterator = 1;}
                if(informationIterator<numberOfInformation){
                informationIterator++;
                }
                else {informationIterator = 1;}
            if(!(numberOfError||numberOfWarning)){
                errorIcon.source="qrc:/assetsMenu/okIcon.png"
                errorTXT.text = "Everything works correctly"
                errorTXT.color = "#38865B"
            }
            else {
               ShowErrors.showErrors();
            }
            if(!numberOfInformation){
                informationTXT.text = "Nothing to say"
            }
            else {
                ShowErrors.showInformation();
            }
        }
    }

    FontLoader {
        id: standardFont
        source: "qrc:/assetsMenu/agency_fb.ttf"
    }



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
                realPort.color = "#38865B"
                realPort.text = "Port: " + realPortS
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
                 realPort.text = "---"
                 realPort.color = "#DB3D40"
                 transmitterTXT.text = "---"
            }

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
        width: 0.28*parent.width
        height: 0.28*parent.height
        property bool menuState: false
        anchors {
            top: parent.top
            topMargin: parent.height*0.35
            right: parent.right
            rightMargin: parent.width*0.05
        }

        Image {
            id: weatherBackground
            height: parent.height*1.2
            width: parent.width*1.1
            anchors.centerIn: parent
            source: "qrc:/assetsMenu/weatherBackGround.png"
        }
            Rectangle {
                id: weatherSideMenuBackground
                width: parent.width*0.15
                height: parent.height
                color: "transparent"
                SequentialAnimation {
                        id: weatherMenuRollBackAnim
                    NumberAnimation {
                        target: weatherRefreshButton
                        alwaysRunToEnd: true
                        property: "height"
                        duration: 330
                        easing.type: Easing.Linear
                        to: 0
                    }
                    NumberAnimation {
                        target: weatherLocationButton
                        alwaysRunToEnd: true
                        property: "height"
                        duration: 330
                        easing.type: Easing.Linear
                        to: 0
                    }
                    NumberAnimation {
                        target: weatherSettingsButton
                        alwaysRunToEnd: true
                        property: "height"
                        duration: 330
                        easing.type: Easing.Linear
                        to: 0
                    }
                }
                    SequentialAnimation {
                            id: weatherMenuRollOutAnim
                        NumberAnimation {
                            target: weatherSettingsButton
                            alwaysRunToEnd: true
                            property: "height"
                            duration: 330
                            easing.type: Easing.Linear
                            to: weatherSideMenuBackground.height*0.25
                        }
                        NumberAnimation {
                            target: weatherLocationButton
                            alwaysRunToEnd: true
                            property: "height"
                            duration: 330
                            easing.type: Easing.Linear
                            to: weatherSideMenuBackground.height*0.25
                        }
                        NumberAnimation {
                            target: weatherRefreshButton
                            alwaysRunToEnd: true
                            property: "height"
                            duration: 330
                            easing.type: Easing.Linear
                            to: weatherSideMenuBackground.height*0.25
                        }
                    }

                Rectangle {
                    id: weatherMainButton
                    width: parent.width
                    height: parent.height*0.25
                    color: "transparent"
                    anchors{
                        top: parent.top
                        horizontalCenter: parent.horizontalCenter
                    }
                    Image {
                        id: weatherMainButtonImage
                        source: "qrc:/assetsMenu/WeatherMenuButton.png"
                        width: parent.width
                        height: parent.height
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(weatherWidget.menuState){
                                    weatherMainButtonImage.source = "qrc:/assetsMenu/WeatherMenuButton.png"
                                    pageRollBackAnim.start();
                                    weatherMenuRollBackAnim.start();
                                    weatherWidget.menuState = false;
                                }
                                else {
                                    weatherMainButtonImage.source = "qrc:/assetsMenu/WeatherMenuButtonClicked.png"
                                    pageRollOutAnim.start();
                                    weatherMenuRollOutAnim.start();
                                    weatherWidget.menuState = true;

                                }
                            }
                        }
                    }
                }
                Image {
                    id: weatherRefreshButton
                    width: parent.width
                    anchors.top: weatherMainButton.bottom
                    anchors.horizontalCenter: weatherMainButton.horizontalCenter
                    source: "qrc:/assetsMenu/WeatherRefreshButton.png"
                    height: 0
                }
                Image {
                    id:weatherLocationButton
                    width: parent.width
                    anchors.top:  weatherRefreshButton.bottom
                    anchors.horizontalCenter: weatherMainButton.horizontalCenter
                    source: "qrc:/assetsMenu/WeatherLocationButton.png"
                    height: 0
                }
                Image {
                    id:weatherSettingsButton
                    width: parent.width
                    anchors.top:  weatherLocationButton.bottom
                    anchors.horizontalCenter: weatherMainButton.horizontalCenter
                    source: "qrc:/assetsMenu/WeatherSettingsButton.png"
                    height: 0
                }
            }
            Rectangle {
                id:weatherPageBackground
                height: parent.height
                width: parent.width - weatherSideMenuBackground.width
                color: "white"
                opacity: 0
                anchors{
                    right: parent.right
                }
                NumberAnimation on width{
                    id: pageRollOutAnim
                    alwaysRunToEnd: true
                    from: parent.width - weatherSideMenuBackground.width
                    to: (parent.width - weatherSideMenuBackground.width)*0.9
                }
                NumberAnimation on width{
                    id: pageRollBackAnim
                    alwaysRunToEnd: true
                    from: (parent.width - weatherSideMenuBackground.width)*0.9
                    to: parent.width - weatherSideMenuBackground.width
                }
            }

        }


    Item {
        id: transmitterWidget
        width: 0.13*parent.width
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
                font.family: fontFamily
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
        width: 0.28*parent.width
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
                        font.family: fontFamily
                        text: "Alerts"
                        color: "#999AA3"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                            horizontalCenterOffset: parent.width*2.2
                        }
                        Image {
                            source: "qrc:/assetsMenu/exampleAlertIcon2.png"
                            height: parent.height*0.6
                            width: parent.height*0.6
                            anchors{
                                left: parent.right
                                leftMargin: parent.height
                                verticalCenter: parent.verticalCenter
                            }
                            Text {
                                text: numberOfError
                                font.pointSize: 0.7*parent.height.toFixed(0);
                                color: "White"
                                anchors{
                                    verticalCenter: parent.verticalCenter
                                    left: parent.right
                                    leftMargin: 0.16*parent.width
                                }
                            }
                            Image {
                                source: "qrc:/assetsMenu/warningIcon.png"
                                height: parent.height
                                width: parent.width
                                anchors{
                                    left: parent.right
                                    verticalCenter: parent.verticalCenter
                                    leftMargin: 1*parent.width
                                }
                                Text {
                                    text: numberOfWarning
                                    font.pointSize: 0.7*parent.height.toFixed(0);
                                    color: "White"
                                    anchors{
                                        verticalCenter: parent.verticalCenter
                                        left: parent.right
                                        leftMargin: 0.1*parent.width
                                    }
                                }
                            }
                            Image {
                                source: "qrc:/assetsMenu/exampleAlertIcon.png"
                                height: parent.height
                                width: parent.width
                                anchors{
                                    left: parent.right
                                    verticalCenter: parent.verticalCenter
                                    leftMargin: 3.2*parent.width
                                }
                                Text {
                                    text: numberOfInformation
                                    font.pointSize: 0.7*parent.height.toFixed(0);
                                    color: "White"
                                    anchors{
                                        verticalCenter: parent.verticalCenter
                                        left: parent.right
                                        leftMargin: 0.2*parent.width
                                    }
                                }
                            }
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
                                id: informationTXT
                                font.family: fontFamily
                                font.pointSize: (parent.height*0.5).toFixed(0)
                                text: "Test text" //add text
                                color: "#2281D1"
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.right
                                    leftMargin: parent.width
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
                    id: errorIcon
                    height: parent.height*0.45
                    width: parent.height*0.45
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: parent.width*0.03
                    }

                    source: "qrc:/assetsMenu/exampleAlertIcon2.png"
                Text {
                    id: errorTXT
                    font.pointSize: (parent.height*0.5).toFixed(0)
                    text: "Test text"  //add text
                    font.family: fontFamily
                    color: "#DB3D40"
                    anchors {
                        verticalCenter: errorIcon.verticalCenter
                        left: errorIcon.right
                        leftMargin: errorIcon.width
                    }


                }
                }


            }
            }

        }
    }
    Item {
        id: graphWidget
        width: 0.4*parent.width
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
        width: 0.13*parent.width
        height: 0.30*parent.height
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
                source: "qrc:/assetsMenu/REQUEST STATUS.png"
            }
            MouseArea{
                anchors{
                    top: parent.top
                    topMargin: parent.height*0.1
                    right: parent.right
                    rightMargin: parent.width*0.1
                }
                enabled: true
                hoverEnabled: true
                width: parent.width*0.1
                height: parent.height*0.2
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    request.visible = true;

                }

            }

            Text {
                id: portTXT
                font.family: fontFamily
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
                font.family: fontFamily
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
            Text {
                id: realPort
                font.family: fontFamily
                color: "#DB3D40" //red
                font.pointSize: (parent.height*0.1).toFixed(0)
                anchors{
                    verticalCenter: port.verticalCenter
                    horizontalCenter: port.horizontalCenter
                    verticalCenterOffset: parent.height*0.15
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
            leftMargin: parent.width*0.47
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
                      font.family: fontFamily
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
                      font.family: fontFamily
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
                      font.family: fontFamily
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.06
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.052
                      }
                      font.pointSize: (parent.height*0.11).toFixed(0)
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
                      font.family: fontFamily
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
        width: parent.width*0.6
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
        if(mapWidget.state === "fullPage") {
            anim1.velocity = 1200
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
            mapWidget.width = parent.width*0.6
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
                        value: "***"  //add your own acces token
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
                         if(mapWidget.state == "windowed"||mapWidget.state =="started") {mapWidget.state = "fullPage"}
                         else {mapWidget.state = "windowed"}
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
                    font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
                        font.family: fontFamily
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
