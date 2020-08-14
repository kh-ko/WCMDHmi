import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
//import "../../component/"
import "../../control/"
import ViewManager 1.0

Item {
    property string textCompany : "NOVASEN"
    property string textTel : "T 051 - 581 - 7071"
    property string textClock : "2020/03/27 23:05:01"
    property bool   isRun : true
    property bool   isComm : true
    property bool   isAlarm : true
    property bool   isNeedBackup : false

    signal signalEventAlarmClicked()

    id: panel

    height: 63
    width: 1920

    UiLabelSystemSmall{
        width: 727
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        textValue: panel.textCompany + "      " + panel.textTel
    }

    UiLabelSystemSmall{
        width: 364
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0
        horizontalAlignment : Text.AlignHCenter
        textValue: textClock
    }

    UiIndicate{
        id : indiBackup
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: indiRun.left
        anchors.rightMargin: 20

        glowOnColor: "#59FF0000"
        offImage: "img/indicator/backup_off.png"
        onImage: "img/indicator/backup_on.png"
        isOn : panel.isNeedBackup

    }

    UiIndicate{
        id : indiRun
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: indiComm.left
        anchors.rightMargin: 20

        glowOnColor: "#590085FF"
        offImage: "img/indicator/run_disable_indi.png"
        onImage: "img/indicator/run_enable_indi.png"
        isOn : panel.isRun

    }

    UiIndicate{
        id : indiComm
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: indiAlarm.left
        anchors.rightMargin: 20

        glowOnColor: "#590085FF"
        glowOffColor:"#59FF0000"
        onImage: "img/indicator/comm_enable_indi.png"
        offImage: "img/indicator/comm_disable_indi.png"
        isOn : panel.isComm

    }

    UiIndicate{
        id : indiAlarm
        width: 30
        height: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20

        glowOnColor: "#59FF0000"
        onImage: "img/indicator/alarm_enalbe_indi.png"
        offImage: "img/indicator/alarm_diable_indi.png"
        isOn : panel.isAlarm

        MouseArea{
            anchors.leftMargin: -53
            anchors.rightMargin: -20
            anchors.topMargin: -16
            anchors.bottomMargin: -36
            anchors.fill: parent

            onClicked: {
                panel.signalEventAlarmClicked();
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
