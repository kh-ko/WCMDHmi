import QtQuick 2.0
import QtGraphicalEffects 1.0
import ViewManager 1.0
import QmlEnumDef 1.0
Item {
    property int customFontSize : 30
    property int type : QmlEnumDef.PANEL_TYPE_DEFAULT
    property string title : ""
    property int titleHeight : title == "" ? 0 : labelTitle.height

    property color bgColor : type == QmlEnumDef.PANEL_TYPE_DEFAULT    ? "#232323" :
                             type == QmlEnumDef.PANEL_TYPE_UP_PANEL   ? "#333333" :
                             type == QmlEnumDef.PANEL_TYPE_METAL      ? "#6FB300" :
                             type == QmlEnumDef.PANEL_TYPE_WEIGHT     ? "#005DB3" :
                             type == QmlEnumDef.PANEL_TYPE_SELECT     ? "#00294F" :
                             type == QmlEnumDef.PANEL_TYPE_DROP_SELECT? "#002140" :
                             type == QmlEnumDef.PANEL_TYPE_DROP       ? "#191919" :
                             type == QmlEnumDef.PANEL_TYPE_POPUP      ? "#434343" :
                             type == QmlEnumDef.PANEL_TYPE_WEIGHT_UP  ? "#0085FF" :
                             type == QmlEnumDef.PANEL_TYPE_BIG_MD     ? "#005DB3" :
                             type == QmlEnumDef.PANEL_TYPE_NONE       ? "#00000000": "#232323"
    id : control

    Rectangle{
        id : bg

        radius: 10
        gradient: Gradient {
            GradientStop {
                position: 0
                color: type == QmlEnumDef.PANEL_TYPE_DEFAULT    ? "#232323" :
                       type == QmlEnumDef.PANEL_TYPE_UP_PANEL   ? "#333333" :
                       type == QmlEnumDef.PANEL_TYPE_METAL      ? "#6FB300" ://"#6FB300" :
                       type == QmlEnumDef.PANEL_TYPE_WEIGHT     ? "#005DB3" ://"#005DB3" :
                       type == QmlEnumDef.PANEL_TYPE_SELECT     ? "#00294F" :
                       type == QmlEnumDef.PANEL_TYPE_DROP_SELECT? "#002140" :
                       type == QmlEnumDef.PANEL_TYPE_DROP       ? "#191919" :
                       type == QmlEnumDef.PANEL_TYPE_POPUP      ? "#434343" :
                       type == QmlEnumDef.PANEL_TYPE_WEIGHT_UP  ? "#0085FF" :
                       type == QmlEnumDef.PANEL_TYPE_BIG_MD     ? "#005DB3" :
                       type == QmlEnumDef.PANEL_TYPE_NONE       ? "#00000000" : "#232323"
            }

            GradientStop {
                position: 1
                color: type == QmlEnumDef.PANEL_TYPE_DEFAULT     ? "#232323" :
                       type == QmlEnumDef.PANEL_TYPE_UP_PANEL    ? "#333333" :
                       type == QmlEnumDef.PANEL_TYPE_METAL       ? "#232323" :
                       type == QmlEnumDef.PANEL_TYPE_WEIGHT      ? "#232323" :
                       type == QmlEnumDef.PANEL_TYPE_SELECT      ? "#00294F" :
                       type == QmlEnumDef.PANEL_TYPE_DROP_SELECT ? "#002140" :
                       type == QmlEnumDef.PANEL_TYPE_DROP        ? "#191919" :
                       type == QmlEnumDef.PANEL_TYPE_POPUP       ? "#434343" :
                       type == QmlEnumDef.PANEL_TYPE_BIG_MD      ? "#232323" :
                       type == QmlEnumDef.PANEL_TYPE_WEIGHT_UP   ? "#0085FF" : "#232323"
            }
        }
        border.width: 0
        anchors.fill: parent
        visible: false
    }

    DropShadow {
        id : bgDrop
        anchors.fill: bg
        horizontalOffset:  5
        verticalOffset: 5
        radius: 5
        samples: 17
        color: "#000000"
        source: bg
        cached: true
        transparentBorder: true

        visible: type == QmlEnumDef.PANEL_TYPE_DROP_SELECT || type == QmlEnumDef.PANEL_TYPE_DROP || type == QmlEnumDef.PANEL_TYPE_NONE ? false : true
    }

    InnerShadow {
        id : bgInner
        anchors.fill: bg
        horizontalOffset: 5
        verticalOffset:5
        radius: 5
        samples: 17
        color: "#59000000"
        source: bg
        cached: true

        visible: bgDrop.visible == false && type != QmlEnumDef.PANEL_TYPE_NONE ? true : false
    }

    UiLabelTitle{
        id : labelTitle
        height: 75
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        leftMargin : 20

        customFontSize : control.customFontSize
        textValue: title

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
