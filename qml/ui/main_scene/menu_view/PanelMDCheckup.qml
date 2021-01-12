import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import ViewManager 1.0
import FontManager 1.0
import "."
import "../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelMDCheckupModel 1.0

UiPanel {
    id: uiPanel
    width : 1519
    height: 997

    function startNextStep()
    {
        mdCheckupModel.onCommandStartNextStep();

        if(mdCheckupModel.step < QmlEnumDef.CHECKUP_RESULT_STEP && mdCheckupModel.step > QmlEnumDef.CHECKUP_STEP_INIT)
        {
            aniCount.restart();
        }
        else if(mdCheckupModel.step == QmlEnumDef.CHECKUP_RESULT_STEP)
        {
            finishCheckup();
        }
    }

    function finishCheckup()
    {
        aniCount.stop();
        timerProgress.value = 10;
    }

    PanelMDCheckupModel{
        id : mdCheckupModel

        onSignalEventChangedStep: {
            aniMessage.stop();
            aniMessage.restart();
        }

        onSignalEventStepComplete:
        {
            uiPanel.startNextStep();
        }
    }

    NumberAnimation {
        id : aniCount
        target: timerProgress
        properties: "value"
        duration: 10000
        from : 10
        to: 0
        running: false
        easing.type: Easing.Linear

        onFinished:
        {
            if(mdCheckupModel.step == QmlEnumDef.CHECKUP_INIT || mdCheckupModel.step == QmlEnumDef.CHECKUP_RESULT_STEP)
                return;

            mdCheckupModel.onCommandTimeout();

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
        type : QmlEnumDef.PANEL_TYPE_DROP


        UiLabelSystem{
            id : labelMessage
            height: 50
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 100


            textValue: mdCheckupModel.step === 0 ? qsTr("After pressing the start button, follow the prompts to perform the check.") :
                       mdCheckupModel.step === 1 ? qsTr("Put the Fe specimen on the middle.") :
                       mdCheckupModel.step === 2 ? qsTr("Put the Fe specimen on the left.") :
                       mdCheckupModel.step === 3 ? qsTr("Put the Fe specimen on the right.") :
                       mdCheckupModel.step === 4 ? qsTr("Put the Sus specimen on the middle.") :
                       mdCheckupModel.step === 5 ? qsTr("Put the Fe specimen on the left.") :
                       mdCheckupModel.step === 6 ? qsTr("Put the Fe specimen on the right.") : qsTr("Check is complete.")
        }

        Rectangle{
            height: 5
            color: "#0085ff"
            radius: 2
            anchors.right: btnCancle.left
            anchors.rightMargin: 50
            anchors.left: labelMessage.left
            anchors.leftMargin: 0
            anchors.top: labelMessage.bottom
            anchors.topMargin: 0
        }

        Rectangle{
            id: messageCover
            x :1500
            height: parent.height - 50
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
            width: parent.width


        }

        UiButton{
            id :btnStart
            height: 80
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.verticalCenterOffset: -60
            anchors.verticalCenter: parent.verticalCenter

            type : QmlEnumDef.BUTTON_TYPE_BLUE
            width : 200
            textValue: mdCheckupModel.step === 0 ? qsTr("Start") : qsTr("Retry")

            visible: mdCheckupModel.step === 0 || mdCheckupModel.step === 7

            onSignalEventClicked: {
                uiPanel.startNextStep();
            }
        }

        UiButton{
            id : btnCancle
            height: 80
            textValue: qsTr("Cancle")
            anchors.verticalCenterOffset: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 100
            width : 200

            onSignalEventClicked: {
                mdCheckupModel.onCommandCancle();
                finishCheckup();
            }
        }
    }

    Item{
        id: panelResult
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: panelMessageBox.bottom
        anchors.topMargin: 0

        visible: mdCheckupModel.step == QmlEnumDef.CHECKUP_RESULT_STEP

        UiLabelContent
        {
            height: 70
            anchors.top: parent.top
            anchors.topMargin: 124
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 100
            textValue: qsTr("· Metal detector check datetime : ") + mdCheckupModel.chekcupDateTime
        }

        UiLabelSystem
        {
            id: labelResult
            x: 100
            width: 100
            height: 50
            anchors.right: lampResult.left
            anchors.rightMargin: 40
            anchors.top: lampResult.top
            anchors.topMargin: 0
            textValue: qsTr("· Result")
        }

        Rectangle {
            id : lampResult
            y: 229
            width: 200
            height: 200
            radius: width/2
            anchors.left: parent.left
            anchors.leftMargin: 242
            anchors.verticalCenter: parent.verticalCenter
            border.width: 0
            color : mdCheckupModel.isPass ? "#0085FF" : "#D9001B"

            visible: false
        }

        DropShadow {
            anchors.fill : lampResult
            radius: 5
            color: "#000000"
            samples: 17
            source: lampResult
            cached: true
        }

        UiLabelContent{
            anchors.fill: lampResult
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.isPass ? qsTr("PASS") : qsTr("FAIL")
        }
    }

    Item {
        id: panelContent
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: panelMessageBox.bottom
        anchors.topMargin: 0

        visible: mdCheckupModel.step != QmlEnumDef.CHECKUP_RESULT_STEP

        Item{
            width : 305
            height: 408
            anchors.left: parent.left
            anchors.leftMargin: 120
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: parent.verticalCenter

            id: labelTimerTitle
            y: 116
            UiLabelSystem{
                height: 50
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                textValue: qsTr("· Timer");
            }

            Text{
                id:timerSec
                x: 83
                y: 116
                width: 120
                height: 120
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                font.pixelSize: 100
                font.family: FontManager.nanumGothicName
                elide: Text.ElideRight
                color : "#FFFFFF"
                text: "" + Math.ceil(timerProgress.value)
                anchors.horizontalCenter: parent.horizontalCenter
            }

            UiProgressBar{
                id:timerProgress
                y: 325
                value: 10
                max: 10
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

            }
        }
    }

    UiDivider{
        id :divider
        width: 710
        height: 2
        anchors.right: parent.right
        anchors.rightMargin: 120
        anchors.verticalCenter: panelContent.verticalCenter
    }

    UiLabelSystem{
        id : labelFe
        width: 50
        height: 194
        anchors.bottom: divider.top
        anchors.bottomMargin: 0
        anchors.left: divider.left
        anchors.leftMargin: 40

        textValue: qsTr("Fe")

    }

    Item{
        id: stepFe01

        width: 150
        height: 150
        anchors.bottom: divider.top
        anchors.bottomMargin: 25
        anchors.left: labelFe.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepFe01
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.feStep01State === 2 ? "#0085FF" :
                    mdCheckupModel.feStep01State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepFe01
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepFe01
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.feStep01State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.feStep01State === 2 ? qsTr("PASS") :
                       mdCheckupModel.feStep01State === 3 ? qsTr("FAIL") :""
        }

        BusyIndicator{
            anchors.fill: parent

            visible: mdCheckupModel.feStep01State === 1
        }
    }

    Item{
        id: stepFe02

        width: 150
        height: 150
        anchors.bottom: divider.top
        anchors.bottomMargin: 25
        anchors.left: stepFe01.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepFe02
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.feStep02State === 2 ? "#0085FF" :
                    mdCheckupModel.feStep02State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepFe02
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepFe02
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.feStep02State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.feStep02State === 2 ? qsTr("PASS") :
                       mdCheckupModel.feStep02State === 3 ? qsTr("FAIL") :""
        }

        BusyIndicator{
            anchors.fill: parent
            visible: mdCheckupModel.feStep02State === 1
        }
    }

    Item{
        id: stepFe03

        width: 150
        height: 150
        anchors.bottom: divider.top
        anchors.bottomMargin: 25
        anchors.left: stepFe02.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepFe03
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.feStep03State === 2 ? "#0085FF" :
                    mdCheckupModel.feStep03State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepFe03
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepFe03
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.feStep03State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.feStep03State === 2 ? qsTr("PASS") :
                       mdCheckupModel.feStep03State === 3 ? qsTr("FAIL") :""
        }

        BusyIndicator{
            anchors.fill: parent
            visible: mdCheckupModel.feStep03State === 1
        }
    }

    UiLabelSystem{
        id : labelSus
        width: 50
        height: 194
        anchors.top: divider.bottom
        anchors.topMargin: 0
        anchors.left: divider.left
        anchors.leftMargin: 40

        textValue: qsTr("Sus")

    }

    Item{
        id: stepSus01

        width: 150
        height: 150
        anchors.verticalCenter: labelSus.verticalCenter
        anchors.left: labelSus.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepSus01
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.susStep01State === 2 ? "#0085FF" :
                    mdCheckupModel.susStep01State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepSus01
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepSus01
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.susStep01State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.susStep01State === 2 ? qsTr("PASS") :
                       mdCheckupModel.susStep01State === 3 ? qsTr("FAIL") :""
        }
        BusyIndicator{
            anchors.fill: parent
            visible: mdCheckupModel.susStep01State === 1
        }
    }

    Item{
        id: stepSus02

        width: 150
        height: 150
        anchors.verticalCenter: labelSus.verticalCenter
        anchors.left: stepSus01.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepSus02
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.susStep02State === 2 ? "#0085FF" :
                    mdCheckupModel.susStep02State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepSus02
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepSus02
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.susStep02State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.susStep02State === 2 ? qsTr("PASS") :
                       mdCheckupModel.susStep02State === 3 ? qsTr("FAIL") :""
        }

        BusyIndicator{
            anchors.fill: parent
            visible: mdCheckupModel.susStep02State === 1
        }
    }

    Item{
        id: stepSus03

        width: 150
        height: 150
        anchors.verticalCenter: labelSus.verticalCenter
        anchors.left: stepSus02.right
        anchors.leftMargin: 50

        Rectangle {
            id : lampStepSus03
            anchors.fill: parent
            radius: parent.width/2
            border.width: 0
            color : mdCheckupModel.susStep03State === 2 ? "#0085FF" :
                    mdCheckupModel.susStep03State === 3 ? "#D9001B" : "#333333"

            visible: false
        }

        DropShadow {
            anchors.fill: lampStepSus03
            horizontalOffset: 5
            verticalOffset: 5
            radius: 5
            color: "#000000"
            samples: 17
            source: lampStepSus03
            cached: true
        }

        UiLabelContent{
            anchors.fill: parent
            horizontalAlignment : Text.AlignHCenter
            textValue: mdCheckupModel.susStep03State === 1 ? qsTr("CHECKING") :
                       mdCheckupModel.susStep03State === 2 ? qsTr("PASS") :
                       mdCheckupModel.susStep03State === 3 ? qsTr("FAIL") :""
        }

        BusyIndicator{
            anchors.fill: parent
            visible: mdCheckupModel.susStep03State === 1
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
