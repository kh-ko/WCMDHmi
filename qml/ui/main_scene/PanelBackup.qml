import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import EnumDefine 1.0
import ViewManager 1.0
import MainViewModel 1.0
import "../../control/"
import PanelBackupModel 1.0

Item{
    property alias isNeedBackup : backupModel.isNeedBackup
    id: element
    width : 1920
    height: 1080

    function backup()
    {
        if(backupModel.isProc)
        {
            ViewManager.toast.show(qsTr("Backup is already in progress."))
            return;
        }

        backupModel.onCommandShowInterface();
    }

    PanelBackupModel{
        id:backupModel

        onSignalEventComplete: {

            backupModel.onCommandCloseInterface()

            switch(error)
            {
            case EnumDefine.BACKUP_NONE_ERROR:
                ViewManager.toast.show(qsTr("Backup complete."))
                break;

            case EnumDefine.USB_ERROR:
                ViewManager.toast.show(qsTr("Please check USB."))
                break;

            case EnumDefine.READ_ERROR:
                ViewManager.toast.show(qsTr("Please check database."))
                break;

            case EnumDefine.BACKUP_ING:
                ViewManager.toast.show(qsTr("Backup is already in progress."))
                break;

            case EnumDefine.DB_OPEN_FAIL:
                ViewManager.toast.show(qsTr("Please check database."))
                break;

            case EnumDefine.BACKUP_CANCLE:
                ViewManager.toast.show(qsTr("Backup is canceled."))
                break;

            case EnumDefine.BACKUP_UNKNOW_ERROR:
                ViewManager.toast.show(qsTr("Unknow error is occured."))
                break;
            }
        }
    }

    Timer {
        id : timer
        interval: 1000
        running: backupModel.isProc
        repeat: true

        onTriggered:
        {
            if(backupModel.isProc)
            {
                backupModel.onCommandUpdate();
            }
        }
    }

    MouseArea{
        anchors.fill: parent

        visible: backupModel.isShowInterface
        onClicked: {
        }
    }

    UiPanel {
        id: paenlProgress
        width: 340
        height: 181
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10

        visible: backupModel.isProc
        type : EnumDefine.PANEL_TYPE_POPUP

        title: qsTr("Backup progress")

        UiProgressBar{
            height: 60
            radius: 30
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40

            min   : 0
            max   : backupModel.totalCnt
            value : backupModel.currentIdx
            minimumSize : 30
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                backupModel.onCommandShowInterface();
            }
        }

    }

    UiPanel {
        id: uiPanel
        width: 800
        height: 500
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        visible: backupModel.isShowInterface
        type : EnumDefine.PANEL_TYPE_POPUP

        title: qsTr("Backup")


        UiLabelSystem{
            width: 200
            height: 60
            textValue: qsTr("From")
            anchors.left: inputStartDate.left
            anchors.leftMargin: 20
            anchors.bottom: inputStartDate.top
            anchors.bottomMargin: 0
        }

        UiInputDate{
            id:inputStartDate
            width: 330
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 40
            bgColor: uiPanel.bgColor

            isHourMode : false
            isDisable: backupModel.isProc

            year: backupModel.startYear
            month: backupModel.startMonth
            day: backupModel.startDay

            onSignalEventChangedDate: {
                backupModel.onCommandSetStartDate(year, month, day)
            }

        }

        UiLabelSystem{
            width: 24
            height: 60
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: inputStartDate.verticalCenter
            textValue: qsTr("~")

        }

        UiLabelSystem{
            width: 200
            height: 60
            textValue: qsTr("To")
            anchors.left: inputEndDate.left
            anchors.leftMargin: 20
            anchors.bottom: inputEndDate.top
            anchors.bottomMargin: 0
        }

        UiInputDate{
            id:inputEndDate
            width: 330
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.verticalCenter: parent.verticalCenter

            bgColor: uiPanel.bgColor
            isHourMode : false
            isDisable: backupModel.isProc

            year: backupModel.endYear
            month: backupModel.endMonth
            day: backupModel.endDay

            onSignalEventChangedDate: {
                backupModel.onCommandSetEndDate(year, month, day)
            }

        }

        UiButton{
            width: (parent.width / 2) - 40
            height: 80
            textValue: qsTr("Backup")
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            visible: !backupModel.isProc
            type: EnumDefine.BUTTON_TYPE_BLUE

            onSignalEventClicked: {
                backupModel.onCommandBackup();
            }
        }

        UiButton{
            width: (parent.width / 2) - 40
            height: 80
            textValue: qsTr("Close")
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            visible: backupModel.isProc
            type: EnumDefine.BUTTON_TYPE_POPUP

            onSignalEventClicked: {
                backupModel.onCommandCloseInterface();
            }

        }

        UiButton{
            width: (parent.width / 2) - 40
            height: 80
            textValue: qsTr("Cancle")
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            //visible: backupModel.isProc

            type: EnumDefine.BUTTON_TYPE_POPUP

            onSignalEventClicked: {

                if(backupModel.isProc)
                {
                    backupModel.onCommandCancle();
                }
                else
                {
                    backupModel.onCommandCloseInterface();
                }
            }
        }

    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
