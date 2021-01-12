import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDef 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import QtGraphicalEffects 1.0

Item {
    property int viewMode : EnumDef.WC_VIEWMODE_CURRENT
    id : panel
    height: 352
    width: 158

    signal signalEventClickedNumber()
    signal signalEventClickedDev()
    signal signalEventClickedTrends()
    Rectangle
    {
        id : container
        anchors.fill: parent
        radius: 30
    }

    DropShadow {
        anchors.fill: container
        horizontalOffset:  5
        verticalOffset: 5
        radius: 5
        samples: 17
        color: "#000000"
        source: container
        cached: true
        transparentBorder: true
    }

    Rectangle
    {
        property bool isPress : false

        id: rectangle
        height: panel.height / 3 + 30
        width: panel.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0

        radius: 20
        border.width: 1
        color : panel.viewMode === EnumDef.WC_VIEWMODE_CURRENT ? "#0085FF" : "#333333"

        Image {
            anchors.verticalCenterOffset: -15
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source:panel.viewMode === EnumDef.WC_VIEWMODE_CURRENT ? "img_btn/btn_number_s.png" : "img_btn/btn_number_n.png"
        }

        Rectangle{
            anchors.fill: parent
            radius : parent.radius
            color : "#59000000"

            visible: parent.isPress
        }

        MouseArea{
            anchors.fill: parent

            onPressed: {parent.isPress = true}
            onReleased: {parent.isPress = false}
            onClicked: { panel.signalEventClickedNumber()}
        }
    }

    Rectangle{
        property bool isPress : false

        height: panel.height / 3 + 30
        width: panel.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom : parent.bottom
        anchors.bottomMargin: 0

        radius: 20
        border.width: 1
        color : panel.viewMode === EnumDef.WC_VIEWMODE_TRENDS ? "#0085FF" : "#333333"

        Image {
            anchors.verticalCenterOffset: 15
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: panel.viewMode === EnumDef.WC_VIEWMODE_TRENDS? "img_btn/btn_trends_s.png" : "img_btn/btn_trends_n.png"
        }

        Rectangle{
            anchors.fill: parent
            radius : parent.radius
            color : "#59000000"

            visible: parent.isPress
        }

        MouseArea{
            anchors.fill: parent

            onPressed: {parent.isPress = true}
            onReleased: {parent.isPress = false}
            onClicked: { panel.signalEventClickedTrends()}
        }
    }

    Rectangle{
        property bool isPress : false

        id : btnDelta

        height: panel.height / 3
        width: panel.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        border.width: 1
        color : panel.viewMode === EnumDef.WC_VIEWMODE_DELTA ? "#0085FF" : "#333333"

        Image {
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: panel.viewMode === EnumDef.WC_VIEWMODE_DELTA ? "img_btn/btn_number_delta_s.png" : "img_btn/btn_number_delta_n.png"
        }

        Rectangle{
            anchors.fill: parent
            radius : parent.radius
            color : "#59000000"

            visible: parent.isPress
        }

        MouseArea{
            anchors.fill: parent

            onPressed: {parent.isPress = true}
            onReleased: {parent.isPress = false}
            onClicked: {panel.signalEventClickedDev()}
        }
    }

    Rectangle{
        id : divider01
        height: 7
        color: "#232323"
        radius: 3
        anchors.bottom: btnDelta.top
        anchors.bottomMargin: -4
        border.width: 1
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        visible: false
    }

    DropShadow {
        id : divider01Drop
        anchors.fill: divider01
        horizontalOffset:  2
        verticalOffset: 2
        radius: 2
        samples: 17
        color: "#000000"
        source: divider01
        cached: true
        transparentBorder: true
    }

    Rectangle{
        id : divider02
        height: 7
        color: "#232323"
        radius: 3
        anchors.top: btnDelta.bottom
        anchors.topMargin: -4
        border.width: 1
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        visible: false
    }

    DropShadow {
        id : divider02Drop
        anchors.fill: divider02
        horizontalOffset:  2
        verticalOffset: 2
        radius: 2
        samples: 17
        color: "#000000"
        source: divider02
        cached: true
        transparentBorder: true
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}
}
##^##*/
