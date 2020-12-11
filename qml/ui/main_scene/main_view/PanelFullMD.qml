import QtQuick 2.0
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import FontManager 1.0
import EnumDefine 1.0
import ViewManager 1.0
import PanelFullMDModel 1.0

Item {
    property Gradient errGradient : Gradient {
        GradientStop {
            position: 0
            color: "#FFA4A4"
        }
        GradientStop {
            position: 1
            color: "#FF2F2F"
        }
    }
    property Gradient norGradient : Gradient {
        GradientStop {
            position: 0
            color: "#599BD7"
        }

        GradientStop {
            position: 1
            color: "#005DB3"
        }
    }

    id : panel

    width : 1503
    height: 837


    PanelFullMDModel
    {
        id :model

        onSignalEventAddedValue: {
            barGraph.updateGraph();

            if(type === EnumDefine.METAL_DETECT_TYPE)
            {
                showAni.start();
                timer.restart();
            }
        }

        onSignalEventChangedPDSeq : {
            barGraph.updateGraph();
        }
    }

    Timer {
        id : timer
        interval: 4000; running: false; repeat: false
        onTriggered:
        {
            closeAni.start()
        }
    }

    ParallelAnimation {
        id :showAni

        NumberAnimation {
            target: highlight
            properties: "opacity"
            duration: 250
            from : 0
            to: 0.5
            easing.type: Easing.InOutQuad
        }
    }

    ParallelAnimation {
        id :closeAni

        NumberAnimation {
            target: highlight
            properties: "opacity"
            duration: 250
            from : 0.5
            to: 0
            easing.type: Easing.InOutQuad
        }
    }

    UiPanel{
        id: bg
        anchors.fill: parent

        type : EnumDefine.PANEL_TYPE_BIG_MD

        Rectangle {
            id: totalArea
            color: "#59000000"
            radius: 10
            height: 386
            width : (parent.width / 2) - (anchors.leftMargin) -20

            anchors.top: parent.top
            anchors.topMargin: 70
            anchors.left: parent.left
            anchors.leftMargin: 45

            Text{
                id:labelTotal

                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 45

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                font.pixelSize: 40
                font.family: FontManager.nanumGothicName

                color : "#FFFFFF"
                text: qsTr("Total")
            }

            Text{
                id:textTotal

                anchors.top: labelTotal.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 45
                anchors.right: parent.right
                anchors.rightMargin: 45
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignRight
                font.pixelSize: 150
                font.family: FontManager.nanumGothicName

                color : "#FFFFFF"
                text: model.mTotalCnt.toLocaleString(ViewManager.locale, 'f', 0)
            }
        }

        Rectangle {
            id: detectArea
            color: "#59000000"
            radius: 10
            height: 386

            anchors.top: parent.top
            anchors.topMargin: 70
            anchors.left: totalArea.right
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 45

            Text{
                id:labelDetect

                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 45

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignLeft
                font.pixelSize: 40
                font.family: FontManager.nanumGothicName

                color : "#FFFFFF"
                text: qsTr("Detect")
            }

            Text{
                id:textDetect

                anchors.top: labelDetect.bottom
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 45
                anchors.right: parent.right
                anchors.rightMargin: 45
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment : Text.AlignRight
                font.pixelSize: 150
                font.family: FontManager.nanumGothicName

                color : "#FFFFFF"
                text: model.mDetectCnt.toLocaleString(ViewManager.locale, 'f', 0)
            }
        }

        Glow {
            id : highlight
            anchors.fill: detectArea
            radius: 10
            samples: 17
            source: detectArea
            color: "#FD4359"
            opacity: 0
        }

        Item
        {
            id : mdTrendsArea
            height: 312
            anchors.left: parent.left
            anchors.leftMargin: 45
            anchors.right: parent.right
            anchors.rightMargin: 45
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 25

            Item
            {
                id : graphController
                width: 259
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0

                UiButton{
                    isImage : true
                    imageSource: "img_btn/up.png"
                    width: (parent.width / 2) - 5
                    height: 90

                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0

                    onSignalEventClicked: {
                        var newValue = model.mTempSenstivity * 1.1

                        if(newValue < 1)
                            newValue = 1

                        if(newValue > 9999)
                            newValue = 9999

                        model.onCommandSetTempSenstivity(newValue)
                    }
                }

                UiButton{

                    isImage : true
                    imageSource: "img_btn/down.png"
                    width: (parent.width / 2) - 5
                    height: 90

                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    onSignalEventClicked: {
                        var newValue = model.mTempSenstivity * 0.9

                        if(newValue < 1)
                            newValue = 1

                        if(newValue > 9999)
                            newValue = 9999

                        model.onCommandSetTempSenstivity(newValue)
                    }
                }

                Rectangle
                {
                    id : inputSenstivityBorder

                    width: 344
                    height: 94
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0

                    radius: 20
                    color : "#FD4359"

                    UiInputNumber
                    {
                        id: inputSenstivity

                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.topMargin: 2
                        anchors.bottomMargin: 2
                        anchors.leftMargin: 2
                        anchors.rightMargin: 2

                        isHighlight : model.mSenstivity !== model.mTempSenstivity
                        isLocaleStyle: false
                        postfix: "mv"
                        bgColor: "#232323"

                        numberValue : model.mTempSenstivity
                        min         : 1
                        max         : 9999

                        onSignalChangeValue: {
                            model.onCommandSetTempSenstivity(value)
                        }
                    }
                }

                UiButton{
                    textValue: qsTr("Apply")
                    width: parent.width
                    height: 90

                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0

                    onSignalEventClicked: {
                        inputPassword.textValue = ""
                        ViewManager.keypad.showKeypad(inputPassword.getVInputText())
                    }
                }
            }

            Rectangle{
                id : barGraphArea

                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: graphController.left
                anchors.rightMargin: 20

                radius: 10
                color : "#59000000"

                UiTrendsBarGraph
                {
                    id : barGraph

                    function updateGraph()
                    {
                        clearValue();

                        for(var i = 0; i < model.onCommandGetTRCount(); i ++)
                        {
                            var gradient = (model.onCommandGetTRIsTradeEvent(i) === false ? errGradient : norGradient)
                            barGraph.addValue(i, model.onCommandGetTRValue(i), gradient);
                        }
                    }

                    Component.onCompleted: {
                        updateGraph();
                    }

                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 20
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    maxValue : model.mTempSenstivity * 2
                    maxCnt   : model.mGraphMaxCnt
                }

                Rectangle{
                    id : senstivityLine
                    height: 2
                    width : barGraph.width + 20 + 20

                    anchors.bottom: barGraph.bottom
                    anchors.bottomMargin:( barGraph.height * (model.mTempSenstivity / barGraph.maxValue))
                    anchors.left: barGraph.left
                    anchors.leftMargin: 0

                    color: "#FD4359"
                }
            }
        }
    }



    UiInputPassword{
        id : inputPassword
        width: 0
        height: 0
        textValue: ""
        labelText : qsTr("Please enter your password.")

        onSignalChangeText: {
            if(model.onCommandCompareAdminPwd(value) || model.onCommandComparePwd(value))
            {
                model.onCommandApplySenstivity();
            }
            else
            {
                toast.show(qsTr("Please check password"));
            }
        }
    }
}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1;anchors_height:100;anchors_width:50}D{i:3;anchors_width:125}
}
##^##*/
