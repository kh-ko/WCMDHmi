import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import "./CheckupAndCarib"
import QtQuick.Layouts 1.3
import PanelMDCheckupModel 1.0
import QmlEnumDef 1.0

UiPanel
{
    property var isAdmin    : true
    property var isWCEnable : true
    property var isMDEnable : true

    id : panel

    width : 1519
    height: 997


    ColumnLayout {
        id: columnLayout
        width: 800
        height: 340
        anchors.verticalCenter: parent.verticalCenter
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter

        UiButton{
            id : btnStaticCaribraion
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            type : QmlEnumDef.BUTTON_TYPE_BLUE

            textValue: qsTr("Weight checker static calibration")

            onSignalEventClicked: {
                viewContainer.clear()
                viewContainer.push(panelWCStaticCaribraion)
            }
        }

        UiButton{
            id : btnDynamicCaribraion
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            type : QmlEnumDef.BUTTON_TYPE_BLUE
            textValue: qsTr("Weight checker dynamic calibration")

            onSignalEventClicked: {
                viewContainer.clear()
                viewContainer.push(panelWCDynamicCaribraion)
            }
        }

        UiButton{
            id : btnMDCheckup
            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            type : QmlEnumDef.BUTTON_TYPE_METAL
            textValue: qsTr("Metal detector checkup")

            visible: isMDEnable

            onSignalEventClicked: {
                viewContainer.clear()
                viewContainer.push(panelMDCheckup)
            }
        }
    }

    StackView
    {
        id: viewContainer
        anchors.fill : parent
        initialItem: panel.isWCEnable === false ? panelMDCheckup : undefined
    }

    Component{ id : panelMDCheckup;
        PanelMDCheckup
        {
            anchors.fill: parent
            isWCEnable : panel.isWCEnable
            isAdmin: panel.isAdmin
            onSignalEventCloseClicked: {
                viewContainer.clear()
            }
        }
    }

    Component{ id : panelWCDynamicCaribraion;
        PanelWCDynamicCaribraion
        {
            anchors.fill: parent

            onSignalEventCloseClicked: {
                viewContainer.clear()
            }
        }
    }

    Component{ id : panelWCStaticCaribraion;
        PanelWCStaticCaribraion
        {
            anchors.fill: parent

            onSignalEventCloseClicked: {
                viewContainer.clear()
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
