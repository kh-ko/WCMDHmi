import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import ProductSettingItemModel 1.0

UiPanel {
    property ProductSettingItemModel itemModel : null
    property bool isViewMode : false
    signal signalEventAddCliecked();
    signal signalEventCancleCliecked();
    signal signalEventRemoveCliecked();

    id : panel

    width: 1023
    height: 947

    type : itemModel.isNew || itemModel.isRemoved ?  EnumDefine.PANEL_TYPE_UP_PANEL : EnumDefine.PANEL_TYPE_SELECT

    UiLabelContent{
        id: labelGeneral
        height: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: btnApply.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        visible: !itemModel.isRemoved

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
        visible: !itemModel.isRemoved

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
        visible: !itemModel.isRemoved

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
        visible: !itemModel.isRemoved

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
        anchors.right: inputMotorAcceleration.left
        anchors.rightMargin: 20
        anchors.left: inputLength.right
        anchors.leftMargin: 40
        anchors.verticalCenter: inputLength.verticalCenter

        isDisable : panel.isViewMode
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        inputWidth: 200
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

    UiInputFloat {
        id: inputMotorAcceleration
        width: 200
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: inputLength.verticalCenter

        isDisable : panel.isViewMode
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix: "s"
        min: 0
        max: 999

        realValue: itemModel.motorAcceleration / 1000
        isHighlight: itemModel.isEditMotorAcceleration

        onSignalChangeValue: {
            itemModel.onCommandSetMotorAcceleration((value * 1000) + 0.5)
        }
    }

    UiDivider{
        id: divider
        width: 2
        anchors.top: inputSpeed.bottom
        anchors.topMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        visible: !itemModel.isRemoved
    }

    UiLabelContent {
        id: labelWeightChecker
        height: 30
        anchors.top: inputLength.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 40
        anchors.rightMargin: 20

        visible: !itemModel.isRemoved

        textValue: qsTr("Weight checker")
        anchors.left: parent.left
        anchors.right: divider.left
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
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

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
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

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
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

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
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        postfix : "g"
        fixedN  : 1
        isLocaleStyle : true
        min : 0
        max : 99999

        labelText : qsTr("· Tare")
        inputWidth : width - 220

        realValue: itemModel.tareWeight / 1000
        isHighlight: itemModel.isEditTareWeight

        onSignalChangeValue: {
            itemModel.onCommandSetTareWeight((value * 1000) + 0.5)
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

    UiComboBox{
        id: comboWCNGMotion
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: inputTare.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: !itemModel.isRemoved

        isUpMode: true
        bgColor : panel.bgColor
        labelText : qsTr("· NG motion")
        comboWidth: width - 220

        listModel :comboWCNGMotionOption
        selIdx: itemModel.wcNGMotion
        isHighlight: itemModel.isEditWCNGMotion

        ListModel{
            id : comboWCNGMotionOption

            ListElement {
                itemText : qsTr("None")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Stop")
                itemIdx : 1
            }
            ListElement {
                itemText : qsTr("Rejector 01")
                itemIdx : 2
            }
            ListElement {
                itemText : qsTr("Rejector 02")
                itemIdx : 3
            }
        }

        onSignalEventChangedSel: {
            itemModel.onCommandSetWCNGMotion(itemIdx)
        }
    }


    UiLabelContent {
        id: labelMetalDetector
        height: 30
        anchors.top: inputSpeed.bottom
        anchors.topMargin: 40
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.left: divider.right

        visible: !itemModel.isRemoved

        textValue: qsTr("Metal detector")
    }

    UiInputNumber {
        id: inputSenstivity
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: divider.right
        anchors.leftMargin: 20
        anchors.top: labelMetalDetector.bottom
        anchors.topMargin: 10

        isDisable : panel.isViewMode
        visible: !itemModel.isRemoved

        bgColor : panel.bgColor
        labelText : qsTr("· Senstivity")
        inputWidth : width - 220
        postfix: ""

        min: 1
        max: 9999

        numberValue: itemModel.mdSenstivity
        isHighlight: itemModel.isEditMDSenstivity

        onSignalChangeValue: {
            itemModel.onCommandSetMDSenstivity(value)
        }
    }

    UiComboBox{
        height: 60
        anchors.verticalCenter: comboWCNGMotion.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: divider.right
        anchors.leftMargin: 20

        isDisable : panel.isViewMode
        visible: !itemModel.isRemoved

        isUpMode: true
        bgColor : panel.bgColor
        labelText : qsTr("· NG motion")
        comboWidth: width - 220

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
                itemText : qsTr("Rejector 01")
                itemIdx : 2
            }
            ListElement {
                itemText : qsTr("Rejector 02")
                itemIdx : 3
            }
        }

        onSignalEventChangedSel: {
            itemModel.onCommandSetMDNGMotion(itemIdx)
        }
    }

    UiButtonAni{
        id : btnApply
        width : 164
        height : 80
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: btnCancle.left
        anchors.rightMargin: 20

        isPlay : true

        visible: (itemModel.isEditNo                 ||
                 itemModel.isEditName               ||
                 itemModel.isEditLength             ||
                 itemModel.isEditSpeed              ||
                 itemModel.isEditMotorAcceleration  ||
                 itemModel.isEditUnderWeight        ||
                 itemModel.isEditUnderWarningWeight ||
                 itemModel.isEditNormalWeight       ||
                 itemModel.isEditOverWarningWeight  ||
                 itemModel.isEditOverWeight         ||
                 itemModel.isEditTareWeight         ||
                 itemModel.isEditWCNGMotion         ||
                 itemModel.isEditAverageN           ||
                 itemModel.isEditMDSenstivity       ||
                 itemModel.isEditMDNGMotion)        &&
                 !panel.isViewMode

        type : EnumDefine.BUTTON_TYPE_BLUE
        textValue: qsTr("Apply")

        onSignalEventClicked:
        {
            panel.signalEventAddCliecked()
        }

    }

    UiButton{
        id : btnCancle
        width : 164
        height : 80
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : btnApply.visible

        type : EnumDefine.BUTTON_TYPE_UP_PANEL
        textValue: qsTr("Cancle")

        onSignalEventClicked:
        {
            panel.signalEventCancleCliecked()
        }
    }
    UiButtonConfirm {
        id : btnRemove
        width : 164
        height: 80
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : !btnApply.visible && !itemModel.isRemoved && !panel.isViewMode

        type : EnumDefine.BUTTON_TYPE_UP_PANEL
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
    D{i:0;formeditorZoom:0.8999999761581421}D{i:31;anchors_height:80}
}
##^##*/
