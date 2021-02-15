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

    UiRadioBtn{
        id: radioUse
        height: 60
        width : 142
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 40

        textMargin : 20

        isHighlight: true
        isSelect: true

        textValue : qsTr("Use")

        onSignalEventClicked:
        {
        }
    }

    UiRadioBtn{
        id: radioNotUse
        height: 60
        anchors.verticalCenter: radioUse.verticalCenter
        width : 151
        anchors.left: radioUse.right
        anchors.verticalCenterOffset: 0
        anchors.leftMargin: 98

        textMargin : 20

        isHighlight: true
        isSelect: true

        textValue : qsTr("Not use")

        onSignalEventClicked:
        {
        }
    }


    UiInputFloat {
        id: inputOver
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: radioUse.bottom
        anchors.topMargin: 80

        labelText : qsTr("· Over")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "g"
        min: 0
        max: 99999.9

        realValue: 0.1
        isHighlight: true

        onSignalChangeValue: {
        }
    }

    UiInputFloat {
        id: inputNormal
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputOver.bottom
        anchors.topMargin: 40

        labelText : qsTr("· Normal")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "g"
        min: 0
        max: 99999.9

        realValue: 0.1
        isHighlight: true

        onSignalChangeValue: {
        }
    }

    UiInputFloat {
        id: inputUnder
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputNormal.bottom
        anchors.topMargin: 40

        labelText : qsTr("· Under")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "g"
        min: 0
        max: 99999.9

        realValue: 0.1
        isHighlight: true

        onSignalChangeValue: {
        }
    }

    UiInputFloat {
        id: inputTare
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputUnder.bottom
        anchors.topMargin: 40

        labelText : qsTr("· Tare")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "g"
        min: 0
        max: 99999.9

        realValue: 0.1
        isHighlight: true

        onSignalChangeValue: {
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
