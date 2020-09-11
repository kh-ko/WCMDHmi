import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import EnumDefine 1.0
import ViewManager 1.0

Item {
    property real min   : 0
    property real max   : 100
    property real value : 50
    property color barColor : "#FFFFFF"
    property int radius : 20
    property real barLength : (bg.width > bg.height) ? (bg.width - 10) * ((control.value - control.min) / (control.max - control.min)) :
                                                 (bg.height - 10) * ((control.value - control.min) / (control.max - control.min))
    property int minimumSize : 0

    id: control
    width : 285
    height: 32

    Rectangle{
        id : bg
        color: "#59000000"
        radius: control.radius
        border.width: 0
        anchors.fill: parent
    }


    Rectangle{
        id : hBar
        width: barLength < minimumSize ? minimumSize :
               barLength > (bg.width - 10)       ? (bg.width - 10)       : barLength
        color: control.barColor
        radius: control.radius
        anchors.left: bg.left
        anchors.leftMargin: 5
        anchors.bottom: bg.bottom
        anchors.bottomMargin: 5
        anchors.top: bg.top
        anchors.topMargin: 5
        border.width: 0

        visible: (bg.width > bg.height)
    }

    Glow {
        opacity: 0.3
        anchors.fill: hBar
        radius: 15
        samples: 17
        source: hBar
        color: hBar.color
        visible: hBar.visible
    }

    Rectangle{
        id : vBar
        height: barLength < minimumSize ? minimumSize :
                barLength > (bg.height - 10)      ? (bg.height - 10)       : barLength
        color: control.barColor
        radius: control.radius
        anchors.left: bg.left
        anchors.leftMargin: 5
        anchors.right: bg.right
        anchors.rightMargin: 5
        anchors.bottom: bg.bottom
        anchors.bottomMargin: 5
        border.width: 0

        visible: (bg.height > bg.width)
    }

    Glow {
        opacity: 0.3
        anchors.fill: vBar
        radius: 15
        samples: 17
        source: vBar
        color: vBar.color
        visible: vBar.visible
    }

}
