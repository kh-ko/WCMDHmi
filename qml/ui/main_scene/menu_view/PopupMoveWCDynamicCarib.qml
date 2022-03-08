import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import MainViewModel 1.0
import "../../../control/"

Item {
    signal signalEventMove()

    id : popup

    anchors.fill: parent
    visible: false

    MouseArea{
        anchors.fill: parent
    }

    Rectangle{
        anchors.fill: parent
        color : "#59000000"
    }

    UiPanel
    {
        id : panel
        width : 704
        height :400

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        type : QmlEnumDef.PANEL_TYPE_POPUP

        MouseArea{
            anchors.fill: parent

            onClicked: {}
        }


        Item{
            anchors.top: parent.top; anchors.topMargin: 20; anchors.bottom: btnYes.top; anchors.bottomMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20

            UiLabelContent{
                width : parent.width; height: parent.height / 2

                horizontalAlignment : Text.AlignHCenter
                textValue: qsTr("A new product has been added.")
            }

            UiLabelContent{
                id: textContent
                width : parent.width; height: parent.height / 2
                anchors.bottom: parent.bottom
                horizontalAlignment : Text.AlignHCenter
                textValue: qsTr("Do you want to perform dynamic caribration?")
            }
        }

        UiButton{
            id: btnYes
            width : 322
            height: 96
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_BLUE
            textValue: qsTr("Yes")

            onSignalEventClicked: {
                popup.signalEventMove();
                popup.visible = false;
            }
        }

        UiButton{
            id: btnNo
            width : 322
            height: 96
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_POPUP
            textValue: qsTr("No")

            onSignalEventClicked: {
                popup.visible = false;
            }
        }
    }
}

/*##^##
Designer {
    D{i:15;anchors_width:183;anchors_x:537}D{i:3;anchors_height:100;anchors_width:100}
}
##^##*/
