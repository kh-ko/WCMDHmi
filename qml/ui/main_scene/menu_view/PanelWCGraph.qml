import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./graph"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
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

        Item {
            id: inputMinMax
            height: 80
            anchors.top: labelMode.bottom
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





        /*
MaxPDCntPerMin
CurrPDCntPerMin
PDCntPerMin
*/
        UiLabelSystem
        {
            id : labelMaxPDCntPerMin

            height: 60; width: 110
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 0

            textValue: qsTr("· Max PD")
        }

        UiLabelContent {
            id: textMaxPDCntPerMin
            width: 115
            height: 60
            textValue: model.maxPDCntPerMin
            anchors.left: labelMaxPDCntPerMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelMaxPDCntPerMin.verticalCenter
        }

        UiLabelSystem
        {
            id : labelCurrPDCntPerMin

            height: 60; width: 118
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: textMaxPDCntPerMin.right; anchors.leftMargin: 10

            textValue: qsTr("· Mmt PD")
        }

        UiLabelContent {
            id: textCurrPDCntPerMin
            width: 115
            height: 60
            textValue: model.currPDCntPerMin
            anchors.left: labelCurrPDCntPerMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelCurrPDCntPerMin.verticalCenter
        }

        UiLabelSystem
        {
            id : labelPDCntPerMin

            height: 60; width: 105
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: textCurrPDCntPerMin.right; anchors.leftMargin: 10

            textValue: qsTr("· Min PD")
        }

        UiLabelContent {
            id: textPDCntPerMin
            width: 115
            height: 60
            textValue: model.pdCntPerMin
            anchors.left: labelPDCntPerMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelPDCntPerMin.verticalCenter
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

        UiLabelSystem
        {
            id: labelRuntimeGraph
            width: 231
            height: 80
            anchors.top: labelMaxPDCntPerMin.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            textValue: qsTr("· Runtime graph")
        }

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


        UiLabelSystem
        {
            id: labelTimingGraph
            width: 231
            height: 80
            anchors.top: parent.top
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

        UiInputNumber {
            id : inputFilterCoefficient
            width: 322
            height: 60
            anchors.top: labelTimingGraph.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0
            inputWidth: 200
            //postfix: "g"
            labelText: qsTr("· Filter coefficient")
            min : 1
            max : 500

            numberValue: model.filterCoefficient
            //isDisable: ! model.isEditable
            isHighlight: model.isEditFilterCoefficient

            onSignalChangeValue:
            {
                model.onCommandSetFilterCoefficient(value)
            }
        }

        Item {
            id: inputMeasureCueSignMeasureSection
            height: 150
            anchors.top: inputFilterCoefficient.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiInputNumber{
                id : inputMeasureCueSign
                width: 322
                height: 60
                anchors.top: parent.top; anchors.topMargin: 10
                inputWidth: 200
                labelText: qsTr("· Cue sign")
                postfix: "ms"

                min : 0
                max : 99999

                numberValue: model.measureCueSign
                //isDisable: ! model.isEditable
                isHighlight: model.isEditMeasureCueSign

                onSignalChangeValue:
                {
                    var temp = Math.ceil(value/10) * 10
                    model.onCommandSetMeasureCueSign(temp)
                }

            }

            UiButton{
                height: 60; width: (inputMeasureCueSign.width / 2) - 10
                anchors.top: inputMeasureCueSign.bottom; anchors.topMargin: 10; anchors.left: inputMeasureCueSign.left; anchors.leftMargin: 0

                isImage : true; imageSource:"/control/img_btn/left-blue.png"
                //isDisable: ! model.isEditable
                onSignalEventClicked: {
                    model.onCommandSetMeasureCueSign(model.measureCueSign - 10)
                }

            }

            UiButton{
                height: 60; width: (inputMeasureCueSign.width / 2) - 10
                anchors.top: inputMeasureCueSign.bottom; anchors.topMargin: 10; anchors.right: inputMeasureCueSign.right; anchors.rightMargin: 0

                isImage : true; imageSource:"/control/img_btn/right-blue.png"
                //isDisable: ! model.isEditable

                onSignalEventClicked: {
                    model.onCommandSetMeasureCueSign(model.measureCueSign + 10)
                }

            }


            UiInputNumber {
                id : inputMeasureSection
                width: 322
                height: 60
                anchors.right: parent.right
                anchors.rightMargin: 0
                inputWidth: 200
                postfix: "ms"
                labelText: qsTr("· Section")
                anchors.top: parent.top; anchors.topMargin: 10
                min : 0
                max : 99999

                numberValue: model.measureSection
                //isDisable: ! model.isEditable
                isHighlight: model.isEditMeasureSection

                onSignalChangeValue:
                {
                    var temp = Math.ceil(value/10) * 10
                    model.onCommandSetMeasureSection(temp)
                }
            }

            UiButton{
                height: 60; width: (inputMeasureSection.width / 2) - 10
                anchors.top: inputMeasureSection.bottom; anchors.topMargin: 10; anchors.left: inputMeasureSection.left; anchors.leftMargin: 0

                isImage : true; imageSource:"/control/img_btn/left-yellow.png"
                //isDisable: ! model.isEditable

                onSignalEventClicked: {
                    model.onCommandSetMeasureSection(model.measureSection - 10);
                }
            }

            UiButton{
                height: 60; width: (inputMeasureSection.width / 2) - 10
                anchors.top: inputMeasureSection.bottom; anchors.topMargin: 10; anchors.right: inputMeasureSection.right; anchors.rightMargin: 0

                isImage : true; imageSource:"/control/img_btn/right-yellow.png"
                //isDisable: ! model.isEditable

                onSignalEventClicked: {
                    model.onCommandSetMeasureSection(model.measureSection + 10);
                }
            }


        }

        WeightCheckerTimingGraph{
            id : graphTiming
            anchors.top : inputMeasureCueSignMeasureSection.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            graphModel: model
        }
    }

    UiButton{
        id: btnZero
        width : 164
        height : 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: panelTimingGraph.left
        anchors.leftMargin: 20

        textValue: qsTr("ZERO")

        onSignalEventClicked: {
            model.onCommandZERO()
        }
    }

    UiButtonAni{
        id : btnApply
        width : 164
        height : 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: btnCancle.left
        anchors.rightMargin: 20

        isPlay : true

        visible: model.isEditFilterCoefficient    ||
                 model.isEditMeasureCueSign       ||
                 model.isEditMeasureSection

        type : QmlEnumDef.BUTTON_TYPE_BLUE
        textValue: qsTr("Apply")

        onSignalEventClicked:
        {
            var ret = model.onCommandApply();

            switch(ret)
            {
            case EnumDef.PDERR_NONE:
                ViewManager.toast.show(qsTr("Your settings have been saved."))
                break;

            case EnumDef.PDERR_FILE_WRITE:
                ViewManager.toast.show(qsTr("SQL error is occured."))
                break;

            case EnumDef.PDERR_NOT_EXIST:
                ViewManager.toast.show(qsTr("This product dose not exist."))
                break;
            }
        }
    }

    UiButton{
        id : btnCancle
        width : 164
        height : 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : btnApply.visible

        type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
        textValue: qsTr("Cancle")

        onSignalEventClicked:
        {
            model.onCommandCancel()
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
