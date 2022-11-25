import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import FontManager 1.0
import ProductSettingItemModel 1.0

UiPanel {
    property ProductSettingItemModel itemModel : null
    property int  maxPPM     : 0
    property bool isViewMode : false
    property bool isEnableWC : true
    property bool isEnableMD : true
    property bool isAdmin    : false
    signal signalEventMoveDynamicCarib();
    signal signalEventAddCliecked();
    signal signalEventCancleCliecked();
    signal signalEventRemoveCliecked();

    id : panel

    width: 1023
    height: 947

    type : itemModel.seq === 0 ?  QmlEnumDef.PANEL_TYPE_UP_PANEL : QmlEnumDef.PANEL_TYPE_SELECT

    UiLabelContent{
        id: labelGeneral
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 20

        visible: itemModel.seq !== 0 || itemModel.isNew

        textValue: qsTr("General")
    }

    UiInputNumber{
        id: inputProductNumber
        width: 320
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: labelGeneral.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: itemModel.seq !== 0 || itemModel.isNew

        bgColor : panel.bgColor
        inputWidth: 150
        labelText: qsTr("· Product No")
        fillZero: "000"
        min : 1
        max : 999

        numberValue: itemModel.no
        isHighlight: itemModel.isEditNo

        onSignalChangeValue: {
            itemModel.onCommandSetNo(value)
        }
    }

    UiInputString{
        id: inputProductName
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: inputProductNumber.right
        anchors.leftMargin: 40
        anchors.verticalCenter: inputProductNumber.verticalCenter

        isDisable : panel.isViewMode
        visible: itemModel.seq !== 0 || itemModel.isNew

        bgColor : panel.bgColor
        labelText: qsTr("· Product Name")
        inputWidth: 420

        textValue: itemModel.name
        isHighlight: itemModel.isEditName

        onSignalChangeText: {
            itemModel.onCommandSetName(value)
        }
    }

    UiInputNumber {
        id: inputLength
        width: 320
        height: 60
        anchors.top: inputProductNumber.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 20
        anchors.left: parent.left

        isDisable : panel.isViewMode
        visible: itemModel.seq !== 0 || itemModel.isNew

        bgColor : panel.bgColor
        inputWidth: 150
        labelText: qsTr("· Length")
        postfix: "mm"
        min: 1
        max: 999

        numberValue: itemModel.length
        isHighlight: itemModel.isEditLength

        onSignalChangeValue: {
            itemModel.onCommandSetLength(value)
        }
    }

    UiInputNumber {
        id: inputSpeed
        width: 320
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: inputLength.right
        anchors.leftMargin: 40
        anchors.verticalCenter: inputLength.verticalCenter

        isDisable : panel.isViewMode
        visible: itemModel.seq !== 0 || itemModel.isNew

        bgColor : panel.bgColor
        inputWidth: 420
        labelText: qsTr("· Speed")
        postfix: "m/min"
        min: 1
        max: 999

        numberValue: itemModel.speed
        isHighlight: itemModel.isEditSpeed

        onSignalChangeValue: {
            itemModel.onCommandSetSpeed(value)
        }
    }

    Text{
        id:textMaxSpeed

        anchors.top: inputSpeed.bottom; anchors.topMargin: 7; anchors.right: inputSpeed.right
        font.pixelSize: 20; font.family: FontManager.nanumGothicName

        //color : itemModel.maxSpeed < itemModel.speed ? "#D9001B" : "#ACACAC"
        color : "#ACACAC"
        text: qsTr("Max PPM: ") + panel.maxPPM

        visible: itemModel.maxSpeed !== -1
    }

    UiLabelSystem{
        id : labelGroup
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputLength.bottom
        anchors.topMargin: 10

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
        textValue: qsTr("· Group")
    }

    UiInputNumber {
        id: inputGroupCount
        width: 292
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top : labelGroup.bottom
        anchors.topMargin: 0

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        inputWidth: 190
        labelText: qsTr("  Count")
        postfix: ""
        min: 0
        max: 999999

        numberValue: itemModel.groupCount
        isHighlight: itemModel.isEditGroupCount

        onSignalChangeValue: {
            itemModel.onCommandSetGroupCount(value)
        }
    }

    UiComboBox{
        id: comboGroupMotion
        height: 60
        width: 350
        z : 1
        anchors.left: inputGroupCount.right
        comboWidth: 260
        anchors.leftMargin: 20
        anchors.verticalCenter: inputGroupCount.verticalCenter

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        labelText : qsTr("Motion")

        listModel :comboGroupMotionOption
        selIdx: itemModel.groupMotion
        isHighlight: itemModel.isEditGroupMotion

        ListModel{
            id : comboGroupMotionOption

            ListElement {
                itemText : qsTr("None")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Stop")
                itemIdx : 1
            }
            ListElement {
                itemText : qsTr("RJ 01")
                itemIdx : 2
            }
            ListElement {
                itemText : qsTr("RJ 02")
                itemIdx : 3
            }
            ListElement {
                itemText : qsTr("RJ 03")
                itemIdx : 4
            }
            ListElement {
                itemText : qsTr("RJ 04")
                itemIdx : 5
            }
        }

        onSignalEventChangedSel: {
            itemModel.onCommandSetGroupMotion(itemIdx)
        }
    }

    UiRadioBtn{
        id: checkGroupLampOn
        height: 60
        width : 128
        anchors.left: comboGroupMotion.right
        anchors.leftMargin: 20
        anchors.verticalCenter: comboGroupMotion.verticalCenter

        textMargin : 10
        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
        isHighlight: itemModel.isEditGroupLamp
        isSelect: itemModel.groupLamp === 1 ? true : false

        textValue : qsTr("Lamp")

        onSignalEventClicked:
        {
            itemModel.onCommandSetGroupLamp(itemModel.groupLamp === 0 ? 1 : 0);
        }
    }

    UiRadioBtn{
        id: checkGroupBuzzerOn
        height: 60
        width : 153
        anchors.left: checkGroupLampOn.right
        anchors.leftMargin: 20
        anchors.verticalCenter: comboGroupMotion.verticalCenter

        textMargin : 10
        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
        isHighlight: itemModel.isEditGroupBuzzer
        isSelect: itemModel.groupBuzzer === 1 ? true : false

        textValue : qsTr("Buzzer")

        onSignalEventClicked:
        {
            itemModel.onCommandSetGroupBuzzer(itemModel.groupBuzzer === 0 ? 1 : 0);
        }
    }

    UiDivider{
        id: divider
        width: 2
        anchors.top: inputGroupCount.bottom
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left; anchors.leftMargin: 620

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
    }

    UiLabelContent {
        id: labelWeightChecker
        height: 30
        anchors.top: inputGroupCount.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 40
        anchors.rightMargin: 20

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        textValue: qsTr("Weight checker")
        anchors.left: parent.left
        anchors.right: divider.left

        UiRadioBtn{
            id: radioWCEtcErrorOn
            width : 120
            anchors.right: radioWCEtcErrorOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditWCEnableEtcError && isSelect
            isSelect: itemModel.wcEnableEtcError === 1 ? true : false

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCEnableEtcError(true);
            }
        }

        UiRadioBtn{
            id: radioWCEtcErrorOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0


            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditWCEnableEtcError && isSelect
            isSelect: itemModel.wcEnableEtcError === 0? true : false
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCEnableEtcError(false)
            }
        }
    }



    UiInputFloat{
        id: inputOver
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: labelWeightChecker.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        postfix : "g"
        isLocaleStyle : true
        min : 0
        max : 99999
        fixedN  : ViewManager.weightFixedN

        labelText : qsTr("· Over")
        inputWidth : width - 220

        realValue: itemModel.overWeight / 1000
        isHighlight: itemModel.isEditOverWeight

        onSignalChangeValue: {
            itemModel.onCommandSetOverWeight((value * 1000) + 0.5)
        }
    }

    /*
    UiInputFloat{
        id: inputOverWarning
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputOver.bottom
        anchors.topMargin: 10

        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

        labelText : qsTr("· Over warning")
        inputWidth : width - 220

        realValue: itemModel.overWarningWeight / 1000
        isHighlight: itemModel.isEditOverWarningWeight

        onSignalChangeValue: {
            itemModel.onCommandSetOverWarningWeight((value * 1000) + 0.5)
        }
    }
*/
    UiInputFloat{
        id: inputNormal
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputOver.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        postfix : "g"
        isLocaleStyle : true
        min : 0
        max : 99999
        fixedN  : ViewManager.weightFixedN

        labelText : qsTr("· Normal")
        inputWidth : width - 220

        realValue: itemModel.normalWeight / 1000
        isHighlight: itemModel.isEditNormalWeight


        onSignalChangeValue: {
            itemModel.onCommandSetNormalWeight((value * 1000) + 0.5)
        }
    }

    /*
    UiInputFloat{
        id: inputUnderWarning
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputNormal.bottom
        anchors.topMargin: 10

        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

        labelText : qsTr("· Under warning")
        inputWidth : width - 220

        realValue: itemModel.underWarningWeight / 1000
        isHighlight: itemModel.isEditUnderWarningWeight

        onSignalChangeValue: {
            itemModel.onCommandSetUnderWarningWeight((value * 1000) + 0.5)
        }
    }
*/
    UiInputFloat{
        id: inputUnder
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputNormal.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        postfix : "g"
        isLocaleStyle : true
        min : 0
        max : 99999
        fixedN  : ViewManager.weightFixedN

        labelText : qsTr("· Under")
        inputWidth : width - 220

        realValue: itemModel.underWeight / 1000
        isHighlight: itemModel.isEditUnderWeight

        onSignalChangeValue: {
            itemModel.onCommandSetUnderWeight((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id: inputTare
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputUnder.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        bgColor : panel.bgColor
        postfix : "g"
        isLocaleStyle : true
        min : 0
        max : 99999

        labelText : qsTr("· Tare")
        inputWidth : width - 220

        realValue: itemModel.tareWeight / 1000
        isHighlight: itemModel.isEditTareWeight
        fixedN  : ViewManager.weightFixedN

        onSignalChangeValue: {
            itemModel.onCommandSetTareWeight((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputDyniamicFactor
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputTare.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC && (panel.isAdmin === true || (itemModel.dynamicFactor === 10000000 && !itemModel.isNew))

        bgColor: panel.bgColor
        labelText : qsTr("· Dynamic factor")
        inputWidth : width - 220
        isHighlight: itemModel.isEditDynamicFactor
        fixedN : 7

        realValue: itemModel.dynamicFactor / 10000000.0

        onSignalChangeValue:
        {
            itemModel.onCommandSetDynamicFactor((value * 10000000) + 0.5)
        }

        UiLabelContent{
            height: 60; width: inputDyniamicFactor.inputWidth - 40
            anchors.right: parent.right
            anchors.rightMargin: 20
            visible: itemModel.dynamicFactor == 10000000
            horizontalAlignment : Text.AlignLeft
            textColor: "#FF0000"
            textValue: qsTr("is not set")
        }

        Rectangle{
            anchors.fill: parent
            color: "#00000000"

            visible:panel.isAdmin === false && itemModel.dynamicFactor === 10000000 && !itemModel.isNew

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    panel.signalEventMoveDynamicCarib()
                }
            }
        }
    }

    /*
    UiInputNumber {
        id: inputAverageN
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputTare.bottom
        anchors.topMargin: 10

        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        labelText : qsTr("· Average N")
        inputWidth : width - 220
        postfix: ""

        min: 1
        max: 99

        numberValue: itemModel.averageN
        isHighlight: itemModel.isEditAverageN

        onSignalChangeValue: {
            itemModel.onCommandSetAverageN(value)
        }
    }*/

    Item{
        id : inputWCDetectMode
        height: 150
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputDyniamicFactor.visible ? inputDyniamicFactor.bottom : inputTare.bottom
        anchors.topMargin: 10

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC

        UiLabelSystem{
            height: 60; width: parent.width - 220
            anchors.top: parent.top; anchors.left: parent.left

            textValue: qsTr("· NG motion")
        }

        UiRadioBtn{
            id: checkWCNGLampOn
            height: 60; width : 128; anchors.right: checkWCNGBuzzerOn.left; anchors.rightMargin: 20; anchors.verticalCenter: checkWCNGBuzzerOn.verticalCenter


            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditWCNGLamp
            isSelect: itemModel.wcNGLamp === 1 ? true : false

            textMargin : 10
            textValue : qsTr("Lamp")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCNGLamp(itemModel.wcNGLamp === 0 ? 1 : 0);
            }
        }

        UiRadioBtn{
            id: checkWCNGBuzzerOn
            height: 60; width : 153; anchors.top: parent.top; anchors.right: parent.right

            isDisable : panel.isViewMode
            visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
            isHighlight: itemModel.isEditWCNGBuzzer
            isSelect: itemModel.wcNGBuzzer === 1 ? true : false

            textMargin : 10
            textValue : qsTr("Buzzer")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCNGBuzzer(itemModel.wcNGBuzzer === 0 ? 1 : 0);
            }
        }

        RowLayout{
            height: 60; width: parent.width
            anchors.bottom: parent.bottom
            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                Text{
                    width: parent.width
                    anchors.bottom: comboWCOverMotion.top; anchors.bottomMargin: 5
                    font.pixelSize: 20; font.family: FontManager.nanumGothicName

                    color : "#ACACAC"; text: qsTr("- Over")
                }
                UiComboBox{
                    id: comboWCOverMotion
                    width: parent.width
                    anchors.bottom: parent.bottom

                    isDisable : panel.isViewMode
                    bgColor : panel.bgColor
                    isUpMode: true
                    z : 3

                    labelText : qsTr("· NG motion")

                    listModel :comboWCOverMotionOption
                    selIdx: itemModel.wcOverMotion
                    isHighlight: itemModel.isEditWCOverMotion

                    ListModel{
                        id : comboWCOverMotionOption

                        ListElement {
                            itemText : qsTr("None")
                            itemIdx : 0
                        }
                        ListElement {
                            itemText : qsTr("Stop")
                            itemIdx : 1
                        }
                        ListElement {
                            itemText : qsTr("RJ 01")
                            itemIdx : 2
                        }
                        ListElement {
                            itemText : qsTr("RJ 02")
                            itemIdx : 3
                        }
                        ListElement {
                            itemText : qsTr("RJ 03")
                            itemIdx : 4
                        }
                        ListElement {
                            itemText : qsTr("RJ 04")
                            itemIdx : 5
                        }
                    }

                    onSignalEventChangedSel: {
                        itemModel.onCommandSetWCOverMotion(itemIdx)
                    }

                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                Text{
                    width: parent.width
                    anchors.bottom: comboWCUnderMotion.top; anchors.bottomMargin: 5
                    font.pixelSize: 20; font.family: FontManager.nanumGothicName

                    color : "#ACACAC"; text: qsTr("- Under")
                }
                UiComboBox{
                    id: comboWCUnderMotion
                    width: parent.width;
                    anchors.bottom: parent.bottom

                    isDisable : panel.isViewMode
                    bgColor : panel.bgColor
                    isUpMode: true
                    z : 3

                    labelText : qsTr("· NG motion")

                    listModel :comboWCUnderMotionOption
                    selIdx: itemModel.wcUnderMotion
                    isHighlight: itemModel.isEditWCUnderMotion

                    ListModel{
                        id : comboWCUnderMotionOption

                        ListElement {
                            itemText : qsTr("None")
                            itemIdx : 0
                        }
                        ListElement {
                            itemText : qsTr("Stop")
                            itemIdx : 1
                        }
                        ListElement {
                            itemText : qsTr("RJ 01")
                            itemIdx : 2
                        }
                        ListElement {
                            itemText : qsTr("RJ 02")
                            itemIdx : 3
                        }
                        ListElement {
                            itemText : qsTr("RJ 03")
                            itemIdx : 4
                        }
                        ListElement {
                            itemText : qsTr("RJ 04")
                            itemIdx : 5
                        }
                    }

                    onSignalEventChangedSel: {
                        itemModel.onCommandSetWCUnderMotion(itemIdx)
                    }

                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                Text{
                    width: parent.width
                    anchors.bottom: comboWCEtcMotion.top; anchors.bottomMargin: 5
                    font.pixelSize: 20; font.family: FontManager.nanumGothicName

                    color : "#ACACAC"; text: qsTr("- Etc")
                }

                UiComboBox{
                    id: comboWCEtcMotion
                    width: parent.width
                    anchors.bottom: parent.bottom

                    isDisable : panel.isViewMode
                    bgColor : panel.bgColor
                    isUpMode: true
                    z : 3

                    labelText : qsTr("· NG motion")

                    listModel :comboWCEtcMotionOption
                    selIdx: itemModel.wcEtcMotion
                    isHighlight: itemModel.isEditWCEtcMotion

                    ListModel{
                        id : comboWCEtcMotionOption

                        ListElement {
                            itemText : qsTr("None")
                            itemIdx : 0
                        }
                        ListElement {
                            itemText : qsTr("Stop")
                            itemIdx : 1
                        }
                        ListElement {
                            itemText : qsTr("RJ 01")
                            itemIdx : 2
                        }
                        ListElement {
                            itemText : qsTr("RJ 02")
                            itemIdx : 3
                        }
                        ListElement {
                            itemText : qsTr("RJ 03")
                            itemIdx : 4
                        }
                        ListElement {
                            itemText : qsTr("RJ 04")
                            itemIdx : 5
                        }
                    }

                    onSignalEventChangedSel: {
                        itemModel.onCommandSetWCEtcMotion(itemIdx)
                    }
                }
            }
        }
    }



    /*
    UiLabelSystem{
        id : inputEnableEtcError
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: comboWCNGMotion.bottom
        anchors.topMargin: 10

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableWC
        textValue: qsTr("· Error detect")

        UiRadioBtn{
            id: radioWCEtcErrorOn
            width : 120
            anchors.right: radioWCEtcErrorOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditWCEnableEtcError && isSelect
            isSelect: itemModel.wcEnableEtcError === 1 ? true : false

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCEnableEtcError(true);
            }
        }

        UiRadioBtn{
            id: radioWCEtcErrorOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditWCEnableEtcError && isSelect
            isSelect: itemModel.wcEnableEtcError === 0? true : false
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                itemModel.onCommandSetWCEnableEtcError(false)
            }
        }
    }
*/
    UiLabelContent {
        id: labelMotor
        height: 30
        anchors.top: inputGroupCount.bottom
        anchors.topMargin: 40
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible:  (itemModel.seq !== 0 || itemModel.isNew) && panel.isAdmin === true

        textValue: qsTr("Motor")
    }

    UiInputFloat {
        id: inputMotorAcceleration
        width: 200
        height: 60
        anchors.right: isEnableWC? parent.right : divider.left
        anchors.rightMargin: 20
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20
        anchors.top: labelMotor.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && panel.isAdmin === true

        labelText : qsTr("· Motor acc")
        inputWidth: width - 180
        bgColor   : panel.bgColor
        postfix   : "s"
        min: 0
        max: 999

        realValue: itemModel.motorAcceleration / 1000
        isHighlight: itemModel.isEditMotorAcceleration

        onSignalChangeValue: {
            itemModel.onCommandSetMotorAcceleration((value * 1000) + 0.5)
        }
    }

    UiInputFloat {
        id: inputMotorDeceleration
        width: 200
        height: 60
        anchors.right: isEnableWC? parent.right : divider.left
        anchors.rightMargin: 20
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20
        anchors.top: inputMotorAcceleration.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && panel.isAdmin === true

        labelText : qsTr("· Motor dec")
        inputWidth: width - 180
        bgColor   : panel.bgColor
        postfix   : "s"
        min: 0
        max: 999

        realValue: itemModel.motorDeceleration / 1000
        isHighlight: itemModel.isEditMotorDeceleration

        onSignalChangeValue: {
            itemModel.onCommandSetMotorDeceleration((value * 1000) + 0.5)
        }
    }

    UiLabelContent {
        id: labelMetalDetector
        height: 30
        anchors.top: inputMotorDeceleration.visible === true ? inputMotorDeceleration.bottom : inputGroupCount.bottom
        anchors.topMargin: 40
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableMD

        textValue: qsTr("Metal detector")

        UiRadioBtn{
            id: radioMDOn
            width : 120
            anchors.right: radioMDOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isDisable : panel.isViewMode
            //isHighlight: itemModel.isEditMDSenstivity && isSelect
            isSelect: itemModel.mdSenstivity < 20000 ? true : false

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                itemModel.onCommandSetMDSenstivity(300);
            }
        }

        UiRadioBtn{
            id: radioMDOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0


            isDisable : panel.isViewMode
            isHighlight: itemModel.isEditMDSenstivity && isSelect && !(itemModel.mdSenstivity < 20000)
            isSelect: !(itemModel.mdSenstivity < 20000) ? true : false
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                itemModel.onCommandSetMDSenstivity(20000)
            }
        }
    }

    UiInputNumber {
        id: inputSenstivity
        height: 60
        anchors.right: isEnableWC? parent.right : divider.left
        anchors.rightMargin: 20
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20
        anchors.top: labelMetalDetector.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode || (itemModel.mdSenstivity >= 20000)
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableMD

        bgColor : panel.bgColor
        labelText : qsTr("· Senstivity")
        inputWidth : width - 180
        postfix: ""

        min: 1
        max: 9999

        numberValue: itemModel.mdSenstivity
        isHighlight: itemModel.isEditMDSenstivity && (itemModel.mdSenstivity < 20000)

        onSignalChangeValue: {
            itemModel.onCommandSetMDSenstivity(value)
        }
    }

    UiComboBox{
        id : comboMDNGMotion
        height: 60
        anchors.top: isEnableWC ? inputWCDetectMode.top : inputSenstivity.bottom
        anchors.topMargin: isEnableWC ? 0 : 10
        anchors.right: isEnableWC? parent.right : divider.left
        anchors.rightMargin: 20
        anchors.left: isEnableWC ? divider.right : parent.left
        anchors.leftMargin: 20

        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableMD

        isUpMode: true
        bgColor : panel.bgColor
        labelText : qsTr("· NG motion")
        comboWidth: width - 180

        listModel :comboMDNGMotionOption
        selIdx: itemModel.mdNGMotion
        isHighlight: itemModel.isEditMDNGMotion

        ListModel{
            id : comboMDNGMotionOption

            ListElement {
                itemText : qsTr("None")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Stop")
                itemIdx : 1
            }
            ListElement {
                itemText : qsTr("RJ 01")
                itemIdx : 2
            }
            ListElement {
                itemText : qsTr("RJ 02")
                itemIdx : 3
            }
            ListElement {
                itemText : qsTr("RJ 03")
                itemIdx : 4
            }
            ListElement {
                itemText : qsTr("RJ 04")
                itemIdx : 5
            }
        }

        onSignalEventChangedSel: {
            itemModel.onCommandSetMDNGMotion(itemIdx)
        }
    }

    UiRadioBtn{
        id: checkMDNGLampOn
        height: 60
        width : 128
        anchors.right: checkMDNGBuzzerOn.left
        anchors.rightMargin: 20
        anchors.verticalCenter: checkMDNGBuzzerOn.verticalCenter

        textMargin : 10
        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableMD
        isHighlight: itemModel.isEditMDNGLamp
        isSelect: itemModel.mdNGLamp === 1 ? true : false

        textValue : qsTr("Lamp")

        onSignalEventClicked:
        {
            itemModel.onCommandSetMDNGLamp(itemModel.mdNGLamp === 0 ? 1 : 0);
        }
    }

    UiRadioBtn{
        id: checkMDNGBuzzerOn
        height: 60
        width : 140
        anchors.top: comboMDNGMotion.bottom
        anchors.topMargin: 10
        anchors.right: isEnableWC? parent.right : divider.left
        anchors.rightMargin: 20

        textMargin : 10
        isDisable : panel.isViewMode
        visible: (itemModel.seq !== 0 || itemModel.isNew) && isEnableMD
        isHighlight: itemModel.isEditMDNGBuzzer
        isSelect: itemModel.mdNGBuzzer === 1 ? true : false

        textValue : qsTr("Buzzer")

        onSignalEventClicked:
        {
            itemModel.onCommandSetMDNGBuzzer(itemModel.mdNGBuzzer === 0 ? 1 : 0);
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

        visible: (itemModel.isEditNo                ||
                 itemModel.isEditName               ||
                 itemModel.isEditLength             ||
                 itemModel.isEditSpeed              ||
                 itemModel.isEditMotorAcceleration  ||
                 itemModel.isEditMotorDeceleration  ||
                 itemModel.isEditUnderWeight        ||
                 itemModel.isEditUnderWarningWeight ||
                 itemModel.isEditNormalWeight       ||
                 itemModel.isEditOverWarningWeight  ||
                 itemModel.isEditOverWeight         ||
                 itemModel.isEditTareWeight         ||
                 itemModel.isEditWCOverMotion       ||
                 itemModel.isEditWCUnderMotion      ||
                 itemModel.isEditWCEtcMotion        ||
                 itemModel.isEditWCEnableEtcError   ||
                 itemModel.isEditDynamicFactor      ||
                 itemModel.isEditMDSenstivity       ||
                 itemModel.isEditMDNGMotion         ||
                 itemModel.isEditGroupCount         ||
                 itemModel.isEditGroupMotion        ||
                 itemModel.isEditGroupLamp          ||
                 itemModel.isEditGroupBuzzer        ||
                 itemModel.isEditWCNGLamp           ||
                 itemModel.isEditWCNGBuzzer         ||
                 itemModel.isEditMDNGLamp           ||
                 itemModel.isEditMDNGBuzzer        ) &&
                 !panel.isViewMode

        type : QmlEnumDef.BUTTON_TYPE_BLUE
        textValue: qsTr("Apply")

        onSignalEventClicked:
        {
            panel.signalEventAddCliecked()
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
            panel.signalEventCancleCliecked()
        }
    }
    UiButtonConfirm {
        id : btnRemove
        width : 164
        height: 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : !btnApply.visible && (itemModel.seq !== 0) && !panel.isViewMode

        type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
        textValue: qsTr("Remove")
        textConfirmMsg: qsTr("Do you want to remove this product?")

        onSignalEventClicked:
        {
            panel.signalEventRemoveCliecked()
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
