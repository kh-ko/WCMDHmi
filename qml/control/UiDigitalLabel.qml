import QtQuick 2.0
import EnumDefine 1.0
import FontManager 1.0
import ViewManager 1.0

Item {
    property bool   visibleNet : true
    property int    fontSize :  100
    property int    eventType :EnumDefine.WEIGHT_OVER_TYPE
    property bool   isCenter : true
    property real    value : 9910.0
    property string postFix : "g"

    id: control


    Text {
        id: textBg
        x : isCenter ? (parent.width - (contentWidth + textPostFix.contentWidth + (control.fontSize * 0.0625))) / 2 : 0
        height: control.fontSize
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter

        font.pixelSize : control.fontSize
        font.family: FontManager.nanumGothicBName

        color: "#00000000"

        text : "8,888.8"

    }

    Text {

        id: textContent
        height: control.fontSize
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: textBg.right
        anchors.rightMargin: 0


        font.pixelSize : control.fontSize
        font.family: FontManager.nanumGothicBName
        font.bold: true

        color: eventType == EnumDefine.WEIGHT_OVER_TYPE ? "#F59A23" : "#D9001B"
        /*eventType == EnumDefine.WEIGHT_OVER_TYPE || eventType == EnumDefine.WEIGHT_UNDER_TYPE ? "#D9001B"
               : eventType == EnumDefine.WEIGHT_OVER_WARNING_TYPE || eventType == EnumDefine.WEIGHT_UNDER_WARNING_TYPE ? "#F59A23"
               : "#FFFFFF"*/

        text : (control.value / 1000).toLocaleString(ViewManager.locale, 'f', 1)
    }

    Text {

        id: textNET
        verticalAlignment: Text.AlignVCenter
        anchors.left: textBg.right
        anchors.leftMargin: control.fontSize * 0.0625
        anchors.top: textBg.top
        anchors.topMargin: control.fontSize * 0.165
        font.pixelSize : control.fontSize * 0.25
        font.family: FontManager.nanumGothicName

        visible: control.visibleNet
        color: "#ACACAC"

        text : "NET"
    }

    Text {

        id: textPostFix
        verticalAlignment: Text.AlignVCenter
        anchors.left: textBg.right
        anchors.leftMargin: control.fontSize * 0.0625
        anchors.bottom: textBg.bottom
        anchors.bottomMargin: control.fontSize * 0.165
        font.pixelSize : control.fontSize * 0.25
        font.family: FontManager.nanumGothicName

        color: "#ACACAC"

        text : control.postFix
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
