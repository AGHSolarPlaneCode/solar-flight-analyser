import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.3
    Window {
        id: root
        flags: Qt.FramelessWindowHint
        height: 250
        width: 800
        color: "transparent"
        property string textS: ""
        property var textToVar: []

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
                Image {
                    source: "qrc:/assetsMenu/closeIcon.png"
                    height: parent.height*0.6
                    width: parent.height*0.6
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: height*0.5
                    opacity: 1
                    MouseArea {
                        anchors.fill:parent
                        onClicked: {
                            root.visible=false;
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
                verticalCenterOffset: parent.height*0.08
            }
            height: parent.height*0.22
            width: parent.width*0.5
            source: "qrc:/assetsMenu/addressBox.png"
            TextInput {
                id: textInputTXT
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height*0.36
                width: parent.width*0.8
                font.pointSize: parent.height*0.36
                font.family: standardFont.name
                validator: RegExpValidator {regExp: /((((localhost)|(([2]([0-4][0-9]|[5][0-5])|[0-1]?[0-9]?[0-9])[.]){3}(([2]([0-4][0-9]|[5][0-5])|[0-1]?[0-9]?[0-9])))(:[0-9]{1,5})?[;]?)+)/ }


            }
        }
        Image{ //accpetButton
            id:accpetButton
            source: "qrc:/assetsMenu/acceptButton.png"
            width: parent.width*0.16
            height: parent.height*0.17
            anchors {
                bottom: parent.bottom
                bottomMargin: parent.height*0.05
                left: parent.left
                leftMargin: parent.width*0.05
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    textS = textInputTXT.text
                    textToVar = textS.split(':')
                    setAdress(textToVar[0],textToVar[1])
                    root.visible=false;
                    textInputTXT.text = ""
                }
            }
        }
        Image { //cancelButton
            id: cancelButton
            source: "qrc:/assetsMenu/cancelButton.png"
            width: parent.width*0.16
            height: parent.height*0.17
            anchors {
                verticalCenter: accpetButton.verticalCenter
                left: accpetButton.right
                leftMargin: parent.width*0.05
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.visible = false
                    textInputTXT.text = ""
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
            color: "#3C4151"

        }
    }
