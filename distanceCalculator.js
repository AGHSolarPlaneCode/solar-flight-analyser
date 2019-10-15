function  distanceCalculate(){
    if(numberOfPoint==0)
    {
        return 0;
    }
        var distance = checkDistance(map.mapItems[1])
        if(distance>=50){
            numberOfPoint--;
            map.removeMapItem(map.mapItems[1])
        }
        return (distance/1000).toFixed(2);
}
function checkDistance (value){
    return (planePosition.distanceTo(value.coordinate))
}

function sqrt(value){
    return Math.sqrt(value);
}

