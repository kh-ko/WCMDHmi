import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0

Item {
    property bool isProductVew : false
    property bool isLoggingVew : false
    property bool isSuper    : false
    property int  selDevice  : EnumDefine.DEVICE_WEIGHT_CHECKER
    property int  selMenu    : EnumDefine.MENU_PRODUCT_SETTING

    id: element

    width : 1769
    height: 997

    Component.onDestruction:
    {
        console.debug("[MenuView.qml] : Destruct");
    }

    Component.onCompleted: {

        console.debug("[MenuView.qml] : Create");

        switch(selMenu)
        {
            case EnumDefine.MENU_PRODUCT_SETTING:
                viewContainer.push(panelProductSetting, {"isViewMode" : element.isProductVew})
                break;
            case EnumDefine.MENU_LOGGING_DATA   :
                viewContainer.push(panelLoggingData, {"selDevice":element.selDevice, "isViewMode" : element.isLoggingVew, "isAdmin" : element.isSuper})
                break;
            case EnumDefine.MENU_DEVICE_SETTING :
                viewContainer.push(panelDeviceSetting,{"isAdmin":element.isSuper})
                break;
            case EnumDefine.MENU_INFORMATION    :
                viewContainer.push(panelInformation, {"isAdmin":element.isSuper})
                break;
            case EnumDefine.MENU_GRAPH          :
                if(selDevice == EnumDefine.DEVICE_METAL_DETECTOR)
                {
                    viewContainer.push(panelMDGraph)
                }
                else
                {
                    viewContainer.push(panelWCGraph)
                }
                break;
            case EnumDefine.MENU_ETC_SETTING    :
                //viewContainer.push(panelEtcSetting)
                break;
            case EnumDefine.MENU_CLOCK_SETTING  :
                viewContainer.push(panelClockSetting)
                break;
        }
    }

    UiPanel
    {
        id : panelSelMenu
        width: 241
        anchors.left: parent.left
        anchors.leftMargin: -10
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        UiToggleBtn{
            id: btnProductSetting
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew
            textValue: qsTr("PRODUCT<br>SETTING")
            isOn : selMenu == EnumDefine.MENU_PRODUCT_SETTING

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_PRODUCT_SETTING)
                    return

                selMenu = EnumDefine.MENU_PRODUCT_SETTING

                viewContainer.clear()
                viewContainer.push(panelProductSetting)
            }
        }

        UiToggleBtn{
            id : btnLogging
            anchors.top: btnProductSetting.visible ? btnProductSetting.bottom : parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isProductVew
            textValue: qsTr("LOGGING<br>DATA")
            isOn : selMenu == EnumDefine.MENU_LOGGING_DATA

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_LOGGING_DATA)
                    return

                selMenu = EnumDefine.MENU_LOGGING_DATA

                viewContainer.clear()
                viewContainer.push(panelLoggingData,{"selDevice":element.selDevice, "isAdmin" : element.isSuper})
            }
        }

        UiToggleBtn{
            id : btnCalib
            anchors.top: btnLogging.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew && !element.isProductVew
            textValue: element.selDevice === EnumDefine.DEVICE_WEIGHT_CHECKER ? qsTr("CALIBRATION") : qsTr("CHECKUP")
            isOn : selMenu === EnumDefine.MENU_CHECK_UP

            onSignalEventClicked:
            {
                if(selMenu === EnumDefine.MENU_CHECK_UP)
                    return

                selMenu = EnumDefine.MENU_CHECK_UP

                viewContainer.clear()

                if(selDevice == EnumDefine.DEVICE_METAL_DETECTOR)
                    viewContainer.push(panelMDCheckup)
                else
                    viewContainer.push(panelWCCaribraion)

            }
        }

        UiToggleBtn{
            id : btnDeviceSetting
            anchors.top: btnCalib.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew && !element.isProductVew
            textValue: qsTr("DEVICE<br>SETTING")
            isOn : selMenu == EnumDefine.MENU_DEVICE_SETTING

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_DEVICE_SETTING)
                    return

                selMenu = EnumDefine.MENU_DEVICE_SETTING

                viewContainer.clear()
                viewContainer.push(panelDeviceSetting,{"isAdmin":element.isSuper})
            }

        }


        UiToggleBtn{
            id : btnGraph
            anchors.top: btnDeviceSetting.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew && !element.isProductVew && element.isSuper
            textValue: qsTr("GRAPH")
            isOn : selMenu == EnumDefine.MENU_GRAPH

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_GRAPH)
                    return

                selMenu = EnumDefine.MENU_GRAPH

                viewContainer.clear()

                if(selDevice == EnumDefine.DEVICE_METAL_DETECTOR)
                    viewContainer.push(panelMDGraph)
                else
                    viewContainer.push(panelWCGraph)
            }
        }

/*
        UiToggleBtn{
            textValue: qsTr("ETC<br>SETTING")
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            Layout.fillWidth: true

            isOn : selMenu == EnumDefine.MENU_ETC_SETTING

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_ETC_SETTING)
                    return

                selMenu = EnumDefine.MENU_ETC_SETTING

                viewContainer.clear()
                viewContainer.push(panelEtcSetting)
            }

        }
*/
        UiToggleBtn {
            id :btnClockSetting
            anchors.top: btnGraph.visible ? btnGraph.bottom : btnDeviceSetting.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew && !element.isProductVew
            textValue: qsTr("CLOCK<br>SETTING")
            isOn : selMenu == EnumDefine.MENU_CLOCK_SETTING

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_CLOCK_SETTING)
                    return

                selMenu = EnumDefine.MENU_CLOCK_SETTING

                viewContainer.clear()
                viewContainer.push(panelClockSetting)
            }
        }

        UiToggleBtn{
            id : btnInfo
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin : 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: (panelSelMenu.height - 160) / 7

            visible: !element.isLoggingVew && !element.isProductVew
            textValue: qsTr("INFORMATION")
            isOn : selMenu == EnumDefine.MENU_INFORMATION

            onSignalEventClicked:
            {
                if(selMenu == EnumDefine.MENU_INFORMATION)
                    return

                selMenu = EnumDefine.MENU_INFORMATION

                viewContainer.clear()
                viewContainer.push(panelInformation,{"isAdmin" : element.isSuper})
            }
        }
    }

    StackView
    {
        id: viewContainer
        anchors.left: panelSelMenu.right
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Component{ id : panelProductSetting; PanelProductSetting{anchors.fill: parent}}
    Component{ id : panelLoggingData;    PanelLoggingData   {anchors.fill: parent}}
    Component{ id : panelMDCheckup;      PanelMDCheckup     {anchors.fill: parent}}
    Component{ id : panelWCCaribraion;   PanelWCCaribration {anchors.fill: parent}}
    Component{ id : panelDeviceSetting;  PanelDeviceSetting {anchors.fill: parent}}
    Component{ id : panelInformation;    PanelInformation   {anchors.fill: parent}}
    Component{ id : panelWCGraph;        PanelWCGraph       {anchors.fill: parent}}
    Component{ id : panelMDGraph;        PanelMDGraph       {anchors.fill: parent}}
    //Component{ id : panelEtcSetting;     PanelEtcSetting    {anchors.fill: parent}}
    Component{ id : panelClockSetting;   PanelClockSetting  {anchors.fill: parent}}
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
