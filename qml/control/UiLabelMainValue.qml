import QtQuick 2.0
import ViewManager 1.0
import FontManager 1.0

Item {
    property bool isPreview : true
    property alias textValue : textContent.text

    id : control

    width : textContent.width
    height : 46

    Text{
        id:textContent

        height: 46
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 40
        font.family: FontManager.nanumGothicName
        color : isPreview ? "#FFFFFF" : ViewManager.defaultColor

        text: "Main value"
    }
}


