import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import QmlEnumDef 1.0
import ViewManager 1.0

Item {
    property int detectCnt : 0
    property int totalCnt :0

    id : panel

    width: 354
    height: 168

    UiPanel{
        id : bg
        anchors.fill: parent
        type : QmlEnumDef.PANEL_TYPE_METAL

        title: qsTr("Metal detector")

        Item
        {
            anchors.fill: parent
            anchors.topMargin: bg.titleHeight
            anchors.bottomMargin: 20
            anchors.leftMargin: 20
            anchors.rightMargin: 20

            UiLabelSystem{
                id : labelTrade
                width : 100
                height : 30
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                textValue: qsTr("Detect")
            }

            UiLabelContent{
                height : 30
                anchors.left: labelTrade.right
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: labelTrade.verticalCenter

                horizontalAlignment : Text.AlignRight
                textValue : panel.detectCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            }

            UiLabelSystem{
                id : labelTotal
                width : 100
                height : 30
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                textValue: qsTr("Total")
            }

            UiLabelContent{
                height : 30
                anchors.left: labelTotal.right
                anchors.leftMargin: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.verticalCenter: labelTotal.verticalCenter

                horizontalAlignment : Text.AlignRight
                textValue : panel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
            }
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.6600000262260437;height:480;width:640}
}
##^##*/
