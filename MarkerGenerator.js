var component
var marker

function createMarkerObjects(coord) {
    component = Qt.createComponent("MapMarker.qml");
    if (component.status === Component.Ready)
        finishCreation(coord);
    else
        component.statusChanged.connect(finishCreation);

}

function finishCreation(pos) {
    if (component.status === Component.Ready) {
        //marker = component.createObject(map, {"marker.coordinate": map.toCoordinate(Qt.point(posX,posY))});
        marker = component.createObject(map);
        marker.coordinate = pos;
        map.addMapItem(marker);
        console.log("Object Created " + pos);
        numberOfPoint = numberOfPoint+1;

        //sprite = component.createObject(appWindow);
        if (marker === null) {
            console.log("Error creating Object");
        }
    }
    else if (component.status === Component.Error) {
        console.log("Error loading component:", component.errorString());
    }
}
