import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../../../../control"
import QmlEnumDef 1.0
import ViewManager 1.0
import SearchSSIDDlgModel 1.0

Rectangle {
    id: dialog
    anchors.fill: parent
    color: "#00000000"
    visible: false

    signal signalEventConnectedAP()

    function close()
    {
        dialog.visible = false;
        listModel.clear();
    }

    function show()
    {
        dialog.visible = true;
        searchModel.onCommandScanAP();
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

        UiButton{
            id : closeBtn
            height: 60
            width: 180
            textValue : qsTr("Cancle")
            type : QmlEnumDef.BUTTON_TYPE_UP_PANEL
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            onSignalEventClicked: {
                dialog.close();
            }
        }

        Item{
            id : busyBox
            anchors.top :closeBtn.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 20

            visible: searchModel.isScanning || searchModel.isConnectingInternet
            UiLabelSystem{
                id :busyText
                height: 50
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
                horizontalAlignment : Text.AlignHCenter
                textValue : searchModel.isScanning ? qsTr("Scanning.") :
                            searchModel.isConnectingInternet ? qsTr("Connecting.") :""
            }

            BusyIndicator{
                anchors.top: busyText.bottom;  anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
                running: true;
            }
        }

        ListView{
            id : listView
            clip: true
            anchors.top :closeBtn.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: 20

            visible: !searchModel.isScanning && !searchModel.isConnectingInternet
            spacing: 20
            model: listModel

            delegate: UiPanel
            {
                id : ipItem

                height : 80
                width  : parent.width
                type   : mouseArea.isPress ? QmlEnumDef.PANEL_TYPE_SELECT : QmlEnumDef.PANEL_TYPE_UP_PANEL

                MouseArea{
                    property bool isPress : false

                    id : mouseArea
                    anchors.fill: parent
                    hoverEnabled: true

                    onContainsMouseChanged:
                    {
                        if(!containsMouse)
                            isPress = false
                    }

                    onPressed:
                    {
                        isPress = true
                    }

                    onReleased: {
                        isPress = false
                    }

                    onClicked:
                    {
                        searchModel.onCommandSelectAP(ssid, auth)

                        if(auth == "")
                        {
                            searchModel.onCommandSetPSK("");
                        }
                        else
                        {
                            password.textValue = ""
                            ViewManager.keypad.showKeypad(password.getVInputText())
                        }
                    }
                }

                UiLabelContent{
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter

                    textValue: ssid
                }
            }

            ListModel{
                id: listModel
            }
        }
    }

    SearchSSIDDlgModel{
        id : searchModel

        onSignalEventFoundAP: {
            listModel.append({"ssid":SSID,"auth":authType})
        }

        onSignalEventConnectedAP:{
            dialog.signalEventConnectedAP();
        }
    }

    UiInputString{
        id : password
        width: 0
        height: 0
        textValue: ""
        labelText : qsTr("Please enter wifi password.")

        onSignalChangeText:
        {
            searchModel.onCommandSetPSK(value)
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
