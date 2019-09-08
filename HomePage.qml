import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.8
import QtQuick.Controls 2.4
import "MarkerGenerator.js" as MarkerGenerator
import "distanceCalculator.js" as DistanceCalculator
import "ShowErrors.js" as ShowErrors
import QtCharts 2.0
import "WeatherPageGenerator.js" as WeatherPageGenerator
import "interfaceFunction.js" as Interface
import "listViewFun.js" as ListFun

Item {
    id: root
    signal connectionChanged(var connectionState)
    property int numberOfPoint : 0  //get from JS function
    property double distanceToNextPoint: DistanceCalculator.distanceCalculate();
    property double longitude: NaN
    property double latitude: NaN
    property string serverAdress : NaN //get from settings (database) or RequestDialog
    property double transmitterDistance : NaN //get from backend
    property double groundSpeed : NaN //get from backend
    property double altitude : NaN
    property var planePosition: QtPositioning.coordinate(NaN,NaN)
    property bool mapFollow: followSwitch.status
    property double xVelocity: NaN
    property double yVelocity: NaN
    property string fontFamily: standardFont.name
    property bool notify: true
    property string realPortS: NaN
//    property int numberOfInformation: 0
//    property int numberOfWarning: 0
//    property int errorIterator: 0
//    property var jsonError: 0
//    property int numberOfError: 0
//    property int informationIterator: 0
//    property var requestError: 0
//    property var informations: []
//    property var sslerror: []

    property real timeElapsed:0
    property bool connected: startButtonState
    property double hdg: NaN
    property real batteryPercentage: 99.5456

    Connections{
        target: adapter
        onTelemetryDataChanged:{
          hdg = adapter.hdg
          longitude = (adapter.lon).toFixed(8).toString()
          latitude = (adapter.lat).toFixed(8).toString()
          altitude = (adapter.alt).toFixed(1).toString()
          groundSpeed = (DistanceCalculator.sqrt((((adapter.vx))^2)+((adapter.vy)^2))).toFixed(1).toString()
          xVelocity = adapter.vx
          yVelocity = adapter.vy
          planePosition = QtPositioning.coordinate(latitude, longitude)
//          transmitterTXT.color = "#38865B" //green
//          portTXT.color = "#38865B"
//          portTXT.text = "Correctly Connected"
//          port.color = "#38865B"
//          realPort.color = "#38865B"
//          realPort.text = "Port: " + realPortS
//          port.text = serverAdress.toUpperCase()
//          transmitterTXT.text = (batteryPercentage.toFixed(1)).toString() + "%"
//            distanceToNextPoint = DistanceCalculator.distanceCalculate()

          if(mapFollow == true){
              map.center = planePosition
          }
        }

        onShowDialogAddressWindow:{
            Interface.showDialog();
        }
    }



    onConnectedChanged: {
        if(connected === true )
        {
            transmitterTXT.color = "#38865B" //green
            portTXT.color = "#38865B"
            portTXT.text = "Correctly Connected"
            port.color = "#38865B"
            realPort.color = "#38865B"
            realPort.text = "Port: " + realPortS
            port.text = serverAdress.toUpperCase()
            transmitterTXT.text = (batteryPercentage.toFixed(1)).toString() + "%"
              distanceToNextPoint = DistanceCalculator.distanceCalculate()
        }else{
            transmitterTXT.color = "#DB3D40"
            portTXT.color = "#DB3D40"//red
            portTXT.text = "Not Connected"
            port.color = "#DB3D40"
            port.text =  "---"
            realPort.text = "---"
            realPort.color = "#DB3D40"
            transmitterTXT.text = "---"
            latitude = NaN;
            longitude = NaN;
            groundSpeed = NaN;
            planePosition = QtPositioning.coordinate(NaN, NaN)
            hdg = NaN;
            altitude = NaN;
        }
    }

//    Connections{
//        target: error
//        onSendJSONErrors:{
//            jsonError = err
//        }
//        onSendRequestError:{
//            requestError = err
//        }
//        onSendSslVector:{
//            sslerror = data
//        }

//    }
    onBatteryPercentageChanged: {
        if(connected == true){
            transmitterTXT.text = transmitterDistance.toFixed(0).toString() + "%"
            if(transmitterDistance.toFixed(0)<=20){
                transmitterTXT.color = "#ff5900"

            }
        }
    }


    Connections {
        target: request
        onSetAdress:{
            serverAdress = adressS
            realPortS = portS
        }

    }


//    Connections {
//        //target: //get target from context
//        onSendJSONErrors:{
//            jsonError = err
//        }
//        onSendRequestError:{
//            requestError = err
//        }
//        onSendSslVector:{
//            sslerror = data
//        }
//    }












    FontLoader {
        id: standardFont
        source: "qrc:/assetsMenu/agency_fb.ttf"
    }



    anchors.fill: parent
    onPlanePositionChanged: {
    }
    onMapFollowChanged: {
        if(mapFollow==true){
            map.center = planePosition

        }
    }

    onNumberOfPointChanged: {
       distanceToNextPoint = DistanceCalculator.distanceCalculate();
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
            if(mapWidget.state === "windowed") {
                mapWidget.height = parent.height*0.5
            }
            else if(mapWidget.state === "fullPage") {
                mapWidget.height = parent.height
            }
        }
        onWidthChanged: {
            if(mapWidget.state === "windowed") {
                mapWidget.width = parent.width*0.5
            }
            else if(mapWidget.state === "fullPage") {
                mapWidget.width = parent.width
            }
        }


                }

    Item {
        id: weatherWidget
        property int page: 1


        width: 0.28*parent.width
        height: 0.28*parent.height
        property bool menuState: false
        anchors {
            top: parent.top
            topMargin: parent.height*0.35
            right: parent.right
            rightMargin: parent.width*0.05
        }

        Component.onCompleted: {
            WeatherPageGenerator.showPage(pageList, 1)
            }

        Image {
            id: weatherBackground
            height: parent.height*1.2
            width: parent.width*1.1
            anchors.centerIn: parent
            source: "qrc:/assetsMenu/weatherBackGround.png"
        }
        Rectangle {
            id:weatherPageBackground
            height: parent.height
            width: parent.width*0.8
            color: "transparent"
            anchors{
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            ListModel {
                id: pageList
            }

        }
            Rectangle {
                id: weatherSideMenuBackground
                width: parent.width*0.2
                color: "transparent"
                //opacity: 0.55
                height: parent.height
                anchors{
                    left:parent.left
                    verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    id: backgroundBar
                    width: parent.width*0.1
                    height: parent.height*0.6
                    color: "#F2B81E"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        horizontalCenter: parent.horizontalCenter
                    }
                }
                Rectangle {
                    id: locationCircle
                    color: "#2F3243"
                    width: parent.width*0.6*1.1
                    height: width
                    radius: width
                    border{
                        color :"#F2B81E"
                        width: radius*0.02
                    }
                    anchors {
                        verticalCenter: backgroundBar.verticalCenter
                        horizontalCenter: backgroundBar.horizontalCenter
                    }
                    Image {
                        source: "qrc:/assetsMenu/locationIcon.png"
                        antialiasing: true
                        anchors{
                            centerIn: parent
                        }
                    }
                    MouseArea {
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                        onEntered: {
                            parent.color = "#292B37"
                        }
                        onExited: {
                            parent.color = "#2F3243"
                        }
                    }
                }
                Rectangle {
                    id: refreshCircle
                    color: "#2F3243"
                    width: parent.width*0.6*1.1
                    height: width
                    radius: width
                    border{
                        color :"#F2B81E"
                        width: radius*0.02
                    }
                    anchors {
                        verticalCenter: backgroundBar.top
                        horizontalCenter: backgroundBar.horizontalCenter
                    }
                    Image {
                        source: "qrc:/assetsMenu/updateIcon.png"
                        antialiasing: true
                        anchors{
                            centerIn: parent
                        }
                    }
                    MouseArea {
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                        onEntered: {
                            parent.color = "#292B37"
                        }
                        onExited: {
                            parent.color = "#2F3243"
                        }
                    }
                }
                Rectangle {
                    id: settingsCircle
                    color: "#2F3243"
                    width: parent.width*0.6*1.1
                    height: width
                    radius: width
                    border{
                        color :"#F2B81E"
                        width: radius*0.02
                    }
                    anchors {
                        verticalCenter: backgroundBar.bottom
                        horizontalCenter: backgroundBar.horizontalCenter
                    }
                    Image {
                        source: "qrc:/assetsMenu/settingsIconWeather.png"
                        antialiasing: true
                        anchors{
                            centerIn: parent
                        }
                    }
                    MouseArea {
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        anchors.fill: parent
                        onEntered: {
                            parent.color = "#292B37"
                        }
                        onExited: {
                            parent.color = "#2F3243"
                        }
                    }
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
                source: "qrc:/assetsMenu/BatteryStatus.png"
            }
            Text{
                text: "Battery\nStatus"
                wrapMode: text.WordWrap
                width: parent.width*0.5
                font.family: standardFont.name
                font.pixelSize: 0.12*parent.height.toFixed(0)
                color: "#FFFFFF"
                opacity: 0.55
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: parent.height*0.04
                    leftMargin: parent.width*0.08
                }
            }

            Text {
                id: transmitterTXT
                color: "#DB3D40"
                font.pointSize: (parent.width*0.13).toFixed(0)
                font.family: fontFamily
                font.bold: false
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
    Connections{
        target: errorManager
        onSendMessageToMainNotification:{
            errorModel.append({"msg": message, "type" : type})
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
            color: "#424D5C"
            radius: height*0.02

            //================= TOPBAR
            Rectangle { //tob bar
                id: alertsTopBar
                height: parent.height*0.3
                width: parent.width
                radius: parent.height*0.02
                color: "#313646"
                anchors {
                    top:parent.top
                    horizontalCenter: parent.horizontalCenter

                }
                Image { //change to trashbin Icon
                    id: clearListViewButton
                    source: "qrc:/assetsMenu/CLEARALLALERTS.svg"
                    height: parent.height*0.7
                    width: height
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: alertsPropertiesSquares.left
                        rightMargin: width*0.5
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            errorModel.clear()
                        }
                    }
                }
//                Rectangle { //change to trashbin Icon
//                    color: "red"
//                    height: parent.height*0.5
//                    width: height
//                    anchors {
//                        verticalCenter: parent.verticalCenter
//                        right: clearListViewButton.left
//                        rightMargin: width*0.5
//                    }
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: {
//                            errorModel.append({"msg": "Error occurred no. 404", "type" : 1})
//                            errorModel.append({"msg": "Strong wind \'25 m/s \'", "type" : 2})
//                        }
//                    }
//                }

                Image { //properties squares
                    id: alertsPropertiesSquares
                    height: parent.height*0.5
                    width: parent.width*0.012
                    opacity: 0.75
                    source: "qrc:/assetsMenu/PROPERTIES SQUARES.png"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: 0.03*parent.width
                    }
                }
                Image { //alert icon
                    id:alertsIcon
                    height: parent.height*0.36
                    width: height
                    source: "qrc:/assetsMenu/NotificationIcon.png"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 0.03*parent.width
                    }
                }
                    Text {
                        font.pointSize: 0.8*alertsIcon.height.toFixed(0)
                        font.family: standardFont.name
                        text: ("Alerts").toUpperCase()
                        color: "#999AA3"
                        font.bold: true
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: alertsIcon.right
                            leftMargin: alertsIcon.width*0.3
                        }

                    }

                }
            //================= ListView
            ListView{
                 width: alertsBackground.width
                 model: errorModel
                 //anim
                 add: Transition {
                           NumberAnimation { properties: "y"; from: alertsBackground.height; duration: 300 }
                       }
                 remove: Transition {
                     NumberAnimation { properties: "opacity"; to: 0; duration: 300 }
                 }
                 move: Transition{NumberAnimation { properties: "y"; duration: 300}}

                 displaced: Transition {
                     SequentialAnimation{
                     PauseAnimation{duration: 200}
                     NumberAnimation { properties: "y"; duration: 300 }
                     }
                 }
                 //-----------------------anim
                 clip: true
                 spacing: alertsBackground.height*0.02
                 ScrollBar.vertical: ScrollBar {
                 active: true
                 anchors {
                     right: parent.right
                     verticalCenter: parent.verticalCenter
                 }
                 }
                 delegate: delegate
                 anchors {
                 top: alertsTopBar.bottom
                 topMargin: alertsBackground.height*0.02
                 horizontalCenter: alertsBackground.horizontalCenter
                 bottom: parent.bottom
                 }

                   }

            }
        Component{

        id: delegate

        Rectangle {
        color: "#363b4d"
        width: alertsBackground.width
        height: alertsBackground.height*0.2
        radius: height*0.2
        border{
            color: "#F2B81E"
            width: height*0.02
        }
        Image {
            id: messageTypeIcon
            height: parent.height*0.6
            source: {
                if(type==0){
                   source = "qrc:/assetsMenu/okIcon.png"
                }else if(type ==1){
                    source = "qrc:/assetsMenu/exampleAlertIcon2.png"
                }
                else {source = "qrc:/assetsMenu/exampleAlertIcon.png"}
            }

            width: height
            anchors{
                left: parent.left
                leftMargin: height*0.3
                verticalCenter: parent.verticalCenter
            }
        }

        Text {
             anchors{
                 left: messageTypeIcon.right
                 leftMargin: messageTypeIcon.width*0.2
                 verticalCenter: parent.verticalCenter
             }
             color: "white"
             font.pixelSize: messageTypeIcon.height
             font.family: standardFont.name
             text: msg
                }

        Image {
            anchors.right: parent.right
            anchors.rightMargin: width*0.5
            anchors.verticalCenter: parent.verticalCenter
            width: height
            visible: {
                if(!type){
                    visible = false
                }
                else{ visible = true
                }
            }
            height: parent.height*0.7
            source: "qrc:/assetsMenu/CLEARONEALERT.svg"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    errorModel.remove(index)
                }
            }
        }
        }
        }
        ListModel {
            id: errorModel
            onCountChanged: {
                ListFun.checkList()
            }
            ListElement {
                type: 0
                msg: "No problem detected"
                selected: false
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
            left: mapWidget.left
        }
        Rectangle {
            id: graphBackground
            anchors.fill: parent
            color: "#292B38"
            Rectangle {
                id: chartBar
                anchors {
                    top: parent.top
                    bottom: chartRect.top
                    left: parent.left
                    right: parent.right
                }
                color: "#313646"
                radius: parent.width * 0.02
                Image {
                    id: speedHeightBar
                    source: "qrc:/assetsMenu/speed_height_bar.png"
                    anchors.fill: parent
                    width: parent.width
                    height: parent.height
                }
//                Rectangle {
//                    id: chartsIcon
//                    anchors {
//                        left: parent.left
//                        top: parent.top
//                        leftMargin: 10
//                        topMargin: 5
//                    }
//                    Image {
//                        id: chartsIconImage
//                        source: "qrc:/assetsMenu/chartsIcon.png"
////                        width: parent.width
////                        height: parent.height
//                    }
//                }
                Image {
                    id: chartsIcon
                    source: "qrc:/assetsMenu/chartsIcon.png"
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: parent.width*0.02
                    }
                    width: parent.width * 0.04
                    height: parent.height * 0.45
                }
//                Rectangle {
//                    id: chartsTextRect
//                    anchors {
//                        left: chartsIcon.right
//                        top: parent.top
//                        leftMargin: 40
//                        bottom: chartsIcon.bottom
//                    }
//                    Text {
//                        id: chartsText
//                        text: qsTr("Speed/Height chart")
//                        color: "#999AA3"
//                        font {
//                            pointSize: parent.height * 4.5
//                            family: fontFamily
//                        }
//                    }
//                }
                Text {
                    id: chartText
                    text: ("Speed/Height chart").toUpperCase()
                    color: "#999AA3"
                    font.bold: true
                    font {
                        pointSize: parent.width * 0.03
                        family: fontFamily
                    }
                    anchors {
                        verticalCenter: chartsIcon.verticalCenter
                        left: chartsIcon.right
                        leftMargin: parent.width*0.02
                        verticalCenterOffset: parent.height*0.17
                    }
                    width: parent.width * 0.6
                    height: parent.height * 0.8
                }
            }
            Rectangle {
                id: chartRect
//                anchors.fill: parent
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: parent.height * 0.8
//                color: parent.color
                color: "#25263B"
                ChartView {
                    anchors.fill: parent
                    margins.bottom: 0
                    margins.top: 0
                    margins.left: 0
                    margins.right: 0
                    antialiasing: true
                    backgroundColor: "#25263B"
                    legend.visible: false
                    // Define x-axis to be used with the series instead of default one
//                    ValueAxis {
//                        min: 20
//                        max: 31
//                        tickCount: 12
//                        labelFormat: "%.0f"
//                        gridVisible: false
//                        color: "#2F3243"
//                    }
                    DateTimeAxis {
                        id: xAxis
                        gridVisible: false
                        color: "#2F3243"
                        format: "hh:mm:ss"
                        tickCount: 5
                    }

                    ValueAxis {
                        id: yAxis1
                        min: 0
                        max: 50
                        tickCount: 5
                        gridVisible: false
                        gridLineColor: "#2F3243"
                        color: "#2F3243"
                        titleText: "Velocity [kph]"
                    }
                    ValueAxis {
                        id: yAxis2
                        min: 0
                        max: 200
                        tickCount: 4
                        gridVisible: false
                        gridLineColor: "#2F3243"
                        color: "#2F3243"
                        titleText: "Altitude [masl]"
                    }

                    AreaSeries {
                        axisX: xAxis
                        axisY: yAxis1
                        color: "#4dfef5"
                        opacity: 0.25
                        //pointLabelsVisible: false
                        borderColor: "#4bddf7"
                        borderWidth: 5.0
                        upperSeries: LineSeries {
                            id: y1
//                            XYPoint { x: 20; y: 4 }
//                            XYPoint { x: 21; y: 5 }
//                            XYPoint { x: 22; y: 6 }
//                            XYPoint { x: 23; y: 8 }
//                            XYPoint { x: 24; y: 7 }
//                            XYPoint { x: 25; y: 6 }
//                            XYPoint { x: 26; y: 4 }
//                            XYPoint { x: 27; y: 6 }
//                            XYPoint { x: 28; y: 4 }
//                            XYPoint { x: 29; y: 5 }
//                            XYPoint { x: 30; y: 6 }
//                            XYPoint { x: 31; y: 7 }
                        }
                    }
                    AreaSeries {
                        axisX: xAxis
                        axisYRight: yAxis2
                        color: "#9b5ed4"
                        opacity: 0.3
                        //pointLabelsVisible: false
                        borderColor: "#bd78f2"
                        borderWidth: 5.0
                        upperSeries: LineSeries {
                            id: y2
//                            XYPoint { x: 20; y: 2 }
//                            XYPoint { x: 21; y: 3 }
//                            XYPoint { x: 22; y: 2 }
//                            XYPoint { x: 23; y: 2 }
//                            XYPoint { x: 24; y: 3 }
//                            XYPoint { x: 25; y: 3 }
//                            XYPoint { x: 26; y: 2 }
//                            XYPoint { x: 27; y: 3 }
//                            XYPoint { x: 28; y: 2 }
//                            XYPoint { x: 29; y: 2 }
//                            XYPoint { x: 30; y: 3 }
//                            XYPoint { x: 31; y: 1 }
                        }
                    }
                    Timer {
                        interval: 100
                        running: true
                        triggeredOnStart: true
                        repeat: true
                        onTriggered: {
                            xAxis.min = new Date(Date.now() - 10000);
                            xAxis.max = new Date(Date.now() + 1000);
                        }
                    }
                    Timer {
                        interval: 100
                        running: true
                        triggeredOnStart: true
                        repeat: true
                        onTriggered: {
                            y1.append(new Date(Date.now()), 25 - 25 * Math.exp(-timeElapsed/10000));
                            y2.append(new Date(Date.now()), 160 -  160 * Math.exp(-timeElapsed/10000));

                        }
                    }                    
                    Timer {
                        id: valueTimer
                        interval: 100
                        running: true
                        triggeredOnStart: true
                        repeat: true
                        onTriggered: {
                            timeElapsed = timeElapsed + 100
                        }

                    }
                }
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
            Rectangle {
                color: "#2F3243"
                width: parent.width*0.5
                height: parent.height*0.3
                anchors{
                    top: parent.top
                    left:parent.left
                    leftMargin: parent.width*0.12
                    topMargin: parent.height*0.07
                }
            }
            Text{
                text: "Request\nAddress"
                wrapMode: text.WordWrap
                width: parent.width*0.5
                font.family: standardFont.name
                font.pixelSize: 0.12*parent.height.toFixed(0)
                color: "#FFFFFF"
                opacity: 0.55
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: parent.height*0.04
                    leftMargin: parent.width*0.08
                }
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
                    Interface.showDialog()

                }

            }

            Text {
                id: portTXT
                font.family: fontFamily
                color: "#DB3D40" //red
                font.pointSize: (parent.height*0.05).toFixed(0)
                anchors {
                    bottom: parent.bottom
                    bottomMargin: 0.1*parent.height
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
                    verticalCenterOffset: parent.height*0.05
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
                  id: groundSpeedRect
                  width: parent.width*0.75
                  height: parent.height*0.75
                  anchors.top: parent.top
                  anchors.left: parent.left
                  anchors.leftMargin: -0.18*width
                  color: "transparent"
                  anchors.topMargin: -parent.height*0.12
                  ChartView{
                      anchors.centerIn: parent
                      anchors.fill: parent
                      antialiasing: true
                      backgroundColor: "transparent"
                      theme: ChartView.ChartThemeBlueIcy
                      margins {
                          left: 0
                          right: 0
                          top: 0
                          bottom: 0
                      }
//                      transform: Rotation{angle: 45}
                      legend.visible: false
                      PieSeries {
                          id: speedSeries
                          PieSlice{
                              id: speedSlice
                              value: 70
                              color: "#292BFF"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          PieSlice{
                              value: 100-speedSlice.value
                              color: "#292BAA"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          holeSize: 0.5
                      }
                      Timer{
                          id: pieTimer
                          interval: 500
                          running: true
                          repeat: true
                          triggeredOnStart: true
                          onTriggered: {
                              speedSlice.value= 70 + Math.random()*(5-2)+2
                              heightSlice.value= 60 + Math.random()*(5-2)+2
                              connectionSlice.value= 30 + Math.random()*(5-2)+2
                              distanceSlice.value= 50 + Math.random()*(5-2)+2
                          }
                      }
                  }
//                  Image {
//                      width: parent.width*0.98
//                      height: parent.height*0.98
//                      anchors.centerIn: parent
//                      source: "qrc:/assetsMenu/SpeedParametr.png"

//                  }
                  Text {
                      id:groundSpeedParamTXT
                      color: "#F5F0F0"
                      font.family: fontFamily
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.02
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: parent.width*0.01
                      }
                      font.pointSize: (parent.height*0.11).toFixed(0)
                      text: groundSpeed.toFixed(0).toString()
                  }
              }
              Rectangle { //Heigth
                  id: heightRect
                  width: parent.width*0.75
                  height: parent.height*0.75
//                  anchors.top: parent.top
                  anchors.right: parent.right
                  anchors.rightMargin: -0.2*width
//                  anchors.topMargin: -0.18*height
                  anchors.bottom: groundSpeedRect.bottom
                  color: "transparent"
//                  Image {
//                      width: parent.width
//                      height: parent.height
//                      anchors.centerIn: parent
//                      source: "qrc:/assetsMenu/Height.png"

//                  }
                  ChartView{
                      anchors.centerIn: parent
                      anchors.fill: parent
                      antialiasing: true
                      backgroundColor: "transparent"
                      theme: ChartView.ChartThemeDark
                      margins {
                          left: 0
                          right: 0
                          top: 0
                          bottom: 0
                      }
                      legend.visible: false
                      PieSeries {
                          id: heightSeries
                          PieSlice{
                              id: heightSlice
                              value: 60
//                              color: "#292BFF"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          PieSlice{
                              value: 100-heightSlice.value
//                              color: "#292BAA"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          holeSize: 0.5
                      }
                  }
                  Text {
                      id:altitudeParamTXT
                      color: "#F5F0F0"
                      font.family: fontFamily
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.02
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: parent.width*0.01
                      }
                      font.pointSize: (parent.height*0.12).toFixed(0)
                      text: altitude.toFixed(0).toString() + "m"}


              }
              Rectangle { //connectionPower
                  id: connectionPowerRect
                  width: parent.width*0.75
                  height: parent.height*0.75
                  anchors.bottom: parent.bottom
                  anchors.left: groundSpeedRect.left
//                  anchors.leftMargin: -0.1*width
                  color: "transparent"
                  anchors.bottomMargin: -0.18*width
//                  Image {
//                      width: parent.width*0.98
//                      height: parent.height*0.98
//                      anchors.centerIn: parent
//                      source: "qrc:/assetsMenu/connectionPower.png"

//                  }
                  ChartView{
                      anchors.centerIn: parent
                      anchors.fill: parent
                      antialiasing: true
                      backgroundColor: "transparent"
                      theme: ChartView.ChartThemeBlueIcy
                      margins {
                          left: 0
                          right: 0
                          top: 0
                          bottom: 0
                      }
                      legend.visible: false
                      PieSeries {
                          id: connectionSeries
                          PieSlice{
                              id: connectionSlice
                              value: 30
//                              color: "#292BFF"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          PieSlice{
                              value: 100-connectionSlice.value
//                              color: "#292BAA"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          holeSize: 0.5
                      }
                  }
                  Text {
                      id: connectionText
                      color: "#F5F0F0"
                      font.family: fontFamily
                      anchors {
                       verticalCenter: parent.verticalCenter
                       verticalCenterOffset: -parent.height*0.01
                       horizontalCenter: parent.horizontalCenter
                       horizontalCenterOffset: -parent.width*0.02
                      }
                      font.pointSize: (parent.height*0.11).toFixed(0)
                      text: batteryPercentage.toFixed(0).toString()+"%"
                  }
              }
              Rectangle { //Distance
                  width: parent.width*0.75
                  height: parent.height*0.75
                  anchors.bottom: connectionPowerRect.bottom
//                  anchors.right: parent.right
//                  anchors.rightMargin: -0.1*width
                  anchors.left: heightRect.left
                  color: "transparent"
//                  Image {
//                      width: parent.width
//                      height: parent.height
//                      anchors.centerIn: parent
//                      source: "qrc:/assetsMenu/Distance.png"

//                  }
                  ChartView{
                      anchors.centerIn: parent
                      anchors.fill: parent
                      antialiasing: true
                      backgroundColor: "transparent"
                      theme: ChartView.ChartThemeBlueCerulean
                      margins {
                          left: 0
                          right: 0
                          top: 0
                          bottom: 0
                      }
                      legend.visible: false
                      PieSeries {
                          id: distanceSeries
                          PieSlice{
                              id: distanceSlice
//                              value: 50
                              value: distanceToNextPoint.toFixed(1).toString() + "km"
//                              color: "#292BFF"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          PieSlice{
                              value: 100-distanceSlice.value
//                              color: "#292BAA"
                              borderWidth: 0
                              borderColor: "transparent"
                          }
                          holeSize: 0.5
                      }
                  }
                  Text {
                      id:distanceText
                      color: "#F5F0F0"
                      font.family: fontFamily
                      anchors {
                       verticalCenter: parent.verticalCenter
//                       verticalCenterOffset: -parent.height*0.01
                       horizontalCenter: parent.horizontalCenter
//                       horizontalCenterOffset: parent.width*0.01
                      }
                      font.pointSize: (parent.height*0.12).toFixed(0)
                      text: distanceToNextPoint.toFixed(1).toString() + "km"
                  }
              }
              Timer{
                  id: textTimer
                  interval: 200
                  running: true
                  repeat: true
                  triggeredOnStart: true
                  onTriggered: {
                      groundSpeedParamTXT.text= (70 + Math.random()*(5-2)+2).toFixed().toString() + "km/h"
                      altitudeParamTXT.text= (60 + Math.random()*(5-2)+2).toFixed(1).toString() + "m"
                      connectionText.text= (30 + Math.random()*(5-2)+2).toFixed(1).toString() + "%"
                      distanceText.text= (50 + Math.random()*(5-2)+2).toFixed(1).toString() + "m"
                  }
              }

        }
    }
    DropArea {
        anchors.fill: parent
        onDropped: {
            anim.running = true;
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
                        value: "*****"                                                            //add your own acces token
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
                    planeAzimut: hdg
                }

            }

            Rectangle { //bottomBar
                id: bottomBar
                color: "#2F3243"
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
                id: plusMinusRectangle
                width: height*2
                height: parent.height*1.3
                color: "transparent"
                opacity: 1
                anchors.left: parent.left
                anchors.leftMargin: -parent.height*0.1
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: parent.height*0.1
                Image {
                    id: plusMinusIcon
                    source: "qrc:/assetsMenu/MinusPlus2off.png"
                    anchors.fill: parent
                    MouseArea {
                        height: parent.height
                        width: parent.width*0.5
                        hoverEnabled: true
                        anchors{
                            left:parent.left
                            verticalCenter: parent.verticalCenter
                        }

                        onClicked: {
                            map.zoomLevel = map.zoomLevel+1
                        }
                        onEntered: {
                            plusMinusIcon.source = "qrc:/assetsMenu/MinusPlusPlunOn.png"
                        }
                        onExited: {
                            plusMinusIcon.source = "qrc:/assetsMenu/MinusPlus2off.png"
                        }
                    }
                    MouseArea {
                        height: parent.height
                        width: parent.width*0.5
                        hoverEnabled: true
                        anchors{
                            right: parent.right
                            verticalCenter: parent.verticalCenter
                        }

                        onClicked: {
                            map.zoomLevel = map.zoomLevel-1
                        }
                        onEntered: {
                            plusMinusIcon.source = "qrc:/assetsMenu/MinusPlusMinusOn.png"
                        }
                        onExited: {
                            plusMinusIcon.source = "qrc:/assetsMenu/MinusPlus2off.png"
                        }
                    }
                }


//                SliderSwitch {
//                    id: followSwitch
//                    anchors.fill: parent
//                    size: parent.width*0.8
//                    onstatecolor: "#009688"
//                    offstatecolor: "#424D5C"
//                    state: "on"
//                }
                }
                Rectangle {
                    id: followRectangle
                width: height*1.1
                height: parent.height*1.3
                color: "transparent"
                opacity: 1
                anchors.left: plusMinusRectangle.horizontalCenter
                anchors.leftMargin: parent.height*0.9
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: parent.height*0.1
                Image {
                    id: followSwitch
                    property bool onOffState: true
                    anchors.fill: parent
                    source: "qrc:/assetsMenu/ButtonFollowOn.png"
                    MouseArea{
                        anchors.fill:parent
                        onClicked: {
                            if(parent.onOffState == true){
                                parent.source = "qrc:/assetsMenu/ButtonFollowOff.png"
                                parent.onOffState = false
                            }
                            else
                            {
                                parent.source = "qrc:/assetsMenu/ButtonFollowOn.png"
                                parent.onOffState = true
                            }
                        }
                    }

                    }
                }
                Rectangle {
                    id: markerRectangle
                width: height*1.1
                height: parent.height*0.83
                color: "#2F3243"
                opacity: 1
                radius: height*0.15
                anchors.left: followRectangle.right
                anchors.leftMargin: -parent.height*0.1
                anchors.verticalCenter: followRectangle.verticalCenter
                anchors.verticalCenterOffset: -parent.height*0.070
                }
                Image {
                    id: dragAndDropIcon
                    source: "qrc:/assetsMenu/markerIcon.png"
                    width: bottomBar.height*0.4
                    antialiasing: true
                    height: bottomBar.height*0.6
                   x: markerRectangle.x + markerRectangle.width*0.28
                   y: markerRectangle.y + markerRectangle.height*0.1
                    Drag.active: markerDragAndDropMouseArea.drag.active
                    Drag.hotSpot.x: 20
                    Drag.hotSpot.y: 20
                    SequentialAnimation {
                        id: anim
                        running: false
                        NumberAnimation { target: dragAndDropIcon; property: "opacity"; to: 0; duration: 250 }
                        PropertyAction { target: dragAndDropIcon; property: "x"; value: markerRectangle.x + markerRectangle.width*0.28 }
                        PropertyAction { target: dragAndDropIcon; property: "y"; value: markerRectangle.y + markerRectangle.height*0.1 }
                        NumberAnimation { target: dragAndDropIcon; property: "opacity"; to: 1; duration: 250 }
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



            Rectangle { //topBar
                color: "#2F3243"
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
                Image{
                    source: "qrc:/assetsMenu/MapProperty.png"
                    height: parent.height*0.7
                    width: height*1.1
                    anchors {
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                        rightMargin: parent.height*0.1
                        verticalCenterOffset: 0
                    }
                }

    }
    }

    }
    RequestDialog{
        id:request

    }

}
