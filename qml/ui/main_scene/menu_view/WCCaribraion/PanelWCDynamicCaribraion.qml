import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import PanelWCDynamicCalibrationModel 1.0

UiPanel {
    id: panel
    width : 1519
    height: 997

    signal signalEventCloseClicked()

    PanelWCDynamicCalibrationModel{
        id:caribratinModel

        onSignalEventChangedIsRemeasure: {
            aniMessage.stop()
            aniMessage.restart()
        }

        onSignalEventCompleteCalibration: {
            ViewManager.toast.show(qsTr("Calibration is complete."))
        }
    }

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

    UiPanel{
        id : panelMessageBox
        height: 260
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20

        clip: true
        type : EnumDefine.PANEL_TYPE_DROP

        UiLabelSystem{
            id : labelMessage
            height: 100
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 100

            textValue: qsTr("1. Check the reference weight and press the 'calibration' button.<br>2. If the conveyer run, let the product through.")
        }

        Rectangle{
            height: 5
            color: "#0085ff"
            radius: 2
            anchors.right: labelMessage.right
            anchors.rightMargin: 400
            anchors.left: labelMessage.left
            anchors.leftMargin: 0
            anchors.top: labelMessage.bottom
            anchors.topMargin: 0
        }

        Rectangle{
            id: messageCover
            x :1500
            height: parent.height - 50
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#00191919"
                }

                GradientStop {
                    position: 0.1
                    color: "#191919"
                }
                orientation: Gradient.Horizontal
            }
        }
    }

    Item{
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: btnComplete.top
        anchors.bottomMargin: 0
        anchors.top: panelMessageBox.bottom
        anchors.topMargin: 0

        Item{
            height: parent.height/3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Text{
                x: 600
                width : 663
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                font.pixelSize: 50
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#ACACAC"
                text: qsTr("· current weight")

            }

            Text{
                id : textCurrWeight
                x: 663
                width : 536
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 280

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignRight
                font.pixelSize: 90
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#FFFFFF"
                text: (caribratinModel.currWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"

            }

            UiInputFloat{
                id : inputCurrWeight
                visible: false
                min : 0.1
                max : 9999.9

                isDisable: true
                realValue:  caribratinModel.currWeight / 1000

            }

            UiButton{
                width: 200
                height: 80
                textValue: qsTr("Set ref weight")
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: textCurrWeight.verticalCenter

                onSignalEventClicked:
                {
                    caribratinModel.onCommandSetRefWeight(caribratinModel.currWeight)
                }
            }

        }

        Item{
            id: element
            height: parent.height/3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.verticalCenter: parent.verticalCenter

            Text{
                x: 600
                width : 663
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                font.pixelSize: 50
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#ACACAC"
                text: qsTr("· Reference weight")

            }

            Text{
                id : textRefWeight
                x: 663
                width : 536
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 280

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignRight
                font.pixelSize: 90
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#FFFFFF"
                text: (caribratinModel.refWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"


            }

            UiInputFloat{
                id : inputRefWeight
                visible: false
                min : 0.1
                max : 9999.9

                realValue:  caribratinModel.refWeight / 1000
                onSignalChangeValue: {
                    caribratinModel.onCommandSetRefWeight((value * 1000) + 0.5)
                }
            }

            /*

            UiButton{
                width: 200
                height: 80
                textValue: qsTr("Edit")
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: textRefWeight.verticalCenter

                onSignalEventClicked: {
                    ViewManager.keypad.showKeypad(inputRefWeight.getVInputText())
                }
            }
            */

        }

        Item{
            id: element1
            height: parent.height/3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Text{
                x: 600
                width : 663
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                font.pixelSize: 50
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#ACACAC"
                text: qsTr("· Moving weight")

            }

            Text{
                id : textDynamicWeight
                x: 668
                width : 536
                anchors.top : parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 280

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignRight
                font.pixelSize: 90
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight

                color : "#FFFFFF"
                text: (caribratinModel.movingWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"

            }

            /*
            UiButton{
                x: 1260
                width: 200
                height: 80
                textValue: qsTr("Measurement")
                anchors.right: parent.right
                anchors.rightMargin: 20
                anchors.verticalCenter: parent.verticalCenter

                onSignalEventClicked: {
                    caribratinModel.onCommandRemeasurement();
                }
            }
            */
        }
    }

    UiButton{
        id: btnComplete
        height: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: btnCaribraion.left
        anchors.rightMargin: 20
        width: 200

        textValue: qsTr("Close")

        onSignalEventClicked: {
            panel.signalEventCloseClicked()
            caribratinModel.onCommandClosed()
        }
    }

    UiButton{
        id: btnCaribraion
        height: 80
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.right: parent.right
        anchors.rightMargin: 40
        width: 200

        textValue: qsTr("Calibraion")

        type: EnumDefine.BUTTON_TYPE_BLUE

        onSignalEventClicked: {
            caribratinModel.onCommandCaribration();
        }
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}D{i:11;anchors_width:700}
}
##^##*/
