import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.3
import "interfaceFunction.js" as Interface
    Window {
        id: root
        flags: Qt.FramelessWindowHint
        height: 250
        width: 650
        color: "transparent"
        property string textS: ""
        property var textToVar: []
        property bool success: false
        property string errorMessage: "No error" //connect to errorManager
        x: (parent.width*0.5)-(root.width*0.35)
        y: (parent.height*0.5)-(root.height*0.15)
        onVisibleChanged: {
            okIndicator.visible = false
            wrongIndicator.visible = true
        }
        Timer {
            id: errorTimer
            repeat: false
            interval: 5*1000
            onTriggered: {
                messageBackground.visible = false
            }
        }

        Connections{
            target: errorManager
            onSendMessageToDialogWindow:{  // receiving messages - checked
                console.log(message, type);
                errorMessage = message
                errorMessageTXT.text = errorMessage
                messageBackground.visible = true
                switch(type){
                case 1:
                    errorMessageIcon.source = "qrc:/assetsMenu/xicon.svg"
                    errorMessageTXT.color = "#FF5050"
                    if(okIndicator.visible === true){
                    okIndicatorOFFAnim.start()
                    }
                    errorTimer.start()
                    break
                case 2:
                    errorMessageIcon.source = "qrc:/assetsMenu/iIcon.svg"
                    errorMessageTXT.color = "#3F75C8"
                    errorTimer.start()
                    break
                case 3:
                    errorMessageIcon.source = "qrc:/assetsMenu/vicon.svg"
                    success = true
                    errorMessageTXT.color = "#24A635"
                    if(okIndicator.visible === false){
                    okIndicatorOnAnim.start()
                         }
                        errorTimer.start()
                    break

                }


            }
        }

        signal setAdress(var adressS,var portS)

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
                            Interface.closeDialog();
                            textInputTXT.text = ""
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

            height: parent.height*0.22
            width: parent.width*0.5
            opacity: 0.9
            antialiasing: true
            source: "qrc:/assetsMenu/addressBox.svg"
            Rectangle {
                id: okIndicator
                visible: false
                color: "transparent"
                width: parent.height*0.7*0.8
                height: parent.height*0.6*0.8
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -parent.height*0.05
                anchors.right: parent.right
                anchors.rightMargin: parent.height*0.2
                Image {
                    height: parent.height*0.6
                    width: height
                    smooth: true
                    antialiasing: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/assetsMenu/viconP.svg"
                }
            }
            Rectangle {
                id: wrongIndicator
                color: "transparent"
                visible: true
                width: parent.height*0.7
                height: parent.height*0.6
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -parent.height*0.05
                anchors.right: parent.right
                anchors.rightMargin: parent.height*0.15
                Image {
                    height: parent.height*0.6
                    width: height
                    smooth: true
                    antialiasing: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/assetsMenu/xiconP.svg"
                }
            }



            TextInput {
                id: textInputTXT
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                selectByMouse: true
                height: parent.height*0.36
                width: parent.width*0.8
                font.pointSize: parent.height*0.26
                font.family: standardFont.name
                color: "#3C4151"
                maximumLength: 32
                //validator: RegExpValidator {regExp: /((((localhost)|(([2]([0-4][0-9]|[5][0-5])|[0-1]?[0-9]?[0-9])[.]){3}(([2]([0-4][0-9]|[5][0-5])|[0-1]?[0-9]?[0-9])))(:[0-9]{1,5})?[;]?)+)/ }
                //validator: RegExpValidator {regExp: /^https?:\/\/(localhost:([0-9]+\.)+[a-zA-Z0-9]{1,6})?$/}
                property string placeholderText: "Enter address:port ..."

                  Text {
                      text: (textInputTXT.placeholderText).toUpperCase()
                      color: "#3C4151"
                      font.family: standardFont.name
                      font.pixelSize: parent.font.pixelSize* 0.7
                      anchors.verticalCenter: parent.verticalCenter
                      anchors.verticalCenterOffset: -parent.height*0.2
                      anchors.horizontalCenterOffset: -parent.width*0.5
                      visible: !textInputTXT.text && !textInputTXT.activeFocus // <----------- ;-)
                  }
              }
            }

        Rectangle{
            id: messageBackground
            visible: false
            width: textInputRectangle.width
            color: "transparent"
            height: textInputRectangle.height*0.4
            anchors {
                horizontalCenter: textInputRectangle.horizontalCenter
                top: textInputRectangle.bottom
                topMargin: -textInputRectangle.height*0.20
            }
            Text {
                id: errorMessageTXT
                text: errorMessage
                color: "white"
                anchors.left: errorMessageIcon.right
                anchors.leftMargin: parent.height*0.2
                anchors.verticalCenter: parent.verticalCenter
                font.family: standardFont.name
                font.pixelSize: parent.height*0.8

            }
            Image {
                id: errorMessageIcon
                source: "qrc:/assetsMenu/iIcon.svg"
                height: parent.height*0.8
                width: height
                smooth: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: parent.height*0.5
                }
            }
        }

        Rectangle{ //verifyButton
            id:accpetButton
            color: "#3C4151"
            width: parent.width*0.16
            height: parent.height*0.17
            radius: height*0.5
            anchors {
                bottom: parent.bottom
                bottomMargin: parent.height*0.05
                left: parent.left
                leftMargin: parent.width*0.05
            }
            border{
                color: "#F2B81E"
                width: parent.height*0.005
            }

            Text{
                text: "VERIFY"
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
                adapter.currentEndpoint = textInputTXT.text
                }
                onEntered: {
                    accpetButton.color = "#424D5C"
                }
                onExited: {
                    accpetButton.color = "#3C4151"
                }
            }
        }
        Rectangle { //OKButton
            id: cancelButton
            color: "#3C4151"
            radius: height*0.5
            width: parent.width*0.16
            height: parent.height*0.17
            anchors {
                verticalCenter: accpetButton.verticalCenter
                left: accpetButton.right
                leftMargin: parent.width*0.05
            }
            border{
                color: "#F2B81E"
                width: parent.height*0.005
            }
            Text{
                text: "OK"
                anchors.centerIn: parent
                font.family: standardFont.name
                font.pixelSize: parent.height*0.5
                color: "#F2B81E"
                font.bold: true
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onClicked: {
                    Interface.closeDialog()
                    if(!success){
                    textInputTXT.text = ""
                    textInputRectangle.forceActiveFocus()
                    }

                }
                onEntered: {
                    cancelButton.color = "#424D5C"
                }
                onExited: {
                    cancelButton.color = "#3C4151"
                }
            }
        }
        Text {
            text: "PRESS REQUEST ADDRESS"
            anchors {
                bottom: textInputRectangle.top
                bottomMargin: parent.height*0.1
                horizontalCenter: parent.horizontalCenter
            }
            font.pointSize: parent.height*0.08
            font.bold: true
            font.family: standardFont.name
            color: "#F2B81E"
            opacity: 95


        }
        SequentialAnimation{
            id: okIndicatorOnAnim
            running: false
            PropertyAnimation {
                target: wrongIndicator
                property: "anchors.verticalCenterOffset"
                from: -wrongIndicator.parent.height*0.05
                to: -wrongIndicator.parent.height*0.1
                duration: 100
            }
            PropertyAnimation {
                target: wrongIndicator
                property: "anchors.verticalCenterOffset"
                to: -wrongIndicator.parent.height*0.05
                from: -wrongIndicator.parent.height*0.1
                duration: 100

            }
            PropertyAnimation{
                target: wrongIndicator
                property: "visible"
                from: true
                to: false
                duration: 0
            }
            PropertyAnimation{
                target: okIndicator
                property: "visible"
                from: false
                to: true
                duration: 0
            }
        }
        SequentialAnimation{
            id: okIndicatorOFFAnim
            running: false
            PropertyAnimation {
                target: okIndicator
                property: "anchors.verticalCenterOffset"
                from: -wrongIndicator.parent.height*0.05
                to: -wrongIndicator.parent.height*0.1
                duration: 100
            }
            PropertyAnimation {
                target: okIndicator
                property: "anchors.verticalCenterOffset"
                to: -wrongIndicator.parent.height*0.05
                from: -wrongIndicator.parent.height*0.1
                duration: 100

            }
            PropertyAnimation{
                target: okIndicator
                property: "visible"
                from: true
                to: false
                duration: 0
            }
            PropertyAnimation{
                target: wrongIndicator
                property: "visible"
                from: false
                to: true
                duration: 0
            }
        }
    }
