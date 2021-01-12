import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import QmlEnumDef 1.0
import ViewManager 1.0

Item {
    property int senstivity : 400
    property int total      : 400
    property int detect     : 400
    property int signal : 150
    property bool isDetail : false

    signal signalEditMDSetting()

    id : panel

    width : 245
    height: 690

    Component.onCompleted: {
        if(isDetail)
        {
            panelStatistics.height = 235;
        }
        else
        {
            panelStatistics.height = 120;
        }

        trans.enabled = true
    }

    states: State
    {
        name: "detail"
        when: panel.isDetail
        PropertyChanges { target: panelStatistics; height : 235}
    }

    transitions: Transition
    {
        id : trans
        enabled : false
        from: ""
        to: "detail"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: panelStatistics; properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
        }
    }

    UiPanel{
        id: bg
        anchors.fill: parent

        type : QmlEnumDef.PANEL_TYPE_METAL
        title: qsTr("Metal detector")

        UiProgressBar{
            id: progressbarMD
            width: 83
            radius: 10
            barColor: panel.signal > panel.senstivity ? "#D9001B": "#56d263"
            anchors.top: parent.top
            anchors.topMargin: bg.titleHeight + 10
            anchors.bottom: panelStatistics.top
            anchors.bottomMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter

            min: panel.senstivity * 2 * 0.25
            max: panel.senstivity * 2* 0.75
            value: panel.signal
            minimumSize: 10
        }

        Image
        {
            anchors.left: progressbarMD.right
            anchors.leftMargin: 0
            anchors.verticalCenter: progressbarMD.verticalCenter
            rotation: 90
            source: "img_panelmetaldetector/md_gauge.png"

        }

        Item
        {
            id: panelStatistics
            height: 120
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiStatistics{
                id : statisticsMD
                //height: panel.isDetail ? 213 : 100
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 0

                isDetail      : panel.isDetail
                imgSrc        : "img_panelevent/metaldetect.png"
                title         : qsTr("Metal")
                value01       : ""+ panel.senstivity + " mv"
                total         : panel.total
                value02       : panel.detect
                bgColor       : "#59D9001B"
                graphColor    : "#D9001B"

                onSignalEventClicked : {
                    panel.signalEditMDSetting()
                }
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
