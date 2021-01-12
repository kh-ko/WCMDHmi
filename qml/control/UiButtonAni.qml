import QtQuick 2.0
import QtGraphicalEffects 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import FontManager 1.0

Item {
    property int    type : 0
    property bool   isImage : false
    property string textValue : "test"
    property alias  imageSource : imageIcon.source
    property bool   isPlay : false
    id : control

    width: 200
    height: 200

    property color btnColor : type == QmlEnumDef.BUTTON_TYPE_DEFAULT ? "#333333" :
                              type == QmlEnumDef.BUTTON_TYPE_UP_PANEL? "#434343" :
                              type == QmlEnumDef.BUTTON_TYPE_POPUP   ? "#535353" :
                              type == QmlEnumDef.BUTTON_TYPE_BLUE    ? "#0085FF" :
                              type == QmlEnumDef.BUTTON_TYPE_METAL   ? "#70B603" : "#333333"

    property color textColor : type == QmlEnumDef.BUTTON_TYPE_DEFAULT ? "#ACACAC" : "#FFFFFF"

    property bool isDisable : false
    property bool isPress : false

    signal signalEventClicked()

    Rectangle {
        id: bg
        color : btnColor
        anchors.fill: parent
        radius: 20
        border.width: 0
        visible: control.isDisable ? true :
                 control.isPlay    ? true : false
    }

    Glow {
        opacity: 0.3
        anchors.fill: bg
        radius: 15
        samples: 17
        source: bg
        color: bg.color
        visible: isPlay

        SequentialAnimation on opacity {
                loops: Animation.Infinite

                PropertyAnimation { to: 1; duration : 500; easing.type : Easing.InOutExpo}
                PropertyAnimation { to: 0; duration : 500; easing.type : Easing.InOutExpo }
            }
    }

    DropShadow {
        anchors.fill: bg
        horizontalOffset: control.isPress? 2 : 5
        verticalOffset: control.isPress? 2 : 5
        radius: 5
        color: "#000000"
        samples: 17
        source: bg
        cached: true
        visible: control.isDisable ? false :
                 control.isPlay     ? false : true
    }

    Image {
        id: imageIcon
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        width : sourceSize.width
        height: sourceSize.height
        fillMode: Image.PreserveAspectFit
        visible: isImage
    }

    Text{
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
        font.pixelSize: 25
        font.family: FontManager.nanumGothicName

        color : control.textColor
        text : control.textValue
        visible: !control.isImage
    }

    Rectangle
    {
        color: "#59000000"
        border.width: 0
        anchors.fill: bg
        radius: bg.radius
        visible: control.isDisable || control.isPress ? true : false
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed: { if(control.isDisable === false)control.isPress = true; }
        onReleased: { if(control.isDisable === false)control.isPress = false; }
        onClicked: { if(control.isDisable === false)control.signalEventClicked(); }
    }

}



/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
