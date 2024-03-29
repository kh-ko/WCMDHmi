import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import ViewManager 1.0
import EnumDef 1.0

Item {
    property bool isEnableWC      : true
    property bool isEnableMD      : true
    property bool isDetail        : false
    property int  mdNGCnt         : 999999
    property int  wcNGCnt         : 999999
    property int  wcEtcMDErrCnt   : 0
    property int  totalCnt        : 999999
    property var  tradeWeight     : 0
    property int  tradeCnt        : 0
    property int  maxPdCntPerMin  : 0
    property int  currPdCntPerMin : 0
    property int  pdCntPerMin     : 0

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
            anchors.topMargin: panel.isEnableWC === false ? (parent.height - (height * 2)) / 3 :  20
            anchors.left: imageTitle.right
            anchors.leftMargin: panel.isEnableWC === false ? 100 :20

            customFontSize: ViewManager.language === EnumDef.LANG_CHN ? 35 : 25
            textValue: qsTr("Total")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelTotal.right
            anchors.leftMargin: 20
            anchors.right:  panel.isEnableWC === false ? parent.right : divider.left
            anchors.rightMargin: panel.isEnableWC === false ? 100 :20
            anchors.verticalCenter: labelTotal.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : panel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"
        }


        UiLabelSystem{
            id : labelMDNG
            width : 132
            height : 30
            anchors.top: panel.isEnableWC === false ? labelTotal.bottom : undefined
            anchors.topMargin : panel.isEnableWC === false ? (parent.height - (height * 2)) / 3 :  undefined
            anchors.verticalCenter: panel.isEnableWC === false ? undefined : parent.verticalCenter
            anchors.left: imageTitle.right
            anchors.leftMargin: panel.isEnableWC === false ? 100 :20

            customFontSize: ViewManager.language === EnumDef.LANG_CHN ? 35 : 25
            textValue: qsTr("Metal NG")

            visible: panel.isEnableMD
        }

        UiLabelContent{
            height : 30
            anchors.left: labelMDNG.right
            anchors.leftMargin: 20
            anchors.right:  panel.isEnableWC === false ? parent.right : divider.left
            anchors.rightMargin: panel.isEnableWC === false ? 100 :20
            anchors.verticalCenter: labelMDNG.verticalCenter

            horizontalAlignment : Text.AlignRight
            textValue : panel.mdNGCnt.toLocaleString(ViewManager.locale, 'f', 0) + " pcs"

            visible: panel.isEnableMD
        }

        UiLabelSystem{
            id : labelWCNG
            width : 132
            height : 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: imageTitle.right
            anchors.leftMargin: 20

            visible: panel.isEnableWC
            textValue: qsTr("Weight NG")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelWCNG.right
            anchors.leftMargin: 20
            anchors.right: divider.left
            anchors.rightMargin: 20
            anchors.verticalCenter: labelWCNG.verticalCenter

            visible: panel.isEnableWC
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

            visible: panel.isEnableWC
        }

        UiLabelSystem{
            id : labelMaxPPM
            width : 167
            height : 30
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: divider.right
            anchors.leftMargin: 20

            visible: panel.isEnableWC
            textValue: qsTr("Max")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelMaxPPM.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: labelMaxPPM.verticalCenter

            visible: panel.isEnableWC
            horizontalAlignment : Text.AlignRight
            //textValue : convertedTradeWeight.toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + tradeWeightPostFix
            textValue : maxPdCntPerMin + " ppm"
        }

        UiLabelSystem{
            id : labelActualPPM
            width : 167
            height : 30
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: divider.right
            anchors.leftMargin: 20

            visible: panel.isEnableWC
            textValue: qsTr("Actual")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelActualPPM.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: labelActualPPM.verticalCenter

            visible: panel.isEnableWC
            horizontalAlignment : Text.AlignRight
            //textValue : tradeCnt === 0 ? (0).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g" : ((tradeWeight/tradeCnt)/1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
            textValue: currPdCntPerMin + " ppm"
        }

        UiLabelSystem{
            id : labelAveragePPM
            width : 167
            height : 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: divider.right
            anchors.leftMargin: 20

            visible: panel.isEnableWC
            textValue: qsTr("Average")
        }

        UiLabelContent{
            height : 30
            anchors.left: labelAveragePPM.right
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: labelAveragePPM.verticalCenter

            visible: panel.isEnableWC
            horizontalAlignment : Text.AlignRight
            //textValue : tradeCnt === 0 ? (0).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g" : ((tradeWeight/tradeCnt)/1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
            textValue:  pdCntPerMin + " ppm"
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
        visible: panel.isEnableWC

        onPressed : { panel.isPress = true;}
        onReleased: { panel.isPress = false;}
        onClicked : { panel.signalEventClicked()}
    }
}



