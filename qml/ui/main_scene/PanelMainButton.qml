import QtQuick 2.0
import "../../control/"
import QtQuick.Layouts 1.3
import ViewManager 1.0
import EnumDefine 1.0

Item {

    //property bool isUnLock : true
    signal signalEventRunClicked()
    signal signalEventHomeClicked()
    signal signalEventStopClicked()
    signal signalEventMenuClicked()
    signal signalEventLockClicked()
    signal signalEventShutdownClicked()

    id : panel

    width : 140
    height: 987

    UiPanel{
        id: uiPanel
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20

            UiButton{
                id: btnHome
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: "img/main_btn/btn_home.png"
                isImage: true

                onSignalEventClicked: {
                    panel.signalEventHomeClicked()
                }
            }

            UiButton{
                id: btnRun
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: "img/main_btn/btn_run.png"
                isImage: true
                onSignalEventClicked: {
                    panel.signalEventRunClicked()
                }
            }

            UiButton{
                id: btnStop
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: "img/main_btn/btn_stop.png"
                isImage: true
                onSignalEventClicked: {
                    panel.signalEventStopClicked()
                }
            }

            UiButton{
                id: btnMenu
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: "img/main_btn/btn_menu.png"
                isImage: true
                onSignalEventClicked: {
                    panel.signalEventMenuClicked()
                }
            }

            UiButtonConfirm{
                id: btnShutdown
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: "img/main_btn/power_blue.png"
                isImage: true
                textConfirmMsg: qsTr("Do you want power off ?")
                onSignalEventClicked: {
                    panel.signalEventShutdownClicked();
                }
            }

            /*
            UiButton{
                id: btnLock
                Layout.fillHeight: true
                Layout.fillWidth: true

                imageSource: ViewManager.mainScene.isLock === true ? "img/main_btn/lock.png" : "img/main_btn/unlock.png"

                isImage: true
                onSignalEventClicked: {
                    panel.signalEventLockClicked()
                }
            }
            */
        }
    }
}







/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
