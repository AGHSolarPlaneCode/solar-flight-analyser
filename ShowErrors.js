function showErrors() {
    if(errorIterator<=numberOfError){
        errorIcon.source = "qrc:/assetsMenu/exampleAlertIcon2.png"
        errorTXT.text = "Error no. " + errorIterator;
        errorTXT.color = "#DB3D40"
    }
    else if(errorIterator<=(numberOfError+numberOfWarning)){
        errorIcon.source = "qrc:/assetsMenu/warningIcon.png"
        errorTXT.text = "Warning no. " + (errorIterator-numberOfError);
        errorTXT.color = "#eaec0b"

    }

}
function showInformation(){
    informationTXT.text = "Information no. " + informationIterator;
}
