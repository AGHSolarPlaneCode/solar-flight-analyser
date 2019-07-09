var component
var scene
function showPage(list, sceneNumber) {
    while(list.count > 0) {
                list.get(0).obj.destroy();
                list.remove(0);
    }
    if(sceneNumber === 1){
        component = Qt.createComponent("WeatherMainPage.qml");
        weatherWidget.page = 1
        if (component.status === Component.Ready)
            finishCreation(list,scene);
        else
            component.statusChanged.connect(finishCreation);

    }
    else  if(sceneNumber === 3){
        component = Qt.createComponent("WeatherSettingsPage.qml");
        weatherWidget.page = 3
        if (component.status === Component.Ready)
            finishCreation(list,scene);
        else
            component.statusChanged.connect(finishCreation);

    }
    else if(sceneNumber === 2){
        component = Qt.createComponent("WeatherLocationPage.qml");
        weatherWidget.page = 2
        if (component.status === Component.Ready)
            finishCreation(list,scene);
        else
            component.statusChanged.connect(finishCreation);

    }
}
function finishCreation(list, scene) {
    if (component.status === Component.Ready) {
        scene = component.createObject(weatherPageBackground)
        list.append({"obj": scene});
        }

    else if (component.status === Component.Error) {
        console.log("Error loading component:", component.errorString());
    }
}
