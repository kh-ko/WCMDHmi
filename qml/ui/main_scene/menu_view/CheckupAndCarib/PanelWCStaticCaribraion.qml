import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelWCStaticCaribrationModel 1.0

UiPanel {
    id: panel
    width : 1519
    height: 997

    signal signalEventCloseClicked()

    anchors.fill: parent

    PanelWCStaticCaribrationModel{
        id : caribratinModel
    }

    MouseArea{
        anchors.fill: parent
    }

    UiPanel{
        id : panelMessageBox
        height: 296
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: currentWeightBox.top
        anchors.bottomMargin: 40

        clip: true
        type : QmlEnumDef.PANEL_TYPE_DROP

        ColumnLayout{
            anchors.fill: parent; anchors.margins: 20
            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true

                Text{
                    anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 40

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignLeft
                    font.pixelSize: 25
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#FFFFFF"
                    text: qsTr("1. After emptying the product on the scale, press 'ZERO' button.")
                }

                UiButton{
                    height: 80; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 40

                    textValue: qsTr("ZERO")

                    onSignalEventClicked: {
                        caribratinModel.onCommandZERO()
                    }
                }
            }
            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                visible: caribratinModel.step > QmlEnumDef.STATIC_CARIB_STEP_INIT

                Text{
                    anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 40

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignLeft
                    font.pixelSize: 25
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#FFFFFF"
                    text: qsTr("2. Please check the standard weight.")
                }

                UiInputFloat{
                    height: 80; width: 220
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: standardWeightConfirmBtn.left; anchors.rightMargin: 20
                    min : 0.1
                    max : 9999.9
                    postfix: "g"

                    realValue:  caribratinModel.standardWeight / 1000
                    onSignalChangeValue: {
                        caribratinModel.onCommandSetStandardWeight((value * 1000) + 0.5)
                    }
                }

                UiButton{
                    id : standardWeightConfirmBtn
                    height: 80; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 40

                    textValue: qsTr("Confirm")

                    onSignalEventClicked: {
                        caribratinModel.onCommandConfirmStandardWeight()
                    }
                }
            }

            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                visible: caribratinModel.step > QmlEnumDef.STATIC_CARIB_STEP_STD_WEIGHT_CHECK
                Text{
                    anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.leftMargin: 40

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignLeft
                    font.pixelSize: 25
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#FFFFFF"
                    text: qsTr("3. After put the standard weight on the scale, press 'Calibration' button.")
                }

                UiButton{
                    height: 80; width: 200
                    anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 40

                    textValue: qsTr("Calibration")

                    onSignalEventClicked: {
                        caribratinModel.onCommandCaribration()
                    }
                }
            }
            Item{
                Layout.preferredHeight: 1; Layout.preferredWidth: 1; Layout.fillHeight: true; Layout.fillWidth: true
                visible: caribratinModel.step > QmlEnumDef.STATIC_CARIB_STEP_CARIB_ING
                Text{
                    anchors.fill: parent

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment : Text.AlignHCenter
                    font.pixelSize: 100
                    font.family: FontManager.nanumGothicName
                    elide: Text.ElideRight

                    color : "#FFFFFF"
                    text: qsTr("Calibration is complete.")
                }
            }
        }
    }

    Item{
        id : currentWeightBox
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
            text: qsTr("Current weight")
        }

        Text{
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.right: parent.right; anchors.rightMargin: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment : Text.AlignRight
            font.pixelSize: 100
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight

            color : "#FFFFFF"
            text: (caribratinModel.currentWeight/1000).toLocaleString(ViewManager.locale, "f", 1) + " g"
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
            panel.signalEventCloseClicked();
        }
    }

    BusyIndicator{
        anchors.fill: parent
        running: true

        visible: caribratinModel.step === QmlEnumDef.STATIC_CARIB_STEP_CARIB_ING
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
