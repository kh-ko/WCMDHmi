import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0

Item {
    property bool isProductVew : false
    property bool isLoggingVew : false
    property bool isSuper    : true
    property bool isWCEnable : true
    property bool isMDEnable : true
    property int  selDevice  : QmlEnumDef.DEVICE_WEIGHT_CHECKER
    property int  selMenu    : QmlEnumDef.MENU_PRODUCT_SETTING

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
            case QmlEnumDef.MENU_PRODUCT_SETTING:
                viewContainer.push(panelProductSetting, {"isViewMode" : element.isProductVew, "isAdmin" : element.isSuper})
                break;
            case QmlEnumDef.MENU_LOGGING_DATA   :
                viewContainer.push(panelLoggingData, {"isViewMode" : element.isLoggingVew, "isAdmin" : element.isSuper, "isWCEnable" : element.isWCEnable, "isMDEnable" : element.isMDEnable})
                break;
            case QmlEnumDef.MENU_DEVICE_SETTING :
                viewContainer.push(panelDeviceSetting,{"isAdmin":element.isSuper})
                break;
            case QmlEnumDef.MENU_INFORMATION    :
                viewContainer.push(panelInformation, {"isAdmin":element.isSuper})
                break;
            case QmlEnumDef.MENU_GRAPH          :
                 viewContainer.push(panelGraph, {"isWCEnable" : element.isWCEnable, "isMDEnable" : element.isMDEnable})
                break;
            case QmlEnumDef.MENU_ETC_SETTING    :
                //viewContainer.push(panelEtcSetting)
                break;
            case QmlEnumDef.MENU_CLOCK_SETTING  :
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

        ColumnLayout{
            anchors.top : parent.top
            anchors.topMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            spacing: 20

            UiToggleBtn{
                id: btnProductSetting
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: !element.isLoggingVew

                textValue: qsTr("PRODUCT<br>SETTING")
                isOn : selMenu == QmlEnumDef.MENU_PRODUCT_SETTING

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_PRODUCT_SETTING)
                        return

                    selMenu = QmlEnumDef.MENU_PRODUCT_SETTING

                    viewContainer.clear()
                    viewContainer.push(panelProductSetting, {"isViewMode" : element.isProductVew, "isAdmin" : element.isSuper})
                }
            }

            UiToggleBtn{
                id : btnLogging
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isProductVew
                textValue: qsTr("LOGGING<br>DATA")
                isOn : selMenu == QmlEnumDef.MENU_LOGGING_DATA

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_LOGGING_DATA)
                        return

                    selMenu = QmlEnumDef.MENU_LOGGING_DATA

                    viewContainer.clear()
                    viewContainer.push(panelLoggingData,{"isAdmin" : element.isSuper, "isWCEnable" : element.isWCEnable, "isMDEnable" : element.isMDEnable})
                }
            }

            UiToggleBtn{
                id : btnCalib
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew
                textValue: element.isWCEnable == true ? qsTr("CALIBRATION<br>/ CHECKUP") :  qsTr("CHECKUP")
                isOn : selMenu === QmlEnumDef.MENU_CHECK_UP

                onSignalEventClicked:
                {
                    if(selMenu === QmlEnumDef.MENU_CHECK_UP)
                        return

                    selMenu = QmlEnumDef.MENU_CHECK_UP

                    viewContainer.clear()
                    viewContainer.push(panelWCCaribMDCheckUp, {"isWCEnable" : element.isWCEnable, "isMDEnable" : element.isMDEnable})

                }
            }

            UiToggleBtn{
                id : btnMaxErr
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew && element.isSuper && (isWCEnable === true)
                textValue: qsTr("MAX ERROR")
                isOn : selMenu === QmlEnumDef.MENU_MAX_ERROR

                onSignalEventClicked:
                {
                    if(selMenu === QmlEnumDef.MENU_MAX_ERROR)
                        return

                    selMenu = QmlEnumDef.MENU_MAX_ERROR

                    viewContainer.clear()

                    viewContainer.clear()
                    viewContainer.push(panelMaxErrorSetting)

                }
            }

            UiToggleBtn{
                id : btnDeviceSetting
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew
                textValue: qsTr("DEVICE<br>SETTING")
                isOn : selMenu == QmlEnumDef.MENU_DEVICE_SETTING

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_DEVICE_SETTING)
                        return

                    selMenu = QmlEnumDef.MENU_DEVICE_SETTING

                    viewContainer.clear()
                    viewContainer.push(panelDeviceSetting,{"isAdmin":element.isSuper})
                }

            }


            UiToggleBtn{
                id : btnGraph
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew && element.isSuper
                textValue: qsTr("GRAPH")
                isOn : selMenu == QmlEnumDef.MENU_GRAPH

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_GRAPH)
                        return

                    selMenu = QmlEnumDef.MENU_GRAPH

                    viewContainer.clear()

                    viewContainer.push(panelGraph, {"isWCEnable" : element.isWCEnable,  "isMDEnable" : element.isMDEnable})
                }
            }

            UiToggleBtn {
                id :btnClockSetting
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew
                textValue: qsTr("CLOCK<br>SETTING")
                isOn : selMenu == QmlEnumDef.MENU_CLOCK_SETTING

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_CLOCK_SETTING)
                        return

                    selMenu = QmlEnumDef.MENU_CLOCK_SETTING

                    viewContainer.clear()
                    viewContainer.push(panelClockSetting)
                }
            }

            UiToggleBtn{
                id : btnInfo
                Layout.fillHeight: true
                Layout.fillWidth: true

                visible: !element.isLoggingVew && !element.isProductVew
                textValue: qsTr("INFORMATION")
                isOn : selMenu == QmlEnumDef.MENU_INFORMATION

                onSignalEventClicked:
                {
                    if(selMenu == QmlEnumDef.MENU_INFORMATION)
                        return

                    selMenu = QmlEnumDef.MENU_INFORMATION

                    viewContainer.clear()
                    viewContainer.push(panelInformation,{"isAdmin" : element.isSuper})
                }
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

    Component{ id : panelProductSetting;  PanelProductSetting  {anchors.fill: parent}}
    Component{ id : panelLoggingData;     PanelLoggingData     {anchors.fill: parent}}
    Component{ id : panelWCCaribMDCheckUp;PanelWCCaribMDCheckup{anchors.fill: parent}}
    Component{ id : panelDeviceSetting;   PanelDeviceSetting   {anchors.fill: parent}}
    Component{ id : panelInformation;     PanelInformation     {anchors.fill: parent}}
    Component{ id : panelGraph;           PanelGraph           {anchors.fill: parent}}
    Component{ id : panelClockSetting;    PanelClockSetting    {anchors.fill: parent}}
    Component{ id : panelMaxErrorSetting; PanelMaxErrorSetting {anchors.fill: parent}}
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
