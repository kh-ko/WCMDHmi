import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ViewManager 1.0
import FontManager 1.0
import EnumDefine 1.0
import "."
import "../../control/"
import "./main_view"
import "./menu_view"
import PanelMDGraphModel 1.0
import MetalDetectorGraphModel 1.0

Rectangle {
    property MetalDetectorGraphModel graphModel : null

    signal signalEventClose()

    id: panel
    color : "#00000000"

    Component.onCompleted: {
        panel.graphModel = model.onCommandGetGraphModel(0)

        for(var i = 0; i < model.sensorCnt; i ++)
        {
            model.onCommandGetGraphModel(i).onCommandSetGraphWidth(canvas.width)
        }
    }

    PanelMDGraphModel {
        id : model

        onSignalEventGraphUpdate : {
            canvas.requestPaint();
        }

        onSignalEventChangedSensorCnt: {
            for(var i = 0; i < model.sensorCnt; i ++)
            {
                model.onCommandGetGraphModel(i).onCommandSetGraphWidth(canvas.width)
            }
        }

        onSignalResultSaveProductSetting: {
            if(error === EnumDefine.SQL_ERROR)
            {
                ViewManager.toast.show(qsTr("SQL error is occured."))
            }
            else if(error === EnumDefine.NOT_EXIST_SEQ)
            {
                ViewManager.toast.show(qsTr("This product dose not exist."))
            }
            else if(error === EnumDefine.ALREADY_NO_ERROR)
            {
                ViewManager.toast.show(qsTr("The Product no already exists."))
            }
            else if(error === EnumDefine.EMPTY_PRODUCT_NO)
            {
                ViewManager.toast.show(qsTr("Please enter product no."))
            }
            else
            {
                ViewManager.toast.show(qsTr("Your settings have been saved."))
            }
        }

    }

    UiPanel {
        id: uiPanel

        property int    selIdx : 0
        property int    sensorCnt : 2
        property bool   isRawGraphOn : false
        property int    senstivity : 300
        property int    range : 1000
        property int    min : 0
        property int    max : 0

        width : 1500
        height : 700
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        title: qsTr("Metal senstivity setting")

        type : EnumDefine.PANEL_TYPE_POPUP

        MouseArea{
            anchors.fill: parent
            onClicked: {}
        }

        UiInputNumber
        {
            id: inputRange
            width: 420
            height: 60
            anchors.top: parent.top
            anchors.topMargin: uiPanel.titleHeight
            anchors.left: parent.left
            anchors.leftMargin: 20


            inputWidth: 200
            labelText: qsTr("· Graph Range")
            isLocaleStyle: false
            postfix: "mv"
            bgColor: uiPanel.bgColor

            numberValue : model.range
            min         : 10
            max         : 9999

            onSignalChangeValue: {
                model.onCommandSetRange(value);
            }

            Text {
                color: "#acacac"
                text: "±"
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 237
                font.pixelSize: 30
            }
        }

        UiLabelSystem{
            id : labelMax
            width: 100
            height: 80
            anchors.verticalCenter: inputRange.verticalCenter
            textValue: qsTr("· Max")
            anchors.left: inputRange.right
            anchors.leftMargin: 100
        }

        UiLabelContent
        {
            id : valueMax
            width: 120
            height: 80
            anchors.verticalCenter: labelMax.verticalCenter
            anchors.left: labelMax.right
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignRight

            textValue: model.max
        }

        UiLabelSystem{
            id : labelMin
            width: 100
            height: 80
            anchors.verticalCenter: valueMax.verticalCenter
            textValue: qsTr("· Min")
            anchors.left: valueMax.right
            anchors.leftMargin: 100
        }

        UiLabelContent
        {
            width: 120
            height: 80
            anchors.verticalCenter: labelMin.verticalCenter
            anchors.left: labelMin.right
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignRight

            textValue: model.min //panel.min
        }

        UiInputNumber
        {
            id: inputSenstivity
            width: 340
            height: 60
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20

            isHighlight : model.isEditSenstivity
            inputWidth: 200
            labelText: qsTr("· Senstivity")
            isLocaleStyle: false
            //postfix: "mv"
            bgColor: uiPanel.bgColor

            numberValue : model.senstivity
            min         : 10
            max         : 9999

            onSignalChangeValue: {
                model.onCommandSetSenstivity(value)
            }

            Text {
                color: "#acacac"
                text: "±"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 164
                font.pixelSize: 30
            }
        }

        UiButton{
            id : btnExpend
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.top: inputSenstivity.bottom
            anchors.topMargin: 20
            anchors.left: inputSenstivity.left
            anchors.leftMargin: 0

            isImage: true
            imageSource: "img/sens_setting/expend.png"

            onSignalEventClicked:
            {
                var sens = model.senstivity + 10;

                if(sens > 9999)
                {
                    sens = 9999
                }

                model.onCommandSetSenstivity(sens)
            }

        }

        UiButton{
            id : btnCompress
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.top: inputSenstivity.bottom
            anchors.topMargin: 20
            anchors.right: inputSenstivity.right
            anchors.rightMargin: 0

            isImage: true
            imageSource: "img/sens_setting/compress.png"

            onSignalEventClicked:
            {
                var sens = model.senstivity - 10;

                if(sens < 1)
                {
                    sens = 1
                }

                model.onCommandSetSenstivity(sens)
            }
        }

        UiButton{
            id : btnSens01
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            visible: model.simpleSens01 > 0
            textValue: qsTr("S1")

            onSignalEventClicked:
            {
                model.onCommandSetSimpleSens01()
            }
        }

        UiButton{
            id : btnSens02
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: btnSens01.right
            anchors.leftMargin: 20

            visible: model.simpleSens02 > 0
            textValue: qsTr("S2")

            onSignalEventClicked:
            {
                model.onCommandSetSimpleSens02()
            }
        }

        UiButton{
            id : btnSens03
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: btnSens02.right
            anchors.leftMargin: 20

            visible: model.simpleSens03 > 0
            textValue: qsTr("S3")

            onSignalEventClicked:
            {
                model.onCommandSetSimpleSens03()
            }
        }

        UiButton{
            id : btnSens04
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: btnSens03.right
            anchors.leftMargin: 20

            visible: model.simpleSens04 > 0
            textValue: qsTr("S4")

            onSignalEventClicked:
            {
                model.onCommandSetSimpleSens04()
            }
        }

        UiButton{
            id : btnSens05
            height: 80
            width: (inputSenstivity.width / 2) - 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.left: btnSens04.right
            anchors.leftMargin: 20

            visible: model.simpleSens05 > 0
            textValue: qsTr("S5")

            onSignalEventClicked:
            {
                model.onCommandSetSimpleSens05()
            }
        }

        UiPanel{
            id :graph
            anchors.top: inputRange.bottom
            anchors.topMargin: 40
            anchors.left: inputSenstivity.right
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: btnClose.top
            anchors.bottomMargin: 20

            clip: true
            type : EnumDefine.PANEL_TYPE_DROP

            Canvas{
                property int centerY : height*0.5

                id: canvas
                anchors.left: parent.left
                anchors.leftMargin: 75
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 20

                enabled: false
                antialiasing: false
                smooth: false
                anchors.fill: parent
                renderTarget : Canvas.FramebufferObject

                onPaint:
                {

                    var ctx = canvas.getContext("2d")
                    var color = ["#FFDF25","#0085FF","#D9001B","#95F204","#8400FF", "#00FFFF", "#F59A23", "#FFFFFF"]
                    ctx.reset();
                    ctx.lineWidth = 4
                    //ctx.strokeStyle = "#FFDF25"
                    ctx.fillStyle = "#00000000"
                    ctx.lineCap = "round"

                    //ctx.beginPath()

                    for(var gIdx = 0; gIdx < model.sensorCnt ; gIdx ++)
                    {
                        var tempGraphModel = model.onCommandGetGraphModel(gIdx);

                        ctx.strokeStyle = color[gIdx]
                        ctx.beginPath()

                        for(var i = 0; i < tempGraphModel.pointCnt; i ++)
                        {
                            var value = tempGraphModel.onCommandGetFilterPointValue(i);
                            var yPosition = centerY + ((centerY * value / tempGraphModel.range) * (-1))

                            if(i === 0)
                            {
                                ctx.moveTo(0,yPosition);
                            }

                            ctx.lineTo(i,yPosition);
                            ctx.moveTo(i,yPosition);
                        }

                        ctx.stroke();
                    }

                }

                Item {
                    id: lineP05
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height/2) * ((panel.graphModel.lineInterval * 5) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: (panel.graphModel.lineInterval * 5)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineP04
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height/2) * ((panel.graphModel.lineInterval * 4) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: (panel.graphModel.lineInterval * 4)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineP03
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height/2) * ((panel.graphModel.lineInterval * 3) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: (panel.graphModel.lineInterval * 3)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineP02
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height/2) * ((panel.graphModel.lineInterval * 2) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: (panel.graphModel.lineInterval * 2)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineP01
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height/2) * ((panel.graphModel.lineInterval) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: (panel.graphModel.lineInterval)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineZero
                    height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "0"

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineM01
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height/2) * ((panel.graphModel.lineInterval) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "-" + (panel.graphModel.lineInterval)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineM02
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height/2) * ((panel.graphModel.lineInterval * 2) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "-" + (panel.graphModel.lineInterval * 2)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: lineM03
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height/2) * ((panel.graphModel.lineInterval * 3) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "-" + (panel.graphModel.lineInterval * 3)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {

                    id: lineM04
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height/2) * ((panel.graphModel.lineInterval * 4) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "-" + (panel.graphModel.lineInterval * 4)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {

                    id: lineM05
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height/2) * ((panel.graphModel.lineInterval * 5) / panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    UiLabelGraph{
                        width: 50
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        textValue: "-" + (panel.graphModel.lineInterval * 5)

                    }

                    Rectangle{
                        height: 1
                        color: "#acacac"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }

                Item {
                    id: linePSens
                    height: 20
                    anchors.verticalCenterOffset: -1 * (canvas.height / 2 ) * (panel.graphModel.senstivity/panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    Rectangle{
                        height: 1
                        color: "#D9001B"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                }

                Item {
                    id: lineMSens
                    height: 20
                    anchors.verticalCenterOffset: (canvas.height / 2 ) * (panel.graphModel.senstivity/panel.graphModel.range)
                    anchors.verticalCenter: parent.verticalCenter

                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: -60

                    Rectangle{
                        height: 1
                        color: "#D9001B"
                        anchors.left: parent.left
                        anchors.leftMargin: 60
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 0

                    }
                }
            }
        }

        UiButton{
            id :btnApply
            height: 80
            textValue: qsTr("Apply")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.right: btnClose.left
            anchors.rightMargin: 20

            type : EnumDefine.BUTTON_TYPE_BLUE

            visible: model.isEditSenstivity

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

            type : EnumDefine.BUTTON_TYPE_POPUP

            onSignalEventClicked: {
                panel.signalEventClose()
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}
}
##^##*/
