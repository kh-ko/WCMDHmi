import QtQuick 2.0
import FontManager 1.0

Item {
    property alias horizontalAlignment : textContent.horizontalAlignment
    property alias textValue           : textContent.text
    property alias textColor           : textContent.color
    property int   rightMargin         : 0
    property int   leftMargin          : 0
    id : control

    Text{
        id:textContent

        anchors.fill : parent
        anchors.rightMargin: rightMargin
        anchors.leftMargin: leftMargin
        anchors.bottomMargin: 0
        anchors.topMargin: 0

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment : Text.AlignLeft
        font.pixelSize: 25
        font.family: FontManager.nanumGothicName
        elide: Text.ElideRight

        color : "#FFFFFF"
        text: "Alarm disable label"
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
