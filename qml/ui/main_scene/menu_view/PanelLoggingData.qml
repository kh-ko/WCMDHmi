import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import "./LoggingData"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import LoggingDataModel 1.0

UiPanel {
    property var  isWCEnable
    property var  isMDEnable
    property bool isViewMode : false
    property bool isAdmin : false
    property var  selectDevice : isWCEnable === true && isMDEnable === false ? QmlEnumDef.DEVICE_WEIGHT_CHECKER : ViewManager.mainScene.selDevLoggingMenu
    id : panel

    width : 1518
    height: 987

    Component.onCompleted: {
        loggingDataModel.onCommandSetSelectDevice(panel.selectDevice)
        loggingDataModel.onCommandSearch()
    }

    LoggingDataModel{
        id : loggingDataModel

        onSignalEventCompletedSearch: {

            listModel.clear()

            for(var i = 0; i < loggingDataModel.onCommandGetListCnt(); i ++)
            {
                listModel.append({"dataIdx" : i})
            }
        }
    }

    UiComboBox {
        id: comboSelDev
        z : 2
        height: 60
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width : 300

        bgColor: panel.bgColor
        selIdx: panel.selectDevice
        listModel: comboSelDevOption
        visible: panel.isWCEnable && panel.isMDEnable

        ListModel {
            id : comboSelDevOption
            ListElement {
                itemText : qsTr("Metal detector")
                itemIdx : 0
            }
            ListElement {
                itemText : qsTr("Weight checker")
                itemIdx : 1
            }
        }

        onSignalEventChangedSel: {
            ViewManager.mainScene.selDevLoggingMenu = itemIdx
            loggingDataModel.onCommandSetSelectDevice(panel.selectDevice)
            loggingDataModel.onCommandSearch();
        }
    }

    UiComboBox {
        id: comboFilter
        z : 1
        height: 60
        width : 300
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: btnBackup.verticalCenter

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
            loggingDataModel.onCommandSearch();
        }
    }

    UiInputDate
    {
        id : inputStartDate

        width: 337
        height: 60
        anchors.left: comboFilter.right
        anchors.leftMargin: 20
        anchors.verticalCenter: btnBackup.verticalCenter

        //isDisable: true
        isCalendarMode: true
        isHourMode : false//isDisable: loggingDataModel.selectOption == EnumDefine.SEARCH_OPTION_TODAY
        year : loggingDataModel.startYear
        month : loggingDataModel.startMonth
        day : loggingDataModel.startDay
        //hour : loggingDataModel.startHour
         //
        onSignalEventChangedDate:
        {
            loggingDataModel.onCommandSetStartDate(year, month, day)
        }
    }

    UiButton{
        id: btnSearch
        width: 164
        height: 80
        anchors.left: inputStartDate.right
        anchors.leftMargin: 20
        anchors.verticalCenter: btnBackup.verticalCenter

        textValue: qsTr("Search")

        onSignalEventClicked: {
            loggingDataModel.onCommandSearch()
            //calendar.visible = true;
        }
    }

    UiButtonConfirm
    {
        id : btnLogginDataReset
        width: 164
        height: 80
        anchors.verticalCenter: btnBackup.verticalCenter
        anchors.right: btnStatisticsInit.left
        anchors.rightMargin: 20

        visible: !panel.isViewMode && panel.isAdmin
        textValue: qsTr("Logging<br>reset")
        textConfirmMsg: qsTr("Do you want to reset logging data?")

        onSignalEventClicked: {
            ViewManager.mainScene.factoryReset(true);
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

    UiButton{
        id : btnBackup
        width: 164
        height: 80
        anchors.top: comboSelDev.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        visible: !panel.isViewMode
        textValue: qsTr("Backup")

        onSignalEventClicked: {
            ViewManager.mainScene.backupData();
        }
    }

    UiLabelContent{
        id: labelTotalCount

        height: 40
        width: 300
        anchors.top: btnBackup.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

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
        anchors.top: labelTotalCount.bottom
        anchors.topMargin: 10
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

            isWeightColumVisible : loggingDataModel.selectDevice === QmlEnumDef.DEVICE_WEIGHT_CHECKER
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
   /*
    MouseArea{
        id: mouseArea00
        anchors.fill: calendar
        //hoverEnabled: true
        propagateComposedEvents: true
        //onHoveredChanged: {console.debug("" + containsMouse)}
        onContainsMouseChanged: {
            console.debug("" + containsMouse)
        }
    }


    UiCalendar{
        id : calendar
        width: 500
        height: 500
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        visible: false

        onPressed: {}
        onClicked: {
            loggingDataModel.onCommandSetStartDate(date.getFullYear(), date.getMonth() + 1 , date.getDate())
            loggingDataModel.onCommandSearch();
            calendar.visible = false
        }
    }*/

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
