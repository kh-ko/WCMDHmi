import QtQuick 2.12
import QtQuick.Controls 2.5
import ViewManager 1.0
import "."
import "../../../../control"
import QtQuick.Layouts 1.3
import QmlEnumDef 1.0
import PanelWCGraphModel 1.0

UiPanel {
    property PanelWCGraphModel graphModel : null

    id : panel
    clip : true

    type : QmlEnumDef.PANEL_TYPE_DROP

    Component.onCompleted: {
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

    Canvas{
        property int centerY : height*0.5

        id: canvasRaw
        anchors.left: parent.left
        anchors.leftMargin: 150
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 10

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

            for(var i = 0; i < panel.graphModel.runtimePointCnt; i ++)
            {
                var value = panel.graphModel.onCommandGetRuntimeRawPointValue(i);
                var yPosition = height - (height * (value / graphModel.range))
                var xPosition = width * (i / graphModel.totalRuntimePointCnt)

                if(i === 0)
                {
                    ctx.moveTo(0,yPosition);
                }

                ctx.lineTo(xPosition,yPosition);
                ctx.moveTo(xPosition,yPosition);

            }

            ctx.stroke();
        }
    }

    Canvas{
        property int centerY : height*0.5

        id: canvasFilter
        anchors.left: parent.left
        anchors.leftMargin: 150
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 10

        enabled: false
        antialiasing: false
        smooth: false
        anchors.fill: parent
        renderTarget : Canvas.FramebufferObject

        onPaint :{
            var ctx = canvasFilter.getContext("2d")

            ctx.reset();
            ctx.lineWidth = 4
            ctx.strokeStyle = "#FFDF25"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            ctx.beginPath()

            for(var i = 0; i < panel.graphModel.runtimePointCnt; i ++)
            {
                var value = panel.graphModel.onCommandGetRuntimePointValue(i);
                var yPosition = height - (height * (value / graphModel.range))
                var xPosition = width * (i / graphModel.totalRuntimePointCnt)

                if(i === 0)
                {
                    ctx.moveTo(0,yPosition);
                }

                ctx.lineTo(xPosition,yPosition);
                ctx.moveTo(xPosition,yPosition);

            }

            ctx.stroke();
        }
    }

    Item {

        property int idx : 10
        id: line10

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 10) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 9
        id: line09

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 9) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 8
        id: line08

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue:(((graphModel.lineInterval * 8) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 7
        id: line07

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 7) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 6
        id: line06

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 6) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 5
        id: line05

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue:(((graphModel.lineInterval * 5) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)

        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 4
        id: line04

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 4) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)
        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 3
        id: line03

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 3) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)

        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 2
        id: line02

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 2) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)

        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 1
        id: line01

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue:(((graphModel.lineInterval * 1) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)

        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

    Item {

        property int idx : 0
        id: line00

        height: 20
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: (canvasFilter.height * ((graphModel.lineInterval * idx) / graphModel.range)) - (height / 2)
        anchors.right: canvasFilter.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        UiLabelGraph{
            width: 130
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            textValue: (((graphModel.lineInterval * 0) + graphModel.minRange) / 1000).toLocaleString(ViewManager.locale, 'f', 3)

        }

        Rectangle{
            height: 1
            color: "#acacac"
            anchors.left: parent.left
            anchors.leftMargin: 150
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 0

        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
