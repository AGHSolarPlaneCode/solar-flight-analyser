import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.3
import "interfaceFunction.js" as Interface
    Window {
        id: root
        flags: Qt.FramelessWindowHint
        height: 250
        property bool isKeyLoaded: false
        width: 650
        property string token: ""
        color: "transparent"
        x: (parent.width*0.5)-(root.width*0.35)
        y: (parent.height*0.5)-(root.height*0.15)

        FontLoader {
            id: standardFont
            source: "qrc:/assetsMenu/agency_fb.ttf"
        }

        Rectangle {
            anchors.fill: parent
            color: "#494F5F"
            radius: 10
            opacity: 0.85
            layer.enabled: true
            clip: true
            Rectangle { //topBar
                anchors{
                    top: parent.top
                    left:parent.left
                    right: parent.right
                }
                color: "#2F3243"
                height: parent.height*0.1
                radius: 10
                opacity: 1
                Rectangle{ //topBar radiusFix
                    anchors{
                        top: parent.verticalCenter
                        left:parent.left
                        right: parent.right
                    }
                    color: "#2F3243"
                    height: parent.height*0.5
                    opacity: 1
                }
                Rectangle {
                    id: exitButton
                    height: parent.height*0.75
                    width: parent.height*0.75
                    radius: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: height*0.5
                    opacity: 1
                    color: "#F2B81E"

                    border{
                        color: "Black"
                        width: width*0.00
                    }
                    Rectangle{
                        width: parent.width*0.6
                        height: parent.height*0.1
                        antialiasing: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenterOffset: height*0.5
                        anchors.horizontalCenterOffset: parent.height*0.03
                        color: "#2C2F3E"
                        rotation: 45
                    }
                    Rectangle{
                        width: parent.width*0.6
                        height: parent.height*0.1
                        anchors.horizontalCenterOffset: parent.height*0.03
                        antialiasing: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenterOffset: height*0.5
                        color: "#2C2F3E"
                        rotation: 135
                    }

                    MouseArea {
                        anchors.fill:parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            pluginDialog.visible = false
                            textInputTXT.text = ""
                            requestBackground.visible = false
                        }
                        onEntered: {
                            exitButton.color = "#e8ac0e"

                        }
                        onExited: {
                           exitButton.color = "#F2B81E"
                        }
                    }
                }
            }

        }
        Image { //TextInput background
            id: textInputRectangle
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
                verticalCenterOffset: parent.height*0.05
            }
            Rectangle {
                color: "transparent"
                opacity: 1
                anchors{
                    right: parent.right
                    rightMargin: parent.height*0.35
                    verticalCenter: parent.verticalCenter
                    verticalCenterOffset: -parent.height*0.05
                }
                width: parent.height*0.6
                height: parent.height*0.5
            }

            height: parent.height*0.35
            width: parent.width*0.85
            opacity: 0.9
            antialiasing: true
            source: "qrc:/assetsMenu/addressBoxMAP.svg"




            TextEdit {
                id: textInputTXT
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -parent.width*0.05
                anchors.verticalCenterOffset: -parent.height*0.05
                selectByMouse: true
                wrapMode: Text.Wrap
                height: parent.height*0.8
                width: parent.width*0.8
                onLengthChanged: {
                    if(length >= 120){
                        text = text.slice(0, 119)
                        cursorPosition = 119
                    }
                }

                font.pointSize: parent.height*0.2
                font.family: standardFont.name
                color: "#3C4151"
                horizontalAlignment : TextEdit.AlignLeft
                verticalAlignment: TextEdit.AlignVCenter
                property string vplaceholderText: "MAPBOX access token..."

                  Text {
                      text: (textInputTXT.vplaceholderText).toUpperCase()
                      color: "#3C4151"
                      font.family: standardFont.name
                      font.pixelSize: parent.font.pixelSize*1
                      horizontalAlignment: Text.AlignLeft
                      verticalAlignment: Text.verticalCenter
                      anchors.verticalCenter: parent.verticalCenter
                      //anchors.verticalCenterOffset: -parent.height*0.2
                      //anchors.horizontalCenterOffset: -parent.width*0.5
                      visible: !textInputTXT.text && !textInputTXT.activeFocus // <----------- ;-)
                  }
              }
            }

//        Rectangle{
//            id: messageBackground
//            visible: false
//            width: textInputRectangle.width
//            color: "transparent"
//            height: textInputRectangle.height*0.4
//            anchors {
//                horizontalCenter: textInputRectangle.horizontalCenter
//                top: textInputRectangle.bottom
//                topMargin: -textInputRectangle.height*0.20
//            }
//            Text {
//                id: errorMessageTXT
//                text: errorMessage
//                color: "white"
//                anchors.left: errorMessageIcon.right
//                anchors.leftMargin: parent.height*0.2
//                anchors.verticalCenter: parent.verticalCenter
//                font.family: standardFont.name
//                font.pixelSize: parent.height*0.8

