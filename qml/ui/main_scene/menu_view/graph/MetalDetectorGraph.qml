import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import EnumDefine 1.0
import MetalDetectorGraphModel 1.0

UiPanel {
    property bool isSelect : false
    property int viewMode : EnumDefine.MD_GRAPH_ALONE

    property MetalDetectorGraphModel graphModel : null

    property int  axisLevel: (canvasFilter.height/2) * ((graphModel.lineInterval) / graphModel.range) <  lineZero.height / 2 ? 2 :
                             (canvasFilter.height/2) * ((graphModel.lineInterval) / graphModel.range) <  lineZero.height     ? 1 : 0

    signal signalEventClicked()

    id : panel
    clip : true

    type : isSelect ? EnumDefine.PANEL_TYPE_DROP_SELECT : EnumDefine.PANEL_TYPE_DROP

    Component.onCompleted: {
        graphModel.onCommandSetGraphWidth(canvasFilter.width)
    }

    Connections{
        target: graphModel
        onSignalEventChangedGraph: {
            if(canvasRaw.available )
            {
                canvasRaw.requestPaint()
            }
            if(canvasFilter.available )
            {
                canvasFilter.requestPaint()
            }
        }
    }

    Item{
        id : indiMinMax
        width: 200
        height: 80
        anchors.top: parent.top
        anchors.topMargin: panel.viewMode == EnumDefine.MD_GRAPH_ALONE ? 20 : (parent.height / 2) - (height / 2)
        anchors.right: parent.right
        anchors.rightMargin: 20

        UiLabelSystem{
            id: labelMax
            width: 73
            height: 30
            textValue: qsTr("· Max")
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        UiLabelContent{
            width: 88
            height: 30
            anchors.left: labelMax.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelMax.verticalCenter

            horizontalAlignment: Text.AlignRight
            textValue: graphModel.max

        }

        UiLabelSystem{
            id: labelMin
            width: 73
            height: 30
            textValue: qsTr("· Min")
            anchors.top: labelMax.bottom
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        UiLabelContent{
            width: 88
            height: 30
            anchors.left: labelMin.right
            anchors.leftMargin: 10
            anchors.verticalCenter: labelMin.verticalCenter

            horizontalAlignment: Text.AlignRight
            textValue: graphModel.min

        }

        UiLamp{
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            isOn : panel.graphModel.isDetect
        }
    }

    Canvas{
        property int centerY : height*0.5

        id: canvasRaw
        anchors.left: parent.left
        anchors.leftMargin: 69
        anchors.top: parent.top
        anchors.topMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 115 : 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 20 : 10
        anchors.right: parent.right
        anchors.rightMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 20 : indiMinMax.width + 40

        enabled: false
        antialiasing: false
        smooth: false
        anchors.fill: parent
        renderTarget : Canvas.FramebufferObject

        visible: panel.graphModel.isRawGraphOn

        onPaint :{

            if(panel.graphModel.isRawGraphOn == false)
                return;

            var ctx = canvasRaw.getContext("2d")

            ctx.reset();
            ctx.lineWidth = 1
            ctx.strokeStyle = "#0085FF"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            ctx.beginPath()

            for(var i = 0; i < panel.graphModel.pointCnt; i ++)
            {
                var value = panel.graphModel.onCommandGetRawPointValue(i);
                var yPosition = centerY + ((centerY * value / graphModel.range) * (-1))

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

    Canvas{
        property int centerY : height*0.5

        id: canvasFilter
        anchors.left: parent.left
        anchors.leftMargin: 69
        anchors.top: parent.top
        anchors.topMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 115 : 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 20 : 10
        anchors.right: parent.right
        anchors.rightMargin: panel.viewMode === EnumDefine.MD_GRAPH_ALONE ? 20 : indiMinMax.width + 40

        enabled: false
        antialiasing: false
        smooth: false
        anchors.fill: parent
        renderTarget : Canvas.FramebufferObject

        onWidthChanged: {
            graphModel.onCommandSetGraphWidth(canvasFilter.width)
        }

        onPaint :{
            var ctx = canvasFilter.getContext("2d")

            ctx.reset();
            ctx.lineWidth = 4
            ctx.strokeStyle = "#FFDF25"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            ctx.beginPath()

            for(var i = 0; i < panel.graphModel.pointCnt; i ++)
            {
                var value = panel.graphModel.onCommandGetFilterPointValue(i);
                var yPosition = centerY + ((centerY * value / graphModel.range) * (-1))

                if(i === 0)
                {
                    ctx.moveTo(0,yPosition);
                }

                ctx.lineTo(i,yPosition);
                ctx.moveTo(i,yPosition);

            }

            ctx.stroke();
        }

        Item {
            id: lineP05
            height: 20
            anchors.verticalCenterOffset: -1 * (canvasFilter.height/2) * ((graphModel.lineInterval * 5) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel == 0

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: (graphModel.lineInterval * 5)

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
            anchors.verticalCenterOffset: -1 * (canvasFilter.height/2) * ((graphModel.lineInterval * 4) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel != 2

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: (graphModel.lineInterval * 4)

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
            anchors.verticalCenterOffset: -1 * (canvasFilter.height/2) * ((graphModel.lineInterval * 3) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel == 0 || panel.axisLevel  == 2

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: (graphModel.lineInterval * 3)

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
            anchors.verticalCenterOffset: -1 * (canvasFilter.height/2) * ((graphModel.lineInterval * 2) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel != 2

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: (graphModel.lineInterval * 2)

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
            anchors.verticalCenterOffset: -1 * (canvasFilter.height/2) * ((graphModel.lineInterval) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel == 0

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: (graphModel.lineInterval)

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
            anchors.verticalCenterOffset: (canvasFilter.height/2) * ((graphModel.lineInterval) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel == 0

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: "-" + (graphModel.lineInterval)

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
            anchors.verticalCenterOffset: (canvasFilter.height/2) * ((graphModel.lineInterval * 2) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel < 2

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: "-" + (graphModel.lineInterval * 2)

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
            anchors.verticalCenterOffset: (canvasFilter.height/2) * ((graphModel.lineInterval * 3) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel != 1

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: "-" + (graphModel.lineInterval * 3)

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
            anchors.verticalCenterOffset: (canvasFilter.height/2) * ((graphModel.lineInterval * 4) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel < 2

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: "-" + (graphModel.lineInterval * 4)

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
            anchors.verticalCenterOffset: (canvasFilter.height/2) * ((graphModel.lineInterval * 5) / graphModel.range)
            anchors.verticalCenter: parent.verticalCenter

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -60

            visible: panel.axisLevel == 0

            UiLabelGraph{
                width: 50
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                textValue: "-" + (graphModel.lineInterval * 5)

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
            anchors.verticalCenterOffset: -1 * (canvasFilter.height / 2 ) * (graphModel.senstivity/graphModel.range)
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
            anchors.verticalCenterOffset: (canvasFilter.height / 2 ) * (graphModel.senstivity/graphModel.range)
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

    MouseArea
    {
        anchors.fill: parent

        onClicked: {
            signalEventClicked()
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:8;anchors_width:765;anchors_x:41}
}
##^##*/
