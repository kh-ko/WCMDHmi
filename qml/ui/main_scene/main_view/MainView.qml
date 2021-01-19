import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import QmlEnumDef 1.0
import EnumDef 1.0
import ViewManager 1.0
import MainViewModel 1.0

Item {

    signal signalEventClickedProductName()
    signal signalEventClickedLastError()

    id: panel
    width: 1759
    height: 997


    Component.onCompleted: {
        console.debug("[MainView.qml] : Create");

        if(model.isEnableWC)
            panelWeightChecker.createObject(emptyArea, {"mainViewModel":model})
        else
            panelFullMD.createObject(emptyArea, {"mainViewModel":model})
    }

    Component.onDestruction:
    {
        console.debug("[MainView.qml] : Destruct");
    }

    MainViewModel
    {
        id:model

        onSignalEventNotifyMDDetect:
        {
            if(model.isEnableWC)
                notifyMDDetect.show()
        }
    }

    PanelProductName{
        id: panelProductName
        width: 680
        height: 150
        anchors.left: parent.left
        anchors.leftMargin: 0

        productNo: model.productNo
        productName: model.productName

        onSignalEventClickedProductName: {
            var dlg = panelProductSelect.createObject(panel, {"mainViewModel":model})
            dlg.open();
        }
    }

    PanelStatusWC{
        id: panelWCStatus
        width: 805
        height: 150
        anchors.left: panelProductName.right
        anchors.leftMargin: 10

        isDetail     : model.isDetail
        mdNGCnt      : model.mdDetectCnt
        wcEtcMDErrCnt: model.wCEtcMDErrorCnt
        wcNGCnt      : model.wcNGCnt
        totalCnt     : model.isEnableWC ? model.wcTotalCnt : model.mdTotalCnt
        tradeCnt     : model.wcTradeCnt
        tradeWeight  : model.wcTradeTotalWeight
        isEnableWC   : model.isEnableWC

        onSignalEventClicked :
        {
            model.onCommandSetIsDetail(!model.isDetail)
        }
    }


    PanelLastError{
        id: panelLastError
        height: 150
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: panelWCStatus.right
        anchors.leftMargin: 10

        errorTime          : model.lastErrorTime
        errorType          : model.lastErrorType
        errorValue         : model.lastErrorValue
        normalWeight       : model.wcNormalWeight
        senstivity         : model.mdSenstivity
        viewMode           : model.wcViewMode

        onSignalEventClickedLastError: {
            if(model.lastErrorType === EnumDef.ET_METAL_DETECT)
                ViewManager.mainScene.selDevLoggingMenu = QmlEnumDef.DEVICE_METAL_DETECTOR;
            else if(model.lastErrorType === EnumDef.ET_WEIGHT_ETCERROR || model.lastErrorType === EnumDef.ET_WEIGHT_UNDER || model.lastErrorType === EnumDef.ET_WEIGHT_OVER)
                ViewManager.mainScene.selDevLoggingMenu = QmlEnumDef.DEVICE_WEIGHT_CHECKER;

            if(model.isEnableWC == false)
                ViewManager.mainScene.selDevLoggingMenu = QmlEnumDef.DEVICE_METAL_DETECTOR;

            ViewManager.mainScene.moveLoggingDataView();
        }
    }



    PanelMD{
        property MainViewModel  mainViewModel
        id: panelMetalDetector
        width: 245
        anchors.top: panelProductName.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        isDetail: model.isDetail
        senstivity : model.mdSenstivity
        signal : model.mdCurrSignal
        total  : model.isEnableWC ? model.wcTotalCnt : model.mdTotalCnt
        detect : model.mdDetectCnt

        PanelMDDetectNotify{
            id : notifyMDDetect
        }

        onSignalEditMDSetting :
        {
            ViewManager.mainScene.showMDSetting()
        }
    }

    Item{
        id : emptyArea
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: panelProductName.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: panelMetalDetector.right
        anchors.leftMargin: 10
    }


    Component
    {
        id : panelFullMD

        PanelFullMD{
            anchors.fill: parent
        }
    }

    Component
    {
        id : panelWeightChecker

        PanelWC{
            anchors.fill: parent

            PanelWCNGNotify{
                id : notifyWCNG
            }

            onSignalEditWCSetting :
            {
                    ViewManager.mainScene.showWCSetting()
            }

            onSignalEditGroupSetting:
            {
                ViewManager.mainScene.showGroupSetting()
            }

            Connections{
                target: mainViewModel
                onSignalEventNotifyWCNG :
                {
                    if(mainViewModel.isEnableWC)
                        notifyWCNG.show(value, eventType)
                }
            }
        }
    }

    Component
    {
        id : panelProductSelect
        PanelProductSelect
        {

        }
    }
}







/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:2;anchors_width:591}D{i:4;anchors_width:430}
}
##^##*/
