import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./graph"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelMDGraphModel 1.0

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
    title: qsTr("Metal detector")

    PanelMDGraphModel
    {
        id : model
    }

    RowLayout {
        spacing: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 0

        Item {
            width: 200
            height: 200
            Layout.preferredHeight: -1
            Layout.preferredWidth: -1
            Layout.fillHeight: true
            Layout.fillWidth: true

            UiLabelSystem
            {
                id: labelMode
                width: 133
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 95
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
/*
            UiRadioBtn{
                id: radioRawMode
                width: 150
                height: 80
                textValue: qsTr("Raw")
                anchors.verticalCenter: labelMode.verticalCenter
                anchors.left: labelMode.right
                anchors.leftMargin: 20

            }

            UiRadioBtn {
                id: radioRawMode1
                width: 150
                height: 80
                anchors.leftMargin: 20
                anchors.verticalCenter: labelMode.verticalCenter
                textValue: qsTr("Filter")
                anchors.left: radioRawMode.right
            }
*/
            UiInputNumber
            {
                id: inputRange
                width: 450
                height: 60
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: labelMode.bottom
                anchors.topMargin: 10

                inputWidth: 300
                labelText: qsTr("· Range")
                isLocaleStyle: false
                postfix: "mv"

                numberValue : model.range
                min         : 10
                max         : 9999

                onSignalChangeValue: {
                    model.onCommandSetRange(value);
                }

                Text {
                    color: "#acacac"
                    text: "±"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 164
                    font.pixelSize: 30
                }

               /* Text {
                    color: "#acacac"
                    text: "_"
                    anchors.leftMargin: 164
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    font.pixelSize: 20
                    anchors.left: parent.left
                }*/

            }

            MetalDetectorGraph{

                id : mainGraph

                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: inputRange.bottom
                anchors.topMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 0

                isSelect : true
                viewMode : QmlEnumDef.MD_GRAPH_SMALL

                graphModel : model.onCommandGetGraphModel(selIdx)

            }

        }

        Item {
            width: 200
            height: 200
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: model.sensorCnt > 1

            UiLabelSystem{
                id : labelMax
                width: 100
                height: 80
                textValue: qsTr("· Max")
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            UiLabelContent
            {
                id : valueMax
                width: 80
                height: 80
                anchors.verticalCenter: labelMax.verticalCenter
                anchors.left: labelMax.right
                anchors.leftMargin: 0
                horizontalAlignment: Text.AlignRight

                textValue: model.max//panel.max
            }

            UiLabelSystem{
                id : labelMin
                width: 100
                height: 80
                textValue: qsTr("· Min")
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: valueMax.right
                anchors.leftMargin: 100
            }

            UiLabelContent
            {
                width: 80
                height: 80
                anchors.verticalCenter: labelMin.verticalCenter
                anchors.left: labelMin.right
                anchors.leftMargin: 0
                horizontalAlignment: Text.AlignRight

                textValue: model.min //panel.min
            }

            ColumnLayout {
                id: columnLayout
                anchors.top: labelMax.bottom
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 0
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible: model.sensorCnt > 1 //panel.sensorCnt > 0

                    graphModel : model.onCommandGetGraphModel(0)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 0;
                    }


                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 1
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible:  model.sensorCnt > 1

                    graphModel : model.onCommandGetGraphModel(1)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 1;
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 2
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible: model.sensorCnt > 2

                    graphModel : model.onCommandGetGraphModel(2)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 2
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 3
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible:  model.sensorCnt > 3

                    graphModel : model.onCommandGetGraphModel(3)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 3
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 4
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible:  model.sensorCnt > 4

                    graphModel : model.onCommandGetGraphModel(4)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 4
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 5
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible: model.sensorCnt > 5

                    graphModel : model.onCommandGetGraphModel(5)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 5
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 6
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible:  model.sensorCnt > 6

                    graphModel : model.onCommandGetGraphModel(6)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 6
                    }
                }

                MetalDetectorGraph{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    isSelect : panel.selIdx == 7
                    viewMode     : QmlEnumDef.MD_GRAPH_SMALL
                    visible:  model.sensorCnt > 7

                    graphModel : model.onCommandGetGraphModel(7)

                    onSignalEventClicked:
                    {
                        panel.selIdx = 7
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:1;anchors_height:100;anchors_width:100}D{i:7;anchors_x:0;anchors_y:"-90"}
D{i:8;anchors_x:0;anchors_y:"-90"}D{i:15;anchors_height:100;anchors_width:100}
}
##^##*/
