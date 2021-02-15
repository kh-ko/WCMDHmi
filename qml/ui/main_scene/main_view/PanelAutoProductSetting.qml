import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0

Dialog {
    property var value
    property var max

    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside

    anchors.centerIn : parent

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();

        console.debug("destory");
    }

    background: Rectangle
    {
        color : "#59000000"
        radius : 10
    }

    UiPanel{
        id :panel

        anchors.centerIn: parent
        height: 1000 / 1 //ViewManager.scale
        width: 1600
        scale: ViewManager.scale



        UiButton{
            id : btnClose
            height: 60
            width: 200
            textValue : qsTr("Close")
            type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            onSignalEventClicked: {

                dialog.close();
            }

        }

        UiButton{
            id : btnApply
            height: 60
            width: 200
            textValue : qsTr("Apply")
            type : QmlEnumDef.BUTTON_TYPE_BLUE
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: btnClose.left
            anchors.rightMargin: 20

            onSignalEventClicked: {

                dialog.close();
            }
        }

        ColumnLayout{
            width: 200
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 20
            anchors.bottomMargin: 20
            anchors.topMargin: 100
            anchors.leftMargin: 20

            UiToggleBtn{
                id: btnGeneral
                Layout.fillHeight: true
                Layout.fillWidth: true

                textValue: qsTr("General")
                //isOn : selMenu == QmlEnumDef.MENU_PRODUCT_SETTING

                onSignalEventClicked:
                {
                    //if(selMenu == QmlEnumDef.MENU_PRODUCT_SETTING)
                    //    return

                    //selMenu = QmlEnumDef.MENU_PRODUCT_SETTING

                    //viewContainer.clear()
                    //viewContainer.push(panelProductSetting, {"isViewMode" : element.isProductVew, "isAdmin" : element.isSuper})
                }
            }

            UiToggleBtn {
                id: btnLength
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Length")
            }

            UiToggleBtn {
                id: btnBelt
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Belt")
            }

            UiToggleBtn {
                id: btnGroup
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Group")
            }

            UiToggleBtn {
                id: btnWeight
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Weight")
            }

            UiToggleBtn {
                id: btnMetalSens
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Metal<br>senstivity")
            }

            UiToggleBtn {
                id: btnNGMotion
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("NG Motion")
            }

            UiToggleBtn {
                id: btnWCCarib
                Layout.fillHeight: true
                Layout.fillWidth: true
                textValue: qsTr("Dynamic<br>caribration")
            }

        }

        Rectangle {
            id: rectangle
            x: 240
            y: 100
            width: 1340
            height: 880
            color: "#ffffff"
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
