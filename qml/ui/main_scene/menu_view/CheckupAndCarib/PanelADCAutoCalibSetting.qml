import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelADCAutoCalibSettingModel 1.0

UiPanel {
    id: panel
    width : 1519; height: 997
    title: qsTr("ADC auto calibration setting")

    signal signalEventCloseClicked()

    anchors.fill: parent


    MouseArea{
        anchors.fill: parent
    }

    PanelADCAutoCalibSettingModel{
        id : settingModel
    }

    UiRadioBtn{
        id: radioUse
        width : 200
        anchors.left: parent.left; anchors.leftMargin: 20; anchors.top: parent.top; anchors.topMargin: panel.titleHeight

        isSelect: settingModel.mIsUse

        textValue : qsTr("Use")

        onSignalEventClicked:
        {
            settingModel.onCommandSetIsUse(true);
        }
    }

    UiRadioBtn{
        id: radioNotUse
        width : 200
        anchors.left: radioUse.right; anchors.leftMargin: 20; anchors.verticalCenter: radioUse.verticalCenter

        isSelect: !settingModel.mIsUse
        textValue : qsTr("Not use")

        onSignalEventClicked:
        {
            settingModel.onCommandSetIsUse(false)
        }
    }

    Item{
        height: 60
        anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.top: radioNotUse.bottom; anchors.topMargin: 10
        visible: settingModel.mIsUse

        UiInputNumber{
            id : inputMin
            height: 60; width : 350
            anchors.left : parent.left; anchors.top: parent.top

            bgColor: panel.bgColor
            postfix: ""
            labelText : qsTr("· Min ADC")
            inputWidth: 170

            numberValue: settingModel.mMinCheckValue

            onSignalChangeValue: {
                settingModel.onCommandSetMinCheckValue(value)
            }
        }

        UiInputNumber{
            id : inputMax
            height: 60; width : 350
            anchors.left : inputMin.right; anchors.leftMargin: 100; anchors.verticalCenter: inputMin.verticalCenter

            bgColor: panel.bgColor
            postfix: ""
            labelText : qsTr("· Max ADC")
            inputWidth: 170

            numberValue: settingModel.mMaxCheckValue

            onSignalChangeValue: {
                settingModel.onCommandSetMaxCheckValue(value)
            }
        }
    }

    UiButton{
        id: btnCancel
        height: 80; width: 200
        anchors.verticalCenter: btnApply.verticalCenter; anchors.right: btnApply.left; anchors.rightMargin: 20

        textValue: qsTr("Cancel")

        onSignalEventClicked: {
            panel.signalEventCloseClicked();
        }
    }

    UiButton{
        id: btnApply
        height: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 40
        width: 200

        textValue: qsTr("Apply")

        onSignalEventClicked: {
            settingModel.onCommandApply();
            panel.signalEventCloseClicked();
        }
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
