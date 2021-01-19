import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelInformationModel 1.0

UiPanel {
    property bool isAdmin : false

    id: uiPanel

    width : 1518
    height : 997

    PanelInformationModel
    {
        id : informationModel

        onSignalResultSaveInformation: {
            ViewManager.toast.show(qsTr("Your settings have been saved."))
        }
    }

    UiInputString{
        id: inputCompany
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        labelText: qsTr("· Manufactured by")
        inputWidth: 300
        anchors.left: parent.left
        anchors.leftMargin: 20

        isDisable: true

        textValue: informationModel.company
    }

    UiInputString {
        id: inputModel
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20

        anchors.top: inputCompany.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.left: parent.left

        inputWidth: 300
        labelText: qsTr("· Model")
        isDisable: true

        textValue: informationModel.model
    }


    UiInputNumber {
        id: inputDeviceNo
        height: 60

        anchors.top: inputModel.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        //postfix: "g"
        labelText: qsTr("· Device number")

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDeviceNumber
        numberValue: informationModel.deviceNumber

        onSignalChangeValue: {
            informationModel.onCommandSetDeviceNumber(value)
        }
    }

    UiLabelSystem{
        id : labelSerialNumber
        height: 60
        visible: false
        anchors.right: divider.left
        anchors.rightMargin: 20
        textValue: qsTr("· Serial number")

        anchors.top: inputModel.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.left: parent.left
    }


    UiInputString {
        id: inputSerialNumber
        height: 60
        visible: false
        anchors.right: divider.left
        anchors.rightMargin: 20

        anchors.top: labelSerialNumber.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.left: parent.left

        inputWidth: -1
        isDisable: true

        textValue: informationModel.serialNumber
    }

    UiInputString {
        id: inputDspVersion
        height: 60

        anchors.top: inputDeviceNo.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        labelText: qsTr("· DSP version")
        isDisable: true

        textValue: informationModel.dspVersion
    }

    UiInputString {
        id: inputHMIVersion
        height: 60

        anchors.top: inputDspVersion.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        labelText: qsTr("· HMI version")
        isDisable: true

        textValue: informationModel.hmiVersion
    }

    UiInputString {
        id: inputPower
        height: 60

        anchors.top: inputHMIVersion.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        labelText: qsTr("· Power")

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditPower
        textValue: informationModel.power

        onSignalChangeText: {
            informationModel.onCommandSetPower(value)
        }
    }

    UiLabelSystem{
        id : labelHomepage
        height: 60
        anchors.top: inputPower.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: divider.left
        anchors.rightMargin: 20

        textValue: qsTr("· Homepage")
    }


    UiInputString {
        id: inputHomepage
        height: 60
        anchors.right: divider.left
        anchors.rightMargin: 20
        anchors.top: labelHomepage.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.left: parent.left

        inputWidth: -1
        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditHomepage
        textValue: informationModel.homepage

        onSignalChangeText: {
            informationModel.onCommandSetHomepage(value)
        }
    }
    /*
    UiInputString {
        id: inputHomepage
        height: 60

        anchors.top: inputPower.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        labelText: qsTr("· Homepage")

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditHomepage
        textValue: informationModel.homepage

        onSignalChangeText: {
            informationModel.onCommandSetHomepage(value)
        }
    }
    */

    UiInputNumber {
        id: inputMax
        height: 60

        anchors.top: inputHomepage.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.left: parent.left
        anchors.right: divider.left
        anchors.rightMargin: 20

        inputWidth: 300
        postfix: "g"
        labelText: qsTr("· Max weight")

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditMaxWeight
        numberValue: informationModel.maxWeight

        onSignalChangeValue: {
            informationModel.onCommandSetMaxWeight(value)
        }
    }

    UiDivider{
        id : divider
        x: 600
        width: 2
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
    }

    Image{
        id : imageDevice
        height: 439
        fillMode: Image.PreserveAspectFit
        source: "Infomation/image_device/device.png"
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: divider.right
        anchors.leftMargin: 20
    }

    UiInputNumber{
        id : inputDistWeightChecker
        width: 800
        height: 60
        labelText: qsTr("① Distance to weight checker")
        anchors.topMargin: 20
        anchors.top: imageDevice.bottom
        anchors.leftMargin: 40
        anchors.left: divider.right
        anchors.right: parent.right
        anchors.rightMargin: 40

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistToWC
        postfix: "mm"
        inputWidth: 170
        bgColor: uiPanel.bgColor

        numberValue: informationModel.distToWC

        onSignalChangeValue:
        {
            informationModel.onCommandSetDistToWC(value)
        }
    }

    UiInputNumber{
        id : inputDistBtwPhotoToSensor
        width: 800
        height: 60
        labelText: qsTr("② Distance between Photo to sensor")
        anchors.topMargin: 10
        anchors.top: inputDistWeightChecker.bottom
        anchors.leftMargin: 40
        anchors.left: divider.right
        anchors.right: parent.right
        anchors.rightMargin: 40

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistBtwPhotoToSensor
        bgColor: uiPanel.bgColor
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distBtwPhotoToSensor

        onSignalChangeValue: {
            informationModel.onCommandSetDistBtwPhotoToSensor(value)
        }
    }


    UiInputNumber{
        id : inputDistBtwSensor
        width: 800
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDistBtwPhotoToSensor.bottom
        anchors.leftMargin: 40
        anchors.left: divider.right
        anchors.right: parent.right
        anchors.rightMargin: 40

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistBtwSensor
        bgColor: uiPanel.bgColor
        labelText : qsTr("③ Distance between sensor")
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distBtwSensor

        onSignalChangeValue: {
            informationModel.onCommandSetDistBtwSensor(value)
        }
    }

    UiInputNumber{
        id : inputSensorLength
        width: 800
        height: 60
        anchors.topMargin: 10
        anchors.top: inputDistBtwSensor.bottom
        anchors.leftMargin: 40
        anchors.left: divider.right
        anchors.right: parent.right
        anchors.rightMargin: 40

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditSensorLength
        bgColor: uiPanel.bgColor
        labelText : qsTr("④ Sensor length")
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.sensorLength

        onSignalChangeValue: {
            informationModel.onCommandSetSensorLength(value)
        }
    }

    UiLabelSystem{
        id : labelSorter
        height: 60
        width: 700
        anchors.topMargin: 10
        anchors.top: inputSensorLength.bottom
        anchors.left: divider.right
        anchors.leftMargin: 40

        textValue: qsTr("⑤ Distance to Sorter")
    }

    UiInputNumber{
        id : inputSorter01
        width: 170
        height: 60
        anchors.top: labelSorter.bottom
        anchors.topMargin: 0
        anchors.left: divider.right
        anchors.leftMargin: 40

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistToSorter01
        bgColor: uiPanel.bgColor
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distToSorter01

        onSignalChangeValue: {
            informationModel.onCommandSetDistToSorter01(value)
        }
    }

    UiInputNumber{
        id : inputSorter02
        width: 170
        height: 60
        anchors.verticalCenter: inputSorter01.verticalCenter
        anchors.left: inputSorter01.right
        anchors.leftMargin: 20

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistToSorter02
        bgColor: uiPanel.bgColor
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distToSorter02

        onSignalChangeValue: {
            informationModel.onCommandSetDistToSorter02(value)
        }
    }

    UiInputNumber{
        id : inputSorter03
        width: 170
        height: 60
        anchors.verticalCenter: inputSorter01.verticalCenter
        anchors.left: inputSorter02.right
        anchors.leftMargin: 20

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistToSorter03
        bgColor: uiPanel.bgColor
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distToSorter03

        onSignalChangeValue: {
            informationModel.onCommandSetDistToSorter03(value)
        }
    }

    UiInputNumber{
        id : inputSorter04
        width: 170
        height: 60
        anchors.verticalCenter: inputSorter01.verticalCenter
        anchors.left: inputSorter03.right
        anchors.leftMargin: 20

        isDisable: !uiPanel.isAdmin
        isHighlight: informationModel.isEditDistToSorter04
        bgColor: uiPanel.bgColor
        postfix: "mm"
        inputWidth: 170

        numberValue: informationModel.distToSorter04

        onSignalChangeValue: {
            informationModel.onCommandSetDistToSorter04(value)
        }
    }

    UiButton{
        id : btnHMIOut
        width: 164
        height: 80
        anchors.verticalCenter: btnApply.verticalCenter
        anchors.right: btnFactoryReset.left
        anchors.rightMargin: 20

        visible: uiPanel.isAdmin
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
        anchors.right: divider.right
        anchors.rightMargin: 20

        visible: uiPanel.isAdmin
        textValue: qsTr("Factory<br>reset")
        textConfirmMsg: qsTr("Do you want factory reset ?")
        onSignalEventClicked: {
            ViewManager.mainScene.factoryReset(false);
        }
    }

    UiButton{
        id : btnApply
        width : 164
        height : 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: btnCancle.left
        anchors.rightMargin: 20

        visible: informationModel.isEditPower                     ||
                 informationModel.isEditHomepage                  ||
                 informationModel.isEditMaxWeight                 ||
                 informationModel.isEditDistBtwPhotoToSensor      ||
                 informationModel.isEditDistBtwSensor             ||
                 informationModel.isEditDistToWC                  ||
                 informationModel.isEditSensorLength              ||
                 informationModel.isEditDeviceNumber              ||
                 informationModel.isEditDistToSorter01            ||
                 informationModel.isEditDistToSorter02            ||
                 informationModel.isEditDistToSorter03            ||
                 informationModel.isEditDistToSorter04


        type : QmlEnumDef.BUTTON_TYPE_BLUE
        textValue: qsTr("Apply")

        onSignalEventClicked:
        {
           informationModel.onCommandSave()
        }

    }

    UiButton{
        id : btnCancle
        width : 164
        height : 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible : btnApply.visible

        textValue: qsTr("Cancle")

        onSignalEventClicked:
        {
            informationModel.onCommandCancle()
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:2}D{i:3}D{i:4}D{i:5}
}
##^##*/
