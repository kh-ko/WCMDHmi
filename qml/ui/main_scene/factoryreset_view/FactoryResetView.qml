import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0
import FontManager 1.0
import QtQuick.Controls.Universal 2.12
import FactoryResetViewModel 1.0
import QtQuick.Controls 2.3

Item {
    property bool isOnlyEvent               : false
    property bool isDeviceCompleted         : false
    property bool isDBCompleted             : false
    property bool isLocalSettingCompleted   : false

    width : 1920
    height :1080

    id : panel

    Component.onCompleted: {

        if(panel.isOnlyEvent)
        {
            factoryResetModel.onCommandLoggingReset();
        }
        else
        {
            factoryResetModel.onCommandFactoryReset();
        }
    }

    FactoryResetViewModel{
        id : factoryResetModel

        onSignalEventExit: {
            Qt.quit()
        }
    }

    Rectangle{
        id: rectangle
        anchors.fill: parent
        color : "#131313"

        Rectangle
        {
            width: 40
            height: 40
            anchors.verticalCenter: labelDevice.verticalCenter
            anchors.right: labelDevice.left
            anchors.rightMargin: 20

            color: factoryResetModel.isDeviceCompleted ? "#0085FF" : "#00000000"
            border.width: 0
            radius: 20

            BusyIndicator {
                anchors.fill: parent

                Universal.accent: Universal.Cobalt
                visible: !factoryResetModel.isDeviceCompleted
            }
        }

        Text{
            id:labelDevice
            width: 500
            height: 80

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#ACACAC"
            text: qsTr("Device factory reset")
            anchors.verticalCenterOffset: -80
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle
        {
            width: 40
            height: 40
            anchors.verticalCenter: labelDB.verticalCenter
            anchors.right: labelDB.left
            anchors.rightMargin: 20

            color: factoryResetModel.isDBCompleted ? "#0085FF" : "#00000000"
            border.width: 0
            radius: 20

            BusyIndicator {
                anchors.fill: parent

                Universal.accent: Universal.Cobalt
                visible: !factoryResetModel.isDBCompleted
            }
        }

        Text{
            id:labelDB
            width: 500
            height: 80


            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#ACACAC"
            text: qsTr("Database factory reset")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle
        {
            width: 40
            height: 40
            anchors.verticalCenter: labelLocalSetting.verticalCenter
            anchors.right: labelLocalSetting.left
            anchors.rightMargin: 20

            color: factoryResetModel.isLocalSettingCompleted ? "#0085FF" : "#00000000"
            border.width: 0
            radius: 20

            BusyIndicator {
                anchors.fill: parent

                Universal.accent: Universal.Cobalt
                visible: !factoryResetModel.isLocalSettingCompleted
            }
        }

        Text{
            id:labelLocalSetting
            width: 500
            height: 80


            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#ACACAC"
            text: qsTr("Local setting factory reset")
            anchors.verticalCenterOffset: 80
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
