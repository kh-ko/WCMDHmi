import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0
import SearchDspDlgModel 1.0

Popup {

    id: dialog
    modal: true
    dim : true
    closePolicy: Popup.CloseOnPressOutside
    anchors.centerIn : Overlay.overlay
    contentHeight: 700; contentWidth: 600
    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    signal signalEventSelectIp(string ip)

    contentItem: UiPanel{
        id :panel

        UiButton{
            id : closeBtn
            height: 60
            width: 180
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

        ListView{
            id : listView
            clip: true
            anchors.top :closeBtn.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 20

            spacing: 20
            model: listModel

            delegate: UiPanel
            {
                id : ipItem

                height : 80
                width  : parent.width
                type   : mouseArea.isPress ? QmlEnumDef.PANEL_TYPE_SELECT : QmlEnumDef.PANEL_TYPE_UP_PANEL

                MouseArea{
                    property bool isPress : false

                    id : mouseArea
                    anchors.fill: parent
                    hoverEnabled: true

                    onContainsMouseChanged:
                    {
                        if(!containsMouse)
                            isPress = false
                    }

                    onPressed:
                    {
                        isPress = true
                    }

                    onReleased: {
                        isPress = false
                    }

                    onClicked:
                    {
                        dialog.signalEventSelectIp(ip)
                        dialog.close();
                    }
                }

                UiLabelContent{
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter

                    textValue: ip
                }
            }

            ListModel{
                id: listModel
            }
        }
    }

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        dialog.destroy();

        console.debug("destory");
    }

    SearchDspDlgModel{
        id : searchModel

        onSignalEventAddedIp: {
            listModel.append({"ip":ip})
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
