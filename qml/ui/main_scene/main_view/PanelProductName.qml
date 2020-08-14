import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0

Item {
    property string productName: "일이삼사오륙칠팔구십일이삼사오"
    property int productNo : 1
    property int totalCnt  : 999999
    property int metalNGCnt : 999999
    property int weightNGCnt : 999999

    signal signalEventClickedProductName()

    width:760
    height: 150

    id : panel

    UiPanel{
        id : bg
        width: 1500
        anchors.fill: parent
        title: qsTr("Product")

        UiLabelContentBig{
            id : labelTitle
            height: 168
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: parent.titleHeight
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            textValue: ("000" + panel.productNo).slice(-3) + "  " + productName
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                panel.signalEventClickedProductName();
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
