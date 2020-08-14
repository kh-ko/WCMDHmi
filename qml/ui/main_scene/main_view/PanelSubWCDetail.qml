import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0

Item {

    property int totalCnt: 999999
    property int tradeCnt: 999999
    property int overCnt : 999999
    property int underCnt : 999999
    property int normalCnt : 999999
    property int underWarningCnt : 999999
    property int overWarningCnt : 999999
    property int overWeight : 999999
    property int underWeight : 999999
    property int normalWeight : 999999
    property int underWarningWeight : 999999
    property int overWarningWeight : 999999
    property int etcErrorCnt: 999999
    property var tradeWeight : 10000000000000
    property real tare :  10999900


    property string tradeWeightPostFix : tradeWeight > 999999999 ? " t" :
                                         tradeWeight > 999999    ? " kg": " g"
    property var convertedTradeWeight : tradeWeight > 999999999 ? tradeWeight /  1000000000:
                                        tradeWeight > 999999    ? tradeWeight /  1000000: tradeWeight / 1000

    id : panel
    width : 601
    height: 746

    UiLabelSystem{
        id: labelTotalCnt
        width: 105
        height: 45
        anchors.top : parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 20

        textValue: qsTr("Total")
    }

    UiLabelContent
    {
        id:valueTotalCnt
        width: 140
        height: 45
        anchors.right: parent.right
        anchors.rightMargin: 307
        anchors.verticalCenter: labelTotalCnt.verticalCenter
        horizontalAlignment:Text.AlignRight
        textValue:panel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
    }

    UiLabelSystem{
        id: labelTrade
        width: 105
        height: 45
        anchors.top : labelTotalCnt.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 20

        textValue: qsTr("Trade")
    }

    UiLabelContent
    {
        id:valueTradeCnt
        width: 140
        height: 45
        anchors.right: parent.right
        anchors.rightMargin: 307
        anchors.verticalCenter: labelTrade.verticalCenter
        horizontalAlignment:Text.AlignRight
        textValue:panel.tradeCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
    }

    UiLabelContent
    {
        id:valueTradeWeight
        width: 140
        height: 45
        anchors.right: parent.right
        anchors.rightMargin: 139
        anchors.verticalCenter: labelTrade.verticalCenter
        horizontalAlignment:Text.AlignRight
        textValue:panel.convertedTradeWeight.toLocaleString(ViewManager.locale, 'f', 1) + panel.tradeWeightPostFix
    }

    UiLabelContent
    {
        id:valueTradeRate
        width: 110
        height: 45
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: labelTrade.verticalCenter
        horizontalAlignment:Text.AlignRight
        textValue:panel.totalCnt < 1 ? "0.0 %" : ((panel.tradeCnt / panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 1) + " %"
    }

    UiLabelSystem{
        id: labelEtcErrorCnt
        width: 105
        height: 45
        anchors.top : labelTrade.bottom
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 20

        textValue: qsTr("Etc error")
    }

    UiLabelContent
    {
        id:valueEtcErrorCnt
        width: 140
        height: 45
        anchors.right: parent.right
        anchors.rightMargin: 307
        anchors.verticalCenter: labelEtcErrorCnt.verticalCenter
        horizontalAlignment:Text.AlignRight
        textValue:panel.etcErrorCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
    }

    Item
    {
        anchors.top: labelEtcErrorCnt.bottom
        anchors.topMargin: 0
        anchors.bottom: barOver.top
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0

        Item
        {
            height: 90
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            UiLabelSystem{
                id: labelMeanValue
                width: 250
                height: 45
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 20

                textValue: qsTr("Mean value trade")
            }

            UiLabelContent
            {
                id:valueMeanValue
                width: 140
                height: 45
                anchors.right: parent.right
                anchors.rightMargin: 139
                anchors.verticalCenter: labelMeanValue.verticalCenter
                horizontalAlignment:Text.AlignRight
                textValue:panel.tradeCnt < 1 ? "0 g" :((panel.tradeWeight / panel.tradeCnt)/ 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            }


            UiLabelSystem{
                id: labelTare
                width: 105
                height: 45
                anchors.top : labelMeanValue.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 20

                textValue: qsTr("Tare")
            }

            UiLabelContent
            {
                id:valueTare
                width: 140
                height: 45
                anchors.right: parent.right
                anchors.rightMargin: 139
                anchors.verticalCenter: labelTare.verticalCenter
                horizontalAlignment:Text.AlignRight
                textValue:((panel.tare) / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            }
        }
    }

    UiLabelContent
    {
        id:labelOverWeight
        width: 140
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: barOver.verticalCenter
        textValue:"99,999,9 g";//((panel.overWeight) / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g <"
    }

    UiProgressBar
    {
        id : barOver
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: barOverWarning.top
        anchors.bottomMargin: 20
        height: 51
        width : 401
        min   : 0
        max   : panel.totalCnt
        value : panel.overCnt
        barColor : "#D9001B"
        radius : 5
        UiLabelContent
        {
            id:rateOverWeight
            width: 110
            height: 51
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:totalCnt < 1 ? "0.0 %" : ((panel.overCnt / panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 1) + " %"
        }

        UiLabelContent
        {
            id:cntOverWeight
            width: 150
            height: 51
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:(panel.overCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }
    }

    UiLabelContent
    {
        id:labelOverWarningWeight
        width: 140
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: barOverWarning.verticalCenter
        textValue:((panel.overWarningWeight) / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g <"
    }

    UiProgressBar
    {
        id : barOverWarning
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: barNormal.top
        anchors.bottomMargin: 20
        height: 51
        width : 401
        min   : 0
        max   : panel.totalCnt
        value : panel.overWarningCnt
        barColor : "#F59A23"
        radius : 5

        UiLabelContent
        {
            id:rateOverWarningWeight
            width: 110
            height: 51
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:totalCnt < 1 ? "0.0 %" : ((panel.overWarningCnt / panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 1) + " %"
        }

        UiLabelContent
        {
            id:cntOverWarningWeight
            width: 150
            height: 51
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:(panel.overWarningCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }
    }

    UiLabelContent
    {
        id:labelNormalWeight
        width: 140
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: barNormal.verticalCenter
        textValue:"Normal"
    }

    UiProgressBar
    {
        id : barNormal
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: barUnderWarning.top
        anchors.bottomMargin: 20
        height: 51
        width : 401
        min   : 0
        max   : panel.totalCnt
        value : panel.normalCnt
        barColor : "#0085FF"
        radius : 5

        UiLabelContent
        {
            id:rateNormalWeight
            width: 110
            height: 51
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:totalCnt < 1 ? "0.0 %" : ((panel.normalCnt / panel.totalCnt) * 100).toLocaleString(ViewManager.locale, 'f', 1) + " %"
        }

        UiLabelContent
        {
            id:cntNormalWeight
            width: 150
            height: 51
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:(panel.normalCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }
    }

    UiLabelContent
    {
        id:labelUnderWarningWeight
        width: 140
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: barUnderWarning.verticalCenter
        textValue:((panel.underWarningWeight) / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g >"
    }

    UiProgressBar
    {
        id : barUnderWarning
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: barUnder.top
        anchors.bottomMargin: 20
        height: 51
        width : 401
        min   : 0
        max   : panel.totalCnt
        value : panel.underWarningCnt
        barColor : "#F59A23"
        radius : 5

        UiLabelContent
        {
            id:rateUnderWarningWeight
            width: 110
            height: 51
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:totalCnt < 1 ? "0.0 %" : ((panel.underWarningCnt / panel.totalCnt) * 100 ).toLocaleString(ViewManager.locale, 'f', 1) + " %"
        }

        UiLabelContent
        {
            id:cntUnderWarning
            width: 150
            height: 51
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:(panel.underWarningCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }
    }

    UiLabelContent
    {
        id:labelUnderWeight
        width: 140
        height: 45
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: barUnder.verticalCenter
        textValue:((panel.underWeight) / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g >"
    }

    UiProgressBar
    {
        id : barUnder
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        height: 51
        width : 401
        min   : 0
        max   : panel.totalCnt
        value : panel.underCnt
        barColor : "#D9001B"
        radius : 5

        UiLabelContent
        {
            id:rateUnderWeight
            width: 110
            height: 51
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:totalCnt < 1 ? "0.0 %" : ((panel.underCnt / panel.totalCnt) * 100 ).toLocaleString(ViewManager.locale, 'f', 1) + " %"
        }

        UiLabelContent
        {
            id:cntUnder
            width: 150
            height: 51
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment:Text.AlignRight
            textValue:(panel.underCnt).toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }
    }
}


