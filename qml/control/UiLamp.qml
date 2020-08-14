import QtQuick 2.0
import QtGraphicalEffects 1.0
import ViewManager 1.0
import "."

Item {
    property bool isOn : false

    id : control
    height: 18
    width: 18
    Rectangle
    {
        id : lamp
        width: 18
        height: 18
        radius: 9
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0
        border.width: 0
        color : isOn? "#D9001B": "#3B3B3B"
    }

    DropShadow {
        anchors.fill: lamp
        horizontalOffset: 1
        verticalOffset: 1
        radius: 2
        color: "#000000"
        samples: 17
        source: lamp
        cached: true
    }
}


