import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0
import MainViewModel 1.0

Item {

    signal signalEventClickedProductName()
    signal signalEventClickedLastError()

    id: element
    width: 1759
    height: 997


    Component.onCompleted: {
        console.debug("[MainView.qml] : Create");
    }

    Component.onDestruction:
    {
        console.debug("[MainView.qml] : Destruct");
    }

    MainViewModel
    {
        id:model

        onSignalEventNotifyWCNG :
        {
            notifyWCNG.show(value, eventType)
        }

        onSignalEventNotifyMDDetect:
        {
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
            ViewManager.mainScene.moveProductView();
        }
    }

    PanelStatusWC{
        id: panelWCStatus
        width: 805
        height: 150
        anchors.left: panelProductName.right
        anchors.leftMargin: 10

        isDetail    : model.isDetail
        mdNGCnt     : model.mdDetectCnt
        wcNGCnt     : model.wcNGCnt
        totalCnt    : model.wcTotalCnt
        tradeCnt    : model.wcTradeCnt
        tradeWeight : model.wcTradeTotalWeight

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
            if(model.lastErrorType === EnumDefine.METAL_DETECT_TYPE)
                ViewManager.mainScene.moveLoggingDataView(EnumDefine.DEVICE_METAL_DETECTOR);
            else if (model.lastErrorType === EnumDefine.WEIGHT_OVER_TYPE || model.lastErrorType === EnumDefine.WEIGHT_UNDER_TYPE || model.lastErrorType === EnumDefine.WEIGHT_ETCERROR_TYPE || model.lastErrorType === EnumDefine.WEIGHT_ETC_METAL_ERROR_TYPE)
                ViewManager.mainScene.moveLoggingDataView(EnumDefine.DEVICE_WEIGHT_CHECKER);
        }
    }



    PanelMD{
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
        total  : model.wcTotalCnt
        detect : model.mdDetectCnt

        PanelMDDetectNotify{
            id : notifyMDDetect
        }

        onSignalEditMDSetting :
        {
            ViewManager.mainScene.showMDSetting()
        }

    }

    PanelWC{
        id: panelWeightChecker
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: panelProductName.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: panelMetalDetector.right
        anchors.leftMargin: 10

        isDetail           : model.isDetail
        currWeight         : model.wcCurrWeight
        currEventType      : model.wcCurrEventType
        avgWeight          : model.wcCurrAvgWeight
        avgEventType       : model.wcCurrAvgEventType
        totalCnt           : model.wcTotalCnt
        tradeCnt           : model.wcTradeCnt
        overCnt            : model.wcOverCnt
        underCnt           : model.wcUnderCnt
        normalCnt          : model.wcNormalCnt
        underWarningCnt    : model.wcUnderWarningCnt
        overWarningCnt     : model.wcOverWarningCnt
        overWeight         : model.wcOverWeight
        underWeight        : model.wcUnderWeight
        normalWeight       : model.wcNormalWeight
        underWarningWeight : model.wcUnderWarningWeight
        overWarningWeight  : model.wcOverWarningWeight
        etcErrorCnt        : model.wcEtcErrorCnt
        tradeWeight        : model.wcTradeTotalWeight
        tare               : model.wcTareWeight
        averageNValue      : model.wcAverageN
        mainViewModel      : model

        PanelWCNGNotify{
            id : notifyWCNG
        }

        onSignalEditWCSetting :
        {

                ViewManager.mainScene.showWCSetting()

        }
    }
}







/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:2;anchors_width:591}D{i:4;anchors_width:430}
}
##^##*/
