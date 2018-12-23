function  distanceCalculate(){
    var lowestDistance = 0;
    var lowestIndex = undefined;
    if(numberOfPoint==0)
    {return 0;}
    var index;
    for(index = 0; numberOfPoint>index; index++){
        var distanceToPoint = checkDistance(map.mapItems[index])
        if(distanceToPoint<=20){
            map.removeMapItem(map.mapItems[index]);
            numberOfPoint--;
        }
        else{

        if((distanceToPoint<lowestDistance)||lowestDistance==0){
            lowestIndex = index;
            lowestDistance = distanceToPoint;
        }
    }
    }
        return (lowestDistance/1000).toFixed(2);
}
function checkDistance (value){
    return (planePosition.distanceTo(value.coordinate))


}
