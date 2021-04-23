import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import EnumDef 1.0
import FontManager 1.0
import "../../control/"

Popup {
    id : dialog

    modal: true
    dim : false
    closePolicy: Popup.NoAutoClose

    contentHeight: 250; contentWidth: 600
    anchors.centerIn : Overlay.overlay
    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    background:  Rectangle
    {
        id: rectangle1
        radius: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#d9000000"
        border.width: 0
    }

    contentItem: Item{
        Item{
            anchors.top: parent.top; anchors.topMargin: 20; anchors.bottom: confirmBtn.top; anchors.bottomMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20

            BusyIndicator{
                id : busyIndi
                height: 50; width: 50
                anchors.verticalCenter: parent.verticalCenter; anchors.left:parent.left; anchors.leftMargin: 0;
            }

            UiLabelContent{
                id: textContent
                height: 100
                anchors.verticalCenter: parent.verticalCenter; anchors.left:busyIndi.right; anchors.leftMargin: 30; anchors.right: parent.right; anchors.rightMargin: 0

                textValue: qsTr("Zero adjustment is in progress.<br> Leave the weighing section empty.")
            }
        }

        UiButton{
            id :confirmBtn
            height: 80
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            textValue: qsTr("Confirm")

            onSignalEventClicked: {
                dialog.close()
            }
        }
    }
}
