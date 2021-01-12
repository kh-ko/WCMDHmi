import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ViewManager 1.0
import FontManager 1.0
import EnumDef 1.0
import QmlEnumDef 1.0
import "."
import "../../control/"
import PanelGroupSettingInHomeModel 1.0

Rectangle {
    signal signalEventClose()

    id: panel
    color : "#33ffffff"
    visible: false

    function close()
    {
        panel.visible = false
    }

    function show()
    {
        model.onCommandReload()
        panel.visible = true;
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            close()
        }
    }

    PanelGroupSettingInHomeModel{
        id : model

        onSignalEventResultSaveGroupSetting:
        {
            if(error == EnumDef.PDERR_NONE)
            {
                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
            else if(error === EnumDef.PDERR_NOT_EXIST)
            {
                ViewManager.toast.show(qsTr("This product dose not exist."))
            }
            else if(error === EnumDef.PDERR_SAME_PD_NUM)
            {
                ViewManager.toast.show(qsTr("The Product no already exists."))
            }
            else if(error === EnumDef.PDERR_SELECTED)
            {
                ViewManager.toast.show(qsTr("Can not remove selected product."))
            }
            else
            {
                ViewManager.toast.show(qsTr("SQL error is occured."))
            }
        }
    }

    UiPanel {
        id: uiPanel

        width : 700
        height : 400
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        title: qsTr("Group setting")

        type : QmlEnumDef.PANEL_TYPE_POPUP

        MouseArea{
            anchors.fill: parent
            onClicked: {}
        }

        UiButton{
            id :btnApply
            height: 80
            textValue: qsTr("Apply")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: btnClose.left
            anchors.rightMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_BLUE

            visible: model.mIsEditGroupCount

            onSignalEventClicked: {
                model.onCommandApply()
            }
        }

        UiButton{
            id :btnClose
            height: 80
            textValue: qsTr("Close")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_POPUP

            onSignalEventClicked: {
                close()

            }
        }

        UiInputNumber {
            id: inputGroupCount
            width: 400
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            bgColor : uiPanel.bgColor
            inputWidth: 190
            labelText: qsTr("· Target count")
            postfix: ""
            min: 0
            max: 999999

            numberValue: model.mGroupCount
            isHighlight: model.mIsEditGroupCount

            onSignalChangeValue: {
                model.onCommandSetGroupCount(value)
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
