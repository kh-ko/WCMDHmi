import QtQuick 2.0
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0

Item {
    property bool isDisable : false
    property alias textValue : textContent.text

    id : control
    width: 200
    height: 200

    property bool isOn : false
    property bool isPress : false

    signal signalEventClicked()

    Rectangle {
        id: bg
        color : isOn ? "#0085FF" : "#333333"
        anchors.fill: parent
        radius: 20
        border.width: 0
        visible: false
    }

    DropShadow {
        anchors.fill: bg
        horizontalOffset: 5
        verticalOffset: 5
        radius: 5
        color: "#000000"
        samples: 17
        source: bg
        cached: true
        visible: !control.isPress && !control.isOn && !control.isDisable
    }

    InnerShadow {
        anchors.fill: bg
        horizontalOffset: 5
        verticalOffset: 5
        radius: 5
        color: "#000000"
        samples: 17
        source: bg
        cached: true
        visible: (control.isPress || control.isOn) && !control.isDisable
    }


    Text{
        id:textContent

        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 25
        font.family: FontManager.nanumGothicName
        color : isOn ? "#ffffff" : "#ACACAC"
        text: "Main button label"
    }

    Rectangle
    {
        color: "#59000000"
        border.width: 0
        anchors.fill: bg
        radius: bg.radius
        visible: control.isPress || control.isDisable
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed:  {if(control.isDisable) return;control.isPress = true; }
        onReleased: {if(control.isDisable) return;control.isPress = false; }
        onClicked:  {if(control.isDisable) return;control.signalEventClicked(); }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