//            }
//            Image {
//                id: errorMessageIcon
//                source: "qrc:/assetsMenu/iIcon.svg"
//                height: parent.height*0.8
//                width: height
//                smooth: true
//                anchors{
//                    verticalCenter: parent.verticalCenter
//                    left: parent.left
//                    leftMargin: parent.height*0.5
//                }
//            }
//        }

        Rectangle{ //verifyButton
            id:accpetButton
            color: "#3C4151"
            width: parent.width*0.16
            height: parent.height*0.17
            radius: height*0.5
            anchors {
                bottom: parent.bottom
                bottomMargin: parent.height*0.05
                horizontalCenter: parent.horizontalCenter
            }
            border{
                color: "#F2B81E"
                width: parent.height*0.005
            }

            Text{
                text: "ADD TOKEN"
                anchors.centerIn: parent
                font.family: standardFont.name
                font.pixelSize: parent.height*0.5
                color: "#F2B81E"
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    token =textInputTXT.text
                    console.log("ACCES token lenght:")
                    console.log(token.length)
                    if(isKeyLoaded){
                        errorModel.insert(0, {"type": 2, "msg" : "You have one chance to change API token"})
                    }
                    else {

                    if((!(token == "")) && token.length>=70){
                        isKeyLoaded = true
                        map.plugin = Qt.createQmlObject('import QtLocation 5.6; Plugin{
                                id: mapBoxPlugin
                                name: "mapbox"
                                PluginParameter{
                                    id: mapBoxPlugintoken
                                    name: "mapbox.access_token"
                                    value: root.token                    }
                                PluginParameter{
                                    name: "mapbox.mapping.map_id"
                                    value: "mapbox.dark"
                                }
                            }', map)
                        if(map.error !== Map.NoError){
                        errorModel.insert(0, {"type": 2, "msg" : "MapBox access token loaded succesfuly"})
                    }
                        else {
                            errorModel.insert(0, {"type": 1, "msg" : "Error on access token loading occured"})
                        }
                        }
                    else {
                        errorModel.insert(0, {"type": 2, "msg" : "MapBox access token is incorrect"})
                    }
                    }
                    pluginDialog.visible = false
                    textInputTXT.text = ""
                    exitButton.forceActiveFocus()
                    requestBackground.visible = false

                }
                onEntered: {
                    accpetButton.color = "#424D5C"
                }
                onExited: {
                    accpetButton.color = "#3C4151"
                }
            }
        }
//        Rectangle { //OKButton
//            id: cancelButton
//            color: "#3C4151"
//            radius: height*0.5
//            width: parent.width*0.16
//            height: parent.height*0.17
//            anchors {
//                verticalCenter: accpetButton.verticalCenter
//                left: accpetButton.right
//                leftMargin: parent.width*0.05
//            }
//            border{
//                color: "#F2B81E"
//                width: parent.height*0.005
//            }
//            Text{
//                text: "OK"
//                anchors.centerIn: parent
//                font.family: standardFont.name
//                font.pixelSize: parent.height*0.5
//                color: "#F2B81E"
//                font.bold: true
//            }
//            MouseArea {
//                anchors.fill: parent
//                cursorShape: Qt.PointingHandCursor
//                hoverEnabled: true
//                onClicked: {
//                    Interface.closeDialog()
//                    if(!success){
//                    textInputTXT.text = ""
//                    textInputRectangle.forceActiveFocus()
//                    }

//                }
//                onEntered: {
//                    cancelButton.color = "#424D5C"
//                }
//                onExited: {
//                    cancelButton.color = "#3C4151"
//                }
//            }
//        }
        Text {
            text: "MAPBOX API ACCESS TOKEN"
            anchors {
                bottom: textInputRectangle.top
                bottomMargin: parent.height*0.05
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: parent.height*0.08
            font.bold: true
            font.family: standardFont.name
            color: "#F2B81E"
            opacity: 95


        }
//        SequentialAnimation{
//            id: okIndicatorOnAnim
//            running: false
//            PropertyAnimation {
//                target: wrongIndicator
//                property: "anchors.verticalCenterOffset"
//                from: -wrongIndicator.parent.height*0.05
//                to: -wrongIndicator.parent.height*0.1
//                duration: 100
//            }
//            PropertyAnimation {
//                target: wrongIndicator
//                property: "anchors.verticalCenterOffset"
//                to: -wrongIndicator.parent.height*0.05
//                from: -wrongIndicator.parent.height*0.1
//                duration: 100

//            }
//            PropertyAnimation{
//                target: wrongIndicator
//                property: "visible"
//                from: true
//                to: false
//                duration: 0
//            }
//            PropertyAnimation{
//                target: okIndicator
//                property: "visible"
//                from: false
//                to: true
//                duration: 0
//            }
//        }
//        SequentialAnimation{
//            id: okIndicatorOFFAnim
//            running: false
//            PropertyAnimation {
//                target: okIndicator
//                property: "anchors.verticalCenterOffset"
//                from: -wrongIndicator.parent.height*0.05
//                to: -wrongIndicator.parent.height*0.1
//                duration: 100
//            }
//            PropertyAnimation {
//                target: okIndicator
//                property: "anchors.verticalCenterOffset"
//                to: -wrongIndicator.parent.height*0.05
//                from: -wrongIndicator.parent.height*0.1
//                duration: 100

//            }
//            PropertyAnimation{
//                target: okIndicator
//                property: "visible"
//                from: true
//                to: false
//                duration: 0
//            }
//            PropertyAnimation{
//                target: wrongIndicator
//                property: "visible"
//                from: false
//                to: true
//                duration: 0
//            }
//        }
    }
