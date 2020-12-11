import QtQuick 2.0
import "../../../control"
import QtQuick.Layouts 1.3
import "."
import EnumDefine 1.0
import ViewManager 1.0
import MainViewModel 1.0

Rectangle{
    property bool           isOpen : visible
    property int            overWeight
    property int            underWeight
    property int            normalWeight
    property MainViewModel  mainViewModel

    id: panel

    color: "#59000000"
    radius: 20
    //title: mainViewModel.wcTrendsOptionLastN == EnumDefine.TRENDSOPTION_TOTAL_SINCE_START ?qsTr("Trends (ALL)") : qsTr("Trends (" + mainViewModel.wcTrendsLastNValue + ")")
    //type : EnumDefine.PANEL_TYPE_WEIGHT_UP

    function drawTrends()
    {
        if(canvas.available)
        {
            canvas.requestPaint()
        }
    }

    Timer {
        interval: 1000; running: true; repeat: true
        onTriggered:
        {
            if(isOpen)
            {
                drawTrends();
            }
        }
    }

    UiLabelTitle{
        id : labelTitle
        height: 75
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        leftMargin : 20

        textValue: mainViewModel.wcTrendsOptionLastN == EnumDefine.TRENDSOPTION_TOTAL_SINCE_START ?qsTr("Trends (ALL)") : qsTr("Trends (") + mainViewModel.wcTrendsLastNValue + ")"

    }

    Rectangle {
        id: rectangle
        color: "#00000000"
        anchors.top: labelTitle.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        clip: true;

        Canvas{
            id : canvas
            enabled: false
            antialiasing: true
            smooth: false
            anchors.fill: parent
            renderTarget : Canvas.FramebufferObject

            onPaint :{
                var ctx = canvas.getContext("2d")

                ctx.reset();
                ctx.lineWidth = 5
                ctx.strokeStyle = "#0085FF"
                ctx.fillStyle = "#00000000"
                ctx.lineCap = "round"

                panel.mainViewModel.onCommandCreateSnopShot(canvas.width, canvas.height);

                overLine.y   =  panel.mainViewModel.onCommandConvertWeightToY(overWeight);
                normalLine.y =  panel.mainViewModel.onCommandConvertWeightToY(normalWeight);
                underLine.y  =  panel.mainViewModel.onCommandConvertWeightToY(underWeight);

                ctx.beginPath()

                for(var i = 0; i < panel.mainViewModel.onCommandGetSnopShotPointsCnt(); i ++)
                {                    
                    var min = panel.mainViewModel.onCommandGetMinPointAt(i);
                    var max = panel.mainViewModel.onCommandGetMaxPointAt(i);
                    var x   = panel.mainViewModel.onCommandConvertPointIdxToX(i, canvas.width);

                    if(i === 0)
                    {
                        ctx.moveTo(0,min);
                    }

                    ctx.lineTo(x,min);
                    ctx.moveTo(x,min);
                    ctx.lineTo(x,max);
                    ctx.moveTo(x,max);

                }

                ctx.stroke();

                //ctx.closePath();
            }
        }

        Rectangle{
            id : underLine
            color: "#D9001B"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            height: 2
        }

        Rectangle{
            id : normalLine
            color: "#ACACAC"  //ViewManager.mainColor
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            height: 2
        }

        Rectangle{
            id : overLine
            color: "#F59A23"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            height: 2
        }
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
            ViewManager.popupTrendsOption.isUnderToOver     = mainViewModel.wcTrendsOptionH == EnumDefine.TRENDSOPTION_H_UNDER_TO_OVER
            ViewManager.popupTrendsOption.isTotal           = mainViewModel.wcTrendsOptionFilter == EnumDefine.TRENDSOPTION_FILTER_TOTAL
            ViewManager.popupTrendsOption.isTotalSinceStart = mainViewModel.wcTrendsOptionLastN == EnumDefine.TRENDSOPTION_TOTAL_SINCE_START
            ViewManager.popupTrendsOption.lastNValue        = mainViewModel.wcTrendsLastNValue
            ViewManager.popupTrendsOption.visible = true;
        }
    }

    Connections {
        target: ViewManager.popupTrendsOption
        onSignalEventClose: {
            mainViewModel.onCommandSaveTrendsOption(ViewManager.popupTrendsOption.isUnderToOver,
                                                    ViewManager.popupTrendsOption.isTotal,
                                                    ViewManager.popupTrendsOption.isTotalSinceStart,
                                                    ViewManager.popupTrendsOption.lastNValue)
        }
    }

}
