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
        id: inputBeltSpeed
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.leftMargin: 40

        bgColor : panel.bgColor
        inputWidth: 420
        labelText: qsTr("· Belt speed")
        postfix: "m/min"
        min: 1
        max: 999

        numberValue: 1
        isHighlight: true

        onSignalChangeValue: {
        }
    }

    UiInputFloat {
        id: inputMotorAcceleration
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputBeltSpeed.bottom
        anchors.topMargin: 40

        labelText : qsTr("· Belt acceleration")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "s"
        min: 0
        max: 999

        realValue: 0.1
        isHighlight: true

        onSignalChangeValue: {
        }
    }


    UiInputFloat {
        id: inputMotorDeceleration
        width: 700
        height: 60
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: inputMotorAcceleration.bottom
        anchors.topMargin: 40

        labelText : qsTr("· Belt deceleration")
        inputWidth: 420
        bgColor   : panel.bgColor
        postfix   : "s"
        min: 0
        max: 999

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
    D{i:0;formeditorZoom:0.75}D{i:1}
}
##^##*/
