import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtPositioning 5.8
import QtLocation 5.9

Window {
    id: root
    visible: true
    width: 1600
    height: 900
    title: qsTr("GPS Location Software")


    AppMenu {
        id: mainMenu
        anchors.fill: parent
        standardcolor: "#F2B81E"
        mousecontainscolor: "#F8C238"
        switchedcolor: "#F8C238"
        state: "home"

        Rectangle {
            id: mainPage
            color: "#292B38"
            width: parent.width*0.92
            height: parent.height*0.861
            anchors {
                right: parent.right
                bottom: parent.bottom
            }
            border {//
                width: 1
                color: "#333644"
            }
            Loader {
                id: pageLoader
                anchors.fill:parent
                onLoaded: {
                    console.log("Loaded")
                }
            }
        }

            Component {
                id: homePage

            Rectangle {
                anchors.fill: parent
                color: "#292B38"
                border {
                    width: 1
                    color: "#333644"
                }
                HomePage {
                id: homePageItem
                anchors.fill: parent
                }


                        }
            }
            Component {
                id: parametersPage
                Rectangle {
                    anchors.fill: parent
                    color: "#292B38"
                    border {
                        width: 1
                        color: "#333644"
              }
//                    //add parameters page here

//                            }

                        }
            }
            Component {
                id: historicalPage
                Rectangle {
                    anchors.fill: parent
                    color: "#292B38"
                    border {
                        width: 1
                        color: "#333644"
              }
//                    //add historical page here

//                            }

                        }
            }
            Component {
                id: settingsPage
                Rectangle {
                    anchors.fill: parent
                    color: "#292B38"
                    border {
                        width: 1
                        color: "#333644"
              }
//                    //add settings page here

//                            }

                        }
            }


            Connections {
                target: mainMenu
                onButtonClicked : {
                    mainMenu.state = buttonState  //menuButton signal
                }
       }



            onStateChanged:
            {
                console.log("state changed")
                if(mainMenu.state === "home") {
                  pageLoader.sourceComponent = undefined
                  pageLoader.sourceComponent = homePage
                }
                else if(mainMenu.state === "parameters") {
                    pageLoader.sourceComponent = undefined
                //add component to load
                }
                else if(mainMenu.state === "historical") {
                //add component to load
                }
                else if(mainMenu.state === "settings") {
                //add component to load
                }

            }
            states: [
            State {
                    name: "home"

                },
                State {
                    name: "parameters"
                },
                State {
                        name: "historical"

                    },
                State {
                        name: "settings"

                    }

            ]



        }

    }




