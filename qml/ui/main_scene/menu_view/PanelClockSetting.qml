import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import PanelClockSettingModel 1.0

UiPanel {
    id: uiPanel
    height: 997
    width : 1519

    PanelClockSettingModel{
        id : clockSettingModel
    }

    UiLabelSystem{
        id: labelYear
        width: 120
        height: 40
        textValue: qsTr("Year")
        anchors.left: parent.left
        anchors.leftMargin: 60
        anchors.top: parent.top
        anchors.topMargin: 40
    }

    UiInputNumber{
        id: inputYear
        width: 120
        height: 60
        anchors.top: labelYear.bottom
        anchors.topMargin: 10
        anchors.left: labelYear.left
        anchors.leftMargin: -20

        isLocaleStyle: false
        min : 2020
        max : 9999
        fillZero: "0000"

        numberValue: clockSettingModel.year

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetYear(value)
        }

    }

    UiLabelSystem{
        id: labelMonth
        width: 100
        height: 40
        textValue: qsTr("Month")
        anchors.left: labelYear.right
        anchors.leftMargin: 20
        anchors.verticalCenter: labelYear.verticalCenter
    }

    UiInputNumber{
        id: inputMonth
        height: 60
        anchors.left: labelMonth.left
        anchors.leftMargin: -20
        anchors.top: labelMonth.bottom
        anchors.topMargin: 10

        isLocaleStyle: false
        min : 1
        max : 12
        postfix: "."
        fillZero: "00"

        numberValue: clockSettingModel.month

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetMonth(value)
        }
    }

    UiLabelSystem{
        id: labelDay
        width: 100
        height: 40
        textValue: qsTr("Day")
        anchors.left: labelMonth.right
        anchors.leftMargin: 20
        anchors.verticalCenter: labelMonth.verticalCenter
    }

    UiInputNumber{
        id: inputDay
        height: 60
        anchors.left: labelDay.left
        anchors.leftMargin: -20
        anchors.top: labelDay.bottom
        anchors.topMargin: 10

        isLocaleStyle: false
        min : 1
        max : 31
        fillZero: "00"

        numberValue: clockSettingModel.day

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetDay(value)
        }

    }

    UiLabelSystem{
        id: labelHour
        width: 100
        height: 40
        textValue: qsTr("Hour")
        anchors.left: inputYear.left
        anchors.leftMargin: 20
        anchors.top: inputYear.bottom
        anchors.topMargin: 40
    }

    UiInputNumber{
        height: 60
        anchors.top: labelHour.bottom
        anchors.topMargin: 10
        anchors.left: labelHour.left
        anchors.leftMargin: -20

        isLocaleStyle: false
        min : 0
        max : 23
        fillZero: "00"

        numberValue: clockSettingModel.hour

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetHour(value)
        }

    }

    UiLabelSystem{
        id: labelMin
        width: 100
        height: 40
        textValue: qsTr("Min")
        anchors.left: labelHour.right
        anchors.leftMargin: 20
        anchors.verticalCenter: labelHour.verticalCenter
    }

    UiInputNumber{
        height: 60
        anchors.left: labelMin.left
        anchors.leftMargin: -20
        anchors.top: labelMin.bottom
        anchors.topMargin: 10

        isLocaleStyle: false
        min : 0
        max : 59
        fillZero: "00"

        numberValue: clockSettingModel.min

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetMin(value)
        }

    }

    UiLabelSystem{
        id : labelSec
        width: 100
        height: 40
        textValue: qsTr("Sec")
        anchors.left: labelMin.right
        anchors.leftMargin: 20
        anchors.verticalCenter: labelMin.verticalCenter
    }

    UiInputNumber{
        height: 60
        anchors.left: labelSec.left
        anchors.leftMargin: -20
        anchors.top: labelSec.bottom
        anchors.topMargin: 10

        isLocaleStyle: false
        min : 0
        max : 59
        fillZero: "00"

        numberValue: clockSettingModel.sec

        onSignalChangeValue:
        {
            clockSettingModel.onCommandSetSec(value)
        }
    }

    UiButton{
        id : btnApply

        height: 80
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        width: 200

        type : EnumDefine.BUTTON_TYPE_BLUE

        textValue: qsTr("Apply")
        onSignalEventClicked: {
            clockSettingModel.onCommandApply()
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
