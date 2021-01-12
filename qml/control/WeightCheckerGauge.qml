import QtQuick 2.12
import QtGraphicalEffects 1.12
import ViewManager 1.0
import EnumDef 1.0

Item {

    property int  eventType
    //property int  avgEventType
    property real under : 100
    property real underWarning : 200
    property real normal : 300
    property real overWarning : 450
    property real over : 800
    property real weight : 600
    //property real avgWeight : 700

    property real min : normal - under > over - normal ? under - ((normal - under) * 0.4):normal - ((over - normal) * 1.4)
    property real max : normal + (normal - min)
    property real range : max - min

    id: control
    width : 526
    height : 108

    Rectangle{
        id :bg
        height : 24
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        color : "#00000000"
        radius: height / 2
    }

    Rectangle{
        id :bar
        height : 14
        anchors.verticalCenter: bg.verticalCenter
        anchors.right: bg.right
        anchors.rightMargin: 5
        anchors.left: bg.left
        anchors.leftMargin: 5
        color : "#D9001B"
        radius: height / 2
/*
        Rectangle{
            id :yellow
            height : 14
            anchors.verticalCenter: red.verticalCenter
            anchors.right: red.right
            anchors.rightMargin: ((control.max - control.over) / control.range) * red.width
            anchors.left: red.left
            anchors.leftMargin: ((control.under - control.min) / control.range) * red.width
            color : "#F59A23"
        }
*/
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#D9001B"
            }

            GradientStop {
                position: ((control.underWarning - control.min) / control.range) - 0.001
                color: "#D9001B"
            }

            GradientStop {
                position: ((control.underWarning - control.min) / control.range)
                color: "#0085FF"
            }

            GradientStop {
                position: ((control.overWarning - control.min) / control.range)
                color: "#0085FF"
            }

            GradientStop {
                position: ((control.overWarning - control.min) / control.range) + 0.001
                color: "#F59A23"
            }
            GradientStop {
                position: 1
                color: "#F59A23"
            }

            orientation: Gradient.Horizontal
        }
/*
        Rectangle{
            id :blue
            height : 14
            anchors.verticalCenter: red.verticalCenter
            anchors.right: red.right
            anchors.rightMargin: ((control.max - control.overWarning) / control.range) * red.width
            anchors.left: red.left
            anchors.leftMargin: ((control.underWarning - control.min) / control.range) * red.width
            color : "#0085FF"
        }
        */
    }

    Image{
        id : gaugeWeight
        anchors.left: bar.left
        anchors.leftMargin: weight < control.min ?  - 20 - (width / 2) : weight > control.max ? (bar.width - width / 2) + 20 :  (bar.width * ((weight - control.min) / control.range) - (width / 2))
        anchors.top: parent.top
        anchors.topMargin: 0
        source: eventType == EnumDef.ET_WEIGHT_OVER  ? "img_weightcheckergauage/big_down_yellow.png" :
                eventType == EnumDef.ET_WEIGHT_UNDER ? "img_weightcheckergauage/big_down_red.png" : "img_weightcheckergauage/big_down_blue.png"



                                                           //||  eventType == EnumDefine.WEIGHT_UNDER_TYPE? "img_weightcheckergauage/big_down_red.png":
                //eventType == EnumDefine.WEIGHT_OVER_WARNING_TYPE || eventType == EnumDefine.WEIGHT_UNDER_WARNING_TYPE ? "img_weightcheckergauage/big_down_yellow.png" :
                //"img_weightcheckergauage/big_down_blue.png"
        visible: true
    }
/*
    DropShadow {
        anchors.fill: gaugeWeight
        horizontalOffset: 5
        verticalOffset:5
        radius: 20
        samples: 17
        color: "#000000"
        source: gaugeWeight
        cached: true
    }
*/
    Glow {
        anchors.fill: gaugeWeight
        radius: 15
        samples: 17
        color: eventType == EnumDef.ET_WEIGHT_OVER  ? "#59F59A23" :
               eventType == EnumDef.ET_WEIGHT_UNDER ? "#59D9001B" : "#590085FF"
        source: gaugeWeight
    }
/*
    Image{
        id : gaugeAvgWeight
        rotation: 180
        anchors.left: red.left
        anchors.leftMargin: avgWeight < control.min ? - 20 - (width / 2) : avgWeight > control.max ? (red.width - width / 2) + 20 :  (red.width * ((avgWeight - control.min) / control.range) - (width / 2))
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        source: avgEventType == EnumDefine.WEIGHT_OVER_TYPE ||  avgEventType == EnumDefine.WEIGHT_UNDER_TYPE? "img_weightcheckergauage/big_down_red.png":
                avgEventType == EnumDefine.WEIGHT_OVER_WARNING_TYPE || avgEventType == EnumDefine.WEIGHT_UNDER_WARNING_TYPE ? "img_weightcheckergauage/big_down_yellow.png" :
                "img_weightcheckergauage/big_down_blue.png"
        visible: true
    }

    DropShadow {
        anchors.fill: gaugeAvgWeight
        horizontalOffset: -5
        verticalOffset:-5
        radius: 5
        rotation: 180
        samples: 17
        color: "#000000"
        source: gaugeAvgWeight
        cached: true
    }

    Glow {
        anchors.fill: gaugeAvgWeight
        rotation: 180
        radius: 15
        samples: 17
        color: avgEventType == EnumDefine.WEIGHT_OVER_TYPE ||  avgEventType == EnumDefine.WEIGHT_UNDER_TYPE? "#59D9001B":
               avgEventType == EnumDefine.WEIGHT_OVER_WARNING_TYPE || avgEventType == EnumDefine.WEIGHT_UNDER_WARNING_TYPE ? "#59F59A23" :
               "#590085FF"
        source: gaugeAvgWeight
    }*/
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
