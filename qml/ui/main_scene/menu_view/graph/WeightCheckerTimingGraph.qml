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
        onSignalEventChangedTimingGraph: {
            if(canvasFilter.available )
            {
                canvasFilter.requestPaint()
            }

            for(var i = 0; i < measureAreaContainer.children.length; i ++)
            {
                measureAreaContainer.children[i].destroy();
            }

            if(graphModel.onCommandMeasureAreaCnt() > 0)
            {
                for( i =0; i < graphModel.onCommandMeasureAreaCnt(); i ++)
                {
                    var measurePointCnt = graphModel.onCommandGetGraphMeasurePointCntList(i)
                    var areaWidth = canvasFilter.width * (measurePointCnt / graphModel.timingPointCnt)
                    var areaStartIdx = graphModel.onCommandGetGraphMeasureStartIdxList(i);

                    var areaStartX = canvasFilter.width * (areaStartIdx / graphModel.timingPointCnt)
                    measureArea.createObject(measureAreaContainer, {"height":canvasFilter.height, "width":areaWidth, "x" : areaStartX, "y":0});
                }
            }
        }

        onSignalEventChangedMinRange:
        {
            if(canvasFilter.available )
            {
                canvasFilter.requestPaint()
            }
        }

        onSignalEventChangedMaxRange:
        {
            if(canvasFilter.available )
            {
                canvasFilter.requestPaint()
            }
        }
    }

    Item{
        id : measureAreaContainer
        anchors.fill: canvasFilter
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
            ctx.strokeStyle = "#0085FF"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            ctx.beginPath()

            for(var i = 0; i < panel.graphModel.timingPointCnt; i ++)
            {
                var value = panel.graphModel.onCommandGetTimingPointValue(i);
                var yPosition = height - (height * (value / graphModel.range))
                var xPosition = width * (i / graphModel.timingPointCnt)

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

    Rectangle {
        id: measureCueSignLine

        width:2
        anchors.top: canvasFilter.top
        anchors.topMargin: 0
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: 0
        anchors.left: canvasFilter.left
        anchors.leftMargin: graphModel.timingPointCnt === 0 ? 0 :canvasFilter.width * (graphModel.measuredCueLineIdx / graphModel.timingPointCnt)

        color: "#0085FF"
        visible: graphModel.measuredStartIdx > 0

    }

    Rectangle {
        id: measureSectionLine

        width:2
        anchors.top: canvasFilter.top
        anchors.topMargin: 0
        anchors.bottom: canvasFilter.bottom
        anchors.bottomMargin: 0
        anchors.left: canvasFilter.left
        anchors.leftMargin: graphModel.timingPointCnt === 0 ? 0 :canvasFilter.width * (graphModel.measuredSectionLineIdx / graphModel.timingPointCnt)

        color: "#FFFF00"
        visible: graphModel.measuredStartIdx > 0
    }

    MouseArea{

        property var selectLine : 0
        anchors.fill: canvasFilter;
        drag.target: parent

        visible: graphModel.measuredStartIdx > 0

        onPressed: {
            console.debug("[debug] onPress mX : " + mouseX + ", measuredLine03.anchors.leftMargin : " + measureCueSignLine.anchors.leftMargin + ", measuredLine04.anchors.leftMargin :" + measureSectionLine.anchors.leftMargin)

            if( mouseX > (measureSectionLine.anchors.leftMargin - 10) && mouseX <  (measureSectionLine.anchors.leftMargin + 10))
                selectLine = 4;
            else if( mouseX > (measureCueSignLine.anchors.leftMargin - 10) && mouseX <  (measureCueSignLine.anchors.leftMargin + 10))
                selectLine = 3;
            else
                selectLine = 0;
        }

        onMouseXChanged:
        {
            console.debug("[debug] selectLine" + selectLine)

            if(selectLine == 3){
                var cueSigneIdx = (mouseX / canvasFilter.width) *  graphModel.timingPointCnt

                console.debug("[debug] cueSigneIdx" + cueSigneIdx)

                graphModel.onCommandSetMeasureCueSignLineIdx(cueSigneIdx)
            }
            else if(selectLine == 4){
                var sectionIdx = (mouseX / canvasFilter.width) *  graphModel.timingPointCnt

                console.debug("[debug] sectionIdx" + cueSigneIdx)

                graphModel.onCommandSetMeasureSectionLineIdx(sectionIdx)
            }
        }
    }

    Rectangle {
        height: 80; width: 80
        anchors.bottom: parent.bottom; anchors.bottomMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20

        color : "#59000000"
        radius: 40

        Image{
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

            source: graphModel.isTimingGraphPause ? "/ui/main_scene/img/graph/play.png" : "/ui/main_scene/img/graph/pause.png"
        }

        MouseArea{
            anchors.fill: parent

            onClicked: {
                graphModel.onCommandSetTimingGraphPlayPause()
            }
        }
    }

    Component{ id : measureArea; Rectangle{ color :"#59D9001B" } }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
