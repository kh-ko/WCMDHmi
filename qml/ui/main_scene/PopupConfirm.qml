import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QmlEnumDef 1.0
import ViewManager 1.0
import FontManager 1.0
import MainViewModel 1.0
import "../../control/"

Rectangle {
    property UiButtonConfirm btn : null

    id: panel
    color: "#59000000"
    border.width: 0

    width: 1920
    height: 1080

    visible: false

    function show(button)
    {
        btn = button;
        textContent.textValue = button.textConfirmMsg;
        panel.visible = true;
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {}
    }

    Rectangle
    {
        id: rectangle1
        width: 700
        height: 400
        radius: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#d9000000"
        border.width: 0

        UiLabelContent{
            id: textContent
            anchors.rightMargin: 40
            anchors.leftMargin: 40
            anchors.topMargin: 40
            anchors.bottomMargin: 132
            anchors.fill: parent

        }

        UiButton{
            height: 80
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            textValue: qsTr("Yes")

            onSignalEventClicked: {
                btn.confirm();
                panel.visible = false;
            }
        }


        UiButton{
            height: 80
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            textValue: qsTr("Cancle")
            type : QmlEnumDef.BUTTON_TYPE_BLUE

            onSignalEventClicked:
            {
                panel.visible = false;
            }

        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
