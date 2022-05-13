import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0
//import EthernetSettingEnumDef 1.0
import EthernetSettingDlgModel 1.0
import EthernetSettingItemModel 1.0

Rectangle {
    id: dialog
    anchors.fill: parent
    color: "#00000000"
    visible: false

    function close()
    {
        dialog.visible = false;
    }

    function show()
    {
        dialog.visible = true;

        dlgModel.onCommandLoad()

        listModel.clear();

        listModel.append({"devIdx":0})
        listModel.append({"devIdx":1})
        listModel.append({"devIdx":2})
    }

    function setDspIP(dspIP)
    {
        dlgModel.onChangedDspIP(dspIP)
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true

        onContainsMouseChanged:
        {
        }

        onPressed:
        {
        }

        onReleased: {
        }

        onClicked:
        {
        }
    }

    UiPanel{
        id :panel
        width: 600; height: 900
        anchors.centerIn: parent

        EthernetSettingDlgModel{
            id : dlgModel
        }

        UiButton{
            id : closeBtn
            height: 60
            width: 180
            textValue : qsTr("Cancel")
            type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            onSignalEventClicked: {
                dialog.close();
            }
        }

        UiButton{
            id : applyBtn
            height: 60
            width: 180
            textValue : qsTr("Apply")
            type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: closeBtn.left
            anchors.rightMargin: 20

            onSignalEventClicked: {
                dialog.close();
                dlgModel.onCommandApply()
            }
        }

        ListView{
            id : listView
            clip: true
            anchors.top :closeBtn.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 20

            spacing: 20
            model: listModel

            delegate: UiPanel
            {
                property EthernetSettingItemModel itemModel : dlgModel.onCommandGetItem(devIdx)
                height : inputSubnetMask.visible ? 490 + 75 : 410 + 75 /* conetent height + title height*/
                width  : parent.width
                type   : QmlEnumDef.PANEL_TYPE_UP_PANEL
                title  : itemModel.mDevType

                UiInputString {
                    id: inputIP
                    height: 60

                    anchors.top: parent.top
                    anchors.topMargin: parent.titleHeight
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    inputWidth: 300
                    labelText: qsTr("· IP")

                    isHighlight: parent.itemModel.mIsEditIP
                    textValue: parent.itemModel.mIP

                    onSignalChangeText: {
                        parent.itemModel.mIP = value
                    }
                }

                UiInputString {
                    id: inputSubnetMask
                    height: 60

                    anchors.top: inputIP.bottom
                    anchors.topMargin: 20
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    visible: false

                    inputWidth: 300
                    labelText: qsTr("· Subnet mask")

                    isHighlight: parent.itemModel.mIsEditSubnetMask
                    textValue: parent.itemModel.mSubnetMask

                    onSignalChangeText: {
                        parent.itemModel.mSubnetMask = value
                    }
                }

                UiInputString {
                    id: inputRoute
                    height: 60

                    anchors.top: inputSubnetMask.visible ? inputSubnetMask.bottom : inputIP.bottom
                    anchors.topMargin: 20
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    inputWidth: 300
                    labelText: qsTr("· Route")

                    isHighlight: parent.itemModel.mIsEditRoute
                    textValue: parent.itemModel.mRoute

                    onSignalChangeText: {
                        parent.itemModel.mRoute = value
                    }
                }

                UiInputString {
                    id: inputMetric
                    height: 60

                    anchors.top: inputRoute.bottom
                    anchors.topMargin: 20
                    anchors.leftMargin: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    inputWidth: 300
                    labelText: qsTr("· Metric")

                    isHighlight: parent.itemModel.mIsEditMetric
                    textValue: parent.itemModel.mMetric

                    onSignalChangeText: {
                        parent.itemModel.mMetric = value
                    }
                }

                UiLabelSystem{
                    id: labelTargetIPs
                    height: 60; width : 200
                    anchors.topMargin: 20
                    anchors.top: inputMetric.bottom
                    anchors.leftMargin: 20
                    anchors.left: parent.left

                    textValue: qsTr("· Target IPs")
                }
                UiButton{
                    id : btnSetDspIP
                    width : 100
                    height: 60
                    anchors.verticalCenter: labelTargetIPs.verticalCenter;
                    anchors.left: labelTargetIPs.right; anchors.leftMargin: 20

                    textValue: qsTr("DSP IP")

                    onSignalEventClicked:
                    {
                        dlgModel.onCommandSetDspIPToTargetIPs(parent.itemModel.mDevType)
                    }
                }

                UiButton{
                    id : btnDelIP
                    width : 100
                    height: 60
                    anchors.verticalCenter: btnSetDspIP.verticalCenter;
                    anchors.left: btnSetDspIP.right; anchors.leftMargin: 20

                    textValue: qsTr("Del")

                    onSignalEventClicked:
                    {
                        dlgModel.onCommandDelTargetIPs(parent.itemModel.mDevType)
                    }
                }

                UiInputString {
                    id: inputCustomTarget
                    height: 60

                    anchors.top: labelTargetIPs.bottom
                    anchors.topMargin: 10
                    anchors.leftMargin: 80
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    maxLength : 255
                    inputWidth: 300
                    labelText: qsTr("Target IPs")

                    //isDisable: parent.itemModel.mIsEditTargetType !== EthernetSettingEnumDef.ETH_TARGET_CUSTOM

                    isHighlight: !isDisable && parent.itemModel.mIsEditTargetIPs
                    textValue: parent.itemModel.mTargetIPs

                    onSignalChangeText: {
                        parent.itemModel.mTargetIPs = value
                    }
                }



//                UiLabelContent{
//                    width: parent.width
//                    height: parent.height
//                    anchors.left: parent.left
//                    anchors.leftMargin: 20
//                    anchors.verticalCenter: parent.verticalCenter

//                    textValue: title
//                }
            }

            ListModel{
                id: listModel
            }
        }
    }

//    SearchSSIDDlgModel{
//        id : searchModel

//        onSignalEventFoundAP: {
//            listModel.append({"ssid":SSID,"auth":authType})
//        }

//        onSignalEventConnectedAP:{
//            dialog.signalEventConnectedAP();
//        }
//    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
