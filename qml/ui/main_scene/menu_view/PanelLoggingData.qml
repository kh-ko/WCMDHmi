import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./LoggingData"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import LoggingDataModel 1.0

UiPanel {
    property int selDevice : EnumDefine.DEVICE_METAL_DETECTOR // isWeightChecker
    property bool isViewMode : false
    property bool isAdmin : false
    title: selDevice == EnumDefine.DEVICE_METAL_DETECTOR ? qsTr("Metal detector") : qsTr("Weight checker")

    id : panel

    width : 1518
    height: 987

    Component.onCompleted: {
        if(panel.isViewMode)
        {
            loggingDataModel.onCommandSearch()
        }
    }

    LoggingDataModel{
        id : loggingDataModel
        isWeightEvent: panel.selDevice == EnumDefine.DEVICE_WEIGHT_CHECKER

        onSignalEventCompletedSearch: {

            listModel.clear()

            for(var i = 0; i < loggingDataModel.onCommandGetListCnt(); i ++)
            {
                listModel.append({"dataIdx" : i})
            }
        }
    }


    UiButton{
        id : btnBackup
        width: 164
        height: 80
        anchors.topMargin: 20
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: !panel.isViewMode
        textValue: qsTr("Backup")

        onSignalEventClicked: {
            ViewManager.mainScene.backupData();
        }
    }

    UiButtonConfirm
    {
        id : btnStatisticsInit
        width: 164
        height: 80
        anchors.verticalCenter: btnBackup.verticalCenter
        anchors.right: btnBackup.left
        anchors.rightMargin: 20

        visible: !panel.isViewMode
        textValue: qsTr("D/P count<br>reset")
        textConfirmMsg: qsTr("Do you want to reset display count?")

        onSignalEventClicked: {
            loggingDataModel.onCommandResetStatistics()
        }
    }

    UiButtonConfirm
    {
        id : btnLogginDataReset
        width: 164
        height: 80
        anchors.verticalCenter: btnStatisticsInit.verticalCenter
        anchors.right: btnStatisticsInit.left
        anchors.rightMargin: 20

        visible: !panel.isViewMode && panel.isAdmin
        textValue: qsTr("Logging<br>reset")
        textConfirmMsg: qsTr("Do you want to reset logging data?")

        onSignalEventClicked: {
            ViewManager.mainScene.factoryReset(true);
        }
    }

    UiComboBox{
        id : comboDate
        z : 2
        height: 60
        anchors.topMargin: 115
        width : 270
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top

        bgColor: panel.bgColor
        selIdx: loggingDataModel.selectOption
        listModel: comboDateOption

        ListModel{
            id : comboDateOption

            ListElement {
                itemText : qsTr("Today")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Period")
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            loggingDataModel.onCommandSetSelectOption(itemIdx)
        }
    }

    UiInputDate
    {
        id : inputStartDate

        width: 439
        anchors.left: comboDate.right
        anchors.leftMargin: 20
        anchors.verticalCenter: comboDate.verticalCenter

        isDisable: loggingDataModel.selectOption == EnumDefine.SEARCH_OPTION_TODAY
        year : loggingDataModel.startYear
        month : loggingDataModel.startMonth
        day : loggingDataModel.startDay
        hour : loggingDataModel.startHour

        onSignalEventChangedDate:
        {
            loggingDataModel.onCommandSetStartDate(year, month, day, hour)
        }
    }

    UiLabelSystem
    {
        id: labelFromTo
        width : 20
        height: 60
        anchors.verticalCenter: inputStartDate.verticalCenter
        anchors.left: inputStartDate.right
        anchors.leftMargin: 20

        textValue: "~"
    }

    UiInputDate {
        id: inputEndDate
        width: 439
        anchors.leftMargin: 20
        anchors.verticalCenter: labelFromTo.verticalCenter
        anchors.left: labelFromTo.right

        isDisable: loggingDataModel.selectOption == EnumDefine.SEARCH_OPTION_TODAY
        year : loggingDataModel.endYear
        month : loggingDataModel.endMonth
        day : loggingDataModel.endDay
        hour : loggingDataModel.endHour
        onSignalEventChangedDate:
        {
            loggingDataModel.onCommandSetEndDate(year, month, day, hour)
        }
    }

    UiButton{
        id: btnSearch
        width: 164
        height: 60
        anchors.right: parent.right
        anchors.rightMargin: 20
        textValue: qsTr("Search")
        anchors.verticalCenter: inputEndDate.verticalCenter

        onSignalEventClicked: {
            loggingDataModel.onCommandSearch()
        }

    }

    UiComboBox {
        id: comboFilter
        width: 270
        height: 60
        z: 1
        anchors.topMargin: 20
        anchors.top: comboDate.bottom
        anchors.leftMargin: 20
        anchors.left: parent.left

        bgColor: panel.bgColor
        selIdx: loggingDataModel.selectFilter
        listModel: comboFilterOption
        ListModel {
            id : comboFilterOption
            ListElement {
                itemText : qsTr("Without Trade")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Total")
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            loggingDataModel.onCommandSetSelectFilter(itemIdx)
        }
    }

    UiLabelContent{
        id: labelTotalCount

        height: 40
        width: 300
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: divider.top
        anchors.bottomMargin: 10
        horizontalAlignment : Text.AlignRight

        textValue: qsTr("Total count : ") + loggingDataModel.totalCnt.toLocaleString(ViewManager.locale, 'f', 0)
    }

    UiDivider{
        id : divider
        height: 2
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: comboFilter.bottom
        anchors.topMargin: 20
    }

    RowLayout{
        id : title
        height: 80
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: divider.bottom
        anchors.topMargin: 0

        spacing: 0

        UiLabelSystem{
            Layout.preferredWidth: 403
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: qsTr("Datetime")
        }

        UiLabelSystem{
            Layout.preferredWidth: 472
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: qsTr("Product")
        }

        UiLabelSystem{
            Layout.preferredWidth: 434
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: qsTr("Event")
        }

        UiLabelSystem{
            Layout.preferredWidth: 169
            Layout.fillHeight: true
            Layout.fillWidth: true

            textValue: qsTr("Value")

            //visible: panel.selDevice == EnumDefine.DEVICE_WEIGHT_CHECKER
        }
    }
    UiDivider{
        height: 2
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: title.bottom
        anchors.topMargin: 0
    }

    ListView {
        id: loggingDataList

        anchors.top: title.bottom
        anchors.topMargin: 2
        anchors.bottom: pageController.top
        anchors.bottomMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        model: listModel
        clip: true

        delegate: LoggingDataListItem
        {
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            height : 40

            isWeightColumVisible : panel.selDevice == EnumDefine.DEVICE_WEIGHT_CHECKER
            model : loggingDataModel
            idx   : dataIdx
        }

        ListModel{
            id: listModel
        }
    }

    UiDivider{
        height: 2
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: pageController.top
        anchors.topMargin: 0
    }

    LoggingDataPageController{
        id: pageController
        height: 80
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        totalPageCnt : loggingDataModel.totalPage
        currentPageIdx : loggingDataModel.currentPageIdx

        onSignalEventMovePage: {
            loggingDataModel.onCommandMovePage(pageIdx)
        }
    }

    Item{
        id : busyIndi
        visible : loggingDataModel.searching
        anchors.fill: parent

        BusyIndicator
        {
            width: 500
            height: 500
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {}
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
