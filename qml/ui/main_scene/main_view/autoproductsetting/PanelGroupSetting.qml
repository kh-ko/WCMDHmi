import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0

UiPanel {

    id : panel
    width: 1340
    height: 880

    type: QmlEnumDef.PANEL_TYPE_UP_PANEL

    UiInputNumber{
        id: inputGroupCount
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.leftMargin: 40

        bgColor : panel.bgColor
        inputWidth: 420
        labelText: qsTr("· Count")
        min: 0
        max: 999999

        numberValue: 0
        isHighlight: true

        onSignalChangeValue: {
        }
    }

    UiComboBox{
        id: comboGroupMotion
        width: 700
        height: 60
        z : 1
        anchors.left: parent.left
        anchors.top: inputGroupCount.bottom
        anchors.topMargin: 40
        anchors.leftMargin: 40
        comboWidth: 420

        bgColor : panel.bgColor
        labelText : qsTr("· Motion")

        listModel :comboGroupMotionOption
        selIdx: 0
        isHighlight: true

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
                itemText : qsTr("Sorter 01")
                itemIdx : 2
            }
            ListElement {
                itemText : qsTr("Sorter 02")
                itemIdx : 3
            }
            ListElement {
                itemText : qsTr("Sorter 03")
                itemIdx : 4
            }
            ListElement {
                itemText : qsTr("Sorter 04")
                itemIdx : 5
            }
        }

        onSignalEventChangedSel: {
        }
    }

    UiRadioBtn{
        id: checkGroupLampOn
        height: 60
        width : 142
        anchors.left: parent.left
        anchors.top: comboGroupMotion.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 319

        textMargin : 20

        isHighlight: true
        isSelect: true

        textValue : qsTr("Lamp")

        onSignalEventClicked:
        {
        }
    }

    UiRadioBtn{
        id: checkGroupBuzzerOn
        height: 60
        anchors.verticalCenter: checkGroupLampOn.verticalCenter
        width : 151
        anchors.left: checkGroupLampOn.right
        anchors.verticalCenterOffset: 0
        anchors.leftMargin: 98

        textMargin : 20

        isHighlight: true
        isSelect: true

        textValue : qsTr("Buzzer")

        onSignalEventClicked:
        {
        }
    }

    UiButton{
        width: 160
        height: 60
        anchors.right: btnNext.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        textValue: qsTr("Pre")
    }

    UiButton{
        id : btnNext
        width: 160
        height: 60
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.rightMargin: 40
        textValue: qsTr("Next")

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
