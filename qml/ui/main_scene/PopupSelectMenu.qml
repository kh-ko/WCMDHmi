import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import MainViewModel 1.0
import "../../control/"

Item {

    property int selDevice : 0

    signal signalEventClose()

    id : popup

    anchors.fill: parent
    visible: false

    MouseArea{
        anchors.fill: parent

        onClicked: {popup.visible = false}
    }

    Rectangle{
        anchors.fill: parent
        color : "#59000000"
    }

    UiPanel
    {
        id : panel
        width : 704
        height :520

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        type : QmlEnumDef.PANEL_TYPE_POPUP

        title : qsTr("Select device")

        MouseArea{
            anchors.fill: parent

            onClicked: {}
        }

        UiButton{
            id: btnWeightChecker
            height: 96
            anchors.verticalCenterOffset: -88
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40


            type : QmlEnumDef.BUTTON_TYPE_BLUE
            textValue: qsTr("Weight checker")

            onSignalEventClicked: {
                selDevice = QmlEnumDef.DEVICE_WEIGHT_CHECKER
                popup.visible = false;
                signalEventClose()
            }
        }

        UiButton{
            id: btnMetalDetector
            height: 96
            anchors.verticalCenterOffset: 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40


            type : QmlEnumDef.BUTTON_TYPE_METAL
            textValue: qsTr("Metal detector")

            onSignalEventClicked: {
                selDevice = QmlEnumDef.DEVICE_METAL_DETECTOR
                popup.visible = false;
                signalEventClose()
            }
        }

        UiButton{
            id: btnCancle
            height: 96
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40


            type : QmlEnumDef.BUTTON_TYPE_POPUP
            textValue: qsTr("Cancle")

            onSignalEventClicked: {
                popup.visible = false;
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_height:100;anchors_width:100}
}
##^##*/
