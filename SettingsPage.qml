import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    Rectangle {
        id: root
         anchors.fill: parent
         color: "#292B38"
         property color childrenColor: "transparent"
         property double fontSize: height*0.05
         border {
             width: 1
             color: "#333644"
                }
         FontLoader {
             id: standardFont
             source: "qrc:/assetsMenu/agency_fb.ttf"
         }
         Rectangle {
            id: background
            anchors.centerIn: parent
            property color childrenColor: "transparent"
            width: parent.width*0.8
            height: parent.height*0.9
            color: parent.childrenColor
            Rectangle {
                id: screenBox
                anchors {
                    left:parent.left
                    top:parent.top
                    topMargin:height*0.1
                }
                height: parent.height*0.30
                width: parent.width*0.45
                color:parent.childrenColor

               Text {
                   id: screenTXT
                   text: "Screen"
                   font.pixelSize: root.fontSize
                   color: "#F2B81E"
                   font.family: standardFont.name
                   anchors {
                       left: parent.left
                       top: parent.top
                       topMargin: height*0.3
                       leftMargin: parent.width*0.05
                   }
               }
               Rectangle {
                   id: resolutionBox
                   width: parent.width*0.7
                   height: parent.height*0.25
                   color: "transparent"
                   anchors {
                       top: screenTXT.bottom
                       topMargin: height*0.1
                       left: parent.left
                       leftMargin: parent.width*0.1
                   }
                   Text {
                       id: resolutionTXT
                       font.pixelSize: parent.height*0.8
                       font.family: standardFont.name
                       color: "#B6B7BD"
                       text: "Resolution"
                       anchors {
                           verticalCenter: parent.verticalCenter
                           left: parent.left
                           leftMargin: parent.width*0.02
                       }
                   }
                   ComboBox {
                       width: parent.width*0.4
                       model: [ "1920x1080", "1600x900", "720x480" ]
                       anchors {
                           verticalCenter: parent.verticalCenter
                           right: parent.right
                           rightMargin: parent.width*0.02
                       }
                   }

               }
               Rectangle {
                   id: fullScreenBox
                   width: parent.width*0.7
                   height: parent.height*0.25
                   color: "transparent"
                   anchors {
                       bottom: parent.bottom
                       left: parent.left
                       leftMargin: parent.width*0.1
                       bottomMargin: height*0.4
                   }
                   Text {
                       id: fullScreenTXT
                       font.pixelSize: parent.height*0.8
                       font.family: standardFont.name
                       color: "#B6B7BD"
                       text: "Full screen"
                       anchors {
                           verticalCenter: parent.verticalCenter
                           left: parent.left
                           leftMargin: parent.width*0.02
                       }
                   }
                   CheckBox {
                       checked: false
                       width: parent.height*0.8
                       height: width
                       anchors {
                           verticalCenter: parent.verticalCenter
                           right: parent.right

                       }
                   }

               }
            }
            Rectangle {
                id: appearanceBox
                color: parent.childrenColor
                height: screenBox.height
                width: screenBox.width
                anchors {
                    left: parent.left
                    top: screenBox.bottom
                    topMargin: height*0.02
                }
                Text {
                    id: appearanceTXT
                    text: "Appearance"
                    font.pixelSize: root.fontSize
                    color: "#F2B81E"
                    font.family: standardFont.name
                    anchors {
                        left: parent.left
                        top: parent.top
                        topMargin: height*0.3
                        leftMargin: parent.width*0.05
                    }
                }               Rectangle {
                    id: themesBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        top: appearanceTXT.bottom
                        topMargin: height*0.1
                        left: parent.left
                        leftMargin: parent.width*0.1
                    }
                    Text {
                        id: themesTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "Themes"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.4
                        model: [ "Dark", "Bright" ]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
                Rectangle {
                    id: waypointsBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        leftMargin: parent.width*0.1
                        bottomMargin: height*0.4
                    }
                    Text {
                        id: waypointsTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "Waypoints"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.18
                        model: [ "Icon1", "Icon2" ]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
            }
            Rectangle {
                id: connectionSettingsBox
                color: parent.childrenColor
                height: appearanceBox.height
                width: appearanceBox.width
                anchors {
                    left: parent.left
                    top: appearanceBox.bottom
                    topMargin: height*0.02
                }
                Text {
                    id: connectionSettingsTXT
                    text: "Connection Settings"
                    font.pixelSize: root.fontSize
                    color: "#F2B81E"
                    font.family: standardFont.name
                    anchors {
                        left: parent.left
                        top: parent.top
                        topMargin: height*0.3
                        leftMargin: parent.width*0.05
                    }
                }               Rectangle {
                    id: portBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        top: connectionSettingsTXT.bottom
                        topMargin: height*0.1
                        left: parent.left
                        leftMargin: parent.width*0.1
                    }
                    Text {
                        id: portTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "Port"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.18
                        model: ["COM1", "COM2","COM3", "COM4","COM5", "COM6","COM7", "COM8", "COM9", "COM10"]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
                Rectangle {
                    id: baudRateBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        leftMargin: parent.width*0.1
                        bottomMargin: height*0.4
                    }
                    Text {
                        id: baudRateTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "Baudrate"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.4
                        model: [ "115200", "57600", "19200", "38400", "4800", "2400","1200",]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }


                }

         }
            Rectangle {
                id: displayFormatBox
                color: parent.childrenColor
                height: appearanceBox.height
                width: appearanceBox.width
                anchors {
                    right:parent.right
                    top: screenBox.top
                }
                Text {
                    id: displayFormatTXT
                    text: "Connection Settings"
                    font.pixelSize: root.fontSize
                    color: "#F2B81E"
                    font.family: standardFont.name
                    anchors {
                        left: parent.left
                        top: parent.top
                        topMargin: height*0.3
                        leftMargin: parent.width*0.05
                    }
                }               Rectangle {
                    id: distanceBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        top: displayFormatTXT.bottom
                        topMargin: height*0.1
                        left: parent.left
                        leftMargin: parent.width*0.1
                    }
                    Text {
                        id: distanceTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "Distance units"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.4
                        model: [ "Kilometers, Centimeters", "Miles, Inches"]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
                Rectangle {
                    id: speedUnitBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        leftMargin: parent.width*0.1
                        bottomMargin: height*0.4
                    }
                    Text {
                        id: speedUnitTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text:"Speed units"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.4
                        model: [ "Kilometers pre hour", "Miles pre hour"]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
            }
            Rectangle {
                id: languageBox
                color: parent.childrenColor
                height: appearanceBox.height
                width: appearanceBox.width
                anchors {
                    right:parent.right
                    top: appearanceBox.top
                }
                Text {
                    id: languaheTXT
                    text: "Connection Settings"
                    font.pixelSize: root.fontSize
                    color: "#F2B81E"
                    font.family: standardFont.name
                    anchors {
                        left: parent.left
                        top: parent.top
                        topMargin: height*0.3
                        leftMargin: parent.width*0.05
                    }
                }               Rectangle {
                    id: languageListBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        top: languaheTXT.bottom
                        topMargin: height*0.1
                        left: parent.left
                        leftMargin: parent.width*0.1
                    }
                    Text {
                        id: languageTXT
                        font.pixelSize: parent.height*0.8
                        font.family: standardFont.name
                        color: "#B6B7BD"
                        text: "UI Language"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.02
                        }
                    }
                    ComboBox {
                        width: parent.width*0.4
                        model: ["English", "German", "Polish"]
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.02
                        }
                    }

                }
                Rectangle {
                    id: buttonBox
                    width: parent.width*0.7
                    height: parent.height*0.25
                    color: "transparent"
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        leftMargin: parent.width*0.1
                        bottomMargin: height*0
                    }
                    Button {
                        id: saveButton
                        width: parent.width*0.2
                        height: parent.height*0.7
                        text: "Save"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: parent.width*0.2
                        }
                    }
                    Button {
                        id: defaultButton
                        width: parent.width*0.2
                        height: parent.height*0.7
                        text: "Default"
                        anchors {
                            verticalCenter: parent.verticalCenter
                            right: parent.right
                            rightMargin: parent.width*0.2
                        }
                    }

                }
            }
         }








//        Slider{
//            id: slider
//            anchors.verticalCenter: parent.verticalCenter
//            anchors.horizontalCenter: parent.horizontalCenter
//            height: parent.height*0.1
//            width: parent.width*0.3
//            from: 10
//            value:  300
//            to: 5000
//        }
//        Text{
//            anchors.bottom: slider.bottom
//            anchors.bottomMargin: slider.height*1
//            anchors.horizontalCenter: parent.horizontalCenter
//            color: "white"
//            text: "Data flow deadTime: " + (slider.value).toFixed(0) + " ms"

//        }
        }
}
