import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ViewManager 1.0
import FontManager 1.0
import QmlEnumDef 1.0
import EnumDef 1.0
import "."
import "../../../../control/"
//import "./main_view"
import "../../img/sens_setting"
import PanelMDGraphModel 1.0
import MetalDetectorGraphModel 1.0

UiPanel {

    id : panel
    width: 1340
    height: 880

    type: QmlEnumDef.PANEL_TYPE_UP_PANEL

    property MetalDetectorGraphModel graphModel : null
    property int    selIdx : 0
    property int    sensorCnt : 2
    property bool   isRawGraphOn : false
    property int    senstivity : 300
    property int    range : 1000
    property int    min : 0
    property int    max : 0




    UiInputNumber
    {
        id: inputRange
        width: 470
        height: 60
        anchors.left: graph.left
        anchors.bottom: graph.top
        anchors.leftMargin: 0
        anchors.bottomMargin: 20


        inputWidth: 250
        labelText: qsTr("· Graph Range")
        isLocaleStyle: false
        postfix: "mv"
        bgColor: panel.bgColor

        numberValue : 10
        min         : 10
        max         : 9999

        onSignalChangeValue: {
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
        anchors.right: valueMax.left
        anchors.rightMargin: 20
        textValue: qsTr("· Max")
    }

    UiLabelContent
    {
        id : valueMax
        width: 120
        height: 80
        anchors.verticalCenter: inputRange.verticalCenter
        anchors.right: labelMin.left
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 100

        textValue: "10"
    }

    UiLabelSystem{
        id : labelMin
        width: 100
        height: 80
        anchors.verticalCenter: inputRange.verticalCenter
        anchors.right: valueMin.left
        anchors.rightMargin: 20
        textValue: qsTr("· Min")
    }

    UiLabelContent
    {
        id : valueMin
        width: 120
        height: 80
        anchors.verticalCenter: inputRange.verticalCenter
        anchors.right: graph.right
        horizontalAlignment: Text.AlignRight
        anchors.rightMargin: 0

        textValue: "11"
    }

    UiInputNumber
    {
        id: inputSenstivity
        width: 470
        height: 60
        anchors.left: parent.left
        anchors.top: parent.top
        postfix: "mv"
        anchors.leftMargin: 40
        anchors.topMargin: 40

        isHighlight : true
        inputWidth: 250
        labelText: qsTr("· Senstivity")
        isLocaleStyle: false
        //postfix: "mv"
        bgColor: panel.bgColor

        numberValue : 10
        min         : 10
        max         : 9999

        onSignalChangeValue: {
        }

        Text {
            color: "#acacac"
            text: "±"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 237
            font.pixelSize: 30
            anchors.verticalCenterOffset: 0
        }
    }


    UiButton{
        id : btnExpend
        width: 140
        height: 60
        anchors.verticalCenter: inputSenstivity.verticalCenter
        anchors.left: inputSenstivity.right
        anchors.leftMargin: 10

        isImage: true
        imageSource: "img/sens_setting/expend.png"

        onSignalEventClicked:
        {

        }

    }

    UiButton{
        id : btnCompress
        width: 140
        height: 60
        anchors.verticalCenter: inputSenstivity.verticalCenter
        anchors.left: btnExpend.right
        anchors.leftMargin: 10

        isImage: true
        imageSource: "img/sens_setting/compress.png"

        onSignalEventClicked:
        {

        }

    }


    UiButton{
        id : btnSens01
        height: 60
        anchors.right: btnSens02.left
        anchors.top: inputSenstivity.bottom
        anchors.topMargin: 20
        anchors.rightMargin: 20
        width: 140

        textValue: qsTr("S1")

        onSignalEventClicked:
        {
        }
    }

    UiButton{
        id : btnSens02
        height: 60
        anchors.verticalCenter: btnSens01.verticalCenter
        anchors.right: btnSens03.left
        anchors.rightMargin: 20
        width: 140

        textValue: qsTr("S2")

        onSignalEventClicked:
        {
        }
    }

    UiButton{
        id : btnSens03
        height: 60
        anchors.verticalCenter: btnSens01.verticalCenter
        anchors.right: btnSens04.left
        anchors.rightMargin: 20
        width: 140

        textValue: qsTr("S3")

        onSignalEventClicked:
        {
        }
    }

    UiButton{
        id : btnSens04
        height: 60
        anchors.verticalCenter: btnSens01.verticalCenter
        anchors.right: btnSens05.left
        anchors.rightMargin: 20
        width: 140

        textValue: qsTr("S4")

        onSignalEventClicked:
        {
        }
    }

    UiButton{
        id : btnSens05
        height: 60
        anchors.verticalCenter: btnSens01.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 40
        width: 140

        textValue: qsTr("S5")

        onSignalEventClicked:
        {
        }
    }

    UiPanel{
        id :graph
        height: 405
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: btnSens01.bottom
        anchors.topMargin: 160
        anchors.leftMargin: 40
        anchors.rightMargin: 40

        clip: true
        type : QmlEnumDef.PANEL_TYPE_DROP

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
        width: 160
        height: 60
        anchors.right: btnNext.left
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        textValue: qsTr("Pre")
    }

    UiButton{
        id : btnNext
        width: 160
        height: 60
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.rightMargin: 40
        textValue: qsTr("Next")

    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:4}D{i:6}
}
##^##*/
