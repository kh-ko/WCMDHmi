import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "./"
import QmlEnumDef 1.0
import ViewManager 1.0
import PanelPDSelectModel 1.0

Dialog {
    property alias textColor : textContent.textColor
    property var message

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
        width: 700
        height: 400
        scale: ViewManager.scale

        UiLabelContent{
            id: textContent
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            anchors.topMargin: 40
            anchors.bottomMargin: 132
            anchors.fill: parent
            textValue: dialog.message

        }
        UiButton{
            height: 60
            width: 180
            textValue : qsTr("Confirm")
            type : QmlEnumDef.BUTTON_TYPE_BLUE
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            onSignalEventClicked: {
                dialog.close();
            }

        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
