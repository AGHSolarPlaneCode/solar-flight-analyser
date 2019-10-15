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
        marker = component.createObject(map);
        marker.number = map.mapItems.length;
        marker.coordinate = pos;
        map.addMapItem(marker);
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
function removeMarker(marker){
    var index = marker.number-1
    map.removeMapItem(marker);
    numberOfPoint--;
    if(map.mapItems.length>1){
    for(var i = 1; i < map.mapItems.length; i++){
        map.mapItems[i].number = i;
    }
    }
   }
function addPoints(){
    var dbLat = waypoint.DBLat
    var dbLong = waypoint.DBLong
    for(var i = 0; i < dbLat.length; i++){
        createMarkerObjects( QtPositioning.coordinate(dbLat[i],dbLong[i]))
    }
}
function clearMap(){
    while(map.mapItems.length>1){
        if(map.mapItems[1].isPositionMarker){
        map.removeMapItem(map.mapItems[1])
            numberOfPoint--
        }
    }
}
