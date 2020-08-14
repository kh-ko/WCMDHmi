import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import EnumDefine 1.0
import ViewManager 1.0
import MainViewModel 1.0
import "../../control/"

Item {

    property bool isUnderToOver     : true
    property bool isTotal           : true
    property bool isTotalSinceStart : true
    property int  lastNValue        : 999999

    signal signalEventClose()

    id : popup

    anchors.fill: parent
    visible: false

    MouseArea{
        anchors.fill: parent

        onClicked: {popup.visible = false}
    }

    Rectangle{
        anchors.fill: parent
        color : "#59000000"
    }

    UiPanel
    {
        id : panel
        width : 704
        height :520

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        type : EnumDefine.PANEL_TYPE_POPUP

        title : qsTr("Trends graph option")

        MouseArea{
            anchors.fill: parent

            onClicked: {}
        }

        UiRadioBtn{
            id: radioUnderToOver;
            width: 312
            height: 75
            anchors.top: panel.top
            anchors.topMargin: panel.titleHeight
            anchors.left: parent.left;
            anchors.leftMargin: 40;

            isSelect: popup.isUnderToOver
            textValue: qsTr("Under to over")

            onSignalEventClicked:{
                popup.isUnderToOver = true;
            }
        }

        UiRadioBtn{
            id: radioMinToMax;
            width: 312
            height: 75
            anchors.top: panel.top
            anchors.topMargin: panel.titleHeight
            anchors.left: radioUnderToOver.right;
            anchors.leftMargin: 0;

            isSelect: !popup.isUnderToOver
            textValue: qsTr("Min to max")

            onSignalEventClicked:{
                popup.isUnderToOver = false;
            }
        }

        UiDivider{id : divider01; height: 2; width: 664; anchors.top: radioUnderToOver.bottom; anchors.topMargin: 20; anchors.horizontalCenter: parent.horizontalCenter}

        UiRadioBtn{
            id: radioTotal;
            width: 312
            height: 75
            anchors.top: divider01.bottom
            anchors.topMargin: 20
            anchors.left: parent.left;
            anchors.leftMargin: 40;

            isSelect: popup.isTotal
            textValue: qsTr("Total")

            onSignalEventClicked:{
                popup.isTotal = true
            }
        }

        UiRadioBtn{
            id: radioTrade;
            width: 312
            height: 75
            anchors.top: divider01.bottom
            anchors.topMargin: 20
            anchors.left: radioTotal.right;
            anchors.leftMargin: 0;

            isSelect: !popup.isTotal
            textValue: qsTr("Trade")

            onSignalEventClicked:{
                popup.isTotal = false
            }
        }

        UiDivider{id : divider02; height: 2; width: 664; anchors.top: radioTotal.bottom; anchors.topMargin: 20; anchors.horizontalCenter: parent.horizontalCenter}

        UiRadioBtn{
            id: radioTotalSinceStart;
            width: 312
            height: 75
            anchors.top: divider02.bottom
            anchors.topMargin: 20
            anchors.left: parent.left;
            anchors.leftMargin: 40;

            isSelect: popup.isTotalSinceStart
            textValue: qsTr("Total since start")

            onSignalEventClicked:{
                popup.isTotalSinceStart = true
            }
        }

        UiRadioBtn{
            id: radioLastN;
            width: 312
            height: 75
            anchors.top: divider02.bottom
            anchors.topMargin: 20
            anchors.left: radioTotalSinceStart.right;
            anchors.leftMargin: 0;

            isSelect: !popup.isTotalSinceStart
            textValue: qsTr("Last N")

            onSignalEventClicked:{
                popup.isTotalSinceStart = false
            }
        }

        UiInputNumber{
            id : inputLastNValue
            width: 150
            height: 75
            anchors.top: divider02.bottom
            anchors.topMargin: 20
            anchors.right: radioLastN.right;
            anchors.rightMargin: 0

            isHighlight  : false
            bgColor      : panel.bgColor
            isDisable    : false
            postfix      : ""
            fillZero     : ""
            isLocaleStyle: true
            numberValue  : popup.lastNValue
            min          : 0
            max          : 999999
            labelText   : ""
            inputWidth  : -1

            onSignalChangeValue: {
                popup.lastNValue = value
            }
        }

        UiButton{
            id: btnApply
            width : 322
            height: 96
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            type : EnumDefine.BUTTON_TYPE_BLUE
            textValue: qsTr("Apply")

            onSignalEventClicked: {
                signalEventClose();
                popup.visible = false;
            }
        }

        UiButton{
            id: btnCancle
            width : 322
            height: 96
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            type : EnumDefine.BUTTON_TYPE_POPUP
            textValue: qsTr("Cancle")

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
