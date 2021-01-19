import QtQuick 2.0
import ViewManager 1.0
import FontManager 1.0

Item {
    property bool isHighlight : false
    property bool isSelect : false
    property alias textValue :  label.text
    property bool isPress : false
    property bool isDisable :false
    property var  textMargin : 20
    id : control
    width: 200
    height: 75

    signal signalEventClicked()

    Rectangle
    {
        id: bg
        width: 40
        height: 40
        color : "#00000000"
        border.width: 5
        border.color: "#0085FF"
        radius: width / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0

        Rectangle
        {
            id: check
            visible: isSelect
            anchors.fill: parent
            anchors.margins: 7
            color : "#0085FF"
            border.width: 0
            radius: width / 2
        }
    }

    Text{
        id : label

        height: parent.height
        width: parent.width - bg.width - control.textMargin
        anchors.verticalCenter: bg.verticalCenter
        anchors.left: bg.right
        anchors.leftMargin: control.textMargin

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment : Text.AlignLeft
        font.pixelSize: 25
        font.family: FontManager.nanumGothicName
        elide: Text.ElideRight

        color : isHighlight? "#0085FF" : "#FFFFFF"
        text: "Alarm disable label"
    }

    Rectangle{
        width: 40
        height: 40
        anchors.verticalCenter: bg.verticalCenter
        anchors.horizontalCenter: bg.horizontalCenter
        radius: bg.radius

        color: "#59000000"

        visible: control.isPress || control.isDisable
    }

    MouseArea
    {
        anchors.fill: parent

        onPressed: {control.isPress = true}
        onReleased:{control.isPress = false}
        onClicked: {signalEventClicked();}
    }
}
