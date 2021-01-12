import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelDeviceSettingModel 1.0

UiPanel {

    property bool isAdmin : true
    id: panel

    width : 1518
    height : 997

    PanelDeviceSettingModel
    {
        id : settingModel

        onSignalResultSaveDeviceSetting: {
            if(isSuss == false && isPwdError)
            {
                ViewManager.toast.show(qsTr("Please check password."))
            }
            else if(isSuss == false)
            {
                ViewManager.toast.show(qsTr("Unknow error."))
            }
            else
            {
                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
        }
    }

    UiLabelContent{
        id: labelGeneral
        height: 60
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20

        textValue: qsTr("General")
    }

    UiComboBox {
        id: comboLanguage
        height: 60
        z: 1
        anchors.topMargin: 10
        anchors.top: labelGeneral.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditLanguage
        bgColor: panel.bgColor
        labelText : qsTr("· Lanugage")
        comboWidth : 230
        selIdx: settingModel.language
        listModel: comboFilterOption
        ListModel {
            id : comboFilterOption
            ListElement {
                itemText : "ENG"
                itemIdx : 0
            }
            ListElement {
                itemText : "한국어"
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            settingModel.onCommandSetLanguage(itemIdx)
        }
    }

    UiInputPassword{
        id : inputPassword
        height: 60
        anchors.topMargin: 10
        anchors.top: comboLanguage.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditPassword
        bgColor: panel.bgColor
        labelText : qsTr("· PWD")
        inputWidth: 230

        textValue: settingModel.password

        onSignalChangeText: {
            settingModel.onCommandSetPassword(value)
        }
    }

    UiInputPassword{
        id : inputNewPassword
        height: 60
        anchors.topMargin: 10
        anchors.top: inputPassword.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditNewPassword
        bgColor: panel.bgColor
        labelText : qsTr("· New PWD")
        inputWidth: 230

        textValue: settingModel.newPassword

        onSignalChangeText: {
            settingModel.onCommandSetNewPassword(value)
        }
    }

    UiInputPassword{
        id : inputConfirmPassword
        height: 60
        anchors.topMargin: 10
        anchors.top: inputNewPassword.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditConfirmPassword
        bgColor: panel.bgColor
        labelText : qsTr("· Confirm PWD")
        inputWidth: 230

        textValue: settingModel.confirmPassword

        onSignalChangeText: {
            settingModel.onCommandSetConfirmPassword(value)
        }
    }

    UiLabelSystem{
        id : inputDayMode
        height: 60
        anchors.topMargin: 10
        anchors.top: inputConfirmPassword.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        textValue: qsTr("· Day mode")

        UiRadioBtn{
            id: radiioDayModeOn
            width : 120
            anchors.right: radiioDayModeOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditIsDayMode && isSelect
            isSelect: settingModel.isDayMode

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                settingModel.onCommandSetIsDayMode(true);
            }
        }

        UiRadioBtn{
            id: radiioDayModeOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditIsDayMode && isSelect
            isSelect: !settingModel.isDayMode
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                settingModel.onCommandSetIsDayMode(false)
            }
        }
    }

    UiLabelSystem{
        id : inputDebugMode
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDayMode.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Debug mode")

        UiRadioBtn{
            id: radiioDebugModeOn
            width : 120
            anchors.right: radioDebugModeOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditIsDebugMode && isSelect
            isSelect: settingModel.isDebugMode

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                settingModel.onCommandSetIsDebugMode(true);
            }
        }

        UiRadioBtn{
            id: radioDebugModeOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditIsDebugMode && isSelect
            isSelect: !settingModel.isDebugMode
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                settingModel.onCommandSetIsDebugMode(false)
            }
        }
    }

    UiInputFloat{
        id : inputLamp
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDebugMode.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditLampTime
        bgColor: panel.bgColor
        labelText : qsTr("· Lamp")
        postfix: "s"
        inputWidth: 230

        realValue: settingModel.lampTime / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetLampTime((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputBuzzer
        height: 60
        anchors.topMargin: 10
        anchors.top: inputLamp.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        isHighlight: settingModel.isEditBuzzerTime
        bgColor: panel.bgColor
        labelText : qsTr("· Buzzer")
        postfix: "s"
        inputWidth: 230

        realValue: settingModel.buzzerTime / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetBuzzerTime((value * 1000) + 0.5)
        }
    }


    UiInputFloat{
        id : inputSpeedConverter
        height: 60
        anchors.topMargin: 10
        anchors.top: inputBuzzer.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSpeedConverter
        fixedN: 4
        bgColor: panel.bgColor
        labelText : qsTr("· m/min → Hz")
        inputWidth: 230

        realValue: settingModel.speedConverter / 10000.0

        onSignalChangeValue: {
            settingModel.onCommandSetSpeedConverter((value * 10000) + 0.5)
        }
    }

    UiComboBox {
        id: comboMotorDirection
        height: 60
        z: 1
        anchors.topMargin: 10
        anchors.top: inputSpeedConverter.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditMotorDirection
        isUpMode : true

        labelText: qsTr("· Transfer")
        bgColor: panel.bgColor
        comboWidth : 254
        selIdx: settingModel.motorDirection
        listModel: comboDirectionOption
        ListModel {
            id : comboDirectionOption
            ListElement {
                itemText : qsTr("Left ← right")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Left → right")
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            settingModel.onCommandSetMotorDirection(itemIdx)
        }
    }

    UiComboBox {
        id: comboMotorType
        height: 60
        z: 1
        anchors.top: comboMotorDirection.bottom
        anchors.topMargin: 10
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditMotorType
        isUpMode : true

        labelText: qsTr("· Motor type")
        bgColor: panel.bgColor
        comboWidth : 254
        selIdx: settingModel.motorType
        listModel: comboMotorTypeOption
        ListModel {
            id : comboMotorTypeOption
            ListElement {
                itemText : qsTr("3-phase")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("BLDC")
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            settingModel.onCommandSetMotorType(itemIdx)
        }
    }

    UiLabelSystem{
        id : labelMotorRPMRatio
        height: 60
        anchors.topMargin: 10
        anchors.top: comboMotorType.bottom
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Motor RPM ratio ( MD : WC : RJ)")
    }

    RowLayout{
        height: 60
        anchors.topMargin: 0
        anchors.top: labelMotorRPMRatio.bottom
        spacing: 10
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: dividerGeneralWeightChecker.left
        anchors.rightMargin: 20

        UiInputFloat{
            id : inputMotorMDRatio
            height: 60

            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: panel.isAdmin
            isHighlight: settingModel.isEditMotorMDRatio
            fixedN: 2
            bgColor: panel.bgColor

            realValue: settingModel.motorMDRatio / 100

            onSignalChangeValue: {
                settingModel.onCommandSetMotorMDRatio((value * 100))
            }
        }

        UiInputFloat{
            id : inputMotorWCRatio
            height: 60

            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: panel.isAdmin
            isHighlight: settingModel.isEditMotorWCRatio
            fixedN: 2
            bgColor: panel.bgColor

            realValue: settingModel.motorWCRatio / 100

            onSignalChangeValue: {
                settingModel.onCommandSetMotorWCRatio((value * 100))
            }
        }

        UiInputFloat{
            id : inputMotorRJRatio
            height: 60

            Layout.preferredHeight: 1
            Layout.preferredWidth: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: panel.isAdmin
            isHighlight: settingModel.isEditMotorRJRatio
            fixedN: 2
            bgColor: panel.bgColor

            realValue: settingModel.motorRJRatio / 100

            onSignalChangeValue: {
                settingModel.onCommandSetMotorRJRatio((value * 100))
            }
        }
    }

    UiDivider
    {
        id : dividerGeneralWeightChecker
        x : parent.width * 0.33
        width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 120
    }

    /*
    UiInputNumber{
        id : inputSensorLength
        height: 60
        anchors.topMargin: 10
        anchors.top: labelWeightChecker.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSensorLength
        bgColor: panel.bgColor
        labelText : qsTr("· Sensor length")
        postfix: "mm"
        inputWidth: 170

        numberValue: settingModel.sensorLength

        onSignalChangeValue: {
            settingModel.onCommandSetSensorLength(value)
        }
    }
*/
    /*
    UiInputNumber{
        id : inputDistToRejector
        height: 60
        anchors.topMargin: 10
        anchors.top: inputSensorLength.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditDistanceToRejector
        bgColor: panel.bgColor
        labelText : qsTr("· Distance to rejector")
        postfix: "mm"
        inputWidth: 170

        numberValue: settingModel.distanceToRejector

        onSignalChangeValue: {
            settingModel.onCommandSetDistanceToRejector(value)
        }
    }
*/

    UiLabelSystem{
        id : labelSorter01
        height: 60
        width : 92
        anchors.topMargin: 10
        anchors.top: btnApply.bottom
        anchors.left: dividerGeneralWeightChecker.right
        anchors.leftMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· St. 01")
    }

    UiInputFloat{
        id : inputSorter01RunTimeRatio
        height: 60
        width : 170

        anchors.leftMargin: 10
        anchors.left: labelSorter01.right
        anchors.verticalCenter: labelSorter01.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter01RunTimeRatio
        bgColor: panel.bgColor
        postfix: "%"

        realValue: settingModel.mSorter01RunTimeRatio / 10.0

        onSignalChangeValue: {
            settingModel.onCommandSetSorter01RunTimeRatio((value * 10))
        }
    }

    UiInputNumber{
        id : inputSorter01OpenTime
        height: 60
        width : 172
        anchors.leftMargin: 15
        anchors.left: inputSorter01RunTimeRatio.right
        anchors.verticalCenter: inputSorter01RunTimeRatio.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter01OpenTime
        bgColor: panel.bgColor
        postfix: "ms"

        numberValue: settingModel.mSorter01OpenTime

        onSignalChangeValue: {
            settingModel.onCommandSetSorter01OpenTime(value)
        }
    }

    UiLabelSystem{
        id : labelSorter02
        height: 60
        width : 92
        anchors.topMargin: 10
        anchors.top: labelSorter01.bottom
        anchors.left: dividerGeneralWeightChecker.right
        anchors.leftMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· St. 02")
    }

    UiInputFloat{
        id : inputSorter02RunTimeRatio
        height: 60
        width : 170

        anchors.leftMargin: 10
        anchors.left: labelSorter02.right
        anchors.verticalCenter: labelSorter02.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter02RunTimeRatio
        bgColor: panel.bgColor
        postfix: "%"

        realValue: settingModel.mSorter02RunTimeRatio / 10.0

        onSignalChangeValue: {
            settingModel.onCommandSetSorter02RunTimeRatio((value * 10))
        }
    }

    UiInputNumber{
        id : inputSorter02OpenTime
        height: 60
        width : 172
        anchors.leftMargin: 15
        anchors.left: inputSorter02RunTimeRatio.right
        anchors.verticalCenter: inputSorter02RunTimeRatio.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter02OpenTime
        bgColor: panel.bgColor
        postfix: "ms"

        numberValue: settingModel.mSorter02OpenTime

        onSignalChangeValue: {
            settingModel.onCommandSetSorter02OpenTime(value)
        }
    }
    UiLabelSystem{
        id : labelSorter03
        height: 60
        width : 92
        anchors.topMargin: 10
        anchors.top: labelSorter02.bottom
        anchors.left: dividerGeneralWeightChecker.right
        anchors.leftMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· St. 03")
    }

    UiInputFloat{
        id : inputSorter03RunTimeRatio
        height: 60
        width : 170

        anchors.leftMargin: 10
        anchors.left: labelSorter03.right
        anchors.verticalCenter: labelSorter03.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter03RunTimeRatio
        bgColor: panel.bgColor
        postfix: "%"

        realValue: settingModel.mSorter03RunTimeRatio / 10.0

        onSignalChangeValue: {
            settingModel.onCommandSetSorter03RunTimeRatio((value * 10))
        }
    }

    UiInputNumber{
        id : inputSorter03OpenTime
        height: 60
        width : 172
        anchors.leftMargin: 15
        anchors.left: inputSorter03RunTimeRatio.right
        anchors.verticalCenter: inputSorter03RunTimeRatio.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter03OpenTime
        bgColor: panel.bgColor
        postfix: "ms"

        numberValue: settingModel.mSorter03OpenTime

        onSignalChangeValue: {
            settingModel.onCommandSetSorter03OpenTime(value)
        }
    }
    UiLabelSystem{
        id : labelSorter04
        height: 60
        width : 92
        anchors.topMargin: 10
        anchors.top: labelSorter03.bottom
        anchors.left: dividerGeneralWeightChecker.right
        anchors.leftMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· St. 04")
    }

    UiInputFloat{
        id : inputSorter04RunTimeRatio
        height: 60
        width : 170

        anchors.leftMargin: 10
        anchors.left: labelSorter04.right
        anchors.verticalCenter: labelSorter04.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter04RunTimeRatio
        bgColor: panel.bgColor
        postfix: "%"

        realValue: settingModel.mSorter04RunTimeRatio / 10.0

        onSignalChangeValue: {
            settingModel.onCommandSetSorter04RunTimeRatio((value * 10) + 0.5)
        }
    }

    UiInputNumber{
        id : inputSorter04OpenTime
        height: 60
        width : 172
        anchors.leftMargin: 15
        anchors.left: inputSorter04RunTimeRatio.right
        anchors.verticalCenter: inputSorter04RunTimeRatio.verticalCenter

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSorter04OpenTime
        bgColor: panel.bgColor
        postfix: "ms"

        numberValue: settingModel.mSorter04OpenTime

        onSignalChangeValue: {
            settingModel.onCommandSetSorter04OpenTime(value)
        }
    }

    UiLabelContent{
        id: labelWeightChecker
        height: 60
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.top: labelSorter04.bottom
        anchors.topMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        textValue: settingModel.isEnableWC ? qsTr("Weight checker") : ""
    }


    UiInputFloat{
        id : inputDisplayStability
        height: 60
        anchors.topMargin: 0
        anchors.top: labelWeightChecker.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditDisplayStability
        bgColor: panel.bgColor
        labelText : qsTr("· Display stability")
        postfix: "%"
        inputWidth: 170

        realValue: settingModel.displayStability / 10.0

        onSignalChangeValue: {
            settingModel.onCommandSetDisplayStability((value * 10) + 0.5)
        }
    }

    UiInputFloat{
        id : inputMeasureCueSign
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDisplayStability.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditMeasureCueSign
        bgColor: panel.bgColor
        labelText : qsTr("· Measure cue sign")
        postfix: "s"
        inputWidth: 170
        fixedN: 2
        realValue: settingModel.measureCueSign / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetMeasureCueSign((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputMinStaticWeight
        height: 60
        anchors.topMargin: 10
        anchors.top: inputMeasureCueSign.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditMinStaticWeight
        bgColor: panel.bgColor
        labelText : qsTr("· Min static weight")
        postfix: "g"
        inputWidth: 170

        realValue: settingModel.minStaticWeight / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetMinStaticWeight((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputMinDynamicWeight
        height: 60
        anchors.topMargin: 10
        anchors.top: inputMinStaticWeight.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditMinDynamicWeight
        bgColor: panel.bgColor
        labelText : qsTr("· Min dynamic weight")
        postfix: "g"
        inputWidth: 170

        realValue: settingModel.minDynamicWeight / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetMinDynamicWeight((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputScaler
        height: 60
        anchors.topMargin: 10
        anchors.top: inputMinDynamicWeight.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditScaler
        bgColor: panel.bgColor
        labelText : qsTr("· Display unit")
        postfix: "g"
        inputWidth: 170

        realValue: settingModel.scaler / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetScaler((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputStaticFactor
        height: 60
        anchors.topMargin: 10
        anchors.top: inputScaler.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditStaticFactor
        fixedN : 7
        bgColor: panel.bgColor
        labelText : qsTr("· Static factor")
        inputWidth: 200

        realValue: settingModel.staticFactor / 10000000.0

        onSignalChangeValue: {
            settingModel.onCommandSetStaticFactor((value * 10000000) + 0.5)
        }
    }

    /*
    UiInputFloat{
        id : inputSDyniamicFactor
        height: 60
        anchors.topMargin: 10
        anchors.top: inputStaticFactor.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        isHighlight: settingModel.isEditDynamicFactor
        fixedN : 7
        bgColor: panel.bgColor
        labelText : qsTr("· Dynamic factor")
        inputWidth: 200

        realValue: settingModel.dynamicFactor / 10000000.0

        onSignalChangeValue:
        {
            settingModel.onCommandSetDynamicFactor((value * 10000000) + 0.5)
        }
    }
*/
    /*
    UiInputFloat{
        id : inputStandardWeight
        height: 60
        anchors.topMargin: 10
        anchors.top: panel.isAdmin? inputSDyniamicFactor.bottom : inputScaler.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        //visible: panel.isAdmin
        isHighlight: settingModel.isEditStandardWeight
        bgColor: panel.bgColor
        labelText : qsTr("· Standard weight")
        postfix: "g"
        inputWidth: 170

        realValue: settingModel.standardWeight / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetStandardWeight((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputRefWeight
        height: 60
        anchors.topMargin: 10
        anchors.top: inputStandardWeight.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        //visible: panel.isAdmin
        isHighlight: settingModel.isEditRefWeight
        bgColor: panel.bgColor
        labelText : qsTr("· Ref weight")
        postfix: "g"
        inputWidth: 170

        realValue: settingModel.refWeight / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetRefWeight((value * 1000) + 0.5)
        }
    }
*/
    UiLabelSystem{
        id : inputWeightPhotoOn
        height: 60
        anchors.topMargin: 10
        anchors.top: inputStaticFactor.bottom
        anchors.leftMargin: 20
        anchors.left: dividerGeneralWeightChecker.right
        anchors.right: dividerWCMD.left
        anchors.rightMargin: 20

        visible: panel.isAdmin && settingModel.isEnableWC
        textValue: qsTr("· Photo mode")

        UiRadioBtn{
            id: radioWeightPhotoModeOn
            width : 120
            anchors.right: radioWeightPhotoModeOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditWCPhotoOn && isSelect
            isSelect: settingModel.wcPhotoOn

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                settingModel.onCommandSetWCPhotoOn(true);
            }
        }

        UiRadioBtn{
            id: radioWeightPhotoModeOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditWCPhotoOn && isSelect
            isSelect: !settingModel.wcPhotoOn
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                settingModel.onCommandSetWCPhotoOn(false)
            }
        }
    }

    UiDivider
    {
        id : dividerWCMD
        x : parent.width * 0.66
        width: 2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 120
    }

    UiLabelContent{
        id: labelWeMetalDetector
        height: 60
        anchors.left: dividerWCMD.right
        anchors.right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.top: btnApply.bottom
        anchors.topMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("Metal detecotor")
    }

    UiLabelSystem{
        id : labelSensorMode
        height: 60
        anchors.topMargin: 10
        anchors.top: labelWeMetalDetector.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Sensor mode")
    }

    UiComboBox {
        id: comboSensorMode
        height: 60
        z: 1
        anchors.topMargin: 10
        anchors.top: labelSensorMode.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditMode
        bgColor: panel.bgColor
        selIdx: settingModel.mode
        listModel: comboModeOption
        ListModel {
            id : comboModeOption
            ListElement {
                itemText : qsTr("Independent")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("noise reduction")
                itemIdx : 1
            }
           // ListElement {
           //     itemText : "noise reduction"
           //     itemIdx : 2
           // }
        }

        onSignalEventChangedSel: {
            settingModel.onCommandSetMode(itemIdx)
        }
    }

    /*
    UiInputNumber{
        id : inputDistBtwSensor
        height: 60
        anchors.topMargin: 10
        anchors.top: comboSensorMode.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditDistanceBtwSensor
        bgColor: panel.bgColor
        labelText : qsTr("· Distance btw sensor")
        postfix: "mm"
        inputWidth: 170

        numberValue: settingModel.distanceBtwSensor

        onSignalChangeValue: {
            settingModel.onCommandSetDistanceBtwSensor(value)
        }
    }
    */

    UiInputFloat{
        id : inputDetectDetectTime
        height: 60
        anchors.topMargin: 10
        anchors.top: comboSensorMode.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditDetectDetectTime
        bgColor: panel.bgColor
        labelText : qsTr("· Detect-Detect time")
        postfix: "s"
        inputWidth: 170

        realValue: settingModel.detectDetectTime / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetDetectDetectTime((value * 1000) + 0.5)
        }
    }

    UiInputFloat{
        id : inputRunDetectTime
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDetectDetectTime.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditRunDetectTime
        bgColor: panel.bgColor
        labelText : qsTr("· Run-Detect time")
        postfix: "s"
        inputWidth: 170

        realValue: settingModel.runDetectTime / 1000.0

        onSignalChangeValue: {
            settingModel.onCommandSetRunDetectTime((value * 1000) + 0.5)
        }
    }

    UiInputNumber{
        id : inputSignalDelayTime
        height: 60
        anchors.topMargin: 10
        anchors.top: inputRunDetectTime.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSignalDelayTime
        bgColor: panel.bgColor
        labelText : qsTr("· Signal delay time")
        postfix: "ms"
        inputWidth: 170

        numberValue: settingModel.signalDelayTime

        onSignalChangeValue: {
            settingModel.onCommandSetSignalDelayTime(value)
        }
    }


    UiLabelSystem{
        id : inputMetalPhotoOn
        height: 60
        anchors.topMargin: 10
        anchors.top: inputSignalDelayTime.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Photo mode")

        UiRadioBtn{
            id: radioMetalPhotoModeOn
            width : 120
            anchors.right: radioMetalPhotoModeOff.left
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditMDPhotoOn && isSelect
            isSelect: settingModel.mdPhotoOn

            textValue : qsTr("ON")

            onSignalEventClicked:
            {
                settingModel.onCommandSetMDPhotoOn(true);
            }
        }

        UiRadioBtn{
            id: radioMetalPhotoModeOff
            width : 120
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            isHighlight: settingModel.isEditMDPhotoOn && isSelect
            isSelect: !settingModel.mdPhotoOn
            textValue : qsTr("OFF")

            onSignalEventClicked:
            {
                settingModel.onCommandSetMDPhotoOn(false)
            }
        }
    }

    UiInputNumber{
        id : inputSensorCnt
        height: 60
        anchors.topMargin: 10
        anchors.top: inputMetalPhotoOn.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSensorCnt
        bgColor: panel.bgColor
        labelText : qsTr("· Sensor count")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.sensorCnt

        onSignalChangeValue: {
            settingModel.onCommandSetSensorCnt(value)
        }
    }

    UiInputNumber{
        id : inputSens01
        height: 50
        anchors.topMargin: 10
        anchors.top: inputSensorCnt.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSimpleSens01
        bgColor: panel.bgColor
        labelText : qsTr("· Metal Senstivity 01")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.simpleSens01

        onSignalChangeValue: {
            settingModel.onCommandSetSimpleSens01(value)
        }
    }

    UiInputNumber{
        id : inputSens02
        height: 50
        anchors.topMargin: 10
        anchors.top: inputSens01.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSimpleSens02
        bgColor: panel.bgColor
        labelText : qsTr("· Metal Senstivity 02")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.simpleSens02

        onSignalChangeValue: {
            settingModel.onCommandSetSimpleSens02(value)
        }
    }

    UiInputNumber{
        id : inputSens03
        height: 50
        anchors.topMargin: 10
        anchors.top: inputSens02.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSimpleSens03
        bgColor: panel.bgColor
        labelText : qsTr("· Metal Senstivity 03")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.simpleSens03

        onSignalChangeValue: {
            settingModel.onCommandSetSimpleSens03(value)
        }
    }

    UiInputNumber{
        id : inputSens04
        height: 50
        anchors.topMargin: 10
        anchors.top: inputSens03.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSimpleSens04
        bgColor: panel.bgColor
        labelText : qsTr("· Metal Senstivity 04")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.simpleSens04

        onSignalChangeValue: {
            settingModel.onCommandSetSimpleSens04(value)
        }
    }

    UiInputNumber{
        id : inputSens05
        height: 50
        anchors.topMargin: 10
        anchors.top: inputSens04.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditSimpleSens05
        bgColor: panel.bgColor
        labelText : qsTr("· Metal Senstivity 05")
        postfix: ""
        inputWidth: 170

        numberValue: settingModel.simpleSens05

        onSignalChangeValue: {
            settingModel.onCommandSetSimpleSens05(value)
        }
    }
/*
    UiLabelSystem{
        id : labelDistWeightChecker
        height: 60
        anchors.topMargin: 10
        anchors.top: inputSignalDelayTime.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Distance to weight checker")
    }

    UiInputNumber{
        id : inputDistWeightChecker
        height: 60
        anchors.topMargin: 0
        anchors.top: labelDistWeightChecker.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditDistanceToWeightChecker
        labelText: " "
        postfix: "mm"
        inputWidth: 170
        bgColor: panel.bgColor

        numberValue: settingModel.distanceToWeightChecker

        onSignalChangeValue:
        {
            settingModel.onCommandSetDistanceToWeightChecker(value)
        }
    }

    UiLabelSystem{
        id : labelDistBtwPhotoToSensor
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDistWeightChecker.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("· Distance btw photo to sensor")
    }

    UiInputNumber{
        id : inputDistBtwPhotoToSensor
        height: 60
        anchors.topMargin: 0
        anchors.top: labelDistBtwPhotoToSensor.bottom
        anchors.left: dividerWCMD.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: panel.isAdmin
        isHighlight: settingModel.isEditDistancePhotoToSensor
        bgColor: panel.bgColor
        labelText : " "
        postfix: "mm"
        inputWidth: 170

        numberValue: settingModel.distancePhotoToSensor

        onSignalChangeValue: {
            settingModel.onCommandSetDistancePhotoToSensor(value)
        }
    }



    UiButton{
        id : btnHMIExit
        width: 164
        height: 80
        anchors.verticalCenter: btnFactoryReset.verticalCenter
        anchors.right: btnHMIOut.left
        anchors.rightMargin: 20

        textValue: qsTr("HMI exit")

        onSignalEventClicked: {
            Qt.quit()
        }
    }*/

    UiButton{
        id : btnHMIOut
        width: 164
        height: 80
        anchors.verticalCenter: btnFactoryReset.verticalCenter
        anchors.right: btnFactoryReset.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("HMI out")

        onSignalEventClicked: {
            ViewManager.minimizeWindow()
        }
    }

    UiButtonConfirm{
        id : btnFactoryReset
        width: 164
        height: 80
        anchors.verticalCenter: btnApply.verticalCenter
        anchors.right: btnApply.left
        anchors.rightMargin: 20

        visible: panel.isAdmin
        textValue: qsTr("Factory<br>reset")
        textConfirmMsg: qsTr("Do you want factory reset ?")
        onSignalEventClicked: {
            ViewManager.mainScene.factoryReset(false);
        }
    }

    UiButton{
        id : btnApply
        width : 164
        height: 80
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: btnCancle.left
        anchors.rightMargin: 20

        visible: settingModel.isEditLanguage            ||
                 settingModel.isEditPassword            ||
                 settingModel.isEditNewPassword         ||
                 settingModel.isEditConfirmPassword     ||
                 settingModel.isEditIsDayMode           ||
                 settingModel.isEditIsDebugMode         ||
                 settingModel.isEditLampTime            ||
                 settingModel.isEditBuzzerTime          ||
                 settingModel.isEditSpeedConverter      ||
                 settingModel.isEditMotorDirection      ||
                 settingModel.isEditMotorType           ||
                 settingModel.isEditMotorMDRatio        ||
                 settingModel.isEditMotorWCRatio        ||
                 settingModel.isEditMotorRJRatio        ||
                 settingModel.isEditSorter01RunTimeRatio||
                 settingModel.isEditSorter01OpenTime    ||
                 settingModel.isEditSorter02RunTimeRatio||
                 settingModel.isEditSorter02OpenTime    ||
                 settingModel.isEditSorter03RunTimeRatio||
                 settingModel.isEditSorter03OpenTime    ||
                 settingModel.isEditSorter04RunTimeRatio||
                 settingModel.isEditSorter04OpenTime    ||
                 settingModel.isEditDisplayStability    ||
                 settingModel.isEditMeasureCueSign      ||
                 settingModel.isEditMinStaticWeight     ||
                 settingModel.isEditMinDynamicWeight    ||
                 settingModel.isEditScaler              ||
                 settingModel.isEditStaticFactor        ||
                 settingModel.isEditStandardWeight      ||
                 settingModel.isEditRefWeight           ||
                 settingModel.isEditWCPhotoOn           ||
                 settingModel.isEditMode                ||
                 settingModel.isEditDetectDetectTime    ||
                 settingModel.isEditRunDetectTime       ||
                 settingModel.isEditSignalDelayTime     ||
                 settingModel.isEditMDPhotoOn           ||
                 settingModel.isEditSensorCnt           ||
                 settingModel.isEditSimpleSens01        ||
                 settingModel.isEditSimpleSens02        ||
                 settingModel.isEditSimpleSens03        ||
                 settingModel.isEditSimpleSens04        ||
                 settingModel.isEditSimpleSens05

        type : QmlEnumDef.BUTTON_TYPE_BLUE
        textValue: qsTr("Apply")

        onSignalEventClicked:
        {
           settingModel.onCommandSave()
        }

    }

    UiButton{
        id : btnCancle
        width : 164
        height: 80
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : btnApply.visible

        textValue: qsTr("Cancle")

        onSignalEventClicked:
        {
            settingModel.onCommandCancle()
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
