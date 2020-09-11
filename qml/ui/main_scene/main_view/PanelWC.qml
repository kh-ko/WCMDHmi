import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0
import MainViewModel 1.0
import FontManager 1.0

Item {
    property int  currWeight        : 9199000
    property int  currEventType     : EnumDefine.WEIGHT_OVER_TYPE
    //property int  avgWeight         : 9199000
    //property int  avgEventType      : EnumDefine.WEIGHT_OVER_TYPE
    property int  totalCnt          : 999999
    property int  tradeCnt          : 999999
    property int  overCnt           : 999999
    property int  underCnt          : 999999
    property int  normalCnt         : 999999
    property int  underWarningCnt   : 999999
    property int  overWarningCnt    : 999999
    property int  overWeight        : 999999
    property int  underWeight       : 999999
    property int  normalWeight      : 999999
    property int  underWarningWeight: 999999
    property int  overWarningWeight : 999999
    property int  etcErrorCnt       : 999999
    property var  tradeWeight       : 10000000000000
    property real tare              :  10999900
    //property int  averageNValue     : 10000
    property int  lastNValue        : 1000
    property MainViewModel  mainViewModel
    property bool isDetail : false

    signal signalEvnetZeroClicked()
    signal signalEditWCSetting()

    id : panel

    width : 1503
    height: 837

    Component.onCompleted: {
        if(panel.isDetail)
        {
            panelStatistics.height = 235;
        }
        else
        {
            panelStatistics.height = 120;
        }

        trans.enabled = true
    }

    states: State
    {
        name: "detail"
        when: panel.isDetail
        PropertyChanges { target: panelStatistics; height : 235}
    }

    transitions: Transition
    {
        id : trans
        enabled : false
        from: ""
        to: "detail"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: panelStatistics; properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
        }
    }

    UiPanel{
        id: bg
        anchors.fill: parent

        type : EnumDefine.PANEL_TYPE_WEIGHT
        title: qsTr("Weight checker")

        UiButton{
            id:btnZero
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top : parent.top
            anchors.topMargin: 20
            width: 110
            height: 96
            textValue: qsTr("ZERO")

            onSignalEventClicked: {
                mainViewModel.onCommandSetZero()
            }
        }

        PanelWCViewMode{
            id : panelViewMode
            anchors.top: btnZero.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width : 110
            height : 352

            viewMode: mainViewModel.wcViewMode

            onSignalEventClickedDev: {
                mainViewModel.onCommandSetWCViewMode(EnumDefine.WC_VIEWMODE_DELTA)
            }

            onSignalEventClickedNumber: {
                mainViewModel.onCommandSetWCViewMode(EnumDefine.WC_VIEWMODE_CURRENT)
            }

            onSignalEventClickedTrends: {
                mainViewModel.onCommandSetWCViewMode(EnumDefine.WC_VIEWMODE_TRENDS)
            }
        }

        Text{
            id:labelCurrentWeight
            width: 330
            height: 55

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignRight
            font.pixelSize: 40
            font.family: FontManager.nanumGothicBName
            elide: Text.ElideRight

            visible: mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_TRENDS
            color : "#ACACAC"
            text: qsTr("Current weight")
            anchors.verticalCenter: textCurrentWeight.verticalCenter
            anchors.right: textCurrentWeight.left
            anchors.rightMargin: 20
        }

        Text{
            id:textCurrentWeight
            width: 270
            height: 55

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignRight
            font.pixelSize: 50
            font.family: FontManager.nanumGothicBName
            elide: Text.ElideRight

            visible: mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_TRENDS
            color : "#FFFFFF"
            text: (panel.currWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            anchors.horizontalCenterOffset: 60
            anchors.bottom: wcView.top
            anchors.bottomMargin: -20
            anchors.horizontalCenter: wcView.horizontalCenter
        }

        Image{
            width: 50
            height: 40
            anchors.verticalCenter: textTare.verticalCenter
            anchors.right: textTare.left
            anchors.rightMargin: 20

            source: "img_panelweightsimple/tare.png"

        }

        Text{
            id:textTare
            height: 55

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignRight
            font.pixelSize: 50
            font.family: FontManager.nanumGothicBName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: (panel.tare / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            anchors.bottom: wcView.top
            anchors.bottomMargin: -20
            anchors.right: wcView.right
            anchors.rightMargin: 20
        }

        Item{
            id : wcView
            anchors.top: parent.top
            anchors.topMargin: bg.titleHeight
            anchors.bottom: panelStatistics.top
            anchors.bottomMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: panelViewMode.left
            anchors.rightMargin: 70

            PanelSubWCSimple{
                anchors.fill: parent

                isWait        : mainViewModel.wait === 0 ? false : true
                visible       : mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_CURRENT || mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_DELTA
                isDevMode     : mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_DELTA
                currWeight    : panel.currWeight
                currEventType : panel.currEventType
                //avgWeight     : panel.avgWeight
                //avgEventType  : panel.avgEventType
                under         : panel.underWeight
                underWarning  : panel.underWarningWeight
                normal        : panel.normalWeight
                overWarning   : panel.overWarningWeight
                over          : panel.overWeight
                //averageNValue : panel.averageNValue

            }

            PanelSubWCTrends{
                anchors.fill: parent
                anchors.margins: 20

                visible     : mainViewModel.wcViewMode === EnumDefine.WC_VIEWMODE_TRENDS
                overWeight  : panel.overWeight
                underWeight : panel.underWeight
                normalWeight: panel.normalWeight
                lastNValue  : panel.lastNValue
                mainViewModel : panel.mainViewModel
            }
        }

        Item
        {
            id: panelStatistics
            height: 120
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            clip: true
            Item
            {
                id: element
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.right: statisticsEtc.left
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0


                UiStatistics{
                    id : statisticsUnder
                    //height: panel.isDetail ? 213 : 100
                    width: 233
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 20

                    isDetail      : panel.isDetail
                    imgSrc        : "img_panelevent/wc_down.png"
                    title         : qsTr("Under")
                    value01       : ""+ (panel.underWeight/1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                    total         : panel.totalCnt
                    value02       : panel.underCnt
                    bgColor       : "#59D9001B"
                    graphColor    : "#D9001B"

                    onSignalEventClicked: {
                        panel.signalEditWCSetting()
                    }
                }

                UiStatistics{
                    id : statisticsNormal
                    //height: panel.isDetail ? 213 : 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 233
                    anchors.top: parent.top
                    anchors.topMargin: 0

                    isDetail      : panel.isDetail
                    imgSrc        : "img_panelevent/wc_dose.png"
                    title         : qsTr("Normal")
                    value01       : ""+ (panel.normalWeight/1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                    total         : panel.totalCnt
                    value02       : panel.normalCnt
                    bgColor       : "#590085FF"
                    graphColor    : "#0085FF"

                    onSignalEventClicked: {
                        panel.signalEditWCSetting()
                    }
                }

                UiStatistics{
                    id : statisticsOver
                    //height: panel.isDetail ? 213 : 100
                    width: 233
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    isDetail      : panel.isDetail
                    imgSrc        : "img_panelevent/wc_up.png"
                    title         : qsTr("Over")
                    value01       : ""+ (panel.overWeight/1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
                    total         : panel.totalCnt
                    value02       : panel.overCnt
                    bgColor       : "#59F59A23"
                    graphColor    : "#F59A23"

                    onSignalEventClicked: {
                        panel.signalEditWCSetting()
                    }
                }

                /*
                UiLabelSystem{
                    id :labelTrade
                    width: 81
                    height: 30
                    textValue: qsTr("Trade")
                    anchors.left: divider.left
                    anchors.leftMargin: 0
                    anchors.bottom: divider.top
                    anchors.bottomMargin: 0

                }

                UiLabelContent{
                    id : textTradeCnt
                    width: 176
                    height: 30
                    anchors.verticalCenter: labelTrade.verticalCenter
                    textValue: panel.tradeCnt.toLocaleString(ViewManager.locale,'f', 0) + " pcs"
                    anchors.left: labelTrade.right
                    anchors.leftMargin: 0
                    anchors.bottom: divider.top
                    anchors.bottomMargin: 0

                    horizontalAlignment: Text.AlignRight
                }

                UiLabelContent{
                    property string tradeWeightPostFix : panel.tradeWeight > 999999999 ? " t" :
                                                         panel.tradeWeight > 999999    ? " kg": " g"
                    property var convertedTradeWeight : panel.tradeWeight > 999999999 ? panel.tradeWeight /  1000000000:
                                                        panel.tradeWeight > 999999    ? panel.tradeWeight /  1000000: panel.tradeWeight / 1000

                    id : textTradeWeight
                    width: 176
                    height: 30
                    anchors.verticalCenter: labelTrade.verticalCenter
                    textValue: convertedTradeWeight.toLocaleString(ViewManager.locale,'f', 1) + tradeWeightPostFix
                    anchors.left: textTradeCnt.right
                    anchors.leftMargin: 28
                    anchors.bottom: divider.top
                    anchors.bottomMargin: 0

                    horizontalAlignment: Text.AlignRight
                }

                UiLabelContent{
                    id : textTradePercent
                    width: 90
                    height: 30
                    anchors.verticalCenter: labelTrade.verticalCenter
                    textValue: ((panel.tradeCnt / panel.totalCnt) * 100).toLocaleString(ViewManager.locale,'f', 1) + " %"
                    anchors.left: textTradeWeight.right
                    anchors.leftMargin: 28
                    anchors.bottom: divider.top
                    anchors.bottomMargin: 0

                    horizontalAlignment: Text.AlignRight
                }


                UiLabelContent{
                    id : textMeanValue
                    width: 90
                    height: 30
                    anchors.verticalCenter: labelTrade.verticalCenter
                    textValue: ((panel.tradeWeight / panel.tradeCnt) / 1000).toLocaleString(ViewManager.locale,'f', 1) + " g/pcs"
                    anchors.left: textTradePercent.right
                    anchors.leftMargin: 28
                    anchors.right: divider.right
                    anchors.rightMargin: 0
                    anchors.bottom: divider.top
                    anchors.bottomMargin: 0

                    horizontalAlignment: Text.AlignRight
                }

                Rectangle{
                    id : divider
                    height: 2
                    width: 800
                    anchors.top: statisticsNormal.bottom
                    anchors.topMargin: 60
                    anchors.horizontalCenter: parent.horizontalCenter
                    color    : "#0085FF"
                }*/

            }

            UiStatistics{
                id : statisticsEtc
                //height: panel.isDetail ? 213 : 100
                width: 180
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 20

                isDetail      : panel.isDetail
                isIcon        : false
                imgSrc        : ""
                title         : qsTr("Etc")
                value01       : ""
                total         : panel.totalCnt
                value02       : panel.etcErrorCnt
                bgColor       : "#59000000"
                graphColor    : "#333333"

                onSignalEventClicked: {
                    panel.signalEditWCSetting()
                }
            }
        }

    }

/*
    Component.onCompleted: {
        if(isDetail)
        {
            panelWCSimple.width = bg.width * 0.6;
            panelWCSimple.height = (bg.height - bg.titleHeight) * 0.6;

        }

        trans.enabled = true
    }

    states: State
    {
        name: "detail"
        when: panel.isDetail
        PropertyChanges { target: panelWCSimple; width : bg.width * 0.6}
        PropertyChanges { target: panelWCSimple; height : (bg.height - bg.titleHeight) * 0.6}
    }

    transitions: Transition
    {
        id: trans

        enabled : false
        from: ""
        to: "detail"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: panelWCSimple; properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
            NumberAnimation { target: panelWCSimple; properties: "width"; duration: 250; easing.type: Easing.InOutQuad}
        }
    }

    UiPanel{
        id: bg
        anchors.fill: parent

        type : EnumDefine.PANEL_TYPE_WEIGHT
        clip: true
        title: qsTr("Weight checker")


        Item
        {
            id : panelWCSimple
            width: parent.width
            height : parent.height - bg.titleHeight
            anchors.top: parent.top
            anchors.topMargin: bg.titleHeight
            anchors.left: parent.left
            anchors.leftMargin: 0

            PanelSubWCSimple{
                width: bg.width
                height: bg.height - bg.titleHeight
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                scale: parent.width/bg.width

                currWeight    : panel.currWeight
                currEventType : panel.currEventType
                avgWeight     : panel.avgWeight
                avgEventType  : panel.avgEventType
                under         : panel.underWeight
                underWarning  : panel.underWarningWeight
                normal        : panel.normalWeight
                overWarning   : panel.overWarningWeight
                over          : panel.overWeight
                averageNValue : panel.averageNValue

            }

            Image{
                width: 30
                height: 25
                anchors.verticalCenter: btnZero.verticalCenter
                anchors.right: labelTare.left
                anchors.rightMargin: 0

                source: "img_panelweightsimple/tare.png"

            }

            UiLabelSystem{
                id : labelTare
                x: 1136
                height: 30
                width: 150
                anchors.verticalCenter: btnZero.verticalCenter
                anchors.right: btnZero.left
                anchors.rightMargin: 40

                horizontalAlignment : Text.AlignRight
                textValue: (panel.tare / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            }

            UiButton{
                id : btnZero
                height: 80
                width : 160
                textValue: qsTr("ZERO")
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.top: parent.top
                anchors.topMargin: 20 - bg.titleHeight

                type : EnumDefine.BUTTON_TYPE_BLUE

                onSignalEventClicked: {
                    mainViewModel.onCommandSetZero();
                }
            }
        }

        Item
        {
            id : panelWCTrendsGraph
            width: parent.width * 0.6
            height :  (bg.height - bg.titleHeight) * 0.4
            anchors.top: panelWCSimple.bottom
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            PanelSubWCTrends{
                anchors.fill: parent
                anchors.margins: 20

                isOpen      : panel.isDetail
                overWeight  : panel.overWeight
                underWeight : panel.underWeight
                normalWeight: panel.normalWeight
                lastNValue  : panel.lastNValue
                mainViewModel : panel.mainViewModel
            }
        }

        PanelSubWCDetail
        {
            id : panelWCDetailInfo
            anchors.top: parent.top
            anchors.topMargin: bg.titleHeight
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: panelWCSimple.right
            anchors.leftMargin: 0
            width: parent.width * 0.4

            totalCnt          : panel.totalCnt
            tradeCnt          : panel.tradeCnt
            overCnt           : panel.overCnt
            underCnt          : panel.underCnt
            normalCnt         : panel.normalCnt
            underWarningCnt   : panel.underWarningCnt
            overWarningCnt    : panel.overWarningCnt
            overWeight        : panel.overWeight
            underWeight       : panel.underWeight
            normalWeight      : panel.normalWeight
            underWarningWeight: panel.underWarningWeight
            overWarningWeight : panel.overWarningWeight
            etcErrorCnt       : panel.etcErrorCnt
            tradeWeight       : panel.tradeWeight
            tare              : panel.tare
        }
    }*/
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
