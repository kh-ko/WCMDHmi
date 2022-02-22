import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ViewManager 1.0
import FontManager 1.0
import EnumDef 1.0
import QmlEnumDef 1.0
import "."
import "../../control/"
import "./main_view"
import "./menu_view"
import PanelWCSettingInHomeModel 1.0

Rectangle {
    signal signalEventClose()

    id: panel
    color : "#00000000"



    PanelWCSettingInHomeModel{
        id : model

        onSignalEventResultSaveProductSetting:
        {
            if(error == EnumDef.PDERR_NONE)
            {
                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
            else if(error === EnumDef.PDERR_NOT_EXIST)
            {
                ViewManager.toast.show(qsTr("This product dose not exist."))
            }
            else if(error === EnumDef.PDERR_SAME_PD_NUM)
            {
                ViewManager.toast.show(qsTr("The Product no already exists."))
            }
            else if(error === EnumDef.PDERR_SELECTED)
            {
                ViewManager.toast.show(qsTr("Can not remove selected product."))
            }
            else
            {
                ViewManager.toast.show(qsTr("SQL error is occured."))
            }
        }
    }

    UiPanel {
        id: uiPanel

        width : 1500
        height : 700
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        title: qsTr("Weight checker setting")

        type : QmlEnumDef.PANEL_TYPE_POPUP

        MouseArea{
            anchors.fill: parent
            onClicked: {}
        }

        UiButton{
            id :btnApply
            height: 80
            textValue: qsTr("Apply")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: btnClose.left
            anchors.rightMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_BLUE

            visible: model.isEditUnderWeight||
                     model.isEditNormalWeight ||
                     model.isEditOverWeight

            onSignalEventClicked: {
                model.onCommandApply()
            }
        }

        UiButton{
            id :btnClose
            height: 80
            textValue: qsTr("Close")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20

            type : QmlEnumDef.BUTTON_TYPE_POPUP

            onSignalEventClicked: {
                panel.signalEventClose()

            }
        }

        Image{
            width: 20
            height: 20
            source: "main_view/img_panelevent/wc_down.png"
            anchors.right: inputUnder.left
            anchors.rightMargin: 20
            anchors.verticalCenter: inputUnder.verticalCenter

        }

        UiInputFloat{
            id :inputUnder
            y: 222
            width: 300
            height: 80
            inputWidth: 200
            labelText: qsTr("Under")
            postfix: "g"
            anchors.bottom: iconUnder.top
            anchors.bottomMargin: 20
            anchors.horizontalCenterOffset: -52
            anchors.horizontalCenter: iconUnder.horizontalCenter

            bgColor: uiPanel.bgColor
            isHighlight: model.isEditUnderWeight
            min : 0.0
            max : 99999
            realValue : model.underWeight / 1000
            fixedN: ViewManager.weightFixedN
            onSignalChangeValue: {
                model.onCommandSetUnderWeight((value * 1000) + 0.5)
            }

        }

        Item {
            id: iconUnder
            x: 1072
            y: 266
            width: 266
            height: 259
            anchors.verticalCenter: iconDose.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: btnApply.top
            anchors.bottomMargin: 20
            anchors.horizontalCenterOffset: -450
            Rectangle {
                id: rectangle21
                x: 40
                width: 200
                height: 200
                color: "#00000000"
                radius: 20
                border.color: "#d9001b"
                anchors.topMargin: 58
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                border.width: 10
                Rectangle {
                    id: rectangle20
                    x: 61
                    y: 61
                    width: 80
                    height: 80
                    color: "#d9001b"
                    radius: 40
                    border.width: 0
                }
            }

            Rectangle {
                id: rectangle22
                x: 127
                width: 20
                height: 44
                color: "#d9001b"
                anchors.topMargin: 14
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: rectangle23
                x: 36
                width: 200
                height: 14
                color: "#d9001b"
                anchors.topMargin: 0
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: rectangle24
                x: 105
                y: 94
                width: 17
                height: 88
                color: "#d9001b"
                radius: 20
                border.color: "#59d9001b"
                border.width: 0
                rotation: -45
            }
        }

        Image{
            width: 20
            height: 20
            source: "main_view/img_panelevent/wc_dose.png"
            anchors.right: inputNormal.left
            anchors.rightMargin: 20
            anchors.verticalCenter: inputNormal.verticalCenter

        }

        UiInputFloat {
            id: inputNormal
            y: 216
            width: 300
            height: 100
            inputWidth: 200
            labelText: qsTr("Noraml")
            anchors.horizontalCenter: iconDose.horizontalCenter
            postfix: "g"
            anchors.bottom: iconDose.top
            anchors.bottomMargin: 0
            anchors.horizontalCenterOffset: -52


            reservedValue: model.currWeight !== 0 ? (model.currWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) : ""
            bgColor: uiPanel.bgColor
            isHighlight: model.isEditNormalWeight
            min : 0
            max : 99999
            realValue : model.normalWeight / 1000
            fixedN: ViewManager.weightFixedN

            onSignalChangeValue: {
                model.onCommandSetNormalWeight((value * 1000) + 0.5)
            }
        }

        Item {
            id: iconDose
            x: 1080
            y: 267
            width: 266
            height: 259
            anchors.verticalCenter: iconOver.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: btnApply.top
            anchors.bottomMargin: 20
            Rectangle {
                id: rectangle16
                x: 40
                width: 200
                height: 200
                color: "#00000000"
                radius: 20
                border.color: "#0085ff"
                anchors.topMargin: 58
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                border.width: 10
                Rectangle {
                    id: rectangle15
                    x: 61
                    y: 61
                    width: 80
                    height: 80
                    color: "#0085ff"
                    radius: 40
                    border.width: 0
                }
            }

            Rectangle {
                id: rectangle17
                x: 127
                width: 20
                height: 24
                color: "#0085ff"
                anchors.topMargin: 34
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: rectangle18
                x: 36
                width: 200
                height: 14
                color: "#0085ff"
                anchors.topMargin: 20
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: rectangle19
                x: 152
                y: 93
                width: 17
                height: 88
                color: "#0085ff"
                radius: 20
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: "#59d9001b"
                border.width: 0
                rotation: 0
            }
        }

        Image {
            width: 20
            height: 20
            anchors.rightMargin: 20
            anchors.right: inputOver.left
            anchors.verticalCenter: inputOver.verticalCenter
            source: "main_view/img_panelevent/wc_up.png"
        }

        UiInputFloat {
            id: inputOver
            y: 216
            width: 300
            height: 120
            inputWidth: 200
            labelText: qsTr("Over")
            anchors.horizontalCenter: iconOver.horizontalCenter
            postfix: "g"
            anchors.bottom: iconOver.top
            anchors.bottomMargin: -20
            anchors.horizontalCenterOffset: -52
            bgColor: uiPanel.bgColor
            isHighlight: model.isEditOverWeight
            min : 0
            max : 99999
            realValue : model.overWeight / 1000
            fixedN : ViewManager.weightFixedN

            onSignalChangeValue: {
                model.onCommandSetOverWeight((value * 1000) + 0.5)
            }
        }

        Item {
            id: iconOver
            x: 1072
            y: 263
            width: 266
            height: 259
            anchors.horizontalCenterOffset: 450
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: btnApply.top
            anchors.bottomMargin: 20
            Rectangle {
                id: rectangle11
                x: 40
                width: 200
                height: 200
                color: "#00000000"
                radius: 20
                anchors.topMargin: 58
                border.color: "#f59a23"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                border.width: 10
                Rectangle {
                    id: rectangle10
                    x: 61
                    y: 61
                    width: 80
                    height: 80
                    color: "#f59a23"
                    radius: 40
                    border.width: 0
                }
            }

            Rectangle {
                id: rectangle12
                x: 127
                width: 20
                height: 4
                color: "#f59a23"
                anchors.topMargin: 54
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }

            Rectangle {
                id: rectangle13
                x: 36
                width: 200
                height: 14
                color: "#f59a23"
                anchors.topMargin: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }

            Rectangle {
                id: rectangle14
                x: 147
                y: 98
                width: 17
                height: 88
                color: "#f59a23"
                radius: 20
                border.color: "#59d9001b"
                border.width: 0
                rotation: 45
            }
        }

        Image {
            width: 30
            height: 30
            source: "img/weight_setting/over_gap.png"
            anchors.rightMargin: 20
            anchors.right: inputOverGap.left
            anchors.verticalCenter: inputOverGap.verticalCenter
        }

        UiInputFloat {
            id: inputOverGap
            x: 402
            y: 93
            width: 200
            height: 80
            anchors.horizontalCenter: iconUnder.horizontalCenter
            postfix: "g"
            anchors.bottom: iconUnder.top
            anchors.bottomMargin: 149
            anchors.horizontalCenterOffset: 720

            bgColor: uiPanel.bgColor
            isHighlight: model.isEditOverGap
            min : 0.0
            max : 99999
            realValue : model.overGap / 1000
           fixedN : ViewManager.weightFixedN

            onSignalChangeValue: {
                model.onCommandSetOverGap((value * 1000) + 0.5)
            }
        }

        Image {
            width: 30
            height: 30
            source: "img/weight_setting/under_gap.png"
            anchors.rightMargin: 20
            anchors.right: inputUnderGap.left
            anchors.verticalCenter: inputUnderGap.verticalCenter
        }

        UiInputFloat {
            id: inputUnderGap
            x: 427
            y: 93
            width: 200
            height: 80
            anchors.horizontalCenter: iconUnder.horizontalCenter
            postfix: "g"
            anchors.bottom: iconUnder.top
            anchors.bottomMargin: 149
            anchors.horizontalCenterOffset: 270

            bgColor: uiPanel.bgColor
            isHighlight: model.isEditUnderGap
            min : 0.0
            max : 99999
            realValue : model.underGap / 1000
            fixedN : ViewManager.weightFixedN

            onSignalChangeValue: {
                model.onCommandSetUnderGap((value * 1000) + 0.5)
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
