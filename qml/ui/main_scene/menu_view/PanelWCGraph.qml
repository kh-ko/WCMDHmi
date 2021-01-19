import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./graph"
import QtQuick.Layouts 1.3
import PanelWCGraphModel 1.0

UiPanel {

    property int    selIdx : 0
    property int    sensorCnt : 2
    property bool   isRawGraphOn : false
    property int    senstivity : 300
    property int    range : 1000
    property int    min : 0
    property int    max : 0

    id: panel

    width : 1518
    height : 997
    //title: qsTr("Weight checker")

    PanelWCGraphModel
    {
        id : model
    }

    Item {
        id : panelRuntimeGraph
        anchors.fill: parent
        anchors.rightMargin: (parent.width / 2) + 20
        anchors.leftMargin: 20
        anchors.topMargin: 75
        anchors.bottomMargin: 20

        UiLabelSystem
        {
            id: labelMode
            width: 133
            height: 80
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            textValue: qsTr("· Mode")
        }

        UiToggleBtn{
            id: toggleIsRawOn
            width: 150
            height: 60

            anchors.verticalCenter: labelMode.verticalCenter
            anchors.left: labelMode.right
            anchors.leftMargin: 20

            isOn: model.isRawGraphOn
            textValue : model.isRawGraphOn ? qsTr("Raw OFF") : qsTr("Raw ON")

            onSignalEventClicked:
            {
                model.onCommandRawGraphOn(!model.isRawGraphOn)
            }
        }

        UiLabelSystem
        {
            id: labelRuntimeGraph
            width: 231
            height: 80
            anchors.top: labelMode.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            textValue: qsTr("· Runtime graph")
        }

/*
        UiToggleBtn{
            id: toggleIsPause
            width: 150
            height: 60

            anchors.verticalCenter: labelRuntimeGraph.verticalCenter
            anchors.right: labelRuntimeGraph.right

            isOn: model.isPause
            textValue : model.isPause ? qsTr("Start") : qsTr("Pause")

            onSignalEventClicked:
            {
                model.onCommandIsPause(!model.isPause)
            }
        }
*/
        WeightCheckerGraph{
            id : graphRuntime
            anchors.top : labelRuntimeGraph.bottom
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            graphModel: model
        }
    }

    Item {
        id : panelTimingGraph
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: (parent.width / 2) + 20
        anchors.topMargin: 75
        anchors.bottomMargin: 20

        Item {
            id: inputMinMax
            height: 80
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiInputNumber{
                width: 322
                height: 60
                anchors.verticalCenter: parent.verticalCenter
                inputWidth: 200
                labelText: qsTr("· Min")
                postfix: "g"

                min : 0
                max : 99999

                numberValue: model.minRange / 1000

                onSignalChangeValue:
                {
                    model.onCommandSetMinRange(value * 1000)
                }

            }

            UiInputNumber {
                width: 322
                height: 60
                anchors.right: parent.right
                anchors.rightMargin: 0
                inputWidth: 200
                postfix: "g"
                labelText: qsTr("· Max")
                anchors.verticalCenter: parent.verticalCenter
                min : 0
                max : 99999

                numberValue: model.maxRange / 1000

                onSignalChangeValue:
                {
                    model.onCommandSetMaxRange(value * 1000)
                }
            }
        }

        UiLabelSystem
        {
            id: labelTimingGraph
            width: 231
            height: 80
            anchors.top: inputMinMax.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            textValue: qsTr("· Timing graph")
        }

        UiLabelContent {
            id: textCurrentWeight
            y: 80
            width: 231
            height: 80
            textValue: (model.eventValue / 1000).toLocaleString(ViewManager.locale, 'f', 3) +  "g"
            anchors.right: graphTiming.right
            anchors.rightMargin: 10
            anchors.verticalCenter: labelTimingGraph.verticalCenter
        }

        WeightCheckerTimingGraph{
            id : graphTiming
            anchors.top : labelTimingGraph.bottom
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            graphModel: model
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:1;anchors_height:100;anchors_width:100}D{i:7;anchors_x:0;anchors_y:"-90"}
}
##^##*/
