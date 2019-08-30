import QtQuick 2.0
import QtQuick.Layouts 1.13
Item {
    id: root

    height: parent.height
    width: parent.width
    anchors.centerIn: parent
    property string mainTemerature: (weather.temp).toString()//weatherAPIAdapter.temp
    property int windValue: weather.windSpeed  //weatherAPIAdapter.windSpeed
    property int rainValue: weather.hum //weatherAPIAdapter -- getter
    property int sunLevel: 50 //get from backend -- don't know which class field
    property string icon: "01d"//weather.iconID
    property color windOff: "#5E5A5A"
    property string sunrise: "-"
    property string sunset: "-"
    property color windOn: "#FFFFFF"
    property color rainOff: "#CDE7EF"
    property color rainOn: "#8FD2E7"
    property int maxTemp: 0
    property int minTemp: 0
    property int pressure: 1024
    antialiasing: true
    FontLoader{
        id: standardFont
        source: "qrc:/assetsMenu/agency_fb.ttf"
    }
    onWindValueChanged: {
        var maxwind = 100
        var minwind = 0
        if(windValue < (maxwind/5)-10){
            windDot1.color = windOff
            windDot2.color = windOff
            windDot3.color = windOff
            windDot4.color = windOff
            windDot5.color = windOff
        }
        else if(windValue <((maxwind/5))){
            windDot1.color = windOn
            windDot2.color = windOff
            windDot3.color = windOff
            windDot4.color = windOff
            windDot5.color = windOff
        }
        else if(windValue <(2*(maxwind/5))){
            windDot1.color = windOn
            windDot2.color = windOn
            windDot3.color = windOff
            windDot4.color = windOff
            windDot5.color = windOff
        }
        else if(windValue <(3*(maxwind/5))){
            windDot1.color = windOn
            windDot2.color = windOn
            windDot3.color = windOn
            windDot4.color = windOff
            windDot5.color = windOff
        }
        else if(windValue <(4*(maxwind/5))){
            windDot1.color = windOn
            windDot2.color = windOn
            windDot3.color = windOn
            windDot4.color = windOn
            windDot5.color = windOff
        }
        else {
            windDot1.color = windOn
            windDot2.color = windOn
            windDot3.color = windOn
            windDot4.color = windOn
            windDot5.color = windOn
        }
    }
    onRainValueChanged: {
        var maxrain = 100
        var minrain = 0
        if(rainValue < (maxrain/5)-10){
            rainDot1.color = rainOff
            rainDot2.color = rainOff
            rainDot3.color = rainOff
            rainDot4.color = rainOff
            rainDot5.color = rainOff
        }
        else if(rainValue <((maxrain/5))){
            rainDot1.color = rainOn
            rainDot2.color = rainOff
            rainDot3.color = rainOff
            rainDot4.color = rainOff
            rainDot5.color = rainOff
        }
        else if(rainValue <(2*(maxrain/5))){
            rainDot1.color = rainOn
            rainDot2.color = rainOn
            rainDot3.color = rainOff
            rainDot4.color = rainOff
            rainDot5.color = rainOff
        }
        else if(rainValue <(3*(maxrain/5))){
            rainDot1.color = rainOn
            rainDot2.color = rainOn
            rainDot3.color = rainOn
            rainDot4.color = rainOff
            rainDot5.color = rainOff
        }
        else if(rainValue <(4*(maxrain/5))){
            rainDot1.color = rainOn
            rainDot2.color = rainOn
            rainDot3.color = rainOn
            rainDot4.color = rainOn
            rainDot5.color = rainOff
        }
        else {
            rainDot1.color = rainOn
            rainDot2.color = rainOn
            rainDot3.color = rainOn
            rainDot4.color = rainOn
            rainDot5.color = rainOn
        }
    }
//    MouseArea { //just for test before established backed connection
//        anchors.fill:parent
//        onClicked: {
//            windValue = 43
//            rainValue = 54
//        }
//    }
    Rectangle {
        id: moreBarBottom
        anchors {
            bottom: root.bottom
            bottomMargin: height*0.4
            left: root.left
//            leftMargin: root.width*0.0
        }
        width: parent.width*0.38
        height: parent.height*0.45
        radius: height*0.1
        color: "#31364A"
        opacity: 0.5


    }
    ColumnLayout {
        anchors {
            horizontalCenter: moreBarBottom.horizontalCenter
            verticalCenter: moreBarBottom.verticalCenter
            verticalCenterOffset: -moreBarBottom.height*0.01
        }
        height: moreBarBottom.height*0.95
        width: moreBarBottom.width
        spacing: moreBarBottom.height*0.05

        Text{
            id:sunriseTXT
            Layout.leftMargin: parent.width*0.1
            //Layout.topMargin: moreBarBottom.height*0.05
            //Layout.alignment: Qt.AlignHCenter
            text: "SUNRISE:  " + sunrise
            font.family: standardFont.name
            visible: true
            color: "#FFFFFF"
            opacity: 1
            Layout.fillHeight: true
            font.pixelSize: moreBarBottom.height*0.2*0.9
        }
        Text{
            id:sunsetTXT
            Layout.leftMargin: parent.width*0.1
            //Layout.alignment: Qt.AlignHCenter
            text: "SUNSET:  " + sunset
            font.family: standardFont.name
            visible: true
            color: "#FFFFFF"
            opacity: 1
            Layout.fillHeight: true
            font.pixelSize: moreBarBottom.height*0.2*0.9
        }


    Text{
        id:tempMaxTXT
        Layout.leftMargin: parent.width*0.1
        //Layout.alignment: Qt.AlignHCenter
        text: "MAX TEMP:  " + maxTemp.toString() + "\u00B0" + "C"
        font.family: standardFont.name
        visible: true
        color: "#FFFFFF"
        opacity: 1
        font.pixelSize: moreBarBottom.height*0.2*0.9
        Layout.fillHeight: true
//        anchors {
//            left: moreBarBottom.left
//            leftMargin: moreBarBottom.width*0.05
//            top: moreBarBottom.top
//            topMargin: height*0.2
//        }
    }
    Text{
        id:tempMinTXT
        Layout.leftMargin: parent.width*0.1
        //Layout.alignment: Qt.AlignHCenter
        text: "MIN TEMP:  " + minTemp.toString() + "\u00B0" + "C"
        font.family: standardFont.name
        visible: true
        color: "#FFFFFF"
        opacity: 1
        Layout.fillHeight: true
        font.pixelSize: moreBarBottom.height*0.2*0.9
//        anchors {
//            top: tempMaxTXT
//            topMargin: height*0.1
//            horizontalCenter:
//        }
    }
    Text{
        id: pressureTXT
        Layout.leftMargin: parent.width*0.1
        Layout.bottomMargin: moreBarBottom.height*0.05
        //Layout.alignment: Qt.AlignHCenter
        text: "PRESSURE:  " + pressure.toString() + " hPa"
        font.family: standardFont.name
        visible: true
        Layout.fillHeight: true
        color: "#FFFFFF"
        opacity: 1
        font.pixelSize: moreBarBottom.height*0.2*0.9
//        anchors {
//            left: moreBarBottom.left
//            leftMargin: moreBarBottom.width*0.05
//            bottom: moreBarBottom.bottom
//            bottomMargin: moreBarBottom.height*0.05
//        }
    }
    }

//    Rectangle {
//        id: moreBar
//        height: parent.height*0.15
//        width: height*3.5
//        radius: height
//        color: "#2F3243"
//        border {
//            color: "#F2B81E"
//            width: radius*0.02
//        }
//        anchors{
//            top: parent.top
//            topMargin: parent.height*0.1
//            horizontalCenter: parent.horizontalCenter
//            horizontalCenterOffset: -parent.width*0.2
//        }
//        MouseArea{
//            anchors.fill:parent
//            onClicked: {
//                if(moreBarBottom.visible ==true){
//                    moreBarBottom.visible = false
//                    pressureTXT.visible = false
//                    tempMaxTXT.visible = false
//                    tempMinTXT.visible = false
//                    moreBarImage.rotation = 0


//                }
//                else {
//                    moreBarBottom.visible = true
//                    pressureTXT.visible = true
//                    tempMaxTXT.visible = true
//                    tempMinTXT.visible = true
//                    moreBarImage.rotation = 180
//                }
//            }
//        }

//        Text {
//            text: ("More").toUpperCase()
//            color: "#F2B81E"
//            font.family: standardFont.name
//            font.pixelSize: parent.height*0.6
//            anchors{
//                verticalCenter: parent.verticalCenter
//                horizontalCenter: parent.horizontalCenter
//                horizontalCenterOffset: -parent.width*0.02
//            }
//        }
//        Image{
//            id:moreBarImage
//            source: "qrc:/assetsMenu/moreicon.png"
//            anchors{
//                right: parent.right
//                rightMargin: parent.width*0.1
//                verticalCenter: parent.verticalCenter
//            }
//        }
//    }


    Image {
        id: weatherMainIcon
        height: parent.height*0.41
        width: parent.width*0.32
        smooth: true
        antialiasing: true
        source: ("qrc:/assetsMenu/weatherIcons/" + icon + ".png")
        anchors {
            top: parent.top
            topMargin: parent.height*0.05
            right: parent.right
            rightMargin: parent.width*0.2
        }
       }
    Rectangle {
        height: parent.height*0.013
        width: weatherMainIcon.width*0.65
        color: "white"
        anchors {
            top: weatherMainIcon.bottom
            horizontalCenter: weatherMainIcon.horizontalCenter
            topMargin: parent.height*0.04
        }
    }


    Text {
        id: weatherMainTemerature
        font.pixelSize: parent.height*0.25
        color: "white"
        font.family: standardFont.name
        anchors{
            right: moreBarBottom.right
            bottom: moreBarBottom.top
            bottomMargin: moreBarBottom.height*0.05
        }
        text: mainTemerature + "\u00B0" + "C"
    }
    Text{
        id: weatherCityName
        color: "white"
        text: "Cracow"
        font.family: standardFont.name
        font.pixelSize: parent.height*0.17
        font.bold: true
        anchors{
            top: weatherMainIcon.bottom
            horizontalCenter: weatherMainIcon.horizontalCenter
            topMargin: parent.height*0.05
        }
    }
    Text {
        font.pixelSize: parent.height*0.08
        color: "white"
        text: new Date().toLocaleDateString(Qt.locale("en_GB"), "dddd")
        font.family: standardFont.name
        anchors{
            horizontalCenter: weatherCityName.horizontalCenter
            top: weatherCityName.bottom
            topMargin: parent.height*0.01
        }
    }



    Rectangle {
        id: bottomRectangle
        color: "transparent"
        width: parent.width*0.8
        height: parent.height*0.14
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            horizontalCenterOffset: -parent.width*0.1
            bottomMargin: parent.height*0.005
        }
//        Text {
//            text: "HUMIDITY"
//            font.family: standardFont.name
//            visible: false
//            font.pixelSize: 0.7*bottomRectangle.height.toFixed(0)
//            color: "#F5F0F0"
//            anchors{
//                bottom: bottomRectangle.top
//                horizontalCenter: rainDot3.horizontalCenter
//            }
//        }
//        Text {
//            text: "WIND SPEED"
//            visible: false
//            font.family: standardFont.name
//            font.pixelSize: 0.7*bottomRectangle.height.toFixed(0)
//            color: "#F5F0F0"
//            anchors{
//                bottom: bottomRectangle.top
//                horizontalCenter: windDot3.horizontalCenter
//            }
//        }
        Image {
            id: windIcon
            smooth: true
            antialiasing: true
            height: parent.height*0.7
            width: parent.height*1
            anchors.left: parent.left
            anchors.leftMargin: parent.height*0
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/assetsMenu/wind.svg"

        }
        Rectangle {
            id: windDot1
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: windOff
            anchors {
                left: windIcon.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot2
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: windOff
            anchors {
                left: windDot1.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot3
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: windOff
            anchors {
                left: windDot2.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot4
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: windOff
            anchors {
                left: windDot3.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: windDot5
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: windOff
            anchors {
                left: windDot4.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Text {
            id: windTXT
            anchors{
                left: windDot5.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
            color: "#FFFFFF"
            font.pixelSize: parent.height*0.4
            font.family: standardFont.name
            text: windValue.toFixed(0) + "km/h"
        }


        //-----------------------------
        Image {
            id: rainIcon
            smooth: true
            antialiasing: true
            height: parent.height*0.5
            width: parent.height*0.35
            anchors.left: windTXT.right
            anchors.leftMargin: parent.height*0.5
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/assetsMenu/rainIcon.svg"
        }
        Rectangle {
            id: rainDot1
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: rainOff
            anchors {
                left: rainIcon.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot2
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: rainOff
            anchors {
                left: rainDot1.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot3
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: rainOff
            anchors {
                left: rainDot2.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot4
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: rainOff
            anchors {
                left: rainDot3.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: rainDot5
            height: parent.height*0.3
            width: parent.height*0.3
            radius: parent.height*0.3
            color: rainOff
            anchors {
                left: rainDot4.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
        }
        Text {
            id: rainTXT
            anchors{
                left: rainDot5.right
                leftMargin: parent.height*0.15
                verticalCenter: parent.verticalCenter
            }
            color: "#FFFFFF"
            font.pixelSize: parent.height*0.4
            font.family: standardFont.name
            text: rainValue.toFixed(0) + "%"
        }

        Text{
            id: sunText
            font.pixelSize: parent.height*0.4
            text: sunLevel.toString();
            color: "white"
            font.family: standardFont.name
            anchors.left: sunIcon.right
            anchors.leftMargin: parent.height*0.1
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -parent.height*0.06
        }
        Image {
            id: sunIcon
            height: parent.height*0.7
            width: parent.height*0.7
            source: "qrc:/assetsMenu/sunLevel.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: rainTXT.right
            anchors.leftMargin: parent.height*0.4
        }


    }
}
