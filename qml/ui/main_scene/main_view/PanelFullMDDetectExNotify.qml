import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDef 1.0
import QmlEnumDef 1.0
import ViewManager 1.0

Item {

    property bool ch01Detect : false
    property bool ch02Detect : false

    id : panel

    height : 500
    anchors.left: parent.left
    anchors.leftMargin: 100
    anchors.right: parent.right
    anchors.rightMargin: 100
    anchors.bottom: parent.bottom
    anchors.bottomMargin: -1 * height

    opacity : 0
    visible : false

    signal signalEventClicked()

    function show(detectChannel)
    {
        if(detectChannel === 1)
            ch01Detect = true;
        else if(detectChannel === 2)
            ch02Detect = true;
        else
            return;

        timer.stop();
        closeAni.stop();
        showAni.stop();


        panel.visible = true;
        panel.opacity = 0;
        panel.anchors.bottomMargin = panel.height;

        //timer.start();
        showAni.start();
    }

    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            //closeAni.start()
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

        Image {
            id: imageIcon01
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40

            width : 500
            height: 500
            source: "/ui/main_scene/main_view/img_panelmetaldetector/md_detect01.png"
            fillMode: Image.PreserveAspectFit
            visible: ch01Detect == true && ch02Detect == false
        }

        Image {
            id: imageIcon02
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40

            width : 500
            height: 500
            source: "/ui/main_scene/main_view/img_panelmetaldetector/md_detect02.png"
            fillMode: Image.PreserveAspectFit
            visible: ch01Detect == false && ch02Detect == true
        }

        Image {
            id: imageIcon03
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40

            width : 500
            height: 500
            source: "/ui/main_scene/main_view/img_panelmetaldetector/md_detect03.png"
            fillMode: Image.PreserveAspectFit
            visible: ch01Detect == true && ch02Detect == true
        }

        UiLabelAlarm{
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 580
            anchors.right: parent.right
            anchors.rightMargin: 40
            height: parent.height

            textValue: ch01Detect == true && ch02Detect == true ? qsTr("Metal is detected on all channels.") :
                       ch01Detect == true && ch02Detect == false? qsTr("Metal is detected on channel 01.")   :
                       ch01Detect == false && ch02Detect == true?qsTr("Metal is detected on channel 02.") : ""
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
                ch01Detect = false;
                ch02Detect = false;
                panel.signalEventClicked();
                closeAni.start()
            }
        }
    }
}
