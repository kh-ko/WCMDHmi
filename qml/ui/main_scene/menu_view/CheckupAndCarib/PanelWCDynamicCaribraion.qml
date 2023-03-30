import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelWCDynamicCalibrationModel 1.0

UiPanel {
    id: panel
    width : 1519
    height: 997

    signal signalEventCloseClicked()

    PanelWCDynamicCalibrationModel{
        id:caribratinModel

        onSignalEventChangedIsRemeasure: {
          //  aniMessage.stop()
          //  aniMessage.restart()
        }

        onSignalEventCompleteCalibration: {
            ViewManager.toast.show(qsTr("Calibration is complete."))
        }

        onSignalEventInvalidCalibration: {
            var msg = qsTr("Please check dynamic factor<br>Dynamic factor is too high or too low.")
            var msgBox = messageBox.createObject(panel,{"message":msg,"textColor":"#D9001B"})
            msgBox.open();
        }
    }

    /*
    NumberAnimation {
        id : aniMessage
        target: messageCover
        properties: "x"
        duration: 250
        from : -50
        to: panelMessageBox.width
        running: false
        easing.type: Easing.Linear
    }
    */

    MouseArea{
        anchors.fill: parent
    }

    Item{
        id : pdInfoBox
        //width: parent.width;
        height: /*noticeProductInfo.height + */(productInfoLabel.height * 2) + 40
        anchors.top: parent.top; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
/*
        Text{
            id : noticeProductInfo
            anchors.top: parent.top; anchors.left: parent.left;

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#ACACAC"
            text: qsTr("1.Please check the product information.")
        }

        UiButton{
            height: 80; width: 200
            anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right;

            textValue: qsTr("Confirm")

            onSignalEventClicked: {
                caribratinModel.onCommandPDConfirm()
            }
        }
*/
        Text{
            id : productInfoLabel
            width: 250
            anchors.top: parent.top; anchors.left: parent.left; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#acacac"
            text: qsTr("· Product")
        }

        Text{
            id : productInfo
            anchors.verticalCenter: productInfoLabel.verticalCenter; anchors.left: productInfoLabel.right; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 30
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: ("000"+caribratinModel.pdNum).slice(-3) + " " + caribratinModel.pdName
        }

        Text{
            id : dynamicFactorLabel
            width: 250
            anchors.top: productInfo.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#acacac"
            text: qsTr("· Dynamic factor")
        }

        Text{
            id : dynamicFactor
            anchors.verticalCenter: dynamicFactorLabel.verticalCenter; anchors.left: dynamicFactorLabel.right; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 30
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: (caribratinModel.dynamicFactor / 10000000.0).toLocaleString(ViewManager.locale, 'f', 7)
        }
/*
        Text{
            id : tareWeightLabel
            width: 250
            anchors.top: dynamicFactor.bottom; anchors.topMargin: 20; anchors.left: parent.left; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 25
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#acacac"
            text: qsTr("· Tare weight")
        }

        Text{
            id : tareWeight
            anchors.verticalCenter: tareWeightLabel.verticalCenter; anchors.left: tareWeightLabel.right; anchors.leftMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 30
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: (caribratinModel.tareWeight / 1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
        }
*/
    }


    UiPanel{
        id : panelMessageBox
        height: 296
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: pdInfoBox.bottom
        anchors.topMargin: 20
        anchors.bottom: tryCountBox.top
        anchors.bottomMargin: 40

        clip: true
        type : QmlEnumDef.PANEL_TYPE_DROP

        ColumnLayout{
            anchors.fill: parent; anchors.topMargin: 20; anchors.bottomMargin: 20; anchors.leftMargin: 60; anchors.rightMargin: 60


            Item{
                Layout.preferredHeight: 3; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                //visible : caribratinModel.step > QmlEnumDef.DYNAMIC_CARIB_STEP_INIT
                Text{
                    id : noticeZERO
                    height: 80
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignLeft
                    font.pixelSize: 25
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#ACACAC"
                    text: qsTr("1. After emptying the product on the scale, press 'ZERO' button.")
                }

                UiButton{
                    height: 80; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right;

                    textValue: qsTr("ZERO")

                    onSignalEventClicked: {
                        caribratinModel.onCommandZERO()
                    }
                }
            }
            Item{
                Layout.preferredHeight: 5; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                visible : caribratinModel.step > QmlEnumDef.DYNAMIC_CARIB_STEP_ZERO

                Item{
                    width: parent.width;
                    height: noticeRefWeight.height + 10 + weightInfoBox.height + 10 + referenceWeightBox.height
                    anchors.verticalCenter: parent.verticalCenter

                    Text{
                        id : noticeRefWeight
                        anchors.top: parent.top; anchors.left: parent.left;

                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment : Text.AlignLeft
                        font.pixelSize: 25
                        font.family: FontManager.nanumGothicName
                        elide: Text.ElideRight

                        color : "#ACACAC"
                        text: qsTr("2. Put the product on the scale and press 'Standard setting' button.")
                    }

                    UiButton{
                        id : stdSettingBtn
                        height: 80; width: 200
                        anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right;

                        textValue: qsTr("Standard setting")

                        onSignalEventClicked: {
                            caribratinModel.onCommandSetRefWeight(caribratinModel.currWeight + caribratinModel.tareWeight)
                        }
                    }

                    Item {
                        id: weightInfoBox
                        height:currentWeightLabel.height
                        anchors.top: noticeRefWeight.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 40; anchors.right: stdSettingBtn.left; anchors.rightMargin: 20

                        Text{
                            id : currentWeightLabel

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment : Text.AlignLeft
                            font.pixelSize: 25
                            font.family: FontManager.nanumGothicName
                            elide: Text.ElideRight

                            color : "#acacac"
                            text: qsTr("· Current weight")
                        }

                        Text{
                            id : currentWeight
                            anchors.verticalCenter: currentWeightLabel.verticalCenter; anchors.left: currentWeightLabel.right; anchors.leftMargin: 20; anchors.right: tareWeightLabel.left; anchors.rightMargin: 20

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment : Text.AlignLeft
                            font.pixelSize: 30
                            font.family: FontManager.nanumGothicName
                            elide: Text.ElideRight

                            color : "#FFFFFF"
                            text: (caribratinModel.currWeight / 1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
                        }

                        Text{
                            id : tareWeightLabel
                            anchors.left: parent.left; anchors.leftMargin: parent.width / 2;

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment : Text.AlignLeft
                            font.pixelSize: 25
                            font.family: FontManager.nanumGothicName
                            elide: Text.ElideRight

                            color : "#acacac"
                            text: qsTr("· Tare weight")
                        }

                        Text{
                            id : tareWeight
                            anchors.verticalCenter: tareWeightLabel.verticalCenter; anchors.left: tareWeightLabel.right; anchors.leftMargin: 20; anchors.right: parent.right;

                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment : Text.AlignLeft
                            font.pixelSize: 30
                            font.family: FontManager.nanumGothicName
                            elide: Text.ElideRight

                            color : "#FFFFFF"
                            text: (caribratinModel.tareWeight / 1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
                        }
                    }
                    //(tare weight included)

                    Text{
                        id : referenceWeightLabel
                        anchors.verticalCenter: referenceWeightBox.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 40

                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment : Text.AlignLeft
                        font.pixelSize: 25
                        font.family: FontManager.nanumGothicName
                        elide: Text.ElideRight

                        color : "#acacac"
                        text: qsTr("· Reference weight (tare weight included)")
                    }

                    Rectangle{
                        id : referenceWeightBox
                        height: 80;
                        anchors.top:weightInfoBox.bottom; anchors.topMargin: 10; anchors.left: referenceWeightLabel.right; anchors.leftMargin: 20; anchors.right: weightInfoBox.right;
                        color: "#59000000"

                        Text{
                            id : referenceWeight
                            //anchors.verticalCenter: referenceWeightLabel.verticalCenter; anchors.left: referenceWeightLabel.right; anchors.leftMargin: 20
                            anchors.fill: parent; anchors.margins: 20
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment : Text.AlignHCenter
                            font.pixelSize: 30
                            font.family: FontManager.nanumGothicName
                            elide: Text.ElideRight

                            color : "#FFFFFF"
                            text: ((caribratinModel.refWeight) / 1000).toLocaleString(ViewManager.locale, 'f', ViewManager.weightFixedN) + " g"
                        }
                    }
                }
            }

            Item{
                Layout.preferredHeight: 4; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                visible : caribratinModel.step > QmlEnumDef.DYNAMIC_CARIB_STEP_STD_SETTING

                Text{
                    id : noticeCarib
                    height: 80
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignLeft
                    font.pixelSize: 25
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#ACACAC"
                    text: qsTr("3. After emptying the product on the scale, press 'Caribration' button.<br>   If the conveyer run, let the product through.")
                }

                UiButton{
                    height: 80; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right;

                    textValue: qsTr("Caribration")

                    onSignalEventClicked: {
                        caribratinModel.onCommandCaribration()
                    }
                }
            }
        }
    }

    Item{
        id : tryCountBox
        height: 120; width: 1000
        anchors.bottom: btnComplete.top; anchors.bottomMargin: 40; anchors.horizontalCenter: parent.horizontalCenter

        Text{
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 40

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignLeft
            font.pixelSize: 50
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#ACACAC"
            text: qsTr("Try count")
        }

        Text{
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.right: parent.right; anchors.rightMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignRight
            font.pixelSize: 100
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: "" + caribratinModel.tryCount + " / 5"
        }
    }

    UiButton{
        id: btnComplete
        height: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 40
        width: 200

        textValue: qsTr("Close")

        onSignalEventClicked: {
            panel.signalEventCloseClicked()
            caribratinModel.onCommandClosed()
        }
    }

    Component
    {
        id : messageBox
        UiMessageBox
        {

        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
