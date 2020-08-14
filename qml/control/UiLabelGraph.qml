import QtQuick 2.0
import FontManager 1.0

Item {
    property alias horizontalAlignment : textContent.horizontalAlignment
    property alias textValue           : textContent.text
    property int   rightMargin         : 0
    property int   leftMargin          : 0

    id : control

    Text{
        id:textContent

        anchors.fill : parent
        anchors.rightMargin: control.rightMargin
        anchors.leftMargin: control.leftMargin
        anchors.bottomMargin: 0
        anchors.topMargin: 0

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment : Text.AlignRight
        font.pixelSize: 15
        font.family: FontManager.nanumGothicName
        elide: Text.ElideRight

        color : "#ACACAC"
        text: "Alarm disable label"


    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
