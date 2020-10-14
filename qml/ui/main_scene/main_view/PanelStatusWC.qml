import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0

Item {
    property bool isDetail     : false
    property int  mdNGCnt      : 999999
    property int  wcNGCnt      : 999999
    property int  wcEtcMDErrCnt: 0
    property int  totalCnt     : 999999
    property var  tradeWeight  : 0
    property int  tradeCnt     : 0

    property string tradeWeightPostFix : panel.tradeWeight > 999999999 ? " t" :
                                         panel.tradeWeight > 999999    ? " kg": " g"
    property var convertedTradeWeight : panel.tradeWeight > 999999999 ? panel.tradeWeight /  1000000000:
                                        panel.tradeWeight > 999999    ? panel.tradeWeight /  1000000: panel.tradeWeight / 1000


    property bool isPress     : false

    signal signalEventClicked()

    id : panel

    width: 805
    height: 150

    UiPanel{
        id : bg
        anchors.fill: parent
        //type : EnumDefine.PANEL_TYPE_WEIGHT

        Image{
            id : imageTitle
            width: 50
            height: 50
            fillMode: Image.PreserveAspectFit
            source: isDetail? "img_btn/btn_statistics_s.png" : "img_btn/btn_statistics_n.png"
            anchors.verticalCenterOffset: 0
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

        }


        UiLabelSystem{
            id : labelTotal
            width : 132
            height : 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: imageTitle.right
            anchors.leftMargin: 20

            textValue: qsTr("Total")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelTotal.right
            anchors.leftMargin: 20
            anchors.right: divider.left
            anchors.rightMargin: 20
            anchors.verticalCenter: labelTotal.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : panel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }


        UiLabelSystem{
            id : labelMDNG
            width : 132
            height : 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: imageTitle.right
            anchors.leftMargin: 20

            textValue: qsTr("Metal NG")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelMDNG.right
            anchors.leftMargin: 20
            anchors.right: divider.left
            anchors.rightMargin: 20
            anchors.verticalCenter: labelMDNG.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : panel.mdNGCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }

        UiLabelSystem{
            id : labelWCNG
            width : 132
            height : 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: imageTitle.right
            anchors.leftMargin: 20

            textValue: qsTr("Weight NG")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelWCNG.right
            anchors.leftMargin: 20
            anchors.right: divider.left
            anchors.rightMargin: 20
            anchors.verticalCenter: labelWCNG.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : (panel.wcNGCnt - panel.wcEtcMDErrCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }


        UiDivider{
            id :divider
            width: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20

        }

        UiLabelSystem{
            id : labelTradeTotal
            width : 167
            height : 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: divider.right
            anchors.leftMargin: 20

            textValue: qsTr("Trade total")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelTradeTotal.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: labelTradeTotal.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : convertedTradeWeight.toLocaleString(ViewManager.locale, 'f', 1) + tradeWeightPostFix
        }

        UiLabelSystem{
            id : labelTradeAverage
            width : 167
            height : 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: divider.right
            anchors.leftMargin: 20

            textValue: qsTr("Trade average")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelTradeAverage.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: labelTradeAverage.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : tradeCnt === 0 ? "0.0 g" : ((tradeWeight/tradeCnt)/1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
        }

    }

    Rectangle{
        anchors.fill: parent
        radius: 10
        visible: panel.isPress ? true : false

        color : "#59000000"
    }

    MouseArea{
        anchors.fill: parent

        onPressed : { panel.isPress = true;}
        onReleased: { panel.isPress = false;}
        onClicked : { panel.signalEventClicked()}
    }
}



