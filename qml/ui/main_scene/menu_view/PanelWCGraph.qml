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

    UiInputNumber {
        id : inputZeroDelayTime
        height: 60; width: 400

        anchors.top: parent.top; anchors.topMargin: 20; anchors.right: panelRuntimeGraph.right
        inputWidth: 180
        postfix: "ms"
        labelText: qsTr("· Zero delay time")
        min : 0
        max : 9999

        numberValue: model.zeroDelayTime
        //isDisable: ! model.isEditable
        isHighlight: model.isEditZeroDelayTime

        onSignalChangeValue:
        {
            model.onCommandSetZeroDelayTime(value)
        }
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

        UiInputNumber {
            id : inputGraphPointCnt
            height: 60; width: 350

            anchors.verticalCenter: labelMode.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 0;
            inputWidth: 130
            //postfix: "g"
            labelText: qsTr("· Graph count")
            min : 1
            max : 100

            numberValue: model.graphPointCnt
            //isDisable: ! model.isEditable
            isHighlight: model.isEditGraphPointCnt

            onSignalChangeValue:
            {
                model.onCommandSetGraphPointCnt(value)
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

                min : -99999
                max : 99999

                inputType: QmlEnumDef.S_INT_MODE
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
                min : -99999
                max : 99999

                inputType: QmlEnumDef.S_INT_MODE
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

            height: 60; width: 125
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 0

            textValue: qsTr("· Max PPM")
        }

        UiLabelContent {
            id: textMaxPDCntPerMin
            width: 114
            height: 60
            textValue: model.maxPDCntPerMin
            anchors.left: labelMaxPDCntPerMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelMaxPDCntPerMin.verticalCenter
        }

        UiLabelSystem
        {
            id : labelCurrPDCntPerMin

            height: 60; width: 125
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: textMaxPDCntPerMin.right; anchors.leftMargin: 10

            textValue: qsTr("· Act PPM")
        }

        UiLabelContent {
            id: textCurrPDCntPerMin
            width: 114
            height: 60
            textValue: model.currPDCntPerMin
            anchors.left: labelCurrPDCntPerMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelCurrPDCntPerMin.verticalCenter
        }

        UiLabelSystem
        {
            id : labelPDCntPerMin

            height: 60; width: 125
            anchors.top: inputMinMax.bottom; anchors.topMargin: 10; anchors.left: textCurrPDCntPerMin.right; anchors.leftMargin: 10

            textValue: qsTr("· Avg PPM")
        }

        UiLabelContent {
            id: textPDCntPerMin
            width: 114
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

        UiLabelSystem
        {
            id: labelAdcValue
            x: 432
            width: 76
            height: 80
            anchors.verticalCenter: labelRuntimeGraph.verticalCenter
            anchors.right: textAdcValue.left
            anchors.rightMargin: 20

            textValue: qsTr("ADC")
        }

        UiLabelContent {
            id: textAdcValue
            x: 557
            width: 162
            height: 60
            textValue: model.adcValue
            anchors.right: graphRuntime.right
            anchors.rightMargin: 0
            anchors.verticalCenter: labelRuntimeGraph.verticalCenter
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


        Item {
            id: currentWeightBox
            height: 80
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            UiLabelSystem
            {
                id: labelTimingGraph
                width: 170
                height: 80
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                textValue: qsTr("· Timing graph")
            }

            UiLabelContent {
                id: textCurrentWeight
                width: 170
                height: 80
                textValue: (model.eventValue / 1000).toLocaleString(ViewManager.locale, 'f', 3) +  "g"
                anchors.left: labelTimingGraph.right
                anchors.leftMargin: 10
                anchors.verticalCenter: labelTimingGraph.verticalCenter
            }

            UiLabelSystem
            {
                id: labelTareWeight
                width: 160
                height: 80
                x : 377
                anchors.top: parent.top
                anchors.topMargin: 0

                textValue: qsTr("· Tare weight")
            }

            UiLabelContent {
                id: textTareWeight
                width: 190
                height: 80
                textValue: (model.tareWeight / 1000).toLocaleString(ViewManager.locale, 'f', 3) +  "g"
                anchors.left: labelTareWeight.right
                anchors.leftMargin: 10
                anchors.verticalCenter: labelTareWeight.verticalCenter
            }
        }

        UiInputNumber {
            id : inputFilterCoefficient
            height: 60; width: 350

            anchors.top: currentWeightBox.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 0;
            inputWidth: 130
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

        UiRadioBtn{
            id: checkGroupBuzzerOn
            height: 60; width: 322
            anchors.top: currentWeightBox.bottom; anchors.topMargin: 10; anchors.right: parent.right; anchors.rightMargin: 0

            textMargin : 10
            isHighlight: model.isEditAutoSetting
            isSelect: model.autoSetting === 1 ? true : false

            textValue : qsTr("Auto setting")

            onSignalEventClicked:
            {
                model.onCommandSetAutoSetting(model.autoSetting === 0 ? 1 : 0);
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
                    if(model.measureCueSign === 0)
                        return;

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

                    if(model.measureSection === 0)
                        return;

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
                 model.isEditMeasureSection       ||
                 model.isEditGraphPointCnt        ||
                 model.isEditAutoSetting          ||
                 model.isEditZeroDelayTime

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
        textValue: qsTr("Cancel")

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
