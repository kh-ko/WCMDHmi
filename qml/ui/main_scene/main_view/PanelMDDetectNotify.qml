import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import QmlEnumDef 1.0
import ViewManager 1.0

Item {

    id : panel

    height : 340
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.right: parent.right
    anchors.rightMargin: 20
    anchors.bottom: parent.bottom
    anchors.bottomMargin: -1 * height

    opacity : 0
    visible : false

    function show()
    {
        timer.stop();
        closeAni.stop();
        showAni.stop();

        panel.visible = true;
        panel.opacity = 0;
        panel.anchors.bottomMargin = panel.height;

        timer.start();
        showAni.start();
    }

    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            closeAni.start()
        }
    }

    ParallelAnimation {
        id :showAni

        NumberAnimation {
            target: panel
            properties: "opacity"
            duration: 250
            from : 0
            to: 1.0
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: panel
            properties: "anchors.bottomMargin"
            duration: 500
            from: -1 * panel.height //toast.height
            to : 20
            easing.type: Easing.InOutQuad
        }
    }

    ParallelAnimation {
        id :closeAni

        NumberAnimation {
            target: panel
            properties: "opacity"
            duration: 250
            from : 1.0
            to: 0
            easing.type: Easing.InOutQuad
        }

        onStopped: {
            panel.visible = false;
        }
    }

    MouseArea{
        anchors.fill: parent
        onCanceled: {}
    }

    Rectangle
    {
        id: uiPanel
        color: "#d9000000"
        radius: 10
        border.width: 0
        anchors.fill: parent

        UiLabelAlarm{
            anchors.fill: parent

            horizontalAlignment : Text.AlignHCenter
            textValue: qsTr("Detect")
        }

        UiButton
        {
            width: 162
            height : 90

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_POPUP
            textValue : qsTr("Confirm")

            onSignalEventClicked:
            {
                closeAni.start()
            }
        }
    }
}
