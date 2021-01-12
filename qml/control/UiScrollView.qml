import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import ViewManager 1.0

ScrollView {
    property color barPressColor : "#39FFFFFF"
    property color barColor : "#59FFFFFF"

    id :control
    clip            : true

    background: Rectangle{
        color : "#00000000"
    }

    ScrollBar.vertical: ScrollBar {
        id : vSBar

        active: true
        orientation: Qt.Vertical
        width: 10 / ViewManager.scale
        height: control.availableHeight
        anchors.right: control.right
        anchors.rightMargin: 5 / ViewManager.scale
        policy: control.availableHeight  < control.contentHeight ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

        contentItem: Rectangle
        {
            width: 10 / ViewManager.scale
            implicitHeight: 100
            radius: width / 2
            color: vSBar.pressed ?  barPressColor : barColor
        }

        background: Rectangle{
            color : "#00000000"
        }
    }

    /*
    ScrollBar.horizontal: ScrollBar {
        id : hSBar

        interactive: false
        active: false
        enabled: false
        orientation: Qt.Horizontal

        height: 10 / ViewManager.scale
        width: control.availableWidth
        anchors.bottom: control.bottom
        anchors.bottomMargin: 5 / ViewManager.scale
        policy: control.availableWidth  < control.contentWidth ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

        contentItem: Rectangle
        {
            implicitWidth: 100
            height: 10 / ViewManager.scale
            radius: height / 2
            color: hSBar.pressed ? barPressColor : barColor
        }

        background: Rectangle{
            color : "#00000000"
        }
    }
    */
}
