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

        onSignalEventCompleteCalibration: {
            ViewManager.toast.show(qsTr("Calibration is complete."))
        }
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
        type : QmlEnumDef.PANEL_TYPE_DROP


        UiLabelSystem{
            id : labelMessage01
            height: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 100

            textValue: qsTr("After put the standard weight on the scale, press 'Calibration' button.")
        }

        Rectangle{
            height: 5
            color: "#0085ff"
            radius: 2
            anchors.right: labelMessage01.right
            anchors.rightMargin: 400
            anchors.left: labelMessage01.left
            anchors.leftMargin: 0
            anchors.top: labelMessage01.bottom
            anchors.topMargin: 0
        }
    }

    Item
    {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: btnCaribraion.top
        anchors.bottomMargin: 0
        anchors.top: panelMessageBox.bottom
        anchors.topMargin: 60
        anchors.left: parent.left
        anchors.leftMargin: 20

        visible: caribratinModel.step === QmlEnumDef.WC_STATIC_CARI_STEP_INIT

        UiLabelSystem{
            id : labelStandardWeight
            width: 250
            height: 30
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.top: parent.top
            anchors.topMargin: 60

            textValue: qsTr("· Standard weight");
        }

        Text{
            id:textStaticWeight
            width: 215
            height: 60

            font.pixelSize: 40
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignRight

            color : "#FFFFFF"
            text: (caribratinModel.standardWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            anchors.left: labelStandardWeight.right
            anchors.leftMargin: 0
            anchors.top: labelStandardWeight.top
            anchors.topMargin: 0
        }

        UiInputFloat{
            id : inputStaticWeight
            visible: false
            min : 0.1
            max : 9999.9

            realValue:  caribratinModel.standardWeight / 1000
            onSignalChangeValue: {
                caribratinModel.onCommandSetStandardWeight((value * 1000) + 0.5)
            }
        }

        UiButton{
            height: 80
            anchors.verticalCenter: textStaticWeight.verticalCenter
            anchors.left: textStaticWeight.right
            anchors.leftMargin: 40
            width: 200

            textValue: qsTr("Edit")

            onSignalEventClicked: {
                ViewManager.keypad.showKeypad(inputStaticWeight.getVInputText())
            }
        }

        Text{
            color: "#ffffff"

            anchors.top: textStaticWeight.bottom
            anchors.topMargin:0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 80
            anchors.right: parent.right
            anchors.rightMargin: 80

            font.pixelSize: 250
            font.family: FontManager.nanumGothicName
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignRight

            text: (caribratinModel.currentWeight / 1000).toLocaleString(ViewManager.locale, 'f', 1) + " g"
            verticalAlignment: Text.AlignVCenter

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
            panel.signalEventCloseClicked();
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

        visible: caribratinModel.step === QmlEnumDef.WC_STATIC_CARI_STEP_INIT
        textValue: qsTr("Calibraion")

        type: QmlEnumDef.BUTTON_TYPE_BLUE

        onSignalEventClicked: {
            caribratinModel.onCommandCaribration()
        }
    }

    BusyIndicator{
        anchors.fill: parent
        running: true

        visible: caribratinModel.isBusy
    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
