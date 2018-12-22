function  distanceCalculate(){
    var lowestDistance = 9999999999999;
    var lowestIndex = undefined;
    if(numberOfPoint==0)
    {return 0;}
    var index;
    for(index = 0; numberOfPoint>index; index++){
        if((checkDistance(map.mapItems[index]))<(lowestDistance)){
            lowestIndex = index;
            lowestDistance = checkDistance(map.mapItems[index]);
        }
    }
        return (lowestDistance/1000).toFixed(0);
}
function checkDistance (value){
    return (planePosition.distanceTo(value.coordinate))


}
